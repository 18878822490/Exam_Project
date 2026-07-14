package com.exam.exam_platform.dto;

import lombok.Data;

@Data
public class PracticeAnswerRequest {
    private Long studentId;
    private String studentName;
    private String studentNo;
    private Long questionId;
    private String answer;
    private Boolean correct;
    private String practiceMode;
}
