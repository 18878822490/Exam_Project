package com.exam.exam_platform.service;

import com.exam.exam_platform.entity.OperationLog;
import com.exam.exam_platform.mapper.OperationLogMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class OperationLogService {
    private final OperationLogMapper operationLogMapper;

    public OperationLogService(OperationLogMapper operationLogMapper) {
        this.operationLogMapper = operationLogMapper;
    }

    @PostConstruct
    public void initializeSchema() {
        operationLogMapper.initSchema();
    }

    public Long record(Long userId, String action, String detail) {
        OperationLog log = new OperationLog();
        log.setUserId(userId);
        log.setAction(action);
        log.setDetail(detail);
        return operationLogMapper.insert(log);
    }

    public List<OperationLog> list(Long userId, String action, Integer limit) {
        return operationLogMapper.list(userId, action, limit == null ? 50 : limit);
    }
}
