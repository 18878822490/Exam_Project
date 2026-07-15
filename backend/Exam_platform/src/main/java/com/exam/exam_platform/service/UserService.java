package com.exam.exam_platform.service;

import com.exam.exam_platform.dto.LoginRequest;
import com.exam.exam_platform.dto.LoginResponse;
import com.exam.exam_platform.dto.RegisterRequest;
import com.exam.exam_platform.entity.Admin;
import com.exam.exam_platform.entity.Student;
import com.exam.exam_platform.entity.Teacher;
import com.exam.exam_platform.mapper.UserMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@Service
public class UserService {
    private static final Map<String, List<String>> CLASSES_BY_MAJOR = new LinkedHashMap<>();

    static {
        CLASSES_BY_MAJOR.put("软件工程", List.of("软工01", "软工02", "软工03"));
        CLASSES_BY_MAJOR.put("计算机科学与技术", List.of("计科01"));
        CLASSES_BY_MAJOR.put("信息网络", List.of("信网01"));
        CLASSES_BY_MAJOR.put("大数据", List.of("大数据01班"));
    }

    private final UserMapper userMapper;
    private final OperationLogService operationLogService;

    public UserService(UserMapper userMapper, OperationLogService operationLogService) {
        this.userMapper = userMapper;
        this.operationLogService = operationLogService;
    }

    @PostConstruct
    public void initializeCatalog() {
        userMapper.initSchema();
        userMapper.ensureDefaultClasses(CLASSES_BY_MAJOR);
    }

    public LoginResponse login(LoginRequest request) {
        UserMapper.AccountRecord account = userMapper.findByUsernameAndPassword(
                requireText(request.getUsername(), "用户名不能为空"),
                requireText(request.getPassword(), "密码不能为空")
        );
        if (account == null) {
            throw new IllegalArgumentException("用户名或密码错误");
        }
        return toResponse(account);
    }

    public void logout(Map<String, Object> payload) {
        Long userId = longValue(payload, "userId", payload == null ? null : payload.get("user_id"));
        if (userId == null || userId <= 0) {
            throw new IllegalArgumentException("用户ID不能为空");
        }
        String role = normalizeRole(stringValue(payload, "role", payload == null ? null : payload.get("userRole")));
        String username = stringValue(payload, "username", null);
        operationLogService.record(userId,
                "USER_LOGOUT_" + role,
                username.isBlank() ? "退出登录" : "退出登录：" + username);
    }

    @Transactional
    public LoginResponse register(RegisterRequest request) {
        String username = requireText(request.getUsername(), "用户名不能为空");
        String role = normalizeRole(request.getRole());

        if (userMapper.existsByUsername(username)) {
            throw new IllegalArgumentException("用户名已存在");
        }

        if ("STUDENT".equals(role)) {
            return registerStudent(request, username);
        }
        if ("TEACHER".equals(role)) {
            return registerTeacher(request, username);
        }
        return registerAdmin(request, username);
    }

    public List<String> listClasses() {
        return userMapper.listClassNames();
    }

    public List<Map<String, Object>> listTeacherClasses(Long teacherId) {
        return userMapper.listTeacherClasses(teacherId);
    }

    public List<Map<String, Object>> listStudentsByClassName(String className) {
        return userMapper.listStudentsByClassName(requireText(className, "班级不能为空"));
    }

    public List<Map<String, Object>> listStudentsForAdmin(String keyword, String className, Integer limit) {
        return userMapper.listStudentsForAdmin(keyword, className, limit);
    }

    public Map<String, Object> studentAdminStats() {
        return userMapper.studentAdminStats();
    }

    public List<Map<String, Object>> listTeachersForAdmin(String keyword, Integer limit) {
        return userMapper.listTeachersForAdmin(keyword, limit);
    }

    public Map<String, Object> teacherAdminStats() {
        return userMapper.teacherAdminStats();
    }

