package com.exam.exam_platform.dto;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class QuestionImportResult {
    private Long logId;
    private String type;
    private String fileName;
    private int totalCount;
    private int successCount;
    private int failedCount;
    private String status;
    private String message;
}
