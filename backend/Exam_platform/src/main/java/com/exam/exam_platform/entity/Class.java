package com.exam.exam_platform.entity;

import lombok.Data;
import java.time.LocalDateTime;
import java.util.List;

@Data
public class Class {
    private Long id;
    private String className;
    private String subject;
    private String theme;
    private LocalDateTime createdTime;

    // 临时字段：该班级所有任课教师（页面展示使用）
    private transient List<Teacher> teacherList;
}