package com.exam.exam_platform.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class OperationLog {
    private Long id;
    private Long userId;
    private String action;
    private String detail;
    private LocalDateTime createdTime;
}