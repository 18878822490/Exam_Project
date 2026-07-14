package com.exam.exam_platform.dto;

import lombok.Data;

@Data
public class QuestionImportLogRequest {
    private Long userId;
    private String importType;
    private String fileName;
    private Integer totalCount;
    private Integer successCount;
    private Integer failedCount;
    private String status;
    private String message;
}
