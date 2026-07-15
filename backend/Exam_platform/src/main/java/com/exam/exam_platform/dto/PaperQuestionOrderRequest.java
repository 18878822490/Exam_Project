package com.exam.exam_platform.dto;

import lombok.Data;

import java.util.List;

@Data
public class PaperQuestionOrderRequest {
    private List<Item> questions;
    private List<Long> questionIds;
    private Integer maxTotalScore;
    private Long userId;

    @Data
    public static class Item {
        private Long questionId;
        private Integer score;
        private Integer sortNo;
    }
}
