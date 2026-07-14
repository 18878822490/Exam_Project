package com.exam.exam_platform.dto;

import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
public class LoginResponse {
    private Long userId;
    private String username;
    private String role;
    private String name;
    private String studentNo;
    private String className;
    private Long teacherId;
    private String subject;
    private List<String> classNames = new ArrayList<>();
}
