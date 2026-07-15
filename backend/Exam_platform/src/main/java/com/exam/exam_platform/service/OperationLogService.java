package com.exam.exam_platform.service;

import com.exam.exam_platform.entity.OperationLog;
import com.exam.exam_platform.mapper.OperationLogMapper;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

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

    public Map<String, Object> dashboard(Long userId, String action, Integer limit) {
        Map<String, Object> result = new LinkedHashMap<>();
        result.put("stats", operationLogMapper.stats());
        result.put("logs", operationLogMapper.listRows(userId, action, limit == null ? 80 : limit));
        return result;
    }
}
