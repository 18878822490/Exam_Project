package com.exam.exam_platform.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class Student {
    private Long id;
    private String username;
    private String password;
    private String name;
    private String studentNo;
    private String major;
    private Long classId;
    private String className;
    private LocalDateTime createdTime;
}