    @Transactional
    public Map<String, Object> createStudentForAdmin(RegisterRequest request) {
        request.setRole("STUDENT");
        if (!nonBlank(request.getPassword())) {
            request.setPassword("123456");
        }
        LoginResponse response = register(request);
        return findStudentById(response.getUserId());
    }

    @Transactional
    public Map<String, Object> createTeacherForAdmin(RegisterRequest request) {
        request.setRole("TEACHER");
        if (!nonBlank(request.getPassword())) {
            request.setPassword("123456");
        }
        LoginResponse response = register(request);
        return findTeacherById(response.getUserId());
    }

    public Map<String, Object> findTeacherById(Long teacherId) {
        if (teacherId == null) {
            throw new IllegalArgumentException("教师ID不能为空");
        }
        Map<String, Object> teacher = userMapper.findTeacherById(teacherId);
        if (teacher == null) {
            throw new IllegalArgumentException("教师不存在");
        }
        return teacher;
    }

    public Map<String, Object> findStudentById(Long studentId) {
        if (studentId == null) {
            throw new IllegalArgumentException("学生ID不能为空");
        }
        Map<String, Object> student = userMapper.findStudentById(studentId);
        if (student == null) {
            throw new IllegalArgumentException("学生不存在");
        }
        return student;
    }

    @Transactional
    public Map<String, Object> updateStudentProfile(Long studentId, Map<String, Object> payload) {
        Map<String, Object> current = findStudentById(studentId);
        String name = requireText(stringValue(payload, "name", current.get("name")), "姓名不能为空");
        String studentNo = requireText(stringValue(payload, "studentNo", payload.getOrDefault("student_no", current.get("student_no"))), "学号不能为空");
        if (userMapper.existsByStudentNoExceptId(studentNo, studentId)) {
            throw new IllegalArgumentException("学号已被其他学生使用");
        }
        String major = requireText(stringValue(payload, "major", current.get("major")), "专业不能为空");
        String className = requireText(stringValue(payload, "className", payload.getOrDefault("class_name", current.get("class_name"))), "班级不能为空");
        Long classId = ensureClass(className, major);
        if (!userMapper.updateStudentProfile(studentId, name, studentNo, major, classId, className)) {
            throw new IllegalArgumentException("学生不存在");
        }
        operationLogService.record(studentId, "USER_UPDATE_STUDENT", "修改学生信息：" + name + " / " + studentNo);
        return findStudentById(studentId);
    }

    @Transactional
    public Map<String, Object> updateTeacherProfile(Long teacherId, Map<String, Object> payload) {
        Map<String, Object> current = findTeacherById(teacherId);
        String name = requireText(stringValue(payload, "name", current.get("name")), "姓名不能为空");
        String subject = requireText(stringValue(payload, "subject", current.get("subject")), "任教学科不能为空");
        String phone = requireText(stringValue(payload, "phone", current.get("phone")), "手机号不能为空");
        String email = stringValue(payload, "email", current.get("email"));
        if (!userMapper.updateTeacherProfile(teacherId, name, subject, phone, email)) {
            throw new IllegalArgumentException("教师不存在");
        }
        operationLogService.record(teacherId, "USER_UPDATE_TEACHER", "修改教师信息：" + name + " / " + subject);
        return findTeacherById(teacherId);
    }

    @Transactional
    public void changePassword(String role, Long userId, Map<String, Object> payload) {
        if (userId == null) {
            throw new IllegalArgumentException("用户ID不能为空");
        }
        String oldPassword = requireText(stringValue(payload, "oldPassword", payload.get("old_password")), "原密码不能为空");
        String newPassword = requireText(stringValue(payload, "newPassword", payload.get("new_password")), "新密码不能为空");
        if (newPassword.length() < 6) {
            throw new IllegalArgumentException("新密码至少 6 位");
        }
        String tableName = switch (normalizeRole(role)) {
            case "STUDENT" -> "students";
            case "TEACHER" -> "teachers";
            case "ADMIN" -> "admins";
            default -> throw new IllegalArgumentException("身份类型不正确");
        };
        if (!userMapper.updatePassword(tableName, userId, oldPassword, newPassword)) {
            throw new IllegalArgumentException("原密码错误或用户不存在");
        }
        operationLogService.record(userId, "PASSWORD_CHANGE_" + normalizeRole(role), "修改登录密码");
    }

