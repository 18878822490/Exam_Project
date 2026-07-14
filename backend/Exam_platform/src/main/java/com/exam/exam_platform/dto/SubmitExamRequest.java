package com.exam.exam_platform.dto;

import lombok.Data;

import java.util.Map;

@Data
public class SubmitExamRequest {
    private Long examId;
    private Long studentId;
    private String studentName;
    private String studentNo;
    private String className;
    private Map<Long, String> answers;
}
