package com.exam.exam_platform.dto;

import lombok.Data;

@Data
public class ReviewScoreRequest {
    private Long answerId;
    private Long teacherId;
    private Double score;
    private String comment;
}
