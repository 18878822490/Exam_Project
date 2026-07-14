package com.exam.exam_platform.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class Exam {
    private Long id;
    private String title;
    private String subject;
    private LocalDateTime startTime;
    private LocalDateTime endTime;
    private Integer duration;
    private Integer totalScore;
    private String status;
    private String flowStatus;
    private Long createdBy;
    private LocalDateTime createdTime;
    private String className;
    private Integer participants;
    private Integer publishedCount;
    private Integer targetStudentCount;
    private Integer pendingReviewCount;
    private Integer reviewedStudents;
    private Double average;
}
