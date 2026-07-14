package com.exam.exam_platform.entity;

import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
public class Teacher {
    private Long id;
    private String username;
    private String password;
    private String name;
    private String subject;
    private String phone;
    private LocalDateTime createdTime;

    private transient List<String> classNames;
}
