package com.exam.exam_platform.dto;

import jakarta.validation.constraints.NotBlank;
import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
public class RegisterRequest {
    @NotBlank(message = "用户名不能为空")
    private String username;

    @NotBlank(message = "密码不能为空")
    private String password;

    @NotBlank(message = "身份不能为空")
    private String role;

    private String name;
    private String studentNo;
    private String major;
    private String classNumber;
    private String className;
    private List<String> classNames = new ArrayList<>();
    private String subject;
    private String phone;
}