    private LoginResponse registerStudent(RegisterRequest request, String username) {
        String studentNo = requireText(request.getStudentNo(), "学生必须填写学号");
        if (userMapper.existsByStudentNo(studentNo)) {
            throw new IllegalArgumentException("学号已存在");
        }
        String major = requireText(request.getMajor(), "学生必须选择专业");
        String className = resolveStudentClassName(request, major);
        Long classId = ensureClass(className, major);

        Student student = new Student();
        student.setUsername(username);
        student.setPassword(request.getPassword());
        student.setName(nonBlank(request.getName()) ? request.getName().trim() : username);
        student.setStudentNo(studentNo);
        student.setMajor(major);
        student.setClassId(classId);
        student.setClassName(className);
        userMapper.insertStudent(student);
        operationLogService.record(student.getId(), "USER_REGISTER_STUDENT",
                "学生注册：" + student.getName() + " / " + student.getStudentNo());

        return toResponse(new UserMapper.AccountRecord(
                student.getId(),
                student.getUsername(),
                "STUDENT",
                student.getName(),
                student.getStudentNo(),
                student.getClassId(),
                student.getClassName(),
                student.getMajor(),
                null
        ));
    }

    private LoginResponse registerTeacher(RegisterRequest request, String username) {
        List<String> classNames = normalizeTeacherClassNames(request);
        if (classNames.isEmpty()) {
            throw new IllegalArgumentException("教师必须选择至少一个所教班级");
        }

        Teacher teacher = new Teacher();
        teacher.setUsername(username);
        teacher.setPassword(request.getPassword());
        teacher.setName(nonBlank(request.getName()) ? request.getName().trim() : username);
        teacher.setSubject(requireText(request.getSubject(), "教师必须选择所任科目"));
        teacher.setPhone(requireText(request.getPhone(), "教师必须填写手机号"));
        userMapper.insertTeacher(teacher);

        for (String className : classNames) {
            Long classId = ensureClass(className, majorForClassName(className));
            userMapper.bindTeacherClass(teacher.getId(), classId);
        }
        operationLogService.record(teacher.getId(), "USER_REGISTER_TEACHER",
                "教师注册：" + teacher.getName() + " / " + teacher.getSubject());

        LoginResponse response = toResponse(new UserMapper.AccountRecord(
                teacher.getId(),
                teacher.getUsername(),
                "TEACHER",
                teacher.getName(),
                null,
                null,
                null,
                null,
                teacher.getSubject()
        ));
        response.setClassNames(userMapper.findTeacherClassNames(teacher.getId()));
        return response;
    }

    private LoginResponse registerAdmin(RegisterRequest request, String username) {
        Admin admin = new Admin();
        admin.setUsername(username);
        admin.setPassword(request.getPassword());
        admin.setName(nonBlank(request.getName()) ? request.getName().trim() : username);
        admin.setPhone(requireText(request.getPhone(), "管理员必须填写手机号"));
        userMapper.insertAdmin(admin);
        operationLogService.record(admin.getId(), "USER_REGISTER_ADMIN", "管理员注册：" + admin.getName());

        return toResponse(new UserMapper.AccountRecord(
                admin.getId(),
                admin.getUsername(),
                "ADMIN",
                admin.getName(),
                null,
                null,
                null,
                null,
                null
        ));
    }

    private LoginResponse toResponse(UserMapper.AccountRecord account) {
        LoginResponse response = new LoginResponse();
        response.setUserId(account.id());
        response.setUsername(account.username());
        response.setRole(account.role());
        response.setName(account.name());
        response.setStudentNo(account.studentNo());
        response.setClassName(account.className());
        response.setSubject(account.subject());

        if ("TEACHER".equals(account.role())) {
            response.setTeacherId(account.id());
            response.setClassNames(userMapper.findTeacherClassNames(account.id()));
        }

        return response;
    }

