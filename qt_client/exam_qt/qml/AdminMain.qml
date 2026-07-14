import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#f3f6fb"
    clip: true

    property string currentMenu: "系统概览"
    property string keyword: ""
    property int profileSubPage: 0
    property bool innerScrollActive: false
    property bool narrowShell: width < 980
    property bool compactShell: width < 980
    property bool mediumShell: width < 1440
    property bool largeShell: width >= 1680 && height >= 900
    property real contentScale: narrowShell ? 1.0 : Math.max(1.06, Math.min(1.26, Math.min(width / 1360, height / 820)))
    property int shellMargin: narrowShell ? 18 : Math.round((mediumShell ? 42 : 52) * contentScale)
    property int sidebarWidth: narrowShell ? 96 : (compactShell ? 110 : Math.min(Math.round((mediumShell ? 326 : 352) * contentScale), Math.round(width * 0.27)))
    property int topbarHeight: narrowShell ? 86 : Math.round((mediumShell ? 104 : 116) * contentScale)
    property int gap: Math.round(18 * contentScale)
    property int smallFont: Math.round(17 * contentScale)
    property int bodyFont: Math.round(19 * contentScale)
    property int strongFont: Math.round(21 * contentScale)
    property int navFont: Math.round(25 * contentScale)
    property int panelTitleFont: Math.round(25 * contentScale)
    property int pageTitleFont: Math.round(39 * contentScale)
    property int statValueFont: Math.round(35 * contentScale)
    property int tableHeaderFont: Math.round(18 * contentScale)
    property int tableCellFont: Math.round(19 * contentScale)
    property int tableHeaderHeight: Math.round(62 * contentScale)
    property int tableRowHeight: Math.round(70 * contentScale)
    property int cardRadius: Math.round(12 * contentScale)
    property var studentManagementData: ({})
    property var teacherManagementData: ({})

    function formatCount(value) {
        var text = String(value === undefined || value === null ? "0" : value)
        if (!/^\d+$/.test(text)) {
            return text
        }
        return text.replace(/\B(?=(\d{3})+(?!\d))/g, ",")
    }

    function metricValue(stats, label, fallback, useComma) {
        var list = stats || []
        for (var i = 0; i < list.length; ++i) {
            if (list[i].label === label) {
                return useComma ? formatCount(list[i].value) : String(list[i].value)
            }
        }
        return useComma ? formatCount(fallback) : String(fallback)
    }

    function applyManagementData(pageInfo, data) {
        if (!data || !data.loaded) {
            return pageInfo
        }
        if (data.stats && data.stats.length > 0) {
            pageInfo.stats = data.stats
        }
        if (data.rows && data.rows.length > 0) {
            pageInfo.rows = data.rows
        }
        if (data.detailRows && data.detailRows.length > 0) {
            pageInfo.detailRows = data.detailRows
        }
        if (data.workflowPanels && data.workflowPanels.length > 0) {
            pageInfo.workflowPanels = data.workflowPanels
        }
        if (data.focusCards && data.focusCards.length > 0) {
            pageInfo.focusCards = data.focusCards
        }
        return pageInfo
    }

    function updateOverviewStatCards() {
        statCards = [
            {"title": "学生总数", "value": metricValue(studentManagementData.stats, "学生总数", "0", true), "delta": metricValue(studentManagementData.stats, "今日新增", "0", false), "icon": "users", "from": "#64a8ff", "to": "#245df0"},
            {"title": "教师总数", "value": metricValue(teacherManagementData.stats, "教师总数", "0", true), "delta": metricValue(teacherManagementData.stats, "今日新增", "0", false), "icon": "teacher", "from": "#35d48a", "to": "#09aa57"},
            {"title": "考试总数", "value": "128", "delta": "8", "icon": "exam", "from": "#8b7cff", "to": "#4f46e5"},
            {"title": "试卷总数", "value": "256", "delta": "12", "icon": "paper", "from": "#ff9a37", "to": "#f36b16"},
            {"title": "今日参考人数", "value": "568", "delta": "45", "icon": "today", "from": "#62a8ff", "to": "#2364e8"}
        ]
    }

    function refreshAdminData() {
        var studentData = adminApi.getStudentManagementData()
        if (studentData && studentData.loaded) {
            studentManagementData = studentData
        }
        var teacherData = adminApi.getTeacherManagementData()
        if (teacherData && teacherData.loaded) {
            teacherManagementData = teacherData
        }
        updateOverviewStatCards()
    }

    function switchMenu(name) {
        currentMenu = name
        keyword = ""
        innerScrollActive = false
        contentScroll.contentY = 0
        if (name === "系统概览" || name === "学生管理" || name === "教师管理") {
            refreshAdminData()
        }
    }

    function openAdminProfile(page) {
        profileSubPage = page
        switchMenu("个人中心")
    }

    function statusBg(text) {
        var value = String(text)
        if (value.indexOf("正常") >= 0 || value.indexOf("通过") >= 0 || value.indexOf("启用") >= 0
                || value.indexOf("成功") >= 0 || value.indexOf("已发布") >= 0 || value.indexOf("已结束") >= 0) {
            return "#dcfce7"
        }
        if (value.indexOf("进行中") >= 0 || value.indexOf("监控中") >= 0) {
            return "#dbeafe"
        }
        if (value.indexOf("待") >= 0 || value.indexOf("草稿") >= 0 || value.indexOf("未开始") >= 0
                || value.indexOf("需") >= 0 || value.indexOf("处理中") >= 0) {
            return "#fff7ed"
        }
        if (value.indexOf("冻结") >= 0 || value.indexOf("异常") >= 0 || value.indexOf("未处理") >= 0) {
            return "#fee2e2"
        }
        return "#f1f5f9"
    }

    function statusFg(text) {
        var value = String(text)
        if (value.indexOf("正常") >= 0 || value.indexOf("通过") >= 0 || value.indexOf("启用") >= 0
                || value.indexOf("成功") >= 0 || value.indexOf("已发布") >= 0 || value.indexOf("已结束") >= 0) {
            return "#16a34a"
        }
        if (value.indexOf("进行中") >= 0 || value.indexOf("监控中") >= 0) {
            return "#2563eb"
        }
        if (value.indexOf("待") >= 0 || value.indexOf("草稿") >= 0 || value.indexOf("未开始") >= 0
                || value.indexOf("需") >= 0 || value.indexOf("处理中") >= 0) {
            return "#f97316"
        }
        if (value.indexOf("冻结") >= 0 || value.indexOf("异常") >= 0 || value.indexOf("未处理") >= 0) {
            return "#dc2626"
        }
        return "#64748b"
    }

    function pageMetrics(page) {
        var values = {
            "学生管理": ["3,245", "42", "18", "98.6%"],
            "教师管理": ["156", "5", "3", "99.2%"],
            "管理员管理": ["12", "1", "2", "100%"],
            "题目管理": ["9,826", "126", "34", "96.8%"],
            "题库管理": ["38", "4", "6", "92.5%"],
            "题目审核": ["86", "24", "62", "71.0%"],
            "考试管理": ["128", "7", "11", "97.4%"],
            "试卷管理": ["256", "18", "36", "94.0%"],
            "考试监控": ["9", "568", "4", "89.5%"],
            "成绩管理": ["4,218", "31", "7", "93.6%"],
            "角色权限": ["6", "12", "3", "100%"],
            "操作日志": ["18,902", "415", "0", "100%"],
            "系统设置": ["24", "3", "1", "稳定"],
            "数据备份": ["31", "1", "0", "100%"]
        }
        return values[page] || ["128", "8", "12", "96%"]
    }

    function pageData(page) {
        var metrics = pageMetrics(page)
        var commonStats = [
            {"label": "总量", "value": metrics[0], "color": "#2563eb"},
            {"label": "今日新增", "value": metrics[1], "color": "#16a34a"},
            {"label": "待处理", "value": metrics[2], "color": "#f97316"},
            {"label": "正常率", "value": metrics[3], "color": "#7c3aed"}
        ]

        var map = {
            "学生管理": {
                "title": "学生管理",
                "subtitle": "维护学生注册审核、基础信息、考试记录与成绩档案",
                "primary": "新增学生",
                "headers": ["学号", "姓名", "班级", "注册审核", "考试情况", "平均分", "操作"],
                "weights": [1.18, 0.8, 0.9, 0.9, 1.15, 0.72, 1.0],
                "statusIndex": 3,
                "stats": [
                    {"label": "学生总数", "value": "3,245", "color": "#2563eb"},
                    {"label": "今日新增", "value": "42", "color": "#16a34a"},
                    {"label": "待审核注册", "value": "18", "color": "#f97316"},
                    {"label": "平均参考率", "value": "98.6%", "color": "#7c3aed"}
                ],
                "tags": [
                    {"text": "注册审核", "color": "#2563eb"},
                    {"text": "信息维护", "color": "#16a34a"},
                    {"text": "考试成绩", "color": "#f97316"}
                ],
                "actions": [
                    {"title": "新增学生", "detail": "按数据库字段录入学号、姓名、班级、专业、手机号和登录账号。", "accent": "#2563eb"},
                    {"title": "注册审核", "detail": "核对学号、班级和身份信息后通过或退回注册申请。", "accent": "#f97316"},
                    {"title": "信息修改", "detail": "支持修改班级、专业、联系方式、账号状态和重置密码。", "accent": "#16a34a"},
                    {"title": "考试成绩档案", "detail": "查看该生参加考试、缺考记录、分数趋势和成绩导出记录。", "accent": "#7c3aed"}
                ],
                "focusCards": [
                    {"title": "注册审核", "value": "18 人", "detail": "待核对学号、班级、专业与身份信息", "accent": "#f97316"},
                    {"title": "信息修改", "value": "42 条", "detail": "今日新增或调整学生基础资料", "accent": "#2563eb"},
                    {"title": "考试与成绩", "value": "3,245 份", "detail": "可查看个人考试记录、缺考和分数趋势", "accent": "#16a34a"}
                ],
                "workflowPanels": [
                    {
                        "title": "注册审核与信息维护",
                        "headers": ["管理事项", "学生", "当前状态", "处理动作"],
                        "weights": [0.95, 1.05, 1.18, 1.2],
                        "statusIndex": 2,
                        "rows": [
                            ["注册审核", "陈可 / 20260202006", "待审核", "核对学号、专业、班级后通过或退回"],
                            ["资料修改", "石晓虹 / 软工01", "正常", "修改手机号、班级、专业或重置密码"],
                            ["批量新增", "今日导入名单", "42 条", "补全学号、班级、登录账号后入库"],
                            ["账号处理", "李明 / 大数据01班", "冻结", "查看异常原因、恢复账号或重置密码"]
                        ]
                    },
                    {
                        "title": "考试记录与成绩档案",
                        "headers": ["学生", "考试情况", "成绩情况", "可执行操作"],
                        "weights": [0.9, 1.22, 1.0, 1.2],
                        "statusIndex": 2,
                        "rows": [
                            ["石晓虹", "已考 8 次 / 缺考 0 次", "平均 86.5", "查看成绩趋势、导出个人成绩"],
                            ["林一", "已考 7 次 / 缺考 1 次", "平均 82.0", "查看缺考记录、发送提醒"],
                            ["周宁", "已考 9 次 / 缺考 0 次", "优秀", "查看考试明细和班级排名"],
                            ["李明", "已考 3 次 / 缺考 2 次", "需补考", "安排补考、查看错题与成绩报告"]
                        ]
                    }
                ],
                "featureSections": [
                    {"title": "注册审核队列", "value": "18 人", "detail": "按学号、姓名、班级、专业核验注册资料，支持通过、退回、冻结。", "points": ["学号唯一校验", "班级与专业匹配", "审核结果写入日志"], "accent": "#f97316"},
                    {"title": "学生资料维护", "value": "42 条", "detail": "维护姓名、学号、专业、班级、手机号、登录账号和账号状态。", "points": ["批量导入学生", "修改班级/专业", "重置密码或恢复账号"], "accent": "#2563eb"},
                    {"title": "考试参与情况", "value": "98.6%", "detail": "查看每个学生已参加、缺考、未提交、补考安排等考试状态。", "points": ["参考次数统计", "缺考学生提醒", "补考安排记录"], "accent": "#16a34a"},
                    {"title": "成绩档案", "value": "3,245 份", "detail": "进入学生个人成绩档案，查看趋势、错题、薄弱知识点和导出记录。", "points": ["个人成绩趋势", "考试报告导出", "异常成绩标记"], "accent": "#7c3aed"}
                ],
                "risk": "冻结账号、重置密码、调整班级等操作会自动写入操作日志。",
                "rows": [
                    ["20260201001", "石晓虹", "软工01", "已通过", "已考 8 / 缺考 0", "86.5", "查看 / 编辑"],
                    ["20260201018", "林一", "软工01", "已通过", "已考 7 / 缺考 1", "82.0", "查看 / 编辑"],
                    ["20260202006", "陈可", "软工02", "待审核", "暂无考试记录", "--", "审核 / 退回"],
                    ["20260301011", "周宁", "计科01", "已通过", "已考 9 / 缺考 0", "91.2", "查看 / 编辑"],
                    ["20260401009", "李明", "大数据01班", "冻结", "已考 3 / 缺考 2", "68.4", "恢复 / 详情"],
                    ["20260203015", "王晨", "软工03", "已通过", "已考 6 / 缺考 0", "88.0", "查看 / 编辑"],
                    ["20260302022", "许诺", "计科02", "待审核", "待参加首次考试", "--", "审核 / 退回"],
                    ["20260402007", "赵雨", "大数据02班", "已通过", "已考 5 / 缺考 1", "79.6", "提醒 / 详情"]
                ],
                "detailTitle": "学生考试与成绩情况",
                "detailHeaders": ["学生", "最近考试", "参考次数", "平均分", "最高分", "成绩状态", "操作"],
                "detailWeights": [0.8, 1.35, 0.86, 0.72, 0.72, 0.9, 1.0],
                "detailStatusIndex": 5,
                "detailRows": [
                    ["石晓虹", "Java期末考试", "8 次", "86.5", "96", "稳定", "成绩报告"],
                    ["林一", "数据结构测试", "7 次", "82.0", "93", "需关注", "成绩报告"],
                    ["周宁", "数据库原理考试", "9 次", "91.2", "98", "优秀", "成绩报告"],
                    ["李明", "C++程序设计考试", "3 次", "68.4", "78", "需补考", "查看记录"],
                    ["王晨", "Java单元测验", "6 次", "88.0", "95", "稳定", "成绩报告"],
                    ["赵雨", "数据库随堂测", "5 次", "79.6", "89", "需关注", "发送提醒"]
                ]
            },
            "教师管理": {
                "title": "教师管理",
                "subtitle": "管理教师账号审核、任课班级、发布考试与批改任务",
                "primary": "新增教师",
                "headers": ["工号", "姓名", "任课科目", "账号审核", "已发布考试", "待批改", "操作"],
                "weights": [1.0, 0.8, 0.9, 0.9, 1.0, 0.78, 1.0],
                "statusIndex": 3,
                "stats": [
                    {"label": "教师总数", "value": "156", "color": "#2563eb"},
                    {"label": "今日新增", "value": "5", "color": "#16a34a"},
                    {"label": "待审核账号", "value": "3", "color": "#f97316"},
                    {"label": "任务完成率", "value": "99.2%", "color": "#7c3aed"}
                ],
                "tags": [
                    {"text": "教师审核", "color": "#2563eb"},
                    {"text": "考试发布", "color": "#16a34a"},
                    {"text": "批改统计", "color": "#f97316"}
                ],
                "actions": [
                    {"title": "新增教师", "detail": "录入工号、姓名、科目、手机号、登录账号和可管理班级。", "accent": "#2563eb"},
                    {"title": "账号审核", "detail": "审核教师注册信息，确认任课科目与班级授权范围。", "accent": "#f97316"},
                    {"title": "发布考试跟踪", "detail": "查看教师已发布、草稿、未开始和进行中的考试安排。", "accent": "#16a34a"},
                    {"title": "批改任务统计", "detail": "统计待批改试卷、已完成批改、平均批改时长和异常任务。", "accent": "#7c3aed"}
                ],
                "focusCards": [
                    {"title": "账号审核", "value": "3 人", "detail": "待确认教师手机号、科目与班级权限", "accent": "#f97316"},
                    {"title": "发布考试", "value": "28 场", "detail": "统计已发布、草稿、进行中考试", "accent": "#2563eb"},
                    {"title": "批改试卷", "value": "44 份", "detail": "追踪待批改试卷与完成率", "accent": "#16a34a"}
                ],
                "workflowPanels": [
                    {
                        "title": "教师账号审核与权限维护",
                        "headers": ["管理事项", "教师", "当前状态", "处理动作"],
                        "weights": [0.95, 1.0, 1.05, 1.28],
                        "statusIndex": 2,
                        "rows": [
                            ["账号审核", "赵老师 / T2024033", "待审核", "确认手机号、任课科目和可管理班级"],
                            ["信息修改", "张老师 / Java", "正常", "调整任课科目、手机号、管理班级"],
                            ["班级授权", "李老师 / 数据结构", "已通过", "维护计科01等班级权限"],
                            ["账号处理", "王老师 / C++", "正常", "重置密码、冻结账号或恢复账号"]
                        ]
                    },
                    {
                        "title": "发布考试与批改任务",
                        "headers": ["教师", "发布考试", "批改情况", "可执行操作"],
                        "weights": [0.85, 1.28, 1.05, 1.18],
                        "statusIndex": 2,
                        "rows": [
                            ["张老师", "Java期末考试 / 12 场", "待批改 18 份", "进入批改任务、查看发布记录"],
                            ["李老师", "数据结构测试 / 9 场", "已完成", "查看历史考试和批改统计"],
                            ["王老师", "C++程序设计考试 / 7 场", "待批改 26 份", "提醒批改、查看异常任务"],
                            ["赵老师", "暂未发布考试", "待分配", "审核账号后分配班级和考试权限"]
                        ]
                    }
                ],
                "featureSections": [
                    {"title": "账号审核", "value": "3 人", "detail": "审核教师注册信息，确认工号、手机号、任课科目和身份真实性。", "points": ["工号唯一校验", "手机号校验", "审核通过/退回"], "accent": "#f97316"},
                    {"title": "班级与科目权限", "value": "156 人", "detail": "配置教师可管理班级、任课科目、题库范围和考试发布权限。", "points": ["分配管理班级", "调整任课科目", "限制数据范围"], "accent": "#2563eb"},
                    {"title": "发布考试情况", "value": "28 场", "detail": "统计教师已发布、草稿、进行中和已结束考试，支持撤回与查看详情。", "points": ["发布记录追踪", "草稿提醒", "撤回发布留痕"], "accent": "#16a34a"},
                    {"title": "批改任务情况", "value": "44 份", "detail": "查看各教师待批改、已完成、超时未批改与批改完成率。", "points": ["待批改提醒", "完成率统计", "异常任务追踪"], "accent": "#7c3aed"}
                ],
                "risk": "调整教师班级权限、冻结账号、撤回考试发布会记录到操作日志。",
                "rows": [
                    ["T2024008", "张老师", "Java", "已通过", "12 场", "18 份", "查看 / 编辑"],
                    ["T2024012", "李老师", "数据结构", "已通过", "9 场", "0 份", "查看 / 编辑"],
                    ["T2024021", "王老师", "C++", "已通过", "7 场", "26 份", "查看 / 编辑"],
                    ["T2024033", "赵老师", "高数", "待审核", "0 场", "--", "审核 / 退回"],
                    ["T2024038", "刘老师", "数据库", "已通过", "6 场", "4 份", "查看 / 编辑"],
                    ["T2024041", "陈老师", "概率论", "待审核", "0 场", "--", "审核 / 退回"],
                    ["T2024046", "孙老师", "计算机网络", "已通过", "5 场", "9 份", "查看 / 编辑"]
                ],
                "detailTitle": "教师发布考试与批改情况",
                "detailHeaders": ["教师", "最近发布考试", "负责班级", "已发布", "待批改", "批改完成率", "操作"],
                "detailWeights": [0.8, 1.35, 1.1, 0.78, 0.78, 0.95, 1.0],
                "detailStatusIndex": 5,
                "detailRows": [
                    ["张老师", "Java期末考试", "软工01 / 软工02", "12 场", "18 份", "94%", "进入任务"],
                    ["李老师", "数据结构测试", "计科01", "9 场", "0 份", "100%", "查看记录"],
                    ["王老师", "C++程序设计考试", "软工03", "7 场", "26 份", "88%", "进入任务"],
                    ["赵老师", "待分配", "大数据01班", "0 场", "--", "待审核", "审核账号"],
                    ["刘老师", "数据库随堂测", "软工02", "6 场", "4 份", "96%", "进入任务"],
                    ["孙老师", "网络阶段测试", "计科02", "5 场", "9 份", "91%", "提醒批改"]
                ]
            },
            "管理员管理": {
                "title": "管理员管理",
                "subtitle": "维护管理端账号和系统级权限",
                "primary": "新增管理员",
                "headers": ["账号", "姓名", "角色", "权限范围", "状态", "最近操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["admin", "超级管理员", "系统管理员", "全部模块", "正常", "15:28 登录系统"],
                    ["audit_admin", "审核管理员", "内容审核", "题目/试卷审核", "正常", "14:52 审核题目"],
                    ["ops_admin", "运维管理员", "系统运维", "日志/备份/设置", "正常", "13:45 数据备份"]
                ]
            },
            "题目管理": {
                "title": "题目管理",
                "subtitle": "集中维护题型、难度、答案解析和知识点",
                "primary": "新增题目",
                "headers": ["题型", "科目", "难度", "知识点", "审核状态", "创建人"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["单选题", "Java", "基础", "JVM", "已通过", "张老师"],
                    ["多选题", "数据结构", "中等", "树与图", "已通过", "李老师"],
                    ["代码题", "C++", "困难", "指针/内存", "待审核", "王老师"],
                    ["填空题", "数据库", "基础", "SQL 查询", "待审核", "赵老师"],
                    ["大题", "高数", "中等", "定积分", "已通过", "高数老师"]
                ]
            },
            "题库管理": {
                "title": "题库管理",
                "subtitle": "按科目维护题库容量、覆盖率和更新状态",
                "primary": "新建题库",
                "headers": ["题库名称", "科目", "题目数", "知识点覆盖", "更新状态", "负责人"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java 基础题库", "Java", "1,286", "92%", "正常", "张老师"],
                    ["数据结构综合题库", "数据结构", "986", "88%", "正常", "李老师"],
                    ["C++ 程序设计题库", "C++", "742", "81%", "需补充", "王老师"],
                    ["数据库原理题库", "数据库", "1,024", "90%", "正常", "赵老师"]
                ]
            },
            "题目审核": {
                "title": "题目审核",
                "subtitle": "查看教师提交的新题目，处理通过或退回",
                "primary": "批量审核",
                "headers": ["题目摘要", "科目", "提交人", "提交时间", "状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java 线程池核心参数", "Java", "张老师", "今天 10:18", "待审核", "查看"],
                    ["B 树插入过程分析", "数据结构", "李老师", "今天 09:46", "待审核", "查看"],
                    ["SQL 聚合函数应用", "数据库", "赵老师", "昨天 17:05", "待审核", "查看"],
                    ["C++ 智能指针选择", "C++", "王老师", "昨天 15:20", "已通过", "详情"]
                ]
            },
            "考试管理": {
                "title": "考试管理",
                "subtitle": "统一查看考试发布、开放、结束和参与情况",
                "primary": "新增考试",
                "headers": ["考试名称", "科目", "班级", "考试时间", "状态", "参考人数"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java期末考试", "Java", "软工01", "07-15 09:00", "进行中", "128/150"],
                    ["数据结构测试", "数据结构", "计科01", "07-16 14:00", "未开始", "0/120"],
                    ["C++程序设计考试", "C++", "软工03", "07-18 10:00", "未开始", "0/100"],
                    ["数据库原理考试", "数据库", "软工02", "07-10 09:00", "已结束", "96/100"]
                ]
            },
            "试卷管理": {
                "title": "试卷管理",
                "subtitle": "管理草稿试卷、正式试卷和组卷结果",
                "primary": "新建试卷",
                "headers": ["试卷名称", "科目", "题量", "总分", "状态", "创建人"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java期末A卷", "Java", "42", "100", "已发布", "张老师"],
                    ["数据结构周测卷", "数据结构", "35", "100", "草稿", "李老师"],
                    ["C++模拟卷一", "C++", "28", "100", "待审核", "王老师"],
                    ["数据库基础卷", "数据库", "30", "100", "已归档", "赵老师"]
                ]
            },
            "考试监控": {
                "title": "考试监控",
                "subtitle": "实时查看在线考试人数、异常提醒和提交进度",
                "primary": "刷新监控",
                "headers": ["考试名称", "在线人数", "异常提醒", "提交率", "状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java期末考试", "568", "2", "76%", "监控中", "进入监控"],
                    ["高数补考", "86", "0", "45%", "监控中", "进入监控"],
                    ["数据库随堂测", "0", "0", "100%", "已结束", "查看报告"]
                ]
            },
            "成绩管理": {
                "title": "成绩管理",
                "subtitle": "汇总考试成绩、发布状态和导出任务",
                "primary": "导出成绩",
                "headers": ["考试名称", "科目", "班级均分", "最高分", "发布状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["Java期末考试", "Java", "84.6", "98", "待发布", "导出"],
                    ["数据结构测试", "数据结构", "79.2", "96", "已发布", "导出"],
                    ["C++程序设计考试", "C++", "81.4", "95", "已发布", "导出"],
                    ["数据库原理考试", "数据库", "86.1", "100", "已发布", "导出"]
                ]
            },
            "角色权限": {
                "title": "角色权限",
                "subtitle": "配置不同角色可访问的菜单和数据范围",
                "primary": "新增角色",
                "headers": ["角色", "成员数", "核心权限", "数据范围", "状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["超级管理员", "1", "全部权限", "全校", "启用", "编辑"],
                    ["题目审核员", "3", "审核题目/试卷", "全部科目", "启用", "编辑"],
                    ["教务管理员", "5", "考试/成绩管理", "所在院系", "启用", "编辑"],
                    ["运维管理员", "3", "日志/备份/设置", "系统", "启用", "编辑"]
                ]
            },
            "操作日志": {
                "title": "操作日志",
                "subtitle": "记录管理员在管理端进行的登录、审核、修改、发布和导出操作",
                "primary": "导出日志",
                "headers": ["操作人", "模块", "操作内容", "IP地址", "时间", "结果"],
                "weights": [0.78, 0.9, 2.35, 1.0, 0.98, 0.72],
                "statusIndex": 5,
                "stats": [
                    {"label": "日志总数", "value": "18,902", "color": "#2563eb"},
                    {"label": "今日操作", "value": "415", "color": "#16a34a"},
                    {"label": "失败操作", "value": "0", "color": "#f97316"},
                    {"label": "记录完整率", "value": "100%", "color": "#7c3aed"}
                ],
                "tags": [
                    {"text": "操作留痕", "color": "#2563eb"},
                    {"text": "审计追踪", "color": "#16a34a"},
                    {"text": "安全可查", "color": "#f97316"}
                ],
                "actions": [
                    {"title": "筛选日志", "detail": "按管理员、模块、时间、结果快速定位具体操作记录。", "accent": "#2563eb"},
                    {"title": "导出日志", "detail": "导出当前筛选范围内的操作日志用于审计归档。", "accent": "#16a34a"},
                    {"title": "异常追踪", "detail": "失败、冻结、撤回、重置等敏感操作会重点标记。", "accent": "#f97316"}
                ],
                "featureSections": [
                    {"title": "今日审计", "value": "415 条", "detail": "覆盖学生管理、教师管理、考试管理、系统设置等后台操作。", "points": ["按模块筛选", "按管理员筛选", "按时间范围导出"], "accent": "#2563eb"},
                    {"title": "敏感操作", "value": "26 条", "detail": "冻结账号、重置密码、撤回考试、修改权限会被重点标记。", "points": ["二次确认", "高亮风险", "可追溯到操作人"], "accent": "#f97316"},
                    {"title": "导出归档", "value": "8 次", "detail": "支持导出当前筛选范围内的日志，用于审计归档和问题追责。", "points": ["Excel 导出", "审计编号", "归档时间记录"], "accent": "#16a34a"},
                    {"title": "安全结果", "value": "100%", "detail": "记录成功、失败、处理中等结果，失败操作可进入异常追踪。", "points": ["失败操作追踪", "IP 地址记录", "结果状态留存"], "accent": "#7c3aed"}
                ],
                "workflowPanels": [
                    {
                        "title": "敏感操作追踪",
                        "headers": ["操作类型", "操作对象", "风险等级", "处理状态"],
                        "weights": [0.95, 1.45, 0.86, 1.0],
                        "statusIndex": 3,
                        "rows": [
                            ["重置密码", "学生 李明 / 20260401009", "中风险", "成功"],
                            ["冻结账号", "学生 李明 / 大数据01班", "高风险", "成功"],
                            ["修改权限", "张老师 / 软工01、软工02", "中风险", "成功"],
                            ["撤回考试", "Java期末考试 草稿", "高风险", "成功"]
                        ]
                    },
                    {
                        "title": "模块操作分布",
                        "headers": ["模块", "今日操作", "主要动作", "异常记录"],
                        "weights": [0.95, 0.82, 1.4, 0.86],
                        "statusIndex": 3,
                        "rows": [
                            ["学生管理", "128 条", "审核、编辑、重置密码", "0 条"],
                            ["教师管理", "76 条", "审核、授权、查看任务", "0 条"],
                            ["考试管理", "92 条", "发布、撤回、导出", "0 条"],
                            ["系统设置", "18 条", "安全策略调整", "0 条"]
                        ]
                    }
                ],
                "risk": "日志只记录管理端操作，不展示学生或教师端的普通浏览行为。",
                "rows": [
                    ["admin", "学生管理", "通过学生陈可的注册审核", "127.0.0.1", "15:36:08", "成功"],
                    ["admin", "教师管理", "修改张老师可管理班级为软工01 / 软工02", "127.0.0.1", "15:21:44", "成功"],
                    ["admin", "考试管理", "撤回《Java期末考试》草稿并重新发布", "127.0.0.1", "14:58:12", "成功"],
                    ["audit_admin", "题目审核", "通过《Java 线程池核心参数》", "127.0.0.1", "14:52:16", "成功"],
                    ["admin", "成绩管理", "导出软工01班 Java期末成绩", "127.0.0.1", "14:30:22", "成功"],
                    ["ops_admin", "系统设置", "开启敏感操作二次确认", "127.0.0.1", "13:45:10", "成功"],
                    ["admin", "学生管理", "重置学生李明的登录密码", "127.0.0.1", "13:18:41", "成功"],
                    ["admin", "教师管理", "冻结教师赵老师待审核账号", "127.0.0.1", "12:52:33", "成功"],
                    ["audit_admin", "题目审核", "退回《B树插入过程分析》并填写原因", "127.0.0.1", "12:21:05", "成功"],
                    ["ops_admin", "系统设置", "调整登录失败锁定阈值为 5 次", "127.0.0.1", "11:46:20", "成功"],
                    ["admin", "学生管理", "将学生赵雨转入大数据02班", "127.0.0.1", "11:18:09", "成功"],
                    ["admin", "教师管理", "新增刘老师数据库任课权限", "127.0.0.1", "10:42:55", "成功"],
                    ["audit_admin", "教师管理", "退回陈老师注册申请并填写原因", "127.0.0.1", "10:08:31", "成功"],
                    ["ops_admin", "系统设置", "导出今日操作日志归档", "127.0.0.1", "09:36:12", "成功"]
                ],
                "detailTitle": "日志审计归档",
                "detailHeaders": ["归档批次", "时间范围", "日志数量", "导出人", "校验状态", "操作"],
                "detailWeights": [1.15, 1.45, 0.82, 0.82, 0.9, 0.78],
                "detailStatusIndex": 4,
                "detailRows": [
                    ["LOG-20260713-01", "今日 00:00-16:00", "415 条", "admin", "完整", "下载"],
                    ["LOG-20260712-01", "昨日全天", "1,268 条", "ops_admin", "完整", "下载"],
                    ["LOG-20260711-01", "07-11 全天", "1,102 条", "ops_admin", "完整", "下载"]
                ]
            },
            "系统设置": {
                "title": "系统设置",
                "subtitle": "维护考试安全策略、通知策略和系统参数",
                "primary": "保存设置",
                "headers": ["设置项", "当前值", "推荐值", "影响范围", "状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["考试切屏检测", "开启", "开启", "所有考试", "启用", "配置"],
                    ["自动保存间隔", "30 秒", "30 秒", "考试作答", "启用", "配置"],
                    ["登录失败锁定", "5 次", "5 次", "全部用户", "启用", "配置"],
                    ["成绩发布通知", "开启", "开启", "学生端", "启用", "配置"]
                ]
            },
            "数据备份": {
                "title": "数据备份",
                "subtitle": "查看数据库备份、恢复点和自动备份策略",
                "primary": "立即备份",
                "headers": ["备份名称", "备份类型", "大小", "完成时间", "状态", "操作"],
                "statusIndex": 4,
                "stats": commonStats,
                "rows": [
                    ["backup_20260713_0200", "自动备份", "1.8GB", "今天 02:00", "成功", "下载"],
                    ["backup_20260712_0200", "自动备份", "1.7GB", "昨天 02:00", "成功", "下载"],
                    ["manual_20260711_1530", "手动备份", "1.7GB", "07-11 15:30", "成功", "下载"],
                    ["backup_20260710_0200", "自动备份", "1.6GB", "07-10 02:00", "成功", "下载"]
                ]
            }
        }
        if (page === "学生管理") {
            map["学生管理"] = applyManagementData(map["学生管理"], studentManagementData)
        }
        if (page === "教师管理") {
            map["教师管理"] = applyManagementData(map["教师管理"], teacherManagementData)
        }
        return map[page] || map["考试管理"]
    }
    property var menuGroups: [
        {"title": "", "items": [
            {"text": "系统概览", "icon": "home"}
        ]},
        {"title": "人员管理", "items": [
            {"text": "学生管理", "icon": "student"},
            {"text": "教师管理", "icon": "teacher"}
        ]},
        {"title": "系统管理", "items": [
            {"text": "操作日志", "icon": "logs"},
            {"text": "系统设置", "icon": "settings"}
        ]}
    ]
    property var statCards: [
        {"title": "学生总数", "value": "3,245", "delta": "23", "icon": "users", "from": "#64a8ff", "to": "#245df0"},
        {"title": "教师总数", "value": "156", "delta": "5", "icon": "teacher", "from": "#35d48a", "to": "#09aa57"},
        {"title": "考试总数", "value": "128", "delta": "8", "icon": "exam", "from": "#8b7cff", "to": "#4f46e5"},
        {"title": "试卷总数", "value": "256", "delta": "12", "icon": "paper", "from": "#ff9a37", "to": "#f36b16"},
        {"title": "今日参考人数", "value": "568", "delta": "45", "icon": "today", "from": "#62a8ff", "to": "#2364e8"}
    ]
    property var lineLabels: ["05-14", "05-15", "05-16", "05-17", "05-18", "05-19", "05-20"]
    property var peopleLine: [580, 635, 720, 728, 676, 762, 802]
    property var examLine: [196, 245, 255, 288, 232, 276, 242]
    property var recentExams: [
        {"name": "Java期末考试", "subject": "Java程序设计", "owner": "张老师", "time": "2024-05-20 09:00", "status": "进行中", "count": "128/150"},
        {"name": "数据结构测试", "subject": "数据结构", "owner": "李老师", "time": "2024-05-19 14:00", "status": "已结束", "count": "96/120"},
        {"name": "C++程序设计考试", "subject": "C++", "owner": "王老师", "time": "2024-05-18 10:00", "status": "已结束", "count": "88/100"},
        {"name": "计算机网络测试", "subject": "计算机网络", "owner": "赵老师", "time": "2024-05-17 16:00", "status": "已结束", "count": "76/80"},
        {"name": "数据库原理考试", "subject": "数据库原理", "owner": "张老师", "time": "2024-05-16 09:00", "status": "已结束", "count": "64/70"}
    ]
    property var alerts: [
        {"type": "高并发预警", "content": "当前参考人数较多，请注意系统负载", "time": "2024-05-20 09:30:15", "status": "未处理", "action": "查看详情"},
        {"type": "存储空间预警", "content": "存储空间使用率已达 85%", "time": "2024-05-20 08:15:22", "status": "处理中", "action": "立即处理"},
        {"type": "题目审核预警", "content": "有 12 道新题目待审核", "time": "2024-05-20 07:45:18", "status": "未处理", "action": "立即处理"}
    ]
    property var logs: [
        {"text": "admin 通过学生陈可的注册审核", "time": "15:36:08"},
        {"text": "admin 修改张老师可管理班级", "time": "15:21:44"},
        {"text": "admin 重新发布《Java期末考试》", "time": "14:58:12"},
        {"text": "audit_admin 通过《Java 线程池核心参数》", "time": "14:52:16"},
        {"text": "admin 导出软工01班 Java期末成绩", "time": "14:30:22"},
        {"text": "ops_admin 开启敏感操作二次确认", "time": "13:45:10"}
    ]

    Component.onCompleted: refreshAdminData()

    Rectangle {
        id: sidebar
        width: root.sidebarWidth
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#132238"

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#172942" }
                GradientStop { position: 1.0; color: "#0d1b2d" }
            }
        }

        Column {
            anchors.fill: parent
            anchors.margins: root.compactShell ? 12 : Math.round(18 * root.contentScale)
            spacing: root.compactShell ? 12 : root.gap

            RowLayout {
                width: parent.width
                height: root.compactShell ? 58 : Math.round(72 * root.contentScale)
                spacing: root.compactShell ? 0 : Math.round(14 * root.contentScale)
                SidebarLogo {
                    Layout.preferredWidth: root.compactShell ? 54 : Math.round(62 * root.contentScale)
                    Layout.preferredHeight: root.compactShell ? 42 : Math.round(50 * root.contentScale)
                    Layout.alignment: root.compactShell ? Qt.AlignHCenter : Qt.AlignVCenter
                }
                Text { visible: !root.compactShell; Layout.fillWidth: true; text: "在线考试平台"; color: "#ffffff"; font.pixelSize: Math.round(31 * root.contentScale); font.bold: true; elide: Text.ElideRight }
                Rectangle {
                    visible: !root.compactShell
                    Layout.preferredWidth: Math.round(72 * root.contentScale)
                    Layout.preferredHeight: Math.round(34 * root.contentScale)
                    radius: root.cardRadius
                    color: "#3c68f3"
                    Text { anchors.centerIn: parent; text: "管理端"; color: "#ffffff"; font.pixelSize: root.bodyFont; font.bold: true }
                }
            }

            Repeater {
                model: root.menuGroups
                delegate: Column {
                    width: parent.width
                    spacing: Math.round(9 * root.contentScale)
                    Text {
                        visible: !root.compactShell && modelData.title.length > 0
                        text: modelData.title
                        color: "#8da1bb"
                        font.pixelSize: root.bodyFont
                        font.bold: true
                        leftPadding: Math.round(24 * root.contentScale)
                        height: visible ? Math.round(32 * root.contentScale) : 0
                        verticalAlignment: Text.AlignVCenter
                    }
                    Repeater {
                        model: modelData.items
                        delegate: SidebarItem {
                            width: parent.width
                            text: modelData.text
                            icon: modelData.icon
                            compact: root.compactShell
                            selected: text === root.currentMenu
                            onClicked: root.switchMenu(text)
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: topbar
        z: 20
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.top: parent.top
        height: root.topbarHeight
        color: "#ffffff"
        border.color: "#edf2f8"

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1
            color: "#e8eef7"
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed: adminApi.startWindowMove()
        }

        RowLayout {
            id: breadcrumbRow
            anchors.left: parent.left
            anchors.leftMargin: root.width < 760 ? 10 : (root.compactShell ? 18 : Math.round(34 * root.contentScale))
            anchors.right: userActions.left
            anchors.rightMargin: root.width < 760 ? 6 : (root.compactShell ? 14 : Math.round(24 * root.contentScale))
            anchors.verticalCenter: parent.verticalCenter
            spacing: root.width < 760 ? 6 : (root.compactShell ? 12 : Math.round(28 * root.contentScale))
            Text { text: "☰"; color: "#26354a"; font.pixelSize: root.width < 760 ? 24 : (root.compactShell ? 30 : Math.round(38 * root.contentScale)); font.bold: true }
            Text {
                Layout.fillWidth: true
                text: root.compactShell ? root.currentMenu : "首页 / " + root.currentMenu
                color: "#273449"
                font.pixelSize: root.compactShell ? 24 : root.navFont
                font.bold: true
                elide: Text.ElideRight
            }
        }

        RowLayout {
            id: userActions
            anchors.right: parent.right
            anchors.rightMargin: root.width < 760 ? 8 : (root.compactShell ? 14 : Math.round(28 * root.contentScale))
            anchors.verticalCenter: parent.verticalCenter
            spacing: root.width < 760 ? 6 : (root.compactShell ? 12 : Math.round(22 * root.contentScale))
            AdminNoticeButton { Layout.preferredWidth: root.width < 760 ? 42 : (root.narrowShell ? 52 : Math.round(62 * root.contentScale)); Layout.preferredHeight: root.width < 760 ? 42 : (root.narrowShell ? 52 : Math.round(62 * root.contentScale)) }
            FullscreenIcon { visible: !root.compactShell; Layout.preferredWidth: Math.round(34 * root.contentScale); Layout.preferredHeight: Math.round(34 * root.contentScale) }
            AdminUserMenu { Layout.preferredWidth: root.width < 760 ? 46 : (root.compactShell ? 64 : Math.round(238 * root.contentScale)); Layout.preferredHeight: root.width < 760 ? 44 : (root.compactShell ? 56 : Math.round(72 * root.contentScale)) }
            WindowControls {
                Layout.preferredWidth: root.width < 760 ? 112 : (root.narrowShell ? 128 : Math.round(158 * root.contentScale))
                Layout.minimumWidth: root.width < 760 ? 112 : (root.narrowShell ? 128 : Math.round(158 * root.contentScale))
                Layout.preferredHeight: root.width < 760 ? 38 : Math.round(50 * root.contentScale)
            }
        }
    }

    Flickable {
        id: contentScroll
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        contentWidth: width
        contentHeight: Math.max(height, root.shellMargin + pageLoader.height + root.shellMargin)
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        interactive: !root.innerScrollActive
        ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }

        Loader {
            id: pageLoader
            property Item loadedPage: item
            x: root.shellMargin
            y: root.shellMargin
            width: contentScroll.width - root.shellMargin * 2
            height: loadedPage ? loadedPage.height : 0
            sourceComponent: root.currentMenu === "系统概览" ? overviewPageComponent
                             : root.currentMenu === "系统设置" ? settingsPageComponent
                             : root.currentMenu === "个人中心" ? profilePageComponent
                             : managementPageComponent
            onLoaded: {
                if (loadedPage) {
                    loadedPage.width = width
                }
            }
            onWidthChanged: {
                if (loadedPage) {
                    loadedPage.width = width
                }
            }
        }
    }

    Component {
        id: overviewPageComponent
        SystemOverviewPage {
            width: pageLoader.width
        }
    }

    Component {
        id: settingsPageComponent
        SystemSettingsPage {
            width: pageLoader.width
        }
    }

    Component {
        id: profilePageComponent
        AdminProfilePage {
            width: pageLoader.width
        }
    }

    Component {
        id: managementPageComponent
        AdminManagementPage {
            width: pageLoader.width
            page: root.currentMenu
        }
    }

    component SystemOverviewPage: Item {
        id: overview
        height: overviewColumn.implicitHeight

        ColumnLayout {
            id: overviewColumn
            width: parent.width
            spacing: root.gap

            GridLayout {
                Layout.fillWidth: true
                columns: parent.width > 1180 ? 5 : (parent.width > 760 ? 3 : (parent.width > 520 ? 2 : 1))
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap
                Repeater {
                    model: root.statCards
                    delegate: StatCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.compactShell ? 104 : Math.round(122 * root.contentScale)
                        title: modelData.title
                        value: modelData.value
                        delta: modelData.delta
                        icon: modelData.icon
                        fromColor: modelData.from
                        toColor: modelData.to
                    }
                }
            }

            GridLayout {
                id: overviewGrid
                Layout.fillWidth: true
                columns: width > 1180 ? 3 : (width > 760 ? 2 : 1)
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: overviewGrid.columns > 2 ? 2 : overviewGrid.columns
                    Layout.preferredHeight: root.narrowShell ? 292 : Math.round(340 * root.contentScale)
                    title: "考试参与情况（近7天）"
                    LineChart {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: Math.round(56 * root.contentScale)
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: Math.round(18 * root.contentScale)
                        people: root.peopleLine
                        exams: root.examLine
                        labels: root.lineLabels
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: overviewGrid.columns > 2 ? 1 : overviewGrid.columns
                    Layout.preferredHeight: root.narrowShell ? 292 : Math.round(340 * root.contentScale)
                    title: "试卷难度分布"
                    DonutChart { anchors.fill: parent; anchors.topMargin: Math.round(56 * root.contentScale); anchors.bottomMargin: Math.round(20 * root.contentScale) }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: overviewGrid.columns > 2 ? 2 : overviewGrid.columns
                    Layout.preferredHeight: root.narrowShell ? 310 : Math.round(360 * root.contentScale)
                    title: "最近考试（5个）"
                    OverviewMoreLink { anchors.top: parent.top; anchors.right: parent.right; anchors.topMargin: Math.round(23 * root.contentScale); anchors.rightMargin: Math.round(22 * root.contentScale) }
                    RecentExamTable { anchors.fill: parent; anchors.topMargin: Math.round(64 * root.contentScale); anchors.margins: Math.round(16 * root.contentScale) }
                }
            }
        }
    }

    component OverviewMoreLink: Text {
        text: "更多 ›"
        color: "#2563eb"
        font.pixelSize: root.bodyFont
        font.bold: true
    }

    component SystemSettingsPage: Item {
        id: settingsPage
        property var settingsData: root.pageData("系统设置")
        height: settingsColumn.implicitHeight

        ColumnLayout {
            id: settingsColumn
            width: parent.width
            spacing: root.gap

            Rectangle {
                id: settingsHero
                property bool narrow: width < 760
                Layout.fillWidth: true
                Layout.preferredHeight: narrow ? Math.round(206 * root.contentScale) : Math.round(164 * root.contentScale)
                radius: root.cardRadius
                color: "#ffffff"
                border.color: "#dbeafe"
                Rectangle { anchors.fill: parent; anchors.topMargin: Math.round(5 * root.contentScale); radius: root.cardRadius; color: "#0f172a"; opacity: 0.04; z: -1 }
                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: Math.round(8 * root.contentScale)
                    radius: Math.round(4 * root.contentScale)
                    color: "#2563eb"
                }
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: settingsHero.narrow ? Math.round(20 * root.contentScale) : Math.round(28 * root.contentScale)
                    spacing: Math.round(20 * root.contentScale)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: Math.round(8 * root.contentScale)
                        Text {
                            Layout.fillWidth: true
                            text: "系统信息"
                            color: "#0f172a"
                            font.pixelSize: root.narrowShell ? root.pageTitleFont : root.pageTitleFont
                            font.bold: true
                            elide: Text.ElideRight
                        }
                        Text {
                            Layout.fillWidth: true
                            text: "集中查看服务器状态、资源占用和系统参数，主页不再堆放系统信息卡片。"
                            color: "#64748b"
                            font.pixelSize: root.bodyFont
                            wrapMode: Text.WordWrap
                            maximumLineCount: settingsHero.narrow ? 2 : 1
                        }
                        Flow {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            spacing: Math.round(8 * root.contentScale)
                            AdminTag { text: "系统设置"; colorValue: "#2563eb" }
                            AdminTag { text: "运行正常"; colorValue: "#16a34a" }
                            AdminTag { text: "资源监测"; colorValue: "#f97316" }
                        }
                    }
                    AdminPrimaryButton {
                        visible: !settingsHero.narrow
                        Layout.preferredWidth: Math.round(136 * root.contentScale)
                        Layout.preferredHeight: Math.round(50 * root.contentScale)
                        text: "保存设置"
                    }
                }
            }

            GridLayout {
                id: settingsGrid
                Layout.fillWidth: true
                columns: width > 1060 ? 2 : 1
                columnSpacing: root.compactShell ? 10 : 14
                rowSpacing: root.compactShell ? 10 : 14

                Panel {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.narrowShell ? Math.round(360 * root.contentScale) : Math.round(410 * root.contentScale)
                    title: "系统信息"
                    SystemInfoPanel {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(68 * root.contentScale)
                        anchors.leftMargin: Math.round(24 * root.contentScale)
                        anchors.rightMargin: Math.round(24 * root.contentScale)
                        anchors.bottomMargin: Math.round(24 * root.contentScale)
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.narrowShell ? Math.round(360 * root.contentScale) : Math.round(410 * root.contentScale)
                    title: "运行状态"
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(68 * root.contentScale)
                        anchors.leftMargin: Math.round(24 * root.contentScale)
                        anchors.rightMargin: Math.round(24 * root.contentScale)
                        anchors.bottomMargin: Math.round(24 * root.contentScale)
                        spacing: Math.round(16 * root.contentScale)
                        InfoRow { label: "数据库状态:"; value: "连接正常 / 读写稳定" }
                        InfoRow { label: "服务状态:"; value: "考试服务、题库服务、通知服务运行中" }
                        InfoRow { label: "备份策略:"; value: "每日 02:00 自动备份" }
                        UsageRow { label: "接口负载:"; value: "328 req/min"; percent: 44; colorValue: "#2563eb" }
                        UsageRow { label: "缓存命中:"; value: "92%"; percent: 92; colorValue: "#16a34a" }
                        Item { Layout.fillHeight: true }
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: settingsGrid.columns
                    Layout.preferredHeight: root.narrowShell ? Math.round(430 * root.contentScale) : Math.round(500 * root.contentScale)
                    title: "系统参数"
                    ManagementTable {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(68 * root.contentScale)
                        anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                        anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                        anchors.bottomMargin: Math.round(22 * root.contentScale)
                        headers: settingsPage.settingsData.headers
                        rows: settingsPage.settingsData.rows
                        statusIndex: settingsPage.settingsData.statusIndex
                    }
                }
            }
        }
    }

    component AdminProfilePage: Item {
        id: profilePage
        height: profileColumn.implicitHeight

        ColumnLayout {
            id: profileColumn
            width: parent.width
            spacing: root.gap

            Rectangle {
                id: profileHero
                property bool narrow: width < 760
                Layout.fillWidth: true
                Layout.preferredHeight: narrow ? Math.round(244 * root.contentScale) : Math.round(176 * root.contentScale)
                radius: root.cardRadius
                color: "#ffffff"
                border.color: "#dbeafe"
                Rectangle { anchors.fill: parent; anchors.topMargin: Math.round(5 * root.contentScale); radius: root.cardRadius; color: "#0f172a"; opacity: 0.04; z: -1 }
                GridLayout {
                    anchors.fill: parent
                    anchors.margins: profileHero.narrow ? Math.round(20 * root.contentScale) : Math.round(28 * root.contentScale)
                    columns: profileHero.narrow ? 2 : 4
                    columnSpacing: Math.round(22 * root.contentScale)
                    rowSpacing: Math.round(14 * root.contentScale)
                    AdminGhostButton {
                        Layout.preferredWidth: Math.round(108 * root.contentScale)
                        Layout.preferredHeight: Math.round(50 * root.contentScale)
                        Layout.alignment: Qt.AlignVCenter
                        text: "返回"
                        onClicked: root.switchMenu("系统概览")
                    }
                    AdminAvatar {
                        Layout.preferredWidth: profileHero.narrow ? Math.round(72 * root.contentScale) : Math.round(88 * root.contentScale)
                        Layout.preferredHeight: profileHero.narrow ? Math.round(72 * root.contentScale) : Math.round(88 * root.contentScale)
                        Layout.alignment: Qt.AlignVCenter
                    }
                    ColumnLayout {
                        Layout.columnSpan: profileHero.narrow ? 2 : 1
                        Layout.fillWidth: true
                        spacing: Math.round(7 * root.contentScale)
                        Text { Layout.fillWidth: true; text: adminApi.adminName(); color: "#0f172a"; font.pixelSize: root.narrowShell ? root.pageTitleFont : root.pageTitleFont; font.bold: true; elide: Text.ElideRight }
                        Text { Layout.fillWidth: true; text: "超级管理员 · 系统权限"; color: "#64748b"; font.pixelSize: root.bodyFont; elide: Text.ElideRight }
                        Text { Layout.fillWidth: true; text: "管理个人信息、密码与系统偏好，退出登录会返回登录页面。"; color: "#64748b"; font.pixelSize: root.smallFont; wrapMode: Text.WordWrap; maximumLineCount: 2 }
                    }
                    AdminPrimaryButton {
                        Layout.columnSpan: profileHero.narrow ? 2 : 1
                        Layout.preferredWidth: profileHero.narrow ? Math.round(132 * root.contentScale) : Math.round(146 * root.contentScale)
                        Layout.preferredHeight: Math.round(50 * root.contentScale)
                        Layout.alignment: profileHero.narrow ? Qt.AlignLeft : Qt.AlignVCenter
                        text: "退出登录"
                        onClicked: adminApi.logout()
                    }
                }
            }

            GridLayout {
                id: profileGrid
                Layout.fillWidth: true
                columns: width > 1080 ? 5 : 1
                columnSpacing: root.compactShell ? 10 : 14
                rowSpacing: root.compactShell ? 10 : 14

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: profileGrid.columns > 1 ? 2 : 1
                    Layout.preferredHeight: root.narrowShell ? Math.round(420 * root.contentScale) : Math.round(500 * root.contentScale)
                    title: "个人中心"
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(70 * root.contentScale)
                        anchors.leftMargin: Math.round(22 * root.contentScale)
                        anchors.rightMargin: Math.round(22 * root.contentScale)
                        anchors.bottomMargin: Math.round(22 * root.contentScale)
                        spacing: Math.round(12 * root.contentScale)
                        Repeater {
                            model: [
                                {"title": "修改个人信息", "sub": "姓名、账号和联系方式", "page": 0, "tone": "#2563eb"},
                                {"title": "修改密码", "sub": "更新管理端登录密码", "page": 1, "tone": "#7c3aed"},
                                {"title": "系统设置", "sub": "通知、登录安全和资源策略", "page": 2, "tone": "#16a34a"},
                                {"title": "退出登录", "sub": "返回登录页面", "page": 3, "tone": "#ef4444"}
                            ]
                            delegate: Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: Math.round(84 * root.contentScale)
                                radius: root.cardRadius
                                color: root.profileSubPage === modelData.page ? "#eff6ff" : "#ffffff"
                                border.color: root.profileSubPage === modelData.page ? "#bfdbfe" : "#e5edf6"
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: Math.round(14 * root.contentScale)
                                    spacing: Math.round(14 * root.contentScale)
                                    Rectangle { Layout.preferredWidth: Math.round(8 * root.contentScale); Layout.preferredHeight: Math.round(48 * root.contentScale); radius: Math.round(4 * root.contentScale); color: modelData.tone }
                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        spacing: Math.round(4 * root.contentScale)
                                        Text { Layout.fillWidth: true; text: modelData.title; color: modelData.page === 3 ? "#ef4444" : "#111827"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                                        Text { Layout.fillWidth: true; text: modelData.sub; color: "#64748b"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
                                    }
                                    Text { text: "›"; color: "#94a3b8"; font.pixelSize: root.navFont; font.bold: true }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        if (modelData.page === 3) {
                                            adminApi.logout()
                                        } else {
                                            root.profileSubPage = modelData.page
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: profileGrid.columns > 1 ? 3 : 1
                    Layout.preferredHeight: root.narrowShell ? Math.round(470 * root.contentScale) : Math.round(500 * root.contentScale)
                    title: root.profileSubPage === 1 ? "修改密码" : (root.profileSubPage === 2 ? "系统设置" : "修改个人信息")
                    Loader {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(70 * root.contentScale)
                        anchors.leftMargin: Math.round(26 * root.contentScale)
                        anchors.rightMargin: Math.round(26 * root.contentScale)
                        anchors.bottomMargin: Math.round(26 * root.contentScale)
                        sourceComponent: root.profileSubPage === 1 ? passwordFormComponent
                                         : (root.profileSubPage === 2 ? settingsFormComponent : infoFormComponent)
                    }

                    Component {
                        id: infoFormComponent
                        ColumnLayout {
                            spacing: Math.round(16 * root.contentScale)
                            GridLayout {
                                Layout.fillWidth: true
                                columns: root.narrowShell ? 1 : 2
                                columnSpacing: Math.round(18 * root.contentScale)
                                rowSpacing: Math.round(14 * root.contentScale)
                                AdminFormField { label: "管理员姓名"; value: adminApi.adminName() }
                                AdminFormField { label: "登录账号"; value: "admin" }
                                AdminFormField { label: "角色权限"; value: "超级管理员" }
                                AdminFormField { label: "联系邮箱"; value: "admin@zhikaoxing.local" }
                            }
                            Item { Layout.fillHeight: true }
                            RowLayout {
                                Layout.fillWidth: true
                                Item { Layout.fillWidth: true }
                                AdminPrimaryButton { Layout.preferredWidth: Math.round(136 * root.contentScale); Layout.preferredHeight: Math.round(50 * root.contentScale); text: "保存资料" }
                            }
                        }
                    }

                    Component {
                        id: passwordFormComponent
                        ColumnLayout {
                            spacing: Math.round(16 * root.contentScale)
                            AdminFormField { label: "当前密码"; value: ""; password: true }
                            AdminFormField { label: "新密码"; value: ""; password: true }
                            AdminFormField { label: "确认新密码"; value: ""; password: true }
                            Text { Layout.fillWidth: true; text: "建议使用 8 位以上密码，并包含数字、字母和符号。"; color: "#64748b"; font.pixelSize: root.smallFont; wrapMode: Text.WordWrap }
                            Item { Layout.fillHeight: true }
                            RowLayout {
                                Layout.fillWidth: true
                                Item { Layout.fillWidth: true }
                                AdminPrimaryButton { Layout.preferredWidth: Math.round(136 * root.contentScale); Layout.preferredHeight: Math.round(50 * root.contentScale); text: "修改密码" }
                            }
                        }
                    }

                    Component {
                        id: settingsFormComponent
                        ColumnLayout {
                            spacing: Math.round(16 * root.contentScale)
                            AdminSettingRow { title: "系统警告通知"; hint: "将高并发、存储空间等警告推送到消息栏"; checked: true }
                            AdminSettingRow { title: "敏感操作确认"; hint: "删除、冻结、重置密码等操作需要二次确认"; checked: true }
                            AdminSettingRow { title: "自动记录日志"; hint: "所有管理端关键操作写入操作日志"; checked: true }
                            Item { Layout.fillHeight: true }
                            RowLayout {
                                Layout.fillWidth: true
                                Item { Layout.fillWidth: true }
                                AdminGhostButton { Layout.preferredWidth: Math.round(136 * root.contentScale); Layout.preferredHeight: Math.round(50 * root.contentScale); text: "进入设置"; onClicked: root.switchMenu("系统设置") }
                                AdminPrimaryButton { Layout.preferredWidth: Math.round(136 * root.contentScale); Layout.preferredHeight: Math.round(50 * root.contentScale); text: "保存设置" }
                            }
                        }
                    }
                }
            }
        }
    }

    component AdminFormField: ColumnLayout {
        id: formField
        property string label: ""
        property string value: ""
        property bool password: false
        Layout.fillWidth: true
        spacing: Math.round(7 * root.contentScale)
        Text {
            Layout.fillWidth: true
            text: formField.label
            color: "#475569"
            font.pixelSize: root.smallFont
            font.bold: true
            elide: Text.ElideRight
        }
        TextField {
            Layout.fillWidth: true
            Layout.preferredHeight: Math.round(54 * root.contentScale)
            text: formField.value
            echoMode: formField.password ? TextInput.Password : TextInput.Normal
            color: "#111827"
            font.pixelSize: root.bodyFont
            leftPadding: Math.round(14 * root.contentScale)
            rightPadding: Math.round(14 * root.contentScale)
            background: Rectangle {
                radius: root.cardRadius
                color: "#f8fafc"
                border.color: parent.activeFocus ? "#93c5fd" : "#e5edf6"
            }
        }
    }

    component AdminSettingRow: Rectangle {
        id: settingRow
        property string title: ""
        property string hint: ""
        property bool checked: false
        Layout.fillWidth: true
        Layout.preferredHeight: Math.round(84 * root.contentScale)
        radius: root.cardRadius
        color: "#f8fafc"
        border.color: "#e5edf6"
        RowLayout {
            anchors.fill: parent
            anchors.margins: Math.round(16 * root.contentScale)
            spacing: Math.round(14 * root.contentScale)
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(5 * root.contentScale)
                Text { Layout.fillWidth: true; text: settingRow.title; color: "#111827"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: settingRow.hint; color: "#64748b"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
            }
            Switch {
                checked: settingRow.checked
            }
        }
    }

    component FocusedAdminManagementPage: Item {
        id: focusedPage
        property string page: ""
        property var pageInfo: root.pageData(page)
        property bool isLogPage: page === "操作日志"
        property bool narrowContent: width < 1120
        property int fallbackHeight: root.narrowShell ? Math.round(2380 * root.contentScale)
                                                      : Math.round((isLogPage ? 1780 : 1840) * root.contentScale)
        height: Math.max(focusedColumn.implicitHeight, fallbackHeight)

        function filteredRows() {
            var rows = pageInfo.rows || []
            var text = root.keyword.trim().toLowerCase()
            if (text.length === 0) {
                return rows
            }
            var result = []
            for (var i = 0; i < rows.length; ++i) {
                if (String(rows[i].join(" ")).toLowerCase().indexOf(text) >= 0) {
                    result.push(rows[i])
                }
            }
            return result
        }

        ColumnLayout {
            id: focusedColumn
            anchors.fill: parent
            spacing: root.gap

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: root.narrowShell ? Math.round(196 * root.contentScale) : Math.round(156 * root.contentScale)
                radius: root.cardRadius
                color: "#ffffff"
                border.color: "#dbeafe"
                clip: true

                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: Math.round(8 * root.contentScale)
                    color: focusedPage.isLogPage ? "#7c3aed" : (focusedPage.page === "学生管理" ? "#2563eb" : "#16a34a")
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: root.narrowShell ? 22 : Math.round(30 * root.contentScale)
                    anchors.rightMargin: root.narrowShell ? 18 : Math.round(28 * root.contentScale)
                    anchors.topMargin: Math.round(20 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                    spacing: Math.round(18 * root.contentScale)

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: Math.round(8 * root.contentScale)
                        Text {
                            Layout.fillWidth: true
                            text: focusedPage.pageInfo.title
                            color: "#0f172a"
                            font.pixelSize: root.pageTitleFont
                            font.bold: true
                            elide: Text.ElideRight
                        }
                        Text {
                            Layout.fillWidth: true
                            text: focusedPage.pageInfo.subtitle
                            color: "#64748b"
                            font.pixelSize: root.bodyFont
                            elide: Text.ElideRight
                        }
                        Flow {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            spacing: Math.round(8 * root.contentScale)
                            Repeater {
                                model: focusedPage.pageInfo.tags || []
                                delegate: AdminTag { text: modelData.text; colorValue: modelData.color }
                            }
                        }
                    }

                    RowLayout {
                        visible: !root.narrowShell
                        spacing: Math.round(10 * root.contentScale)
                        AdminPrimaryButton {
                            Layout.preferredWidth: Math.round((focusedPage.isLogPage ? 138 : 132) * root.contentScale)
                            Layout.preferredHeight: Math.round(52 * root.contentScale)
                            text: focusedPage.pageInfo.primary
                        }
                        AdminGhostButton {
                            Layout.preferredWidth: Math.round(106 * root.contentScale)
                            Layout.preferredHeight: Math.round(52 * root.contentScale)
                            text: "刷新"
                            onClicked: root.refreshAdminData()
                        }
                        AdminGhostButton {
                            Layout.preferredWidth: Math.round(106 * root.contentScale)
                            Layout.preferredHeight: Math.round(52 * root.contentScale)
                            text: focusedPage.isLogPage ? "筛选" : "导出"
                        }
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: parent.width > 980 ? 4 : (parent.width > 560 ? 2 : 1)
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap
                Repeater {
                    model: focusedPage.pageInfo.stats || []
                    delegate: ManagementMetricCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 108 : Math.round(126 * root.contentScale)
                        label: modelData.label
                        value: modelData.value
                        colorValue: modelData.color
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: focusedPage.narrowContent ? 1 : 3
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: focusedPage.narrowContent ? 1 : 2
                    Layout.preferredHeight: root.narrowShell ? 650 : Math.round(650 * root.contentScale)
                    title: focusedPage.isLogPage ? "操作日志记录" : focusedPage.pageInfo.title + "列表"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                        anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                        anchors.topMargin: Math.round(68 * root.contentScale)
                        anchors.bottomMargin: Math.round(20 * root.contentScale)
                        spacing: Math.round(12 * root.contentScale)

                        Flow {
                            id: focusedFilters
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            spacing: Math.round(8 * root.contentScale)

                            TextField {
                                id: focusedSearch
                                width: focusedFilters.width < 680
                                       ? focusedFilters.width
                                       : Math.min(Math.round(390 * root.contentScale), Math.max(300, focusedFilters.width * 0.38))
                                height: Math.round(50 * root.contentScale)
                                text: root.keyword
                                placeholderText: focusedPage.isLogPage ? "搜索操作人、模块、操作内容或时间" : "搜索姓名、账号、班级、科目或状态"
                                color: "#111827"
                                font.pixelSize: root.bodyFont
                                leftPadding: Math.round(18 * root.contentScale)
                                rightPadding: Math.round(18 * root.contentScale)
                                verticalAlignment: TextInput.AlignVCenter
                                onTextChanged: root.keyword = text
                                background: Rectangle {
                                    radius: root.cardRadius
                                    color: "#f8fafc"
                                    border.color: focusedSearch.activeFocus ? "#93c5fd" : "#e5edf6"
                                }
                            }

                            Repeater {
                                model: focusedPage.isLogPage ? ["全部", "学生管理", "教师管理", "系统设置"] : ["全部", "已通过", "待审核", "冻结"]
                                delegate: Rectangle {
                                    width: Math.max(Math.round(92 * root.contentScale), tagText.implicitWidth + Math.round(30 * root.contentScale))
                                    height: Math.round(50 * root.contentScale)
                                    radius: root.cardRadius
                                    color: index === 0 ? "#eff6ff" : "#f8fafc"
                                    border.color: index === 0 ? "#bfdbfe" : "#e5edf6"
                                    Text {
                                        id: tagText
                                        anchors.centerIn: parent
                                        text: modelData
                                        color: index === 0 ? "#2563eb" : "#64748b"
                                        font.pixelSize: root.smallFont
                                        font.bold: true
                                    }
                                }
                            }

                            Text {
                                width: focusedFilters.width < 680 ? focusedFilters.width : implicitWidth + 8
                                height: Math.round(50 * root.contentScale)
                                text: "共 " + focusedPage.filteredRows().length + " 条"
                                color: "#64748b"
                                font.pixelSize: root.bodyFont
                                font.bold: true
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: focusedFilters.width < 680 ? Text.AlignRight : Text.AlignLeft
                            }
                        }

                        ManagementTable {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            headers: focusedPage.pageInfo.headers || []
                            rows: focusedPage.filteredRows()
                            weights: focusedPage.pageInfo.weights || []
                            statusIndex: focusedPage.pageInfo.statusIndex || -1
                        }
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.narrowShell ? 520 : Math.round(650 * root.contentScale)
                    title: focusedPage.isLogPage ? "日志处理" : "管理操作"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(66 * root.contentScale)
                        anchors.leftMargin: Math.round(20 * root.contentScale)
                        anchors.rightMargin: Math.round(20 * root.contentScale)
                        anchors.bottomMargin: Math.round(20 * root.contentScale)
                        spacing: Math.round(12 * root.contentScale)
                        Repeater {
                            model: focusedPage.pageInfo.actions || []
                            delegate: ManageActionCard {
                                title: modelData.title
                                detail: modelData.detail
                                accent: modelData.accent
                            }
                        }
                        Item { Layout.fillHeight: true }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Math.round(116 * root.contentScale)
                            radius: root.cardRadius
                            color: "#f8fafc"
                            border.color: "#e5edf6"
                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: Math.round(16 * root.contentScale)
                                spacing: Math.round(12 * root.contentScale)
                                Rectangle {
                                    Layout.preferredWidth: Math.round(48 * root.contentScale)
                                    Layout.preferredHeight: Math.round(48 * root.contentScale)
                                    radius: root.cardRadius
                                    color: "#fff7ed"
                                    Text { anchors.centerIn: parent; text: "!"; color: "#f97316"; font.pixelSize: root.panelTitleFont; font.bold: true }
                                }
                                Text {
                                    Layout.fillWidth: true
                                    text: focusedPage.pageInfo.risk || "关键操作会自动写入操作日志，便于后续审计。"
                                    color: "#475569"
                                    font.pixelSize: root.bodyFont
                                    wrapMode: Text.WordWrap
                                }
                            }
                        }
                    }
                }
            }

            GridLayout {
                visible: (focusedPage.pageInfo.workflowPanels || []).length > 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? implicitHeight : 0
                columns: parent.width > 1120 ? 2 : 1
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap
                Repeater {
                    model: focusedPage.pageInfo.workflowPanels || []
                    delegate: Panel {
                        property var workflow: modelData
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 336 : Math.round(360 * root.contentScale)
                        title: workflow.title
                        ManagementTable {
                            anchors.fill: parent
                            anchors.topMargin: Math.round(66 * root.contentScale)
                            anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                            anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                            anchors.bottomMargin: Math.round(20 * root.contentScale)
                            headers: workflow.headers || []
                            rows: workflow.rows || []
                            weights: workflow.weights || []
                            statusIndex: workflow.statusIndex || -1
                        }
                    }
                }
            }

            Panel {
                visible: (focusedPage.pageInfo.detailRows || []).length > 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? (root.narrowShell ? 330 : Math.round(360 * root.contentScale)) : 0
                title: focusedPage.pageInfo.detailTitle || "详情"
                ManagementTable {
                    anchors.fill: parent
                    anchors.topMargin: Math.round(66 * root.contentScale)
                    anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                    anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                    headers: focusedPage.pageInfo.detailHeaders || []
                    rows: focusedPage.pageInfo.detailRows || []
                    weights: focusedPage.pageInfo.detailWeights || []
                    statusIndex: focusedPage.pageInfo.detailStatusIndex || -1
                }
            }
        }
    }

    component AdminManagementPage: Item {
        id: pageRoot
        property string page: ""
        property var pageInfo: root.pageData(page)
        property int fallbackHeight: root.narrowShell ? Math.round(2520 * root.contentScale)
                                                      : Math.round((page === "操作日志" ? 2100 : 2200) * root.contentScale)
        height: Math.max(pageColumn.implicitHeight, fallbackHeight)

        function filteredRows() {
            var rows = pageInfo.rows || []
            var text = root.keyword.trim().toLowerCase()
            if (text.length === 0) {
                return rows
            }
            var result = []
            for (var i = 0; i < rows.length; ++i) {
                if (String(rows[i].join(" ")).toLowerCase().indexOf(text) >= 0) {
                    result.push(rows[i])
                }
            }
            return result
        }

        ColumnLayout {
            id: pageColumn
            width: parent.width
            spacing: root.gap

            Rectangle {
                id: managementHero
                property bool narrow: width < 760
                Layout.fillWidth: true
                Layout.preferredHeight: narrow ? Math.round(226 * root.contentScale) : Math.round(182 * root.contentScale)
                radius: root.cardRadius
                color: "#ffffff"
                border.color: "#dbeafe"
                Rectangle { anchors.fill: parent; anchors.topMargin: 5; radius: root.cardRadius; color: "#0f172a"; opacity: 0.04; z: -1 }
                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 7
                    radius: 4
                    color: "#2563eb"
                }
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: managementHero.narrow ? Math.round(20 * root.contentScale) : Math.round(28 * root.contentScale)
                    spacing: managementHero.narrow ? Math.round(12 * root.contentScale) : Math.round(14 * root.contentScale)
                    RowLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: !managementHero.narrow
                        spacing: Math.round(18 * root.contentScale)
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: Math.round(8 * root.contentScale)
                            Text {
                                Layout.fillWidth: true
                                text: pageRoot.pageInfo.title
                                color: "#0f172a"
                                font.pixelSize: root.narrowShell ? Math.round(28 * root.contentScale) : root.pageTitleFont
                                font.bold: true
                                elide: Text.ElideRight
                            }
                            Text {
                                Layout.fillWidth: true
                                text: pageRoot.pageInfo.subtitle
                                color: "#64748b"
                                font.pixelSize: root.bodyFont
                                elide: Text.ElideRight
                            }
                             Flow {
                                 Layout.fillWidth: true
                                 Layout.preferredHeight: implicitHeight
                                 spacing: Math.round(8 * root.contentScale)
                                Repeater {
                                    model: pageRoot.pageInfo.tags || [
                                        {"text": "管理端", "color": "#2563eb"},
                                        {"text": "实时数据", "color": "#16a34a"},
                                        {"text": "权限审计", "color": "#f97316"}
                                    ]
                                    delegate: AdminTag { text: modelData.text; colorValue: modelData.color }
                                }
                             }
                        }
                        RowLayout {
                            visible: !managementHero.narrow
                            spacing: Math.round(8 * root.contentScale)
                            AdminPrimaryButton {
                                Layout.preferredWidth: Math.round(130 * root.contentScale)
                                Layout.preferredHeight: Math.round(48 * root.contentScale)
                                text: pageRoot.pageInfo.primary
                            }
                            AdminGhostButton {
                                Layout.preferredWidth: Math.round(102 * root.contentScale)
                                Layout.preferredHeight: Math.round(48 * root.contentScale)
                                text: "刷新"
                                onClicked: root.refreshAdminData()
                            }
                            AdminGhostButton {
                                Layout.preferredWidth: Math.round(102 * root.contentScale)
                                Layout.preferredHeight: Math.round(48 * root.contentScale)
                                text: "导出"
                            }
                        }
                    }

                    RowLayout {
                        visible: managementHero.narrow
                        Layout.fillWidth: true
                        spacing: Math.round(8 * root.contentScale)
                        AdminPrimaryButton {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Math.round(48 * root.contentScale)
                            text: pageRoot.pageInfo.primary
                        }
                        AdminGhostButton {
                            Layout.preferredWidth: Math.round(88 * root.contentScale)
                            Layout.preferredHeight: Math.round(48 * root.contentScale)
                            text: "刷新"
                            onClicked: root.refreshAdminData()
                        }
                        AdminGhostButton {
                            Layout.preferredWidth: Math.round(88 * root.contentScale)
                            Layout.preferredHeight: Math.round(48 * root.contentScale)
                            text: "导出"
                        }
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: parent.width > 980 ? 4 : (parent.width > 560 ? 2 : 1)
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap
                Repeater {
                    model: pageRoot.pageInfo.stats || []
                    delegate: ManagementMetricCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 108 : Math.round(128 * root.contentScale)
                        label: modelData.label
                        value: modelData.value
                        colorValue: modelData.color
                    }
                }
            }

            GridLayout {
                visible: (pageRoot.pageInfo.workflowPanels || []).length > 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? implicitHeight : 0
                columns: parent.width > 1080 ? 2 : 1
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap
                Repeater {
                    model: pageRoot.pageInfo.workflowPanels || []
                    delegate: Panel {
                        property var workflow: modelData
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 338 : Math.round(398 * root.contentScale)
                        title: workflow.title
                        ManagementTable {
                            anchors.fill: parent
                            anchors.topMargin: Math.round(64 * root.contentScale)
                            anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                            anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                            anchors.bottomMargin: Math.round(20 * root.contentScale)
                            headers: workflow.headers || []
                            rows: workflow.rows || []
                            weights: workflow.weights || []
                            statusIndex: workflow.statusIndex || -1
                        }
                    }
                }
            }

            Panel {
                id: featurePanel
                property int featureCount: (pageRoot.pageInfo.featureSections || []).length
                property int featureColumns: root.narrowShell ? 1 : (width > Math.round(1180 * root.contentScale) ? 4 : 2)
                property int featureRows: Math.max(1, Math.ceil(featureCount / Math.max(1, featureColumns)))
                visible: featureCount > 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? Math.round((86 + featureRows * 214 + (featureRows - 1) * 14) * root.contentScale) : 0
                title: pageRoot.page === "操作日志" ? "日志审计功能" : (pageRoot.page === "学生管理" ? "学生管理功能" : "教师管理功能")

                GridLayout {
                    anchors.fill: parent
                    anchors.topMargin: Math.round(68 * root.contentScale)
                    anchors.leftMargin: root.narrowShell ? 16 : Math.round(22 * root.contentScale)
                    anchors.rightMargin: root.narrowShell ? 16 : Math.round(22 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                    columns: featurePanel.featureColumns
                    columnSpacing: root.compactShell ? 12 : Math.round(14 * root.contentScale)
                    rowSpacing: Math.round(14 * root.contentScale)
                    Repeater {
                        model: pageRoot.pageInfo.featureSections || []
                        delegate: ManagementFeatureCard {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            title: modelData.title
                            value: modelData.value
                            detail: modelData.detail
                            points: modelData.points || []
                            accent: modelData.accent
                        }
                    }
                }
            }

            Panel {
                visible: (pageRoot.pageInfo.focusCards || []).length > 0 && (pageRoot.pageInfo.workflowPanels || []).length === 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? (root.narrowShell ? Math.round(460 * root.contentScale) : Math.round(220 * root.contentScale)) : 0
                title: pageRoot.page === "学生管理" ? "学生管理核心事项" : "教师管理核心事项"
                GridLayout {
                    anchors.fill: parent
                    anchors.topMargin: Math.round(68 * root.contentScale)
                    anchors.leftMargin: root.narrowShell ? 16 : Math.round(22 * root.contentScale)
                    anchors.rightMargin: root.narrowShell ? 16 : Math.round(22 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                    columns: root.narrowShell ? 1 : 3
                    columnSpacing: root.gap
                    rowSpacing: Math.round(12 * root.contentScale)
                    Repeater {
                        model: pageRoot.pageInfo.focusCards || []
                        delegate: ManagementFocusCard {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            title: modelData.title
                            value: modelData.value
                            detail: modelData.detail
                            accent: modelData.accent
                        }
                    }
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: parent.width > 1120 ? 3 : 1
                columnSpacing: root.compactShell ? 12 : root.gap
                rowSpacing: root.compactShell ? 12 : root.gap

                Panel {
                    Layout.fillWidth: true
                    Layout.columnSpan: parent.width > 1120 ? 2 : 1
                    Layout.preferredHeight: root.narrowShell ? 600 : Math.round(700 * root.contentScale)
                    title: pageRoot.pageInfo.title + "列表"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.leftMargin: root.narrowShell ? 14 : Math.round(18 * root.contentScale)
                        anchors.rightMargin: root.narrowShell ? 14 : Math.round(18 * root.contentScale)
                        anchors.topMargin: Math.round(62 * root.contentScale)
                        anchors.bottomMargin: Math.round(18 * root.contentScale)
                        spacing: Math.round(12 * root.contentScale)

                        Flow {
                            id: managementFilters
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            spacing: 8

                            TextField {
                                id: adminSearch
                                width: managementFilters.width < 640
                                       ? managementFilters.width
                                       : Math.min(Math.round(340 * root.contentScale), Math.max(260, managementFilters.width * 0.34))
                                height: Math.round(48 * root.contentScale)
                                text: root.keyword
                                placeholderText: "搜索名称、账号、科目或状态"
                                color: "#111827"
                                font.pixelSize: root.bodyFont
                                leftPadding: Math.round(38 * root.contentScale)
                                onTextChanged: root.keyword = text
                                background: Rectangle {
                                    radius: root.cardRadius
                                    color: "#f8fafc"
                                    border.color: adminSearch.activeFocus ? "#93c5fd" : "#e5edf6"
                                    Text {
                                        anchors.left: parent.left
                                        anchors.leftMargin: Math.round(12 * root.contentScale)
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: "⌕"
                                        color: "#94a3b8"
                                        font.pixelSize: root.strongFont
                                    }
                                }
                            }

                            Row {
                                spacing: 6
                                height: Math.round(44 * root.contentScale)
                                Repeater {
                                    model: ["全部", "正常", "待处理", "异常"]
                                    delegate: Rectangle {
                                        width: root.narrowShell ? 78 : Math.round(92 * root.contentScale)
                                        height: Math.round(44 * root.contentScale)
                                        radius: root.cardRadius
                                        color: index === 0 ? "#eff6ff" : "#f8fafc"
                                        border.color: index === 0 ? "#bfdbfe" : "#e5edf6"
                                        Text {
                                            anchors.centerIn: parent
                                            text: modelData
                                            color: index === 0 ? "#2563eb" : "#64748b"
                                            font.pixelSize: root.smallFont
                                            font.bold: true
                                        }
                                    }
                                }
                            }

                            Text {
                                width: managementFilters.width < 640 ? managementFilters.width : implicitWidth + 10
                                height: Math.round(44 * root.contentScale)
                                text: "共 " + pageRoot.filteredRows().length + " 条"
                                color: "#64748b"
                                font.pixelSize: root.bodyFont
                                font.bold: true
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: managementFilters.width < 640 ? Text.AlignRight : Text.AlignLeft
                            }
                        }

                         ManagementTable {
                             Layout.fillWidth: true
                             Layout.fillHeight: true
                             headers: pageRoot.pageInfo.headers
                             rows: pageRoot.filteredRows()
                             weights: pageRoot.pageInfo.weights || []
                             statusIndex: pageRoot.pageInfo.statusIndex
                         }
                    }
                }

                Panel {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.narrowShell ? 600 : Math.round(700 * root.contentScale)
                    title: "页面操作"
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.topMargin: Math.round(64 * root.contentScale)
                        anchors.leftMargin: Math.round(20 * root.contentScale)
                        anchors.rightMargin: Math.round(20 * root.contentScale)
                        anchors.bottomMargin: Math.round(20 * root.contentScale)
                        spacing: Math.round(13 * root.contentScale)
                        Repeater {
                            model: pageRoot.pageInfo.actions || [
                                {"title": "批量处理", "detail": "勾选列表数据后可统一启用、冻结、审核或导出", "accent": "#2563eb"},
                                {"title": "权限校验", "detail": "关键操作会记录到操作日志，便于后续审计", "accent": "#7c3aed"},
                                {"title": "数据同步", "detail": "页面数据与考试、用户、题库模块保持同步", "accent": "#16a34a"}
                            ]
                            delegate: ManageActionCard {
                                title: modelData.title
                                detail: modelData.detail
                                accent: modelData.accent
                            }
                        }
                        Item { Layout.fillHeight: true }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Math.round(100 * root.contentScale)
                            radius: root.cardRadius
                            color: "#f8fafc"
                            border.color: "#e5edf6"
                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: Math.round(14 * root.contentScale)
                                spacing: Math.round(12 * root.contentScale)
                                Rectangle {
                                    Layout.preferredWidth: Math.round(46 * root.contentScale)
                                    Layout.preferredHeight: Math.round(46 * root.contentScale)
                                    radius: 12
                                    color: "#fee2e2"
                                    Text { anchors.centerIn: parent; text: "!"; color: "#ef4444"; font.pixelSize: root.panelTitleFont; font.bold: true }
                                }
                                 Text {
                                     Layout.fillWidth: true
                                     text: pageRoot.pageInfo.risk || "删除、冻结、恢复等高风险操作请二次确认。"
                                     color: "#475569"
                                     font.pixelSize: root.bodyFont
                                     wrapMode: Text.WordWrap
                                }
                            }
                        }
                    }
                }
            }

            Panel {
                visible: pageRoot.page === "操作日志"
                Layout.fillWidth: true
                Layout.preferredHeight: pageRoot.page === "操作日志" ? Math.round(230 * root.contentScale) : 0
                 title: "操作日志摘要"
                 OperationLogPanel {
                    anchors.fill: parent
                    anchors.topMargin: Math.round(64 * root.contentScale)
                    anchors.leftMargin: Math.round(22 * root.contentScale)
                    anchors.rightMargin: Math.round(22 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                 }
             }

            Panel {
                visible: (pageRoot.pageInfo.detailRows || []).length > 0
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? (root.narrowShell ? 282 : Math.round(330 * root.contentScale)) : 0
                title: pageRoot.pageInfo.detailTitle || "详情"
                ManagementTable {
                    anchors.fill: parent
                    anchors.topMargin: Math.round(64 * root.contentScale)
                    anchors.leftMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                    anchors.rightMargin: root.narrowShell ? 14 : Math.round(20 * root.contentScale)
                    anchors.bottomMargin: Math.round(20 * root.contentScale)
                    headers: pageRoot.pageInfo.detailHeaders || []
                    rows: pageRoot.pageInfo.detailRows || []
                    weights: pageRoot.pageInfo.detailWeights || []
                    statusIndex: pageRoot.pageInfo.detailStatusIndex || -1
                }
            }
         }
     }

    component ManagementFocusCard: Rectangle {
        id: focusCard
        property string title: ""
        property string value: ""
        property string detail: ""
        property color accent: "#2563eb"
        radius: Math.round(16 * root.contentScale)
        color: "#f8fbff"
        border.color: Qt.rgba(focusCard.accent.r, focusCard.accent.g, focusCard.accent.b, 0.28)
        RowLayout {
            anchors.fill: parent
            anchors.margins: Math.round(20 * root.contentScale)
            spacing: Math.round(16 * root.contentScale)
            Rectangle {
                Layout.preferredWidth: Math.round(58 * root.contentScale)
                Layout.preferredHeight: Math.round(58 * root.contentScale)
                radius: Math.round(18 * root.contentScale)
                color: Qt.rgba(focusCard.accent.r, focusCard.accent.g, focusCard.accent.b, 0.13)
                Text { anchors.centerIn: parent; text: "•"; color: focusCard.accent; font.pixelSize: Math.round(36 * root.contentScale); font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(5 * root.contentScale)
                Text { Layout.fillWidth: true; text: focusCard.title; color: "#0f172a"; font.pixelSize: root.strongFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: focusCard.value; color: focusCard.accent; font.pixelSize: Math.round(32 * root.contentScale); font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: focusCard.detail; color: "#64748b"; font.pixelSize: root.bodyFont; wrapMode: Text.WordWrap; maximumLineCount: 2 }
            }
        }
    }

    component ManagementFeatureCard: Rectangle {
        id: featureCard
        property string title: ""
        property string value: ""
        property string detail: ""
        property var points: []
        property color accent: "#2563eb"
        radius: root.cardRadius
        color: "#f8fbff"
        border.color: Qt.rgba(featureCard.accent.r, featureCard.accent.g, featureCard.accent.b, 0.26)
        clip: true

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: Math.round(5 * root.contentScale)
            color: featureCard.accent
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: Math.round(18 * root.contentScale)
            anchors.rightMargin: Math.round(16 * root.contentScale)
            anchors.topMargin: Math.round(16 * root.contentScale)
            anchors.bottomMargin: Math.round(14 * root.contentScale)
            spacing: Math.round(9 * root.contentScale)

            RowLayout {
                Layout.fillWidth: true
                spacing: Math.round(10 * root.contentScale)
                Rectangle {
                    Layout.preferredWidth: Math.round(42 * root.contentScale)
                    Layout.preferredHeight: Math.round(42 * root.contentScale)
                    radius: Math.round(12 * root.contentScale)
                    color: Qt.rgba(featureCard.accent.r, featureCard.accent.g, featureCard.accent.b, 0.13)
                    Text {
                        anchors.centerIn: parent
                        text: "✓"
                        color: featureCard.accent
                        font.pixelSize: root.strongFont
                        font.bold: true
                    }
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 2
                    Text {
                        Layout.fillWidth: true
                        text: featureCard.title
                        color: "#0f172a"
                        font.pixelSize: root.strongFont
                        font.bold: true
                        elide: Text.ElideRight
                    }
                    Text {
                        Layout.fillWidth: true
                        text: featureCard.value
                        color: featureCard.accent
                        font.pixelSize: Math.round(27 * root.contentScale)
                        font.bold: true
                        elide: Text.ElideRight
                    }
                }
            }

            Text {
                Layout.fillWidth: true
                text: featureCard.detail
                color: "#475569"
                font.pixelSize: root.bodyFont
                wrapMode: Text.WordWrap
                maximumLineCount: 3
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(5 * root.contentScale)
                Repeater {
                    model: featureCard.points
                    delegate: RowLayout {
                        Layout.fillWidth: true
                        spacing: Math.round(8 * root.contentScale)
                        Rectangle {
                            Layout.preferredWidth: Math.round(7 * root.contentScale)
                            Layout.preferredHeight: Math.round(7 * root.contentScale)
                            radius: Math.round(4 * root.contentScale)
                            color: featureCard.accent
                            opacity: 0.9
                        }
                        Text {
                            Layout.fillWidth: true
                            text: modelData
                            color: "#334155"
                            font.pixelSize: root.smallFont
                            font.bold: true
                            elide: Text.ElideRight
                        }
                    }
                }
            }
        }
    }

    component ManagementMetricCard: Rectangle {
        id: metric
        property string label: ""
        property string value: ""
        property color colorValue: "#2563eb"
        radius: root.cardRadius
        color: "#ffffff"
        border.color: "#e7edf6"
        Rectangle { anchors.fill: parent; anchors.topMargin: 5; radius: root.cardRadius; color: "#0f172a"; opacity: 0.04; z: -1 }
        RowLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 16 : Math.round(18 * root.contentScale)
            spacing: root.narrowShell ? 12 : Math.round(14 * root.contentScale)
            Rectangle {
                Layout.preferredWidth: root.narrowShell ? 40 : Math.round(46 * root.contentScale)
                Layout.preferredHeight: root.narrowShell ? 40 : Math.round(46 * root.contentScale)
                radius: Math.round(12 * root.contentScale)
                color: Qt.rgba(metric.colorValue.r, metric.colorValue.g, metric.colorValue.b, 0.12)
                Text { anchors.centerIn: parent; text: "•"; color: metric.colorValue; font.pixelSize: root.narrowShell ? 26 : root.statValueFont; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(3 * root.contentScale)
                Text { Layout.fillWidth: true; text: metric.label; color: "#64748b"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: metric.value; color: "#0f172a"; font.pixelSize: root.narrowShell ? Math.round(26 * root.contentScale) : Math.round(31 * root.contentScale); font.bold: true; elide: Text.ElideRight }
            }
        }
    }

    component AdminTag: Rectangle {
        id: tag
        property string text: ""
        property color colorValue: "#2563eb"
        width: tagText.implicitWidth + Math.round(20 * root.contentScale)
        height: Math.round(32 * root.contentScale)
        radius: root.cardRadius
        color: Qt.rgba(tag.colorValue.r, tag.colorValue.g, tag.colorValue.b, 0.11)
        Text {
            id: tagText
            anchors.centerIn: parent
            text: tag.text
            color: tag.colorValue
            font.pixelSize: root.smallFont
            font.bold: true
        }
    }

    component AdminPrimaryButton: Rectangle {
        id: button
        property string text: ""
        signal clicked()
        implicitWidth: Math.max(Math.round(126 * root.contentScale), buttonText.implicitWidth + Math.round(46 * root.contentScale))
        implicitHeight: Math.round(50 * root.contentScale)
        height: implicitHeight
        radius: root.cardRadius
        color: mouse.containsMouse ? "#1d4ed8" : "#2563eb"
        Text { id: buttonText; anchors.centerIn: parent; text: button.text; color: "#ffffff"; font.pixelSize: root.strongFont; font.bold: true; elide: Text.ElideRight; width: parent.width - 18; horizontalAlignment: Text.AlignHCenter }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: button.clicked() }
    }

    component AdminGhostButton: Rectangle {
        id: button
        property string text: ""
        signal clicked()
        implicitWidth: Math.max(Math.round(108 * root.contentScale), buttonText.implicitWidth + Math.round(42 * root.contentScale))
        implicitHeight: Math.round(50 * root.contentScale)
        height: implicitHeight
        radius: root.cardRadius
        color: mouse.containsMouse ? "#eff6ff" : "#ffffff"
        border.color: mouse.containsMouse ? "#93c5fd" : "#dbe3ef"
        Text { id: buttonText; anchors.centerIn: parent; text: button.text; color: "#2563eb"; font.pixelSize: root.strongFont; font.bold: true; elide: Text.ElideRight; width: parent.width - 16; horizontalAlignment: Text.AlignHCenter }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: button.clicked() }
    }

    component ManagementTable: Rectangle {
        id: tableRoot
        property var headers: []
        property var rows: []
        property var weights: []
        property var effectiveWeights: weights.length > 0 ? weights : [1.22, 1.0, 1.05, 1.18, 0.84, 1.0]
        property int statusIndex: -1
        property real contentMinWidth: {
            var total = 0
            for (var i = 0; i < headers.length; ++i) {
                total += effectiveWeights.length > i ? Number(effectiveWeights[i]) : 1
            }
            return Math.max(width, Math.round(total * (root.narrowShell ? 112 : 142) * root.contentScale) + 32)
        }
        color: "transparent"
        clip: true
        Flickable {
            id: tableFlick
            anchors.fill: parent
            contentWidth: tableRoot.contentMinWidth
            contentHeight: tableColumn.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            interactive: contentWidth > width || contentHeight > height
            ScrollBar.horizontal: ScrollBar { policy: tableFlick.contentWidth > tableFlick.width ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
            ScrollBar.vertical: ScrollBar { policy: tableFlick.contentHeight > tableFlick.height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
            HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
            ColumnLayout {
                id: tableColumn
                width: tableFlick.contentWidth
                spacing: 0
                TableHeader {
                    values: tableRoot.headers
                    weights: tableRoot.effectiveWeights
                }
                Repeater {
                    model: tableRoot.rows
                    delegate: TableRow {
                        values: modelData
                        weights: tableRoot.effectiveWeights
                        statusIndex: tableRoot.statusIndex
                    }
                }
            }
        }
    }

    component ManageActionCard: Rectangle {
        id: card
        property string title: ""
        property string detail: ""
        property color accent: "#2563eb"
        Layout.fillWidth: true
        Layout.preferredHeight: Math.round(104 * root.contentScale)
        radius: root.cardRadius
        color: "#f8fafc"
        border.color: "#e5edf6"
        RowLayout {
            anchors.fill: parent
            anchors.margins: Math.round(15 * root.contentScale)
            spacing: Math.round(12 * root.contentScale)
            Rectangle {
                Layout.preferredWidth: Math.round(48 * root.contentScale)
                Layout.preferredHeight: Math.round(48 * root.contentScale)
                radius: Math.round(12 * root.contentScale)
                color: Qt.rgba(card.accent.r, card.accent.g, card.accent.b, 0.13)
                Text { anchors.centerIn: parent; text: "✓"; color: card.accent; font.pixelSize: root.navFont; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(4 * root.contentScale)
                Text { Layout.fillWidth: true; text: card.title; color: "#111827"; font.pixelSize: root.strongFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: card.detail; color: "#64748b"; font.pixelSize: root.smallFont; wrapMode: Text.WordWrap; maximumLineCount: 2 }
            }
        }
    }

    component SidebarItem: Rectangle {
        id: item
        property string text: ""
        property string icon: ""
        property bool selected: false
        property bool compact: false
        signal clicked()
        height: compact ? 58 : Math.round(70 * root.contentScale)
        radius: root.cardRadius
        color: selected ? "#2d63f6" : (mouse.containsMouse ? "#1d314c" : "transparent")
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: item.compact ? 0 : Math.round(26 * root.contentScale)
            anchors.rightMargin: item.compact ? 0 : Math.round(18 * root.contentScale)
            spacing: item.compact ? 0 : Math.round(22 * root.contentScale)
            SidebarMenuIcon {
                Layout.preferredWidth: item.compact ? 26 : Math.round(31 * root.contentScale)
                Layout.preferredHeight: item.compact ? 26 : Math.round(31 * root.contentScale)
                Layout.alignment: item.compact ? Qt.AlignHCenter : Qt.AlignVCenter
                kind: item.icon
                selected: item.selected
            }
                Text { visible: !item.compact; Layout.fillWidth: true; text: item.text; color: "#f3f7ff"; font.pixelSize: root.navFont; font.bold: true; elide: Text.ElideRight }
            Text { visible: !item.compact && !item.selected && item.text !== "系统概览"; text: "›"; color: "#a7b7cc"; font.pixelSize: Math.round(27 * root.contentScale) }
        }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: item.clicked() }
    }

    component SidebarLogo: Item {
        Image {
            anchors.fill: parent
            source: "qrc:/assets/brand-logo-mark.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            mipmap: true
        }
    }

    component SidebarMenuIcon: Canvas {
        id: menuIcon
        property string kind: ""
        property bool selected: false
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = menuIcon.selected ? "#ffffff" : "#dce8f8"
            ctx.fillStyle = ctx.strokeStyle
            ctx.lineWidth = 2
            ctx.lineCap = "round"
            ctx.lineJoin = "round"
            var k = menuIcon.kind
            if (k === "home") {
                ctx.beginPath(); ctx.moveTo(3, 11); ctx.lineTo(11, 4); ctx.lineTo(19, 11); ctx.stroke()
                ctx.strokeRect(6, 11, 10, 8)
            } else if (k === "monitor") {
                ctx.strokeRect(4, 5, 14, 10); ctx.beginPath(); ctx.moveTo(11, 15); ctx.lineTo(11, 19); ctx.moveTo(7, 19); ctx.lineTo(15, 19); ctx.stroke()
            } else if (k === "settings") {
                ctx.beginPath(); ctx.arc(11, 11, 5, 0, Math.PI * 2); ctx.stroke()
                for (var i = 0; i < 6; ++i) { var a = i * Math.PI / 3; ctx.beginPath(); ctx.moveTo(11 + Math.cos(a) * 7, 11 + Math.sin(a) * 7); ctx.lineTo(11 + Math.cos(a) * 9, 11 + Math.sin(a) * 9); ctx.stroke() }
            } else if (k === "backup") {
                ctx.beginPath()
                ctx.moveTo(4, 6)
                ctx.quadraticCurveTo(11, 2, 18, 6)
                ctx.quadraticCurveTo(11, 10, 4, 6)
                ctx.stroke()
                ctx.beginPath()
                ctx.moveTo(4, 6); ctx.lineTo(4, 16)
                ctx.quadraticCurveTo(11, 20, 18, 16)
                ctx.lineTo(18, 6)
                ctx.stroke()
            } else if (k === "exam" || k === "paper" || k === "logs" || k === "question" || k === "audit" || k === "score") {
                ctx.strokeRect(5, 3, 12, 16); ctx.beginPath(); ctx.moveTo(8, 8); ctx.lineTo(14, 8); ctx.moveTo(8, 12); ctx.lineTo(15, 12); ctx.moveTo(8, 16); ctx.lineTo(12, 16); ctx.stroke()
                if (k === "audit") { ctx.beginPath(); ctx.moveTo(11, 17); ctx.lineTo(14, 20); ctx.lineTo(19, 14); ctx.stroke() }
            } else {
                ctx.beginPath(); ctx.arc(8, 8, 4, 0, Math.PI * 2); ctx.arc(15, 9, 3, 0, Math.PI * 2); ctx.fill()
                ctx.beginPath(); ctx.moveTo(3, 19); ctx.quadraticCurveTo(8, 13, 13, 19); ctx.moveTo(11, 19); ctx.quadraticCurveTo(15, 14, 20, 19); ctx.stroke()
            }
        }
        onKindChanged: requestPaint()
        onSelectedChanged: requestPaint()
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component FullscreenIcon: Canvas {
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = "#334155"
            ctx.lineWidth = 2
            ctx.lineCap = "round"
            var p = 6, q = width - 6
            ctx.beginPath()
            ctx.moveTo(p, 11); ctx.lineTo(p, p); ctx.lineTo(11, p)
            ctx.moveTo(q - 5, p); ctx.lineTo(q, p); ctx.lineTo(q, 11)
            ctx.moveTo(q, q - 5); ctx.lineTo(q, q); ctx.lineTo(q - 5, q)
            ctx.moveTo(11, q); ctx.lineTo(p, q); ctx.lineTo(p, q - 5)
            ctx.stroke()
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component AdminAvatar: Canvas {
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.fillStyle = "#dbeafe"
            ctx.beginPath(); ctx.arc(width / 2, height / 2, width / 2, 0, Math.PI * 2); ctx.fill()
            ctx.fillStyle = "#1f2937"
            ctx.beginPath(); ctx.arc(width / 2, 15, 9, Math.PI, 0); ctx.fill()
            ctx.fillStyle = "#f7c59b"
            ctx.beginPath(); ctx.arc(width / 2, 18, 8, 0, Math.PI * 2); ctx.fill()
            ctx.fillStyle = "#2563eb"
            ctx.beginPath(); ctx.moveTo(10, 37); ctx.quadraticCurveTo(width / 2, 25, width - 10, 37); ctx.closePath(); ctx.fill()
            ctx.strokeStyle = "#ffffff"; ctx.lineWidth = 2
            ctx.beginPath(); ctx.moveTo(width / 2 - 5, 17); ctx.lineTo(width / 2 - 5, 17); ctx.moveTo(width / 2 + 5, 17); ctx.lineTo(width / 2 + 5, 17); ctx.stroke()
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component StatGlyph: Canvas {
        id: glyph
        property string kind: ""
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = "#ffffff"
            ctx.fillStyle = "#ffffff"
            ctx.lineWidth = 3
            ctx.lineCap = "round"
            ctx.lineJoin = "round"
            if (glyph.kind === "users" || glyph.kind === "teacher") {
                ctx.beginPath(); ctx.arc(13, 12, 6, 0, Math.PI * 2); ctx.fill()
                ctx.beginPath(); ctx.arc(25, 15, 5, 0, Math.PI * 2); ctx.fill()
                ctx.beginPath(); ctx.moveTo(4, 31); ctx.quadraticCurveTo(13, 21, 22, 31); ctx.moveTo(19, 31); ctx.quadraticCurveTo(26, 24, 32, 31); ctx.stroke()
                if (glyph.kind === "teacher") { ctx.strokeRect(24, 2, 7, 7); ctx.beginPath(); ctx.moveTo(27, 4); ctx.lineTo(27, 7); ctx.moveTo(25, 5.5); ctx.lineTo(30, 5.5); ctx.stroke() }
            } else if (glyph.kind === "exam" || glyph.kind === "paper") {
                ctx.strokeRect(8, 4, 18, 25)
                ctx.beginPath(); ctx.moveTo(13, 11); ctx.lineTo(22, 11); ctx.moveTo(13, 17); ctx.lineTo(22, 17); ctx.moveTo(13, 23); ctx.lineTo(18, 23); ctx.stroke()
                if (glyph.kind === "paper") { ctx.beginPath(); ctx.moveTo(22, 4); ctx.lineTo(26, 8); ctx.lineTo(22, 8); ctx.closePath(); ctx.fill() }
            } else if (glyph.kind === "today") {
                ctx.strokeRect(7, 8, 20, 21)
                ctx.beginPath(); ctx.moveTo(12, 4); ctx.lineTo(12, 11); ctx.moveTo(22, 4); ctx.lineTo(22, 11); ctx.moveTo(12, 20); ctx.lineTo(16, 24); ctx.lineTo(23, 16); ctx.stroke()
            }
        }
        onKindChanged: requestPaint()
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component Panel: Rectangle {
        id: panel
        property string title: ""
        radius: root.cardRadius
        color: "#ffffff"
        border.color: "#e8eef7"
        antialiasing: true
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowOpacity: 0.10
            shadowBlur: 0.55
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 0
        }
        Text {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: Math.round(22 * root.contentScale)
            anchors.topMargin: Math.round(22 * root.contentScale)
            text: panel.title
            color: "#111827"
            font.pixelSize: root.panelTitleFont
            font.bold: true
        }
    }

    component StatCard: Rectangle {
        id: stat
        property string title: ""
        property string value: ""
        property string delta: ""
        property string icon: ""
        property color fromColor: "#60a5ff"
        property color toColor: "#2563eb"
        radius: root.cardRadius
        color: "#ffffff"
        border.color: "#e8eef7"
        antialiasing: true
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowOpacity: 0.10
            shadowBlur: 0.55
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 0
        }
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: root.narrowShell ? 16 : Math.round(22 * root.contentScale)
            anchors.rightMargin: root.narrowShell ? 16 : Math.round(20 * root.contentScale)
            anchors.topMargin: root.narrowShell ? 16 : Math.round(20 * root.contentScale)
            anchors.bottomMargin: root.narrowShell ? 16 : Math.round(20 * root.contentScale)
            spacing: root.narrowShell ? 12 : Math.round(18 * root.contentScale)
            Rectangle {
                Layout.preferredWidth: root.narrowShell ? 54 : Math.round(64 * root.contentScale)
                Layout.preferredHeight: root.narrowShell ? 54 : Math.round(64 * root.contentScale)
                radius: root.narrowShell ? 11 : Math.round(12 * root.contentScale)
                gradient: Gradient {
                    GradientStop { position: 0.0; color: stat.fromColor }
                    GradientStop { position: 1.0; color: stat.toColor }
                }
                StatGlyph { anchors.centerIn: parent; width: root.narrowShell ? 31 : Math.round(36 * root.contentScale); height: width; kind: stat.icon }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(4 * root.contentScale)
                Text { Layout.fillWidth: true; text: stat.title; color: "#475569"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: stat.value; color: "#0f172a"; font.pixelSize: root.narrowShell ? Math.round(24 * root.contentScale) : root.statValueFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: "较昨日  ↑ " + stat.delta; color: "#0aa85a"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
            }
        }
    }

    component AdminUserMenu: Item {
        id: userMenu
        z: 2

        Rectangle {
            id: profileChip
            anchors.fill: parent
            radius: height / 2
            color: chipMouse.containsMouse ? "#eff6ff" : "#ffffff"
            border.color: chipMouse.containsMouse ? "#bfdbfe" : "#e5edf6"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: root.compactShell ? 6 : Math.round(10 * root.contentScale)
                anchors.rightMargin: root.compactShell ? 6 : Math.round(18 * root.contentScale)
                spacing: root.compactShell ? 0 : Math.round(14 * root.contentScale)
                AdminAvatar { Layout.preferredWidth: root.compactShell ? 44 : Math.round(54 * root.contentScale); Layout.preferredHeight: root.compactShell ? 44 : Math.round(54 * root.contentScale) }
                ColumnLayout {
                    visible: !root.compactShell
                    Layout.fillWidth: true
                    spacing: Math.round(2 * root.contentScale)
                    Text { Layout.fillWidth: true; text: adminApi.adminName(); color: "#111827"; font.pixelSize: root.strongFont; font.bold: true; elide: Text.ElideRight }
                    Text { Layout.fillWidth: true; text: "超级管理员"; color: "#64748b"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                }
            }
            MouseArea {
                id: chipMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: root.openAdminProfile(0)
            }
        }
    }

    component AdminMenuAction: Rectangle {
        id: action
        property string title: ""
        property string hint: ""
        property bool danger: false
        signal clicked()
        Layout.fillWidth: true
        Layout.preferredHeight: Math.round(46 * root.contentScale)
        radius: root.cardRadius
        color: actionMouse.containsMouse ? (danger ? "#fef2f2" : "#eff6ff") : "transparent"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Math.round(12 * root.contentScale)
            anchors.rightMargin: Math.round(12 * root.contentScale)
            spacing: Math.round(10 * root.contentScale)
            Text { Layout.fillWidth: true; text: action.title; color: action.danger ? "#ef4444" : "#111827"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
            Text { text: action.hint; color: action.danger ? "#ef4444" : "#94a3b8"; font.pixelSize: root.smallFont }
        }
        MouseArea { id: actionMouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: action.clicked() }
    }

    component AdminNoticeButton: Item {
        id: notice
        property bool allOpen: false
        property bool open: false
        z: open ? 150 : 2

        function keepOpen() {
            closeNoticeTimer.stop()
            open = true
        }

        function requestClose() {
            closeNoticeTimer.restart()
        }

        Timer {
            id: closeNoticeTimer
            interval: 260
            repeat: false
            onTriggered: {
                if (!bellMouse.containsMouse && !noticePanelMouse.containsMouse && !showAllWarningsMouse.containsMouse && !allNoticePanelMouse.containsMouse && !closeAllWarningsMouse.containsMouse) {
                    notice.open = false
                    notice.allOpen = false
                }
            }
        }

        Rectangle {
            id: bell
            anchors.centerIn: parent
            width: root.narrowShell ? 52 : Math.round(62 * root.contentScale)
            height: root.narrowShell ? 52 : Math.round(62 * root.contentScale)
            radius: width / 2
            color: notice.open ? "#eff6ff" : "transparent"
            BellIcon { anchors.centerIn: parent; width: Math.round(36 * root.contentScale); height: width }
            Rectangle {
                width: Math.round(26 * root.contentScale)
                height: Math.round(26 * root.contentScale)
                radius: 9
                color: "#ef4444"
                anchors.right: parent.right
                anchors.rightMargin: -2
                anchors.top: parent.top
                anchors.topMargin: -2
                border.color: "#ffffff"
                border.width: Math.max(2, Math.round(2 * root.contentScale))
                Text { anchors.centerIn: parent; text: String(root.alerts.length); color: "#ffffff"; font.pixelSize: root.smallFont; font.bold: true }
            }
            MouseArea {
                id: bellMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onEntered: notice.keepOpen()
                onExited: notice.requestClose()
            }
        }

        Rectangle {
            id: noticePanel
            width: Math.round(430 * root.contentScale)
            height: Math.round(350 * root.contentScale)
            x: notice.width - width
            y: notice.height + Math.round(4 * root.contentScale)
            radius: Math.round(22 * root.contentScale)
            color: "#ffffff"
            border.color: "#dbe7f6"
            visible: notice.open && !notice.allOpen
            opacity: notice.open && !notice.allOpen ? 1 : 0
            scale: notice.open && !notice.allOpen ? 1 : 0.98
            transformOrigin: Item.TopRight
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: true
                shadowOpacity: 0.16
                shadowBlur: 0.65
                shadowVerticalOffset: 8
            }
            Behavior on opacity { NumberAnimation { duration: 120 } }
            Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutCubic } }
            MouseArea {
                id: noticePanelMouse
                anchors.fill: parent
                hoverEnabled: true
                onEntered: notice.keepOpen()
                onExited: notice.requestClose()
            }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Math.round(20 * root.contentScale)
                spacing: Math.round(12 * root.contentScale)
                RowLayout {
                    Layout.fillWidth: true
                    Text { Layout.fillWidth: true; text: "系统警告"; color: "#0f172a"; font.pixelSize: root.panelTitleFont; font.bold: true; elide: Text.ElideRight }
                    Rectangle {
                        Layout.preferredWidth: Math.round(104 * root.contentScale)
                        Layout.preferredHeight: Math.round(36 * root.contentScale)
                        radius: Math.round(18 * root.contentScale)
                        color: "#fef2f2"
                        Text { anchors.centerIn: parent; text: root.alerts.length + " 条未读"; color: "#ef4444"; font.pixelSize: root.smallFont; font.bold: true }
                    }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Repeater {
                    model: root.alerts
                    delegate: AdminAlertNoticeRow { row: modelData }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Text {
                    Layout.fillWidth: true
                    Layout.preferredHeight: Math.round(44 * root.contentScale)
                    text: "查看全部警告"
                    color: "#2563eb"
                    font.pixelSize: root.bodyFont
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    MouseArea {
                        id: showAllWarningsMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onEntered: notice.keepOpen()
                        onExited: notice.requestClose()
                        onClicked: {
                            notice.keepOpen()
                            notice.allOpen = true
                        }
                    }
                }
            }
        }

        Rectangle {
            id: allNoticePanel
            width: Math.round(540 * root.contentScale)
            height: Math.round(500 * root.contentScale)
            x: notice.width - width
            y: notice.height + Math.round(4 * root.contentScale)
            radius: Math.round(24 * root.contentScale)
            color: "#ffffff"
            border.color: "#dbe7f6"
            visible: notice.allOpen
            z: 180
            layer.enabled: true
            layer.effect: MultiEffect {
                shadowEnabled: true
                shadowOpacity: 0.16
                shadowBlur: 0.65
                shadowVerticalOffset: 8
            }
            MouseArea {
                id: allNoticePanelMouse
                anchors.fill: parent
                hoverEnabled: true
                onEntered: notice.keepOpen()
                onExited: notice.requestClose()
            }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Math.round(22 * root.contentScale)
                spacing: Math.round(14 * root.contentScale)
                RowLayout {
                    Layout.fillWidth: true
                    Text { Layout.fillWidth: true; text: "全部系统警告"; color: "#0f172a"; font.pixelSize: root.panelTitleFont; font.bold: true; elide: Text.ElideRight }
                    Text {
                        text: "×"
                        color: "#94a3b8"
                        font.pixelSize: root.navFont
                        font.bold: true
                        MouseArea {
                            id: closeAllWarningsMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onEntered: notice.keepOpen()
                            onExited: notice.requestClose()
                            onClicked: {
                                notice.allOpen = false
                                notice.open = false
                            }
                        }
                    }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Flickable {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: width
                    contentHeight: allNoticeColumn.height
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                    HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                    Column {
                        id: allNoticeColumn
                        width: parent.width
                        spacing: Math.round(12 * root.contentScale)
                        Repeater {
                            model: root.alerts
                            delegate: AdminAlertCard { width: allNoticeColumn.width; row: modelData }
                        }
                    }
                }
            }
        }
    }

    component AdminAlertNoticeRow: RowLayout {
        property var row: ({})
        Layout.fillWidth: true
        Layout.preferredHeight: Math.round(64 * root.contentScale)
        spacing: Math.round(12 * root.contentScale)
        Rectangle {
            Layout.preferredWidth: Math.round(42 * root.contentScale)
            Layout.preferredHeight: Math.round(42 * root.contentScale)
            radius: width / 2
            color: row.status === "未处理" ? "#fef2f2" : "#fff7ed"
            Text { anchors.centerIn: parent; text: row.status === "未处理" ? "!" : "…"; color: row.status === "未处理" ? "#ef4444" : "#f97316"; font.pixelSize: root.strongFont; font.bold: true }
        }
        ColumnLayout {
            Layout.fillWidth: true
            spacing: Math.round(3 * root.contentScale)
            Text { Layout.fillWidth: true; text: row.type; color: "#111827"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
            Text { Layout.fillWidth: true; text: row.content; color: "#64748b"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
        }
        Text { text: row.status; color: root.statusFg(row.status); font.pixelSize: root.smallFont; font.bold: true }
    }

    component AdminAlertCard: Rectangle {
        id: alertCard
        property var row: ({})
        height: Math.round(104 * root.contentScale)
        radius: root.cardRadius
        color: "#f8fbff"
        border.color: "#e2edf8"
        RowLayout {
            anchors.fill: parent
            anchors.margins: Math.round(16 * root.contentScale)
            spacing: Math.round(14 * root.contentScale)
            Rectangle {
                Layout.preferredWidth: Math.round(50 * root.contentScale)
                Layout.preferredHeight: Math.round(50 * root.contentScale)
                radius: width / 2
                color: alertCard.row.status === "未处理" ? "#fef2f2" : "#fff7ed"
                Text { anchors.centerIn: parent; text: alertCard.row.status === "未处理" ? "!" : "…"; color: alertCard.row.status === "未处理" ? "#ef4444" : "#f97316"; font.pixelSize: root.strongFont; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: Math.round(4 * root.contentScale)
                Text { Layout.fillWidth: true; text: alertCard.row.type; color: "#111827"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: alertCard.row.content; color: "#4b5563"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: alertCard.row.time; color: "#94a3b8"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
            }
            Rectangle {
                Layout.preferredWidth: Math.round(78 * root.contentScale)
                Layout.preferredHeight: Math.round(32 * root.contentScale)
                radius: Math.round(16 * root.contentScale)
                color: root.statusBg(alertCard.row.status)
                Text { anchors.centerIn: parent; text: alertCard.row.status; color: root.statusFg(alertCard.row.status); font.pixelSize: root.smallFont; font.bold: true }
            }
        }
    }

    component NoticeIcon: Item {
        id: notice
        property int count: 0
        Layout.preferredWidth: Math.round(40 * root.contentScale)
        Layout.preferredHeight: Math.round(40 * root.contentScale)
        BellIcon { anchors.centerIn: parent; width: Math.round(30 * root.contentScale); height: width }
        Rectangle {
            width: Math.round(21 * root.contentScale)
            height: Math.round(21 * root.contentScale)
            radius: width / 2
            color: "#ef4444"
            anchors.right: parent.right
            anchors.top: parent.top
            Text { anchors.centerIn: parent; text: String(notice.count); color: "#ffffff"; font.pixelSize: Math.max(12, root.smallFont - 2); font.bold: true }
        }
    }

    component BellIcon: Canvas {
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = "#334155"
            ctx.lineWidth = 2
            ctx.lineCap = "round"
            ctx.lineJoin = "round"
            ctx.beginPath()
            ctx.moveTo(width * 0.28, height * 0.70)
            ctx.lineTo(width * 0.72, height * 0.70)
            ctx.quadraticCurveTo(width * 0.62, height * 0.62, width * 0.62, height * 0.42)
            ctx.quadraticCurveTo(width * 0.62, height * 0.23, width * 0.50, height * 0.23)
            ctx.quadraticCurveTo(width * 0.38, height * 0.23, width * 0.38, height * 0.42)
            ctx.quadraticCurveTo(width * 0.38, height * 0.62, width * 0.28, height * 0.70)
            ctx.stroke()
            ctx.beginPath()
            ctx.moveTo(width * 0.44, height * 0.80)
            ctx.quadraticCurveTo(width * 0.50, height * 0.87, width * 0.56, height * 0.80)
            ctx.stroke()
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component RecentExamTable: Rectangle {
        id: recentTable
        property var tableWeights: [1.35, 1.12, 0.78, 1.36, 0.78, 0.82]
        property real contentMinWidth: {
            var total = 0
            for (var i = 0; i < tableWeights.length; ++i) {
                total += Number(tableWeights[i])
            }
            return Math.max(width, Math.round(total * (root.narrowShell ? 82 : 94)) + 24)
        }
        color: "transparent"
        Flickable {
            id: recentFlick
            anchors.fill: parent
            contentWidth: recentTable.contentMinWidth
            contentHeight: recentColumn.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            ScrollBar.horizontal: ScrollBar { policy: recentFlick.contentWidth > recentFlick.width ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
            HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
            ColumnLayout {
                id: recentColumn
                width: recentFlick.contentWidth
                spacing: 0
                TableHeader {
                    values: ["考试名称", "科目", "创建人", "考试时间", "状态", "参考人数"]
                    weights: recentTable.tableWeights
                }
                Repeater {
                    model: root.recentExams
                    delegate: TableRow {
                        values: [modelData.name, modelData.subject, modelData.owner, modelData.time, modelData.status, modelData.count]
                        weights: recentTable.tableWeights
                        statusIndex: 4
                    }
                }
            }
        }
    }

    component TableHeader: Rectangle {
        id: tableHeader
        property var values: []
        property var weights: []
        Layout.fillWidth: true
        Layout.preferredHeight: root.tableHeaderHeight
        radius: root.cardRadius
        color: "#f7f9fc"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Math.round(14 * root.contentScale)
            anchors.rightMargin: Math.round(14 * root.contentScale)
            Repeater {
                model: values
                delegate: Text {
                    Layout.fillWidth: tableHeader.weights.length === 0
                    Layout.preferredWidth: tableHeader.weights.length > index ? tableHeader.weights[index] * (root.narrowShell ? 112 : 142) * root.contentScale : Math.round(124 * root.contentScale)
                    Layout.minimumWidth: tableHeader.weights.length > index ? tableHeader.weights[index] * 96 * root.contentScale : Math.round(98 * root.contentScale)
                    text: modelData
                    color: "#5b6777"
                    font.pixelSize: root.tableHeaderFont
                    font.bold: true
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    component TableRow: Rectangle {
        id: tableRow
        property var values: []
        property var weights: []
        property int statusIndex: -1
        Layout.fillWidth: true
        Layout.preferredHeight: root.tableRowHeight
        color: "#ffffff"
        border.color: "#eef2f7"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Math.round(14 * root.contentScale)
            anchors.rightMargin: Math.round(14 * root.contentScale)
            Repeater {
                model: values
                delegate: Rectangle {
                    Layout.fillWidth: tableRow.weights.length === 0
                    Layout.preferredWidth: tableRow.weights.length > index ? tableRow.weights[index] * (root.narrowShell ? 112 : 142) * root.contentScale : Math.round(124 * root.contentScale)
                    Layout.minimumWidth: tableRow.weights.length > index ? tableRow.weights[index] * 96 * root.contentScale : Math.round(98 * root.contentScale)
                    height: Math.round(38 * root.contentScale)
                    color: "transparent"
                    Rectangle {
                        visible: index === statusIndex
                        anchors.centerIn: parent
                        width: Math.max(Math.round(58 * root.contentScale), statusText.implicitWidth + Math.round(18 * root.contentScale))
                        height: Math.round(32 * root.contentScale)
                        radius: root.cardRadius
                        color: root.statusBg(modelData)
                        Text { id: statusText; anchors.centerIn: parent; text: modelData; color: root.statusFg(modelData); font.pixelSize: root.smallFont; font.bold: true }
                    }
                    Text {
                        visible: index !== statusIndex
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        text: modelData
                        color: "#111827"
                        font.pixelSize: root.tableCellFont
                        font.bold: index === 0
                        elide: Text.ElideRight
                    }
                }
            }
        }
    }

    component AlertTable: Rectangle {
        id: alertTable
        property real contentMinWidth: Math.max(width, Math.round((root.narrowShell ? 620 : 760) * root.contentScale))
        color: "transparent"
        Flickable {
            id: alertFlick
            anchors.fill: parent
            contentWidth: alertTable.contentMinWidth
            contentHeight: alertColumn.implicitHeight
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            ScrollBar.horizontal: ScrollBar { policy: alertFlick.contentWidth > alertFlick.width ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
            HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
            ColumnLayout {
                id: alertColumn
                width: alertFlick.contentWidth
                spacing: 0
                TableHeader {
                    values: ["预警类型", "预警内容", "预警时间", "处理状态", "操作"]
                    weights: [1.05, 2.2, 1.45, 0.95, 0.82]
                }
                Repeater {
                    model: root.alerts
                    delegate: AlertRow { row: modelData }
                }
            }
        }
    }

    component AlertRow: Rectangle {
        id: alertRow
        property var row: ({})
        Layout.fillWidth: true
        Layout.preferredHeight: Math.round(42 * root.contentScale)
        color: "#ffffff"
        border.color: "#eef2f7"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Math.round(14 * root.contentScale)
            anchors.rightMargin: Math.round(14 * root.contentScale)
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: Math.round(32 * root.contentScale)
                color: "transparent"
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.min(parent.width, alertTypeText.implicitWidth + Math.round(20 * root.contentScale))
                    height: Math.round(28 * root.contentScale)
                    radius: Math.round(7 * root.contentScale)
                    color: alertRow.row.type.indexOf("高并发") >= 0 ? "#fee2e2" : (alertRow.row.type.indexOf("存储") >= 0 ? "#ffedd5" : "#dbeafe")
                    Text {
                        id: alertTypeText
                        anchors.centerIn: parent
                        text: alertRow.row.type
                        color: alertRow.row.type.indexOf("高并发") >= 0 ? "#ef4444" : (alertRow.row.type.indexOf("存储") >= 0 ? "#f59e0b" : "#2563eb")
                        font.pixelSize: root.smallFont
                        font.bold: true
                    }
                }
            }
            Text { Layout.fillWidth: true; text: row.content; color: "#111827"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
            Text { Layout.fillWidth: true; text: row.time; color: "#475569"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: Math.round(32 * root.contentScale)
                color: "transparent"
                Rectangle {
                    anchors.centerIn: parent
                    width: statusLabel.implicitWidth + Math.round(20 * root.contentScale)
                    height: Math.round(28 * root.contentScale)
                    radius: Math.round(7 * root.contentScale)
                    color: alertRow.row.status === "未处理" ? "#fee2e2" : "#ffedd5"
                    Text {
                        id: statusLabel
                        anchors.centerIn: parent
                        text: alertRow.row.status
                        color: alertRow.row.status === "未处理" ? "#ef4444" : "#f59e0b"
                        font.pixelSize: root.smallFont
                        font.bold: true
                    }
                }
            }
            Text { Layout.fillWidth: true; text: row.action; color: "#2563eb"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
        }
    }

    component SystemInfoPanel: ColumnLayout {
        spacing: Math.round(16 * root.contentScale)
        InfoRow { label: "系统版本:"; value: "v2.1.0" }
        InfoRow { label: "服务器时间:"; value: "2024-05-20 15:30:45" }
        InfoRow { label: "系统环境:"; value: "Linux / Nginx / MySQL" }
        UsageRow { label: "存储空间:"; value: "256GB / 500GB"; percent: 51; colorValue: "#2563eb" }
        UsageRow { label: "内存使用:"; value: "4.2GB / 8GB"; percent: 52; colorValue: "#94a3b8" }
        UsageRow { label: "CPU使用率:"; value: "32%"; percent: 32; colorValue: "#22c55e" }
    }

    component InfoRow: RowLayout {
        property string label: ""
        property string value: ""
        Layout.fillWidth: true
        Text { text: label; color: "#475569"; font.pixelSize: root.bodyFont; Layout.preferredWidth: Math.round(104 * root.contentScale) }
        Text { Layout.fillWidth: true; text: value; color: "#1f2937"; font.pixelSize: root.bodyFont; elide: Text.ElideRight }
    }

    component UsageRow: ColumnLayout {
        property string label: ""
        property string value: ""
        property int percent: 0
        property color colorValue: "#2563eb"
        Layout.fillWidth: true
        spacing: Math.round(8 * root.contentScale)
        RowLayout {
            Layout.fillWidth: true
            Text { text: label; color: "#475569"; font.pixelSize: root.bodyFont; Layout.preferredWidth: Math.round(104 * root.contentScale) }
            Text { Layout.fillWidth: true; text: value + "    (" + percent + "%)"; color: "#1f2937"; font.pixelSize: root.bodyFont; elide: Text.ElideRight }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: Math.round(7 * root.contentScale)
            radius: Math.round(4 * root.contentScale)
            color: "#e5edf6"
            Rectangle { width: parent.width * percent / 100; height: parent.height; radius: Math.round(4 * root.contentScale); color: colorValue }
        }
    }

    component OperationLogPanel: ColumnLayout {
        spacing: Math.round(10 * root.contentScale)
        Repeater {
            model: root.logs
            delegate: RowLayout {
                Layout.fillWidth: true
                spacing: Math.round(8 * root.contentScale)
                Rectangle { Layout.preferredWidth: Math.round(8 * root.contentScale); Layout.preferredHeight: Math.round(8 * root.contentScale); radius: Math.round(4 * root.contentScale); color: "#cbd5e1" }
                Text { Layout.fillWidth: true; text: modelData.text; color: "#475569"; font.pixelSize: root.bodyFont; elide: Text.ElideRight }
                Text { text: modelData.time; color: "#64748b"; font.pixelSize: root.smallFont }
            }
        }
    }

    component LineChart: Item {
        id: chart
        property var people: []
        property var exams: []
        property var labels: []
        property int hoverIndex: -1
        property string hoverSeries: ""
        property real hoverValue: 0
        property real hoverX: 0
        property real hoverY: 0
        readonly property real chartLeft: 50
        readonly property real chartRight: 24
        readonly property real chartTop: 34
        readonly property real chartBottom: 42

        function axisMax() {
            var maxValue = 0
            for (var i = 0; i < people.length; ++i) {
                maxValue = Math.max(maxValue, Number(people[i]))
            }
            for (var j = 0; j < exams.length; ++j) {
                maxValue = Math.max(maxValue, Number(exams[j]))
            }
            return Math.max(1000, Math.ceil(maxValue / 100) * 100)
        }

        function plotX(index, total) {
            var count = Math.max(2, total)
            return chartLeft + (width - chartLeft - chartRight) / (count - 1) * index
        }

        function plotY(value) {
            var maxValue = axisMax()
            var h = height - chartTop - chartBottom
            return chartTop + h - h * Number(value) / maxValue
        }

        function choosePoint(mx, my) {
            var bestDistance = 9999
            var bestIndex = -1
            var bestSeries = ""
            var bestValue = 0
            var bestX = 0
            var bestY = 0
            function scan(values, name) {
                for (var i = 0; i < values.length; ++i) {
                    var px = chart.plotX(i, values.length)
                    var py = chart.plotY(values[i])
                    var distance = Math.sqrt(Math.pow(mx - px, 2) + Math.pow(my - py, 2))
                    if (distance < bestDistance) {
                        bestDistance = distance
                        bestIndex = i
                        bestSeries = name
                        bestValue = values[i]
                        bestX = px
                        bestY = py
                    }
                }
            }
            scan(people, "参考人数")
            scan(exams, "考试次数")
            if (bestDistance <= 18) {
                hoverIndex = bestIndex
                hoverSeries = bestSeries
                hoverValue = bestValue
                hoverX = bestX
                hoverY = bestY
            } else {
                hoverIndex = -1
                hoverSeries = ""
            }
            chartCanvas.requestPaint()
        }

        onWidthChanged: chartCanvas.requestPaint()
        onHeightChanged: chartCanvas.requestPaint()
        onPeopleChanged: chartCanvas.requestPaint()
        onExamsChanged: chartCanvas.requestPaint()
        onLabelsChanged: chartCanvas.requestPaint()

        Canvas {
            id: chartCanvas
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                var left = chart.chartLeft
                var right = chart.chartRight
                var top = chart.chartTop
                var bottom = chart.chartBottom
                var w = width - left - right
                var h = height - top - bottom

                ctx.lineWidth = 1
                ctx.strokeStyle = "#e5eaf2"
                for (var i = 0; i <= 5; ++i) {
                    var y = top + h / 5 * i
                    ctx.beginPath()
                    ctx.moveTo(left, y)
                    ctx.lineTo(left + w, y)
                    ctx.stroke()
                }

                function draw(values, color) {
                    if (values.length === 0) {
                        return
                    }
                    ctx.strokeStyle = color
                    ctx.fillStyle = color
                    ctx.lineWidth = 3
                    ctx.lineJoin = "round"
                    ctx.lineCap = "round"
                    ctx.beginPath()
                    for (var p = 0; p < values.length; ++p) {
                        var x = chart.plotX(p, values.length)
                        var yy = chart.plotY(values[p])
                        if (p === 0) {
                            ctx.moveTo(x, yy)
                        } else {
                            ctx.lineTo(x, yy)
                        }
                    }
                    ctx.stroke()
                    for (var q = 0; q < values.length; ++q) {
                        var px = chart.plotX(q, values.length)
                        var py = chart.plotY(values[q])
                        ctx.beginPath()
                        ctx.arc(px, py, chart.hoverIndex === q ? 5.5 : 4, 0, Math.PI * 2)
                        ctx.fill()
                        ctx.lineWidth = 2
                        ctx.strokeStyle = "#ffffff"
                        ctx.stroke()
                        ctx.strokeStyle = color
                    }
                }

                draw(chart.people, "#3b82f6")
                draw(chart.exams, "#22c55e")

                if (chart.hoverIndex >= 0) {
                    ctx.strokeStyle = "#94a3b8"
                    ctx.lineWidth = 1
                    ctx.setLineDash([4, 4])
                    ctx.beginPath()
                    ctx.moveTo(chart.hoverX, top)
                    ctx.lineTo(chart.hoverX, top + h)
                    ctx.stroke()
                    ctx.setLineDash([])
                }
            }
        }

        Repeater {
            model: 6
            delegate: Text {
                x: 6
                y: chart.chartTop + (chart.height - chart.chartTop - chart.chartBottom) / 5 * index - height / 2
                text: String(Math.round(chart.axisMax() - chart.axisMax() / 5 * index))
                color: "#64748b"
                font.pixelSize: Math.max(12, root.smallFont - 1)
            }
        }

        Repeater {
            model: chart.labels
            delegate: Text {
                x: chart.plotX(index, chart.labels.length) - width / 2
                y: chart.height - 24
                text: modelData
                color: "#64748b"
                font.pixelSize: Math.max(12, root.smallFont - 1)
            }
        }

        Row {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 18
            Text { text: "● 参考人数"; color: "#3b82f6"; font.pixelSize: root.smallFont; font.bold: true }
            Text { text: "● 考试次数"; color: "#22c55e"; font.pixelSize: root.smallFont; font.bold: true }
        }

        Rectangle {
            id: chartTooltip
            visible: chart.hoverIndex >= 0
            width: Math.round(178 * root.contentScale)
            height: Math.round(96 * root.contentScale)
            x: Math.max(Math.round(8 * root.contentScale), Math.min(chart.hoverX - width / 2, chart.width - width - Math.round(8 * root.contentScale)))
            y: Math.max(Math.round(6 * root.contentScale), chart.hoverY - height - Math.round(16 * root.contentScale))
            radius: root.cardRadius
            color: "#111827"
            opacity: visible ? 0.96 : 0
            z: 10
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Math.round(12 * root.contentScale)
                spacing: Math.round(4 * root.contentScale)
                Text { Layout.fillWidth: true; text: chart.labels[chart.hoverIndex] || ""; color: "#dbeafe"; font.pixelSize: root.smallFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: chart.hoverSeries; color: "#ffffff"; font.pixelSize: root.bodyFont; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: "具体数据：" + chart.hoverValue; color: "#cbd5e1"; font.pixelSize: root.smallFont; elide: Text.ElideRight }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
            onPositionChanged: chart.choosePoint(mouseX, mouseY)
            onExited: {
                chart.hoverIndex = -1
                chart.hoverSeries = ""
                chartCanvas.requestPaint()
            }
        }
    }

    component DonutChart: Canvas {
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var cx = width * 0.34
            var cy = height * 0.54
            var r = Math.min(width * 0.40, height * 0.41)
            var vals = [0.30, 0.50, 0.20]
            var colors = ["#377cf6", "#76cc72", "#f7be31"]
            var start = -Math.PI / 2
            for (var i = 0; i < vals.length; ++i) {
                ctx.beginPath()
                ctx.moveTo(cx, cy)
                ctx.arc(cx, cy, r, start, start + Math.PI * 2 * vals[i])
                ctx.closePath()
                ctx.fillStyle = colors[i]
                ctx.fill()
                start += Math.PI * 2 * vals[i]
            }
            ctx.beginPath()
            ctx.arc(cx, cy, r * 0.50, 0, Math.PI * 2)
            ctx.fillStyle = "#ffffff"
            ctx.fill()
            var names = ["简单", "中等", "困难"]
            for (var j = 0; j < names.length; ++j) {
                var y = cy - 44 * root.contentScale + j * 44 * root.contentScale
                ctx.fillStyle = colors[j]
                ctx.fillRect(width * 0.66, y - 8 * root.contentScale, 16 * root.contentScale, 16 * root.contentScale)
                ctx.fillStyle = "#1f2937"
                ctx.font = root.bodyFont + "px sans-serif"
                ctx.fillText(names[j], width * 0.66 + 28 * root.contentScale, y + 6 * root.contentScale)
                ctx.fillText(String(vals[j] * 100) + "%", width * 0.66 + 106 * root.contentScale, y + 6 * root.contentScale)
            }
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    component WindowControls: RowLayout {
        property int buttonSize: root.width < 760 ? 34 : Math.round(48 * root.contentScale)
        property int controlGap: root.width < 760 ? 5 : Math.round(6 * root.contentScale)
        width: buttonSize * 3 + controlGap * 2
        height: root.width < 760 ? 38 : Math.round(50 * root.contentScale)
        spacing: controlGap
        WindowButton { symbol: "-"; onClicked: adminApi.minimizeWindow() }
        WindowButton { symbol: "□"; onClicked: adminApi.toggleMaximizeWindow() }
        WindowButton { symbol: "X"; danger: true; onClicked: adminApi.closeWindow() }
    }

    component WindowButton: Item {
        id: control
        property string symbol: ""
        property bool danger: false
        signal clicked()
        Layout.preferredWidth: root.width < 760 ? 34 : Math.round(48 * root.contentScale)
        Layout.minimumWidth: root.width < 760 ? 34 : Math.round(48 * root.contentScale)
        Layout.preferredHeight: root.width < 760 ? 34 : Math.round(48 * root.contentScale)
        Layout.minimumHeight: root.width < 760 ? 34 : Math.round(48 * root.contentScale)
        Rectangle {
            anchors.fill: parent
            radius: root.width < 760 ? 10 : root.cardRadius
            color: mouse.containsMouse ? (control.danger ? "#fef2f2" : "#f1f5f9") : "transparent"
        }
        Text { anchors.centerIn: parent; text: control.symbol; color: control.danger ? "#ef4444" : "#334155"; font.pixelSize: root.width < 760 ? 18 : root.navFont; font.bold: true }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: control.clicked() }
    }
}
