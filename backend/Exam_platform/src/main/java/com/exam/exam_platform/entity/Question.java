package com.exam.exam_platform.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class Question {
    private Long id;
    private String subject;
    private String type;
    private String content;
    private String optionA;
    private String optionB;
    private String optionC;
    private String optionD;
    private String answer;
    private String analysis;
    private String difficulty;
    private String knowledgePoint;
    private Integer score;
    private Long createdBy;
    private LocalDateTime createdTime;
}
