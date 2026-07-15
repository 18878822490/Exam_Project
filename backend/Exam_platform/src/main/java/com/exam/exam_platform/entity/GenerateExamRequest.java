package com.exam.exam_platform.entity;

import lombok.Data;

@Data
public class GenerateExamRequest {
    private String title;
    private Integer duration;
    private Integer questionCount;
    private Integer maxTotalScore;
    private String difficulty;
    private String knowledgePoint;
    private Long createdBy;
}
