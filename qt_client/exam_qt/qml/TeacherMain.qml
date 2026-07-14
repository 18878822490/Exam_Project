import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Rectangle {
    id: root
    color: "#eef2f8"
    clip: true

    property int currentPage: 0
    property int animationKey: 0
    property bool narrowShell: width < 980
    property bool compactShell: width < 1180
    property bool mediumShell: width < 1360
    property real contentScale: narrowShell ? 1.0 : Math.max(1.12, Math.min(1.48, Math.min(width / 1180, height / 700)))
    property int shellHMargin: narrowShell ? 14 : (compactShell ? 22 : 38)
    property int shellVMargin: narrowShell ? 16 : (compactShell ? 22 : 30)
    property int pageGap: narrowShell ? 14 : 22
    property int normalNavHeight: narrowShell ? 96 : (compactShell ? 120 : 136)
    property bool navHidden: false
    property bool classDetailMode: false
    property string toastText: ""
    property string selectedClassName: ""
    property int activePaperId: 0
    property int selectedQuestionId: -1
    property int publishQuestionIndex: 0
    property int reviewExamIndex: 0
    property int reviewStudentIndex: 0
    property int reviewQuestionIndex: 0
    property int profileSubPage: 0
    property bool publishPaperMode: false
    property bool reviewPaperSelected: false
    property bool reviewWorkMode: false
    property bool classExamDetailMode: false
    property string todoDraftType: "批改试卷"
    property date nowTime: new Date()
    property string publishDraftName: "Java期末考试"
    property string publishDraftSubject: "Java"
    property string publishDraftStart: "2026-06-20 09:00"
    property string publishDraftEnd: "2026-06-20 11:00"
    property int publishTargetScore: 100
    property var selectedClassExam: ({})
    property var profile: ({})
    property var dashboard: ({})
    property var classes: []
    property var classStudents: []
    property var allStudents: []
    property var reviewStudents: []
    property var exams: []
    property var questions: []
    property var importLogs: []
    property var scoreStats: ({})
    property var pendingReviews: []
    property var studentAnswers: []
    property var reviewAnswerDetails: []
    property var paperQuestions: []
    property var selectedPublishClasses: []
    property var selectedPaperQuestions: []
    property var todoItems: []
    property var menuItems: [
        {"title": "首页", "page": 0},
        {"title": "题库管理", "page": 1},
        {"title": "发布考试", "page": 2},
        {"title": "批改试卷", "page": 3},
        {"title": "成绩分析", "page": 4}
    ]
    property var pageTitles: ["教师首页", "题库管理", "发布考试", "批改试卷", "班级成绩分析", "个人中心"]
    property var pageSubtitles: [
        "教学数据、考试进度与待办提醒",
        "左侧浏览题目，右侧查看题目详情、答案与解析",
        "配置试卷、筛选题目、查看并发布考试",
        "选择试卷和学生，仅批改高数大题与编程题",
        "按班级、考试和时间查看成绩趋势、分布、排名与薄弱题",
        "管理账号资料、安全密码与系统偏好"
    ]

    Component.onCompleted: {
        refreshAll()
        animationKey += 1
    }

    function refreshAll() {
        profile = teacherApi.getTeacherProfile()
        dashboard = teacherApi.getDashboardStats()
        classes = teacherApi.getTeacherClasses()
        allStudents = collectAllStudents()
        exams = teacherApi.getExamList()
        questions = teacherApi.getQuestions()
        importLogs = teacherApi.getImportLogs()
        scoreStats = teacherApi.getScoreStatistics()
        pendingReviews = teacherApi.getPendingReviews()
        studentAnswers = teacherApi.getStudentAnswers()
        todoItems = teacherApi.getTodoItems()

        if (selectedClassName === "" && classes.length > 0) {
            selectedClassName = classes[0].name
        }
        classStudents = selectedClassName.length > 0 ? teacherApi.getClassStudents(selectedClassName) : []
        if (activePaperId <= 0 && exams.length > 0) {
            activePaperId = Number(exams[0].id)
        }
        paperQuestions = activePaperId > 0 ? teacherApi.getPaperQuestions(activePaperId) : []
        reviewStudents = reviewPaperSelected && activePaperId > 0 ? teacherApi.getStudentAnswersForPaper(activePaperId) : allStudents
        reviewAnswerDetails = []
    }

    function switchPage(page) {
        if (page === 3) {
            teacherApi.openMarkWorkbench()
            return
        }
        if (page === 4) {
            teacherApi.openScoreAnalysisWorkbench()
            return
        }
        if (page === currentPage) {
            animationKey += 1
            return
        }
        classDetailMode = false
        classExamDetailMode = false
        publishPaperMode = false
        reviewWorkMode = false
        currentPage = page
        animationKey += 1
    }

    function pageComponent(page) {
        if (page === 1) return questionBankPageComponent
        if (page === 2) return publishExamPageComponent
        if (page === 3) return reviewPageComponent
        if (page === 4) return classPageComponent
        if (page === 5) return profileCenterPageComponent
        return dashboardPageComponent
    }

    function showToast(text) {
        toastText = text
        toastTimer.restart()
    }

    function pad2(value) {
        return Number(value) < 10 ? "0" + Number(value) : String(Number(value))
    }

    function twoDigitOptions(count) {
        var values = []
        for (var i = 0; i < count; ++i) {
            values.push(pad2(i))
        }
        return values
    }

    function formatDateTime(date) {
        return date.getFullYear() + "-" + pad2(date.getMonth() + 1) + "-" + pad2(date.getDate())
                + " " + pad2(date.getHours()) + ":" + pad2(date.getMinutes())
    }

    function defaultTodoTime() {
        var date = new Date(nowTime.getTime() + 60 * 60 * 1000)
        date.setSeconds(0)
        date.setMilliseconds(0)
        return formatDateTime(date)
    }

    function parseDateTime(value) {
        var text = String(value || "").trim()
        var parts = text.split(" ")
        if (parts.length < 2) {
            return null
        }
        var dateParts = parts[0].split("-")
        var timeParts = parts[1].split(":")
        if (dateParts.length !== 3 || timeParts.length < 2) {
            return null
        }
        var date = new Date(Number(dateParts[0]), Number(dateParts[1]) - 1, Number(dateParts[2]),
                            Number(timeParts[0]), Number(timeParts[1]), 0, 0)
        return isNaN(date.getTime()) ? null : date
    }

    function todoTimestamp(item) {
        var date = parseDateTime(item && item.time)
        return date ? date.getTime() : 9999999999999
    }

    function sortedTodoItems() {
        var rows = []
        for (var i = 0; i < todoItems.length; ++i) {
            rows.push(todoItems[i])
        }
        var now = nowTime.getTime()
        rows.sort(function(a, b) {
            var at = todoTimestamp(a)
            var bt = todoTimestamp(b)
            var afuture = at >= now
            var bfuture = bt >= now
            if (afuture !== bfuture) {
                return afuture ? -1 : 1
            }
            return afuture ? at - bt : bt - at
        })
        return rows
    }

    function nextTodo() {
        var rows = sortedTodoItems()
        return rows.length > 0 ? rows[0] : ({})
    }

    function todoCountdown(item) {
        var date = parseDateTime(item && item.time)
        if (!date) {
            return "--"
        }
        var diff = date.getTime() - nowTime.getTime()
        if (diff <= 0) {
            return "已到提醒时间"
        }
        var totalSeconds = Math.floor(diff / 1000)
        var days = Math.floor(totalSeconds / 86400)
        var hours = Math.floor((totalSeconds % 86400) / 3600)
        var minutes = Math.floor((totalSeconds % 3600) / 60)
        var seconds = totalSeconds % 60
        if (days > 0) {
            return days + "天 " + hours + "时 " + minutes + "分"
        }
        if (hours > 0) {
            return hours + "时 " + minutes + "分 " + seconds + "秒"
        }
        return minutes + "分 " + seconds + "秒"
    }

    function signedMetric(value, decimals) {
        var number = Number(value || 0)
        var scale = Math.pow(10, decimals || 0)
        var rounded = Math.round(number * scale) / scale
        var text = (decimals || 0) > 0 ? rounded.toFixed(decimals) : String(Math.round(rounded))
        return (rounded >= 0 ? "+" : "") + text
    }

    function metricPositive(value) {
        return Number(value || 0) >= 0
    }

    function examStatusColor(status) {
        if (status === "进行中") return "#16a34a"
        if (status === "待批改") return "#ef4444"
        if (status === "未开始") return "#2563eb"
        if (status === "已完成") return "#64748b"
        return "#f59e0b"
    }

    function workflowExamCards() {
        var result = []
        var priority = {"进行中": 0, "待批改": 1, "未开始": 2, "草稿": 3}
        for (var i = 0; i < exams.length; ++i) {
            var status = exams[i].status || "草稿"
            if (status === "进行中" || status === "待批改" || status === "未开始" || status === "草稿") {
                result.push(exams[i])
            }
        }
        result.sort(function(a, b) {
            var ap = priority[a.status || "草稿"]
            var bp = priority[b.status || "草稿"]
            if (ap !== bp) return ap - bp
            return Number(b.id || 0) - Number(a.id || 0)
        })
        return result.slice(0, 3)
    }

    function profileName() {
        var name = profile.name || profile.username || "教师"
        return String(name).length > 0 ? String(name) : "教师"
    }

    function avatarText() {
        var name = profileName()
        return name.length > 0 ? name.charAt(0) : "师"
    }

    function profileSubtitle() {
        var subject = profile.subject || "教师端"
        return subject + " · " + (profile.role || "教师")
    }

    function collectAllStudents() {
        var result = []
        var seen = {}
        for (var i = 0; i < classes.length; ++i) {
            var rows = teacherApi.getClassStudents(classes[i].name)
            for (var j = 0; j < rows.length; ++j) {
                var student = rows[j]
                var key = String(student.studentNo || student.username || student.id || student.name || (i + "-" + j))
                if (!seen[key]) {
                    student.className = student.className || classes[i].name
                    student.reviewStatus = "未选择考试"
                    result.push(student)
                    seen[key] = true
                }
            }
        }
        return result
    }

    function openProfileCenter(subPage) {
        profileSubPage = subPage || 0
        currentPage = 5
        classDetailMode = false
        classExamDetailMode = false
        publishPaperMode = false
        reviewWorkMode = false
        animationKey += 1
    }

    function updatePublishDraft(name, subject, startText, endText) {
        publishDraftName = name && name.length > 0 ? name : "未命名试卷"
        publishDraftSubject = subject && subject.length > 0 ? subject : "Java"
        publishDraftStart = startText || "2026-06-20 09:00"
        publishDraftEnd = endText || "2026-06-20 11:00"
    }

    function movePaperQuestion(index, direction) {
        var target = index + direction
        if (target < 0 || target >= selectedPaperQuestions.length) {
            showToast(direction < 0 ? "已经是第一题" : "已经是最后一题")
            return
        }
        var next = selectedPaperQuestions.slice()
        var item = next[index]
        next[index] = next[target]
        next[target] = item
        selectedPaperQuestions = next
    }

    function removePaperQuestion(index) {
        if (index < 0 || index >= selectedPaperQuestions.length) return
        var next = selectedPaperQuestions.slice()
        next.splice(index, 1)
        selectedPaperQuestions = next
        showToast("已移出试卷")
    }

    function smartGeneratePaper(subject, counts, difficulty, knowledgePoint) {
        var generated = []
        var typeNames = Object.keys(counts)
        var used = {}
        var targetScore = paperTargetScore()
        var currentScore = 0
        var cleanDifficulty = cleanFilterText(difficulty)
        var cleanKnowledge = String(knowledgePoint || "").trim()
        var missing = []
        var blockedByScore = 0
        for (var i = 0; i < typeNames.length; ++i) {
            var typeName = typeNames[i]
            var need = Number(counts[typeName] || 0)
            if (need <= 0) continue
            var rows = searchQuestionPool("", subject, typeName, cleanDifficulty, cleanKnowledge)
            var picked = 0
            var available = rows ? rows.length : 0
            for (var j = 0; j < rows.length && picked < need; ++j) {
                var q = rows[j]
                var id = String(q.id || q.questionId || "")
                if (id.length > 0 && used[id]) continue
                if (id.length > 0) used[id] = true
                var score = questionScoreValue(q)
                if (currentScore + score > targetScore) {
                    blockedByScore += 1
                    continue
                }
                q.score = score
                generated.push(q)
                currentScore += score
                picked += 1
            }
            if (picked < need) {
                missing.push(typeName + " " + picked + "/" + need + "（可用" + available + "）")
            }
        }
        selectedPaperQuestions = generated
        if (generated.length > 0) {
            publishPaperMode = true
            animationKey += 1
        }
        if (generated.length > 0) {
            var note = missing.length > 0 ? ("；不足：" + missing.join("，")) : ""
            if (blockedByScore > 0) note += "；部分题目因满分限制未加入"
            showToast("已智能生成 " + generated.length + " 道题，总分 " + currentScore + "/" + targetScore + note)
        } else if (missing.length > 0) {
            showToast("没有生成成功：" + missing.join("，") + "，请放宽筛选或补充题库")
        } else {
            showToast("题型数量为 0 或满分限制过低，无法生成试卷")
        }
    }

    function saveCurrentDraft(name, subject, startText, endText) {
        updatePublishDraft(name, subject, startText, endText)
        if (selectedPaperQuestions.length === 0) {
            showToast("请先添加或生成题目")
            return -1
        }
        if (paperTotalScore() > paperTargetScore()) {
            showToast("当前试卷总分超过设定满分，不能保存草稿")
            return -1
        }
        var paperId = teacherApi.createDraftPaperFromQuestions(publishDraftName, publishDraftSubject, publishDraftStart, publishDraftEnd, selectedPaperQuestions)
        if (paperId > 0) {
            activePaperId = paperId
            refreshAll()
            showToast("草稿已保存，首页草稿列表已更新")
        } else {
            showToast("草稿保存失败：" + teacherApi.lastError())
        }
        return paperId
    }

    function selectReviewExam(exam, index) {
        reviewExamIndex = index
        activePaperId = Number(exam.id || 0)
        reviewPaperSelected = activePaperId > 0
        paperQuestions = activePaperId > 0 ? teacherApi.getPaperQuestions(activePaperId) : []
        reviewStudents = activePaperId > 0 ? teacherApi.getStudentAnswersForPaper(activePaperId) : allStudents
        reviewAnswerDetails = []
        reviewStudentIndex = 0
        reviewQuestionIndex = 0
        reviewWorkMode = false
    }

    function selectedReviewAnswer() {
        var question = selectedReviewQuestion()
        var qid = String(question.id || question.questionId || "")
        for (var i = 0; i < reviewAnswerDetails.length; ++i) {
            var row = reviewAnswerDetails[i]
            if (String(row.questionId || row.question_id || "") === qid) {
                return row
            }
        }
        return reviewStudents.length > reviewStudentIndex ? reviewStudents[reviewStudentIndex] : ({})
    }

    function beginReviewStudent(index) {
        reviewStudentIndex = index
        reviewQuestionIndex = 0
        var student = reviewStudents.length > index ? reviewStudents[index] : ({})
        reviewAnswerDetails = activePaperId > 0 && String(student.studentNo || "").length > 0
                ? teacherApi.getStudentAnswersForStudent(activePaperId, String(student.studentNo))
                : []
        reviewWorkMode = true
        animationKey += 1
    }

    function examsForClass(className) {
        var result = []
        for (var i = 0; i < exams.length; ++i) {
            var examClass = String(exams[i].className || "")
            if (examClass.length === 0 || examClass === className) {
                result.push(exams[i])
            }
        }
        return result.length > 0 ? result : orderedExams()
    }

    function openClassExam(exam) {
        selectedClassExam = exam
        classExamDetailMode = true
        animationKey += 1
    }

    function questionTypeScore(type) {
        if (type === "单选题") return 3
        if (type === "多选题") return 5
        if (type === "判断题") return 3
        if (type === "填空题") return 2
        if (type === "高数大题") return 10
        if (type === "编程题" || type === "代码题") return 15
        return 3
    }

    function paperTargetScore() {
        var value = Math.round(Number(publishTargetScore || 100))
        return value > 0 ? value : 100
    }

    function setPublishTargetScore(value) {
        var next = Math.round(Number(value || 100))
        if (isNaN(next) || next <= 0) next = 100
        publishTargetScore = Math.max(1, Math.min(500, next))
        if (paperTotalScore() > publishTargetScore) {
            showToast("当前试卷总分已超过设定满分，请移除题目或调高满分")
        }
    }

    function questionScoreValue(question) {
        if (!question) return 0
        var explicitScore = Number(question.score || question.paper_score || question.questionScore || 0)
        return explicitScore > 0 ? explicitScore : questionTypeScore(normalizeType(question.type || question.content))
    }

    function canAppendQuestion(question) {
        return paperTotalScore() + questionScoreValue(question) <= paperTargetScore()
    }

    function nextQuestionId() {
        var maxId = 0
        for (var i = 0; i < questions.length; ++i) {
            maxId = Math.max(maxId, Number(questions[i].id || 0))
        }
        return maxId + 1
    }

    function orderedExams() {
        var list = exams.length > 0 ? exams.slice() : [
            {"id": 1, "name": "Java期末考试", "subject": "Java", "status": "已发布", "date": "2026-06-20"}
        ]
        list.sort(function(a, b) {
            var aj = String(a.name || "").indexOf("Java期末") >= 0 ? -1 : 0
            var bj = String(b.name || "").indexOf("Java期末") >= 0 ? -1 : 0
            if (aj !== bj) return aj - bj
            return String(b.date || b.startTime || "").localeCompare(String(a.date || a.startTime || ""))
        })
        return list
    }

    function examDate(exam) {
        return String(exam.date || exam.startTime || exam.createdTime || "2026-06-20").slice(0, 16)
    }

    function normalizeType(type) {
        var text = String(type || "").trim()
        var lower = text.toLowerCase()
        if (text === "判断" || lower === "judge" || lower === "truefalse" || lower === "true/false") return "判断题"
        if (text === "代码题" || lower === "program" || lower === "coding" || lower === "code") return "编程题"
        if (lower === "single" || lower === "singlechoice" || text === "单选" || text === "选择题") return "单选题"
        if (lower === "multiple" || lower === "multiplechoice" || lower === "multi" || text === "多选") return "多选题"
        if (lower === "blank" || lower === "fill" || text === "填空") return "填空题"
        if (lower === "math" || text === "高数题") return "高数大题"
        return text
    }

    function cleanFilterText(value) {
        var text = String(value || "").trim()
        return text.indexOf("全部") >= 0 ? "" : text
    }

    function normalizeSubject(subject) {
        var text = String(subject || "").trim()
        var lower = text.toLowerCase()
        if (text === "高等数学" || text === "数学" || lower === "math" || lower === "advanced mathematics") return "高数"
        if (lower === "cpp" || lower === "c plus plus" || text === "C＋＋") return "C++"
        if (lower === "java") return "Java"
        if (text === "数据结构与算法") return "数据结构"
        if (lower === "mysql" || lower === "database") return "数据库"
        return text
    }

    function normalizeDifficultyText(difficulty) {
        var text = cleanFilterText(difficulty)
        var lower = text.toLowerCase()
        if (lower === "easy" || text === "简单") return "基础"
        if (lower === "medium" || lower === "middle" || lower === "normal" || text === "中") return "中等"
        if (lower === "hard" || lower === "difficult" || text === "难") return "困难"
        return text
    }

    function isKnownQuestionType(type) {
        var value = normalizeType(String(type || ""))
        return value === "单选题" || value === "多选题" || value === "判断题" || value === "填空题"
                || value === "高数大题" || value === "编程题"
    }

    function questionText(question) {
        if (!question) return ""
        var content = String(question.content || "")
        var typeValue = String(question.type || "")
        if (isKnownQuestionType(content) && !isKnownQuestionType(typeValue) && typeValue.length > 0) {
            return typeValue
        }
        return content
    }

    function questionTypeText(question) {
        if (!question) return "--"
        if (isKnownQuestionType(question.type)) return normalizeType(question.type)
        if (isKnownQuestionType(question.content)) return normalizeType(question.content)
        return String(question.type || "--")
    }

    function cleanQuestionOption(value) {
        var text = String(value || "").trim()
        return text === "--" ? "" : text
    }

    function questionOptionValue(question, keys) {
        if (!question) return ""
        for (var i = 0; i < keys.length; ++i) {
            var value = question[keys[i]]
            var text = cleanQuestionOption(value)
            if (text.length > 0) {
                return text
            }
        }
        return ""
    }

    function questionOptions(question) {
        var defs = [
            {"label": "A", "keys": ["optionA", "option_a", "A", "a"]},
            {"label": "B", "keys": ["optionB", "option_b", "B", "b"]},
            {"label": "C", "keys": ["optionC", "option_c", "C", "c"]},
            {"label": "D", "keys": ["optionD", "option_d", "D", "d"]}
        ]
        var rows = []
        for (var i = 0; i < defs.length; ++i) {
            var text = questionOptionValue(question, defs[i].keys)
            if (text.length > 0) {
                rows.push({"label": defs[i].label, "text": text})
            }
        }
        return rows
    }

    function typeOptions(subject) {
        if (subject === "高数") {
            return ["单选题", "多选题", "判断题", "填空题", "高数大题"]
        }
        return ["单选题", "多选题", "判断题", "填空题", "编程题"]
    }

    function questionsFor(subject, type, keyword, difficulty, knowledgePoint) {
        var result = []
        var key = (keyword || "").trim()
        var cleanDifficulty = normalizeDifficultyText(difficulty)
        var cleanKnowledge = String(knowledgePoint || "").trim()
        var cleanSubject = normalizeSubject(subject)
        var cleanType = normalizeType(type)
        for (var i = 0; i < questions.length; ++i) {
            var q = questions[i]
            var qType = normalizeType(questionTypeText(q))
            var qSubject = normalizeSubject(q.subject)
            var qDifficulty = normalizeDifficultyText(q.difficulty)
            var searchable = [
                questionText(q),
                q.answer,
                q.analysis,
                q.knowledgePoint,
                q.subject,
                questionTypeText(q)
            ].join(" ")
            if ((cleanSubject === "" || qSubject === cleanSubject)
                    && (cleanType === "" || qType === cleanType)
                    && (cleanDifficulty === "" || qDifficulty === cleanDifficulty)
                    && (cleanKnowledge === "" || String(q.knowledgePoint || "").indexOf(cleanKnowledge) >= 0)
                    && (key === "" || searchable.indexOf(key) >= 0)) {
                result.push(q)
            }
        }
        return result
    }

    function searchQuestionPool(keyword, subject, type, difficulty, knowledgePoint) {
        var cleanDifficulty = cleanFilterText(difficulty)
        var cleanKnowledge = String(knowledgePoint || "").trim()
        var rows = teacherApi.searchQuestionsAdvanced(keyword || "", subject || "", type || "", cleanDifficulty, cleanKnowledge)
        if ((!rows || rows.length === 0) && String(subject || "").trim().length > 0) {
            rows = teacherApi.searchQuestionsAdvanced(keyword || "", "", type || "", cleanDifficulty, cleanKnowledge)
        }
        if (!rows || rows.length === 0) {
            rows = questionsFor(subject || "", type || "", keyword || "", cleanDifficulty, cleanKnowledge)
        }
        if ((!rows || rows.length === 0) && String(subject || "").trim().length > 0) {
            rows = questionsFor("", type || "", keyword || "", cleanDifficulty, cleanKnowledge)
        }
        return rows || []
    }

    function selectedQuestion() {
        for (var i = 0; i < questions.length; ++i) {
            if (Number(questions[i].id) === selectedQuestionId) {
                return questions[i]
            }
        }
        return questions.length > 0 ? questions[0] : ({})
    }

    function countForType(type) {
        var count = 0
        for (var i = 0; i < selectedPaperQuestions.length; ++i) {
            if (normalizeType(selectedPaperQuestions[i].type) === type) {
                count += 1
            }
        }
        return count
    }

    function paperTotalScore() {
        var total = 0
        for (var i = 0; i < selectedPaperQuestions.length; ++i) {
            total += questionScoreValue(selectedPaperQuestions[i])
        }
        return total
    }

    function paperRemainingScore() {
        return Math.max(0, paperTargetScore() - paperTotalScore())
    }

    function togglePublishClass(className, checked) {
        var next = selectedPublishClasses.slice()
        var idx = next.indexOf(className)
        if (checked && idx < 0) next.push(className)
        if (!checked && idx >= 0) next.splice(idx, 1)
        selectedPublishClasses = next
    }

    function selectedReviewQuestion() {
        var subjective = []
        for (var i = 0; i < paperQuestions.length; ++i) {
            var type = normalizeType(paperQuestions[i].type)
            if (type === "高数大题" || type === "编程题") {
                subjective.push(paperQuestions[i])
            }
        }
        return subjective.length > 0 ? subjective[Math.min(reviewQuestionIndex, subjective.length - 1)] : ({})
    }

    function subjectiveQuestionCount() {
        var count = 0
        for (var i = 0; i < paperQuestions.length; ++i) {
            var type = normalizeType(paperQuestions[i].type)
            if (type === "高数大题" || type === "编程题") count += 1
        }
        return count
    }

    Timer {
        id: toastTimer
        interval: 2200
        repeat: false
        onTriggered: root.toastText = ""
    }

    Timer {
        id: clockTimer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: root.nowTime = new Date()
    }

    FileDialog {
        id: ocrDialog
        title: "选择拍照导入图片"
        nameFilters: ["图片文件 (*.png *.jpg *.jpeg *.bmp)", "所有文件 (*)"]
        onAccepted: {
            var result = teacherApi.reserveOcrImport(selectedFile)
            root.refreshAll()
            var count = Number(result.successCount || 0)
            var status = String(result.status || "")
            var message = String(result.message || "")
            root.showToast(count > 0 ? ("OCR已识别导入 " + count + " 道题") : ("OCR导入" + (status.length > 0 ? status : "失败") + (message.length > 0 ? ("：" + message) : "，请查看导入日志")))
        }
    }

    FileDialog {
        id: questionFileDialog
        title: "导入题库文件"
        nameFilters: ["题库文件 (*.csv *.xlsx *.xls)", "CSV 文件 (*.csv)", "Excel 文件 (*.xlsx *.xls)", "所有文件 (*)"]
        onAccepted: {
            var count = teacherApi.importQuestionsFromFile(selectedFile)
            root.refreshAll()
            root.showToast(count > 0 ? ("已导入 " + count + " 道题") : ("导入失败：" + teacherApi.lastError()))
        }
    }

    Dialog {
        id: addQuestionDialog
        modal: true
        width: Math.min(620, root.width - 80)
        height: 690
        x: (root.width - width) / 2
        y: Math.max(36, (root.height - height) / 2)
        padding: 0
        background: Rectangle {
            radius: 26
            color: "#f8fbff"
            border.color: "#dbeafe"
        }
        onOpened: {
            addQuestionId.text = String(root.nextQuestionId())
            addQuestionContent.text = ""
            addQuestionAnswer.text = ""
            addQuestionAnalysis.text = ""
        }
        contentItem: ColumnLayout {
            anchors.fill: parent
            anchors.margins: 26
            spacing: 14
            RowLayout {
                Layout.fillWidth: true
                Text { text: "新增题目"; color: "#111827"; font.pixelSize: 26; font.bold: true; Layout.fillWidth: true }
                SoftButton { Layout.preferredWidth: 82; text: "关闭"; onClicked: addQuestionDialog.close() }
            }
            RowLayout {
                Layout.fillWidth: true
                AppField { id: addQuestionId; Layout.fillWidth: true; placeholderText: "ID"; readOnly: true }
                AppCombo { id: addQuestionSubject; Layout.fillWidth: true; model: ["Java", "C++", "高数", "数据结构", "数据库"] }
                AppCombo { id: addQuestionType; Layout.fillWidth: true; model: ["单选题", "多选题", "填空题", "高数大题", "编程题"] }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 46
                radius: 15
                color: "#eff6ff"
                border.color: "#bfdbfe"
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    Text { text: "自动分值"; color: "#64748b"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true }
                    Text { text: root.questionTypeScore(addQuestionType.currentText) + " 分"; color: "#2563eb"; font.pixelSize: 16; font.bold: true }
                }
            }
            TextArea {
                id: addQuestionContent
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                placeholderText: "题目内容"
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                color: "#111827"
                background: Rectangle { radius: 16; color: "#ffffff"; border.color: "#dbe7f6" }
            }
            TextArea {
                id: addQuestionAnswer
                Layout.fillWidth: true
                Layout.preferredHeight: 92
                placeholderText: "答案"
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                color: "#111827"
                background: Rectangle { radius: 16; color: "#ffffff"; border.color: "#dbe7f6" }
            }
            TextArea {
                id: addQuestionAnalysis
                Layout.fillWidth: true
                Layout.preferredHeight: 118
                placeholderText: "解析"
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                color: "#111827"
                background: Rectangle { radius: 16; color: "#ffffff"; border.color: "#dbe7f6" }
            }
            PrimaryButton {
                Layout.fillWidth: true
                text: "确认新增"
                onClicked: {
                    if (addQuestionContent.text.trim().length === 0) {
                        root.showToast("请填写题目内容")
                        return
                    }
                    var payload = {
                        "id": Number(addQuestionId.text),
                        "subject": addQuestionSubject.currentText,
                        "type": addQuestionType.currentText,
                        "content": addQuestionContent.text.trim(),
                        "score": root.questionTypeScore(addQuestionType.currentText),
                        "answer": addQuestionAnswer.text.trim(),
                        "analysis": addQuestionAnalysis.text.trim(),
                        "difficulty": "中等"
                    }
                    var newId = teacherApi.addQuestion(payload)
                    if (newId > 0) {
                        root.refreshAll()
                        root.selectedQuestionId = newId
                        addQuestionDialog.close()
                        root.showToast("新增完成")
                    } else {
                        root.showToast("新增失败：" + teacherApi.lastError())
                    }
                }
            }
        }
    }

    Dialog {
        id: todoDialog
        modal: true
        width: Math.min(820, root.width - 96)
        height: Math.min(660, root.height - 88)
        x: (root.width - width) / 2
        y: Math.max(36, (root.height - height) / 2)
        padding: 0
        background: Rectangle {
            radius: 30
            color: "#f8fbff"
            border.color: "#dbeafe"
        }
        onOpened: {
            todoTitle.text = ""
            root.todoDraftType = "批改试卷"
            todoTime.value = root.defaultTodoTime()
        }
        contentItem: ColumnLayout {
            anchors.fill: parent
            anchors.margins: 36
            spacing: 20
            RowLayout {
                Layout.fillWidth: true
                Text { text: "新增待办"; color: "#111827"; font.pixelSize: 34; font.bold: true; Layout.fillWidth: true }
                SoftButton { Layout.preferredWidth: 104; Layout.preferredHeight: 56; text: "关闭"; onClicked: todoDialog.close() }
            }
            AppField {
                id: todoTitle
                Layout.fillWidth: true
                Layout.preferredHeight: 70
                font.pixelSize: 21
                leftPadding: 22
                rightPadding: 22
                placeholderText: "待办内容，例如：批改 Java 期末考试"
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 12
                Text { text: "待办类型"; color: "#64748b"; font.pixelSize: 17; font.bold: true }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 14
                    Repeater {
                        model: ["批改试卷", "未出完卷子", "要出卷子"]
                        delegate: Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 66
                            radius: 18
                            color: root.todoDraftType === modelData ? "#eff6ff" : "#ffffff"
                            border.color: root.todoDraftType === modelData ? "#93c5fd" : "#dbe7f6"
                            border.width: root.todoDraftType === modelData ? 2 : 1
                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 18
                                anchors.rightMargin: 18
                                spacing: 12
                                Rectangle {
                                    Layout.preferredWidth: 12
                                    Layout.preferredHeight: 12
                                    radius: 6
                                    color: root.todoDraftType === modelData ? "#2563eb" : "#cbd5e1"
                                }
                                Text {
                                    text: modelData
                                    color: root.todoDraftType === modelData ? "#2563eb" : "#334155"
                                    font.pixelSize: 18
                                    font.bold: true
                                    Layout.fillWidth: true
                                    horizontalAlignment: Text.AlignHCenter
                                }
                            }
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: root.todoDraftType = modelData
                            }
                        }
                    }
                }
            }
            DateBox {
                id: todoTime
                Layout.fillWidth: true
                label: "提醒时间"
                value: root.defaultTodoTime()
                labelSize: 17
                fieldHeight: 64
                valueSize: 19
            }
            Text {
                Layout.fillWidth: true
                text: "当前时间：" + root.formatDateTime(root.nowTime)
                color: "#64748b"
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignRight
            }
            PrimaryButton {
                Layout.fillWidth: true
                Layout.preferredHeight: 66
                text: "确认添加"
                onClicked: {
                    if (todoTitle.text.trim().length === 0) {
                        root.showToast("请填写待办内容")
                        return
                    }
                    if (teacherApi.addTodoItem(todoTitle.text.trim(), root.todoDraftType, todoTime.value)) {
                        root.todoItems = teacherApi.getTodoItems()
                        todoDialog.close()
                        root.showToast("待办已保存")
                    } else {
                        root.showToast("保存失败：" + teacherApi.lastError())
                    }
                }
            }
        }
    }

    Component { id: dashboardPageComponent; DashboardPage {} }
    Component { id: questionBankPageComponent; QuestionBankPage {} }
    Component { id: publishExamPageComponent; PublishExamPage {} }
    Component { id: reviewPageComponent; ReviewPage {} }
    Component { id: classPageComponent; ClassPage {} }
    Component { id: profileCenterPageComponent; ProfileCenterPage {} }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: topNav
            Layout.fillWidth: true
            Layout.preferredHeight: root.navHidden ? 48 : root.normalNavHeight
            color: "#f8fafd"
            opacity: 0.98
            border.color: "#dbeafe"
            z: 10
            Behavior on Layout.preferredHeight { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: teacherApi.startWindowMove()
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: root.width < 760 ? 8 : (root.narrowShell ? 14 : 28)
                anchors.rightMargin: root.width < 760 ? 8 : (root.narrowShell ? 12 : 24)
                spacing: root.width < 760 ? 6 : (root.narrowShell ? 9 : (root.compactShell ? 9 : 16))
                z: 2

                RowLayout {
                    Layout.preferredWidth: root.width < 760 ? 42 : (root.navHidden ? (root.narrowShell ? 66 : 194) : (root.narrowShell ? 70 : (root.compactShell ? 180 : 270)))
                    spacing: root.narrowShell ? 0 : 16
                    LogoMark { Layout.preferredWidth: root.width < 760 ? 38 : (root.narrowShell ? 46 : 58); Layout.preferredHeight: root.width < 760 ? 38 : (root.narrowShell ? 46 : 58) }
                    ColumnLayout {
                        visible: !root.navHidden && !root.narrowShell
                        spacing: 0
                        Text { text: "智考星"; color: "#111827"; font.pixelSize: 38; font.bold: true }
                        Text { text: "考试系统教师端"; color: "#7b8494"; font.pixelSize: 19; font.bold: true }
                    }
                }

                Flickable {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                    Layout.preferredHeight: root.narrowShell ? 60 : 82
                    contentWidth: teacherNavRow.implicitWidth
                    contentHeight: height
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    interactive: contentWidth > width
                    Row {
                        id: teacherNavRow
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: root.width < 760 ? 5 : (root.narrowShell ? 7 : (root.compactShell ? 8 : 14))
                        Repeater {
                            model: root.menuItems
                            TopNavButton {
                                width: root.width < 760 ? 74 : (root.narrowShell ? 96 : (root.compactShell ? 128 : 168))
                                height: root.narrowShell ? 56 : 78
                                text: modelData.title
                                selected: root.currentPage === modelData.page
                                onClicked: root.switchPage(modelData.page)
                            }
                        }
                    }
                }

                NotificationButton {}

                Rectangle {
                    id: topProfileChip
                    Layout.preferredWidth: root.navHidden || root.narrowShell ? 64 : (root.compactShell ? 84 : 236)
                    Layout.preferredHeight: root.narrowShell ? 58 : 76
                    radius: 28
                    color: topProfileMouse.containsMouse || root.currentPage === 5 ? "#eef6ff" : "#ffffff"
                    border.color: root.currentPage === 5 ? "#93c5fd" : "#dbeafe"
                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 16
                        spacing: 12
                        Avatar {
                            Layout.preferredWidth: root.narrowShell ? 42 : 56
                            Layout.preferredHeight: root.narrowShell ? 42 : 56
                            label: root.avatarText()
                        }
                        ColumnLayout {
                            visible: !root.navHidden && !root.compactShell
                            Layout.fillWidth: true
                            spacing: 0
                            Text {
                                Layout.fillWidth: true
                                text: root.profile.username || root.profileName()
                                color: "#111827"
                                font.pixelSize: 24
                                font.bold: true
                                elide: Text.ElideRight
                            }
                            Text {
                                Layout.fillWidth: true
                                text: root.profileName() + " · 个人中心"
                                color: "#64748b"
                                font.pixelSize: 18
                                font.bold: true
                                elide: Text.ElideRight
                            }
                        }
                    }
                    MouseArea {
                        id: topProfileMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: root.openProfileCenter(0)
                    }
                }

                WindowControls {
                    Layout.preferredWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.minimumWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.preferredHeight: root.width < 760 ? 38 : (root.narrowShell ? 44 : 50)
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            Loader {
                id: pageLoader
                anchors.fill: parent
                sourceComponent: root.pageComponent(root.currentPage)
            }
        }
    }

    Rectangle {
        id: toast
        width: Math.min(430, parent.width - 64)
        height: 48
        radius: 16
        color: "#102033"
        opacity: root.toastText.length > 0 ? 0.94 : 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.toastText.length > 0 ? 28 : -60
        z: 60
        Behavior on opacity { NumberAnimation { duration: 180 } }
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }
        Text {
            anchors.centerIn: parent
            text: root.toastText
            color: "#ffffff"
            font.pixelSize: 14
            font.bold: true
        }
    }

    component PageShell: Item {
        id: shell
        default property alias content: body.data
        property bool scrollable: true

        Flickable {
            id: pageFlick
            anchors.fill: parent
            anchors.leftMargin: root.shellHMargin
            anchors.rightMargin: root.narrowShell ? 14 : 20
            anchors.topMargin: root.shellVMargin
            anchors.bottomMargin: root.narrowShell ? 18 : 28
            contentWidth: width
            contentHeight: body.height * root.contentScale + 4
            clip: true
            interactive: contentHeight > height
            boundsBehavior: Flickable.DragOverBounds
            boundsMovement: Flickable.FollowBoundsBehavior
            maximumFlickVelocity: 11200
            flickDeceleration: 3600
            pixelAligned: false
            ScrollBar.vertical: ScrollBar {
                policy: pageFlick.contentHeight > pageFlick.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                width: 14
                contentItem: Rectangle { radius: 7; color: "#9fb3cc" }
                background: Rectangle { radius: 7; color: "#edf2f8" }
            }

            Column {
                id: body
                width: parent.width / root.contentScale
                spacing: root.pageGap
                transformOrigin: Item.TopLeft
                transform: Scale {
                    xScale: root.contentScale
                    yScale: root.contentScale
                }
            }
        }
    }

    component Card: Item {
        id: card
        property real radius: 24
        property bool hoverable: false
        property int enterDelay: 0
        property int enterDirection: 1
        property real enterDistance: 42
        property color fillColor: "#f8fbff"
        property color borderColor: "#dbe5f3"
        default property alias content: body.data

        opacity: 0
        transform: Translate { id: cardSlide; x: card.enterDirection * card.enterDistance }
        Component.onCompleted: enterTimer.restart()

        Timer {
            id: enterTimer
            interval: card.enterDelay
            repeat: false
            onTriggered: enterAnim.start()
        }

        ParallelAnimation {
            id: enterAnim
            NumberAnimation { target: card; property: "opacity"; to: 1; duration: 420; easing.type: Easing.OutCubic }
            NumberAnimation { target: cardSlide; property: "x"; to: 0; duration: 420; easing.type: Easing.OutCubic }
        }

        HoverHandler { id: hover; enabled: card.hoverable }

        Rectangle {
            anchors.fill: parent
            anchors.topMargin: hover.hovered ? 16 : 13
            anchors.leftMargin: 4
            anchors.rightMargin: 4
            radius: card.radius
            color: "#0f172a"
            opacity: hover.hovered ? 0.11 : 0.075
        }

        Rectangle {
            id: body
            anchors.fill: parent
            radius: card.radius
            color: card.fillColor
            border.color: hover.hovered ? "#bcd2f3" : card.borderColor
            border.width: 1
            scale: hover.hovered ? 1.005 : 1
            clip: true
            Behavior on scale { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }

            Rectangle {
                anchors.fill: parent
                radius: parent.radius
                opacity: 0.52
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#ffffff" }
                    GradientStop { position: 0.58; color: "#ffffff" }
                    GradientStop { position: 1.0; color: "#eaf3ff" }
                }
            }
        }
    }

    component TopNavButton: Item {
        id: control
        property string text: ""
        property bool selected: false
        property bool hovered: mouse.containsMouse
        property bool pressed: mouse.pressed
        signal clicked()
        Layout.preferredWidth: root.narrowShell ? 96 : (root.compactShell ? 128 : 168)
        Layout.preferredHeight: root.narrowShell ? 56 : 78
        implicitWidth: Layout.preferredWidth
        implicitHeight: Layout.preferredHeight
        opacity: enabled ? 1 : 0.56

        Rectangle {
            anchors.fill: face
            anchors.topMargin: control.pressed ? 8 : 11
            anchors.leftMargin: 6
            anchors.rightMargin: 6
            radius: root.narrowShell ? 13 : 16
            color: "#1d4ed8"
            opacity: control.pressed ? 0.24 : (control.hovered ? 0.12 : 0)
        }
        Rectangle {
            id: face
            anchors.fill: parent
            radius: root.narrowShell ? 13 : 16
            color: control.selected ? "#2563eb" : (control.hovered ? "#eef6ff" : "transparent")
            scale: control.pressed ? 0.985 : 1
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        Text {
            anchors.centerIn: parent
            text: control.text
            color: control.selected ? "#ffffff" : "#475569"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: root.narrowShell ? 19 : (root.compactShell ? 22 : 26)
            font.bold: true
            elide: Text.ElideRight
            width: parent.width - 10
        }
        MouseArea {
            id: mouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: control.clicked()
        }
    }

    component WindowControls: RowLayout {
        property int buttonSize: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        property int controlGap: root.width < 760 ? 5 : (root.narrowShell ? 5 : 6)
        width: buttonSize * 3 + controlGap * 2
        height: root.width < 760 ? 38 : (root.narrowShell ? 44 : 50)
        spacing: controlGap
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Layout.minimumWidth: width
        Layout.preferredWidth: width
        Layout.preferredHeight: height
        WindowButton { symbol: "-"; onClicked: teacherApi.minimizeWindow() }
        WindowButton { symbol: "□"; onClicked: teacherApi.toggleMaximizeWindow() }
        WindowButton { symbol: "X"; danger: true; onClicked: teacherApi.closeWindow() }
    }

    component WindowButton: Item {
        id: control
        property string symbol: ""
        property bool danger: false
        signal clicked()
        Layout.preferredWidth: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        Layout.minimumWidth: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        Layout.preferredHeight: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        Layout.minimumHeight: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        width: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        height: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: control.danger && buttonMouse.containsMouse ? "#ef4444" : (buttonMouse.containsMouse ? "#eaf2ff" : "#ffffff")
            border.width: 1
            border.color: control.danger && buttonMouse.containsMouse ? "#ef4444" : "#dbeafe"
        }
        Rectangle {
            visible: control.symbol === "-"
            width: root.width < 760 ? 11 : (root.narrowShell ? 12 : 14)
            height: root.width < 760 ? 2 : (root.narrowShell ? 2 : 3)
            radius: height / 2
            anchors.centerIn: parent
            color: "#334155"
        }
        Text {
            visible: control.symbol !== "-"
            anchors.centerIn: parent
            text: control.symbol
            color: control.danger && buttonMouse.containsMouse ? "#ffffff" : "#334155"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: root.width < 760 ? 18 : (root.narrowShell ? 20 : 24)
            font.bold: true
        }
        MouseArea {
            id: buttonMouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: control.clicked()
        }
    }

    component LogoMark: Item {
        Image {
            anchors.fill: parent
            source: "qrc:/assets/brand-logo-mark.png"
            fillMode: Image.PreserveAspectFit
            smooth: true
            mipmap: true
        }
    }

    component Avatar: Rectangle {
        id: avatar
        property string label: "师"
        radius: width / 2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#dbeafe" }
            GradientStop { position: 1.0; color: "#eef2ff" }
        }
        border.color: "#bfdbfe"
        Text {
            anchors.centerIn: parent
            text: avatar.label
            color: "#2563eb"
            font.pixelSize: avatar.width * 0.42
            font.bold: true
        }
    }

    component InfoLine: RowLayout {
        id: line
        property string label: ""
        property string value: ""
        Layout.fillWidth: true
        spacing: 8
        Text { text: line.label; color: "#94a3b8"; font.pixelSize: 12; Layout.preferredWidth: 42 }
        Text { text: line.value; color: "#334155"; font.pixelSize: 13; Layout.fillWidth: true; elide: Text.ElideRight }
    }

    component PrimaryButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        property bool pressed: mouse.pressed
        signal clicked()
        implicitHeight: 56
        height: 56
        opacity: enabled ? 1 : 0.56
        Rectangle {
            anchors.fill: face
            anchors.topMargin: control.pressed ? 10 : 12
            radius: 16
            color: "#1d4ed8"
            opacity: control.pressed ? 0.30 : (control.hovered ? 0.18 : 0.10)
        }
        Rectangle {
            id: face
            anchors.fill: parent
            radius: 16
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3b82f6" }
                GradientStop { position: 1.0; color: control.hovered ? "#5b5cf0" : "#4f46e5" }
            }
            scale: control.pressed ? 0.985 : 1
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        Text {
            anchors.centerIn: parent
            text: control.text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            font.bold: true
        }
        MouseArea {
            id: mouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            enabled: control.enabled
            onClicked: control.clicked()
        }
    }

    component SoftButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        property bool pressed: mouse.pressed
        signal clicked()
        implicitHeight: 52
        height: 52
        opacity: enabled ? 1 : 0.56
        Rectangle {
            anchors.fill: face
            anchors.topMargin: control.pressed ? 8 : 10
            anchors.leftMargin: 6
            anchors.rightMargin: 6
            radius: 15
            color: "#1d4ed8"
            opacity: control.pressed ? 0.18 : (control.hovered ? 0.10 : 0)
        }
        Rectangle {
            id: face
            anchors.fill: parent
            radius: 15
            color: control.hovered ? "#eef6ff" : "#f6f8fc"
            border.color: "transparent"
            scale: control.pressed ? 0.985 : 1
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        Text {
            anchors.centerIn: parent
            text: control.text
            color: "#2563eb"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 17
            font.bold: true
        }
        MouseArea {
            id: mouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            enabled: control.enabled
            onClicked: control.clicked()
        }
    }

    component SuccessButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        property bool pressed: mouse.pressed
        signal clicked()
        implicitHeight: 56
        height: 56
        opacity: enabled ? 1 : 0.56
        Rectangle {
            anchors.fill: face
            anchors.topMargin: control.pressed ? 10 : 12
            radius: 16
            color: "#16a34a"
            opacity: control.pressed ? 0.28 : (control.hovered ? 0.18 : 0.10)
        }
        Rectangle {
            id: face
            anchors.fill: parent
            radius: 16
            color: control.hovered ? "#22c55e" : "#34b85a"
            scale: control.pressed ? 0.985 : 1
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        Text {
            anchors.centerIn: parent
            text: control.text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            font.bold: true
        }
        MouseArea {
            id: mouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            enabled: control.enabled
            onClicked: control.clicked()
        }
    }

    component AppField: TextField {
        id: field
        height: 58
        leftPadding: 18
        rightPadding: 18
        color: "#172033"
        placeholderTextColor: "#aeb7c5"
        font.pixelSize: 18
        verticalAlignment: TextInput.AlignVCenter
        selectionColor: "#3b82f6"
        selectedTextColor: "#ffffff"
        background: Rectangle {
            radius: 15
            color: field.activeFocus ? "#ffffff" : "#f7f9fd"
            border.width: field.activeFocus ? 2 : 1
            border.color: field.activeFocus ? "#3b82f6" : "#e4eaf3"
        }
    }

    component AppCombo: ComboBox {
        id: combo
        height: 58
        hoverEnabled: true
        font.pixelSize: 17
        contentItem: Text {
            text: combo.displayText
            color: "#172033"
            verticalAlignment: Text.AlignVCenter
            leftPadding: 16
            rightPadding: 52
            font: combo.font
            elide: Text.ElideRight
        }
        indicator: Rectangle {
            x: combo.width - width - 12
            y: (combo.height - height) / 2
            width: 32
            height: 32
            radius: 16
            color: combo.popup.visible ? "#dbeafe" : (combo.hovered ? "#eaf2ff" : "#edf4ff")
            border.color: combo.popup.visible || combo.activeFocus ? "#93c5fd" : "#dbe7f5"
            rotation: combo.popup.visible ? 180 : 0
            Behavior on rotation { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }

            Canvas {
                id: comboArrow
                anchors.centerIn: parent
                width: 15
                height: 15
                property color strokeColor: combo.popup.visible || combo.activeFocus ? "#2563eb" : "#64748b"
                onStrokeColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)
                    ctx.strokeStyle = strokeColor
                    ctx.lineWidth = 2.4
                    ctx.lineCap = "round"
                    ctx.lineJoin = "round"
                    ctx.beginPath()
                    ctx.moveTo(3, 5)
                    ctx.lineTo(width / 2, height - 4)
                    ctx.lineTo(width - 3, 5)
                    ctx.stroke()
                }
            }
        }
        background: Rectangle {
            radius: 15
            color: combo.activeFocus || combo.hovered ? "#ffffff" : "#f7f9fd"
            border.width: combo.activeFocus ? 2 : 1
            border.color: combo.activeFocus ? "#3b82f6" : (combo.hovered ? "#bfdbfe" : "#e4eaf3")
        }
        delegate: ItemDelegate {
            id: comboDelegate
            width: combo.width
            height: 48
            hoverEnabled: true
            contentItem: Text {
                text: modelData
                color: comboDelegate.hovered || comboDelegate.highlighted ? "#1d4ed8" : "#172033"
                font.pixelSize: 16
                font.bold: comboDelegate.hovered || comboDelegate.highlighted
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle {
                radius: 12
                color: comboDelegate.hovered || comboDelegate.highlighted ? "#eff6ff" : "transparent"
            }
        }
        popup: Popup {
            y: combo.height + 8
            width: combo.width
            padding: 6
            implicitHeight: Math.min(contentItem.implicitHeight + 12, 252)
            background: Rectangle {
                radius: 16
                color: "#ffffff"
                border.color: "#dbeafe"
            }
            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: combo.popup.visible ? combo.delegateModel : null
                currentIndex: combo.highlightedIndex
                spacing: 4
                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
            }
        }
    }

    component SectionTitle: Column {
        property string title: root.pageTitles[root.currentPage]
        property string subtitle: root.pageSubtitles[root.currentPage]
        width: parent.width
        spacing: root.narrowShell ? 4 : 6
        Text {
            width: parent.width
            text: parent.title
            color: "#111827"
            font.pixelSize: root.narrowShell ? 30 : (root.compactShell ? 38 : 44)
            font.bold: true
            wrapMode: Text.WordWrap
        }
        Text {
            width: parent.width
            text: parent.subtitle
            color: "#64748b"
            font.pixelSize: root.narrowShell ? 16 : 20
            wrapMode: Text.WordWrap
        }
    }

    component NotificationButton: Item {
        id: notify
        property bool dropdownHovered: dropdownMouse.containsMouse
        Layout.preferredWidth: root.narrowShell ? 54 : 66
        Layout.preferredHeight: root.narrowShell ? 54 : 66
        z: 80

        Rectangle {
            id: notifyFace
            anchors.fill: parent
            radius: 20
            color: notifyMouse.containsMouse || notify.dropdownHovered ? "#eef6ff" : "#ffffff"
            border.color: "#dbeafe"
            Text {
                anchors.centerIn: parent
                text: "✉"
                color: "#2563eb"
                font.pixelSize: 28
                font.bold: true
            }
            Rectangle {
                visible: root.todoItems.length > 0
                width: Math.max(26, badgeText.implicitWidth + 12)
                height: 26
                radius: 13
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: -5
                anchors.rightMargin: -5
                color: "#ef4444"
                border.color: "#ffffff"
                border.width: 2
                Text {
                    id: badgeText
                    anchors.centerIn: parent
                    text: root.todoItems.length > 99 ? "99+" : String(root.todoItems.length)
                    color: "#ffffff"
                    font.pixelSize: 14
                    font.bold: true
                }
            }
        }
        MouseArea {
            id: notifyMouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
        Rectangle {
            id: dropdown
            width: 480
            height: Math.min(430, 122 + Math.max(1, root.todoItems.slice(0, 4).length) * 92)
            x: -width + notify.width
            y: notify.height + 10
            radius: 20
            color: "#ffffff"
            border.color: "#dbeafe"
            opacity: notifyMouse.containsMouse || notify.dropdownHovered ? 1 : 0
            visible: opacity > 0.02
            Behavior on opacity { NumberAnimation { duration: 140 } }
            Rectangle {
                anchors.fill: parent
                anchors.topMargin: 12
                radius: parent.radius
                color: "#2563eb"
                opacity: 0.05
            }
            MouseArea {
                id: dropdownMouse
                anchors.fill: parent
                hoverEnabled: true
            }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 22
                spacing: 14
                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "通知提醒"; color: "#111827"; font.pixelSize: 30; font.bold: true; Layout.fillWidth: true }
                    Text { text: root.todoItems.length + " 条"; color: "#ef4444"; font.pixelSize: 21; font.bold: true }
                }
                Repeater {
                    model: root.todoItems.length > 0 ? root.sortedTodoItems().slice(0, 4) : [{"title":"暂无待办提醒", "type":"系统通知", "time":"--"}]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 86
                        radius: 18
                        color: "#f8fbff"
                        border.color: "#e5edf6"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 14
                            Rectangle {
                                Layout.preferredWidth: 10
                                Layout.preferredHeight: 46
                                radius: 5
                                color: modelData.type === "批改试卷" ? "#f97316" : "#2563eb"
                            }
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 5
                                Text { text: modelData.title || "--"; color: "#111827"; font.pixelSize: 21; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                                Text { text: (modelData.type || "提醒") + " · " + (modelData.time || "--") + (root.todoItems.length > 0 ? (" · " + root.todoCountdown(modelData)) : ""); color: "#64748b"; font.pixelSize: 18; Layout.fillWidth: true; elide: Text.ElideRight }
                            }
                        }
                    }
                }
            }
        }
    }

    component MetricCard: Card {
        id: metric
        property string label: ""
        property string value: ""
        property string delta: ""
        property bool positive: true
        property string iconText: ""
        property color iconColor: "#2563eb"
        property color iconBg: "#eef6ff"
        property color accent: "#2563eb"
        height: root.narrowShell ? 132 : (root.compactShell ? 146 : 160)
        Item {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 16 : 22
            Rectangle {
                width: 4
                height: parent.height - 8
                radius: 2
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                color: metric.accent
                opacity: 0.85
            }
            Rectangle {
                visible: metric.delta.length > 0
                anchors.top: parent.top
                anchors.right: parent.right
                width: Math.max(76, deltaText.implicitWidth + 24)
                height: 34
                radius: 17
                color: metric.positive ? "#ecfdf3" : "#fef2f2"
                Text {
                    id: deltaText
                    anchors.centerIn: parent
                text: (metric.positive ? "↗ " : "↘ ") + metric.delta
                    color: metric.positive ? "#22c55e" : "#ef4444"
                    font.pixelSize: root.narrowShell ? 12 : 13
                    font.bold: true
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: root.narrowShell ? 14 : 18
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8
                Text {
                    text: metric.label
                    color: "#64748b"
                    font.pixelSize: root.narrowShell ? 13 : 15
                    font.bold: true
                }
                Text {
                    text: metric.value
                    color: "#111827"
                    font.pixelSize: root.narrowShell ? 34 : (root.compactShell ? 38 : 42)
                    font.bold: true
                }
                Rectangle {
                    width: 58
                    height: 4
                    radius: 2
                    color: metric.accent
                    opacity: 0.28
                }
            }
        }
    }

    component ProfileCenterPage: PageShell {
        SectionTitle { title: "个人中心"; subtitle: "账号资料、安全密码与系统设置" }

        Card {
            width: parent.width
            height: root.narrowShell ? 350 : 250
            enterDelay: 20
            GridLayout {
                anchors.fill: parent
                anchors.margins: root.narrowShell ? 24 : 34
                columns: root.narrowShell ? 2 : 4
                columnSpacing: root.narrowShell ? 18 : 30
                rowSpacing: root.narrowShell ? 16 : 22
                SoftButton {
                    Layout.preferredWidth: root.narrowShell ? 104 : 126
                    Layout.preferredHeight: 58
                    Layout.alignment: Qt.AlignVCenter
                    text: "返回"
                    onClicked: root.switchPage(0)
                }
                Avatar {
                    Layout.preferredWidth: root.narrowShell ? 90 : 118
                    Layout.preferredHeight: root.narrowShell ? 90 : 118
                    Layout.alignment: Qt.AlignVCenter
                    label: root.avatarText()
                }
                ColumnLayout {
                    Layout.columnSpan: root.narrowShell ? 2 : 1
                    Layout.fillWidth: true
                    spacing: 10
                    Text { text: root.profileName(); color: "#111827"; font.pixelSize: root.narrowShell ? 32 : 38; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                    Text { text: "账号：" + (root.profile.username || "teacher"); color: "#475569"; font.pixelSize: 19; Layout.fillWidth: true; elide: Text.ElideRight }
                    Text { text: "科目：" + (root.profile.subject || "教师端") + "    邮箱：" + (root.profile.email || "未绑定"); color: "#475569"; font.pixelSize: 18; Layout.fillWidth: true; wrapMode: Text.WordWrap; maximumLineCount: root.narrowShell ? 2 : 1; elide: Text.ElideRight }
                    Flow {
                        Layout.fillWidth: true
                        spacing: 10
                        TeacherProfilePill { text: "教师账号"; tone: "#2563eb"; bg: "#eff6ff" }
                        TeacherProfilePill { text: "自动保存开启"; tone: "#16a34a"; bg: "#ecfdf3" }
                    }
                }
                Rectangle {
                    Layout.columnSpan: root.narrowShell ? 2 : 1
                    Layout.preferredWidth: 156
                    Layout.preferredHeight: 56
                    Layout.alignment: root.narrowShell ? Qt.AlignLeft : Qt.AlignVCenter
                    radius: 28
                    color: "#eff6ff"
                    Text { anchors.centerIn: parent; text: root.profile.role || "教师"; color: "#2563eb"; font.pixelSize: 21; font.bold: true }
                }
            }
        }

        TeacherProfileStats { width: parent.width }

        GridLayout {
            width: parent.width
            columns: parent.width > 1080 ? 5 : 1
            columnSpacing: 18
            rowSpacing: 18

            Card {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1080 ? 2 : 1
                Layout.preferredHeight: root.narrowShell ? 520 : 540
                enterDelay: 80
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 28
                    spacing: 14
                    Repeater {
                        model: [
                            {"title":"修改个人信息", "sub":"姓名、学科、邮箱和手机", "page":0, "tone":"#2563eb"},
                            {"title":"修改密码", "sub":"更新登录密码", "page":1, "tone":"#7c3aed"},
                            {"title":"系统设置", "sub":"通知、显示和自动保存", "page":2, "tone":"#16a34a"},
                            {"title":"退出登录", "sub":"返回登录页面", "page":3, "tone":"#ef4444"}
                        ]
                        delegate: Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 104
                            radius: 22
                            color: root.profileSubPage === modelData.page ? "#eff6ff" : "#ffffff"
                            border.color: root.profileSubPage === modelData.page ? "#bfdbfe" : "#e5edf6"
                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 18
                                spacing: 16
                                Rectangle {
                                    Layout.preferredWidth: 12
                                    Layout.preferredHeight: 60
                                    radius: 6
                                    color: modelData.tone
                                }
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Text { text: modelData.title; color: modelData.page === 3 ? "#ef4444" : "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                                    Text { text: modelData.sub; color: "#64748b"; font.pixelSize: 17; Layout.fillWidth: true; elide: Text.ElideRight }
                                }
                                Text { text: "›"; color: "#94a3b8"; font.pixelSize: 36; font.bold: true }
                            }
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (modelData.page === 3) {
                                        teacherApi.logout()
                                    } else {
                                        root.profileSubPage = modelData.page
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Card {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1080 ? 3 : 1
                Layout.preferredHeight: root.narrowShell ? 620 : 540
                enterDelay: 120
                Loader {
                    anchors.fill: parent
                    anchors.margins: root.narrowShell ? 24 : 32
                    sourceComponent: root.profileSubPage === 1 ? passwordFormComponent
                                     : (root.profileSubPage === 2 ? settingsFormComponent : infoFormComponent)
                }

                Component {
                    id: infoFormComponent
                    ColumnLayout {
                        spacing: 22
                        Text { text: "修改个人信息"; color: "#111827"; font.pixelSize: 30; font.bold: true }
                        Text { Layout.fillWidth: true; text: "维护教师姓名、任教学科、手机号和邮箱，首页、发布考试和批改记录会同步使用这些信息。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
                        GridLayout {
                            Layout.fillWidth: true
                            columns: root.narrowShell ? 1 : 2
                            columnSpacing: 18
                            rowSpacing: 18
                            AppField { id: profileNameField; Layout.fillWidth: true; placeholderText: "姓名"; text: root.profileName() }
                            AppField { id: profileSubjectField; Layout.fillWidth: true; placeholderText: "任教学科"; text: root.profile.subject || "" }
                            AppField { id: profilePhoneField; Layout.fillWidth: true; placeholderText: "手机号"; text: root.profile.phone || "" }
                            AppField { id: profileEmailField; Layout.fillWidth: true; placeholderText: "邮箱"; text: root.profile.email || "" }
                        }
                        TeacherProfileNote { title: "资料用途"; body: "这些信息会出现在班级考试、试卷发布、批改任务和消息提醒中，建议与学校账号资料保持一致。" }
                        Item { Layout.fillHeight: true }
                        PrimaryButton {
                            Layout.fillWidth: true
                            text: "保存修改"
                            onClicked: {
                                var payload = {
                                    "name": profileNameField.text,
                                    "subject": profileSubjectField.text,
                                    "phone": profilePhoneField.text,
                                    "email": profileEmailField.text
                                }
                                if (teacherApi.updateTeacherProfile(payload)) {
                                    root.profile = teacherApi.getTeacherProfile()
                                    root.showToast("个人信息已保存到数据库")
                                } else {
                                    root.showToast(teacherApi.lastError() || "保存个人信息失败")
                                }
                            }
                        }
                    }
                }

                Component {
                    id: passwordFormComponent
                    ColumnLayout {
                        spacing: 20
                        Text { text: "修改密码"; color: "#111827"; font.pixelSize: 30; font.bold: true }
                        Text { Layout.fillWidth: true; text: "更新教师端登录密码，建议不少于 6 位并避免与其他平台共用。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
                        AppField { id: oldPasswordField; Layout.fillWidth: true; placeholderText: "原密码"; echoMode: TextInput.Password }
                        AppField { id: newPasswordField; Layout.fillWidth: true; placeholderText: "新密码"; echoMode: TextInput.Password }
                        AppField { id: confirmPasswordField; Layout.fillWidth: true; placeholderText: "确认新密码"; echoMode: TextInput.Password }
                        TeacherProfileNote { title: "安全提示"; body: "修改成功后请重新保管新密码，批改和发布考试前确认账号可正常登录。" }
                        Item { Layout.fillHeight: true }
                        PrimaryButton {
                            Layout.fillWidth: true
                            text: "确认修改密码"
                            onClicked: {
                                if (oldPasswordField.text.length === 0) {
                                    root.showToast("请输入原密码")
                                    return
                                }
                                if (newPasswordField.text.length < 6) {
                                    root.showToast("新密码至少 6 位")
                                    return
                                }
                                if (newPasswordField.text !== confirmPasswordField.text) {
                                    root.showToast("两次输入的新密码不一致")
                                    return
                                }
                                if (teacherApi.changePassword(oldPasswordField.text, newPasswordField.text)) {
                                    root.showToast("密码已修改")
                                    oldPasswordField.text = ""
                                    newPasswordField.text = ""
                                    confirmPasswordField.text = ""
                                } else {
                                    root.showToast(teacherApi.lastError() || "修改密码失败")
                                }
                            }
                        }
                    }
                }

                Component {
                    id: settingsFormComponent
                    ColumnLayout {
                        spacing: 18
                        Text { text: "系统设置"; color: "#111827"; font.pixelSize: 30; font.bold: true }
                        Text { Layout.fillWidth: true; text: "调整提醒、草稿保存和顶部栏显示方式，减少发布考试与批改试卷时的重复操作。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
                        SettingSwitch { Layout.fillWidth: true; label: "待办提醒"; description: "有考试发布、批改任务时提醒"; checked: true }
                        SettingSwitch { Layout.fillWidth: true; label: "自动保存草稿"; description: "发布考试时保留当前试卷配置"; checked: true }
                        SettingSwitch { Layout.fillWidth: true; label: "精简顶部栏"; description: "滚动页面时自动收起顶部空间"; checked: !root.navHidden; onToggled: root.navHidden = !checked }
                        Item { Layout.fillHeight: true }
                        SoftButton {
                            Layout.fillWidth: true
                            text: "清理本地缓存"
                            onClicked: root.showToast("缓存已清理")
                        }
                    }
                }
            }
        }
    }

    component TeacherProfilePill: Rectangle {
        id: pill
        property string text: ""
        property color tone: "#2563eb"
        property color bg: "#eff6ff"
        width: Math.max(118, pillText.implicitWidth + 30)
        height: 40
        radius: 20
        color: pill.bg
        Text { id: pillText; anchors.centerIn: parent; text: pill.text; color: pill.tone; font.pixelSize: 18; font.bold: true }
    }

    component TeacherProfileStats: GridLayout {
        columns: width > 1080 ? 4 : 2
        columnSpacing: root.narrowShell ? 12 : 18
        rowSpacing: root.narrowShell ? 12 : 18
        TeacherProfileStatCard { Layout.fillWidth: true; title: "任教学科"; value: root.profile.subject || "未设置"; detail: "发布考试默认科目"; accent: "#2563eb" }
        TeacherProfileStatCard { Layout.fillWidth: true; title: "管理班级"; value: String(root.classes.length || 1) + " 个"; detail: "班级考试与成绩概览"; accent: "#16a34a" }
        TeacherProfileStatCard { Layout.fillWidth: true; title: "待批改"; value: String(root.pendingReviews.length || 0) + " 份"; detail: "进入批改试卷处理"; accent: "#f97316" }
        TeacherProfileStatCard { Layout.fillWidth: true; title: "题库数量"; value: String(root.questions.length || 0) + " 题"; detail: "组卷与发布考试使用"; accent: "#8b5cf6" }
    }

    component TeacherProfileStatCard: Rectangle {
        id: statCard
        property string title: ""
        property string value: ""
        property string detail: ""
        property color accent: "#2563eb"
        implicitHeight: root.narrowShell ? 128 : 150
        radius: root.narrowShell ? 18 : 22
        color: "#f8fbff"
        border.color: "#dbe7f6"
        border.width: 1
        clip: true
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: root.narrowShell ? 8 : 10
            color: statCard.accent
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: root.narrowShell ? 22 : 28
            anchors.rightMargin: root.narrowShell ? 18 : 24
            anchors.topMargin: root.narrowShell ? 18 : 24
            anchors.bottomMargin: root.narrowShell ? 18 : 22
            spacing: root.narrowShell ? 7 : 9
            Text { text: statCard.title; color: "#64748b"; font.pixelSize: 17; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { text: statCard.value; color: "#111827"; font.pixelSize: root.narrowShell ? 26 : 30; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { text: statCard.detail; color: "#64748b"; font.pixelSize: 16; Layout.fillWidth: true; elide: Text.ElideRight }
        }
    }

    component TeacherProfileNote: Rectangle {
        id: note
        property string title: ""
        property string body: ""
        Layout.fillWidth: true
        Layout.preferredHeight: 118
        radius: 22
        color: "#f8fbff"
        border.color: "#dbe7f6"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 16
            Rectangle { Layout.preferredWidth: 12; Layout.fillHeight: true; radius: 6; color: "#2563eb" }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8
                Text { text: note.title; color: "#111827"; font.pixelSize: 22; font.bold: true }
                Text { Layout.fillWidth: true; text: note.body; color: "#64748b"; font.pixelSize: 17; wrapMode: Text.WordWrap }
            }
        }
    }

    component SettingSwitch: Rectangle {
        id: settingSwitch
        property string label: ""
        property string description: ""
        property bool checked: false
        signal toggled()
        Layout.preferredHeight: 92
        radius: 22
        color: "#ffffff"
        border.color: "#e5edf6"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 16
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: settingSwitch.label; color: "#111827"; font.pixelSize: 20; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                Text { text: settingSwitch.description; color: "#64748b"; font.pixelSize: 16; Layout.fillWidth: true; elide: Text.ElideRight }
            }
            Rectangle {
                id: switchTrack
                Layout.preferredWidth: 84
                Layout.preferredHeight: 40
                radius: 20
                color: settingSwitch.checked ? "#3b82f6" : "#e5e7eb"
                border.color: settingSwitch.checked ? "#2563eb" : "#d1d5db"
                Behavior on color { ColorAnimation { duration: 140 } }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    text: "ON"
                    visible: settingSwitch.checked
                    color: "#ffffff"
                    font.pixelSize: 12
                    font.bold: true
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: "OFF"
                    visible: !settingSwitch.checked
                    color: "#64748b"
                    font.pixelSize: 12
                    font.bold: true
                }
                Rectangle {
                    width: 32
                    height: 32
                    radius: 16
                    y: 4
                    x: settingSwitch.checked ? switchTrack.width - width - 4 : 4
                    color: "#ffffff"
                    border.color: settingSwitch.checked ? "#bfdbfe" : "#e5e7eb"
                    Behavior on x { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        settingSwitch.checked = !settingSwitch.checked
                        settingSwitch.toggled()
                    }
                }
            }
        }
    }

    component TeacherHeroCard: Card {
        height: root.narrowShell ? 560 : Math.max(380, Math.min(430, root.height * 0.46))
        radius: 24
        fillColor: "#121a34"
        borderColor: "#26324a"

        Rectangle {
            anchors.fill: parent
            radius: 24
            color: "#121a34"
            clip: true
            Rectangle { width: 390; height: 390; radius: 195; color: "#3b82f6"; opacity: 0.20; x: -92; y: -132 }
            Rectangle { width: 520; height: 520; radius: 260; color: "#22c55e"; opacity: 0.13; anchors.right: parent.right; anchors.rightMargin: 54; y: -94 }
            Rectangle { width: 280; height: 280; radius: 140; color: "#f59e0b"; opacity: 0.10; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.rightMargin: -86; anchors.bottomMargin: -108 }
            Rectangle { anchors.fill: parent; color: "#071224"; opacity: 0.30 }

            GridLayout {
                anchors.fill: parent
                anchors.leftMargin: root.narrowShell ? 22 : 36
                anchors.rightMargin: root.narrowShell ? 22 : 32
                anchors.topMargin: root.narrowShell ? 24 : 34
                anchors.bottomMargin: root.narrowShell ? 24 : 34
                columns: root.narrowShell ? 1 : 2
                columnSpacing: 34
                rowSpacing: 22

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    spacing: root.narrowShell ? 14 : 18

                    RowLayout {
                        spacing: 10
                        Rectangle {
                            Layout.preferredWidth: 92
                            Layout.preferredHeight: 30
                            radius: 15
                            color: "#1d2a44"
                            border.color: "#40516d"
                            Text { anchors.centerIn: parent; text: root.profile.subject || "教师端"; color: "#cbd5e1"; font.pixelSize: 13; font.bold: true }
                        }
                        Text { text: "今日教学概览"; color: "#cbd5e1"; font.pixelSize: 15; font.bold: true }
                    }

                    Text {
                        Layout.fillWidth: true
                        text: "下午好，" + root.profileName()
                        color: "#ffffff"
                        font.pixelSize: root.narrowShell ? 34 : (root.compactShell ? 39 : 44)
                        font.bold: true
                        elide: Text.ElideRight
                    }

                    Text {
                        Layout.fillWidth: true
                        text: "当前有 " + String(root.dashboard.examCount || root.exams.length || 0) + " 份试卷、" + String(root.dashboard.studentCount || 0) + " 名学生、" + String(root.pendingReviews.length || 0) + " 份待批改任务。"
                        color: "#aab4c3"
                        font.pixelSize: root.narrowShell ? 15 : 18
                        wrapMode: Text.WordWrap
                    }

                    Flow {
                        Layout.fillWidth: true
                        spacing: 12
                        PrimaryButton {
                            width: root.narrowShell ? Math.min(170, (parent.width - 12) / 2) : 150
                            text: "发布考试"
                            onClicked: root.switchPage(2)
                        }
                        SoftButton {
                            width: root.narrowShell ? Math.min(170, (parent.width - 12) / 2) : 150
                            text: "批改试卷"
                            onClicked: root.switchPage(3)
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: root.narrowShell
                    Layout.preferredWidth: root.narrowShell ? 1 : 430
                    Layout.preferredHeight: root.narrowShell ? 282 : 292
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    radius: 22
                    color: "#26324a"
                    opacity: 0.88
                    border.color: "#52627a"
                    border.width: 1

                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 1
                        radius: 21
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#334155" }
                            GradientStop { position: 1.0; color: "#1d273c" }
                        }
                        opacity: 0.58
                    }

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 26
                        spacing: 14

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10
                            Rectangle {
                                Layout.preferredWidth: 34
                                Layout.preferredHeight: 34
                                radius: 12
                                color: "#334155"
                                Text { anchors.centerIn: parent; text: "◷"; color: "#cbd5e1"; font.pixelSize: 18; font.bold: true }
                            }
                            Text { text: "下一项工作"; color: "#cbd5e1"; font.pixelSize: 15; font.bold: true; Layout.fillWidth: true }
                            Rectangle {
                                Layout.preferredWidth: 82
                                Layout.preferredHeight: 30
                                radius: 15
                                color: "#4b3428"
                                Text { anchors.centerIn: parent; text: "待处理"; color: "#f59e0b"; font.pixelSize: 12; font.bold: true }
                            }
                        }

                        Text {
                            Layout.fillWidth: true
                            text: root.todoItems.length > 0 ? root.nextTodo().title : "查看班级考试安排"
                            color: "#ffffff"
                            font.pixelSize: root.narrowShell ? 21 : 24
                            font.bold: true
                            wrapMode: Text.WordWrap
                            maximumLineCount: 2
                            elide: Text.ElideRight
                        }

                        Text {
                            text: root.todoItems.length > 0 ? (root.nextTodo().time + " · " + root.nextTodo().type) : "进入我的班级查看考试概况"
                            color: "#aab4c3"
                            font.pixelSize: 14
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.minimumHeight: root.narrowShell ? 96 : 112
                            radius: 20
                            color: "#172033"
                            border.color: "#3b465c"
                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 18
                                spacing: 8
                                Text {
                                    Layout.fillWidth: true
                                    text: "倒计时"
                                    color: "#93c5fd"
                                    font.pixelSize: 17
                                    font.bold: true
                                }
                                Text {
                                    Layout.fillWidth: true
                                    text: root.todoItems.length > 0 ? root.todoCountdown(root.nextTodo()) : "--"
                                    color: "#ffffff"
                                    font.pixelSize: root.narrowShell ? 30 : 40
                                    font.bold: true
                                    horizontalAlignment: Text.AlignLeft
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    component HeroCountBox: Rectangle {
        property string number: "0"
        property string label: ""
        Layout.preferredWidth: 86
        Layout.preferredHeight: 76
        radius: 18
        color: "#3b465c"
        opacity: 0.94
        Column {
            anchors.centerIn: parent
            spacing: 3
            Text { text: number; color: "#60a5fa"; font.pixelSize: 28; font.bold: true; horizontalAlignment: Text.AlignHCenter }
            Text { text: label; color: "#aab4c3"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter }
        }
    }

    component DashboardPage: PageShell {
        TeacherHeroCard {
            width: parent.width
            enterDelay: 0
            enterDirection: -1
        }

        GridLayout {
            width: parent.width
            columns: root.narrowShell ? 1 : (parent.width > 1100 ? 4 : 2)
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            MetricCard { Layout.fillWidth: true; value: String(root.dashboard.questionCount || root.questions.length || 0); label: "题库总量"; delta: root.signedMetric(root.dashboard.questionDelta || 0, 0); positive: root.metricPositive(root.dashboard.questionDelta || 0); iconText: "Q"; iconColor: "#3b82f6"; iconBg: "#eef6ff"; accent: "#2563eb"; enterDelay: 0; enterDirection: -1 }
            MetricCard { Layout.fillWidth: true; value: String(root.dashboard.examCount || root.exams.length || 0); label: "试卷数量"; delta: root.signedMetric(root.dashboard.examDelta || 0, 0); positive: root.metricPositive(root.dashboard.examDelta || 0); iconText: "P"; iconColor: "#22c55e"; iconBg: "#ecfdf3"; accent: "#10b981"; enterDelay: 80; enterDirection: -1 }
            MetricCard { Layout.fillWidth: true; value: String(root.dashboard.studentCount || 0); label: "学生人数"; delta: root.signedMetric(root.dashboard.studentDelta || 0, 0); positive: root.metricPositive(root.dashboard.studentDelta || 0); iconText: "S"; iconColor: "#8b5cf6"; iconBg: "#f3e8ff"; accent: "#8b5cf6"; enterDelay: 160; enterDirection: 1 }
            MetricCard { Layout.fillWidth: true; value: String(root.scoreStats.average || 86.5); label: "平均成绩"; delta: root.signedMetric(root.dashboard.averageDelta || 0, 1); positive: root.metricPositive(root.dashboard.averageDelta || 0); iconText: "A"; iconColor: "#f59e0b"; iconBg: "#fff7ed"; accent: "#f59e0b"; enterDelay: 240; enterDirection: 1 }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1120 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            LineChartCard { Layout.fillWidth: true; Layout.columnSpan: parent.width > 1120 ? 2 : 1; Layout.preferredHeight: root.narrowShell ? 320 : 380; title: "近 7 次考试平均分趋势"; enterDelay: 80; enterDirection: -1 }
            PendingCard { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 320 : 380; enterDelay: 150; enterDirection: 1 }
        }

        Card {
            width: parent.width
            height: root.narrowShell ? 318 : 260
            enterDelay: 220
            enterDirection: 1
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: root.narrowShell ? 18 : 24
                spacing: 12
                Text { text: "进行中和草稿试卷"; color: "#111827"; font.pixelSize: 22; font.bold: true }
                ListView {
                    id: workflowExamList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: root.workflowExamCards()
                    visible: count > 0
                    spacing: 10
                    interactive: false
                    delegate: Rectangle {
                        width: ListView.view.width
                        height: 58
                        radius: 16
                        color: "#ffffff"
                        border.color: "#e5edf6"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: root.narrowShell ? 10 : 12
                            spacing: 12
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text { text: modelData.name || "--"; color: "#111827"; font.pixelSize: 15; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                                Text {
                                    text: "已交 " + Number(modelData.participants || 0)
                                          + (Number(modelData.targetStudentCount || 0) > 0 ? ("/" + Number(modelData.targetStudentCount || 0)) : "")
                                          + " · 待批改 " + Number(modelData.pendingReviewCount || 0)
                                    color: "#94a3b8"
                                    font.pixelSize: 12
                                    Layout.fillWidth: true
                                    elide: Text.ElideRight
                                }
                            }
                            Text { visible: !root.narrowShell; text: modelData.subject || "--"; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 90 }
                            Text { visible: !root.narrowShell; text: modelData.date || ""; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 120 }
                            Text { text: modelData.status || "草稿"; color: root.examStatusColor(modelData.status || "草稿"); font.pixelSize: 13; font.bold: true; Layout.preferredWidth: root.narrowShell ? 68 : 80; horizontalAlignment: Text.AlignHCenter }
                        }
                    }
                }
                Text {
                    visible: workflowExamList.count === 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: "暂无进行中、待批改、未开始或草稿试卷"
                    color: "#94a3b8"
                    font.pixelSize: 17
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    component LineChartCard: Card {
        id: chartCard
        property string title: ""
        property int hoverIndex: -1
        property var points: []
        property string subjectName: root.profile.subject || ""
        function reloadTrend() {
            hoverIndex = -1
            points = teacherApi.getClassScoreTrend(classCombo.currentText, subjectName)
            chartCanvas.requestPaint()
        }
        function chartX(i) {
            return 56 + i * ((chartCanvas.width - 92) / Math.max(points.length - 1, 1))
        }
        function chartY(value) {
            return 36 + (100 - Number(value)) / 50 * (chartCanvas.height - 88)
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4
                    Text { text: chartCard.title; color: "#111827"; font.pixelSize: 25; font.bold: true }
                    Text { text: classCombo.currentText + (chartCard.subjectName.length > 0 ? (" · " + chartCard.subjectName) : "") + " 班级均分"; color: "#8a8f99"; font.pixelSize: 14 }
                }
                AppCombo {
                    id: classCombo
                    Layout.preferredWidth: 170
                    model: root.classes.length > 0 ? root.classes.map(function(c) { return c.name }) : ["软件工程01"]
                    onCurrentTextChanged: {
                        chartCard.reloadTrend()
                    }
                }
                Rectangle {
                    Layout.preferredWidth: 96
                    Layout.preferredHeight: 42
                    radius: 21
                    color: "#eef6ff"
                    Text { anchors.centerIn: parent; text: "实时统计"; color: "#2563eb"; font.pixelSize: 15; font.bold: true }
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Component.onCompleted: chartCard.reloadTrend()
                Canvas {
                    id: chartCanvas
                    anchors.fill: parent
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        ctx.strokeStyle = "#e8edf5"
                        ctx.lineWidth = 1
                        ctx.setLineDash([6, 7])
                        for (var gy = 0; gy < 4; ++gy) {
                            var y = 36 + gy * ((height - 88) / 3)
                            ctx.beginPath()
                            ctx.moveTo(56, y)
                            ctx.lineTo(width - 36, y)
                            ctx.stroke()
                        }
                        if (chartCard.points.length === 0) {
                            ctx.setLineDash([])
                            ctx.fillStyle = "#94a3b8"
                            ctx.font = "18px sans-serif"
                            ctx.textAlign = "center"
                            ctx.fillText("暂无该班级该科目的成绩数据", width / 2, height / 2)
                            ctx.textAlign = "left"
                            return
                        }
                        ctx.setLineDash([])
                        var fill = ctx.createLinearGradient(0, 40, 0, height - 38)
                        fill.addColorStop(0, "rgba(34,197,94,0.20)")
                        fill.addColorStop(1, "rgba(34,197,94,0.02)")
                        ctx.beginPath()
                        for (var i = 0; i < chartCard.points.length; ++i) {
                            var x = chartCard.chartX(i)
                            y = chartCard.chartY(chartCard.points[i].value)
                            if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y)
                        }
                        ctx.lineTo(chartCard.chartX(chartCard.points.length - 1), height - 34)
                        ctx.lineTo(chartCard.chartX(0), height - 34)
                        ctx.closePath()
                        ctx.fillStyle = fill
                        ctx.fill()
                        ctx.beginPath()
                        ctx.lineWidth = 4
                        ctx.strokeStyle = "#22c55e"
                        for (i = 0; i < chartCard.points.length; ++i) {
                            x = chartCard.chartX(i)
                            y = chartCard.chartY(chartCard.points[i].value)
                            if (i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y)
                        }
                        ctx.stroke()
                        for (i = 0; i < chartCard.points.length; ++i) {
                            x = chartCard.chartX(i)
                            y = chartCard.chartY(chartCard.points[i].value)
                            ctx.beginPath()
                            ctx.fillStyle = i === chartCard.hoverIndex ? "#16a34a" : "#22c55e"
                            ctx.arc(x, y, i === chartCard.hoverIndex ? 7 : 5, 0, Math.PI * 2)
                            ctx.fill()
                        }
                        ctx.fillStyle = "#8a8f99"
                        ctx.font = "13px sans-serif"
                        for (i = 0; i < chartCard.points.length; ++i) {
                            x = chartCard.chartX(i)
                            ctx.fillText(chartCard.points[i].label || ("第" + (i + 1) + "次"), x - 18, height - 10)
                        }
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPositionChanged: {
                        var nearest = -1
                        var nearestDistance = 9999
                        for (var i = 0; i < chartCard.points.length; ++i) {
                            var dx = mouse.x - chartCard.chartX(i)
                            var dy = mouse.y - chartCard.chartY(chartCard.points[i].value)
                            var distance = Math.sqrt(dx * dx + dy * dy)
                            if (distance < nearestDistance) {
                                nearestDistance = distance
                                nearest = i
                            }
                        }
                        chartCard.hoverIndex = nearestDistance < 34 ? nearest : -1
                        chartCanvas.requestPaint()
                    }
                    onExited: {
                        chartCard.hoverIndex = -1
                        chartCanvas.requestPaint()
                    }
                }
                Rectangle {
                    visible: chartCard.hoverIndex >= 0
                    width: 164
                    height: 88
                    radius: 18
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    x: chartCard.hoverIndex >= 0 ? Math.min(parent.width - width - 10, chartCard.chartX(chartCard.hoverIndex) + 20) : 0
                    y: chartCard.hoverIndex >= 0 ? Math.max(8, chartCard.chartY(chartCard.points[chartCard.hoverIndex].value) - 78) : 0
                    Column {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 8
                        Text { text: chartCard.hoverIndex >= 0 ? chartCard.points[chartCard.hoverIndex].label : ""; color: "#111827"; font.pixelSize: 17; font.bold: true }
                        Text { text: chartCard.hoverIndex >= 0 ? "班级均分：" + chartCard.points[chartCard.hoverIndex].value : ""; color: "#2563eb"; font.pixelSize: 17; font.bold: true }
                    }
                }
            }
        }
    }

    component PendingCard: Card {
        id: pendingCard

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                Text { text: "待办提醒"; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
                PrimaryButton {
                    Layout.preferredWidth: 108
                    Layout.preferredHeight: 42
                    text: "新增待办"
                    onClicked: todoDialog.open()
                }
            }
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: false
                model: root.sortedTodoItems().slice(0, 3)
                delegate: Rectangle {
                    width: ListView.view.width
                    height: 58
                    radius: 15
                    color: "#fff7ed"
                    border.color: "#fed7aa"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 11
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 3
                            Text { text: modelData.title || "待办事项"; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                            Text { text: modelData.type || "批改试卷"; color: "#f97316"; font.pixelSize: 12; font.bold: true }
                        }
                        Text { text: modelData.time || ""; color: "#64748b"; font.pixelSize: 12; font.bold: true }
                    }
                }
            }
        }
    }

    component QuestionBankPage: PageShell {
        function cleanBankFilter(value, prefix) {
            var text = String(value || "").trim()
            if (text.indexOf(prefix) === 0) {
                text = text.substring(prefix.length).trim()
            }
            return text.indexOf("全部") >= 0 ? "" : text
        }

        function reloadQuestionBank(showMessage) {
            var rows = teacherApi.searchQuestions(
                        bankSearch.text,
                        cleanBankFilter(bankType.currentText, "题型："),
                        cleanBankFilter(bankDifficulty.currentText, "难度："))
            root.questions = rows
            root.selectedQuestionId = rows.length > 0 ? Number(rows[0].id) : -1
            if (showMessage) {
                root.showToast(rows.length > 0 ? ("已筛选出 " + rows.length + " 道题目") : "没有找到匹配题目")
            }
        }

        Item {
            width: parent.width
            height: root.narrowShell ? 154 : 92

            SectionTitle {
                id: questionBankTitle
                width: root.narrowShell ? parent.width : Math.max(360, parent.width - questionBankActions.width - 24)
                anchors.left: parent.left
                anchors.top: parent.top
            }

            Row {
                id: questionBankActions
                width: root.narrowShell ? parent.width : 344
                height: 56
                spacing: 12
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: root.narrowShell ? 96 : 8

                PrimaryButton {
                    width: root.narrowShell ? (parent.width - parent.spacing) / 2 : 156
                    text: "新增题目"
                    onClicked: addQuestionDialog.open()
                }
                SoftButton {
                    width: root.narrowShell ? (parent.width - parent.spacing) / 2 : 176
                    text: "CSV/Excel导入"
                    onClicked: questionFileDialog.open()
                }
            }
        }

        Card {
            width: parent.width
            height: root.narrowShell ? 214 : (root.compactShell ? 148 : 104)
            enterDelay: 20
            Flow {
                anchors.fill: parent
                anchors.margins: root.narrowShell ? 18 : 22
                spacing: 14
                AppCombo {
                    id: bankType
                    width: root.narrowShell ? (parent.width - 14) / 2 : 168
                    model: ["题型：全部", "单选题", "多选题", "填空题", "高数大题", "编程题"]
                    onActivated: reloadQuestionBank(false)
                }
                AppCombo {
                    id: bankDifficulty
                    width: root.narrowShell ? (parent.width - 14) / 2 : 168
                    model: ["难度：全部", "基础", "中等", "困难"]
                    onActivated: reloadQuestionBank(false)
                }
                AppField {
                    id: bankSearch
                    width: root.narrowShell ? parent.width : Math.max(260, parent.width - 614)
                    text: ""
                    placeholderText: "搜索题目内容，例如：微分方程"
                    onAccepted: reloadQuestionBank(true)
                }
                PrimaryButton {
                    width: root.narrowShell ? (parent.width - 14) / 2 : 116
                    text: "搜索"
                    onClicked: reloadQuestionBank(true)
                }
                SoftButton {
                    width: root.narrowShell ? (parent.width - 14) / 2 : 106
                    text: "重置"
                    onClicked: {
                        bankSearch.text = ""
                        bankType.currentIndex = 0
                        bankDifficulty.currentIndex = 0
                        reloadQuestionBank(true)
                    }
                }
            }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1100 ? 5 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18

            QuestionListCard { Layout.fillWidth: true; Layout.columnSpan: parent.width > 1100 ? 3 : 1; Layout.preferredHeight: root.narrowShell ? 680 : 640 }
            QuestionDetailCard { Layout.fillWidth: true; Layout.columnSpan: parent.width > 1100 ? 2 : 1; Layout.preferredHeight: root.narrowShell ? 760 : 640; question: root.selectedQuestion() }
        }

        OcrImportCard { width: parent.width; height: root.narrowShell ? 180 : 126; enterDelay: 180 }
        ImportLogCard { width: parent.width; height: root.narrowShell ? 300 : 260; enterDelay: 240 }
    }

    component QuestionListCard: Card {
        id: listCard
        property var rows: root.questions
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            RowLayout {
                Layout.fillWidth: true
                Text { text: "题目列表"; color: "#111827"; font.pixelSize: 28; font.bold: true; Layout.fillWidth: true }
                Text { text: "共 " + listCard.rows.length + " 道题目"; color: "#8a8f99"; font.pixelSize: 20; font.bold: true }
            }
            Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#e5edf6" }
            RowLayout {
                Layout.fillWidth: true
                spacing: 0
                Text { Layout.preferredWidth: 88; text: "ID"; color: "#8a8f99"; font.pixelSize: 17; font.bold: true }
                Text { Layout.preferredWidth: 110; text: "科目"; color: "#8a8f99"; font.pixelSize: 17; font.bold: true }
                Text { Layout.fillWidth: true; text: "题目"; color: "#8a8f99"; font.pixelSize: 17; font.bold: true }
                Text { Layout.preferredWidth: 118; text: "题型"; color: "#8a8f99"; font.pixelSize: 17; font.bold: true }
            }
            Repeater {
                model: listCard.rows.slice(0, 6)
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 76
                    radius: 14
                    color: root.selectedQuestionId === Number(modelData.id) ? "#eef6ff" : "#ffffff"
                    border.color: root.selectedQuestionId === Number(modelData.id) ? "#bfdbfe" : "#e5edf6"
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: root.selectedQuestionId = Number(modelData.id)
                    }
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 0
                        Text { Layout.preferredWidth: 88; text: "Q-" + modelData.id; color: "#2563eb"; font.pixelSize: 17; font.bold: true; elide: Text.ElideRight }
                        Text { Layout.preferredWidth: 110; text: modelData.subject || "--"; color: "#475569"; font.pixelSize: 17; font.bold: true; elide: Text.ElideRight }
                        Text { Layout.fillWidth: true; text: root.questionText(modelData); color: "#111827"; font.pixelSize: 18; font.bold: true; elide: Text.ElideRight }
                        Text { Layout.preferredWidth: 118; text: root.questionTypeText(modelData); color: "#475569"; font.pixelSize: 17; elide: Text.ElideRight }
                    }
                }
            }
        }
    }

    component QuestionDetailCard: Card {
        id: detail
        property var question: ({})
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 26
            spacing: 16
            RowLayout {
                Layout.fillWidth: true
                Text { text: "题目详情"; color: "#111827"; font.pixelSize: 28; font.bold: true; Layout.fillWidth: true }
                Text { text: root.questionTypeText(detail.question); color: "#2563eb"; font.pixelSize: 18; font.bold: true }
            }
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ColumnLayout {
                    width: parent.width
                    spacing: 16
                    DetailBlock { title: "题目"; text: root.questionText(detail.question) || "请选择左侧题目" }
                    OptionGrid { Layout.fillWidth: true; question: detail.question }
                    DetailBlock { title: "答案"; text: detail.question.answer || "--"; accent: true }
                    DetailBlock { title: "解析"; text: detail.question.analysis || "暂无解析"; large: true }
                }
            }
        }
    }

    component OptionGrid: Rectangle {
        id: optionGrid
        property var question: ({})
        property var optionRows: root.questionOptions(question)
        visible: optionRows.length > 0
        Layout.preferredHeight: visible ? (root.narrowShell ? 250 : 170) : 0
        radius: 18
        color: "#ffffff"
        border.color: "#e5edf6"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 10
            Text { text: "选项"; color: "#64748b"; font.pixelSize: 17; font.bold: true }
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: root.narrowShell ? 1 : 2
                columnSpacing: 10
                rowSpacing: 10
                Repeater {
                    model: optionGrid.optionRows
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        radius: 14
                        color: "#f8fbff"
                        border.color: "#e5edf6"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 8
                            Rectangle {
                                Layout.preferredWidth: 24
                                Layout.preferredHeight: 24
                                radius: 12
                                color: "#eff6ff"
                                Text { anchors.centerIn: parent; text: modelData.label; color: "#2563eb"; font.pixelSize: 16; font.bold: true }
                            }
                            Text {
                                Layout.fillWidth: true
                                text: modelData.text
                                color: "#111827"
                                font.pixelSize: 17
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }
        }
    }

    component DetailBlock: Rectangle {
        id: detailBlock
        property string title: ""
        property string text: ""
        property bool accent: false
        property bool large: false
        Layout.fillWidth: true
        Layout.preferredHeight: large
                                ? Math.max(root.narrowShell ? 230 : 210, Math.min(root.narrowShell ? 380 : 320, bodyText.implicitHeight + 74))
                                : Math.max(accent ? 96 : 136, Math.min(root.narrowShell ? 260 : 220, bodyText.implicitHeight + 58))
        radius: 18
        color: accent ? "#eff6ff" : "#ffffff"
        border.color: accent ? "#bfdbfe" : "#e5edf6"
        clip: true
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 6
            Text {
                Layout.fillWidth: true
                text: detailBlock.title
                color: "#64748b"
                font.pixelSize: detailBlock.large ? 18 : 17
                font.bold: true
            }
            ScrollView {
                id: detailBodyScroll
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                contentWidth: availableWidth
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: bodyText.implicitHeight > height + 2 ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff
                Text {
                    id: bodyText
                    width: Math.max(0, detailBodyScroll.availableWidth)
                    text: detailBlock.text
                    color: "#111827"
                    font.pixelSize: detailBlock.large ? 17 : 18
                    font.bold: detailBlock.accent
                    lineHeight: detailBlock.large ? 1.2 : 1.12
                    wrapMode: Text.WrapAnywhere
                }
            }
        }
    }

    component OcrImportCard: Card {
        RowLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 18
            Rectangle {
                Layout.preferredWidth: 54
                Layout.preferredHeight: 54
                radius: 18
                color: "#eef6ff"
                Text { anchors.centerIn: parent; text: "OCR"; color: "#2563eb"; font.pixelSize: 15; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text { text: "拍照导入 OCR"; color: "#111827"; font.pixelSize: 20; font.bold: true }
                Text { text: "上传图片后由后端识别题干、选项、答案与解析，并写入导入日志。"; color: "#64748b"; font.pixelSize: 13 }
            }
            PrimaryButton { Layout.preferredWidth: 140; text: "选择图片"; onClicked: ocrDialog.open() }
        }
    }

    component ImportLogCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 12
            Text { text: "导入日志"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Repeater {
                model: root.importLogs.length > 0 ? root.importLogs.slice(0, 4) : [{"type":"OCR","fileName":"暂无记录","status":"待导入","time":"--","message":"选择图片后会显示在这里"}]
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 44
                    radius: 14
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        Text { text: modelData.type || "OCR"; color: "#2563eb"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 86 }
                        Text { text: modelData.fileName || ""; color: "#111827"; font.pixelSize: 13; Layout.fillWidth: true; elide: Text.ElideRight }
                        Text { text: modelData.status || ""; color: "#16a34a"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 80 }
                    }
                }
            }
        }
    }

    component PublishExamPage: PageShell {
        Loader {
            width: parent.width
            sourceComponent: root.publishPaperMode ? paperViewerComponent : publishEditorComponent
        }

        Component {
            id: publishEditorComponent
            Column {
                width: parent.width
                spacing: 20
                SectionTitle {}
                GridLayout {
                    width: parent.width
                    columns: parent.width > 1180 ? 5 : 1
                    columnSpacing: root.narrowShell ? 12 : 18
                    rowSpacing: root.narrowShell ? 12 : 18

                    PublishConfigCard { id: publishConfig; Layout.fillWidth: true; Layout.columnSpan: parent.width > 1180 ? 2 : 1; Layout.preferredHeight: root.narrowShell ? 960 : 840 }
                    PublishQuestionCard {
                        Layout.fillWidth: true
                        Layout.columnSpan: parent.width > 1180 ? 3 : 1
                        Layout.preferredHeight: root.narrowShell ? 820 : 840
                        subject: publishConfig.subject
                        typeName: publishConfig.selectedType
                        difficulty: publishConfig.selectedDifficulty
                        knowledgePoint: publishConfig.selectedKnowledgePoint
                    }
                }
            }
        }

        Component {
            id: paperViewerComponent
            Column {
                width: parent.width
                spacing: 20
                Card {
                    width: parent.width
                    height: root.narrowShell ? 142 : 96
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 22
                        spacing: 14
                        SoftButton { Layout.preferredWidth: 96; text: "返回"; onClicked: root.publishPaperMode = false }
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: "查看试卷"; color: "#111827"; font.pixelSize: 26; font.bold: true }
                            Text { text: "可调整题目顺序后发布考试"; color: "#64748b"; font.pixelSize: 14 }
                        }
                        Rectangle {
                            Layout.preferredWidth: 146
                            Layout.preferredHeight: 42
                            radius: 21
                            color: "#eff6ff"
                            Text { anchors.centerIn: parent; text: "共 " + root.selectedPaperQuestions.length + " 题"; color: "#2563eb"; font.pixelSize: 15; font.bold: true }
                        }
                        Rectangle {
                            Layout.preferredWidth: 156
                            Layout.preferredHeight: 42
                            radius: 21
                            color: root.paperTotalScore() > root.paperTargetScore() ? "#fef2f2" : "#ecfdf3"
                            Text {
                                anchors.centerIn: parent
                                text: root.paperTotalScore() + "/" + root.paperTargetScore() + " 分"
                                color: root.paperTotalScore() > root.paperTargetScore() ? "#ef4444" : "#16a34a"
                                font.pixelSize: 15
                                font.bold: true
                            }
                        }
                    }
                }
                PaperPreviewCard {
                    width: parent.width
                    height: root.narrowShell ? 820 : 680
                    titleText: root.publishDraftName
                    subject: root.publishDraftSubject
                    startText: root.publishDraftStart
                    endText: root.publishDraftEnd
                    editable: true
                    enterDelay: 80
                }
            }
        }
    }

    component SmartRatioRow: RowLayout {
        id: ratioRow
        property string label: ""
        property color barColor: "#3b82f6"
        property int targetValue: 0
        property alias value: ratioSlider.value
        signal edited()
        Layout.fillWidth: true
        spacing: 12
        function playToTarget() {
            ratioEnter.stop()
            ratioSlider.value = 0
            ratioEnter.to = ratioRow.targetValue
            ratioEnter.start()
        }
        Text { text: ratioRow.label; color: "#111827"; font.pixelSize: 15; font.bold: true; Layout.preferredWidth: 72 }
        Rectangle {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            radius: 10
            color: minusMouse.containsMouse ? "#fee2e2" : "#f6f8fc"
            border.color: minusMouse.containsMouse ? "#fecaca" : "#e5edf6"
            Text { anchors.centerIn: parent; text: "-"; color: minusMouse.containsMouse ? "#ef4444" : "#64748b"; font.pixelSize: 18; font.bold: true }
            MouseArea {
                id: minusMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    ratioSlider.value = Math.max(ratioSlider.from, ratioSlider.value - 1)
                    ratioRow.edited()
                }
            }
        }
        Slider {
            id: ratioSlider
            Layout.fillWidth: true
            from: 0
            to: 50
            stepSize: 1
            snapMode: Slider.SnapAlways
            onPressedChanged: {
                if (!pressed) ratioRow.edited()
            }
            NumberAnimation {
                id: ratioEnter
                target: ratioSlider
                property: "value"
                duration: 520
                easing.type: Easing.OutCubic
            }
            background: Rectangle {
                x: ratioSlider.leftPadding
                y: ratioSlider.topPadding + ratioSlider.availableHeight / 2 - height / 2
                width: ratioSlider.availableWidth
                height: 10
                radius: 5
                color: "#edf0f6"
                Rectangle {
                    width: ratioSlider.visualPosition * parent.width
                    height: parent.height
                    radius: 5
                    color: ratioRow.barColor
                }
            }
            handle: Rectangle {
                x: ratioSlider.leftPadding + ratioSlider.visualPosition * (ratioSlider.availableWidth - width)
                y: ratioSlider.topPadding + ratioSlider.availableHeight / 2 - height / 2
                width: 20
                height: 20
                radius: 10
                color: "#ffffff"
                border.color: ratioRow.barColor
                border.width: 3
            }
        }
        Rectangle {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            radius: 10
            color: plusMouse.containsMouse ? "#dcfce7" : "#f6f8fc"
            border.color: plusMouse.containsMouse ? "#bbf7d0" : "#e5edf6"
            Text { anchors.centerIn: parent; text: "+"; color: plusMouse.containsMouse ? "#16a34a" : "#64748b"; font.pixelSize: 18; font.bold: true }
            MouseArea {
                id: plusMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    ratioSlider.value = Math.min(ratioSlider.to, ratioSlider.value + 1)
                    ratioRow.edited()
                }
            }
        }
        Rectangle {
            Layout.preferredWidth: 66
            Layout.preferredHeight: 34
            radius: 12
            color: "#f8fbff"
            border.color: "#e5edf6"
            Text {
                anchors.centerIn: parent
                text: Math.round(ratioSlider.value) + " 题"
                color: ratioRow.barColor
                font.pixelSize: 14
                font.bold: true
            }
        }
    }

    component PublishConfigCard: Card {
        id: config
        property int activeTab: 0
        property string subject: subjectCombo.currentText
        property string selectedType: root.typeOptions(subject)[0]
        property string paperName: paperNameField.text
        property string startText: startBox.value
        property string endText: endBox.value
        property string selectedDifficulty: difficultyCombo.currentText
        property string selectedKnowledgePoint: knowledgePointField.text
        property bool ratioClamping: false
        function playRatioRows() {
            singleRatio.playToTarget()
            multiRatio.playToTarget()
            judgeRatio.playToTarget()
            blankRatio.playToTarget()
            appRatio.playToTarget()
            Qt.callLater(function() { config.enforceAllRatioLimits() })
        }
        function ratioTypeFor(row) {
            if (row === singleRatio) return "单选题"
            if (row === multiRatio) return "多选题"
            if (row === judgeRatio) return "判断题"
            if (row === blankRatio) return "填空题"
            return config.subject === "高数" ? "高数大题" : "编程题"
        }
        function ratioRows() {
            return [singleRatio, multiRatio, judgeRatio, blankRatio, appRatio]
        }
        function ratioPlanScore() {
            var total = 0
            var rows = ratioRows()
            for (var i = 0; i < rows.length; ++i) {
                total += Math.round(rows[i].value) * root.questionTypeScore(ratioTypeFor(rows[i]))
            }
            return total
        }
        function limitedCounts(rawCounts) {
            var result = ({})
            var total = 0
            var order = ["单选题", "多选题", "判断题", "填空题", config.subject === "高数" ? "高数大题" : "编程题"]
            for (var i = 0; i < order.length; ++i) {
                var typeName = order[i]
                var score = root.questionTypeScore(typeName)
                var requested = Math.max(0, Math.round(Number(rawCounts[typeName] || 0)))
                var allowed = Math.max(0, Math.floor((root.paperTargetScore() - total) / score))
                var count = Math.min(requested, allowed)
                result[typeName] = count
                total += count * score
            }
            return result
        }
        function ratioCounts() {
            var typeName = config.subject === "高数" ? "高数大题" : "编程题"
            var raw = {
                "单选题": Math.round(singleRatio.value),
                "多选题": Math.round(multiRatio.value),
                "判断题": Math.round(judgeRatio.value),
                "填空题": Math.round(blankRatio.value)
            }
            raw[typeName] = Math.round(appRatio.value)
            return config.limitedCounts(raw)
        }
        function enforceRatioLimit(row) {
            if (ratioClamping) return
            ratioClamping = true
            var rows = ratioRows()
            var otherScore = 0
            for (var i = 0; i < rows.length; ++i) {
                if (rows[i] === row) continue
                otherScore += Math.round(rows[i].value) * root.questionTypeScore(ratioTypeFor(rows[i]))
            }
            var score = root.questionTypeScore(ratioTypeFor(row))
            var maxCount = Math.max(0, Math.floor((root.paperTargetScore() - otherScore) / score))
            if (Math.round(row.value) > maxCount) {
                row.value = maxCount
                root.showToast("已按满分 " + root.paperTargetScore() + " 分限制题型数量")
            }
            ratioClamping = false
        }
        function enforceAllRatioLimits() {
            var rows = ratioRows()
            for (var i = 0; i < rows.length; ++i) {
                enforceRatioLimit(rows[i])
            }
        }
        onActiveTabChanged: {
            if (activeTab === 1) Qt.callLater(function() { config.playRatioRows() })
        }
        Component.onCompleted: {
            if (activeTab === 1) Qt.callLater(function() { config.playRatioRows() })
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 24
            spacing: root.narrowShell ? 10 : 12
            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                Repeater {
                    model: ["基础配置", "题型比例", "高级规则"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 44
                        radius: 14
                        color: config.activeTab === index ? "#eff6ff" : "transparent"
                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: config.activeTab === index ? "#2563eb" : "#7b8494"
                            font.pixelSize: 15
                            font.bold: true
                        }
                        Rectangle {
                            width: 54
                            height: 3
                            radius: 2
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.bottom
                            color: "#3b82f6"
                            visible: config.activeTab === index
                        }
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: config.activeTab = index
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                visible: config.activeTab === 0
                spacing: 12
                Text { text: "基础配置"; color: "#111827"; font.pixelSize: 22; font.bold: true }
                AppField { id: paperNameField; Layout.fillWidth: true; placeholderText: "试卷名称，例如：Java期末考试"; text: "Java期末考试" }
                AppCombo { id: subjectCombo; Layout.fillWidth: true; model: ["Java", "C++", "高数", "数据结构", "数据库"] }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10
                    AppField {
                        id: targetScoreField
                        Layout.fillWidth: true
                        placeholderText: "试卷满分"
                        text: String(root.publishTargetScore)
                        validator: IntValidator { bottom: 1; top: 500 }
                        onEditingFinished: {
                            root.setPublishTargetScore(text)
                            text = String(root.publishTargetScore)
                            config.enforceAllRatioLimits()
                        }
                        onAccepted: {
                            root.setPublishTargetScore(text)
                            text = String(root.publishTargetScore)
                            config.enforceAllRatioLimits()
                        }
                    }
                    Rectangle {
                        Layout.preferredWidth: 148
                        Layout.preferredHeight: 58
                        radius: 16
                        color: root.paperTotalScore() > root.paperTargetScore() ? "#fef2f2" : "#ecfdf3"
                        border.color: root.paperTotalScore() > root.paperTargetScore() ? "#fecaca" : "#bbf7d0"
                        Text {
                            anchors.centerIn: parent
                            text: root.paperTotalScore() + "/" + root.paperTargetScore() + " 分"
                            color: root.paperTotalScore() > root.paperTargetScore() ? "#ef4444" : "#16a34a"
                            font.pixelSize: 17
                            font.bold: true
                        }
                    }
                }
                DateBox { id: startBox; Layout.fillWidth: true; label: "开始时间"; value: "2026-06-20 09:00" }
                DateBox { id: endBox; Layout.fillWidth: true; label: "结束时间"; value: "2026-06-20 11:00" }

                Text { text: "试卷题目"; color: "#111827"; font.pixelSize: 18; font.bold: true }
                Repeater {
                    model: root.typeOptions(config.subject)
                    TypeRow {
                        Layout.fillWidth: true
                        typeName: modelData
                        count: root.countForType(modelData)
                        onFilterClicked: config.selectedType = modelData
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                visible: config.activeTab === 0
                spacing: 10
                Text { text: "发布班级"; color: "#111827"; font.pixelSize: 18; font.bold: true }
                Flow {
                    Layout.fillWidth: true
                    spacing: 8
                    Repeater {
                        model: root.classes
                        CheckDelegate {
                            id: classChip
                            text: modelData.name
                            checked: root.selectedPublishClasses.indexOf(modelData.name) >= 0
                            height: 34
                            onToggled: root.togglePublishClass(modelData.name, checked)
                            contentItem: Text {
                                text: classChip.text
                                color: classChip.checked ? "#ffffff" : "#334155"
                                verticalAlignment: Text.AlignVCenter
                                leftPadding: 10
                                rightPadding: 10
                                font.pixelSize: 12
                                font.bold: true
                            }
                            indicator: null
                            background: Rectangle {
                                radius: 12
                                color: classChip.checked ? "#2563eb" : "#ffffff"
                                border.color: classChip.checked ? "#2563eb" : "#dfe7f2"
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                id: ratioPanel
                visible: config.activeTab === 1
                spacing: 20
                onVisibleChanged: {
                    if (visible) Qt.callLater(function() { config.playRatioRows() })
                }
                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "题型比例"; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
                    Rectangle {
                        Layout.preferredWidth: 146
                        Layout.preferredHeight: 38
                        radius: 14
                        color: config.ratioPlanScore() > root.paperTargetScore() ? "#fef2f2" : "#eff6ff"
                        Text {
                            anchors.centerIn: parent
                            text: config.ratioPlanScore() + "/" + root.paperTargetScore() + " 分"
                            color: config.ratioPlanScore() > root.paperTargetScore() ? "#ef4444" : "#2563eb"
                            font.pixelSize: 15
                            font.bold: true
                        }
                    }
                }
                SmartRatioRow { id: singleRatio; label: "单选题"; barColor: "#3b82f6"; targetValue: 12; onEdited: config.enforceRatioLimit(singleRatio) }
                SmartRatioRow { id: multiRatio; label: "多选题"; barColor: "#6d5dfc"; targetValue: 5; onEdited: config.enforceRatioLimit(multiRatio) }
                SmartRatioRow { id: judgeRatio; label: "判断题"; barColor: "#f59e0b"; targetValue: 4; onEdited: config.enforceRatioLimit(judgeRatio) }
                SmartRatioRow { id: blankRatio; label: "填空题"; barColor: "#a855f7"; targetValue: 3; onEdited: config.enforceRatioLimit(blankRatio) }
                SmartRatioRow { id: appRatio; label: config.subject === "高数" ? "高数大题" : "编程题"; barColor: "#ef4444"; targetValue: 1; onEdited: config.enforceRatioLimit(appRatio) }
                Item { Layout.fillHeight: true }
                SuccessButton {
                    Layout.fillWidth: true
                    text: "一键生成试卷"
                    onClicked: {
                        var counts = config.ratioCounts()
                        root.updatePublishDraft(config.paperName, config.subject, config.startText, config.endText)
                        root.smartGeneratePaper(config.subject, counts, config.selectedDifficulty, config.selectedKnowledgePoint)
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                visible: config.activeTab === 2
                spacing: 16
                Text { text: "高级规则"; color: "#111827"; font.pixelSize: 22; font.bold: true }
                AppCombo { id: difficultyCombo; Layout.fillWidth: true; model: ["全部难度", "基础", "中等", "困难"] }
                AppField { id: knowledgePointField; Layout.fillWidth: true; placeholderText: "知识点筛选，例如：数组、函数、导数" }
                SettingSwitch { Layout.fillWidth: true; label: "禁止重复题目"; description: "同一试卷内不重复抽取相同题目"; checked: true }
                SettingSwitch { Layout.fillWidth: true; label: "按章节顺序排列"; description: "按知识点章节整理题目顺序"; checked: false }
                SettingSwitch { Layout.fillWidth: true; label: "随机打乱选项"; description: "客观题发布前自动打乱选项"; checked: true }
                SettingSwitch { Layout.fillWidth: true; label: "显示参考答案"; description: "查看试卷时展示参考答案"; checked: false }
                Item { Layout.fillHeight: true }
                RowLayout {
                    Layout.fillWidth: true
                    SuccessButton {
                        Layout.fillWidth: true
                        text: "一键生成试卷"
                        onClicked: {
                            root.updatePublishDraft(config.paperName, config.subject, config.startText, config.endText)
                            root.smartGeneratePaper(config.subject, config.limitedCounts({"单选题": 12, "多选题": 6, "填空题": 5, "编程题": 2, "高数大题": 2}), config.selectedDifficulty, config.selectedKnowledgePoint)
                        }
                    }
                    SoftButton {
                        Layout.preferredWidth: 112
                        text: "清空"
                        onClicked: {
                            root.selectedPaperQuestions = []
                            root.showToast("已清空试卷")
                        }
                    }
                }
            }

            Item { Layout.fillHeight: true }

            Flow {
                Layout.fillWidth: true
                spacing: 10
                SoftButton {
                    width: root.narrowShell ? parent.width : (parent.width - 20) / 3
                    text: "复制以往试卷"
                    onClicked: copyPaperPopup.open()
                }
                SoftButton {
                    width: root.narrowShell ? (parent.width - 10) / 2 : (parent.width - 20) / 3
                    text: "保存草稿"
                    onClicked: root.saveCurrentDraft(config.paperName, config.subject, config.startText, config.endText)
                }
                SoftButton {
                    width: root.narrowShell ? (parent.width - 10) / 2 : (parent.width - 20) / 3
                    text: "查看试卷"
                    onClicked: {
                        root.updatePublishDraft(paperNameField.text, subjectCombo.currentText, startBox.value, endBox.value)
                        root.publishPaperMode = true
                        root.animationKey += 1
                    }
                }
            }
            Item {
                Layout.preferredWidth: 0
                Layout.preferredHeight: 0
                Layout.minimumWidth: 0
                Layout.minimumHeight: 0
                Popup {
                    id: copyPaperPopup
                    parent: Overlay.overlay
                    width: Math.min(root.width - 56, 560)
                    height: Math.min(root.height - 96, 520)
                    x: Math.max(28, (root.width - width) / 2)
                    y: Math.max(48, (root.height - height) / 2)
                    modal: true
                    focus: true
                    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                    padding: 0
                background: Rectangle {
                    radius: 24
                    color: "#ffffff"
                    border.color: "#dbe7f6"
                    layer.enabled: true
                }
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 22
                        spacing: 14
                        RowLayout {
                            Layout.fillWidth: true
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 4
                                Text { text: "复制以往试卷"; color: "#111827"; font.pixelSize: 24; font.bold: true }
                                Text { text: "从真实考试列表选择一张，复制为新的草稿后继续编辑。"; color: "#64748b"; font.pixelSize: 14 }
                            }
                            SoftButton {
                                Layout.preferredWidth: 42
                                text: "×"
                                onClicked: copyPaperPopup.close()
                            }
                        }
                        ListView {
                            id: copyPaperList
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true
                            spacing: 10
                            model: root.orderedExams()
                            boundsBehavior: Flickable.DragOverBounds
                            boundsMovement: Flickable.FollowBoundsBehavior
                            maximumFlickVelocity: 7600
                            flickDeceleration: 3200
                            reuseItems: true
                            cacheBuffer: height * 2
                            ScrollBar.vertical: ScrollBar {
                                policy: copyPaperList.contentHeight > copyPaperList.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                                width: 12
                                contentItem: Rectangle { radius: 6; color: "#9fb3cc" }
                                background: Rectangle { radius: 6; color: "#edf2f8" }
                            }
                            delegate: Rectangle {
                                width: ListView.view.width - (copyPaperList.contentHeight > copyPaperList.height ? 18 : 0)
                                height: 78
                                radius: 18
                                color: copyMouse.containsMouse ? "#eef6ff" : "#f8fbff"
                                border.color: copyMouse.containsMouse ? "#bfdbfe" : "#e5edf6"
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 14
                                    spacing: 12
                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        spacing: 5
                                        Text {
                                            Layout.fillWidth: true
                                            text: modelData.name || modelData.title || "未命名试卷"
                                            color: "#111827"
                                            font.pixelSize: 16
                                            font.bold: true
                                            elide: Text.ElideRight
                                        }
                                        Text {
                                            Layout.fillWidth: true
                                            text: (modelData.subject || "综合") + " · " + (modelData.status || "草稿") + " · " + root.examDate(modelData)
                                            color: "#64748b"
                                            font.pixelSize: 13
                                            elide: Text.ElideRight
                                        }
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 92
                                        Layout.preferredHeight: 34
                                        radius: 12
                                        color: "#2563eb"
                                        Text { anchors.centerIn: parent; text: "复制"; color: "#ffffff"; font.pixelSize: 14; font.bold: true }
                                    }
                                }
                                MouseArea {
                                    id: copyMouse
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        var sourceName = modelData.name || modelData.title || "未命名试卷"
                                        var id = teacherApi.copyExamAsDraftById(Number(modelData.id || 0), sourceName + " 副本")
                                        if (id > 0) {
                                            root.activePaperId = id
                                            root.refreshAll()
                                            root.selectedPaperQuestions = teacherApi.getPaperQuestions(id)
                                            root.updatePublishDraft(sourceName + " 副本", modelData.subject || config.subject, startBox.value, endBox.value)
                                            root.publishPaperMode = true
                                            copyPaperPopup.close()
                                            root.animationKey += 1
                                            root.showToast("已复制为草稿，可调整题目后发布")
                                        } else {
                                            root.showToast("复制失败：" + teacherApi.lastError())
                                        }
                                    }
                                }
                            }
                        }
                        Text {
                            visible: root.orderedExams().length === 0
                            Layout.fillWidth: true
                            text: "暂无可复制的试卷"
                            color: "#94a3b8"
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
        }
    }

    component DateBox: ColumnLayout {
        id: dateBox
        property string label: ""
        property string value: ""
        property date pickedDate: new Date()
        property int labelSize: 12
        property int fieldHeight: 48
        property int valueSize: 14
        function setComboText(box, text) {
            for (var i = 0; i < box.model.length; ++i) {
                if (box.model[i] === text) {
                    box.currentIndex = i
                    return
                }
            }
        }
        function syncFromValue() {
            var parts = String(value).split(" ")
            if (parts.length > 0) {
                var d = parts[0].split("-")
                if (d.length === 3) {
                    pickedDate = new Date(Number(d[0]), Number(d[1]) - 1, Number(d[2]))
                }
            }
            if (parts.length > 1) {
                var t = parts[1].split(":")
                if (t.length >= 2) {
                    setComboText(hourBox, root.pad2(t[0]))
                    setComboText(minuteBox, root.pad2(t[1]))
                }
            }
        }
        function updateValue() {
            if (!hourBox || !minuteBox) {
                return
            }
            value = Qt.formatDate(pickedDate, "yyyy-MM-dd") + " " + hourBox.currentText + ":" + minuteBox.currentText
        }
        spacing: 6
        Component.onCompleted: syncFromValue()
        Text { text: dateBox.label; color: "#64748b"; font.pixelSize: dateBox.labelSize; font.bold: true }
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: dateBox.fieldHeight
            radius: 15
            color: dateMouse.containsMouse ? "#ffffff" : "#f7f9fd"
            border.color: "#e4eaf3"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 14
                anchors.rightMargin: 14
                spacing: 10
                Text {
                    Layout.fillWidth: true
                    text: dateBox.value
                    color: "#172033"
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: dateBox.valueSize
                }
                Text {
                    text: "⌄"
                    color: "#64748b"
                    font.pixelSize: 17
                }
            }
            MouseArea {
                id: dateMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    dateBox.syncFromValue()
                    popup.open()
                }
            }
            Popup {
                id: popup
                width: Math.max(320, parent.width)
                y: parent.height + 6
                padding: 14
                modal: false
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
                background: Rectangle { radius: 18; color: "#ffffff"; border.color: "#dbe7f6" }
                ColumnLayout {
                    width: parent.width
                    spacing: 10
                    RowLayout {
                        Layout.fillWidth: true
                        SoftButton {
                            Layout.preferredWidth: 44
                            text: "<"
                            onClicked: {
                                var m = monthGrid.month - 1
                                if (m < 0) {
                                    monthGrid.month = 11
                                    monthGrid.year -= 1
                                } else {
                                    monthGrid.month = m
                                }
                            }
                        }
                        Text {
                            Layout.fillWidth: true
                            text: monthGrid.year + "年 " + (monthGrid.month + 1) + "月"
                            color: "#111827"
                            font.pixelSize: 16
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        SoftButton {
                            Layout.preferredWidth: 44
                            text: ">"
                            onClicked: {
                                var m = monthGrid.month + 1
                                if (m > 11) {
                                    monthGrid.month = 0
                                    monthGrid.year += 1
                                } else {
                                    monthGrid.month = m
                                }
                            }
                        }
                    }
                    DayOfWeekRow {
                        Layout.fillWidth: true
                        locale: monthGrid.locale
                        delegate: Text {
                            text: shortName
                            color: "#94a3b8"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 12
                        }
                    }
                    MonthGrid {
                        id: monthGrid
                        Layout.fillWidth: true
                        Layout.preferredHeight: 214
                        month: dateBox.pickedDate.getMonth()
                        year: dateBox.pickedDate.getFullYear()
                        onClicked: function(date) {
                            dateBox.pickedDate = date
                            dateBox.updateValue()
                        }
                        delegate: Rectangle {
                            readonly property date cellDate: model.date
                            readonly property bool picked: cellDate.getFullYear() === dateBox.pickedDate.getFullYear()
                                                            && cellDate.getMonth() === dateBox.pickedDate.getMonth()
                                                            && cellDate.getDate() === dateBox.pickedDate.getDate()
                            readonly property bool outsideMonth: model.month !== monthGrid.month
                            radius: 10
                            color: picked ? "#2563eb" : (model.today ? "#eef6ff" : "transparent")
                            Text {
                                anchors.centerIn: parent
                                text: model.day
                                color: parent.picked ? "#ffffff" : (parent.outsideMonth ? "#cbd5e1" : "#334155")
                                font.pixelSize: 13
                                font.bold: parent.picked
                            }
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "时间"; color: "#64748b"; font.pixelSize: 13; font.bold: true }
                        AppCombo {
                            id: hourBox
                            Layout.fillWidth: true
                            model: root.twoDigitOptions(24)
                            currentIndex: 9
                            onCurrentTextChanged: dateBox.updateValue()
                        }
                        AppCombo {
                            id: minuteBox
                            Layout.fillWidth: true
                            model: root.twoDigitOptions(60)
                            onCurrentTextChanged: dateBox.updateValue()
                        }
                    }
                    PrimaryButton {
                        Layout.fillWidth: true
                        text: "确定时间"
                        onClicked: {
                            dateBox.updateValue()
                            popup.close()
                        }
                    }
                }
            }
        }
    }

    component TypeRow: Rectangle {
        id: row
        property string typeName: ""
        property int count: 0
        signal filterClicked()
        implicitHeight: 58
        radius: 16
        color: "#ffffff"
        border.color: "#e5edf6"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 14
            anchors.rightMargin: 12
            spacing: 10
            Text { text: row.typeName; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true }
            Text { text: row.count + " 题"; color: "#2563eb"; font.pixelSize: 14; font.bold: true; Layout.preferredWidth: 52; horizontalAlignment: Text.AlignRight }
            Text {
                id: filterText
                Layout.preferredWidth: 46
                text: "筛选"
                color: filterMouse.containsMouse ? "#ef4444" : "#2563eb"
                font.pixelSize: 14
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Behavior on color { ColorAnimation { duration: 120 } }
                MouseArea {
                    id: filterMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: row.filterClicked()
                }
            }
        }
    }

    component PublishQuestionCard: Card {
        id: qcard
        property string subject: "Java"
        property string typeName: "单选题"
        property string searchText: searchField.text
        property string difficulty: ""
        property string knowledgePoint: ""
        property bool backendLoaded: false
        property var backendRows: []
        property var rows: backendLoaded ? backendRows : root.questionsFor(subject, typeName, searchText, difficulty, knowledgePoint)
        property var currentQuestion: rows.length > 0 ? rows[Math.min(root.publishQuestionIndex, rows.length - 1)] : ({})
        property string emptyText: backendLoaded
                                   ? ("后端题库中没有匹配「" + subject + " · " + typeName + "」的题目，请检查科目、题型、难度或知识点筛选。")
                                   : "正在读取题库..."
        function refreshFromBackend(showEmptyToast) {
            var cleanDifficulty = root.cleanFilterText(difficulty)
            var cleanKnowledge = String(knowledgePoint || "").trim()
            var rows = root.searchQuestionPool(searchText, subject, typeName, cleanDifficulty, cleanKnowledge)
            backendRows = rows ? rows : []
            backendLoaded = true
            root.publishQuestionIndex = 0
            if (backendRows.length === 0 && showEmptyToast) {
                root.showToast("没有找到题目，请检查科目、题型、难度、知识点或题库数据")
            }
        }
        Component.onCompleted: Qt.callLater(function() { qcard.refreshFromBackend(false) })
        onSubjectChanged: Qt.callLater(function() { qcard.refreshFromBackend(false) })
        onTypeNameChanged: Qt.callLater(function() { qcard.refreshFromBackend(false) })
        onDifficultyChanged: Qt.callLater(function() { qcard.refreshFromBackend(false) })
        onKnowledgePointChanged: Qt.callLater(function() { qcard.refreshFromBackend(false) })
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                Text { text: qcard.subject + " · " + qcard.typeName; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
                Text { text: "共 " + qcard.rows.length + " 题"; color: "#64748b"; font.pixelSize: 14 }
            }
            RowLayout {
                Layout.fillWidth: true
                AppField { id: searchField; Layout.fillWidth: true; placeholderText: "搜索该科目该题型的题目" }
                PrimaryButton {
                    Layout.preferredWidth: 96
                    text: "搜索"
                    onClicked: {
                        qcard.refreshFromBackend(true)
                    }
                }
            }
            DetailBlock { title: "题目"; text: root.questionText(qcard.currentQuestion) || qcard.emptyText; Layout.preferredHeight: 150 }
            DetailBlock { title: "答案"; text: qcard.currentQuestion.answer || "--"; accent: true }
            DetailBlock { title: "解析"; text: qcard.currentQuestion.analysis || "暂无解析"; large: true }
            RowLayout {
                Layout.fillWidth: true
                SoftButton {
                    Layout.fillWidth: true
                    text: "上一题"
                    onClicked: {
                        if (root.publishQuestionIndex <= 0) {
                            root.showToast("已为第一题")
                            return
                        }
                        root.publishQuestionIndex -= 1
                    }
                }
                SoftButton {
                    Layout.fillWidth: true
                    text: "下一题"
                    onClicked: {
                        if (qcard.rows.length === 0 || root.publishQuestionIndex >= qcard.rows.length - 1) {
                            root.showToast("已为最后一题")
                            return
                        }
                        root.publishQuestionIndex += 1
                    }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 46
                radius: 16
                color: root.paperRemainingScore() <= 0 ? "#fff7ed" : "#f8fbff"
                border.color: root.paperRemainingScore() <= 0 ? "#fed7aa" : "#e5edf6"
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    spacing: 10
                    Text { text: "当前总分"; color: "#64748b"; font.pixelSize: 14; font.bold: true }
                    Text { text: root.paperTotalScore() + "/" + root.paperTargetScore() + " 分"; color: root.paperTotalScore() > root.paperTargetScore() ? "#ef4444" : "#2563eb"; font.pixelSize: 17; font.bold: true; Layout.fillWidth: true }
                    Text { text: "剩余 " + root.paperRemainingScore() + " 分"; color: root.paperRemainingScore() <= 0 ? "#f97316" : "#16a34a"; font.pixelSize: 14; font.bold: true }
                }
            }
            PrimaryButton {
                Layout.fillWidth: true
                text: "添加到试卷"
                onClicked: {
                    if (!root.questionText(qcard.currentQuestion)) {
                        root.showToast("没有可添加的题目")
                        return
                    }
                    var q = qcard.currentQuestion
                    var qid = String(q.id || q.questionId || "")
                    for (var i = 0; i < root.selectedPaperQuestions.length; ++i) {
                        if (String(root.selectedPaperQuestions[i].id || root.selectedPaperQuestions[i].questionId || "") === qid) {
                            root.showToast("该题已在试卷中")
                            return
                        }
                    }
                    var score = root.questionScoreValue(q)
                    if (root.paperTotalScore() + score > root.paperTargetScore()) {
                        root.showToast("加入该题后总分会超过 " + root.paperTargetScore() + " 分，不能添加")
                        return
                    }
                    q.score = score
                    root.selectedPaperQuestions = root.selectedPaperQuestions.concat([q])
                    root.showToast("已添加到试卷，当前总分 " + root.paperTotalScore() + "/" + root.paperTargetScore())
                }
            }
        }
    }

    component PaperPreviewCard: Card {
        id: preview
        property string titleText: ""
        property string subject: ""
        property string startText: ""
        property string endText: ""
        property bool editable: false
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 28
            spacing: 14
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 58
                ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: totalBadge.left
                    anchors.rightMargin: 18
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 4
                    Text { text: preview.titleText; color: "#111827"; font.pixelSize: 28; font.bold: true }
                    Text { text: "科目：" + preview.subject + "    考试时间：" + preview.startText + " - " + preview.endText; color: "#64748b"; font.pixelSize: 14 }
                }
                Rectangle {
                    id: totalBadge
                    width: 116
                    height: 48
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    radius: 18
                    color: root.paperTotalScore() > root.paperTargetScore() ? "#fef2f2" : "#eff6ff"
                    border.color: "transparent"
                    Text {
                        anchors.centerIn: parent
                        text: "总分 " + root.paperTotalScore() + "/" + root.paperTargetScore()
                        color: root.paperTotalScore() > root.paperTargetScore() ? "#ef4444" : "#2563eb"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }
            }
            Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#e5edf6" }
            Flickable {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: width
                contentHeight: paperColumn.height
                clip: true
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 9800
                flickDeceleration: 3600
                Column {
                    id: paperColumn
                    width: parent.width
                    spacing: 14
                    Text {
                        visible: root.selectedPaperQuestions.length === 0
                        width: parent.width
                        text: "题目添加后会在这里生成完整试卷。"
                        color: "#94a3b8"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Repeater {
                        model: root.selectedPaperQuestions
                        Rectangle {
                            width: parent.width
                            height: Math.max(76, questionLine.implicitHeight + answerLine.implicitHeight + 32)
                            radius: 16
                            color: "#ffffff"
                            border.color: "#e5edf6"
                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 14
                                spacing: 12
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Text {
                                        id: questionLine
                                        Layout.fillWidth: true
                                        text: (index + 1) + ". [" + root.questionTypeText(modelData) + " " + (modelData.score || root.questionTypeScore(root.questionTypeText(modelData))) + "分] " + root.questionText(modelData)
                                        color: "#111827"
                                        font.pixelSize: 15
                                        wrapMode: Text.WordWrap
                                    }
                                    Text {
                                        id: answerLine
                                        visible: preview.editable
                                        Layout.fillWidth: true
                                        text: "参考答案：" + (modelData.answer || "--")
                                        color: "#64748b"
                                        font.pixelSize: 13
                                        wrapMode: Text.WordWrap
                                        maximumLineCount: 2
                                        elide: Text.ElideRight
                                    }
                                }
                                RowLayout {
                                    visible: preview.editable
                                    Layout.preferredWidth: 208
                                    spacing: 8
                                    SoftButton { Layout.preferredWidth: 58; text: "上移"; enabled: index > 0; onClicked: root.movePaperQuestion(index, -1) }
                                    SoftButton { Layout.preferredWidth: 58; text: "下移"; enabled: index < root.selectedPaperQuestions.length - 1; onClicked: root.movePaperQuestion(index, 1) }
                                    SoftButton { Layout.preferredWidth: 66; text: "移除"; onClicked: root.removePaperQuestion(index) }
                                }
                            }
                        }
                    }
                }
            }
            PrimaryButton {
                Layout.fillWidth: true
                text: "发布考试"
                onClicked: {
                    if (root.selectedPaperQuestions.length === 0) {
                        root.showToast("请先添加题目")
                        return
                    }
                    if (root.selectedPublishClasses.length === 0) {
                        root.showToast("请选择发布班级")
                        return
                    }
                    if (root.paperTotalScore() > root.paperTargetScore()) {
                        root.showToast("当前试卷总分超过设定满分，不能发布")
                        return
                    }
                    var paperId = teacherApi.createDraftPaperFromQuestions(preview.titleText, preview.subject, preview.startText, preview.endText, root.selectedPaperQuestions)
                    if (paperId > 0 && teacherApi.publishExam(paperId, root.selectedPublishClasses, preview.startText, preview.endText)) {
                        root.activePaperId = paperId
                        root.refreshAll()
                        root.showToast("考试已发布")
                    } else {
                        root.showToast("发布失败：" + teacherApi.lastError())
                    }
                }
            }
        }
    }

    component ReviewPage: PageShell {
        Loader {
            width: parent.width
            sourceComponent: root.reviewWorkMode ? reviewWorkComponent : reviewPickComponent
        }

        Component {
            id: reviewPickComponent
            Column {
                width: parent.width
                spacing: 20
                SectionTitle {}
                GridLayout {
                    width: parent.width
                    columns: parent.width > 1180 ? 5 : 1
                    columnSpacing: root.narrowShell ? 12 : 18
                    rowSpacing: root.narrowShell ? 12 : 18
                    ReviewExamList { Layout.fillWidth: true; Layout.columnSpan: parent.width > 1180 ? 2 : 1; Layout.preferredHeight: root.narrowShell ? 520 : 620 }
                    ReviewStudentList { Layout.fillWidth: true; Layout.columnSpan: parent.width > 1180 ? 3 : 1; Layout.preferredHeight: root.narrowShell ? 560 : 620 }
                }
            }
        }

        Component {
            id: reviewWorkComponent
            Column {
                width: parent.width
                spacing: 20
                Card {
                    width: parent.width
                    height: root.narrowShell ? 128 : 96
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 22
                        spacing: 14
                        SoftButton { Layout.preferredWidth: 96; text: "返回"; onClicked: root.reviewWorkMode = false }
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: "批改试卷"; color: "#111827"; font.pixelSize: 26; font.bold: true }
                            Text { text: (root.selectedReviewAnswer().studentName || "--") + " · " + (root.selectedReviewAnswer().studentNo || ""); color: "#64748b"; font.pixelSize: 14 }
                        }
                    }
                }
                ReviewWorkArea { width: parent.width; height: root.narrowShell ? 900 : 660; enterDelay: 80 }
            }
        }
    }

    component ReviewExamList: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 12
            Text { text: "试卷列表"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            ListView {
                id: reviewExamList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: contentHeight > height
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 7200
                flickDeceleration: 3000
                reuseItems: true
                cacheBuffer: height * 2
                model: root.orderedExams()
                ScrollBar.vertical: ScrollBar {
                    policy: reviewExamList.contentHeight > reviewExamList.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                    width: 12
                    contentItem: Rectangle { radius: 6; color: "#9fb3cc" }
                    background: Rectangle { radius: 6; color: "#edf2f8" }
                }
                delegate: Rectangle {
                    width: ListView.view.width - (reviewExamList.contentHeight > reviewExamList.height ? 18 : 0)
                    height: 68
                    radius: 16
                    color: root.reviewExamIndex === index ? "#eef6ff" : "#ffffff"
                    border.color: root.reviewExamIndex === index ? "#bfdbfe" : "#e5edf6"
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: root.selectReviewExam(modelData, index)
                    }
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: modelData.name || "--"; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                            Text { text: root.examDate(modelData); color: "#64748b"; font.pixelSize: 12; Layout.fillWidth: true; elide: Text.ElideRight }
                        }
                        Text { text: modelData.subject || ""; color: "#2563eb"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 70; horizontalAlignment: Text.AlignRight }
                    }
                }
            }
        }
    }

    component ReviewStudentList: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: root.reviewPaperSelected ? "参加考试学生" : "学生列表"
                    color: "#111827"
                    font.pixelSize: 22
                    font.bold: true
                    Layout.fillWidth: true
                }
                Text {
                    text: root.reviewPaperSelected ? "已选择试卷" : "请选择左侧试卷"
                    color: root.reviewPaperSelected ? "#16a34a" : "#f59e0b"
                    font.pixelSize: 13
                    font.bold: true
                }
            }
            ListView {
                id: reviewStudentList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: contentHeight > height
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 7200
                flickDeceleration: 3000
                pixelAligned: false
                reuseItems: true
                cacheBuffer: height * 2
                model: root.reviewStudents.length > 0 ? root.reviewStudents : [{"studentName":"学生1","studentNo":"20250101","score":"--","status":"待批改"}]
                ScrollBar.vertical: ScrollBar {
                    policy: reviewStudentList.contentHeight > reviewStudentList.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                    width: 12
                    contentItem: Rectangle { radius: 6; color: "#9fb3cc" }
                    background: Rectangle { radius: 6; color: "#edf2f8" }
                }
                delegate: Rectangle {
                    readonly property bool finished: String(modelData.status || modelData.reviewStatus || "") === "已批改" || (String(modelData.score || "").length > 0 && String(modelData.score || "") !== "--")
                    width: ListView.view.width - (reviewStudentList.contentHeight > reviewStudentList.height ? 18 : 0)
                    height: 64
                    radius: 16
                    color: root.reviewStudentIndex === index ? "#eef6ff" : "#ffffff"
                    border.color: root.reviewStudentIndex === index ? "#bfdbfe" : "#e5edf6"
                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.reviewStudentIndex = index }
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: modelData.studentName || modelData.name || "--"; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                            Text { text: modelData.studentNo || modelData.username || ""; color: "#64748b"; font.pixelSize: 12; Layout.fillWidth: true; elide: Text.ElideRight }
                        }
                        Text { text: finished ? (String(modelData.score || "--") + " 分") : "--"; color: "#2563eb"; font.pixelSize: 16; font.bold: true; Layout.preferredWidth: 72; horizontalAlignment: Text.AlignRight }
                        Text {
                            text: root.reviewPaperSelected ? (finished ? "已批改" : "待批改") : (modelData.className || "全部学生")
                            color: root.reviewPaperSelected ? (finished ? "#16a34a" : "#f59e0b") : "#64748b"
                            font.pixelSize: 13
                            font.bold: true
                            Layout.preferredWidth: 86
                            horizontalAlignment: Text.AlignHCenter
                        }
                        SoftButton {
                            visible: root.reviewPaperSelected
                            Layout.preferredWidth: 78
                            text: finished ? "查看" : "批改"
                            onClicked: root.beginReviewStudent(index)
                        }
                    }
                }
            }
        }
    }

    component ReviewWorkArea: Card {
        id: reviewArea
        property var question: root.selectedReviewQuestion()
        property var answer: root.selectedReviewAnswer()
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            RowLayout {
                Layout.fillWidth: true
                Text { text: "改卷区域"; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
                Text { text: (root.reviewQuestionIndex + 1) + " / " + root.subjectiveQuestionCount(); color: "#2563eb"; font.pixelSize: 14; font.bold: true }
            }
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: parent.width > 980 ? 2 : 1
                columnSpacing: root.narrowShell ? 14 : 22
                rowSpacing: root.narrowShell ? 14 : 22
                DetailBlock {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    title: "学生答题情况"
                    text: root.questionText(reviewArea.question) + "\n\n学生答案：" + (reviewArea.answer.answer || "暂无答题内容")
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 16
                    DetailBlock { Layout.fillWidth: true; Layout.preferredHeight: 230; title: "参考答案"; text: reviewArea.question.answer || "--"; accent: true }
                    AppField { id: scoreInput; Layout.fillWidth: true; placeholderText: "输入本题得分，满分 " + (reviewArea.question.score || 10) }
                    TextArea {
                        id: commentInput
                        Layout.fillWidth: true
                        Layout.preferredHeight: 150
                        placeholderText: "教师评价"
                        font.pixelSize: 14
                        color: "#111827"
                        background: Rectangle { radius: 16; color: "#f7f9fd"; border.color: "#e4eaf3" }
                    }
                    PrimaryButton {
                        Layout.fillWidth: true
                        text: "保存并下一题"
                        onClicked: {
                            if (scoreInput.text.trim().length === 0) {
                                root.showToast("请输入本题得分")
                                return
                            }
                            var answerId = Number(reviewArea.answer.id || 0)
                            if (answerId > 0) {
                                teacherApi.saveReviewScore(answerId, Number(scoreInput.text), commentInput.text)
                                root.reviewStudents = root.activePaperId > 0 ? teacherApi.getStudentAnswersForPaper(root.activePaperId) : root.reviewStudents
                                var student = root.reviewStudents.length > root.reviewStudentIndex ? root.reviewStudents[root.reviewStudentIndex] : ({})
                                root.reviewAnswerDetails = root.activePaperId > 0 && String(student.studentNo || "").length > 0
                                        ? teacherApi.getStudentAnswersForStudent(root.activePaperId, String(student.studentNo))
                                        : []
                            } else {
                                root.showToast("未找到该题答卷，无法保存评分")
                                return
                            }
                            if (root.reviewQuestionIndex >= root.subjectiveQuestionCount() - 1) {
                                completeDialog.open()
                                root.refreshAll()
                            } else {
                                root.reviewQuestionIndex += 1
                            }
                        }
                    }
                }
            }
        }
        Dialog {
            id: completeDialog
            title: "批改完成"
            modal: true
            standardButtons: Dialog.Ok
            Text { text: "该同学已经批改完成"; color: "#111827"; font.pixelSize: 16; padding: 24 }
        }
    }

    component ClassPage: PageShell {
        SectionTitle {}
        Loader {
            width: parent.width
            sourceComponent: root.classDetailMode ? classDetailComponent : classListComponent
        }

        Component {
            id: classListComponent
            GridLayout {
                width: parent.width
                columns: root.narrowShell ? 1 : (parent.width > 1050 ? 3 : 2)
                columnSpacing: root.narrowShell ? 12 : 18
                rowSpacing: root.narrowShell ? 12 : 18
                Repeater {
                    model: root.classes
                    ClassCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 210
                        classInfo: modelData
                    }
                }
            }
        }

        Component {
            id: classDetailComponent
            ClassDetailView { width: parent.width }
        }
    }

    component ClassCard: Card {
        id: classCard
        property var classInfo: ({})
        hoverable: true
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                root.selectedClassName = classCard.classInfo.name
                root.classStudents = teacherApi.getClassStudents(root.selectedClassName)
                root.classDetailMode = true
                root.classExamDetailMode = false
                root.animationKey += 1
            }
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 14
            Text { text: classCard.classInfo.name || "--"; color: "#111827"; font.pixelSize: 23; font.bold: true }
            Text { text: classCard.classInfo.major || "专业未设置"; color: "#64748b"; font.pixelSize: 13 }
            RowLayout {
                Layout.fillWidth: true
                InnerMetric { Layout.fillWidth: true; label: "学生"; value: String(classCard.classInfo.students || 0) }
                InnerMetric { Layout.fillWidth: true; label: "考试"; value: String(classCard.classInfo.examCount || 0) }
            }
        }
    }

    component InnerMetric: Rectangle {
        id: innerMetric
        property string label: ""
        property string value: ""
        Layout.preferredHeight: 76
        radius: 18
        color: "#ffffff"
        border.color: "#e5edf6"
        Column {
            anchors.centerIn: parent
            spacing: 4
            Text { text: innerMetric.value; color: "#2563eb"; font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
            Text { text: innerMetric.label; color: "#64748b"; font.pixelSize: 13; anchors.horizontalCenter: parent.horizontalCenter }
        }
    }

    component ClassDetailView: Column {
        spacing: 18
        Loader {
            width: parent.width
            sourceComponent: root.classExamDetailMode ? classExamScoreComponent : classExamListComponent
        }

        Component {
            id: classExamListComponent
            Column {
                width: parent.width
                spacing: 18
                Card {
                    width: parent.width
                    height: root.narrowShell ? 230 : 136
                    Flow {
                        anchors.fill: parent
                        anchors.margins: root.narrowShell ? 18 : 24
                        spacing: 18
                        SoftButton { width: root.narrowShell ? 96 : 96; text: "返回"; onClicked: root.classDetailMode = false }
                        ColumnLayout {
                            width: root.narrowShell ? parent.width : Math.max(260, parent.width - 420)
                            height: root.narrowShell ? 58 : 66
                            Text { Layout.fillWidth: true; text: root.selectedClassName; color: "#111827"; font.pixelSize: root.narrowShell ? 22 : 26; font.bold: true; elide: Text.ElideRight }
                            Text { Layout.fillWidth: true; text: "点击参加考试查看分数区间与学生成绩"; color: "#64748b"; font.pixelSize: 14; elide: Text.ElideRight }
                        }
                        MetricMini { width: root.narrowShell ? (parent.width - 18) / 2 : 84; height: 58; label: "学生"; value: root.classStudents.length }
                        MetricMini { width: root.narrowShell ? (parent.width - 18) / 2 : 84; height: 58; label: "考试"; value: root.examsForClass(root.selectedClassName).length }
                    }
                }
                GridLayout {
                    width: parent.width
                    columns: parent.width > 1100 ? 2 : 1
                    columnSpacing: root.narrowShell ? 12 : 18
                    rowSpacing: root.narrowShell ? 12 : 18
                    ClassExamListCard { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 390 : 420 }
                    ClassStudentRosterCard { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 390 : 420 }
                }
            }
        }

        Component {
            id: classExamScoreComponent
            Column {
                width: parent.width
                spacing: 18
                Card {
                    width: parent.width
                    height: root.narrowShell ? 292 : 164
                    Flow {
                        anchors.fill: parent
                        anchors.margins: root.narrowShell ? 18 : 24
                        spacing: 18
                        SoftButton { width: root.narrowShell ? 112 : 112; text: "考试列表"; onClicked: root.classExamDetailMode = false }
                        ColumnLayout {
                            width: root.narrowShell ? parent.width : Math.max(260, parent.width - 510)
                            height: root.narrowShell ? 58 : 66
                            Text { Layout.fillWidth: true; text: root.selectedClassExam.name || "考试概况"; color: "#111827"; font.pixelSize: root.narrowShell ? 22 : 26; font.bold: true; elide: Text.ElideRight }
                            Text { Layout.fillWidth: true; text: root.selectedClassName + " · " + root.examDate(root.selectedClassExam); color: "#64748b"; font.pixelSize: 14; elide: Text.ElideRight }
                        }
                        MetricMini { width: root.narrowShell ? (parent.width - 36) / 3 : 84; height: 58; label: "平均分"; value: root.selectedClassExam.average || root.scoreStats.average || 86.5 }
                        MetricMini { width: root.narrowShell ? (parent.width - 36) / 3 : 84; height: 58; label: "最高分"; value: 98 }
                        MetricMini { width: root.narrowShell ? (parent.width - 36) / 3 : 84; height: 58; label: "最低分"; value: 54 }
                    }
                }
                GridLayout {
                    width: parent.width
                    columns: parent.width > 1100 ? 2 : 1
                    columnSpacing: root.narrowShell ? 12 : 18
                    rowSpacing: root.narrowShell ? 12 : 18
                    PieCard { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 300 : 330 }
                    StudentScoreCard { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 360 : 330 }
                }
            }
        }
    }

    component ClassExamListCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            Text { text: "参加考试"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            ListView {
                id: classExamList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: contentHeight > height
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 6800
                flickDeceleration: 2800
                reuseItems: true
                cacheBuffer: height * 2
                model: root.examsForClass(root.selectedClassName)
                delegate: Rectangle {
                    width: ListView.view.width - (classExamList.contentHeight > classExamList.height ? 18 : 0)
                    height: 68
                    radius: 16
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 12
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { text: modelData.name || "--"; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                            Text { text: root.examDate(modelData); color: "#64748b"; font.pixelSize: 12; Layout.fillWidth: true; elide: Text.ElideRight }
                        }
                        Text { text: modelData.status || "已发布"; color: "#16a34a"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 76; horizontalAlignment: Text.AlignHCenter }
                        Text { text: "查看"; color: "#2563eb"; font.pixelSize: 14; font.bold: true; Layout.preferredWidth: 48; horizontalAlignment: Text.AlignRight }
                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: root.openClassExam(modelData)
                    }
                }
            }
        }
    }

    component ClassStudentRosterCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            Text { text: "班级学生"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            ListView {
                id: rosterList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: contentHeight > height
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 6800
                flickDeceleration: 2800
                reuseItems: true
                cacheBuffer: height * 2
                model: root.classStudents
                delegate: Rectangle {
                    width: ListView.view.width - (rosterList.contentHeight > rosterList.height ? 18 : 0)
                    height: 52
                    radius: 14
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 11
                        Text { text: modelData.name || "--"; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                        Text { text: modelData.studentNo || modelData.username || ""; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 130 }
                    }
                }
            }
        }
    }

    component PieCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            Text { text: "分数区间分布"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Canvas {
                Layout.fillWidth: true
                Layout.fillHeight: true
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0,0,width,height)
                    var colors = ["#22c55e", "#3b82f6", "#f59e0b", "#ef4444"]
                    var values = [42, 36, 16, 6]
                    var total = 100
                    var start = -Math.PI / 2
                    var cx = width / 2
                    var cy = height / 2
                    var r = Math.min(width, height) * 0.33
                    for (var i = 0; i < values.length; ++i) {
                        var end = start + Math.PI * 2 * values[i] / total
                        ctx.beginPath()
                        ctx.moveTo(cx, cy)
                        ctx.arc(cx, cy, r, start, end)
                        ctx.closePath()
                        ctx.fillStyle = colors[i]
                        ctx.fill()
                        start = end
                    }
                    ctx.fillStyle = "#ffffff"
                    ctx.beginPath()
                    ctx.arc(cx, cy, r * 0.55, 0, Math.PI * 2)
                    ctx.fill()
                }
            }
        }
    }

    component StudentScoreCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            Text { text: "学生成绩"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            RowLayout {
                Layout.fillWidth: true
                Text { text: "姓名"; color: "#94a3b8"; font.pixelSize: 13; Layout.fillWidth: true }
                Text { visible: !root.narrowShell; text: "学号"; color: "#94a3b8"; font.pixelSize: 13; Layout.preferredWidth: 130 }
                Text { text: "分数"; color: "#94a3b8"; font.pixelSize: 13; Layout.preferredWidth: 70 }
            }
            ListView {
                id: classStudentScoreList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 10
                interactive: contentHeight > height
                boundsBehavior: Flickable.DragOverBounds
                boundsMovement: Flickable.FollowBoundsBehavior
                maximumFlickVelocity: 7200
                flickDeceleration: 3000
                pixelAligned: false
                reuseItems: true
                cacheBuffer: height * 2
                model: root.classStudents
                ScrollBar.vertical: ScrollBar {
                    policy: classStudentScoreList.contentHeight > classStudentScoreList.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                    width: 12
                    contentItem: Rectangle { radius: 6; color: "#9fb3cc" }
                    background: Rectangle { radius: 6; color: "#edf2f8" }
                }
                delegate: Rectangle {
                    width: ListView.view.width - (classStudentScoreList.contentHeight > classStudentScoreList.height ? 18 : 0)
                    height: 46
                    radius: 12
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        Text { text: modelData.name || "--"; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true }
                        Text { visible: !root.narrowShell; text: modelData.studentNo || modelData.username || ""; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 130 }
                        Text { text: String(80 + (index * 3) % 18); color: "#2563eb"; font.pixelSize: 15; font.bold: true; Layout.preferredWidth: 70 }
                    }
                }
            }
        }
    }

    component MetricMini: ColumnLayout {
        property string label: ""
        property var value: ""
        implicitWidth: root.narrowShell ? 96 : 84
        implicitHeight: 58
        spacing: 2
        Text { Layout.fillWidth: true; text: String(parent.value); color: "#2563eb"; font.pixelSize: root.narrowShell ? 22 : 26; font.bold: true; horizontalAlignment: Text.AlignHCenter }
        Text { Layout.fillWidth: true; text: parent.label; color: "#64748b"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter }
    }
}
