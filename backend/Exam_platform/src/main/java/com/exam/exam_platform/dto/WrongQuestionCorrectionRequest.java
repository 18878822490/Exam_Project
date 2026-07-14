package com.exam.exam_platform.dto;

import lombok.Data;

@Data
public class WrongQuestionCorrectionRequest {
    private Long answerId;
    private String sourceType;
    private String studentNo;
    private String correctionAnswer;
    private String errorReason;
    private String knowledgeSummary;
}
