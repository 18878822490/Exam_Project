package com.exam.exam_platform.dto;

import com.exam.exam_platform.entity.Question;
import lombok.Data;

import java.util.List;

@Data
public class BatchQuestionImportRequest {
    private Long userId;
    private String importType;
    private String fileName;
    private List<Question> questions;
}
