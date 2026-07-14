import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#eef2f8"
    clip: true

    property int currentPage: 0
    property int animationKey: 0
    property int pageEnterDirection: 1
    property bool innerScrollActive: false
    property bool narrowShell: width < 980
    property bool compactShell: width < 1180
    property bool mediumShell: width < 1360
    property real contentScale: (examMode || practiceExamMode || narrowShell) ? 1.0 : Math.max(1.12, Math.min(1.48, Math.min(width / 1180, height / 700)))
    property real examScale: narrowShell ? 1.0 : Math.max(1.0, Math.min(1.22, Math.min(width / 1366, height / 768)))
    property int shellHMargin: narrowShell ? 14 : (compactShell ? 22 : 38)
    property int shellVMargin: narrowShell ? 16 : (compactShell ? 22 : 30)
    property int pageGap: narrowShell ? 14 : 22
    property int normalNavHeight: narrowShell ? 96 : (compactShell ? 120 : 136)
    property int profileMode: 0
    property bool examMode: false
    property bool practiceExamMode: false
    property bool practiceExamFinished: false
    property int practiceMode: 0
    property int activeWrongQuestionIndex: 0
    property int practiceTimeLimit: 30
    property int activeExamId: 0
    property int activeQuestionIndex: 0
    property int activePracticeExamIndex: 0
    property string toastText: ""
    property var profile: ({})
    property var exams: []
    property var questions: []
    property var practiceQuestions: []
    property var practiceExamQuestions: []
    property var answers: ({})
    property var markedQuestions: ({})
    property var practiceAnswers: ({})
    property var practiceExamAnswers: ({})
    property var practiceChecked: ({})
    property var scoreReport: ({})
    property var scoreHistory: []
    property string activeReportSubject: "高等数学"
    property string activePracticeSubject: "全部科目"
    property var menuItems: [
        {"title": "首页", "icon": "⌂", "page": 0},
        {"title": "我的考试", "icon": "▣", "page": 1},
        {"title": "题库练习", "icon": "▤", "page": 2},
        {"title": "成绩分析", "icon": "∥", "page": 3}
    ]
    property var studentNotifications: []
    property var trendPoints: []
    property var classTrendPoints: []
    property var subjectTrendMap: ({})
    property var activityBars: []
    property var subjectCards: []
    property var achievements: []
    property var aiSuggestions: []
    property var wrongQuestionRows: []
    property var pageTitles: ["学生首页", "我的考试", "题库练习", "成绩分析", "个人中心", "成绩报告"]
    property var pageSubtitles: [
        "查看考试安排、继续答题与提交状态",
        "选择考试、查看说明并进入答题",
        "按题型和难度练习，提交后立即查看答案解析",
        "选择科目查看个人与班级成绩趋势、科目表现和考试历史",
        "管理个人资料与账号安全",
        "查看本场考试得分、扣分题型与薄弱知识点",
    ]

    Component.onCompleted: refreshAll()

    Timer {
        id: notificationRefreshTimer
        interval: 30000
        repeat: true
        running: true
        triggeredOnStart: false
        onTriggered: {
            if (root.examMode || root.practiceExamMode) {
                return
            }
            root.exams = studentApi.getPublishedExams()
            root.scoreHistory = studentApi.getScoreHistory("")
            root.syncActiveReportSubject()
        }
    }

    function refreshAll() {
        profile = studentApi.getStudentProfile()
        exams = studentApi.getPublishedExams()
        scoreHistory = studentApi.getScoreHistory("")
        subjectCards = studentApi.getPracticeSubjectStats()
        wrongQuestionRows = studentApi.getWrongQuestions()
        syncActiveReportSubject()
        if (activeExamId <= 0) {
            var reportRows = reportExamRows()
            if (reportRows.length > 0) activeExamId = Number(reportRows[0].id || 0)
            else if (exams.length > 0) activeExamId = Number(exams[0].id || 0)
        }
        scoreReport = activeExamId > 0 ? studentApi.getScoreReport(activeExamId) : ({})
        aiSuggestions = aiSuggestionRows()
    }

    function profileName() {
        return String(profile.name || profile.username || "学生")
    }

    function avatarText() {
        var name = profileName()
        return name.length > 0 ? name.charAt(0) : "学"
    }

    function triggerPageEnter(direction) {
        innerScrollActive = false
        pageEnterDirection = direction < 0 ? -1 : 1
        animationKey += 1
    }

    function switchPage(page) {
        var direction = page >= currentPage ? 1 : -1
        examMode = false
        practiceExamMode = false
        currentPage = page
        if (page === 2) practiceMode = 0
        if (page !== 4) profileMode = 0
        triggerPageEnter(direction)
    }

    function openPracticeWrongBook() {
        var direction = currentPage <= 2 ? 1 : -1
        examMode = false
        practiceExamMode = false
        currentPage = 2
        practiceMode = 1
        wrongQuestionRows = studentApi.getWrongQuestions()
        aiSuggestions = aiSuggestionRows()
        activeWrongQuestionIndex = 0
        triggerPageEnter(direction)
    }

    function openRandomPaperConfig() {
        var direction = currentPage <= 2 ? 1 : -1
        examMode = false
        practiceExamMode = false
        currentPage = 2
        practiceMode = 2
        triggerPageEnter(direction)
    }

    function openProfileCenter(mode) {
        var direction = currentPage <= 4 ? 1 : -1
        examMode = false
        practiceExamMode = false
        currentPage = 4
        profileMode = mode || 0
        triggerPageEnter(direction)
    }

    function exitExamMode() {
        examMode = false
        triggerPageEnter(-1)
    }

    function exitPracticeExamMode() {
        practiceExamMode = false
        currentPage = 2
        triggerPageEnter(-1)
    }

    function pageComponent() {
        if (currentPage === 1) return examListPageComponent
        if (currentPage === 2) return practicePageComponent
        if (currentPage === 3) return gradeAnalysisPageComponent
        if (currentPage === 4) return profilePageComponent
        if (currentPage === 5) return scoreReportPageComponent
        return dashboardPageComponent
    }

    function selectedExam() {
        var rows = examRows()
        for (var i = 0; i < rows.length; ++i) {
            if (Number(rows[i].id || 0) === activeExamId) return rows[i]
        }
        return rows.length > 0 ? rows[0] : ({})
    }

    function examRows() {
        var rows = []
        var seen = ({})
        for (var i = 0; i < exams.length; ++i) {
            var exam = exams[i]
            var examId = Number(exam.id || exam.examId || 0)
            if (examId > 0) seen[String(examId)] = true
            rows.push(exam)
        }
        for (var h = scoreHistory.length - 1; h >= 0; --h) {
            var item = scoreHistory[h]
            var historyId = Number(item.id || item.examId || 0)
            if (historyId > 0 && seen[String(historyId)]) continue
            rows.push({
                "id": historyId,
                "title": item.title || item.name || "未命名考试",
                "subject": item.subject || "综合",
                "score": item.score,
                "totalScore": item.full || item.fullScore || 100,
                "date": item.date,
                "startTime": item.date,
                "status": "已完成",
                "className": item.className || profile.className
            })
            if (historyId > 0) seen[String(historyId)] = true
        }
        return rows
    }

    function examTitle(exam) {
        return String(exam.title || exam.name || "综合考试")
    }

    function examSubject(exam) {
        return String(exam.subject || "综合")
    }

    function subjectAccent(subject) {
        var name = String(subject || "")
        if (name.indexOf("高等") >= 0 || name.indexOf("数学") >= 0) return "#3b82f6"
        if (name.indexOf("线性") >= 0) return "#22c55e"
        if (name.indexOf("概率") >= 0) return "#a855f7"
        if (name.indexOf("数据") >= 0) return "#06b6d4"
        if (name.indexOf("数据库") >= 0) return "#ef4444"
        return "#22c55e"
    }

    function scoreForExam(examId) {
        var target = Number(examId || 0)
        if (target <= 0) return ({})
        for (var i = 0; i < scoreHistory.length; ++i) {
            var row = scoreHistory[i]
            if (Number(row.id || row.examId || 0) === target) return row
        }
        return ({})
    }

    function pad2(value) {
        var number = Math.max(0, Number(value || 0))
        return number < 10 ? "0" + number : String(number)
    }

    function parseDateValue(value) {
        if (value === undefined || value === null || String(value).length === 0) return null
        var text = String(value).replace(" ", "T")
        if (text.length === 10) text += "T00:00:00"
        var date = new Date(text)
        return isNaN(date.getTime()) ? null : date
    }

    function examStartDate(exam) {
        return parseDateValue(exam.startTime || exam.start_time || exam.date)
    }

    function dateKey(date) {
        if (!date) return ""
        return date.getFullYear() + "-" + pad2(date.getMonth() + 1) + "-" + pad2(date.getDate())
    }

    function formatExamTime(exam) {
        var date = examStartDate(exam)
        if (!date) return "-- · " + (exam.duration || 90) + " 分钟"
        return (date.getMonth() + 1) + " 月 " + date.getDate() + " 日 · "
                + pad2(date.getHours()) + ":" + pad2(date.getMinutes())
                + " · " + (exam.duration || 90) + " 分钟"
    }

    function countdownParts(exam) {
        var date = examStartDate(exam)
        if (!date) return {"days": "00", "hours": "00", "minutes": "00", "past": true}
        var diff = date.getTime() - Date.now()
        if (diff <= 0) return {"days": "00", "hours": "00", "minutes": "00", "past": true}
        var dayMs = 24 * 60 * 60 * 1000
        var hourMs = 60 * 60 * 1000
        var days = Math.floor(diff / dayMs)
        var hours = Math.floor((diff - days * dayMs) / hourMs)
        var minutes = Math.floor((diff - days * dayMs - hours * hourMs) / 60000)
        return {"days": pad2(days), "hours": pad2(hours), "minutes": pad2(minutes), "past": false}
    }

    function countdownShortLabel(date) {
        if (!date) return "待参加"
        var diff = date.getTime() - Date.now()
        if (diff <= 0) return "已开始"
        var days = Math.floor(diff / (24 * 60 * 60 * 1000))
        if (days > 0) return days + " 天后"
        var hours = Math.floor(diff / (60 * 60 * 1000))
        if (hours > 0) return hours + " 小时后"
        return Math.max(1, Math.floor(diff / 60000)) + " 分钟后"
    }

    function displayQuestionType(type) {
        var value = String(type || "").toLowerCase()
        if (value === "single" || value === "option" || value === "choice" || value === "单选") return "单选题"
        if (value === "multiple" || value === "multi" || value === "多选") return "多选题"
        if (value === "blank" || value === "fill" || value === "fill_blank" || value === "填空") return "填空题"
        if (value === "judge" || value === "truefalse" || value === "判断") return "判断题"
        if (value === "program" || value === "coding" || value === "code") return "编程题"
        if (value === "hard_math") return "高数大题"
        return String(type || "题目")
    }

    function displayDifficulty(value) {
        var text = String(value || "").toLowerCase()
        if (text === "easy" || text === "basic" || text === "基础") return "基础"
        if (text === "medium" || text === "normal" || text === "middle" || text === "中等") return "中等"
        if (text === "hard" || text === "difficult" || text === "困难") return "困难"
        return String(value || "中等")
    }

    function isMultipleChoice(type) {
        return displayQuestionType(type) === "多选题"
    }

    function isManualQuestion(type) {
        var label = displayQuestionType(type)
        return label === "编程题" || label === "高数大题" || label === "简答题"
    }

    function examStatus(exam, index) {
        var scored = scoreForExam(exam.id || exam.examId)
        if (scored.score !== undefined) return "已完成"
        var explicitStatus = String(exam.status || "")
        if (explicitStatus === "已发布") return "待参加"
        if (explicitStatus === "未开始") return "未开放"
        if (explicitStatus.length > 0) return explicitStatus
        return "待参加"
    }

    function examCountdownLabel(exam, index) {
        var status = examStatus(exam, index)
        if (status === "已完成") {
            var scored = scoreForExam(exam.id || exam.examId)
            return displayNumber(scored.score !== undefined ? scored.score : exam.score) + " 分"
        }
        if (status === "未开放") return "未开放"
        return countdownShortLabel(examStartDate(exam))
    }

    function filteredExamRows(keyword, status) {
        var rows = examRows()
        var result = []
        var kw = String(keyword || "").toLowerCase()
        for (var i = 0; i < rows.length; ++i) {
            var row = rows[i]
            var title = examTitle(row).toLowerCase()
            var subject = examSubject(row).toLowerCase()
            var rowStatus = examStatus(row, i)
            var matchText = kw.length === 0 || title.indexOf(kw) >= 0 || subject.indexOf(kw) >= 0
            var matchStatus = status === "全部" || rowStatus === status
            if (matchText && matchStatus) result.push(row)
        }
        return result
    }

    function upcomingExamRows(showAll) {
        var rows = examRows()
        var result = []
        for (var i = 0; i < rows.length; ++i) {
            if (examStatus(rows[i], i) === "已完成") continue
            result.push({"exam": rows[i], "rowIndex": i})
        }
        result.sort(function(left, right) {
            var leftDate = examStartDate(left.exam)
            var rightDate = examStartDate(right.exam)
            var leftTime = leftDate ? leftDate.getTime() : 9999999999999
            var rightTime = rightDate ? rightDate.getTime() : 9999999999999
            return leftTime - rightTime
        })
        if (!showAll && result.length > 2) return result.slice(0, 2)
        return result
    }

    function nextExamEntry() {
        var rows = upcomingExamRows(true)
        return rows.length > 0 ? rows[0] : ({})
    }

    function nextExam() {
        var entry = nextExamEntry()
        return entry.exam || ({})
    }

    function upcomingExamCount() {
        return upcomingExamRows(true).length
    }

    function completedExamCount() {
        var seen = ({})
        var count = 0
        for (var i = 0; i < scoreHistory.length; ++i) {
            var id = String(scoreHistory[i].id || scoreHistory[i].examId || i)
            if (seen[id]) continue
            seen[id] = true
            count += 1
        }
        return count
    }

    function scorePercent(row) {
        var full = Number(row.full || row.fullScore || 100)
        var score = Number(row.score || 0)
        return full > 0 ? score / full * 100 : 0
    }

    function averageScoreText() {
        if (scoreHistory.length === 0) return "--"
        var total = 0
        for (var i = 0; i < scoreHistory.length; ++i) total += scorePercent(scoreHistory[i])
        return displayNumber(total / scoreHistory.length)
    }

    function averageScoreDeltaText() {
        if (scoreHistory.length < 2) return "暂无对比"
        var latest = scorePercent(scoreHistory[scoreHistory.length - 1])
        var previous = scorePercent(scoreHistory[scoreHistory.length - 2])
        var delta = Math.round((latest - previous) * 10) / 10
        if (delta === 0) return "持平"
        return (delta > 0 ? "+" : "") + delta
    }

    function studyStreakDays() {
        if (scoreHistory.length === 0) return 0
        var seen = ({})
        var dates = []
        for (var i = 0; i < scoreHistory.length; ++i) {
            var date = parseDateValue(scoreHistory[i].date)
            if (!date) continue
            var key = dateKey(date)
            if (!seen[key]) {
                seen[key] = true
                dates.push(date)
            }
        }
        if (dates.length === 0) return 0
        dates.sort(function(a, b) { return b.getTime() - a.getTime() })
        var streak = 1
        var cursor = new Date(dates[0].getFullYear(), dates[0].getMonth(), dates[0].getDate())
        for (var j = 1; j < dates.length; ++j) {
            var next = new Date(dates[j].getFullYear(), dates[j].getMonth(), dates[j].getDate())
            var diffDays = Math.round((cursor.getTime() - next.getTime()) / (24 * 60 * 60 * 1000))
            if (diffDays === 1) {
                streak += 1
                cursor = next
            } else if (diffDays > 1) {
                break
            }
        }
        return streak
    }

    function dashboardHeroSubtitle() {
        var exam = nextExam()
        if (!exam.id && !exam.examId) return "暂无待参加考试，完成考试后这里会同步展示最新安排与成绩。"
        return "下一场：" + examTitle(exam) + " · " + countdownShortLabel(examStartDate(exam))
    }

    function recentDashboardScoreRows(limit) {
        var rows = []
        for (var i = scoreHistory.length - 1; i >= 0 && rows.length < Number(limit || 3); --i) {
            var item = scoreHistory[i]
            rows.push({
                "name": item.title || item.name || "未命名考试",
                "subject": item.subject || "综合",
                "score": displayNumber(item.score),
                "full": item.full || item.fullScore || 100,
                "rank": item.rank || "--",
                "level": item.level || scoreLevelFor(item.score, item.full || item.fullScore || 100),
                "color": item.accent || subjectAccent(item.subject)
            })
        }
        return rows
    }

    function dashboardActivityBars() {
        var bars = [0, 0, 0, 0, 0, 0, 0]
        var today = new Date()
        var start = new Date(today.getFullYear(), today.getMonth(), today.getDate())
        start.setDate(start.getDate() - 6)
        for (var i = 0; i < scoreHistory.length; ++i) {
            var date = parseDateValue(scoreHistory[i].date)
            if (!date) continue
            var clean = new Date(date.getFullYear(), date.getMonth(), date.getDate())
            var diff = Math.round((clean.getTime() - start.getTime()) / (24 * 60 * 60 * 1000))
            if (diff >= 0 && diff < 7) bars[diff] += 1
        }
        return bars
    }

    function dashboardActivityTotal() {
        var bars = dashboardActivityBars()
        var total = 0
        for (var i = 0; i < bars.length; ++i) total += Number(bars[i] || 0)
        return total
    }

    function achievementRows() {
        var rows = []
        var completed = completedExamCount()
        var avg = Number(averageScoreText())
        var latest = scoreHistory.length > 0 ? scoreHistory[scoreHistory.length - 1] : ({})
        if (completed > 0) rows.push("完成首考")
        if (completed >= 3) rows.push("稳定参测")
        if (!isNaN(avg) && avg >= 80) rows.push("稳定发挥")
        if (!isNaN(avg) && avg >= 90) rows.push("高分突破")
        if (Number(latest.classRank || 99) > 0 && Number(latest.classRank || 99) <= 3) rows.push("班级前列")
        if (studyStreakDays() >= 2) rows.push("连续记录")
        if (rows.length === 0) rows.push("暂无徽章")
        return rows
    }

    function aiSuggestionRows() {
        var rows = []
        var wrongCounts = ({})
        var maxSubject = ""
        var maxCount = 0
        for (var i = 0; i < wrongQuestionRows.length; ++i) {
            var subject = String(wrongQuestionRows[i].subject || "综合")
            wrongCounts[subject] = Number(wrongCounts[subject] || 0) + 1
            if (wrongCounts[subject] > maxCount) {
                maxSubject = subject
                maxCount = wrongCounts[subject]
            }
        }
        if (maxCount > 0) {
            rows.push({
                "title": maxSubject + "错题集中",
                "body": "当前错题本中该科目有 " + maxCount + " 道待复盘题，建议先完成订正并整理错误原因。",
                "color": subjectAccent(maxSubject)
            })
        }

        if (scoreHistory.length >= 2) {
            var last = scoreHistory[scoreHistory.length - 1]
            var prev = scoreHistory[scoreHistory.length - 2]
            var lastFull = Math.max(1, Number(last.full || last.fullScore || 100))
            var prevFull = Math.max(1, Number(prev.full || prev.fullScore || 100))
            var delta = Math.round((Number(last.score || 0) / lastFull - Number(prev.score || 0) / prevFull) * 100)
            rows.push({
                "title": delta >= 0 ? "最近成绩保持上升" : "最近成绩出现波动",
                "body": delta >= 0 ? ("最近一次较上次提升 " + delta + " 个百分点，可继续保持当前复盘节奏。") : ("最近一次较上次下降 " + Math.abs(delta) + " 个百分点，建议优先查看扣分题型和薄弱知识点。"),
                "color": delta >= 0 ? "#22c55e" : "#f59e0b"
            })
        }

        var upcoming = upcomingExamRows(false)
        if (upcoming.length > 0) {
            var exam = upcoming[0].exam
            rows.push({
                "title": examSubject(exam) + "考试临近",
                "body": examTitle(exam) + "将在 " + countdownShortLabel(examStartDate(exam)) + " 开始，可先完成对应科目题库练习。",
                "color": "#2563eb"
            })
        }

        if (rows.length === 0) {
            rows.push({
                "title": "暂无个性化建议",
                "body": "完成考试或题库练习后，将根据成绩、错题和考试安排生成复盘建议。",
                "color": "#22c55e"
            })
        }
        return rows.slice(0, 3)
    }

    function relativeDateText(value) {
        var date = parseDateValue(value)
        if (!date) return "刚刚"
        var diff = Date.now() - date.getTime()
        if (diff < 0) return countdownShortLabel(date)
        var minutes = Math.floor(diff / 60000)
        if (minutes < 60) return Math.max(1, minutes) + " 分钟前"
        var hours = Math.floor(minutes / 60)
        if (hours < 24) return hours + " 小时前"
        var days = Math.floor(hours / 24)
        return days + " 天前"
    }

    function studentNotificationRows(includeAll) {
        var rows = []
        var upcoming = upcomingExamRows(true)
        for (var i = 0; i < upcoming.length; ++i) {
            var exam = upcoming[i].exam
            rows.push({
                "title": examStatus(exam, i) === "未开放" ? "考试未开放" : "新考试发布",
                "body": examSubject(exam) + " · " + examTitle(exam) + " · " + formatExamTime(exam),
                "time": countdownShortLabel(examStartDate(exam)),
                "color": "#f59e0b",
                "icon": "!"
            })
        }
        for (var j = scoreHistory.length - 1; j >= 0; --j) {
            var score = scoreHistory[j]
            rows.push({
                "title": "成绩发布",
                "body": (score.subject || "综合") + " · " + (score.title || score.name || "未命名考试") + "：" + displayNumber(score.score) + " 分",
                "time": relativeDateText(score.date),
                "color": "#22c55e",
                "icon": "✓"
            })
        }
        return includeAll ? rows : rows.slice(0, 3)
    }

    function notificationCount() {
        return studentNotificationRows(true).length
    }

    function startSubjectPractice(subjectName) {
        activePracticeSubject = subjectName || "全部科目"
        loadPracticeQuestions("", "", subjectName)
        activePracticeIndex = 0
        currentPage = 2
        practiceMode = 3
        triggerPageEnter(1)
    }

    function openScoreReport(exam) {
        var direction = currentPage <= 5 ? 1 : -1
        selectExam(exam)
        activeReportSubject = examSubject(exam)
        examMode = false
        practiceExamMode = false
        currentPage = 5
        triggerPageEnter(direction)
    }

    function scoreHistoryRows(subject) {
        var selected = String(subject || activeReportSubject || "")
        var rows = []
        for (var i = 0; i < scoreHistory.length; ++i) {
            var row = scoreHistory[i]
            var rowSubject = String(row.subject || "综合")
            if (selected.length === 0 || selected === "全部科目" || selected === "暂无成绩" || rowSubject === selected) {
                rows.push(row)
            }
        }
        return rows
    }

    function recentScoreRows(subject, limit) {
        var rows = scoreHistoryRows(subject)
        var start = Math.max(0, rows.length - Number(limit || 7))
        var result = []
        for (var i = start; i < rows.length; ++i) result.push(rows[i])
        return result
    }

    function analysisSubjectOptions() {
        var seen = ({})
        var result = []
        for (var i = 0; i < scoreHistory.length; ++i) {
            var subject = String(scoreHistory[i].subject || "综合")
            if (!seen[subject]) {
                seen[subject] = true
                result.push(subject)
            }
        }
        if (result.length === 0) result.push("暂无成绩")
        return result
    }

    function syncActiveReportSubject() {
        var options = analysisSubjectOptions()
        if (options.length === 0 || options[0] === "暂无成绩") return
        for (var i = 0; i < options.length; ++i) {
            if (options[i] === activeReportSubject) return
        }
        activeReportSubject = options[options.length - 1]
    }

    function normalizedChartScore(row, key) {
        var value = Number(row[key] || 0)
        return Math.round(value * 10) / 10
    }

    function subjectTrendPoints(subject) {
        var rows = recentScoreRows(subject, 7)
        var result = []
        for (var i = 0; i < rows.length; ++i) {
            result.push(normalizedChartScore(rows[i], "score"))
        }
        return result
    }

    function classTrendPointsFor(subject) {
        var rows = recentScoreRows(subject, 7)
        var result = []
        for (var i = 0; i < rows.length; ++i) {
            result.push(normalizedChartScore(rows[i], "classAverage"))
        }
        return result
    }

    function trendLabelsFor(subject) {
        var rows = recentScoreRows(subject, 7)
        var labels = []
        for (var i = 0; i < rows.length; ++i) {
            labels.push(String(rows[i].trendLabel || rows[i].date || ("第" + (i + 1) + "次")))
        }
        return labels
    }

    function latestSubjectRow(subject) {
        var rows = scoreHistoryRows(subject)
        return rows.length > 0 ? rows[rows.length - 1] : ({})
    }

    function latestSubjectScoreText(subject) {
        var row = latestSubjectRow(subject)
        return row.score !== undefined ? displayNumber(row.score) + " 分" : "--"
    }

    function subjectAverageText(subject) {
        var rows = scoreHistoryRows(subject)
        if (rows.length === 0) return "--"
        var total = 0
        for (var i = 0; i < rows.length; ++i) total += Number(rows[i].score || 0)
        return displayNumber(total / rows.length) + " 分"
    }

    function subjectRankText(subject) {
        var row = latestSubjectRow(subject)
        return row.rank || "--"
    }

    function subjectTrendDeltaText(subject) {
        var rows = scoreHistoryRows(subject)
        if (rows.length < 2) return "暂无对比"
        var last = Number(rows[rows.length - 1].score || 0)
        var prev = Number(rows[rows.length - 2].score || 0)
        var delta = Math.round((last - prev) * 10) / 10
        if (delta === 0) return "持平"
        return (delta > 0 ? "+" : "") + delta
    }

    function subjectScoreRows() {
        var options = analysisSubjectOptions()
        var rows = []
        for (var i = 0; i < options.length; ++i) {
            if (options[i] === "暂无成绩") continue
            var latest = latestSubjectRow(options[i])
            rows.push({
                "name": options[i],
                "score": latest.score !== undefined ? displayNumber(latest.score) : "--",
                "full": latest.full || latest.fullScore || 100,
                "level": latest.level || scoreLevelFor(latest.score, latest.full || latest.fullScore || 100),
                "color": latest.accent || subjectAccent(options[i])
            })
        }
        return rows
    }

    function examHistoryRows(subject) {
        var rows = scoreHistoryRows(subject)
        var result = []
        for (var i = rows.length - 1; i >= 0; --i) {
            var row = rows[i]
            result.push({
                "name": row.title || row.name || "未命名考试",
                "subject": row.subject || "综合",
                "date": row.date || "--",
                "score": displayNumber(row.score),
                "full": row.full || row.fullScore || 100,
                "rank": row.rank || "--",
                "level": row.level || scoreLevelFor(row.score, row.full || row.fullScore || 100),
                "accent": row.accent || subjectAccent(row.subject)
            })
        }
        return result
    }

    function scoreLevelFor(score, full) {
        var percent = Number(score || 0) / Math.max(1, Number(full || 100))
        if (percent >= 0.9) return "优秀"
        if (percent >= 0.8) return "良好"
        if (percent >= 0.6) return "合格"
        return "需加强"
    }

    function activeSubjectExamId() {
        var historyRows = scoreHistoryRows(activeReportSubject)
        if (historyRows.length > 0) return Number(historyRows[historyRows.length - 1].id || historyRows[historyRows.length - 1].examId || activeExamId || 0)
        var rows = examRows()
        var subject = String(activeReportSubject || "")
        for (var i = 0; i < rows.length; ++i) {
            if (examSubject(rows[i]).indexOf(subject) >= 0 || subject.indexOf(examSubject(rows[i])) >= 0) {
                return Number(rows[i].id || activeExamId || 0)
            }
        }
        return activeExamId
    }

    function exportActiveReportExcel() {
        var path = studentApi.exportScoreHistoryExcel(activeReportSubject)
        showToast(path.length > 0 ? activeReportSubject + "成绩 Excel 已导出" : studentApi.lastError())
    }

    function printActiveReportPdf() {
        var path = studentApi.printScoreReportPdf(activeSubjectExamId())
        showToast(path.length > 0 ? activeReportSubject + "成绩 PDF 已生成" : studentApi.lastError())
    }

    function currentReportExamId() {
        return Number(currentReportExam().id || activeExamId || 0)
    }

    function exportCurrentReportExcel() {
        var exam = currentReportExam()
        var path = studentApi.exportScoreReportExcel(currentReportExamId())
        showToast(path.length > 0 ? examTitle(exam) + " 成绩报告 Excel 已导出" : studentApi.lastError())
    }

    function printCurrentReportPdf() {
        var exam = currentReportExam()
        var path = studentApi.printScoreReportPdf(currentReportExamId())
        showToast(path.length > 0 ? examTitle(exam) + " 成绩报告 PDF 已生成" : studentApi.lastError())
    }

    function selectExam(exam) {
        activeExamId = Number(exam.id || 0)
        scoreReport = activeExamId > 0 ? studentApi.getScoreReport(activeExamId) : ({})
    }

    function startExam(exam) {
        selectExam(exam)
        questions = studentApi.getExamQuestions(activeExamId)
        answers = ({})
        markedQuestions = ({})
        activeQuestionIndex = 0
        examMode = true
        triggerPageEnter(1)
    }

    function currentQuestion() {
        if (questions.length === 0) return ({})
        return questions[Math.min(activeQuestionIndex, questions.length - 1)]
    }

    function answerFor(questionId) {
        return answers[String(questionId)] || ""
    }

    function setAnswer(questionId, value) {
        var next = {}
        for (var key in answers) next[key] = answers[key]
        next[String(questionId)] = value
        answers = next
    }

    function questionMarked(questionId) {
        return markedQuestions[String(questionId)] === true
    }

    function toggleQuestionMark(questionId) {
        var next = {}
        for (var key in markedQuestions) next[key] = markedQuestions[key]
        next[String(questionId)] = !questionMarked(questionId)
        markedQuestions = next
    }

    function answeredCount() {
        var count = 0
        for (var i = 0; i < questions.length; ++i) {
            if (String(answerFor(questions[i].id)).trim().length > 0) count += 1
        }
        return count
    }

    function markedCount() {
        var count = 0
        for (var i = 0; i < questions.length; ++i) {
            if (questionMarked(questions[i].id)) count += 1
        }
        return count
    }

    function submitActiveExam() {
        if (questions.length === 0) {
            showToast("当前考试暂无题目")
            return
        }
        if (answeredCount() < questions.length) {
            showToast("还有题目未作答，请检查后提交")
            return
        }
        var ok = studentApi.submitExam(activeExamId, answers)
        if (ok) {
            showToast("交卷成功")
            examMode = false
            currentPage = 5
            scoreHistory = studentApi.getScoreHistory("")
            wrongQuestionRows = studentApi.getWrongQuestions()
            scoreReport = studentApi.getScoreReport(activeExamId)
            aiSuggestions = aiSuggestionRows()
            triggerPageEnter(1)
        } else {
            showToast(studentApi.lastError())
        }
    }

    function optionText(question, key) {
        if (key === "A") return question.optionA || "--"
        if (key === "B") return question.optionB || "--"
        if (key === "C") return question.optionC || "--"
        return question.optionD || "--"
    }

    function isObjective(type) {
        var label = displayQuestionType(type)
        return label === "单选题" || label === "多选题" || label === "判断题"
    }

    function loadPracticeQuestions(type, difficulty, keyword) {
        practiceQuestions = studentApi.getPracticeQuestions(type || "", difficulty || "", keyword || "")
        activePracticeIndex = 0
        practiceAnswers = ({})
        practiceChecked = ({})
        showToast("已加载 " + practiceQuestions.length + " 道练习题")
    }

    property int activePracticeIndex: 0

    function currentPracticeQuestion() {
        if (practiceQuestions.length === 0) return ({})
        return practiceQuestions[Math.min(activePracticeIndex, practiceQuestions.length - 1)]
    }

    function practiceAnswerFor(questionId) {
        return practiceAnswers[String(questionId)] || ""
    }

    function setPracticeAnswer(questionId, value) {
        var next = {}
        for (var key in practiceAnswers) next[key] = practiceAnswers[key]
        next[String(questionId)] = value
        practiceAnswers = next
    }

    function practiceIsChecked(questionId) {
        return practiceChecked[String(questionId)] === true
    }

    function markPracticeChecked(questionId) {
        var next = {}
        for (var key in practiceChecked) next[key] = practiceChecked[key]
        next[String(questionId)] = true
        practiceChecked = next
    }

    function normalizePracticeAnswer(value) {
        return String(value || "").replace(/，/g, ",").replace(/；/g, ";").replace(/\s/g, "").toUpperCase()
    }

    function practiceIsCorrect(question) {
        if (isManualQuestion(question.type)) return false
        return normalizePracticeAnswer(practiceAnswerFor(question.id)) === normalizePracticeAnswer(question.answer)
    }

    function practiceOptionSelected(question, key) {
        var value = String(practiceAnswerFor(question.id))
        if (isMultipleChoice(question.type)) return value.indexOf(key) >= 0
        return value === key
    }

    function togglePracticeObjectiveAnswer(question, key) {
        if (!isMultipleChoice(question.type)) {
            setPracticeAnswer(question.id, key)
            return
        }

        var current = String(practiceAnswerFor(question.id))
        var next = ""
        for (var i = 0; i < 4; ++i) {
            var letter = ["A", "B", "C", "D"][i]
            var picked = current.indexOf(letter) >= 0
            if (letter === key) picked = !picked
            if (picked) next += letter
        }
        setPracticeAnswer(question.id, next)
    }

    function checkPracticeQuestion() {
        var question = currentPracticeQuestion()
        if (!question.id) {
            showToast("暂无练习题")
            return
        }
        if (practiceIsChecked(question.id)) {
            showToast("已查看解析")
            return
        }
        if (String(practiceAnswerFor(question.id)).trim().length === 0) {
            showToast("请先作答")
            return
        }
        var correct = practiceIsCorrect(question)
        var saved = studentApi.savePracticeAnswer(Number(question.id || 0), practiceAnswerFor(question.id), correct, "题库练习")
        if (!saved) {
            showToast(studentApi.lastError() || "练习记录保存失败")
            return
        }
        subjectCards = studentApi.getPracticeSubjectStats()
        if (!correct) wrongQuestionRows = studentApi.getWrongQuestions()
        aiSuggestions = aiSuggestionRows()
        markPracticeChecked(question.id)
        showToast(correct ? "回答正确" : "已显示答案解析")
    }

    function shuffledRows(rows) {
        var copy = []
        for (var i = 0; i < rows.length; ++i) copy.push(rows[i])
        for (var j = copy.length - 1; j > 0; --j) {
            var swapIndex = Math.floor(Math.random() * (j + 1))
            var temp = copy[j]
            copy[j] = copy[swapIndex]
            copy[swapIndex] = temp
        }
        return copy
    }

    function startPracticeMockExam(count) {
        var pool = practiceQuestions.length > 0 ? practiceQuestions : studentApi.getPracticeQuestions("", "", "")
        if (pool.length === 0) {
            showToast("题库暂无可用题目")
            return
        }
        var picked = shuffledRows(pool).slice(0, Math.min(Number(count || 10), pool.length))
        practiceExamQuestions = picked
        practiceExamAnswers = ({})
        activePracticeExamIndex = 0
        practiceExamFinished = false
        examMode = false
        currentPage = 2
        practiceMode = 0
        practiceExamMode = true
        triggerPageEnter(1)
        showToast("已随机生成 " + picked.length + " 道题")
    }

    function currentWrongQuestion() {
        if (wrongQuestionRows.length === 0) return ({})
        return wrongQuestionRows[Math.min(activeWrongQuestionIndex, wrongQuestionRows.length - 1)]
    }

    function currentPracticeExamQuestion() {
        if (practiceExamQuestions.length === 0) return ({})
        return practiceExamQuestions[Math.min(activePracticeExamIndex, practiceExamQuestions.length - 1)]
    }

    function practiceExamAnswerFor(questionId) {
        return practiceExamAnswers[String(questionId)] || ""
    }

    function setPracticeExamAnswer(questionId, value) {
        var next = {}
        for (var key in practiceExamAnswers) next[key] = practiceExamAnswers[key]
        next[String(questionId)] = value
        practiceExamAnswers = next
    }

    function practiceExamAnsweredCount() {
        var count = 0
        for (var i = 0; i < practiceExamQuestions.length; ++i) {
            if (String(practiceExamAnswerFor(practiceExamQuestions[i].id)).trim().length > 0) count += 1
        }
        return count
    }

    function practiceExamOptionSelected(question, key) {
        var value = String(practiceExamAnswerFor(question.id))
        if (isMultipleChoice(question.type)) return value.indexOf(key) >= 0
        return value === key
    }

    function togglePracticeExamObjectiveAnswer(question, key) {
        if (!isMultipleChoice(question.type)) {
            setPracticeExamAnswer(question.id, key)
            return
        }

        var current = String(practiceExamAnswerFor(question.id))
        var next = ""
        for (var i = 0; i < 4; ++i) {
            var letter = ["A", "B", "C", "D"][i]
            var picked = current.indexOf(letter) >= 0
            if (letter === key) picked = !picked
            if (picked) next += letter
        }
        setPracticeExamAnswer(question.id, next)
    }

    function practiceExamIsCorrect(question) {
        if (isManualQuestion(question.type)) return false
        return normalizePracticeAnswer(practiceExamAnswerFor(question.id)) === normalizePracticeAnswer(question.answer)
    }

    function practiceExamCorrectCount() {
        var count = 0
        for (var i = 0; i < practiceExamQuestions.length; ++i) {
            if (practiceExamIsCorrect(practiceExamQuestions[i])) count += 1
        }
        return count
    }

    function practiceExamObjectiveCount() {
        var count = 0
        for (var i = 0; i < practiceExamQuestions.length; ++i) {
            if (!isManualQuestion(practiceExamQuestions[i].type)) count += 1
        }
        return count
    }

    function practiceExamScoreText() {
        var total = practiceExamObjectiveCount()
        if (total === 0) return "待批改"
        return String(Math.round(practiceExamCorrectCount() / total * 100))
    }

    function submitPracticeMockExam() {
        if (practiceExamQuestions.length === 0) {
            showToast("暂无模拟卷")
            return
        }
        var savedCount = 0
        var failedCount = 0
        for (var i = 0; i < practiceExamQuestions.length; ++i) {
            var question = practiceExamQuestions[i]
            var answer = practiceExamAnswerFor(question.id)
            if (String(answer).trim().length === 0) continue
            if (studentApi.savePracticeAnswer(Number(question.id || 0), answer, practiceExamIsCorrect(question), "随机组卷")) savedCount += 1
            else failedCount += 1
        }
        subjectCards = studentApi.getPracticeSubjectStats()
        wrongQuestionRows = studentApi.getWrongQuestions()
        aiSuggestions = aiSuggestionRows()
        practiceExamFinished = true
        showToast(failedCount > 0 ? ("模拟答题已完成，" + failedCount + " 条记录保存失败") : ("模拟答题已完成，已保存 " + savedCount + " 条练习记录，客观题得分 " + practiceExamScoreText()))
    }

    function optionSelected(question, key) {
        var value = String(answerFor(question.id))
        if (isMultipleChoice(question.type)) return value.indexOf(key) >= 0
        return value === key
    }

    function toggleObjectiveAnswer(question, key) {
        if (!isMultipleChoice(question.type)) {
            setAnswer(question.id, key)
            return
        }

        var current = String(answerFor(question.id))
        var next = ""
        for (var i = 0; i < 4; ++i) {
            var letter = ["A", "B", "C", "D"][i]
            var picked = current.indexOf(letter) >= 0
            if (letter === key) picked = !picked
            if (picked) next += letter
        }
        setAnswer(question.id, next)
    }

    function showToast(text) {
        toastText = text
        toastTimer.restart()
    }

    function reportSummaryValue(key, fallback) {
        var summary = scoreReport.summary || {}
        return summary[key] !== undefined ? summary[key] : fallback
    }

    function displayNumber(value) {
        var number = Number(value || 0)
        return String(Math.round(number * 10) / 10)
    }

    function myScore() {
        var rows = scoreReport.scores || []
        var currentNo = String(profile.studentNo || profile.username || "")
        for (var i = 0; i < rows.length; ++i) {
            var row = rows[i]
            var rowNo = String(row.studentNo || row.student_no || "")
            if (rowNo === currentNo) {
                return displayNumber(row.totalScore !== undefined ? row.totalScore : row.total_score)
            }
        }
        return rows.length > 0 ? "未出" : "--"
    }

    function reportExamRows() {
        var rows = []
        for (var h = scoreHistory.length - 1; h >= 0; --h) {
            var item = scoreHistory[h]
            rows.push({
                "id": item.id || item.examId,
                "title": item.title || item.name || "未命名考试",
                "subject": item.subject || "综合",
                "score": item.score,
                "totalScore": item.full || item.fullScore || 100,
                "date": item.date,
                "startTime": item.date,
                "status": "已完成",
                "className": item.className || profile.className
            })
        }
        if (rows.length > 0) return rows
        rows = examRows()
        var result = []
        for (var i = 0; i < rows.length; ++i) {
            if (examStatus(rows[i], i) === "已完成") result.push(rows[i])
        }
        return result
    }

    function currentReportExam() {
        var rows = reportExamRows()
        for (var i = 0; i < rows.length; ++i) {
            if (Number(rows[i].id || 0) === activeExamId) return rows[i]
        }
        return rows.length > 0 ? rows[0] : selectedExam()
    }

    function activeReportExamIndex() {
        var rows = reportExamRows()
        for (var i = 0; i < rows.length; ++i) {
            if (Number(rows[i].id || 0) === activeExamId) return i
        }
        return 0
    }

    function selectReportExam(index) {
        var rows = reportExamRows()
        if (index < 0 || index >= rows.length) return
        selectExam(rows[index])
        activeReportSubject = examSubject(rows[index])
    }

    function reportFullScore() {
        var exam = currentReportExam()
        var full = Number(exam.totalScore || scoreReport.fullScore || scoreReport.paperScore || 100)
        return full > 0 ? full : 100
    }

    function reportTotalScoreNumber() {
        var direct = Number(scoreReport.personalScore || scoreReport.myScore || scoreReport.studentScore || 0)
        if (direct > 0) return Math.round(direct * 10) / 10
        var mine = Number(myScore())
        if (!isNaN(mine) && mine > 0) return Math.round(mine * 10) / 10
        var exam = currentReportExam()
        var examScore = Number(exam.score || 0)
        return examScore > 0 ? examScore : 0
    }

    function reportLostScore() {
        return Math.max(0, Math.round((reportFullScore() - reportTotalScoreNumber()) * 10) / 10)
    }

    function reportScoreLevel() {
        var percent = reportTotalScoreNumber() / Math.max(1, reportFullScore())
        if (percent >= 0.9) return "优秀"
        if (percent >= 0.8) return "良好"
        if (percent >= 0.6) return "合格"
        return "需加强"
    }

    function reportTypeRows() {
        var source = scoreReport.typeBreakdown || scoreReport.typeScores || scoreReport.typeScoreBreakdown || []
        var rows = []
        for (var i = 0; i < source.length; ++i) {
            var item = source[i]
            var full = Number(item.full || item.fullScore || item.total || item.totalScore || 0)
            var score = Number(item.score || item.earned || item.earnedScore || 0)
            var deduct = Number(item.deduct || item.deduction || item.lost || Math.max(0, full - score))
            rows.push({
                "type": item.type || item.name || item.label || "题型",
                "score": Math.round(score * 10) / 10,
                "full": full > 0 ? Math.round(full * 10) / 10 : 0,
                "deduct": Math.round(deduct * 10) / 10,
                "weak": item.weak || item.weakPoint || item.reason || "待分析",
                "color": item.color || ["#3b82f6", "#8b5cf6", "#22c55e", "#f59e0b", "#ef4444"][i % 5]
            })
        }
        return rows
    }

    function reportWeakKnowledgeRows() {
        var source = scoreReport.weakKnowledgePoints || scoreReport.weakAreas || scoreReport.knowledgeWeakness || []
        var rows = []
        for (var i = 0; i < source.length; ++i) {
            var item = source[i]
            rows.push({
                "name": item.name || item.knowledge || item.knowledgePoint || item.label || "知识点",
                "mastery": Number(item.mastery || item.rate || item.accuracy || 0),
                "lost": Number(item.lost || item.deduct || item.deduction || 0),
                "reason": item.reason || item.problem || item.description || "掌握不稳定",
                "advice": item.advice || item.suggestion || "结合错题重做同类题"
            })
        }
        return rows
    }

    function reportDeductionRows() {
        var source = scoreReport.deductionDetails || scoreReport.answerDetails || scoreReport.personalAnswers || []
        var rows = []
        for (var i = 0; i < source.length; ++i) {
            var item = source[i]
            var full = Number(item.full || item.fullScore || item.questionScore || item.paperScore || 0)
            var score = Number(item.score || item.earned || 0)
            var deduct = Number(item.deduct || item.deduction || Math.max(0, full - score))
            if (deduct <= 0 && score >= full) continue
            rows.push({
                "index": item.index || item.questionIndex || ("第" + (i + 1) + "题"),
                "type": item.type || "题目",
                "score": Math.round(score * 10) / 10,
                "full": full > 0 ? Math.round(full * 10) / 10 : "--",
                "deduct": Math.round(deduct * 10) / 10,
                "knowledge": item.knowledge || item.knowledgePoint || item.weak || "知识点待归纳",
                "reason": item.reason || item.comment || item.analysis || "该题未得满分，需要复盘作答过程"
            })
        }
        return rows
    }

    function saveProfileChanges(name, studentNo, className) {
        var ok = studentApi.updateProfile({"name": name, "studentNo": studentNo, "className": className})
        if (ok) {
            profile = studentApi.getStudentProfile()
            exams = studentApi.getPublishedExams()
            showToast("个人信息已保存")
            profileMode = 0
        } else {
            showToast(studentApi.lastError())
        }
    }

    function savePasswordChange(oldPassword, newPassword, confirmPassword) {
        if (newPassword !== confirmPassword) {
            showToast("两次输入的新密码不一致")
            return
        }
        var ok = studentApi.changePassword(oldPassword, newPassword)
        showToast(ok ? "密码已更新" : studentApi.lastError())
        if (ok) profileMode = 0
    }

    function saveSettingChanges(noticeEnabled, autoSaveEnabled, compactMode) {
        var ok = studentApi.saveSettings({
            "noticeEnabled": noticeEnabled,
            "autoSaveEnabled": autoSaveEnabled,
            "compactMode": compactMode
        })
        profile = studentApi.getStudentProfile()
        showToast(ok ? "考试设置已保存" : studentApi.lastError())
        if (ok) profileMode = 0
    }

    Timer {
        id: toastTimer
        interval: 2200
        repeat: false
        onTriggered: root.toastText = ""
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        StudentTopNav {
            Layout.fillWidth: true
            Layout.preferredHeight: (root.examMode || root.practiceExamMode) ? (root.narrowShell ? 58 : 68) : root.normalNavHeight
            visible: true
            z: 20
        }

        Loader {
            id: pageLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: root.examMode ? answerPageComponent : (root.practiceExamMode ? practiceMockExamPageComponent : root.pageComponent())
            clip: true
            transform: Translate { id: pageSlide; x: 0 }

            function runEnter() {
                pageEnter.stop()
                pageSlide.x = root.pageEnterDirection * 46
                pageLoader.opacity = 0
                pageEnter.restart()
            }

            Connections {
                target: root
                function onAnimationKeyChanged() {
                    pageLoader.runEnter()
                }
            }

            ParallelAnimation {
                id: pageEnter
                NumberAnimation { target: pageLoader; property: "opacity"; to: 1; duration: 330; easing.type: Easing.OutCubic }
                NumberAnimation { target: pageSlide; property: "x"; to: 0; duration: 360; easing.type: Easing.OutCubic }
            }
        }
    }

    Rectangle {
        width: Math.min(420, parent.width - 64)
        height: 48
        radius: 16
        color: "#102033"
        opacity: root.toastText.length > 0 ? 0.94 : 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.toastText.length > 0 ? 28 : -60
        z: 80
        Behavior on opacity { NumberAnimation { duration: 180 } }
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }
        Text { anchors.centerIn: parent; text: root.toastText; color: "#ffffff"; font.pixelSize: 14; font.bold: true }
    }

    Component { id: dashboardPageComponent; DashboardPage {} }
    Component { id: examListPageComponent; ExamListPage {} }
    Component { id: practicePageComponent; PracticePage {} }
    Component { id: practiceMockExamPageComponent; PracticeMockExamPageV2 {} }
    Component { id: gradeAnalysisPageComponent; GradeAnalysisPage {} }
    Component { id: scoreReportPageComponent; ScoreReportPage {} }
    Component { id: profilePageComponent; ProfilePage {} }
    Component { id: answerPageComponent; AnswerPage {} }

    component PageShell: Item {
        default property alias content: body.data
        Flickable {
            id: scroll
            anchors.fill: parent
            anchors.leftMargin: root.shellHMargin
            anchors.rightMargin: root.narrowShell ? 14 : 24
            anchors.topMargin: root.shellVMargin
            anchors.bottomMargin: root.narrowShell ? 18 : 28
            contentWidth: width
            contentHeight: body.height * root.contentScale + 4
            clip: true
            interactive: !root.innerScrollActive && contentHeight > height
            pixelAligned: false
            synchronousDrag: false
            boundsBehavior: Flickable.OvershootBounds
            boundsMovement: Flickable.FollowBoundsBehavior
            maximumFlickVelocity: 12000
            flickDeceleration: 3600
            ScrollBar.vertical: ScrollBar {
                policy: scroll.contentHeight > scroll.height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff
                width: 12
                contentItem: Rectangle { radius: 6; color: "#9fb3cc" }
                background: Rectangle { radius: 6; color: "#edf2f8" }
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

    component SectionTitle: Column {
        property string title: root.pageTitles[root.currentPage]
        property string subtitle: root.pageSubtitles[root.currentPage]
        width: parent.width
        spacing: root.narrowShell ? 4 : 6
        Text { width: parent.width; text: title; color: "#111827"; font.pixelSize: root.narrowShell ? 30 : (root.compactShell ? 38 : 44); font.bold: true; elide: Text.ElideRight }
        Text { width: parent.width; text: subtitle; color: "#64748b"; font.pixelSize: root.narrowShell ? 16 : 20; wrapMode: Text.WordWrap }
    }

    component FilterCombo: ComboBox {
        id: combo
        font.pixelSize: 18
        leftPadding: 18
        rightPadding: 42
        indicator: Text {
            x: combo.width - width - 16
            y: (combo.height - height) / 2
            text: "⌄"
            color: "#64748b"
            font.pixelSize: 22
            font.bold: true
        }
        contentItem: Text {
            text: combo.displayText
            color: "#0f172a"
            font.pixelSize: 18
            font.bold: true
            leftPadding: 18
            rightPadding: 34
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideNone
        }
        background: Rectangle {
            radius: 18
            color: combo.hovered || combo.activeFocus ? "#ffffff" : "#f8fbff"
            border.color: combo.activeFocus ? "#2563eb" : "#dbe7f6"
            border.width: 1
        }
        delegate: ItemDelegate {
            width: combo.width
            height: 50
            contentItem: Text {
                text: modelData
                color: highlighted ? "#2563eb" : "#0f172a"
                font.pixelSize: 17
                font.bold: highlighted
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                radius: 12
                color: highlighted ? "#eff6ff" : "#ffffff"
            }
        }
        popup: Popup {
            y: combo.height + 6
            width: combo.width
            implicitHeight: Math.min(240, listView.contentHeight + 12)
            padding: 6
            contentItem: ListView {
                id: listView
                clip: true
                implicitHeight: contentHeight
                model: combo.popup.visible ? combo.delegateModel : null
                currentIndex: combo.highlightedIndex
            }
            background: Rectangle {
                radius: 18
                color: "#ffffff"
                border.color: "#dbe7f6"
            }
        }
    }

    component Card: Item {
        id: card
        property real radius: 24
        property bool hoverable: false
        property int enterDelay: 0
        property int enterDirection: 1
        property real enterDistance: 34
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
            onTriggered: enterAnim.restart()
        }

        ParallelAnimation {
            id: enterAnim
            NumberAnimation { target: card; property: "opacity"; to: 1; duration: 380; easing.type: Easing.OutCubic }
            NumberAnimation { target: cardSlide; property: "x"; to: 0; duration: 400; easing.type: Easing.OutCubic }
        }

        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 12
            anchors.leftMargin: 4
            anchors.rightMargin: 4
            radius: card.radius
            color: "#0f172a"
            opacity: 0.07
        }
        Rectangle {
            id: body
            anchors.fill: parent
            radius: card.radius
            color: card.fillColor
            border.color: card.borderColor
            clip: true
        }
    }

    component LineChart: Canvas {
        id: chart
        property var points: []
        property var comparePoints: []
        property var labels: ["6/1", "6/8", "6/15", "6/22", "6/29", "7/5", "7/10"]
        property int hoverIndex: -1
        property real hoverX: 0
        property real hoverY: 0

        function valueBounds() {
            var values = []
            for (var a = 0; points && a < points.length; ++a) values.push(Number(points[a] || 0))
            for (var b = 0; comparePoints && b < comparePoints.length; ++b) values.push(Number(comparePoints[b] || 0))
            if (values.length === 0) return {"min": 0, "max": 100}
            var minValue = values[0]
            var maxValue = values[0]
            for (var i = 1; i < values.length; ++i) {
                minValue = Math.min(minValue, values[i])
                maxValue = Math.max(maxValue, values[i])
            }
            minValue = Math.max(0, Math.floor((minValue - 8) / 10) * 10)
            maxValue = Math.ceil((maxValue + 8) / 10) * 10
            if (maxValue - minValue < 20) maxValue = minValue + 20
            return {"min": minValue, "max": maxValue}
        }

        function pointPosition(values, index) {
            var left = 44
            var right = 18
            var top = 16
            var bottom = 34
            var plotW = Math.max(1, width - left - right)
            var plotH = Math.max(1, height - top - bottom)
            var bounds = valueBounds()
            var x = left + (values.length === 1 ? 0 : plotW / (values.length - 1) * index)
            var v = Math.max(bounds.min, Math.min(bounds.max, Number(values[index] || 0)))
            var y = top + (bounds.max - v) / Math.max(1, bounds.max - bounds.min) * plotH
            return {"x": x, "y": y}
        }

        function updateHover(mx, my) {
            if (!points || points.length === 0) {
                hoverIndex = -1
                requestPaint()
                return
            }

            var best = -1
            var bestDistance = 999999
            for (var i = 0; i < points.length; ++i) {
                var pos = pointPosition(points, i)
                var dx = mx - pos.x
                var dy = my - pos.y
                var distance = Math.sqrt(dx * dx + dy * dy)
                if (distance < bestDistance) {
                    bestDistance = distance
                    best = i
                    hoverX = pos.x
                    hoverY = pos.y
                }
            }

            hoverIndex = bestDistance <= 36 ? best : -1
            requestPaint()
        }

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var left = 44
            var right = 18
            var top = 16
            var bottom = 34
            var plotW = Math.max(1, width - left - right)
            var plotH = Math.max(1, height - top - bottom)
            var bounds = valueBounds()
            ctx.lineWidth = 1
            ctx.strokeStyle = "#eef2f7"
            ctx.font = "12px sans-serif"
            ctx.fillStyle = "#9ca3af"
            for (var i = 0; i <= 4; ++i) {
                var y = top + plotH / 4 * i
                ctx.beginPath()
                ctx.moveTo(left, y)
                ctx.lineTo(left + plotW, y)
                ctx.stroke()
                ctx.fillText(String(Math.round(bounds.max - (bounds.max - bounds.min) / 4 * i)), 8, y + 4)
            }

            function drawLine(values, color, alpha) {
                if (!values || values.length === 0) return
                ctx.globalAlpha = alpha
                ctx.lineWidth = 3
                ctx.strokeStyle = color
                ctx.beginPath()
                for (var p = 0; p < values.length; ++p) {
                    var x = left + (values.length === 1 ? 0 : plotW / (values.length - 1) * p)
                    var v = Math.max(bounds.min, Math.min(bounds.max, Number(values[p] || 0)))
                    var py = top + (bounds.max - v) / Math.max(1, bounds.max - bounds.min) * plotH
                    if (p === 0) ctx.moveTo(x, py)
                    else ctx.lineTo(x, py)
                }
                ctx.stroke()
                for (var d = 0; d < values.length; ++d) {
                    var dx = left + (values.length === 1 ? 0 : plotW / (values.length - 1) * d)
                    var dv = Math.max(bounds.min, Math.min(bounds.max, Number(values[d] || 0)))
                    var dy = top + (bounds.max - dv) / Math.max(1, bounds.max - bounds.min) * plotH
                    ctx.beginPath()
                    ctx.arc(dx, dy, 4, 0, Math.PI * 2)
                    ctx.fillStyle = color
                    ctx.fill()
                }
                ctx.globalAlpha = 1
            }

            drawLine(comparePoints, "#94a3b8", 0.7)
            drawLine(points, "#22c55e", 1)
            ctx.fillStyle = "#8b949e"
            var labelCount = labels ? labels.length : 0
            for (var l = 0; l < labelCount; ++l) {
                var lx = left + plotW / Math.max(1, labelCount - 1) * l
                ctx.fillText(labels[l], lx - 12, height - 10)
            }

            if (hoverIndex >= 0 && hoverIndex < points.length) {
                var hoverPos = pointPosition(points, hoverIndex)
                ctx.beginPath()
                ctx.arc(hoverPos.x, hoverPos.y, 10, 0, Math.PI * 2)
                ctx.fillStyle = "rgba(34, 197, 94, 0.18)"
                ctx.fill()
                ctx.beginPath()
                ctx.arc(hoverPos.x, hoverPos.y, 6, 0, Math.PI * 2)
                ctx.fillStyle = "#22c55e"
                ctx.fill()
                ctx.beginPath()
                ctx.arc(hoverPos.x, hoverPos.y, 3, 0, Math.PI * 2)
                ctx.fillStyle = "#ffffff"
                ctx.fill()
            }
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPointsChanged: requestPaint()
        onComparePointsChanged: requestPaint()
        onLabelsChanged: requestPaint()

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
            onPositionChanged: (mouse) => chart.updateHover(mouse.x, mouse.y)
            onExited: {
                chart.hoverIndex = -1
                chart.requestPaint()
            }
        }

        Rectangle {
            width: 132
            height: chart.hoverIndex >= 0 && chart.comparePoints && chart.comparePoints.length > chart.hoverIndex ? 72 : 56
            radius: 14
            color: "#111827"
            opacity: chart.hoverIndex >= 0 ? 0.94 : 0
            visible: opacity > 0
            x: Math.max(4, Math.min(chart.hoverX - width / 2, chart.width - width - 4))
            y: Math.max(4, chart.hoverY - height - 16)
            z: 20
            Behavior on opacity { NumberAnimation { duration: 120 } }
            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 4
                Text {
                    width: parent.width
                    text: chart.hoverIndex >= 0 ? (chart.labels[chart.hoverIndex] || ("第 " + (chart.hoverIndex + 1) + " 次")) : ""
                    color: "#cbd5e1"
                    font.pixelSize: 12
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    width: parent.width
                    text: chart.hoverIndex >= 0 ? ("我的成绩 " + chart.points[chart.hoverIndex] + " 分") : ""
                    color: "#4ade80"
                    font.pixelSize: 14
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    width: parent.width
                    visible: chart.hoverIndex >= 0 && chart.comparePoints && chart.comparePoints.length > chart.hoverIndex
                    text: chart.hoverIndex >= 0 && chart.comparePoints && chart.comparePoints.length > chart.hoverIndex ? ("班级均分 " + chart.comparePoints[chart.hoverIndex] + " 分") : ""
                    color: "#cbd5e1"
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    component BarChart: Canvas {
        id: barsChart
        property var bars: []
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var left = 18
            var right = 18
            var top = 16
            var bottom = 34
            var plotW = Math.max(1, width - left - right)
            var plotH = Math.max(1, height - top - bottom)
            var count = Math.max(1, bars.length)
            var gap = 12
            var barW = Math.max(18, (plotW - gap * (count - 1)) / count)
            var maxValue = 1
            for (var m = 0; m < bars.length; ++m) maxValue = Math.max(maxValue, Number(bars[m] || 0))
            for (var i = 0; i < count; ++i) {
                var value = Number(bars[i] || 0)
                var h = value <= 0 ? 0 : Math.max(8, plotH * value / maxValue)
                var x = left + i * (barW + gap)
                var y = top + plotH - h
                ctx.fillStyle = i >= count - 2 ? "#22c55e" : "#bfdbfe"
                ctx.fillRect(x, y, barW, h)
                ctx.fillStyle = "#8b949e"
                ctx.font = "12px sans-serif"
                ctx.fillText(["一","二","三","四","五","六","日"][i] || "", x + barW / 2 - 6, height - 10)
            }
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onBarsChanged: requestPaint()
    }

    component MetricCard: Card {
        id: metric
        property string label: ""
        property string value: ""
        property string hint: ""
        property color accent: "#2563eb"
        height: 156
        Item {
            anchors.fill: parent
            anchors.margins: 22
            Rectangle { width: 4; height: parent.height - 8; radius: 2; color: metric.accent; opacity: 0.88; anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 18
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8
                Text { text: metric.label; color: "#64748b"; font.pixelSize: 15; font.bold: true }
                Text { text: metric.value; color: "#111827"; font.pixelSize: 40; font.bold: true }
                Text { text: metric.hint; color: "#8a94a6"; font.pixelSize: 12; elide: Text.ElideRight; width: parent.width }
            }
        }
    }

    component DashboardPage: PageShell {
        Card {
            width: parent.width
            height: root.narrowShell ? 480 : (root.compactShell ? 390 : 350)
            Rectangle {
                anchors.fill: parent
                radius: 24
                color: "#121a34"
                clip: true
                Rectangle { width: 360; height: 360; radius: 180; color: "#22c55e"; opacity: 0.18; x: -80; y: -130 }
                Rectangle { width: 520; height: 520; radius: 260; color: "#0ea5e9"; opacity: 0.12; anchors.right: parent.right; anchors.rightMargin: 90; y: -20 }
                Rectangle { anchors.fill: parent; color: "#071224"; opacity: 0.34 }
                GridLayout {
                    anchors.fill: parent
                    anchors.leftMargin: root.narrowShell ? 22 : 36
                    anchors.rightMargin: root.narrowShell ? 22 : 32
                    anchors.topMargin: root.narrowShell ? 24 : 34
                    anchors.bottomMargin: root.narrowShell ? 24 : 34
                    columns: root.narrowShell ? 1 : 2
                    columnSpacing: root.narrowShell ? 18 : 34
                    rowSpacing: root.narrowShell ? 18 : 34
                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: !root.narrowShell
                        Layout.alignment: root.narrowShell ? Qt.AlignTop : Qt.AlignVCenter
                        spacing: root.narrowShell ? 12 : 18
                        RowLayout {
                            spacing: 10
                            Text { text: root.studyStreakDays() > 0 ? ("连续记录 " + root.studyStreakDays() + " 天") : "暂无连续记录"; color: "#cbd5e1"; font.pixelSize: 15; font.bold: true }
                            Rectangle {
                                Layout.preferredWidth: 92
                                Layout.preferredHeight: 28
                                radius: 14
                                color: "#4b3428"
                                Text { anchors.centerIn: parent; text: "真实数据"; color: "#f59e0b"; font.pixelSize: 12; font.bold: true }
                            }
                        }
                        Text { Layout.fillWidth: true; text: "下午好，" + root.profileName(); color: "#ffffff"; font.pixelSize: root.narrowShell ? 30 : (root.compactShell ? 36 : 44); font.bold: true; elide: Text.ElideRight }
                        Text {
                            Layout.fillWidth: true
                            text: root.dashboardHeroSubtitle()
                            color: "#aab4c3"
                            font.pixelSize: root.narrowShell ? 14 : 18
                            wrapMode: Text.WordWrap
                        }
                        Flow {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                            spacing: 10
                            PrimaryButton { width: root.narrowShell ? Math.min(150, parent.width) : 150; text: "进入考试"; onClicked: root.switchPage(1) }
                            SoftButton { width: root.narrowShell ? Math.min(150, parent.width) : 150; text: "刷题练习"; onClicked: root.switchPage(2) }
                        }
                    }
                    Rectangle {
                        Layout.fillWidth: root.narrowShell
                        Layout.preferredWidth: root.narrowShell ? Math.max(260, parent.width) : (root.compactShell ? 360 : 430)
                        Layout.preferredHeight: root.narrowShell ? 210 : 244
                        Layout.alignment: root.narrowShell ? Qt.AlignHCenter : (Qt.AlignRight | Qt.AlignVCenter)
                        radius: 22
                        color: "#26324a"
                        opacity: 0.86
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
                            opacity: 0.55
                        }
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: root.narrowShell ? 18 : 26
                            spacing: root.narrowShell ? 10 : 14
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
                                Text { text: "下一场考试"; color: "#cbd5e1"; font.pixelSize: 15; font.bold: true }
                            }
                            Text { Layout.fillWidth: true; text: root.nextExam().id || root.nextExam().examId ? root.examTitle(root.nextExam()) : "暂无待参加考试"; color: "#ffffff"; font.pixelSize: root.narrowShell ? 20 : 24; font.bold: true; wrapMode: Text.WordWrap }
                            Text { text: root.nextExam().id || root.nextExam().examId ? root.formatExamTime(root.nextExam()) : "完成考试后会展示最新安排"; color: "#aab4c3"; font.pixelSize: 14 }
                            RowLayout {
                                Layout.fillWidth: true
                                spacing: 12
                                CountdownBox { Layout.fillWidth: true; number: root.countdownParts(root.nextExam()).days; label: "天" }
                                CountdownBox { Layout.fillWidth: true; number: root.countdownParts(root.nextExam()).hours; label: "时" }
                                CountdownBox { Layout.fillWidth: true; number: root.countdownParts(root.nextExam()).minutes; label: "分" }
                            }
                        }
                    }
                }
            }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1050 ? 4 : (parent.width > 560 ? 2 : 1)
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            HomeStatCard { Layout.fillWidth: true; label: "即将考试"; value: String(root.upcomingExamCount()); tag: "待参加"; accent: "#4f7df3" }
            HomeStatCard { Layout.fillWidth: true; label: "已完成考试"; value: String(root.completedExamCount()); tag: "已归档"; accent: "#34c6a2" }
            HomeStatCard { Layout.fillWidth: true; label: "平均成绩"; value: root.averageScoreText(); tag: root.averageScoreDeltaText(); accent: "#8b5cf6" }
            HomeStatCard { Layout.fillWidth: true; label: "连续记录"; value: root.studyStreakDays() + "天"; tag: "按成绩日期"; accent: "#f5a623" }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1160 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            TrendChartCard {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1160 ? 2 : 1
                Layout.preferredHeight: root.narrowShell ? 310 : 360
                title: "成绩趋势"
                subtitle: "过去 7 次考试表现"
                points: root.subjectTrendPoints(root.activeReportSubject)
                comparePoints: root.classTrendPointsFor(root.activeReportSubject)
                labels: root.trendLabelsFor(root.activeReportSubject)
            }
            UpcomingExamPanel { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 320 : 360 }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1160 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            RecentScorePanel { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 320 : 360 }
            ActivityBarPanel { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 300 : 360 }
            AchievementPanel { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 300 : 360 }
        }
    }

    component CountdownBox: Rectangle {
        property string number: "00"
        property string label: ""
        Layout.preferredWidth: 86
        Layout.preferredHeight: 76
        radius: 18
        color: "#3b465c"
        opacity: 0.94
        Column {
            anchors.centerIn: parent
            spacing: 3
            Text { text: number; color: "#4ade80"; font.pixelSize: 28; font.bold: true; horizontalAlignment: Text.AlignHCenter }
            Text { text: label; color: "#aab4c3"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter }
        }
    }

    component HomeStatCard: Card {
        id: stat
        property string label: ""
        property string value: ""
        property string tag: ""
        property color accent: "#22c55e"
        height: root.narrowShell ? 128 : 154
        radius: 24
        fillColor: "#ffffff"
        borderColor: "#e5edf6"
        Item {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 26
            Rectangle {
                width: 5
                height: parent.height - 16
                radius: 3
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                color: stat.accent
                opacity: 0.95
            }
            Rectangle {
                width: Math.max(86, tagText.implicitWidth + 32)
                height: 34
                radius: 17
                anchors.top: parent.top
                anchors.right: parent.right
                color: "#ecfdf3"
                Text {
                    id: tagText
                    anchors.centerIn: parent
                    text: stat.tag
                    color: "#22c55e"
                    font.pixelSize: 14
                    font.bold: true
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 28
                anchors.right: parent.right
                anchors.rightMargin: root.narrowShell ? 72 : 96
                anchors.top: parent.top
                anchors.topMargin: 8
                spacing: root.narrowShell ? 12 : 18
                Text { width: parent.width; text: stat.label; color: "#536784"; font.pixelSize: root.narrowShell ? 15 : 17; font.bold: true; elide: Text.ElideRight }
                Text { text: stat.value; color: "#071226"; font.pixelSize: root.narrowShell ? 32 : 42; font.bold: true }
            }
            Rectangle {
                width: 76
                height: 6
                radius: 3
                anchors.left: parent.left
                anchors.leftMargin: 28
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -18
                color: Qt.rgba(stat.accent.r, stat.accent.g, stat.accent.b, 0.34)
            }
        }
    }

    component TrendChartCard: Card {
        id: trend
        property string title: "成绩趋势"
        property string subtitle: ""
        property var points: []
        property var comparePoints: []
        property var labels: []
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4
                    Text { text: trend.title; color: "#111827"; font.pixelSize: 22; font.bold: true }
                    Text { text: trend.subtitle; color: "#8b949e"; font.pixelSize: 13 }
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: trend.comparePoints && trend.comparePoints.length > 0 ? 24 : 0
                visible: trend.comparePoints && trend.comparePoints.length > 0
                spacing: 18
                LegendDot { colorValue: "#22c55e"; label: "个人曲线" }
                LegendDot { colorValue: "#94a3b8"; label: "班级曲线" }
                Item { Layout.fillWidth: true }
            }
            LineChart {
                Layout.fillWidth: true
                Layout.fillHeight: true
                points: trend.points
                comparePoints: trend.comparePoints
                labels: trend.labels
            }
            Text {
                Layout.fillWidth: true
                visible: !trend.points || trend.points.length === 0
                text: "暂无成绩数据"
                color: "#94a3b8"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    component UpcomingExamPanel: Card {
        id: upcoming
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                Text { text: "即将考试"; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
            }
            Flickable {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: width
                contentHeight: upcomingColumn.height
                clip: true
                interactive: contentHeight > height
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                Column {
                    id: upcomingColumn
                    width: parent.width
                    spacing: 12
                    Repeater {
                        model: root.upcomingExamRows(true)
                        delegate: UpcomingExamItem {
                            width: upcomingColumn.width
                            exam: modelData.exam
                            rowIndex: modelData.rowIndex
                        }
                    }
                }
            }
        }
    }

    component UpcomingExamItem: Rectangle {
        id: item
        property var exam: ({})
        property int rowIndex: 0
        height: 86
        radius: 20
        color: "#f8fafc"
        border.color: "#e5e7eb"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 14
            Rectangle {
                Layout.preferredWidth: 52
                Layout.preferredHeight: 52
                radius: 18
                color: root.subjectAccent(root.examSubject(item.exam))
                Text { anchors.centerIn: parent; text: root.examSubject(item.exam).charAt(0); color: "#ffffff"; font.pixelSize: 22; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text { Layout.fillWidth: true; text: root.examTitle(item.exam); color: "#111827"; font.pixelSize: 16; font.bold: true; elide: Text.ElideRight }
                Text { Layout.fillWidth: true; text: "科目：" + root.examSubject(item.exam); color: "#2563eb"; font.pixelSize: 12; font.bold: true; elide: Text.ElideRight }
                Text { text: (item.exam.startTime || "2026-07-15 09:00") + "    " + (item.exam.duration || 90) + " 分钟"; color: "#6b7280"; font.pixelSize: 12 }
            }
            Rectangle {
                Layout.preferredWidth: 78
                Layout.preferredHeight: 34
                radius: 17
                color: "#eff6ff"
                Text { anchors.centerIn: parent; text: root.examCountdownLabel(item.exam, item.rowIndex); color: "#3b82f6"; font.pixelSize: 14; font.bold: true }
            }
        }
    }

    component RecentScorePanel: Card {
        id: recentScores
        property var rows: root.recentDashboardScoreRows(3)
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "近期成绩"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: recentScores.rows.length === 0
                text: "暂无成绩记录"
                color: "#94a3b8"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Repeater {
                model: recentScores.rows
                delegate: ScoreListRow { Layout.fillWidth: true; row: modelData }
            }
        }
    }

    component ScoreListRow: Rectangle {
        id: row
        property var row: ({})
        height: 72
        radius: 18
        color: "#ffffff"
        border.color: "#eef2f7"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 12
            Rectangle {
                Layout.preferredWidth: 44
                Layout.preferredHeight: 44
                radius: 16
                color: "#f8fafc"
                border.color: row.row.color || "#22c55e"
                Text { anchors.centerIn: parent; text: String(row.row.score); color: row.row.color || "#22c55e"; font.pixelSize: 17; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 2
                Text { Layout.fillWidth: true; text: row.row.name; color: "#111827"; font.pixelSize: 14; font.bold: true; elide: Text.ElideRight }
                Text { text: (row.row.subject || "综合") + " · " + row.row.rank; color: "#8b949e"; font.pixelSize: 12 }
            }
            Rectangle { Layout.preferredWidth: 58; Layout.preferredHeight: 28; radius: 14; color: "#ecfdf3"; Text { anchors.centerIn: parent; text: row.row.level; color: row.row.color; font.pixelSize: 12; font.bold: true } }
        }
    }

    component ActivityBarPanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            Text { text: "本周考试记录"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            BarChart { Layout.fillWidth: true; Layout.fillHeight: true; bars: root.dashboardActivityBars() }
            Text {
                Layout.fillWidth: true
                visible: root.dashboardActivityTotal() === 0
                text: "暂无本周考试记录"
                color: "#94a3b8"
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    component AchievementPanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "成就徽章"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 2
                columnSpacing: 10
                rowSpacing: 10
                Repeater {
                    model: root.achievementRows()
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 54
                        radius: 18
                        color: index % 2 === 0 ? "#ecfdf3" : "#eff6ff"
                        Text { anchors.centerIn: parent; text: modelData; color: index % 2 === 0 ? "#16a34a" : "#3b82f6"; font.pixelSize: 13; font.bold: true }
                    }
                }
            }
        }
    }

    component ExamListPage: PageShell {
        id: examPage
        property string activeStatus: "全部"
        RowLayout {
            width: parent.width
            spacing: 18
            SectionTitle { Layout.fillWidth: true; title: "我的考试"; subtitle: "查看所有考试安排、参加考试、查看成绩" }
            StatusCountBadge { label: "待参加"; value: "2"; accent: "#f59e0b" }
            StatusCountBadge { label: "已完成"; value: "3"; accent: "#22c55e" }
        }
        Card {
            width: parent.width
            height: root.narrowShell ? 154 : 104
            Flow {
                anchors.fill: parent
                anchors.margins: 22
                spacing: 14
                TextField {
                    id: examSearch
                    width: root.narrowShell ? parent.width : Math.max(260, parent.width - 4 * 110 - 56)
                    height: 48
                    placeholderText: "搜索考试名称或科目"
                    verticalAlignment: TextInput.AlignVCenter
                    leftPadding: 18
                    rightPadding: 18
                    color: "#111827"
                    placeholderTextColor: "#94a3b8"
                    font.pixelSize: 15
                    background: Rectangle { radius: 16; color: "#ffffff"; border.color: examSearch.activeFocus ? "#22c55e" : "#e5edf6" }
                }
                Repeater {
                    model: ["全部", "待参加", "已完成", "未开放"]
                    delegate: Rectangle {
                        width: root.narrowShell ? Math.max(72, (parent.width - 42) / 4) : 96
                        height: 44
                        radius: 16
                        color: examPage.activeStatus === modelData ? "#ecfdf3" : "#ffffff"
                        border.color: examPage.activeStatus === modelData ? "#bbf7d0" : "#e5edf6"
                        Text { anchors.centerIn: parent; text: modelData; color: examPage.activeStatus === modelData ? "#16a34a" : "#64748b"; font.pixelSize: 13; font.bold: true }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: examPage.activeStatus = modelData }
                    }
                }
            }
        }
        GridLayout {
            width: parent.width
            columns: parent.width > 980 ? 2 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            Repeater {
                model: root.filteredExamRows(examSearch.text, examPage.activeStatus)
                delegate: ExamGridCard {
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.narrowShell ? 286 : 258
                    exam: modelData
                    rowIndex: index
                }
            }
        }
    }

    component StatusCountBadge: Rectangle {
        id: badge
        property string label: ""
        property string value: ""
        property color accent: "#22c55e"
        Layout.preferredWidth: 116
        Layout.preferredHeight: 44
        radius: 18
        color: "#ffffff"
        border.color: "#e5edf6"
        Row {
            anchors.centerIn: parent
            spacing: 8
            Rectangle {
                width: 22
                height: 22
                radius: 11
                color: badge.accent
                Text { anchors.centerIn: parent; text: badge.value; color: "#ffffff"; font.pixelSize: 12; font.bold: true }
            }
            Text { text: badge.label; color: "#111827"; font.pixelSize: 13; font.bold: true; anchors.verticalCenter: parent.verticalCenter }
        }
    }

    component ExamGridCard: Card {
        id: card
        property var exam: ({})
        property int rowIndex: 0
        property string status: root.examStatus(exam, rowIndex)
        property color accent: root.subjectAccent(root.examSubject(exam))
        Rectangle { anchors.left: parent.left; anchors.top: parent.top; anchors.right: parent.right; height: 6; radius: 3; color: card.accent }
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 10
            RowLayout {
                Layout.fillWidth: true
                spacing: 14
                Rectangle {
                    Layout.preferredWidth: 52
                    Layout.preferredHeight: 52
                    radius: 16
                    color: card.accent
                    Text { anchors.centerIn: parent; text: root.examSubject(card.exam).charAt(0); color: "#ffffff"; font.pixelSize: 20; font.bold: true }
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 3
                    Text { text: root.examSubject(card.exam); color: "#8b949e"; font.pixelSize: 12 }
                    Text { Layout.fillWidth: true; text: root.examTitle(card.exam); color: "#111827"; font.pixelSize: 18; font.bold: true; elide: Text.ElideRight }
                }
                Rectangle {
                    Layout.preferredWidth: 78
                    Layout.preferredHeight: 34
                    radius: 17
                    color: card.status === "已完成" ? "#ecfdf3" : (card.status === "未开放" ? "#f3f4f6" : "#fff7ed")
                    Text { anchors.centerIn: parent; text: (card.status === "待参加" ? "◷ " : (card.status === "已完成" ? "✓ " : "⌂ ")) + card.status; color: card.status === "已完成" ? "#16a34a" : (card.status === "未开放" ? "#64748b" : "#f59e0b"); font.pixelSize: 12; font.bold: true }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                ExamInfoChip { Layout.fillWidth: true; icon: "▣"; text: (card.exam.startTime || "2026-07-15").slice(0, 10) }
                ExamInfoChip { Layout.fillWidth: true; icon: "◷"; text: (card.exam.duration || 90) + " 分钟" }
                ExamInfoChip { Layout.fillWidth: true; icon: "☷"; text: card.status === "未开放" ? "-- 人" : (card.rowIndex % 2 === 0 ? "48 人" : "52 人") }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: card.status === "已完成" ? 64 : 52
                radius: 16
                color: card.status === "已完成" ? Qt.rgba(card.accent.r, card.accent.g, card.accent.b, 0.07) : "#fffaf5"
                border.color: card.status === "已完成" ? Qt.rgba(card.accent.r, card.accent.g, card.accent.b, 0.20) : "#fed7aa"
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 18
                    anchors.rightMargin: 18
                    spacing: 12
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 2
                        Text {
                            text: card.status === "已完成" ? (root.examCountdownLabel(card.exam, card.rowIndex).replace(" 分", "")) : "考试时间： " + (card.exam.startTime || "--") + "–" + (card.exam.endTime || "--").split(" ")[1]
                            color: card.status === "已完成" ? card.accent : "#6b7280"
                            font.pixelSize: card.status === "已完成" ? 30 : 14
                            font.bold: true
                        }
                        Text {
                            visible: card.status === "已完成"
                            text: "满分 " + (card.exam.totalScore || 100) + "    班级第 " + (card.rowIndex === 2 ? "1" : "4") + " 名"
                            color: card.accent
                            font.pixelSize: 12
                            font.bold: true
                        }
                    }
                    Rectangle {
                        Layout.preferredWidth: card.status === "已完成" ? 58 : 68
                        Layout.preferredHeight: 32
                        radius: 16
                        color: card.status === "已完成" ? "#ecfdf3" : "#fff7ed"
                        Text { anchors.centerIn: parent; text: card.status === "已完成" ? (Number(root.examCountdownLabel(card.exam, card.rowIndex).replace(" 分", "")) >= 90 ? "优秀" : "良好") : root.examCountdownLabel(card.exam, card.rowIndex); color: card.status === "已完成" ? "#16a34a" : "#f59e0b"; font.pixelSize: 12; font.bold: true }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                PrimaryButton {
                    Layout.fillWidth: true
                    text: card.status === "待参加" ? "▷ 进入考试" : (card.status === "已完成" ? "查看成绩报告 ›" : "未开放")
                    enabled: card.status !== "未开放"
                    onClicked: card.status === "待参加" ? root.startExam(card.exam) : root.openScoreReport(card.exam)
                }
            }
        }
    }

    component ExamInfoChip: Rectangle {
        id: chip
        property string icon: ""
        property string text: ""
        Layout.preferredHeight: 34
        radius: 14
        color: "#f8fafc"
        Row {
            anchors.centerIn: parent
            spacing: 7
            Text { text: chip.icon; color: "#94a3b8"; font.pixelSize: 13; anchors.verticalCenter: parent.verticalCenter }
            Text { text: chip.text; color: "#6b7280"; font.pixelSize: 12; anchors.verticalCenter: parent.verticalCenter }
        }
    }

    component ExamMiniMetric: Rectangle {
        id: metric
        property string label: ""
        property string value: ""
        property color accent: "#22c55e"
        Layout.preferredHeight: 58
        radius: 16
        color: "#f8fafc"
        border.color: "#eef2f7"
        Column {
            anchors.centerIn: parent
            spacing: 4
            Text { text: metric.value; color: metric.accent; font.pixelSize: 15; font.bold: true; horizontalAlignment: Text.AlignHCenter }
            Text { text: metric.label; color: "#94a3b8"; font.pixelSize: 11; horizontalAlignment: Text.AlignHCenter }
        }
    }

    component ExamRow: Rectangle {
        id: row
        property var exam: ({})
        property bool selected: false
        signal startRequested()
        signal selectRequested()
        height: 78
        radius: 18
        color: selected ? "#eef6ff" : "#ffffff"
        border.color: selected ? "#bfdbfe" : "#e5edf6"
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            cursorShape: Qt.PointingHandCursor
            onClicked: row.selectRequested()
        }
        RowLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 12
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text { text: row.exam.title || row.exam.name || "--"; color: "#111827"; font.pixelSize: 15; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                Text { text: (row.exam.subject || "综合") + " · " + (row.exam.startTime || "--"); color: "#64748b"; font.pixelSize: 12; Layout.fillWidth: true; elide: Text.ElideRight }
            }
            Text { text: (row.exam.totalScore || 100) + "分"; color: "#2563eb"; font.pixelSize: 14; font.bold: true; Layout.preferredWidth: 58; horizontalAlignment: Text.AlignRight }
            Text { text: (row.exam.duration || 90) + "分钟"; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 70; horizontalAlignment: Text.AlignRight }
            PrimaryButton { Layout.preferredWidth: 86; text: "进入"; onClicked: row.startRequested() }
        }
    }

    component ExamDetailPanel: Card {
        id: detail
        property var exam: ({})
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "考试详情"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            DetailBlock { title: "考试名称"; text: detail.exam.title || detail.exam.name || "--"; accent: true }
            DetailBlock { title: "考试时间"; text: (detail.exam.startTime || "--") + "  至  " + (detail.exam.endTime || "--") }
            DetailBlock { title: "考试说明"; text: "考试开始后可逐题作答，客观题自动评分，主观题等待教师批改。" }
            Item { Layout.fillHeight: true }
            PrimaryButton { Layout.fillWidth: true; text: "开始考试"; onClicked: root.startExam(detail.exam) }
        }
    }

    component AnswerPage: Item {
        ColumnLayout {
            property int pageMargin: root.narrowShell ? 16 : 28
            width: Math.max(280, (parent.width - pageMargin * 2) / root.examScale)
            height: Math.max(360, (parent.height - pageMargin * 2) / root.examScale)
            anchors.centerIn: parent
            scale: root.examScale
            transformOrigin: Item.Center
            spacing: root.narrowShell ? 12 : 18
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4
                    Text { text: "在线考试"; color: "#111827"; font.pixelSize: 28; font.bold: true }
                    Text { text: "自动保存答案，支持题号导航、倒计时与交卷确认"; color: "#8b949e"; font.pixelSize: 13 }
                }
                ExamControlStrip {
                    Layout.preferredWidth: root.narrowShell ? 188 : 224
                    Layout.preferredHeight: 42
                    statusText: "考试中"
                    onExitRequested: root.exitExamMode()
                }
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: width > 760 ? 4 : 1
                columnSpacing: root.narrowShell ? 12 : 18
                rowSpacing: root.narrowShell ? 12 : 18
                Card {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: parent.width > 760 ? 3 : 1
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: root.narrowShell ? 18 : 28
                        spacing: root.narrowShell ? 12 : 18
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 8
                            Text { Layout.fillWidth: true; text: root.examTitle(root.selectedExam()); color: "#111827"; font.pixelSize: 24; font.bold: true; elide: Text.ElideRight }
                            Text {
                                text: root.displayQuestionType(root.currentQuestion().type) + " · 每题 " + (root.currentQuestion().score || 3) + " 分 · 共 " + root.questions.length + " 题 · 已答 " + root.answeredCount() + " 题 · 已标记 " + root.markedCount() + " 题"
                                color: "#64748b"
                                font.pixelSize: 13
                            }
                        }
                        Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                        RowLayout {
                            Layout.fillWidth: true
                            Text {
                                Layout.fillWidth: true
                                text: (root.activeQuestionIndex + 1) + ". " + (root.currentQuestion().content || "暂无题目")
                                color: "#111827"
                                font.pixelSize: 18
                                font.bold: true
                                wrapMode: Text.WordWrap
                            }
                            SoftButton {
                                Layout.preferredWidth: 116
                                text: root.questionMarked(root.currentQuestion().id) ? "★ 已标记" : "☆ 标记"
                                onClicked: root.toggleQuestionMark(root.currentQuestion().id)
                            }
                        }
                        Loader {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            sourceComponent: root.isObjective(root.currentQuestion().type) ? optionAnswerComponent : textAnswerComponent
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            SoftButton {
                                Layout.fillWidth: true
                                text: "上一题"
                                enabled: root.activeQuestionIndex > 0
                                onClicked: root.activeQuestionIndex -= 1
                            }
                            SoftButton {
                                Layout.fillWidth: true
                                text: root.questionMarked(root.currentQuestion().id) ? "取消标记" : "标记本题"
                                onClicked: root.toggleQuestionMark(root.currentQuestion().id)
                            }
                            PrimaryButton {
                                Layout.fillWidth: true
                                text: "下一题"
                                enabled: root.activeQuestionIndex < root.questions.length - 1
                                onClicked: root.activeQuestionIndex += 1
                            }
                        }
                    }
                }

                ColumnLayout {
                    id: rightTools
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: 1
                    spacing: root.narrowShell ? 12 : 14
                    ExamClockCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 150 : 184
                        label: "◷  剩余时间"
                        value: "42 : 12"
                        hint: "43 分钟后结束"
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumHeight: 220
                        radius: 24
                        color: "#ffffff"
                        border.color: "#e5edf6"
                        clip: true
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 14
                            RowLayout {
                                Layout.fillWidth: true
                                Text { text: "答题卡"; color: "#111827"; font.pixelSize: 20; font.bold: true; Layout.fillWidth: true }
                                Text { text: (root.activeQuestionIndex + 1) + "/" + root.questions.length; color: "#8b949e"; font.pixelSize: 15 }
                            }
                            GridLayout {
                                Layout.fillWidth: true
                                columns: 5
                                columnSpacing: 8
                                rowSpacing: 8
                                Repeater {
                                    model: root.questions
                                    delegate: Rectangle {
                                        Layout.preferredWidth: 38
                                        Layout.preferredHeight: 38
                                        radius: 14
                                        property bool current: index === root.activeQuestionIndex
                                        property bool answered: root.answerFor(modelData.id).length > 0
                                        property bool marked: root.questionMarked(modelData.id)
                                        color: current ? "#3b82f6" : (marked ? "#fff7ed" : (answered ? "#eff6ff" : "#f3f4f6"))
                                        border.color: marked ? "#f59e0b" : (current ? "#3b82f6" : "transparent")
                                        Text { anchors.centerIn: parent; text: String(index + 1); color: current ? "#ffffff" : (marked ? "#f59e0b" : "#64748b"); font.pixelSize: 14; font.bold: true }
                                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.activeQuestionIndex = index }
                                    }
                                }
                            }
                            Item { Layout.fillHeight: true }
                            RowLayout {
                                spacing: 12
                                LegendDot { colorValue: "#dbeafe"; label: "已答" }
                                LegendDot { colorValue: "#f3f4f6"; label: "未答" }
                                LegendDot { colorValue: "#f59e0b"; label: "标记" }
                            }
                        }
                    }
                    DangerButton { Layout.fillWidth: true; text: "提交试卷"; onClicked: root.submitActiveExam() }
                }
            }
        }

        Component {
            id: optionAnswerComponent
            ColumnLayout {
                spacing: 12
                Repeater {
                    model: ["A", "B", "C", "D"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 68
                        radius: 16
                        color: root.optionSelected(root.currentQuestion(), modelData) ? "#eff6ff" : "#f8fafc"
                        border.color: root.optionSelected(root.currentQuestion(), modelData) ? "#3b82f6" : "#e5e7eb"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 14
                            Rectangle {
                                Layout.preferredWidth: 34
                                Layout.preferredHeight: 34
                                radius: 17
                                color: root.optionSelected(root.currentQuestion(), modelData) ? "#3b82f6" : "#ffffff"
                                border.color: "#eef2f7"
                                Text { anchors.centerIn: parent; text: modelData; color: root.optionSelected(root.currentQuestion(), modelData) ? "#ffffff" : "#64748b"; font.pixelSize: 14; font.bold: true }
                            }
                            Text { Layout.fillWidth: true; text: root.optionText(root.currentQuestion(), modelData); color: "#111827"; font.pixelSize: 15; font.bold: true; wrapMode: Text.WordWrap; maximumLineCount: 3; elide: Text.ElideRight }
                        }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.toggleObjectiveAnswer(root.currentQuestion(), modelData) }
                    }
                }
            }
        }

        Component {
            id: textAnswerComponent
            TextArea {
                text: root.answerFor(root.currentQuestion().id)
                placeholderText: "在这里输入答案"
                wrapMode: TextArea.Wrap
                color: "#111827"
                font.pixelSize: 16
                onTextChanged: root.setAnswer(root.currentQuestion().id, text)
                background: Rectangle { radius: 18; color: "#ffffff"; border.color: "#e5edf6" }
            }
        }
    }

    component PracticePage: PageShell {
        Component.onCompleted: {
            if (root.practiceQuestions.length === 0) root.loadPracticeQuestions("", "", "")
        }
        RowLayout {
            width: parent.width
            spacing: 14
            SectionTitle {
                Layout.fillWidth: true
                title: root.practiceMode === 1 ? "错题本" : (root.practiceMode === 2 ? "随机组卷" : (root.practiceMode === 3 ? root.activePracticeSubject + "题库刷题" : "题库练习"))
                subtitle: root.practiceMode === 1 ? "订正练习和考试中的错题，补充错误原因与知识点总结" : (root.practiceMode === 2 ? "按科目、题型、难度和数量随机抽题，开启限时模拟" : (root.practiceMode === 3 ? "左侧选择题目，右侧完成作答并查看解析" : "选择科目题库、错题本或随机组卷开始练习"))
            }
            SoftButton {
                Layout.preferredWidth: 92
                visible: root.practiceMode === 2
                text: "返回"
                onClicked: {
                    root.practiceMode = 0
                    root.triggerPageEnter(-1)
                }
            }
        }

        GridLayout {
            width: parent.width
            height: root.practiceMode === 0 ? (parent.width > 760 ? 138 : 282) : 0
            visible: root.practiceMode === 0
            columns: parent.width > 760 ? 2 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            PracticeQuickCard { Layout.fillWidth: true; title: "错题本"; hint: "订正错题、记录原因与知识点"; accent: "#f59e0b"; icon: "错"; onClicked: root.openPracticeWrongBook() }
            PracticeQuickCard { Layout.fillWidth: true; title: "随机组卷"; hint: "选择题型科目难度，限时模拟"; accent: "#2563eb"; icon: "卷"; onClicked: root.openRandomPaperConfig() }
        }

        PracticeSubjectGrid { width: parent.width; height: root.practiceMode === 0 ? (width > 1120 ? 602 : (width > 760 ? 912 : 1842)) : 0; visible: root.practiceMode === 0 }
        WrongQuestionPage { width: parent.width; height: root.practiceMode === 1 ? (root.narrowShell ? 1180 : 760) : 0; visible: root.practiceMode === 1 }
        RandomPaperConfigPage { width: parent.width; height: root.practiceMode === 2 ? (root.narrowShell ? 840 : 620) : 0; visible: root.practiceMode === 2 }
        PracticeBankPanel { width: parent.width; height: root.practiceMode === 3 ? (root.narrowShell ? 1180 : 760) : 0; visible: root.practiceMode === 3 }
    }

    component PracticeSubjectGrid: GridLayout {
        columns: width > 1120 ? 3 : (width > 760 ? 2 : 1)
        columnSpacing: root.narrowShell ? 12 : 18
        rowSpacing: root.narrowShell ? 12 : 18
        Repeater {
            model: root.subjectCards
            delegate: SubjectPracticeCard {
                Layout.fillWidth: true
                Layout.preferredHeight: 292
                subject: modelData
            }
        }
    }

    component PracticeBankPanel: Card {
        GridLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 24
            columns: root.narrowShell ? 1 : 2
            columnSpacing: root.narrowShell ? 14 : 28
            rowSpacing: root.narrowShell ? 14 : 28

            Rectangle {
                Layout.fillWidth: root.narrowShell
                Layout.preferredWidth: root.narrowShell ? Math.max(260, parent.width) : 420
                Layout.preferredHeight: root.narrowShell ? 420 : parent.height
                Layout.fillHeight: true
                radius: 24
                color: "#ffffff"
                border.color: "#e2edf8"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 22
                    spacing: 14
                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: root.activePracticeSubject + "题目"; color: "#0f172a"; font.pixelSize: 24; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                        SoftButton {
                            Layout.preferredWidth: 74
                            text: "返回"
                            onClicked: {
                                root.practiceMode = 0
                                root.triggerPageEnter(-1)
                            }
                        }
                    }
                    Text { text: "共 " + root.practiceQuestions.length + " 题"; color: "#64748b"; font.pixelSize: 15 }
                    Flickable {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        contentWidth: width
                        contentHeight: practiceListColumn.height
                        clip: true
                        interactive: contentHeight > height
                        boundsBehavior: Flickable.StopAtBounds
                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
                        HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                        Column {
                            id: practiceListColumn
                            width: parent.width
                            spacing: 12
                            Repeater {
                                model: root.practiceQuestions
                                delegate: PracticeListRow {
                                    width: practiceListColumn.width
                                    question: modelData
                                    rowIndex: index
                                }
                            }
                        }
                    }
                }
            }

            PracticeQuestionDetail {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    component PracticeListRow: Rectangle {
        id: row
        property var question: ({})
        property int rowIndex: 0
        height: 82
        radius: 18
        color: root.activePracticeIndex === rowIndex ? "#2563eb" : "#f8fbff"
        border.color: root.activePracticeIndex === rowIndex ? "#2563eb" : "#e2edf8"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 18
            anchors.rightMargin: 16
            spacing: 16
            Text {
                text: String(rowIndex + 1)
                color: root.activePracticeIndex === rowIndex ? "#ffffff" : "#0f172a"
                font.pixelSize: 20
                font.bold: true
                Layout.preferredWidth: 32
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 3
                Text {
                    Layout.fillWidth: true
                    text: root.displayQuestionType(row.question.type)
                    color: root.activePracticeIndex === rowIndex ? "#ffffff" : "#2563eb"
                    font.pixelSize: 15
                    font.bold: true
                    elide: Text.ElideRight
                }
                Text {
                    Layout.fillWidth: true
                    text: row.question.subject || row.question.knowledge || "综合练习"
                    color: root.activePracticeIndex === rowIndex ? "#dbeafe" : "#64748b"
                    font.pixelSize: 13
                    elide: Text.ElideRight
                }
            }
            Rectangle {
                Layout.preferredWidth: 66
                Layout.preferredHeight: 30
                radius: 15
                color: root.activePracticeIndex === rowIndex ? "#3b82f6" : "#eef6ff"
                Text {
                    anchors.centerIn: parent
                    text: root.displayDifficulty(row.question.difficulty || row.question.level)
                    color: root.activePracticeIndex === rowIndex ? "#ffffff" : "#2563eb"
                    font.pixelSize: 12
                    font.bold: true
                }
            }
        }
        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.activePracticeIndex = rowIndex }
    }

    component PracticeQuestionDetail: Rectangle {
        id: detail
        property var question: root.currentPracticeQuestion()
        radius: 24
        color: "#ffffff"
        border.color: "#e2edf8"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 18
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "第 " + (root.activePracticeIndex + 1) + " 题"
                    color: "#2563eb"
                    font.pixelSize: 18
                    font.bold: true
                    Layout.fillWidth: true
                }
                Rectangle {
                    Layout.preferredWidth: 82
                    Layout.preferredHeight: 36
                    radius: 18
                    color: "#eff6ff"
                    Text { anchors.centerIn: parent; text: root.displayQuestionType(detail.question.type); color: "#2563eb"; font.pixelSize: 13; font.bold: true }
                }
                Rectangle {
                    Layout.preferredWidth: 78
                    Layout.preferredHeight: 36
                    radius: 18
                    color: root.displayDifficulty(detail.question.difficulty || detail.question.level) === "困难" ? "#fff7ed" : "#f0fdf4"
                    Text {
                        anchors.centerIn: parent
                        text: root.displayDifficulty(detail.question.difficulty || detail.question.level)
                        color: root.displayDifficulty(detail.question.difficulty || detail.question.level) === "困难" ? "#f97316" : "#16a34a"
                        font.pixelSize: 13
                        font.bold: true
                    }
                }
            }
            Text {
                Layout.fillWidth: true
                text: detail.question.content || "暂无题目"
                color: "#0f172a"
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.WordWrap
                lineHeight: 1.18
            }
            Loader {
                Layout.fillWidth: true
                Layout.preferredHeight: root.isObjective(detail.question.type) ? 230 : 210
                sourceComponent: root.isObjective(detail.question.type) ? practiceOptionComponent : practiceTextComponent
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: root.practiceIsChecked(detail.question.id) ? 112 : 0
                visible: root.practiceIsChecked(detail.question.id)
                radius: 18
                color: root.practiceIsCorrect(detail.question) ? "#f0fdf4" : "#fff7ed"
                border.color: root.practiceIsCorrect(detail.question) ? "#bbf7d0" : "#fed7aa"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 6
                    Text {
                        text: "正确答案：" + (detail.question.answer || "暂无")
                        color: root.practiceIsCorrect(detail.question) ? "#16a34a" : "#f97316"
                        font.pixelSize: 15
                        font.bold: true
                    }
                    Text {
                        Layout.fillWidth: true
                        text: detail.question.analysis || "暂无解析"
                        color: "#475569"
                        font.pixelSize: 13
                        wrapMode: Text.WordWrap
                        maximumLineCount: 3
                        elide: Text.ElideRight
                    }
                }
            }
            Item { Layout.fillHeight: true }
            RowLayout {
                Layout.fillWidth: true
                spacing: 12
                SoftButton {
                    Layout.fillWidth: true
                    text: "上一题"
                    enabled: root.activePracticeIndex > 0
                    onClicked: root.activePracticeIndex -= 1
                }
                PrimaryButton {
                    Layout.fillWidth: true
                    text: root.practiceIsChecked(detail.question.id) ? "已查看解析" : "提交查看解析"
                    onClicked: root.checkPracticeQuestion()
                }
                SoftButton {
                    Layout.fillWidth: true
                    text: "下一题"
                    enabled: root.activePracticeIndex < root.practiceQuestions.length - 1
                    onClicked: root.activePracticeIndex += 1
                }
            }
        }

        Component {
            id: practiceOptionComponent
            GridLayout {
                columns: width > 720 ? 2 : 1
                columnSpacing: 14
                rowSpacing: 14
                Repeater {
                    model: ["A", "B", "C", "D"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 96
                        radius: 18
                        property bool selected: root.practiceOptionSelected(root.currentPracticeQuestion(), modelData)
                        color: selected ? "#eff6ff" : "#f8fbff"
                        border.color: selected ? "#2563eb" : "#e2edf8"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 16
                            spacing: 14
                            Rectangle {
                                Layout.preferredWidth: 38
                                Layout.preferredHeight: 38
                                radius: 19
                                color: selected ? "#2563eb" : "#ffffff"
                                border.color: selected ? "#2563eb" : "#e2edf8"
                                Text { anchors.centerIn: parent; text: modelData; color: selected ? "#ffffff" : "#64748b"; font.pixelSize: 15; font.bold: true }
                            }
                            Text {
                                Layout.fillWidth: true
                                text: root.optionText(root.currentPracticeQuestion(), modelData)
                                color: "#0f172a"
                                font.pixelSize: 16
                                font.bold: true
                                wrapMode: Text.WordWrap
                                maximumLineCount: 3
                                elide: Text.ElideRight
                            }
                        }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.togglePracticeObjectiveAnswer(root.currentPracticeQuestion(), modelData) }
                    }
                }
            }
        }

        Component {
            id: practiceTextComponent
            TextArea {
                text: root.practiceAnswerFor(root.currentPracticeQuestion().id)
                placeholderText: "在这里输入你的答案"
                placeholderTextColor: "#94a3b8"
                wrapMode: TextArea.Wrap
                color: "#0f172a"
                font.pixelSize: 16
                onTextChanged: root.setPracticeAnswer(root.currentPracticeQuestion().id, text)
                background: Rectangle { radius: 18; color: "#f8fbff"; border.color: "#dbe7f6" }
            }
        }
    }

    component WrongQuestionPage: Card {
        GridLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 24
            columns: root.narrowShell ? 1 : 2
            columnSpacing: root.narrowShell ? 14 : 24
            rowSpacing: root.narrowShell ? 14 : 24

            Rectangle {
                Layout.fillWidth: root.narrowShell
                Layout.preferredWidth: root.narrowShell ? Math.max(260, parent.width) : 390
                Layout.preferredHeight: root.narrowShell ? 360 : parent.height
                Layout.fillHeight: true
                radius: 24
                color: "#ffffff"
                border.color: "#e2edf8"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 22
                    spacing: 14
                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "错题列表"; color: "#0f172a"; font.pixelSize: 24; font.bold: true; Layout.fillWidth: true }
                        SoftButton { Layout.preferredWidth: 74; text: "返回"; onClicked: root.practiceMode = 0 }
                    }
                    Text { text: "已批改考试错题共 " + root.wrongQuestionRows.length + " 题"; color: "#64748b"; font.pixelSize: 14 }
                    Flickable {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        contentWidth: width
                        contentHeight: wrongListColumn.height
                        clip: true
                        interactive: contentHeight > height
                        boundsBehavior: Flickable.StopAtBounds
                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
                        HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                        Column {
                            id: wrongListColumn
                            width: parent.width
                            spacing: 12
                            Text {
                                width: parent.width
                                height: root.wrongQuestionRows.length === 0 ? 180 : 0
                                visible: root.wrongQuestionRows.length === 0
                                text: "暂无错题记录"
                                color: "#94a3b8"
                                font.pixelSize: 16
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            Repeater {
                                model: root.wrongQuestionRows
                                delegate: WrongQuestionListRow {
                                    width: wrongListColumn.width
                                    row: modelData
                                    rowIndex: index
                                }
                            }
                        }
                    }
                }
            }

            WrongQuestionDetail {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    component WrongQuestionListRow: Rectangle {
        id: rowItem
        property var row: ({})
        property int rowIndex: 0
        height: 100
        radius: 18
        color: root.activeWrongQuestionIndex === rowIndex ? "#2563eb" : "#f8fbff"
        border.color: root.activeWrongQuestionIndex === rowIndex ? "#2563eb" : "#e2edf8"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 14
            Text {
                text: String(rowIndex + 1)
                color: root.activeWrongQuestionIndex === rowIndex ? "#ffffff" : "#0f172a"
                font.pixelSize: 22
                font.bold: true
                Layout.preferredWidth: 28
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        text: root.displayQuestionType(rowItem.row.type)
                        color: root.activeWrongQuestionIndex === rowIndex ? "#ffffff" : "#2563eb"
                        font.pixelSize: 15
                        font.bold: true
                    }
                    Text {
                        text: rowItem.row.source || "错题"
                        color: root.activeWrongQuestionIndex === rowIndex ? "#dbeafe" : "#94a3b8"
                        font.pixelSize: 12
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }
                }
                Text {
                    Layout.fillWidth: true
                    text: rowItem.row.subject || "综合"
                    color: root.activeWrongQuestionIndex === rowIndex ? "#dbeafe" : "#64748b"
                    font.pixelSize: 13
                    elide: Text.ElideRight
                }
                Text {
                    Layout.fillWidth: true
                    text: "错选 " + (rowItem.row.wrongAnswer || "--") + " · 正确 " + (rowItem.row.answer || "--")
                    color: root.activeWrongQuestionIndex === rowIndex ? "#ffffff" : "#f97316"
                    font.pixelSize: 12
                    font.bold: true
                    elide: Text.ElideRight
                }
            }
        }
        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.activeWrongQuestionIndex = rowIndex }
    }

    component WrongQuestionDetail: Rectangle {
        id: wrongDetail
        property var question: root.currentWrongQuestion()
        property string redoAnswer: ""
        property int currentAnswerId: Number(question.answerId || 0)
        function loadCorrectionFields() {
            redoAnswer = question.correctionAnswer || ""
            correctionReasonInput.text = question.correctionReason || ""
            correctionKnowledgeInput.text = question.correctionSummary || ""
        }
        onCurrentAnswerIdChanged: Qt.callLater(loadCorrectionFields)
        Component.onCompleted: loadCorrectionFields()
        radius: 24
        color: "#ffffff"
        border.color: "#e2edf8"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 16
            RowLayout {
                Layout.fillWidth: true
                Text { text: "第 " + (root.activeWrongQuestionIndex + 1) + " 题订正"; color: "#2563eb"; font.pixelSize: 20; font.bold: true; Layout.fillWidth: true }
                Rectangle {
                    Layout.preferredWidth: 86
                    Layout.preferredHeight: 34
                    radius: 17
                    color: "#eff6ff"
                    Text { anchors.centerIn: parent; text: root.displayQuestionType(wrongDetail.question.type); color: "#2563eb"; font.pixelSize: 13; font.bold: true }
                }
                Rectangle {
                    Layout.preferredWidth: 76
                    Layout.preferredHeight: 34
                    radius: 17
                    color: "#fff7ed"
                    Text { anchors.centerIn: parent; text: root.displayDifficulty(wrongDetail.question.difficulty); color: "#f97316"; font.pixelSize: 13; font.bold: true }
                }
            }
            Text {
                Layout.fillWidth: true
                text: wrongDetail.question.content || "暂无题目"
                color: "#0f172a"
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.WordWrap
            }
            GridLayout {
                Layout.fillWidth: true
                columns: width > 760 ? 2 : 1
                columnSpacing: 14
                rowSpacing: 14
                Repeater {
                    model: ["A", "B", "C", "D"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 74
                        radius: 18
                        property bool selected: wrongDetail.redoAnswer.indexOf(modelData) >= 0
                        property bool wasWrong: String(wrongDetail.question.wrongAnswer || "").indexOf(modelData) >= 0
                        property bool correct: String(wrongDetail.question.answer || "").indexOf(modelData) >= 0
                        color: selected ? "#eff6ff" : (wasWrong ? "#fff7ed" : (correct ? "#f0fdf4" : "#f8fbff"))
                        border.color: selected ? "#2563eb" : (wasWrong ? "#fed7aa" : (correct ? "#bbf7d0" : "#e2edf8"))
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 12
                            Rectangle {
                                Layout.preferredWidth: 36
                                Layout.preferredHeight: 36
                                radius: 18
                                color: selected ? "#2563eb" : "#ffffff"
                                border.color: selected ? "#2563eb" : "#e2edf8"
                                Text { anchors.centerIn: parent; text: modelData; color: selected ? "#ffffff" : "#64748b"; font.pixelSize: 15; font.bold: true }
                            }
                            Text {
                                Layout.fillWidth: true
                                text: root.optionText(wrongDetail.question, modelData)
                                color: "#0f172a"
                                font.pixelSize: 15
                                font.bold: true
                                wrapMode: Text.WordWrap
                                maximumLineCount: 2
                                elide: Text.ElideRight
                            }
                            Text {
                                text: wasWrong ? "当时错选" : (correct ? "正确答案" : "")
                                color: wasWrong ? "#f97316" : "#16a34a"
                                font.pixelSize: 12
                                font.bold: true
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: wrongDetail.redoAnswer = root.isMultipleChoice(wrongDetail.question.type) ? (wrongDetail.redoAnswer.indexOf(modelData) >= 0 ? wrongDetail.redoAnswer.replace(modelData, "") : wrongDetail.redoAnswer + modelData) : modelData
                        }
                    }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 82
                radius: 18
                color: "#f8fbff"
                border.color: "#e2edf8"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 4
                    Text { text: "解析：" + (wrongDetail.question.analysis || "暂无解析"); color: "#475569"; font.pixelSize: 13; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                    Text { text: "知识点：" + (wrongDetail.question.knowledge || "待总结"); color: "#2563eb"; font.pixelSize: 13; font.bold: true }
                }
            }
            GridLayout {
                Layout.fillWidth: true
                columns: root.narrowShell ? 1 : 2
                columnSpacing: 14
                rowSpacing: 14
                TextArea {
                    id: correctionReasonInput
                    Layout.fillWidth: true
                    Layout.preferredHeight: 112
                    placeholderText: "写下当时的错误原因"
                    placeholderTextColor: "#94a3b8"
                    wrapMode: TextArea.Wrap
                    background: Rectangle { radius: 18; color: "#f8fbff"; border.color: "#dbe7f6" }
                }
                TextArea {
                    id: correctionKnowledgeInput
                    Layout.fillWidth: true
                    Layout.preferredHeight: 112
                    placeholderText: "整理本题知识点总结"
                    placeholderTextColor: "#94a3b8"
                    wrapMode: TextArea.Wrap
                    background: Rectangle { radius: 18; color: "#f8fbff"; border.color: "#dbe7f6" }
                }
            }
            Item { Layout.fillHeight: true }
            RowLayout {
                Layout.fillWidth: true
                SoftButton { Layout.fillWidth: true; text: "上一题"; enabled: root.activeWrongQuestionIndex > 0; onClicked: root.activeWrongQuestionIndex -= 1 }
                PrimaryButton {
                    Layout.fillWidth: true
                    text: "保存订正"
                    onClicked: {
                        var saved = studentApi.saveWrongQuestionCorrection(
                            Number(wrongDetail.question.answerId || 0),
                            wrongDetail.question.sourceType || "exam",
                            wrongDetail.redoAnswer,
                            correctionReasonInput.text,
                            correctionKnowledgeInput.text
                        )
                        if (saved) {
                            var keepIndex = root.activeWrongQuestionIndex
                            root.wrongQuestionRows = studentApi.getWrongQuestions()
                            root.activeWrongQuestionIndex = Math.min(keepIndex, Math.max(root.wrongQuestionRows.length - 1, 0))
                            root.aiSuggestions = root.aiSuggestionRows()
                            root.showToast("订正记录已保存")
                        } else {
                            root.showToast(studentApi.lastError() || "订正保存失败")
                        }
                    }
                }
                SoftButton { Layout.fillWidth: true; text: "下一题"; enabled: root.activeWrongQuestionIndex < root.wrongQuestionRows.length - 1; onClicked: root.activeWrongQuestionIndex += 1 }
            }
        }
    }

    component RandomPaperConfigPage: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 28
            spacing: root.narrowShell ? 14 : 20
            GridLayout {
                Layout.fillWidth: true
                columns: root.narrowShell ? 1 : 2
                rowSpacing: 6
                columnSpacing: 16
                Text {
                    Layout.fillWidth: true
                    text: "随机组卷设置"
                    color: "#0f172a"
                    font.pixelSize: 26
                    font.bold: true
                    elide: Text.ElideRight
                }
                Text {
                    Layout.fillWidth: root.narrowShell
                    Layout.preferredWidth: root.narrowShell ? parent.width : 360
                    text: "选择范围后随机抽题，可作为限时模拟考试完成"
                    color: "#64748b"
                    font.pixelSize: 14
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignRight
                }
            }
            GridLayout {
                Layout.fillWidth: true
                columns: parent.width > 980 ? 4 : (parent.width > 560 ? 2 : 1)
                columnSpacing: root.narrowShell ? 12 : 18
                rowSpacing: root.narrowShell ? 12 : 18
                RandomConfigBlock {
                    Layout.fillWidth: true
                    title: "科目"
                    FilterCombo { id: randomSubjectCombo; anchors.fill: parent; model: ["全部科目", "高等数学", "Java基础", "数据库基础", "计算机网络", "数据结构"] }
                }
                RandomConfigBlock {
                    Layout.fillWidth: true
                    title: "题型"
                    FilterCombo { id: randomTypeCombo; anchors.fill: parent; model: ["全部题型", "单选题", "多选题", "填空题", "编程题"] }
                }
                RandomConfigBlock {
                    Layout.fillWidth: true
                    title: "难度"
                    FilterCombo { id: randomDifficultyCombo; anchors.fill: parent; model: ["全部难度", "基础", "中等", "困难"] }
                }
                RandomConfigBlock {
                    Layout.fillWidth: true
                    title: "题目数量"
                    NumberStepper { id: randomCountBox; anchors.fill: parent; from: 5; to: 50; value: 10; stepSize: 5; suffix: "题" }
                }
                RandomConfigBlock {
                    Layout.fillWidth: true
                    title: "限时时长（分钟）"
                    NumberStepper { id: randomTimeBox; anchors.fill: parent; from: 10; to: 180; value: 30; stepSize: 5; suffix: "分钟" }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: root.narrowShell ? 260 : 180
                radius: 24
                color: "#f8fbff"
                border.color: "#e2edf8"
                GridLayout {
                    anchors.fill: parent
                    anchors.margins: root.narrowShell ? 18 : 24
                    columns: root.narrowShell ? 1 : 3
                    columnSpacing: 18
                    rowSpacing: 14
                    Rectangle {
                        Layout.preferredWidth: 76
                        Layout.preferredHeight: 76
                        radius: 24
                        color: "#eff6ff"
                        Text { anchors.centerIn: parent; text: "卷"; color: "#2563eb"; font.pixelSize: 28; font.bold: true }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 8
                        Text { text: "限时模拟考试"; color: "#0f172a"; font.pixelSize: 22; font.bold: true }
                        Text { Layout.fillWidth: true; text: "系统将按当前条件随机抽题，进入后按模拟考试流程作答，提交后查看客观题得分与解析。"; color: "#64748b"; font.pixelSize: 14; wrapMode: Text.WordWrap }
                    }
                    PrimaryButton {
                        Layout.fillWidth: root.narrowShell
                        Layout.preferredWidth: root.narrowShell ? parent.width : 160
                        text: "开始组卷"
                        onClicked: {
                            randomCountBox.commitInput()
                            randomTimeBox.commitInput()
                            root.practiceTimeLimit = randomTimeBox.value
                            root.loadPracticeQuestions(randomTypeCombo.currentText === "全部题型" ? "" : randomTypeCombo.currentText,
                                                       randomDifficultyCombo.currentText === "全部难度" ? "" : randomDifficultyCombo.currentText,
                                                       randomSubjectCombo.currentText === "全部科目" ? "" : randomSubjectCombo.currentText)
                            root.startPracticeMockExam(randomCountBox.value)
                        }
                    }
                }
            }
        }
    }

    component RandomConfigBlock: ColumnLayout {
        id: block
        property string title: ""
        spacing: 8
        default property alias content: slot.data
        Text { text: block.title; color: "#64748b"; font.pixelSize: 14; font.bold: true }
        Item {
            id: slot
            Layout.fillWidth: true
            Layout.preferredHeight: 52
        }
    }

    component NumberStepper: Rectangle {
        id: stepper
        property int from: 0
        property int to: 100
        property int value: 0
        property int stepSize: 1
        property string suffix: ""
        radius: 18
        color: "#ffffff"
        border.color: "#dbe7f6"
        function clamp(nextValue) {
            return Math.max(stepper.from, Math.min(stepper.to, nextValue))
        }
        function commitInput() {
            var next = parseInt(valueInput.text)
            if (isNaN(next)) next = stepper.value
            stepper.value = stepper.clamp(next)
            valueInput.text = String(stepper.value)
        }
        RowLayout {
            anchors.fill: parent
            anchors.margins: 6
            spacing: 8
            StepperButton {
                Layout.preferredWidth: 40
                Layout.fillHeight: true
                text: "−"
                enabled: stepper.value > stepper.from
                onClicked: stepper.value = stepper.clamp(stepper.value - stepper.stepSize)
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 14
                color: valueInput.activeFocus ? "#ffffff" : "#f8fbff"
                border.width: valueInput.activeFocus ? 2 : 1
                border.color: valueInput.activeFocus ? "#2563eb" : "#dbe7f6"
                Row {
                    anchors.centerIn: parent
                    spacing: 6
                    TextInput {
                        id: valueInput
                        width: Math.max(54, implicitWidth + 18)
                        height: 38
                        text: String(stepper.value)
                        color: "#0f172a"
                        font.pixelSize: 17
                        font.bold: true
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        selectByMouse: true
                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator { bottom: stepper.from; top: stepper.to }
                        onEditingFinished: stepper.commitInput()
                        Keys.onReturnPressed: {
                            stepper.commitInput()
                            focus = false
                        }
                        Keys.onEnterPressed: {
                            stepper.commitInput()
                            focus = false
                        }
                    }
                    Text {
                        text: stepper.suffix
                        visible: stepper.suffix.length > 0
                        color: "#0f172a"
                        font.pixelSize: 16
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                TapHandler {
                    onTapped: {
                        valueInput.forceActiveFocus()
                        valueInput.selectAll()
                    }
                }
            }
            StepperButton {
                Layout.preferredWidth: 40
                Layout.fillHeight: true
                text: "+"
                enabled: stepper.value < stepper.to
                onClicked: stepper.value = stepper.clamp(stepper.value + stepper.stepSize)
            }
        }
        onValueChanged: if (!valueInput.activeFocus) valueInput.text = String(stepper.value)
    }

    component StepperButton: Rectangle {
        id: stepButton
        property string text: ""
        signal clicked()
        radius: 14
        color: enabled ? (buttonMouse.containsMouse ? "#dbeafe" : "#eff6ff") : "#f1f5f9"
        border.color: enabled ? "#bfdbfe" : "#e5e7eb"
        opacity: enabled ? 1 : 0.58
        Text {
            anchors.centerIn: parent
            text: stepButton.text
            color: "#2563eb"
            font.pixelSize: 20
            font.bold: true
        }
        MouseArea {
            id: buttonMouse
            anchors.fill: parent
            hoverEnabled: true
            enabled: stepButton.enabled
            cursorShape: Qt.PointingHandCursor
            onClicked: stepButton.clicked()
        }
    }

    component PracticeQuickCard: Card {
        id: quick
        property string title: ""
        property string hint: ""
        property string icon: ""
        property color accent: "#22c55e"
        signal clicked()
        height: root.narrowShell ? 126 : 132
        RowLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 22
            spacing: root.narrowShell ? 12 : 16
            Rectangle {
                Layout.preferredWidth: root.narrowShell ? 48 : 56
                Layout.preferredHeight: root.narrowShell ? 48 : 56
                radius: 18
                color: Qt.rgba(quick.accent.r, quick.accent.g, quick.accent.b, 0.12)
                Text { anchors.centerIn: parent; text: quick.icon; color: quick.accent; font.pixelSize: 22; font.bold: true }
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 6
                Text { text: quick.title; color: "#111827"; font.pixelSize: 22; font.bold: true }
                Text { Layout.fillWidth: true; text: quick.hint; color: "#64748b"; font.pixelSize: 13; wrapMode: Text.WordWrap }
            }
            Text { text: "›"; color: quick.accent; font.pixelSize: 30; font.bold: true }
        }
        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: quick.clicked() }
    }

    component SubjectPracticeCard: Card {
        id: subjectCard
        property var subject: ({})
        property color accent: subject.color || "#22c55e"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 22
            spacing: 12
            RowLayout {
                Layout.fillWidth: true
                Rectangle {
                    Layout.preferredWidth: 54
                    Layout.preferredHeight: 54
                    radius: 18
                    color: subjectCard.accent
                    Text { anchors.centerIn: parent; text: subjectCard.subject.icon || "题"; color: "#ffffff"; font.pixelSize: 21; font.bold: true }
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 3
                    Text { text: subjectCard.subject.name || "--"; color: "#111827"; font.pixelSize: 20; font.bold: true }
                    Text { text: "准确率 " + (subjectCard.subject.accuracy || 0) + "%"; color: "#64748b"; font.pixelSize: 13 }
                }
                Text { text: (subjectCard.subject.progress || 0) + "%"; color: subjectCard.accent; font.pixelSize: 20; font.bold: true }
            }
            ProgressBarLine { Layout.fillWidth: true; value: (subjectCard.subject.progress || 0) / 100; accent: subjectCard.accent }
            RowLayout {
                Layout.fillWidth: true
                DifficultyPill { Layout.fillWidth: true; label: "基础"; value: subjectCard.subject.easy || 0; accent: "#22c55e" }
                DifficultyPill { Layout.fillWidth: true; label: "中等"; value: subjectCard.subject.middle || 0; accent: "#f59e0b" }
                DifficultyPill { Layout.fillWidth: true; label: "困难"; value: subjectCard.subject.hard || 0; accent: "#ef4444" }
            }
            Item { Layout.fillHeight: true }
            PrimaryButton {
                Layout.fillWidth: true
                text: "开始练习"
                onClicked: root.startSubjectPractice(subjectCard.subject.name || "")
            }
        }
    }

    component ProgressBarLine: Rectangle {
        id: bar
        property real value: 0
        property color accent: "#22c55e"
        Layout.preferredHeight: 10
        radius: 5
        color: "#eef2f7"
        Rectangle {
            width: parent.width * Math.max(0, Math.min(1, bar.value))
            height: parent.height
            radius: parent.radius
            color: bar.accent
            Behavior on width { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
        }
    }

    component DifficultyPill: Rectangle {
        id: pill
        property string label: ""
        property int value: 0
        property color accent: "#22c55e"
        Layout.preferredHeight: 44
        radius: 14
        color: Qt.rgba(pill.accent.r, pill.accent.g, pill.accent.b, 0.10)
        Column {
            anchors.centerIn: parent
            spacing: 1
            Text { text: pill.value + "%"; color: pill.accent; font.pixelSize: 13; font.bold: true; horizontalAlignment: Text.AlignHCenter }
            Text { text: pill.label; color: "#64748b"; font.pixelSize: 10; horizontalAlignment: Text.AlignHCenter }
        }
    }

    component PracticeMockExamPage: Item {
        id: mockPage
        Rectangle {
            anchors.fill: parent
            color: "#0f172a"
            opacity: 0.58
        }

        Rectangle {
            id: mockDialog
            property var question: root.currentPracticeExamQuestion()
            width: Math.min(660, parent.width - 64)
            height: Math.min(560, parent.height - 56)
            anchors.centerIn: parent
            radius: 28
            color: "#ffffff"
            clip: true

            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 96
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#60a5fa" }
                        GradientStop { position: 1.0; color: "#2563eb" }
                    }
                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 28
                        anchors.rightMargin: 24
                        spacing: 16
                        Rectangle {
                            Layout.preferredWidth: 48
                            Layout.preferredHeight: 48
                            radius: 16
                            color: "#ffffff"
                            opacity: 0.18
                            Text { anchors.centerIn: parent; text: root.displayQuestionType(mockDialog.question.type).charAt(0); color: "#ffffff"; font.pixelSize: 20; font.bold: true }
                        }
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 2
                            Text { Layout.fillWidth: true; text: mockDialog.question.subject || "随机组卷"; color: "#ffffff"; font.pixelSize: 20; font.bold: true; elide: Text.ElideRight }
                            Text { text: "题目 " + (root.activePracticeExamIndex + 1) + " / " + root.practiceExamQuestions.length; color: "#dbeafe"; font.pixelSize: 13; font.bold: true }
                        }
                        Text {
                            text: "×"
                            color: "#dbeafe"
                            font.pixelSize: 24
                            font.bold: true
                            MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.exitPracticeExamMode() }
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 32
                    spacing: 16
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Rectangle {
                            Layout.preferredWidth: 72
                            Layout.preferredHeight: 30
                            radius: 15
                            color: "#eff6ff"
                            Text { anchors.centerIn: parent; text: root.displayQuestionType(mockDialog.question.type); color: "#2563eb"; font.pixelSize: 12; font.bold: true }
                        }
                        Rectangle {
                            Layout.preferredWidth: 62
                            Layout.preferredHeight: 30
                            radius: 15
                            color: "#fff7ed"
                            Text { anchors.centerIn: parent; text: root.displayDifficulty(mockDialog.question.difficulty || mockDialog.question.level); color: "#f97316"; font.pixelSize: 12; font.bold: true }
                        }
                        Item { Layout.fillWidth: true }
                        Text { text: root.practiceExamAnsweredCount() + " / " + root.practiceExamQuestions.length + " 已作答"; color: "#64748b"; font.pixelSize: 13; font.bold: true }
                    }
                    Text {
                        Layout.fillWidth: true
                        text: mockDialog.question.content || "暂无题目"
                        color: "#111827"
                        font.pixelSize: 19
                        font.bold: true
                        wrapMode: Text.WordWrap
                        lineHeight: 1.2
                    }
                    Loader {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.isObjective(mockDialog.question.type) ? 156 : 74
                        sourceComponent: root.isObjective(mockDialog.question.type) ? mockOptionAnswerComponent : mockTextAnswerComponent
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.practiceExamFinished ? 82 : 0
                        visible: root.practiceExamFinished
                        radius: 18
                        color: root.practiceExamIsCorrect(mockDialog.question) ? "#f0fdf4" : "#fff7ed"
                        border.color: root.practiceExamIsCorrect(mockDialog.question) ? "#bbf7d0" : "#fed7aa"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 4
                            Text {
                                text: "正确答案：" + (mockDialog.question.answer || "暂无")
                                color: root.practiceExamIsCorrect(mockDialog.question) ? "#16a34a" : "#f97316"
                                font.pixelSize: 14
                                font.bold: true
                            }
                            Text {
                                Layout.fillWidth: true
                                text: mockDialog.question.analysis || "暂无解析"
                                color: "#475569"
                                font.pixelSize: 13
                                wrapMode: Text.WordWrap
                                maximumLineCount: 2
                                elide: Text.ElideRight
                            }
                        }
                    }
                    Item { Layout.fillHeight: true }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12
                        PrimaryButton {
                            Layout.fillWidth: true
                            text: root.activePracticeExamIndex >= root.practiceExamQuestions.length - 1 ? (root.practiceExamFinished ? "再抽一套" : "提交模拟卷") : "下一题"
                            onClicked: {
                                if (root.activePracticeExamIndex < root.practiceExamQuestions.length - 1) {
                                    root.activePracticeExamIndex += 1
                                } else if (root.practiceExamFinished) {
                                    root.startPracticeMockExam(root.practiceExamQuestions.length || 10)
                                } else {
                                    root.submitPracticeMockExam()
                                }
                            }
                        }
                        SoftButton {
                            Layout.preferredWidth: 72
                            text: "跳过"
                            enabled: root.activePracticeExamIndex < root.practiceExamQuestions.length - 1
                            onClicked: root.activePracticeExamIndex += 1
                        }
                    }
                }
            }
        }

        Component {
            id: mockOptionAnswerComponent
            GridLayout {
                columns: 2
                columnSpacing: 12
                rowSpacing: 12
                Repeater {
                    model: ["A", "B", "C", "D"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 70
                        radius: 18
                        property var question: root.currentPracticeExamQuestion()
                        property bool selected: root.practiceExamOptionSelected(question, modelData)
                        property bool correct: root.normalizePracticeAnswer(question.answer).indexOf(modelData) >= 0
                        color: root.practiceExamFinished && correct ? "#dcfce7" : (selected ? "#eff6ff" : "#f8fbff")
                        border.color: root.practiceExamFinished && correct ? "#22c55e" : (selected ? "#2563eb" : "#e2edf8")
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 12
                            Rectangle {
                                Layout.preferredWidth: 34
                                Layout.preferredHeight: 34
                                radius: 17
                                color: selected ? "#2563eb" : (root.practiceExamFinished && correct ? "#22c55e" : "#ffffff")
                                border.color: selected ? "#2563eb" : "#e2edf8"
                                Text { anchors.centerIn: parent; text: modelData; color: selected || (root.practiceExamFinished && correct) ? "#ffffff" : "#64748b"; font.pixelSize: 14; font.bold: true }
                            }
                            Text { Layout.fillWidth: true; text: root.optionText(root.currentPracticeExamQuestion(), modelData); color: "#111827"; font.pixelSize: 14; wrapMode: Text.WordWrap; maximumLineCount: 2; elide: Text.ElideRight }
                        }
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: root.practiceExamFinished ? Qt.ArrowCursor : Qt.PointingHandCursor
                            enabled: !root.practiceExamFinished
                            onClicked: root.togglePracticeExamObjectiveAnswer(root.currentPracticeExamQuestion(), modelData)
                        }
                    }
                }
            }
        }

        Component {
            id: mockTextAnswerComponent
            TextArea {
                text: root.practiceExamAnswerFor(root.currentPracticeExamQuestion().id)
                placeholderText: "在此输入答案..."
                placeholderTextColor: "#94a3b8"
                wrapMode: TextArea.Wrap
                enabled: !root.practiceExamFinished
                color: "#111827"
                font.pixelSize: 15
                onTextChanged: {
                    if (!root.practiceExamFinished) root.setPracticeExamAnswer(root.currentPracticeExamQuestion().id, text)
                }
                background: Rectangle { radius: 18; color: "#f8fbff"; border.color: "#dbe7f6" }
            }
        }
    }

    component PracticeMockExamPageV2: Item {
        id: mockFormal
        ColumnLayout {
            property int pageMargin: root.narrowShell ? 16 : 28
            width: Math.max(280, (parent.width - pageMargin * 2) / root.examScale)
            height: Math.max(360, (parent.height - pageMargin * 2) / root.examScale)
            anchors.centerIn: parent
            scale: root.examScale
            transformOrigin: Item.Center
            spacing: root.narrowShell ? 12 : 18

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4
                    Text { text: "随机组卷模拟考试"; color: "#111827"; font.pixelSize: 28; font.bold: true }
                    Text { text: "按正式考试界面作答，提交后查看客观题得分与解析"; color: "#8b949e"; font.pixelSize: 13 }
                }
                ExamControlStrip {
                    Layout.preferredWidth: root.narrowShell ? 188 : 224
                    Layout.preferredHeight: 42
                    statusText: "考试中"
                    onExitRequested: root.exitPracticeExamMode()
                }
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: width > 760 ? 4 : 1
                columnSpacing: root.narrowShell ? 12 : 18
                rowSpacing: root.narrowShell ? 12 : 18

                Card {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: parent.width > 760 ? 3 : 1
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: root.narrowShell ? 18 : 28
                        spacing: root.narrowShell ? 12 : 18

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 8
                            Text { Layout.fillWidth: true; text: "模拟试卷"; color: "#111827"; font.pixelSize: 24; font.bold: true; elide: Text.ElideRight }
                            Text {
                                text: root.displayQuestionType(root.currentPracticeExamQuestion().type) + " · 共 " + root.practiceExamQuestions.length + " 题 · 已答 " + root.practiceExamAnsweredCount() + " 题"
                                color: "#64748b"
                                font.pixelSize: 13
                            }
                        }
                        Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }

                        Text {
                            Layout.fillWidth: true
                            text: (root.activePracticeExamIndex + 1) + ". " + (root.currentPracticeExamQuestion().content || "暂无题目")
                            color: "#111827"
                            font.pixelSize: 18
                            font.bold: true
                            wrapMode: Text.WordWrap
                        }

                        Loader {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            sourceComponent: root.isObjective(root.currentPracticeExamQuestion().type) ? mockFormalOptionComponent : mockFormalTextComponent
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: root.practiceExamFinished ? 96 : 0
                            visible: root.practiceExamFinished
                            radius: 18
                            color: root.practiceExamIsCorrect(root.currentPracticeExamQuestion()) ? "#f0fdf4" : "#fff7ed"
                            border.color: root.practiceExamIsCorrect(root.currentPracticeExamQuestion()) ? "#bbf7d0" : "#fed7aa"
                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 14
                                spacing: 5
                                Text {
                                    text: "正确答案：" + (root.currentPracticeExamQuestion().answer || "暂无")
                                    color: root.practiceExamIsCorrect(root.currentPracticeExamQuestion()) ? "#16a34a" : "#f97316"
                                    font.pixelSize: 14
                                    font.bold: true
                                }
                                Text {
                                    Layout.fillWidth: true
                                    text: root.currentPracticeExamQuestion().analysis || "暂无解析"
                                    color: "#475569"
                                    font.pixelSize: 13
                                    wrapMode: Text.WordWrap
                                    maximumLineCount: 2
                                    elide: Text.ElideRight
                                }
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 12
                            SoftButton {
                                Layout.fillWidth: true
                                text: "上一题"
                                enabled: root.activePracticeExamIndex > 0
                                onClicked: root.activePracticeExamIndex -= 1
                            }
                            PrimaryButton {
                                Layout.fillWidth: true
                                text: "下一题"
                                enabled: root.activePracticeExamIndex < root.practiceExamQuestions.length - 1
                                onClicked: root.activePracticeExamIndex += 1
                            }
                        }
                    }
                }

                ColumnLayout {
                    id: mockRightTools
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: 1
                    spacing: root.narrowShell ? 12 : 14
                    ExamClockCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: root.narrowShell ? 150 : 184
                        label: "◷  模拟倒计时"
                        value: (root.practiceTimeLimit < 10 ? "0" : "") + root.practiceTimeLimit + " : 00"
                        hint: root.practiceExamFinished ? ("客观题得分 " + root.practiceExamScoreText()) : "提交后查看解析"
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumHeight: 220
                        radius: 24
                        color: "#ffffff"
                        border.color: "#e5edf6"
                        clip: true
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 14
                            RowLayout {
                                Layout.fillWidth: true
                                Text { text: "答题卡"; color: "#111827"; font.pixelSize: 20; font.bold: true; Layout.fillWidth: true }
                                Text { text: (root.activePracticeExamIndex + 1) + "/" + root.practiceExamQuestions.length; color: "#8b949e"; font.pixelSize: 15 }
                            }
                            Flickable {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                contentWidth: width
                                contentHeight: mockCardGrid.height
                                clip: true
                                interactive: contentHeight > height
                                boundsBehavior: Flickable.StopAtBounds
                                ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                                HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                                GridLayout {
                                    id: mockCardGrid
                                    width: parent.width
                                    columns: 5
                                    columnSpacing: 8
                                    rowSpacing: 8
                                    Repeater {
                                        model: root.practiceExamQuestions
                                        delegate: Rectangle {
                                            Layout.preferredWidth: 38
                                            Layout.preferredHeight: 38
                                            radius: 14
                                            property bool current: index === root.activePracticeExamIndex
                                            property bool answered: root.practiceExamAnswerFor(modelData.id).length > 0
                                            color: current ? "#3b82f6" : (answered ? "#eff6ff" : "#f3f4f6")
                                            border.color: current ? "#3b82f6" : "transparent"
                                            Text { anchors.centerIn: parent; text: String(index + 1); color: current ? "#ffffff" : "#64748b"; font.pixelSize: 14; font.bold: true }
                                            MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.activePracticeExamIndex = index }
                                        }
                                    }
                                }
                            }
                            RowLayout {
                                spacing: 12
                                LegendDot { colorValue: "#dbeafe"; label: "已答" }
                                LegendDot { colorValue: "#f3f4f6"; label: "未答" }
                            }
                        }
                    }
                    DangerButton {
                        Layout.fillWidth: true
                        text: root.practiceExamFinished ? "再抽一套" : "提交试卷"
                        onClicked: {
                            if (root.practiceExamFinished) root.startPracticeMockExam(root.practiceExamQuestions.length || 10)
                            else root.submitPracticeMockExam()
                        }
                    }
                }
            }
        }

        Component {
            id: mockFormalOptionComponent
            ColumnLayout {
                spacing: 12
                Repeater {
                    model: ["A", "B", "C", "D"]
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 68
                        radius: 16
                        property var question: root.currentPracticeExamQuestion()
                        property bool selected: root.practiceExamOptionSelected(question, modelData)
                        property bool correct: root.normalizePracticeAnswer(question.answer).indexOf(modelData) >= 0
                        color: root.practiceExamFinished && correct ? "#dcfce7" : (selected ? "#eff6ff" : "#f8fafc")
                        border.color: root.practiceExamFinished && correct ? "#22c55e" : (selected ? "#3b82f6" : "#e5e7eb")
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 14
                            Rectangle {
                                Layout.preferredWidth: 34
                                Layout.preferredHeight: 34
                                radius: 17
                                color: selected ? "#3b82f6" : (root.practiceExamFinished && correct ? "#22c55e" : "#ffffff")
                                border.color: "#eef2f7"
                                Text { anchors.centerIn: parent; text: modelData; color: selected || (root.practiceExamFinished && correct) ? "#ffffff" : "#64748b"; font.pixelSize: 14; font.bold: true }
                            }
                            Text { Layout.fillWidth: true; text: root.optionText(root.currentPracticeExamQuestion(), modelData); color: "#111827"; font.pixelSize: 15; font.bold: true; wrapMode: Text.WordWrap; maximumLineCount: 3; elide: Text.ElideRight }
                        }
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: root.practiceExamFinished ? Qt.ArrowCursor : Qt.PointingHandCursor
                            enabled: !root.practiceExamFinished
                            onClicked: root.togglePracticeExamObjectiveAnswer(root.currentPracticeExamQuestion(), modelData)
                        }
                    }
                }
            }
        }

        Component {
            id: mockFormalTextComponent
            TextArea {
                text: root.practiceExamAnswerFor(root.currentPracticeExamQuestion().id)
                placeholderText: "在这里输入答案"
                placeholderTextColor: "#94a3b8"
                wrapMode: TextArea.Wrap
                color: "#111827"
                font.pixelSize: 16
                enabled: !root.practiceExamFinished
                onTextChanged: {
                    if (!root.practiceExamFinished) root.setPracticeExamAnswer(root.currentPracticeExamQuestion().id, text)
                }
                background: Rectangle { radius: 18; color: "#ffffff"; border.color: "#e5edf6" }
            }
        }
    }

    component GradeAnalysisPage: PageShell {
        Flow {
            width: parent.width
            spacing: 14
            SectionTitle { width: parent.width; title: "成绩分析"; subtitle: "按科目查看个人成绩趋势、班级均值对比、考试历史和学习建议" }
            FilterCombo {
                id: analysisSubjectCombo
                width: root.narrowShell ? Math.min(parent.width, 190) : 174
                height: 46
                model: root.analysisSubjectOptions()
                currentIndex: Math.max(0, root.analysisSubjectOptions().indexOf(root.activeReportSubject))
                onCurrentTextChanged: {
                    if (currentText !== "暂无成绩") root.activeReportSubject = currentText
                }
            }
            SoftButton { width: root.narrowShell ? 142 : 142; text: "导出科目成绩"; onClicked: root.exportActiveReportExcel() }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1080 ? 4 : (parent.width > 560 ? 2 : 1)
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            GradeKpiCard { Layout.fillWidth: true; label: "最新成绩"; value: root.latestSubjectScoreText(root.activeReportSubject); delta: root.subjectTrendDeltaText(root.activeReportSubject); accent: "#22c55e" }
            GradeKpiCard { Layout.fillWidth: true; label: "科目均分"; value: root.subjectAverageText(root.activeReportSubject); delta: "个人均分"; accent: "#3b82f6" }
            GradeKpiCard { Layout.fillWidth: true; label: "班级排名"; value: root.subjectRankText(root.activeReportSubject); delta: "最近一次"; accent: "#8b5cf6" }
            GradeKpiCard { Layout.fillWidth: true; label: "考试次数"; value: root.scoreHistoryRows(root.activeReportSubject).length + " 场"; delta: "已归档"; accent: "#f59e0b" }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1180 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            TrendChartCard {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1180 ? 2 : 1
                Layout.preferredHeight: root.narrowShell ? 360 : 430
                title: root.activeReportSubject + "成绩趋势"
                subtitle: "绿色为个人曲线，灰色为班级均值，鼠标悬浮节点查看具体数据"
                points: root.subjectTrendPoints(root.activeReportSubject)
                comparePoints: root.classTrendPointsFor(root.activeReportSubject)
                labels: root.trendLabelsFor(root.activeReportSubject)
            }
            SubjectScorePanel {
                Layout.fillWidth: true
                Layout.preferredHeight: root.narrowShell ? 360 : 430
            }
        }

        GridLayout {
            width: parent.width
            columns: parent.width > 1180 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            ExamHistoryPanel {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1180 ? 2 : 1
                Layout.preferredHeight: root.narrowShell ? 430 : 430
            }
            AiAdvicePanel { Layout.fillWidth: true; Layout.preferredHeight: root.narrowShell ? 430 : 430 }
        }
    }

    component ScoreReportPage: PageShell {
        Flow {
            width: parent.width
            spacing: 14
            SectionTitle { width: parent.width; title: "成绩报告"; subtitle: "查看本场考试个人得分、扣分题型和薄弱知识点" }
            FilterCombo {
                id: reportExamCombo
                width: root.narrowShell ? Math.min(parent.width, 260) : 260
                height: 46
                model: root.reportExamRows().map(function(e) { return root.examTitle(e) })
                currentIndex: root.activeReportExamIndex()
                onCurrentIndexChanged: root.selectReportExam(currentIndex)
            }
            SoftButton { width: root.narrowShell ? 118 : 118; text: "导出Excel"; onClicked: root.exportCurrentReportExcel() }
            SoftButton { width: root.narrowShell ? 112 : 112; text: "打印PDF"; onClicked: root.printCurrentReportPdf() }
            SoftButton { width: root.narrowShell ? 128 : 128; text: "返回考试"; onClicked: root.switchPage(1) }
            SoftButton { width: root.narrowShell ? 128 : 128; text: "成绩分析"; onClicked: root.switchPage(3) }
        }
        ScoreReportHeroCard { width: parent.width }
        GridLayout {
            width: parent.width
            columns: parent.width > 1080 ? 4 : (parent.width > 560 ? 2 : 1)
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            ReportKpiCard { Layout.fillWidth: true; label: "本场得分"; value: root.reportTotalScoreNumber() + " / " + root.reportFullScore(); detail: root.reportScoreLevel(); accent: "#22c55e" }
            ReportKpiCard { Layout.fillWidth: true; label: "本场扣分"; value: root.reportLostScore() + " 分"; detail: "按题型追踪"; accent: "#ef4444" }
            ReportKpiCard { Layout.fillWidth: true; label: "薄弱知识点"; value: root.reportWeakKnowledgeRows().length + " 个"; detail: "优先复盘"; accent: "#f59e0b" }
            ReportKpiCard { Layout.fillWidth: true; label: "错扣题目"; value: root.reportDeductionRows().length + " 题"; detail: "查看明细"; accent: "#8b5cf6" }
        }
        GridLayout {
            width: parent.width
            columns: parent.width > 1180 ? 3 : 1
            columnSpacing: root.narrowShell ? 12 : 18
            rowSpacing: root.narrowShell ? 12 : 18
            TypeScoreBreakdownCard {
                Layout.fillWidth: true
                Layout.columnSpan: parent.width > 1180 ? 2 : 1
                Layout.preferredHeight: root.narrowShell ? 470 : 430
            }
            WeakKnowledgePanel {
                Layout.fillWidth: true
                Layout.preferredHeight: root.narrowShell ? 470 : 430
            }
        }
        DeductionDetailPanel { width: parent.width; height: root.narrowShell ? 470 : 430 }
    }

    component ScoreReportHeroCard: Card {
        height: root.narrowShell ? 360 : 260
        GridLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 22 : 30
            columns: root.narrowShell ? 1 : 3
            columnSpacing: 26
            rowSpacing: 18
            ColumnLayout {
                Layout.fillWidth: true
                Layout.columnSpan: root.narrowShell ? 1 : 2
                spacing: 12
                Text {
                    Layout.fillWidth: true
                    text: root.examTitle(root.currentReportExam())
                    color: "#111827"
                    font.pixelSize: root.narrowShell ? 28 : 34
                    font.bold: true
                    elide: Text.ElideRight
                }
                Text {
                    Layout.fillWidth: true
                    text: root.examSubject(root.currentReportExam()) + " · " + (root.currentReportExam().startTime || root.currentReportExam().date || "已完成考试")
                    color: "#64748b"
                    font.pixelSize: 18
                    elide: Text.ElideRight
                }
                Text {
                    Layout.fillWidth: true
                    text: "这份报告按你的个人答题记录统计，重点展示题型得分、扣分来源、薄弱知识点和下一步复盘方向。"
                    color: "#475569"
                    font.pixelSize: 18
                    wrapMode: Text.WordWrap
                }
                Flow {
                    Layout.fillWidth: true
                    spacing: 10
                    ReportTag { text: "题型扣分"; colorValue: "#ef4444"; bg: "#fef2f2" }
                    ReportTag { text: "薄弱知识点"; colorValue: "#f59e0b"; bg: "#fff7ed" }
                    ReportTag { text: "个人诊断"; colorValue: "#2563eb"; bg: "#eff6ff" }
                }
            }
            Rectangle {
                Layout.fillWidth: root.narrowShell
                Layout.preferredWidth: root.narrowShell ? parent.width : 270
                Layout.fillHeight: true
                radius: 24
                color: "#111827"
                Column {
                    anchors.centerIn: parent
                    width: parent.width
                    spacing: 10
                    Text { width: parent.width; text: "本场得分"; color: "#cbd5e1"; font.pixelSize: 18; font.bold: true; horizontalAlignment: Text.AlignHCenter }
                    Text { width: parent.width; text: root.reportTotalScoreNumber(); color: "#ffffff"; font.pixelSize: root.narrowShell ? 56 : 66; font.bold: true; horizontalAlignment: Text.AlignHCenter }
                    Text { width: parent.width; text: "满分 " + root.reportFullScore() + " · 扣 " + root.reportLostScore() + " 分"; color: "#94a3b8"; font.pixelSize: 17; horizontalAlignment: Text.AlignHCenter }
                    Rectangle {
                        width: 108
                        height: 38
                        radius: 19
                        color: root.reportScoreLevel() === "优秀" ? "#064e3b" : (root.reportScoreLevel() === "良好" ? "#1e3a8a" : "#7c2d12")
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text { anchors.centerIn: parent; text: root.reportScoreLevel(); color: "#ffffff"; font.pixelSize: 18; font.bold: true }
                    }
                }
            }
        }
    }

    component ReportTag: Rectangle {
        id: tag
        property string text: ""
        property color colorValue: "#2563eb"
        property color bg: "#eff6ff"
        width: Math.max(104, tagText.implicitWidth + 28)
        height: 38
        radius: 19
        color: tag.bg
        Text { id: tagText; anchors.centerIn: parent; text: tag.text; color: tag.colorValue; font.pixelSize: 17; font.bold: true }
    }

    component ReportKpiCard: Card {
        id: kpi
        property string label: ""
        property string value: ""
        property string detail: ""
        property color accent: "#22c55e"
        height: root.narrowShell ? 132 : 150
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 22
            spacing: 8
            Text { text: kpi.label; color: "#64748b"; font.pixelSize: 17; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { text: kpi.value; color: "#111827"; font.pixelSize: root.narrowShell ? 27 : 31; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            RowLayout {
                Layout.fillWidth: true
                Rectangle { Layout.preferredWidth: 56; Layout.preferredHeight: 5; radius: 3; color: kpi.accent; opacity: 0.75 }
                Text { text: kpi.detail; color: kpi.accent; font.pixelSize: 16; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            }
        }
    }

    component TypeScoreBreakdownCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16
            RowLayout {
                Layout.fillWidth: true
                Text { text: "题型得分与扣分"; color: "#111827"; font.pixelSize: 24; font.bold: true; Layout.fillWidth: true }
                Text { text: "按本场考试统计"; color: "#94a3b8"; font.pixelSize: 15 }
            }
            Repeater {
                model: root.reportTypeRows()
                delegate: Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 78
                    radius: 18
                    color: "#ffffff"
                    border.color: "#e5edf6"
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 14
                        spacing: 8
                        RowLayout {
                            Layout.fillWidth: true
                            Text { text: modelData.type; color: "#111827"; font.pixelSize: 18; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                            Text { text: "得 " + modelData.score + " / " + modelData.full; color: modelData.color; font.pixelSize: 18; font.bold: true }
                            Text { text: "扣 " + modelData.deduct; color: "#ef4444"; font.pixelSize: 17; font.bold: true }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 10
                            radius: 5
                            color: "#eef2f7"
                            Rectangle {
                                width: parent.width * Math.max(0, Math.min(1, Number(modelData.score || 0) / Math.max(1, Number(modelData.full || 1))))
                                height: parent.height
                                radius: parent.radius
                                color: modelData.color
                            }
                        }
                    }
                }
            }
        }
    }

    component WeakKnowledgePanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "薄弱知识点"; color: "#111827"; font.pixelSize: 24; font.bold: true }
            Flickable {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: width
                contentHeight: weakKnowledgeColumn.height
                clip: true
                interactive: contentHeight > height
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                Column {
                    id: weakKnowledgeColumn
                    width: parent.width
                    spacing: 12
                    Repeater {
                        model: root.reportWeakKnowledgeRows()
                        delegate: Rectangle {
                            width: weakKnowledgeColumn.width
                            height: 112
                            radius: 18
                            color: "#fffaf2"
                            border.color: "#fed7aa"
                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 14
                                spacing: 6
                                RowLayout {
                                    Layout.fillWidth: true
                                    Text { text: modelData.name; color: "#111827"; font.pixelSize: 18; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                                    Text { text: "掌握 " + modelData.mastery + "%"; color: "#f97316"; font.pixelSize: 16; font.bold: true }
                                }
                                Text { Layout.fillWidth: true; text: modelData.reason; color: "#7c2d12"; font.pixelSize: 15; elide: Text.ElideRight }
                                Text { Layout.fillWidth: true; text: "建议：" + modelData.advice; color: "#475569"; font.pixelSize: 15; elide: Text.ElideRight }
                            }
                        }
                    }
                }
            }
        }
    }

    component DeductionDetailPanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            RowLayout {
                Layout.fillWidth: true
                Text { text: "扣分明细"; color: "#111827"; font.pixelSize: 24; font.bold: true; Layout.fillWidth: true }
                Text { text: "具体到题目、题型和知识点"; color: "#94a3b8"; font.pixelSize: 15 }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 44
                radius: 14
                color: "#f8fafc"
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    Text { text: "题目"; color: "#8b949e"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 82 }
                    Text { text: "题型"; color: "#8b949e"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 92 }
                    Text { text: "得分/满分"; color: "#8b949e"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 96 }
                    Text { text: "扣分"; color: "#8b949e"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 70 }
                    Text { text: "薄弱知识点与原因"; color: "#8b949e"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true }
                }
            }
            Flickable {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: width
                contentHeight: deductionColumn.height
                clip: true
                interactive: contentHeight > height
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                Column {
                    id: deductionColumn
                    width: parent.width
                    spacing: 10
                    Repeater {
                        model: root.reportDeductionRows()
                        delegate: Rectangle {
                            width: deductionColumn.width
                            height: root.narrowShell ? 116 : 74
                            radius: 16
                            color: "#ffffff"
                            border.color: "#e5edf6"
                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 16
                                anchors.rightMargin: 16
                                spacing: 12
                                Text { text: modelData.index; color: "#111827"; font.pixelSize: 16; font.bold: true; Layout.preferredWidth: 82 }
                                Text { text: modelData.type; color: "#2563eb"; font.pixelSize: 15; font.bold: true; Layout.preferredWidth: 92; elide: Text.ElideRight }
                                Text { text: modelData.score + "/" + modelData.full; color: "#111827"; font.pixelSize: 15; font.bold: true; Layout.preferredWidth: 96 }
                                Text { text: "-" + modelData.deduct; color: "#ef4444"; font.pixelSize: 16; font.bold: true; Layout.preferredWidth: 70 }
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 4
                                    Text { Layout.fillWidth: true; text: modelData.knowledge; color: "#111827"; font.pixelSize: 15; font.bold: true; elide: Text.ElideRight }
                                    Text { Layout.fillWidth: true; text: modelData.reason; color: "#64748b"; font.pixelSize: 14; elide: Text.ElideRight }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    component GradeKpiCard: Card {
        id: kpi
        property string label: ""
        property string value: ""
        property string delta: ""
        property color accent: "#22c55e"
        height: root.narrowShell ? 128 : 150
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 18 : 22
            spacing: root.narrowShell ? 6 : 8
            RowLayout {
                Layout.fillWidth: true
                Text { text: kpi.label; color: "#64748b"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true }
                Rectangle {
                    Layout.preferredWidth: 72
                    Layout.preferredHeight: 28
                    radius: 14
                    color: Qt.rgba(kpi.accent.r, kpi.accent.g, kpi.accent.b, 0.10)
                    Text { anchors.centerIn: parent; text: kpi.delta; color: kpi.accent; font.pixelSize: 11; font.bold: true }
                }
            }
            Text { text: kpi.value; color: "#111827"; font.pixelSize: root.narrowShell ? 30 : 38; font.bold: true }
            ProgressBarLine { Layout.fillWidth: true; value: 0.82; accent: kpi.accent }
        }
    }

    component SubjectScorePanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16
            Text { text: "科目成绩"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Text {
                Layout.fillWidth: true
                visible: root.subjectScoreRows().length === 0
                text: "暂无科目成绩"
                color: "#94a3b8"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
            }
            Repeater {
                model: root.subjectScoreRows()
                delegate: SubjectScoreRow { Layout.fillWidth: true; row: modelData }
            }
        }
    }

    component SubjectScoreRow: ColumnLayout {
        id: row
        property var row: ({})
        spacing: 8
        RowLayout {
            Layout.fillWidth: true
            Text { text: row.row.name; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true }
            Text { text: row.row.score; color: row.row.color; font.pixelSize: 15; font.bold: true }
            Rectangle { Layout.preferredWidth: 50; Layout.preferredHeight: 26; radius: 13; color: "#eff6ff"; Text { anchors.centerIn: parent; text: row.row.level; color: row.row.color; font.pixelSize: 11; font.bold: true } }
        }
        ProgressBarLine {
            Layout.fillWidth: true
            value: isNaN(Number(row.row.score)) ? 0 : Number(row.row.score) / Math.max(1, Number(row.row.full || 100))
            accent: row.row.color
        }
    }

    component ExamHistoryPanel: Card {
        id: history
        property var rows: root.examHistoryRows(root.activeReportSubject)
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            RowLayout {
                Layout.fillWidth: true
                Text { text: "考试历史"; color: "#111827"; font.pixelSize: 22; font.bold: true; Layout.fillWidth: true }
                Text { text: "共 " + history.rows.length + " 场"; color: "#94a3b8"; font.pixelSize: 13 }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 42
                color: "#f8fafc"
                radius: 14
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 14
                    anchors.rightMargin: 14
                    Text { text: "考试名称"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.fillWidth: true }
                    Text { visible: !root.narrowShell; text: "考试日期"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.preferredWidth: 130 }
                    Text { text: "得分"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.preferredWidth: 70 }
                    Text { visible: !root.narrowShell; text: "满分"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.preferredWidth: 70 }
                    Text { visible: !root.narrowShell; text: "班级排名"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.preferredWidth: 92 }
                    Text { text: "评级"; color: "#8b949e"; font.pixelSize: 12; font.bold: true; Layout.preferredWidth: 70 }
                }
            }
            Flickable {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: width
                contentHeight: historyColumn.height
                clip: true
                interactive: contentHeight > height
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: contentHeight > height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }
                HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                Column {
                    id: historyColumn
                    width: parent.width
                    spacing: 10
                    Text {
                        width: parent.width
                        height: history.rows.length === 0 ? 160 : 0
                        visible: history.rows.length === 0
                        text: "暂无考试历史"
                        color: "#94a3b8"
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    Repeater {
                        model: history.rows
                        delegate: HistoryRow { width: historyColumn.width; row: modelData }
                    }
                }
            }
        }
    }

    component HistoryRow: Rectangle {
        id: row
        property var row: ({})
        height: 58
        Layout.preferredHeight: 58
        radius: 14
        color: "#ffffff"
        border.color: "#eef2f7"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 14
            anchors.rightMargin: 14
            Text { text: row.row.name; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { visible: !root.narrowShell; text: row.row.date; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 130 }
            Text { text: row.row.score; color: row.row.accent || "#22c55e"; font.pixelSize: 15; font.bold: true; Layout.preferredWidth: 70 }
            Text { visible: !root.narrowShell; text: row.row.full || 100; color: "#8b949e"; font.pixelSize: 13; Layout.preferredWidth: 70 }
            Text { visible: !root.narrowShell; text: row.row.rank; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 92 }
            Rectangle {
                Layout.preferredWidth: 62
                Layout.preferredHeight: 28
                radius: 14
                color: row.row.level === "优秀" ? "#ecfdf3" : (row.row.level === "良好" ? "#eff6ff" : "#fff7ed")
                Text {
                    anchors.centerIn: parent
                    text: row.row.level
                    color: row.row.level === "优秀" ? "#16a34a" : (row.row.level === "良好" ? "#2563eb" : "#f59e0b")
                    font.pixelSize: 12
                    font.bold: true
                }
            }
        }
    }

    component AiAdvicePanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "AI 个性化建议"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: width > 980 ? 3 : 1
                columnSpacing: 14
                rowSpacing: 14
                Repeater {
                    model: root.aiSuggestions
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredHeight: 132
                        radius: 18
                        color: "#ffffff"
                        border.color: "#eef2f7"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 12
                            Rectangle { Layout.preferredWidth: 8; Layout.fillHeight: true; radius: 4; color: modelData.color }
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 8
                                Text { Layout.fillWidth: true; text: modelData.title; color: "#111827"; font.pixelSize: 15; font.bold: true; wrapMode: Text.WordWrap; maximumLineCount: 2; elide: Text.ElideRight }
                                Text { Layout.fillWidth: true; text: modelData.body; color: "#64748b"; font.pixelSize: 12; wrapMode: Text.WordWrap; maximumLineCount: 4; elide: Text.ElideRight }
                            }
                        }
                    }
                }
            }
        }
    }

    component DistributionCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14
            Text { text: "分数区间"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Repeater {
                model: root.scoreReport.distribution || []
                delegate: RowLayout {
                    Layout.fillWidth: true
                    spacing: 12
                    Text { text: modelData.label; color: "#64748b"; font.pixelSize: 13; Layout.preferredWidth: 72 }
                    ProgressBarLine { Layout.fillWidth: true; value: Number(modelData.value || 0) / 20; accent: "#2563eb" }
                    Text { text: modelData.value + "人"; color: "#111827"; font.pixelSize: 13; font.bold: true; Layout.preferredWidth: 44 }
                }
            }
        }
    }

    component WeakQuestionCard: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 12
            Text { text: "题目分析"; color: "#111827"; font.pixelSize: 22; font.bold: true }
            Repeater {
                model: root.scoreReport.questionAnalysis || []
                delegate: Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 62
                    radius: 16
                    color: modelData.low ? "#fff7ed" : "#ffffff"
                    border.color: modelData.low ? "#fed7aa" : "#e5edf6"
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        Text { text: modelData.index || "--"; color: "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true }
                        Text { text: "均分 " + (modelData.average || "--") + " / " + (modelData.full || "--"); color: modelData.low ? "#f97316" : "#2563eb"; font.pixelSize: 14; font.bold: true }
                    }
                }
            }
        }
    }

    component ProfilePage: PageShell {
        SectionTitle {}
        Card {
            width: parent.width
            height: root.narrowShell ? 330 : 240
            GridLayout {
                anchors.fill: parent
                anchors.margins: root.narrowShell ? 22 : 32
                columns: root.narrowShell ? 1 : 3
                columnSpacing: root.narrowShell ? 16 : 28
                rowSpacing: root.narrowShell ? 16 : 20
                Avatar { Layout.preferredWidth: root.narrowShell ? 88 : 116; Layout.preferredHeight: root.narrowShell ? 88 : 116; label: root.avatarText() }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10
                    Text { text: root.profileName(); color: "#111827"; font.pixelSize: root.narrowShell ? 34 : 40; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                    Text { text: "学号：" + (root.profile.studentNo || "--"); color: "#475569"; font.pixelSize: 19; Layout.fillWidth: true; elide: Text.ElideRight }
                    Text { text: "班级：" + (root.profile.className || "--"); color: "#475569"; font.pixelSize: 19; Layout.fillWidth: true; elide: Text.ElideRight }
                    Flow {
                        Layout.fillWidth: true
                        spacing: 10
                        ProfilePill { text: "学生账号"; tone: "#2563eb"; bg: "#eff6ff" }
                        ProfilePill { text: "通知已开启"; tone: "#16a34a"; bg: "#ecfdf3" }
                    }
                }
                SoftButton {
                    Layout.fillWidth: root.narrowShell
                    Layout.preferredWidth: root.narrowShell ? parent.width : 150
                    Layout.preferredHeight: 58
                    text: "退出登录"
                    onClicked: studentApi.logout()
                }
            }
        }
        ProfileInfoGrid { width: parent.width; visible: root.profileMode === 0 }
        ProfileActions { width: parent.width; visible: root.profileMode === 0 }
        EditProfilePanel { width: parent.width; height: root.narrowShell ? 680 : 560; visible: root.profileMode === 1 }
        PasswordPanel { width: parent.width; height: root.narrowShell ? 650 : 540; visible: root.profileMode === 2 }
        SettingPanel { width: parent.width; height: root.narrowShell ? 680 : 560; visible: root.profileMode === 3 }
    }

    component ProfilePill: Rectangle {
        property string text: ""
        property color tone: "#2563eb"
        property color bg: "#eff6ff"
        width: Math.max(112, pillText.implicitWidth + 28)
        height: 38
        radius: 19
        color: bg
        Text { id: pillText; anchors.centerIn: parent; text: parent.text; color: parent.tone; font.pixelSize: 17; font.bold: true }
    }

    component ProfileInfoGrid: GridLayout {
        columns: width > 980 ? 4 : 2
        columnSpacing: root.narrowShell ? 12 : 18
        rowSpacing: root.narrowShell ? 12 : 18
        ProfileInfoCard { Layout.fillWidth: true; title: "账号身份"; value: "学生"; detail: "可参加考试与题库练习"; accent: "#2563eb" }
        ProfileInfoCard { Layout.fillWidth: true; title: "当前班级"; value: root.profile.className || "--"; detail: "成绩统计按班级归档"; accent: "#16a34a" }
        ProfileInfoCard { Layout.fillWidth: true; title: "学号"; value: root.profile.studentNo || "--"; detail: "与数据库注册信息同步"; accent: "#8b5cf6" }
        ProfileInfoCard { Layout.fillWidth: true; title: "学习提醒"; value: root.notificationCount() + " 条"; detail: "考试与成绩通知"; accent: "#f59e0b" }
    }

    component ProfileInfoCard: Rectangle {
        id: infoCard
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
            color: infoCard.accent
        }
        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: root.narrowShell ? 22 : 28
            anchors.rightMargin: root.narrowShell ? 18 : 24
            anchors.topMargin: root.narrowShell ? 18 : 24
            anchors.bottomMargin: root.narrowShell ? 18 : 22
            spacing: root.narrowShell ? 7 : 9
            Text { text: infoCard.title; color: "#64748b"; font.pixelSize: 17; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { text: infoCard.value; color: "#111827"; font.pixelSize: root.narrowShell ? 26 : 30; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
            Text { text: infoCard.detail; color: "#64748b"; font.pixelSize: 16; Layout.fillWidth: true; elide: Text.ElideRight }
        }
    }

    component ProfileActions: GridLayout {
        columns: width > 980 ? 3 : 1
        columnSpacing: root.narrowShell ? 12 : 18
        rowSpacing: root.narrowShell ? 12 : 18
        ProfileAction { Layout.fillWidth: true; title: "修改个人信息"; hint: "姓名、学号、班级信息"; colorMark: "#2563eb"; mode: 1 }
        ProfileAction { Layout.fillWidth: true; title: "修改密码"; hint: "更新账号登录密码"; colorMark: "#8b5cf6"; mode: 2 }
        ProfileAction { Layout.fillWidth: true; title: "考试设置"; hint: "提醒、答题偏好、自动保存"; colorMark: "#16a34a"; mode: 3 }
    }

    component EditProfilePanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 24 : 32
            spacing: 22
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.preferredWidth: 118; Layout.preferredHeight: 54 }
                Text {
                    text: "修改个人信息"
                    color: "#111827"
                    font.pixelSize: 30
                    font.bold: true
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                SoftButton { Layout.preferredWidth: 118; text: "返回"; onClicked: root.profileMode = 0 }
            }
            Text { Layout.fillWidth: true; text: "保持姓名、学号和班级与注册数据库一致，保存后首页、考试记录和成绩分析会同步更新。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
            GridLayout {
                Layout.fillWidth: true
                columns: width > 780 ? 3 : 1
                columnSpacing: 18
                rowSpacing: 18
                FormField { id: profileNameField; Layout.fillWidth: true; label: "姓名"; text: root.profile.name || "" }
                FormField { id: profileNoField; Layout.fillWidth: true; label: "学号"; text: root.profile.studentNo || "" }
                FormField { id: profileClassField; Layout.fillWidth: true; label: "班级"; text: root.profile.className || "" }
            }
            Rectangle {
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
                        Text { text: "资料同步"; color: "#111827"; font.pixelSize: 22; font.bold: true }
                        Text { Layout.fillWidth: true; text: "学号与班级建议按注册表填写，方便老师在考试列表、批改记录和成绩报表中准确筛选。"; color: "#64748b"; font.pixelSize: 17; wrapMode: Text.WordWrap }
                    }
                }
            }
            Item { Layout.fillHeight: true }
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true }
                PrimaryButton {
                    Layout.preferredWidth: 170
                    text: "保存"
                    onClicked: root.saveProfileChanges(profileNameField.text, profileNoField.text, profileClassField.text)
                }
            }
        }
    }

    component PasswordPanel: Card {
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 24 : 32
            spacing: 22
            RowLayout {
                Layout.fillWidth: true
                Text { text: "修改密码"; color: "#111827"; font.pixelSize: 30; font.bold: true; Layout.fillWidth: true }
                SoftButton { Layout.preferredWidth: 118; text: "返回"; onClicked: root.profileMode = 0 }
            }
            Text { Layout.fillWidth: true; text: "建议使用不少于 6 位的新密码。更新后下次登录会使用新密码。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
            GridLayout {
                Layout.fillWidth: true
                columns: width > 780 ? 3 : 1
                columnSpacing: 18
                rowSpacing: 18
                FormField { id: oldPasswordField; Layout.fillWidth: true; label: "原密码"; echoMode: TextInput.Password }
                FormField { id: newPasswordField; Layout.fillWidth: true; label: "新密码"; echoMode: TextInput.Password }
                FormField { id: confirmPasswordField; Layout.fillWidth: true; label: "确认新密码"; echoMode: TextInput.Password }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 126
                radius: 22
                color: "#fff7ed"
                border.color: "#fed7aa"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 22
                    spacing: 8
                    Text { text: "安全建议"; color: "#9a3412"; font.pixelSize: 22; font.bold: true }
                    Text { Layout.fillWidth: true; text: "不要与其他平台共用密码，考试前请提前确认账号能正常登录。"; color: "#9a3412"; font.pixelSize: 17; wrapMode: Text.WordWrap }
                }
            }
            Item { Layout.fillHeight: true }
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true }
                PrimaryButton {
                    Layout.preferredWidth: 180
                    text: "更新密码"
                    onClicked: root.savePasswordChange(oldPasswordField.text, newPasswordField.text, confirmPasswordField.text)
                }
            }
        }
    }

    component SettingPanel: Card {
        id: settingPanel
        property var saved: root.profile.settings || ({})
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 24 : 32
            spacing: 18
            RowLayout {
                Layout.fillWidth: true
                Text { text: "考试设置"; color: "#111827"; font.pixelSize: 30; font.bold: true; Layout.fillWidth: true }
                SoftButton { Layout.preferredWidth: 118; text: "返回"; onClicked: root.profileMode = 0 }
            }
            Text { Layout.fillWidth: true; text: "控制考试提醒、答题保存和答题卡显示方式，设置会在进入考试和题库练习时生效。"; color: "#64748b"; font.pixelSize: 18; wrapMode: Text.WordWrap }
            SettingSwitch { id: noticeSwitch; Layout.fillWidth: true; title: "考试提醒"; hint: "发布考试和临近开考时显示提醒"; checked: settingPanel.saved.noticeEnabled !== false }
            SettingSwitch { id: autoSaveSwitch; Layout.fillWidth: true; title: "自动保存"; hint: "答题过程中保留当前输入状态"; checked: settingPanel.saved.autoSaveEnabled !== false }
            SettingSwitch { id: compactSwitch; Layout.fillWidth: true; title: "紧凑答题卡"; hint: "题量较多时使用更紧凑的答题卡"; checked: settingPanel.saved.compactMode === true }
            Item { Layout.fillHeight: true }
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true }
                PrimaryButton {
                    Layout.preferredWidth: 180
                    text: "保存设置"
                    onClicked: root.saveSettingChanges(noticeSwitch.checked, autoSaveSwitch.checked, compactSwitch.checked)
                }
            }
        }
    }

    component FormField: ColumnLayout {
        id: field
        property alias text: input.text
        property string label: ""
        property int echoMode: TextInput.Normal
        spacing: 10
        Text { text: field.label; color: "#64748b"; font.pixelSize: 18; font.bold: true }
        TextField {
            id: input
            Layout.fillWidth: true
            Layout.preferredHeight: 62
            echoMode: field.echoMode
            color: "#111827"
            font.pixelSize: 19
            verticalAlignment: TextInput.AlignVCenter
            leftPadding: 18
            rightPadding: 18
            topPadding: 0
            bottomPadding: 0
            background: Rectangle { radius: 18; color: "#ffffff"; border.color: input.activeFocus ? "#2563eb" : "#dbe5f3"; border.width: input.activeFocus ? 2 : 1 }
        }
    }

    component SettingSwitch: Rectangle {
        id: setting
        property string title: ""
        property string hint: ""
        property bool checked: false
        height: 92
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
                Text { text: setting.title; color: "#111827"; font.pixelSize: 20; font.bold: true }
                Text { text: setting.hint; color: "#64748b"; font.pixelSize: 16; Layout.fillWidth: true; elide: Text.ElideRight }
            }
            Rectangle {
                Layout.preferredWidth: 76
                Layout.preferredHeight: 38
                radius: 19
                color: setting.checked ? "#2563eb" : "#cbd5e1"
                Behavior on color { ColorAnimation { duration: 160 } }
                Rectangle {
                    width: 30
                    height: 30
                    radius: 15
                    y: 4
                    x: setting.checked ? 42 : 4
                    color: "#ffffff"
                    Behavior on x { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }
                }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: setting.checked = !setting.checked }
            }
        }
    }

    component ProfileAction: Card {
        id: action
        property string title: ""
        property string hint: ""
        property color colorMark: "#2563eb"
        property int mode: 0
        height: root.narrowShell ? 178 : 198
        RowLayout {
            anchors.fill: parent
            anchors.margins: root.narrowShell ? 22 : 28
            spacing: 18
            Rectangle { Layout.preferredWidth: 12; Layout.preferredHeight: 86; radius: 6; color: action.colorMark }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 10
                Text { text: action.title; color: "#111827"; font.pixelSize: root.narrowShell ? 24 : 27; font.bold: true; Layout.fillWidth: true; elide: Text.ElideRight }
                Text { text: action.hint; color: "#64748b"; font.pixelSize: 18; Layout.fillWidth: true; wrapMode: Text.WordWrap }
            }
            Text { text: "›"; color: action.colorMark; font.pixelSize: 36; font.bold: true; Layout.alignment: Qt.AlignVCenter }
        }
        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.profileMode = action.mode }
    }

    component DetailBlock: Rectangle {
        id: detailBlock
        property string title: ""
        property string text: ""
        property bool accent: false
        Layout.fillWidth: true
        Layout.preferredHeight: accent ? 86 : 110
        radius: 18
        color: accent ? "#eff6ff" : "#ffffff"
        border.color: accent ? "#bfdbfe" : "#e5edf6"
        Column {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 6
            Text { text: detailBlock.title; color: "#64748b"; font.pixelSize: 12; font.bold: true }
            Text { width: parent.width; text: detailBlock.text; color: "#111827"; font.pixelSize: 15; wrapMode: Text.WordWrap; maximumLineCount: 4; elide: Text.ElideRight }
        }
    }

    component ExamClockCard: Rectangle {
        id: clockCard
        property string label: "◷  剩余时间"
        property string value: "42 : 12"
        property string hint: ""
        radius: 24
        color: "#202124"
        border.color: "#2f3136"
        clip: true
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#2a2d34" }
                GradientStop { position: 1.0; color: "#17181c" }
            }
        }
        Column {
            anchors.centerIn: parent
            width: parent.width
            spacing: root.narrowShell ? 10 : 14
            Text {
                width: parent.width
                text: clockCard.label
                color: "#9ca3af"
                font.pixelSize: root.narrowShell ? 15 : 17
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                width: parent.width
                text: clockCard.value
                color: "#ffffff"
                font.pixelSize: root.narrowShell ? 42 : 56
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                width: parent.width
                text: clockCard.hint
                color: "#9ca3af"
                font.pixelSize: root.narrowShell ? 15 : 17
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
    }

    component ExamControlStrip: Rectangle {
        id: strip
        property string statusText: "考试中"
        signal exitRequested()
        implicitWidth: 224
        implicitHeight: 40
        Layout.preferredHeight: 40
        radius: 0
        color: "transparent"
        border.color: "transparent"
        Row {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: strip.width < 214 ? 8 : 12
            Rectangle {
                width: strip.width < 214 ? 84 : 96
                height: 36
                radius: 18
                color: "#fef2f2"
                border.color: "#fecaca"
                Text { anchors.centerIn: parent; text: strip.statusText; color: "#ef4444"; font.pixelSize: 13; font.bold: true }
            }
            DangerButton {
                width: strip.width < 214 ? 96 : 104
                height: 36
                text: "退出考试"
                onClicked: strip.exitRequested()
            }
        }
    }

    component PrimaryButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        signal clicked()
        implicitHeight: 54
        height: 54
        opacity: enabled ? 1 : 0.55
        Rectangle {
            anchors.fill: parent
            radius: 15
            color: control.hovered ? "#1d4ed8" : "#2563eb"
        }
        Text { anchors.centerIn: parent; text: control.text; color: "#ffffff"; font.pixelSize: 18; font.bold: true }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; enabled: control.enabled; onClicked: control.clicked() }
    }

    component SoftButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        signal clicked()
        implicitHeight: 54
        height: 54
        opacity: enabled ? 1 : 0.55
        Rectangle { anchors.fill: parent; radius: 15; color: control.hovered ? "#eef6ff" : "#f6f8fc" }
        Text { anchors.centerIn: parent; text: control.text; color: "#2563eb"; font.pixelSize: 18; font.bold: true }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; enabled: control.enabled; onClicked: control.clicked() }
    }

    component DangerButton: Item {
        id: control
        property string text: ""
        property bool hovered: mouse.containsMouse
        signal clicked()
        implicitHeight: 54
        height: 54
        opacity: enabled ? 1 : 0.55
        Rectangle {
            anchors.fill: parent
            radius: 15
            color: control.hovered ? "#dc2626" : "#ff4b4b"
        }
        Text { anchors.centerIn: parent; text: control.text; color: "#ffffff"; font.pixelSize: 18; font.bold: true }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; enabled: control.enabled; onClicked: control.clicked() }
    }

    component LegendDot: Row {
        id: legend
        property color colorValue: "#dbeafe"
        property string label: ""
        spacing: 6
        Rectangle { width: 12; height: 12; radius: 4; color: legend.colorValue; anchors.verticalCenter: parent.verticalCenter }
        Text { text: legend.label; color: "#8b949e"; font.pixelSize: 12; anchors.verticalCenter: parent.verticalCenter }
    }

    component StudentTopNav: Rectangle {
        id: nav
        color: (root.examMode || root.practiceExamMode) ? "#ffffff" : "#f8fafc"
        border.color: (root.examMode || root.practiceExamMode) ? "#fee2e2" : "#eef2f7"
        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
            opacity: (root.examMode || root.practiceExamMode) ? 0.96 : 0.78
        }
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: (root.examMode || root.practiceExamMode) ? "#fff7f7" : "#ffffff" }
                GradientStop { position: 1.0; color: (root.examMode || root.practiceExamMode) ? "#ffffff" : "#ecfdf3" }
            }
            opacity: (root.examMode || root.practiceExamMode) ? 0.62 : 0.32
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed: studentApi.startWindowMove()
        }

        Loader {
            anchors.fill: parent
            sourceComponent: (root.examMode || root.practiceExamMode) ? examNavComponent : normalNavComponent
        }

        Component {
            id: normalNavComponent
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: root.width < 760 ? 8 : (root.narrowShell ? 14 : 32)
                anchors.rightMargin: root.width < 760 ? 8 : (root.narrowShell ? 12 : 24)
                spacing: root.width < 760 ? 6 : (root.narrowShell ? 8 : 18)

                RowLayout {
                    Layout.preferredWidth: root.width < 760 ? 42 : (root.narrowShell ? 66 : (root.compactShell ? 166 : 260))
                    spacing: root.narrowShell ? 0 : 16
                    LogoMark { Layout.preferredWidth: root.width < 760 ? 38 : (root.narrowShell ? 46 : 62); Layout.preferredHeight: root.width < 760 ? 38 : (root.narrowShell ? 46 : 62) }
                    ColumnLayout {
                        visible: !root.narrowShell
                        spacing: 0
                        Text { text: "智考星"; color: "#111827"; font.pixelSize: 38; font.bold: true }
                        Text { text: "学生端"; color: "#8b949e"; font.pixelSize: 19; font.bold: true }
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                    Layout.preferredHeight: root.narrowShell ? 60 : 82
                    clip: true
                    Flickable {
                        anchors.fill: parent
                        contentWidth: studentNavRow.implicitWidth
                        contentHeight: height
                        clip: true
                        boundsBehavior: Flickable.StopAtBounds
                        interactive: contentWidth > width
                        Row {
                            id: studentNavRow
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: root.width < 760 ? 5 : (root.narrowShell ? 7 : 14)
                            Repeater {
                                model: root.menuItems
                                TopNavButton {
                                    width: root.width < 760 ? 74 : (root.narrowShell ? 98 : (root.compactShell ? 148 : 196))
                                    height: root.narrowShell ? 56 : 78
                                    text: modelData.title
                                    icon: modelData.icon
                                    selected: root.currentPage === modelData.page && !root.examMode
                                    onClicked: root.switchPage(modelData.page)
                                }
                            }
                        }
                    }
                }

                StudentNotificationButton { Layout.preferredWidth: root.width < 760 ? 42 : (root.narrowShell ? 54 : 66); Layout.preferredHeight: root.width < 760 ? 44 : (root.narrowShell ? 56 : 76) }
                StudentUserMenu { Layout.preferredWidth: root.width < 760 ? 46 : (root.narrowShell ? 64 : (root.compactShell ? 86 : 230)); Layout.preferredHeight: root.width < 760 ? 44 : (root.narrowShell ? 56 : 76) }
                WindowControls {
                    Layout.preferredWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.minimumWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.preferredHeight: root.width < 760 ? 38 : (root.narrowShell ? 44 : 50)
                }
            }
        }

        Component {
            id: examNavComponent
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: root.width < 760 ? 8 : (root.narrowShell ? 12 : 28)
                anchors.rightMargin: root.width < 760 ? 8 : (root.narrowShell ? 10 : 18)
                spacing: root.width < 760 ? 6 : (root.narrowShell ? 8 : 14)
                LogoMark { Layout.preferredWidth: root.width < 760 ? 30 : (root.narrowShell ? 34 : 42); Layout.preferredHeight: root.width < 760 ? 30 : (root.narrowShell ? 34 : 42) }
                Text { visible: !root.narrowShell; text: "智考星"; color: "#111827"; font.pixelSize: 17; font.bold: true }
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                    spacing: 2
                    Text { Layout.fillWidth: true; text: root.practiceExamMode ? "随机组卷模拟考试" : root.examTitle(root.selectedExam()); color: "#111827"; font.pixelSize: 17; font.bold: true; elide: Text.ElideRight }
                    Text { text: root.practiceExamMode ? (root.practiceExamAnsweredCount() + " / " + root.practiceExamQuestions.length + " 已作答") : (root.answeredCount() + " / " + root.questions.length + " 已作答"); color: "#64748b"; font.pixelSize: 12 }
                }
                WindowControls {
                    Layout.preferredWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.minimumWidth: root.width < 760 ? 112 : (root.narrowShell ? 132 : 150)
                    Layout.preferredHeight: root.width < 760 ? 38 : (root.narrowShell ? 44 : 50)
                }
            }
        }
    }

    component StudentUserMenu: Item {
        id: menu
        property bool hovered: chipMouse.containsMouse
        z: 1
        Rectangle {
            id: profileChip
            anchors.fill: parent
            radius: 28
            color: menu.hovered ? "#f0fdf4" : "#ffffff"
            border.color: menu.hovered ? "#bbf7d0" : "#eef2f7"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: root.compactShell ? 5 : 8
                anchors.rightMargin: root.compactShell ? 5 : 14
                spacing: root.compactShell ? 0 : 10
                Avatar { Layout.preferredWidth: root.narrowShell ? 42 : 56; Layout.preferredHeight: root.narrowShell ? 42 : 56; label: root.avatarText() }
                ColumnLayout {
                    visible: !root.compactShell
                    Layout.fillWidth: true
                    spacing: 0
                    Text { Layout.fillWidth: true; text: root.profileName(); color: "#111827"; font.pixelSize: 24; font.bold: true; elide: Text.ElideRight }
                    Text { Layout.fillWidth: true; text: root.profile.className || "2022 级 1 班"; color: "#7b8494"; font.pixelSize: 18; font.bold: true; elide: Text.ElideRight }
                }
            }
            MouseArea {
                id: chipMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: root.openProfileCenter(0)
            }
        }
    }

    component MenuAction: Rectangle {
        id: item
        property string title: ""
        property string hint: ""
        property bool danger: false
        signal clicked()
        height: 42
        radius: 14
        color: actionMouse.containsMouse ? (danger ? "#fef2f2" : "#f0fdf4") : "transparent"
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            spacing: 8
            Text { text: item.title; color: item.danger ? "#ef4444" : "#111827"; font.pixelSize: 14; font.bold: true; Layout.fillWidth: true }
            Text { text: item.hint; color: "#94a3b8"; font.pixelSize: 11 }
        }
        MouseArea { id: actionMouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: item.clicked() }
    }

    component StudentNotificationButton: Item {
        id: notice
        property bool allOpen: false
        property bool open: allOpen || bellMouse.containsMouse || panelMouse.containsMouse || allPanelMouse.containsMouse
        z: open ? 120 : 1
        Rectangle {
            id: bell
            anchors.centerIn: parent
            width: 58
            height: 58
            radius: 29
            color: bellMouse.containsMouse || notice.open ? "#f1f5f9" : "transparent"
            Text { anchors.centerIn: parent; text: "🔔"; color: "#111827"; font.pixelSize: 28 }
            Rectangle {
                width: 9
                height: 9
                radius: 5
                color: "#ef4444"
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.top: parent.top
                anchors.topMargin: 9
                border.color: "#ffffff"
                border.width: 2
            }
            Rectangle {
                width: 28
                height: 28
                radius: 14
                color: "#ef4444"
                visible: root.notificationCount() > 0
                anchors.right: parent.right
                anchors.rightMargin: -1
                anchors.top: parent.top
                anchors.topMargin: -1
                Text { anchors.centerIn: parent; text: String(root.notificationCount()); color: "#ffffff"; font.pixelSize: 16; font.bold: true }
            }
            MouseArea {
                id: bellMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
            }
        }

        Rectangle {
            id: noticePanel
            width: Math.min(root.width - 40, 500)
            height: root.narrowShell ? 396 : 424
            x: notice.width - width
            y: notice.height + 8
            radius: 24
            color: "#ffffff"
            border.color: "#e5e7eb"
            visible: notice.open && !notice.allOpen
            opacity: notice.open && !notice.allOpen ? 1 : 0
            scale: notice.open && !notice.allOpen ? 1 : 0.98
            transformOrigin: Item.TopRight
            Behavior on opacity { NumberAnimation { duration: 130 } }
            Behavior on scale { NumberAnimation { duration: 130; easing.type: Easing.OutCubic } }
            MouseArea { id: panelMouse; anchors.fill: parent; hoverEnabled: true }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14
                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "通知"; color: "#111827"; font.pixelSize: 28; font.bold: true; Layout.fillWidth: true }
                    Rectangle {
                        Layout.preferredWidth: 112
                        Layout.preferredHeight: 40
                        radius: 20
                        color: "#fef2f2"
                        Text { anchors.centerIn: parent; text: root.notificationCount() + " 条未读"; color: "#ef4444"; font.pixelSize: 17; font.bold: true }
                    }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Repeater {
                    model: root.studentNotificationRows(false)
                    delegate: RowLayout {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 92
                        spacing: 16
                        Rectangle {
                            Layout.preferredWidth: 54
                            Layout.preferredHeight: 54
                            radius: 27
                            color: Qt.rgba(modelData.color === "#f59e0b" ? 0.96 : (modelData.color === "#22c55e" ? 0.13 : 0.23),
                                           modelData.color === "#f59e0b" ? 0.62 : (modelData.color === "#22c55e" ? 0.77 : 0.51),
                                           modelData.color === "#f59e0b" ? 0.04 : (modelData.color === "#22c55e" ? 0.37 : 0.96),
                                           0.12)
                            Text { anchors.centerIn: parent; text: modelData.icon; color: modelData.color; font.pixelSize: 22; font.bold: true }
                        }
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4
                            Text { Layout.fillWidth: true; text: modelData.title; color: "#111827"; font.pixelSize: 20; font.bold: true; elide: Text.ElideRight }
                            Text { Layout.fillWidth: true; text: modelData.body; color: "#4b5563"; font.pixelSize: 17; elide: Text.ElideRight }
                            Text { Layout.fillWidth: true; text: modelData.time; color: "#a1a1aa"; font.pixelSize: 15; elide: Text.ElideRight }
                        }
                    }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Text {
                    Layout.fillWidth: true
                    text: "查看全部通知"
                    color: "#22c55e"
                    font.pixelSize: 19
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: notice.allOpen = true }
                }
            }
        }

        Rectangle {
            id: allNoticePanel
            width: Math.min(root.width - 48, 600)
            height: Math.min(root.height - 160, 560)
            x: notice.width - width
            y: notice.height + 8
            radius: 24
            color: "#ffffff"
            border.color: "#dbe7f6"
            visible: notice.allOpen
            z: 150
            MouseArea { id: allPanelMouse; anchors.fill: parent; hoverEnabled: true }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 26
                spacing: 14
                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "全部通知"; color: "#0f172a"; font.pixelSize: 30; font.bold: true; Layout.fillWidth: true }
                    Rectangle {
                        Layout.preferredWidth: 112
                        Layout.preferredHeight: 40
                        radius: 20
                        color: "#fef2f2"
                        Text { anchors.centerIn: parent; text: root.notificationCount() + " 条未读"; color: "#ef4444"; font.pixelSize: 17; font.bold: true }
                    }
                    Text {
                        text: "×"
                        color: "#94a3b8"
                        font.pixelSize: 32
                        font.bold: true
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: notice.allOpen = false }
                    }
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#eef2f7" }
                Flickable {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: width
                    contentHeight: allNoticeColumn.height
                    clip: true
                    interactive: contentHeight > height
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }
                    HoverHandler { onHoveredChanged: root.innerScrollActive = hovered }
                    Column {
                        id: allNoticeColumn
                        width: parent.width
                        spacing: 14
                        Repeater {
                            model: root.studentNotificationRows(true)
                            delegate: Rectangle {
                                width: allNoticeColumn.width
                                height: 102
                                radius: 18
                                color: "#f8fbff"
                                border.color: "#e2edf8"
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 18
                                    spacing: 16
                                    Rectangle {
                                        Layout.preferredWidth: 54
                                        Layout.preferredHeight: 54
                                        radius: 27
                                        color: Qt.rgba(modelData.color === "#f59e0b" ? 0.96 : (modelData.color === "#22c55e" ? 0.13 : 0.23),
                                                       modelData.color === "#f59e0b" ? 0.62 : (modelData.color === "#22c55e" ? 0.77 : 0.51),
                                                       modelData.color === "#f59e0b" ? 0.04 : (modelData.color === "#22c55e" ? 0.37 : 0.96),
                                                       0.12)
                                        Text { anchors.centerIn: parent; text: modelData.icon; color: modelData.color; font.pixelSize: 22; font.bold: true }
                                    }
                                    ColumnLayout {
                                        Layout.fillWidth: true
                                        spacing: 5
                                        Text { Layout.fillWidth: true; text: modelData.title; color: "#111827"; font.pixelSize: 20; font.bold: true; elide: Text.ElideRight }
                                        Text { Layout.fillWidth: true; text: modelData.body; color: "#4b5563"; font.pixelSize: 17; elide: Text.ElideRight }
                                        Text { Layout.fillWidth: true; text: modelData.time; color: "#a1a1aa"; font.pixelSize: 15; elide: Text.ElideRight }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    component TopNavButton: Item {
        id: control
        property string text: ""
        property string icon: ""
        property bool selected: false
        signal clicked()
        Layout.preferredWidth: root.narrowShell ? 98 : (root.compactShell ? 148 : 196)
        Layout.preferredHeight: root.narrowShell ? 56 : 78
        Rectangle { anchors.fill: parent; radius: 18; color: mouse.containsMouse ? "#f3f7f5" : "transparent" }
        Row {
            anchors.centerIn: parent
            spacing: root.narrowShell ? 5 : 10
            Text { text: control.icon; color: control.selected ? "#22c55e" : "#6b7280"; font.pixelSize: root.narrowShell ? 22 : 30; font.bold: true; anchors.verticalCenter: parent.verticalCenter }
            Text { width: root.narrowShell ? 60 : implicitWidth; text: control.text; color: control.selected ? "#22c55e" : "#6b7280"; font.pixelSize: root.narrowShell ? 19 : (root.compactShell ? 23 : 26); font.bold: true; anchors.verticalCenter: parent.verticalCenter; elide: Text.ElideRight }
        }
        MouseArea { id: mouse; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor; onClicked: control.clicked() }
    }

    component WindowControls: RowLayout {
        property int buttonSize: root.width < 760 ? 34 : (root.narrowShell ? 40 : 46)
        property int controlGap: root.width < 760 ? 5 : (root.narrowShell ? 5 : 6)
        width: buttonSize * 3 + controlGap * 2
        height: root.width < 760 ? 38 : (root.narrowShell ? 44 : 50)
        z: 20
        spacing: controlGap
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Layout.minimumWidth: width
        Layout.preferredWidth: width
        Layout.preferredHeight: height
        WindowButton { symbol: "-"; onClicked: studentApi.minimizeWindow() }
        WindowButton { symbol: "□"; onClicked: studentApi.toggleMaximizeWindow() }
        WindowButton { symbol: "X"; danger: true; onClicked: studentApi.closeWindow() }
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
            color: control.danger && buttonMouse.containsMouse ? "#ef4444" : (buttonMouse.containsMouse ? "#ecfdf3" : "#ffffff")
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
            color: control.danger && buttonMouse.containsMouse ? "#ffffff" : (control.danger ? "#ef4444" : "#334155")
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
        property string label: "学"
        radius: width / 2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#dbeafe" }
            GradientStop { position: 1.0; color: "#eef2ff" }
        }
        border.color: "#bfdbfe"
        Text { anchors.centerIn: parent; text: parent.label; color: "#2563eb"; font.pixelSize: parent.width * 0.42; font.bold: true }
    }
}
