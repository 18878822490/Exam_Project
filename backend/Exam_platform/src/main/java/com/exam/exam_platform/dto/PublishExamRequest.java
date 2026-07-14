package com.exam.exam_platform.dto;

import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
public class PublishExamRequest {
    private Long examId;
    private Long createdBy;
    private List<Long> classIds;
    private List<String> classNames;
    private LocalDateTime startTime;
    private LocalDateTime endTime;
    private String status;
}
