package com.exam.exam_platform.dto;

import lombok.Data;

@Data
public class PaperQuestionRequest {
    private Long questionId;
    private Integer score;
    private Integer sortNo;
    private Integer maxTotalScore;
    private Long userId;
}
