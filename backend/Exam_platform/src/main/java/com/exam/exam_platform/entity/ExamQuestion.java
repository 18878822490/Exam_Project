package com.exam.exam_platform.entity;

import lombok.Data;

@Data
public class ExamQuestion {
    private Long id;
    private Long examId;
    private Long questionId;
    private Integer sortNo;
    private Integer score;
}