    private Long ensureClass(String className, String major) {
        Long classId = userMapper.findClassIdByName(className);
        return classId != null ? classId : userMapper.insertClass(className, major);
    }

    private String resolveStudentClassName(RegisterRequest request, String major) {
        String className = nonBlank(request.getClassName())
                ? request.getClassName().trim()
                : request.getClassNumber() == null ? "" : request.getClassNumber().trim();
        if (!nonBlank(className)) {
            throw new IllegalArgumentException("学生必须选择班级");
        }
        if (!validClassForMajor(major, className)) {
            throw new IllegalArgumentException("该专业下没有这个班级");
        }
        return className;
    }

    private List<String> normalizeTeacherClassNames(RegisterRequest request) {
        LinkedHashSet<String> classNames = new LinkedHashSet<>();
        if (request.getClassNames() != null) {
            for (String className : request.getClassNames()) {
                if (nonBlank(className)) {
                    classNames.add(className.trim());
                }
            }
        }
        if (classNames.isEmpty() && nonBlank(request.getClassName())) {
            classNames.add(request.getClassName().trim());
        }
        for (String className : classNames) {
            if (!allClassNames().contains(className)) {
                throw new IllegalArgumentException("教师所教班级不在可选范围内：" + className);
            }
        }
        return new ArrayList<>(classNames);
    }

    private boolean validClassForMajor(String major, String className) {
        String databaseMajor = userMapper.findClassMajorByName(className);
        if (databaseMajor != null) {
            return !nonBlank(databaseMajor) || databaseMajor.equals(major);
        }

        List<String> classNames = CLASSES_BY_MAJOR.get(major);
        return classNames != null && classNames.contains(className);
    }

    private List<String> allClassNames() {
        LinkedHashSet<String> names = new LinkedHashSet<>(userMapper.listClassNames());
        CLASSES_BY_MAJOR.values().forEach(names::addAll);
        return new ArrayList<>(names);
    }

    private String majorForClassName(String className) {
        String databaseMajor = userMapper.findClassMajorByName(className);
        if (databaseMajor != null) {
            return databaseMajor;
        }

        for (Map.Entry<String, List<String>> entry : CLASSES_BY_MAJOR.entrySet()) {
            if (entry.getValue().contains(className)) {
                return entry.getKey();
            }
        }
        return null;
    }

    private String normalizeRole(String role) {
        String trimmed = requireText(role, "身份不能为空");
        if ("学生".equals(trimmed)) {
            return "STUDENT";
        }
        if ("教师".equals(trimmed) || "老师".equals(trimmed)) {
            return "TEACHER";
        }
        if ("管理员".equals(trimmed)) {
            return "ADMIN";
        }

        String upper = trimmed.toUpperCase(Locale.ROOT);
        if ("STUDENT".equals(upper) || "TEACHER".equals(upper) || "ADMIN".equals(upper)) {
            return upper;
        }
        throw new IllegalArgumentException("身份类型不正确");
    }

    private String requireText(String value, String message) {
        if (!nonBlank(value)) {
            throw new IllegalArgumentException(message);
        }
        return value.trim();
    }

    private boolean nonBlank(String value) {
        return value != null && !value.trim().isEmpty();
    }

    private String stringValue(Map<String, Object> payload, String key, Object fallback) {
        if (payload != null && payload.containsKey(key) && payload.get(key) != null) {
            return String.valueOf(payload.get(key)).trim();
        }
        return fallback == null ? "" : String.valueOf(fallback).trim();
    }

    private Long longValue(Map<String, Object> payload, String key, Object fallback) {
        Object value = payload != null && payload.containsKey(key) ? payload.get(key) : fallback;
        if (value == null) {
            return null;
        }
        if (value instanceof Number number) {
            return number.longValue();
        }
        String text = String.valueOf(value).trim();
        return text.isEmpty() ? null : Long.parseLong(text);
    }
}
