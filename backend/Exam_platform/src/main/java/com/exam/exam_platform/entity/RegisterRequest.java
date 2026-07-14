package com.exam.exam_platform.entity;

import lombok.Data;

@Data
public class RegisterRequest {
    private String username;
    private String password;
    private String role;
    private String name;
    private String className;
}