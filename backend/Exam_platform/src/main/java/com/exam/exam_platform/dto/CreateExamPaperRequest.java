package com.exam.exam_platform.dto;

import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

@Data
public class CreateExamPaperRequest {
    private String title;
    private String subject;
    private LocalDateTime startTime;
    private LocalDateTime endTime;
    private Integer duration;
    private Long createdBy;
    private String difficulty;
    private String knowledgePoint;
    private Map<String, Integer> typeCounts;
    private List<Long> questionIds;
}
