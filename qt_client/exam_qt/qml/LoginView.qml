import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#f4f9ff"
    clip: true

    property bool registerMode: false
    property bool forgotMode: false
    property bool formAnimating: false
    property bool loginBusy: false
    property bool registerBusy: false
    property string loginStatus: ""
    property string registerStatus: ""
    property string loginError: ""
    property string registerError: ""
    property string pendingRegisterRole: ""
    property int selectedLoginRole: 0
    property bool phoneShell: width < 560
    property bool narrowShell: width < 860
    property bool compactShell: width < 980
    property bool shortShell: height < 900
    property bool wideShell: width >= 1500 && height >= 860
    property bool tallShell: height >= 980
    property real widthScale: Math.max(0.92, Math.min(1.12, width / 1440))
    property real heightScale: Math.max(0.92, Math.min(1.12, height / 900))
    property real adaptiveScale: Math.min(widthScale, heightScale)
    property real brandMotion: 0
    property real uiScale: 1.0
    property int cardMargin: 0
    property int formInset: phoneShell ? 22 : (narrowShell ? 42 : Math.round(70 * adaptiveScale))
    property int controlHeight: phoneShell ? 62 : Math.round(Math.max(62, Math.min(92, (narrowShell ? 74 : 82) * adaptiveScale)))
    property int labelSize: phoneShell ? 16 : Math.round(Math.max(18, Math.min(24, (narrowShell ? 18 : 21) * adaptiveScale)))
    property int bodySize: phoneShell ? 18 : Math.round(Math.max(21, Math.min(29, (narrowShell ? 21 : 25) * adaptiveScale)))
    property int controlFontSize: phoneShell ? 18 : Math.round(Math.max(22, Math.min(29, (narrowShell ? 22 : 25) * adaptiveScale)))
    property int loginTitleSize: phoneShell ? 42 : Math.round(Math.max(52, Math.min(78, (narrowShell ? 54 : 66) * adaptiveScale)))
    property int roleCardHeight: phoneShell ? 110 : Math.round(Math.max(132, Math.min(176, (narrowShell ? 132 : 152) * adaptiveScale)))
    property int roleIconSize: phoneShell ? 48 : Math.round(Math.max(58, Math.min(82, (narrowShell ? 58 : 72) * adaptiveScale)))
    property int roleTextSize: phoneShell ? 15 : Math.round(Math.max(19, Math.min(26, (narrowShell ? 19 : 23) * adaptiveScale)))
    property int roleGap: phoneShell ? 10 : Math.round(Math.max(18, Math.min(24, 20 * adaptiveScale)))
    property color roleBlue: "#4386ff"
    property color roleBlueDeep: "#2f63d8"
    property var classCatalog: []
    property var majors: ["软件工程", "计算机科学与技术", "信息网络", "大数据"]
    property var classesByMajor: ({
        "软件工程": ["软工01", "软工02", "软工03"],
        "计算机科学与技术": ["计科01"],
        "信息网络": ["信网01"],
        "大数据": ["大数据01班"]
    })
    property var subjects: ["高数", "Java", "C++", "数据结构", "数据库", "英语"]
    property var classOptions: [
        "软工01", "软工02", "软工03",
        "计科01",
        "信网01",
        "大数据01班"
    ]
    property var selectedTeacherClasses: []
    property int formIndex: forgotMode ? 2 : (registerMode ? 1 : 0)

    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        NumberAnimation {
            target: root
            property: "brandMotion"
            from: 0
            to: 1
            duration: 16000
            easing.type: Easing.Linear
        }
    }

    Component.onCompleted: {
        var rows = loginWindow.getClassCatalog()
        if (rows && rows.length > 0) {
            setClassCatalog(rows)
        }
    }

    onRegisterModeChanged: {
        formAnimating = true
        formAnimationTimer.restart()
    }

    onForgotModeChanged: {
        formAnimating = true
        formAnimationTimer.restart()
    }

    function studentClassOptions(major) {
        var rows = classesByMajor[major] || []
        return rows.length > 0 ? rows : classOptions
    }

    function classRowName(row) {
        return String(row && row.name !== undefined ? row.name : (row && row["name"] !== undefined ? row["name"] : "")).trim()
    }

    function classRowMajor(row) {
        return String(row && row.major !== undefined ? row.major : (row && row["major"] !== undefined ? row["major"] : "")).trim()
    }

    function setClassCatalog(rows) {
        classCatalog = rows || []
        var nextMajors = []
        var nextByMajor = ({})
        var nextClasses = []
        for (var i = 0; i < classCatalog.length; i++) {
            var className = classRowName(classCatalog[i])
            var majorName = classRowMajor(classCatalog[i])
            if (className.length === 0) {
                continue
            }
            if (nextClasses.indexOf(className) < 0) {
                nextClasses.push(className)
            }
            if (majorName.length > 0) {
                if (nextMajors.indexOf(majorName) < 0) {
                    nextMajors.push(majorName)
                }
                if (!nextByMajor[majorName]) {
                    nextByMajor[majorName] = []
                }
                if (nextByMajor[majorName].indexOf(className) < 0) {
                    nextByMajor[majorName].push(className)
                }
            }
        }
        if (nextClasses.length > 0) {
            classOptions = nextClasses
        }
        if (nextMajors.length > 0) {
            majors = nextMajors
            classesByMajor = nextByMajor
        }
        selectedTeacherClasses = selectedTeacherClasses.filter(function(className) {
            return classOptions.indexOf(className) >= 0
        })
    }

    function toggleTeacherClass(className, checked) {
        var next = selectedTeacherClasses.slice()
        var index = next.indexOf(className)
        if (checked && index < 0) {
            next.push(className)
        } else if (!checked && index >= 0) {
            next.splice(index, 1)
        }
        selectedTeacherClasses = next
    }

    function loginSucceeded() {
        loginBusy = false
        loginError = ""
        loginStatus = "✓ 登录完成"
    }

    function loginFailed(message) {
        loginBusy = false
        loginStatus = ""
        loginError = message
    }

    function registerSucceeded() {
        registerBusy = false
        registerError = ""
        registerStatus = "✓ 注册成功，请使用新账号登录"
        registerReturnTimer.restart()
    }

    function registerFailed(message) {
        registerBusy = false
        registerStatus = ""
        registerError = message
    }

    function setBusy(kind, value) {
        if (kind === "login") {
            loginBusy = value
        } else {
            registerBusy = value
        }
    }

    Timer {
        id: registerReturnTimer
        interval: 1100
        repeat: false
        onTriggered: {
            root.registerMode = false
            root.forgotMode = false
            root.registerStatus = ""
            root.registerError = ""
        }
    }

    Timer {
        id: formAnimationTimer
        interval: 280
        repeat: false
        onTriggered: root.formAnimating = false
    }

    Rectangle {
        x: -width * 0.20
        y: -height * 0.16
        width: root.width * 0.64
        height: root.height * 0.56
        radius: width / 2
        color: "#84e4df"
        opacity: 0.34
    }

    Rectangle {
        x: root.width * 0.62
        y: root.height * 0.58
        width: root.width * 0.52
        height: root.height * 0.52
        radius: width / 2
        color: "#bfd8ff"
        opacity: 0.46
    }

    Rectangle {
        id: shadow
        width: card.width
        height: card.height
        radius: 0
        color: "#1c4b87"
        opacity: 0.10
        visible: false
        scale: root.uiScale
        anchors.centerIn: card
        anchors.verticalCenterOffset: 16
    }

    Rectangle {
        id: card
        anchors.fill: parent
        scale: root.uiScale
        transformOrigin: Item.Center
        radius: 0
        color: "#ffffff"
        border.color: "#dbe7f7"
        border.width: 0
        clip: true

        property real leftWidth: root.compactShell ? 0 : Math.max(520, Math.min(root.wideShell ? 860 : 720, width * (root.wideShell ? 0.44 : 0.42)))
        property real rightWidth: width - leftWidth

        Rectangle {
            id: brandPanel
            visible: !root.compactShell
            width: card.leftWidth
            height: parent.height
            radius: 0
            color: "#0f4c9a"
            clip: true

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0F4C9A" }
                GradientStop { position: 1.0; color: "#3B82F6" }
            }

            Rectangle {
                width: 220
                height: 220
                radius: 110
                x: -84 + Math.sin(root.brandMotion * Math.PI * 2) * 18
                y: 44 + Math.cos(root.brandMotion * Math.PI * 2) * 12
                color: "#46d5ce"
                opacity: 0.32
            }

            Rectangle {
                width: 190
                height: 190
                radius: 95
                x: parent.width - 118 + Math.cos(root.brandMotion * Math.PI * 2) * 12
                y: -54 + Math.sin(root.brandMotion * Math.PI * 2) * 10
                color: "#ffffff"
                opacity: 0.12
            }

            Canvas {
                id: brandMotionLayer
                anchors.fill: parent
                opacity: 0.62
                property real phase: root.brandMotion
                onPhaseChanged: requestPaint()
                onWidthChanged: requestPaint()
                onHeightChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.reset()
                    ctx.clearRect(0, 0, width, height)

                    var t = phase * Math.PI * 2
                    var nodes = [
                        [width * 0.12, height * 0.22],
                        [width * 0.30, height * 0.13],
                        [width * 0.58, height * 0.20],
                        [width * 0.82, height * 0.12],
                        [width * 0.76, height * 0.36],
                        [width * 0.50, height * 0.42],
                        [width * 0.20, height * 0.48],
                        [width * 0.86, height * 0.64],
                        [width * 0.58, height * 0.76],
                        [width * 0.26, height * 0.70]
                    ]

                    ctx.strokeStyle = "rgba(255,255,255,0.13)"
                    ctx.lineWidth = 1
                    ctx.beginPath()
                    for (var i = 0; i < nodes.length - 1; i++) {
                        ctx.moveTo(nodes[i][0], nodes[i][1])
                        ctx.lineTo(nodes[i + 1][0], nodes[i + 1][1])
                    }
                    ctx.moveTo(nodes[1][0], nodes[1][1])
                    ctx.lineTo(nodes[5][0], nodes[5][1])
                    ctx.moveTo(nodes[4][0], nodes[4][1])
                    ctx.lineTo(nodes[8][0], nodes[8][1])
                    ctx.stroke()

                    for (i = 0; i < nodes.length; i++) {
                        var pulse = 0.55 + 0.45 * Math.sin(t + i * 0.72)
                        ctx.fillStyle = "rgba(255,255,255," + (0.22 + pulse * 0.28) + ")"
                        ctx.beginPath()
                        ctx.arc(nodes[i][0], nodes[i][1], 2.2 + pulse * 1.2, 0, Math.PI * 2)
                        ctx.fill()
                    }

                    for (i = 0; i < 5; i++) {
                        var p = (phase + i * 0.18) % 1
                        var x = width * (0.08 + p * 0.84)
                        var y = height * (0.18 + (i % 3) * 0.18) + Math.sin(t + i) * 14
                        var streak = ctx.createLinearGradient(x - 54, y, x + 18, y)
                        streak.addColorStop(0, "rgba(255,255,255,0)")
                        streak.addColorStop(0.72, "rgba(255,255,255,0.18)")
                        streak.addColorStop(1, "rgba(255,255,255,0)")
                        ctx.strokeStyle = streak
                        ctx.lineWidth = 1.2
                        ctx.beginPath()
                        ctx.moveTo(x - 54, y)
                        ctx.lineTo(x + 18, y)
                        ctx.stroke()
                    }
                }
            }

            Column {
                anchors.fill: parent
                anchors.leftMargin: Math.round(Math.max(26, Math.min(36, 28 * root.adaptiveScale)))
                anchors.rightMargin: Math.round(Math.max(30, Math.min(46, 38 * root.adaptiveScale)))
                anchors.topMargin: Math.round(Math.max(24, Math.min(34, 26 * root.adaptiveScale)))
                anchors.bottomMargin: Math.round(Math.max(18, Math.min(28, 22 * root.adaptiveScale)))
                spacing: Math.round(Math.max(8, Math.min(16, (root.shortShell ? 10 : 14) * root.adaptiveScale)))

                Row {
                    id: logoRow
                    spacing: Math.round(Math.max(14, Math.min(18, 15 * root.adaptiveScale)))
                    height: Math.round(Math.max(76, Math.min(92, 78 * root.adaptiveScale)))
                    opacity: 0

                    Component.onCompleted: logoFade.start()

                    NumberAnimation {
                        id: logoFade
                        target: logoRow
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: 760
                        easing.type: Easing.OutCubic
                    }

                    LogoMark {
                        width: Math.round(Math.max(72, Math.min(88, 74 * root.adaptiveScale)))
                        height: width
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 3
                        Text {
                            text: "智考星"
                            color: "white"
                            font.pixelSize: Math.round(Math.max(42, Math.min(54, 44 * root.adaptiveScale)))
                            font.bold: true
                        }
                        Text {
                            text: "智能考试系统"
                            color: "#c9dcff"
                            font.pixelSize: Math.round(Math.max(18, Math.min(23, 19 * root.adaptiveScale)))
                            font.bold: true
                        }
                    }
                }

                Text {
                    width: parent.width
                    text: "让每一次考试\n都更加智能"
                    color: "white"
                    font.pixelSize: Math.round(Math.max(42, Math.min(58, 46 * root.adaptiveScale)))
                    font.bold: true
                    lineHeight: 1.16
                    wrapMode: Text.WordWrap
                }

                Text {
                    width: parent.width
                    text: "题库 · 组卷 · 考试 · 成绩分析\n一站式智能考试管理平台"
                    color: "#d7e6ff"
                    font.pixelSize: Math.round(Math.max(19, Math.min(25, 20 * root.adaptiveScale)))
                    font.bold: true
                    lineHeight: 1.46
                    wrapMode: Text.WordWrap
                }

                TechSphere {
                    width: parent.width
                    height: Math.round(Math.max(root.shortShell ? 168 : 230,
                                               Math.min(root.shortShell ? 230 : 370,
                                                        parent.height - (root.shortShell ? 546 : 618))))
                    phase: root.brandMotion
                }

                Row {
                    width: parent.width
                    height: Math.round(Math.max(92, Math.min(116, (root.shortShell ? 92 : 104) * root.adaptiveScale)))
                    spacing: Math.round(Math.max(10, Math.min(16, 12 * root.adaptiveScale)))

                    FeaturePill {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        height: parent.height
                        title: "智能组卷"
                        text: "自动生成个性化试卷"
                        active: true
                    }

                    FeaturePill {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        height: parent.height
                        title: "在线考试"
                        text: "实时答题与自动提交"
                    }

                    FeaturePill {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        height: parent.height
                        title: "成绩分析"
                        text: "多维度学习数据分析"
                    }
                }

                Row {
                    width: parent.width
                    height: Math.round(Math.max(54, Math.min(70, 58 * root.adaptiveScale)))
                    spacing: Math.round(Math.max(18, Math.min(28, 22 * root.adaptiveScale)))

                    StatBlock {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        value: "128+"
                        label: "考试场次"
                    }

                    StatBlock {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        value: "3260+"
                        label: "题库数量"
                    }

                    StatBlock {
                        width: Math.round((parent.width - parent.spacing * 2) / 3)
                        value: "98%"
                        label: "系统稳定率"
                    }
                }
            }
        }

        Rectangle {
            id: formViewport
            x: brandPanel.width
            width: card.rightWidth
            height: parent.height
            color: "#ffffff"
            clip: true

            Item {
                id: formTrack
                anchors.fill: parent

                LoginForm {
                    anchors.fill: parent
                    visible: root.formIndex === 0
                }

                RegisterForm {
                    anchors.fill: parent
                    visible: root.formIndex === 1
                }

                ForgotPasswordForm {
                    anchors.fill: parent
                    visible: root.formIndex === 2
                }
            }
        }
    }

    Rectangle {
        id: registerNotice
        z: 30
        width: Math.min(420, root.width - 56)
        height: 46
        radius: 16
        color: "#effcf4"
        border.color: "#bdeccf"
        opacity: root.registerStatus.length > 0 ? 1 : 0
        visible: opacity > 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: card.verticalCenter
        anchors.verticalCenterOffset: -8
        Behavior on opacity { NumberAnimation { duration: 180 } }

        Text {
            anchors.centerIn: parent
            text: root.registerStatus
            color: "#107c41"
            font.pixelSize: 14
            font.bold: true
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

    component TechSphere: Canvas {
        id: sphere
        property real phase: 0
        opacity: 0.96
        onPhaseChanged: requestPaint()
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.clearRect(0, 0, width, height)

            var cx = width * 0.52
            var cy = height * 0.52
            var r = Math.min(width, height) * 0.38
            var t = phase * Math.PI * 2

            var glow = ctx.createRadialGradient(cx, cy, r * 0.1, cx, cy, r * 1.42)
            glow.addColorStop(0, "rgba(255,255,255," + (0.34 + 0.06 * Math.sin(t)) + ")")
            glow.addColorStop(0.55, "rgba(147,197,253,0.18)")
            glow.addColorStop(1, "rgba(147,197,253,0)")
            ctx.fillStyle = glow
            ctx.beginPath()
            ctx.arc(cx, cy, r * 1.42, 0, Math.PI * 2)
            ctx.fill()

            ctx.strokeStyle = "rgba(255,255,255,0.50)"
            ctx.lineWidth = 2
            ctx.beginPath()
            ctx.arc(cx, cy, r, 0, Math.PI * 2)
            ctx.stroke()

            ctx.strokeStyle = "rgba(255,255,255,0.34)"
            ctx.lineWidth = 1.5
            ctx.beginPath()
            ctx.ellipse(cx, cy, r * 1.18, r * 0.34, -0.08 + Math.sin(t) * 0.05, 0, Math.PI * 2)
            ctx.stroke()
            ctx.beginPath()
            ctx.ellipse(cx, cy, r * 0.50, r * 0.92, Math.cos(t) * 0.06, 0, Math.PI * 2)
            ctx.stroke()

            for (var dot = 0; dot < 4; dot++) {
                var orbit = t + dot * Math.PI / 2
                var ox = cx + Math.cos(orbit) * r * 1.18
                var oy = cy + Math.sin(orbit) * r * 0.34
                ctx.fillStyle = "rgba(255,255,255,0.72)"
                ctx.beginPath()
                ctx.arc(ox, oy, 3.2, 0, Math.PI * 2)
                ctx.fill()
            }

            var nodes = [
                [cx - r * 1.10, cy - r * 0.10],
                [cx - r * 0.54, cy - r * 0.78],
                [cx + r * 0.42, cy - r * 0.92],
                [cx + r * 1.03, cy - r * 0.24],
                [cx + r * 0.76, cy + r * 0.50],
                [cx - r * 0.20, cy + r * 0.68]
            ]
            ctx.strokeStyle = "rgba(255,255,255,0.20)"
            ctx.lineWidth = 1
            ctx.beginPath()
            for (var i = 0; i < nodes.length; i++) {
                var p = nodes[i]
                var n = nodes[(i + 1) % nodes.length]
                ctx.moveTo(p[0], p[1])
                ctx.lineTo(n[0], n[1])
            }
            ctx.stroke()
            ctx.fillStyle = "rgba(255,255,255,0.48)"
            for (i = 0; i < nodes.length; i++) {
                var nodePulse = 0.75 + 0.25 * Math.sin(t + i * 0.65)
                ctx.beginPath()
                ctx.arc(nodes[i][0], nodes[i][1], 3.4 + nodePulse * 1.4, 0, Math.PI * 2)
                ctx.fill()
            }

            ctx.fillStyle = "rgba(255,255,255,0.88)"
            ctx.beginPath()
            for (i = 0; i < 10; i++) {
                var angle = -Math.PI / 2 + i * Math.PI / 5 + Math.sin(t) * 0.04
                var sr = i % 2 === 0 ? r * 0.20 : r * 0.085
                var sx = cx - r * 0.18 + Math.cos(angle) * sr
                var sy = cy - r * 0.10 + Math.sin(angle) * sr
                if (i === 0) ctx.moveTo(sx, sy)
                else ctx.lineTo(sx, sy)
            }
            ctx.closePath()
            ctx.fill()

            ctx.fillStyle = "rgba(224,242,254,0.82)"
            ctx.beginPath()
            ctx.moveTo(cx + r * 0.05, cy - r * 0.46)
            ctx.lineTo(cx + r * 0.58, cy - r * 0.28)
            ctx.lineTo(cx + r * 0.08, cy - r * 0.08)
            ctx.lineTo(cx - r * 0.45, cy - r * 0.28)
            ctx.closePath()
            ctx.fill()

            ctx.strokeStyle = "rgba(255,255,255,0.72)"
            ctx.lineWidth = 2.4
            var bx = cx - r * 0.44
            var by = cy + r * 0.20
            var bw = r * 0.88
            var bh = r * 0.30
            var br = 12
            ctx.beginPath()
            ctx.moveTo(bx + br, by)
            ctx.lineTo(bx + bw - br, by)
            ctx.quadraticCurveTo(bx + bw, by, bx + bw, by + br)
            ctx.lineTo(bx + bw, by + bh - br)
            ctx.quadraticCurveTo(bx + bw, by + bh, bx + bw - br, by + bh)
            ctx.lineTo(bx + br, by + bh)
            ctx.quadraticCurveTo(bx, by + bh, bx, by + bh - br)
            ctx.lineTo(bx, by + br)
            ctx.quadraticCurveTo(bx, by, bx + br, by)
            ctx.closePath()
            ctx.stroke()
            ctx.beginPath()
            ctx.moveTo(cx, cy + r * 0.20)
            ctx.lineTo(cx, cy + r * 0.50)
            ctx.stroke()
        }
    }

    component FeaturePill: Rectangle {
        id: pill
        property string title: ""
        property string text: ""
        property bool active: false
        property bool hovered: pillMouse.containsMouse
        height: Math.round(Math.max(92, Math.min(116, (root.shortShell ? 92 : 104) * root.adaptiveScale)))
        radius: Math.round(Math.max(18, Math.min(24, 20 * root.adaptiveScale)))
        color: hovered || active ? "#55ffffff" : "#32ffffff"
        border.color: hovered || active ? "#92ffffff" : "#54ffffff"
        scale: hovered ? 1.012 : 1
        transform: Translate { y: pill.hovered ? -4 : 0 }
        Behavior on scale { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
        Behavior on color { ColorAnimation { duration: 150 } }

        Column {
            anchors.fill: parent
            anchors.leftMargin: Math.round(Math.max(14, Math.min(20, 16 * root.adaptiveScale)))
            anchors.rightMargin: Math.round(Math.max(12, Math.min(18, 14 * root.adaptiveScale)))
            anchors.topMargin: Math.round(Math.max(13, Math.min(18, 14 * root.adaptiveScale)))
            anchors.bottomMargin: Math.round(Math.max(13, Math.min(18, 14 * root.adaptiveScale)))
            spacing: Math.round(Math.max(5, Math.min(8, 6 * root.adaptiveScale)))
            Text {
                width: parent.width
                text: title
                color: "white"
                font.pixelSize: Math.round(Math.max(22, Math.min(29, 24 * root.adaptiveScale)))
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                width: parent.width
                text: pill.text
                color: "#d8e7ff"
                font.pixelSize: Math.round(Math.max(15, Math.min(20, 16 * root.adaptiveScale)))
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
        }

        MouseArea {
            id: pillMouse
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
        }
    }

    component StatBlock: Item {
        id: statBlock
        property string value: ""
        property string label: ""
        height: parent ? parent.height : 60

        Column {
            anchors.centerIn: parent
            spacing: 2
            Text {
                width: statBlock.width
                text: statBlock.value
                color: "white"
                font.pixelSize: Math.round(Math.max(24, Math.min(34, 26 * root.adaptiveScale)))
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                width: statBlock.width
                text: statBlock.label
                color: "#cce0ff"
                font.pixelSize: Math.round(Math.max(13, Math.min(17, 14 * root.adaptiveScale)))
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    component AppButton: Item {
        id: control
        property string text: ""
        property bool secondary: false
        property bool hovered: mouse.containsMouse
        property bool pressed: mouse.pressed
        signal clicked()
        opacity: enabled ? 1 : 0.56
        height: root.controlHeight
        implicitHeight: root.controlHeight

        Rectangle {
            anchors.fill: face
            anchors.topMargin: control.pressed ? 8 : 10
            radius: Math.round(Math.max(18, Math.min(22, 18 * root.adaptiveScale)))
            visible: !control.secondary
            color: "#1d4ed8"
            opacity: control.pressed ? 0.30 : (control.hovered ? 0.18 : 0.10)
        }
        Rectangle {
            id: face
            anchors.fill: parent
            radius: Math.round(Math.max(18, Math.min(22, 18 * root.adaptiveScale)))
            color: control.secondary ? "transparent" : "#4386ff"
            gradient: Gradient {
                GradientStop { position: 0.0; color: control.secondary ? "transparent" : "#4386ff" }
                GradientStop { position: 1.0; color: control.secondary ? "transparent" : (control.hovered ? "#6254ee" : "#5657e7") }
            }
            scale: control.pressed ? 0.985 : 1
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        Text {
            anchors.centerIn: parent
            text: control.text
            color: control.secondary ? "#2b63ba" : "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: root.controlFontSize
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
        height: root.controlHeight
        leftPadding: root.phoneShell ? 16 : 24
        rightPadding: root.phoneShell ? 16 : 24
        color: "#172033"
        placeholderTextColor: "#b7bdc8"
            font.pixelSize: root.controlFontSize
        verticalAlignment: TextInput.AlignVCenter
        selectionColor: "#2d66c3"
        selectedTextColor: "white"
        background: Rectangle {
            radius: Math.round(Math.max(20, Math.min(24, 20 * root.adaptiveScale)))
            color: "#ffffff"
            border.width: field.activeFocus ? 2 : 1
            border.color: field.activeFocus ? "#4386ff" : (field.hovered ? "#dce5f4" : "#edf0f6")
        }
    }

    component AppCombo: ComboBox {
        id: combo
        height: root.shortShell ? 50 : (root.narrowShell ? 56 : 62)
        font.pixelSize: root.phoneShell ? 15 : (root.narrowShell ? 17 : 19)
        contentItem: Text {
            text: combo.displayText
            color: "#172033"
            verticalAlignment: Text.AlignVCenter
            leftPadding: 16
            rightPadding: 34
            elide: Text.ElideRight
            font: combo.font
        }
        indicator: Text {
            x: combo.width - width - 14
            y: (combo.height - height) / 2
            text: "⌄"
            color: "#66758a"
            font.pixelSize: 22
        }
        background: Rectangle {
            radius: 11
            color: combo.activeFocus ? "#ffffff" : "#f5f7fb"
            border.width: combo.activeFocus ? 2 : 1
            border.color: combo.activeFocus ? "#2d66c3" : "#edf1f7"
        }
        popup: Popup {
            y: combo.height + 4
            width: combo.width
            implicitHeight: Math.min(contentItem.implicitHeight + 8, 220)
            padding: 4
            background: Rectangle {
                radius: 10
                color: "#ffffff"
                border.color: "#dfe7f2"
            }
            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: combo.popup.visible ? combo.delegateModel : null
                currentIndex: combo.highlightedIndex
            }
        }
    }

    component MessageText: Text {
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        color: "#d13438"
        font.pixelSize: root.labelSize
        wrapMode: Text.WordWrap
    }

    component StatusButton: Button {
        id: statusButton
        height: visible ? (root.shortShell ? 40 : 48) : 0
        visible: text.length > 0
        font.pixelSize: root.phoneShell ? 15 : 17
        font.bold: true
        contentItem: Text {
            text: statusButton.text
            color: "#107c41"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font: statusButton.font
        }
        background: Rectangle {
            radius: 10
            color: statusButton.hovered ? "#defbe9" : "#effcf4"
            border.color: "#c9f2d8"
        }
    }

    component LoginRoleCard: Item {
        id: roleCard
        property int roleIndex: 0
        property string title: ""
        property string iconText: ""
        property bool selected: root.selectedLoginRole === roleIndex
        property bool hovered: roleMouse.containsMouse
        property bool pressed: roleMouse.pressed
        width: parent ? Math.max(root.phoneShell ? 104 : 170, Math.min(root.phoneShell ? 126 : 300, (parent.width - root.roleGap * 2) / 3)) : 270
        height: root.roleCardHeight
        scale: selected ? 1.02 : (hovered ? 1.01 : 1)
        Behavior on scale { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }

        Rectangle {
            anchors.fill: parent
            radius: Math.round(Math.max(18, Math.min(24, 18 * root.adaptiveScale)))
            color: roleCard.selected ? "#eef5ff" : (roleCard.hovered ? "#f8fbff" : "#ffffff")
            border.width: roleCard.selected ? 2 : 1
            border.color: roleCard.selected ? root.roleBlue : (roleCard.hovered ? "#cfe0ff" : "#eceff5")
        }

        Column {
            width: parent.width
            anchors.centerIn: parent
            spacing: Math.round(Math.max(root.shortShell ? 9 : 12, Math.min(16, (root.shortShell ? 9 : 14) * root.adaptiveScale)))
            Rectangle {
                width: root.roleIconSize
                height: root.roleIconSize
                radius: Math.round(Math.max(root.shortShell ? 16 : 22, Math.min(28, (root.shortShell ? 16 : 24) * root.adaptiveScale)))
                anchors.horizontalCenter: parent.horizontalCenter
                color: roleCard.selected ? root.roleBlue : (roleCard.hovered ? "#eaf2ff" : "#f0f1f6")
                Text {
                    anchors.centerIn: parent
                    text: roleCard.iconText
                    color: roleCard.selected ? "#ffffff" : "#9398a4"
                    font.pixelSize: Math.round(Math.max(root.shortShell ? 25 : (root.narrowShell ? 30 : 36), Math.min(40, (root.shortShell ? 25 : (root.narrowShell ? 30 : 36)) * root.adaptiveScale)))
                    font.bold: true
                }
            }
            Text {
                width: parent.width
                text: roleCard.title
                color: roleCard.selected ? root.roleBlueDeep : "#6f7480"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: root.roleTextSize
                font.bold: true
            }
        }

        MouseArea {
            id: roleMouse
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: root.selectedLoginRole = roleCard.roleIndex
        }
    }

    component LoginForm: Item {
        function submitLoginForm() {
            root.loginError = ""
            root.loginStatus = ""
            if (loginUsername.text.trim() === "" || loginPassword.text === "") {
                root.loginError = "请输入用户名和密码"
                return
            }
            loginWindow.submitLogin(loginUsername.text.trim(), loginPassword.text)
        }

        Item {
            id: loginPane
            anchors.fill: parent
            clip: true

            Item {
                id: loginStage
                anchors.fill: parent
                anchors.margins: root.phoneShell ? 18 : Math.round(Math.max(30, Math.min(72, root.formInset)))
                clip: false

                property real desiredWidth: Math.max(root.phoneShell ? Math.min(width, 360) : 520, Math.min(width, root.wideShell ? 1040 : 900))
                property real fitScale: Math.min(1, Math.max(0.78, (height - 8) / Math.max(1, loginColumn.implicitHeight)))

                Column {
                    id: loginColumn
                    width: loginStage.desiredWidth
                    x: (loginStage.width - width * scale) / 2
                    y: Math.max(0, (loginStage.height - implicitHeight * scale) / 2)
                    scale: loginStage.fitScale
                    transformOrigin: Item.TopLeft
                    spacing: Math.round(Math.max(root.shortShell ? 12 : (root.narrowShell ? 15 : 18), Math.min(22, (root.shortShell ? 12 : (root.narrowShell ? 15 : 18)) * root.adaptiveScale)))

                    Text {
                        width: parent.width
                        text: "欢迎登录"
                        color: "#151820"
                        font.pixelSize: root.loginTitleSize
                        font.bold: true
                    }

                    Text {
                        width: parent.width
                        text: "选择您的身份并登录系统"
                        color: "#7b8190"
                        font.pixelSize: root.bodySize
                    }

                    Flow {
                        width: parent.width
                        spacing: root.roleGap
                        LoginRoleCard { roleIndex: 0; title: "教师端"; iconText: "师" }
                        LoginRoleCard { roleIndex: 1; title: "学生端"; iconText: "学" }
                        LoginRoleCard { roleIndex: 2; title: "管理端"; iconText: "管" }
                    }

                    Text {
                        text: "账号"
                        color: "#232834"
                        font.pixelSize: root.labelSize
                        font.bold: true
                    }
                    AppField {
                        id: loginUsername
                        width: parent.width
                        placeholderText: root.selectedLoginRole === 0 ? "输入教师端账号" : (root.selectedLoginRole === 1 ? "输入学生端账号" : "输入管理员账号")
                        onAccepted: submitLoginForm()
                    }

                    Text {
                        text: "密码"
                        color: "#232834"
                        font.pixelSize: root.labelSize
                        font.bold: true
                    }
                    AppField {
                        id: loginPassword
                        width: parent.width
                        placeholderText: "请输入密码"
                        echoMode: TextInput.Password
                        onAccepted: submitLoginForm()
                    }

                    Row {
                        width: parent.width
                        height: Math.round(Math.max(root.shortShell ? 32 : 38, Math.min(44, (root.shortShell ? 32 : 38) * root.adaptiveScale)))
                        spacing: 10
                        CheckBox {
                            id: rememberLogin
                            width: Math.round(Math.max(32, Math.min(38, 32 * root.adaptiveScale)))
                            height: width
                            indicator: Rectangle {
                                width: Math.round(Math.max(26, Math.min(32, 26 * root.adaptiveScale)))
                                height: width
                                radius: 6
                                border.color: rememberLogin.checked ? "#4386ff" : "#9aa0aa"
                                color: rememberLogin.checked ? "#4386ff" : "transparent"
                                Text {
                                    anchors.centerIn: parent
                                    text: rememberLogin.checked ? "✓" : ""
                                    color: "#ffffff"
                                    font.pixelSize: Math.round(Math.max(14, Math.min(18, 14 * root.adaptiveScale)))
                                    font.bold: true
                                }
                            }
                        }
                        Text {
                            text: "记住登录"
                            color: "#707684"
                            font.pixelSize: root.labelSize
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Item { width: 1; height: 1 }
                        Text {
                            id: forgotLink
                            width: Math.max(100, parent.width - 128)
                            text: "忘记密码?"
                            color: "#4386ff"
                            font.pixelSize: root.labelSize
                            horizontalAlignment: Text.AlignRight
                            anchors.verticalCenter: parent.verticalCenter
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    root.loginError = ""
                                    root.loginStatus = ""
                                    root.registerMode = false
                                    root.forgotMode = true
                                }
                            }
                        }
                    }

                    AppButton {
                        width: parent.width
                        text: root.loginBusy ? "登录中..." : "登录"
                        enabled: !root.loginBusy
                        onClicked: submitLoginForm()
                    }

                    AppButton {
                        width: parent.width
                        text: "创建账号"
                        secondary: true
                        onClicked: {
                            root.loginError = ""
                            root.loginStatus = ""
                            root.forgotMode = false
                            root.registerMode = true
                        }
                    }

                    Item { width: 1; height: Math.round(Math.max(root.shortShell ? 2 : 8, Math.min(16, (root.shortShell ? 2 : 8) * root.adaptiveScale))) }

                    MessageText {
                        text: root.loginError
                        visible: root.loginError.length > 0
                    }
                    StatusButton {
                        width: parent.width
                        text: root.loginStatus
                        enabled: false
                    }
                }
            }
        }
    }

    component RegisterForm: Item {
        function roleCode() {
            if (roleCombo.currentIndex === 1) {
                return "TEACHER"
            }
            if (roleCombo.currentIndex === 2) {
                return "ADMIN"
            }
            return "STUDENT"
        }

        function selectedClassName() {
            return classCombo.currentText
        }

        function submitRegisterForm() {
            root.registerError = ""
            root.registerStatus = ""
            root.pendingRegisterRole = roleCode()
            if (registerUsername.text.trim() === "" || registerPassword.text === "") {
                root.registerError = "请输入用户名和密码"
                return
            }
            if (registerName.text.trim() === "") {
                root.registerError = "请输入姓名"
                return
            }
            if (registerPassword.text !== confirmPassword.text) {
                root.registerError = "两次输入的密码不一致"
                return
            }
            if (roleCode() === "STUDENT" && studentNoField.text.trim() === "") {
                root.registerError = "请输入学号"
                return
            }
            if (roleCode() === "STUDENT" && selectedClassName().trim() === "") {
                root.registerError = "请选择数据库中的班级"
                return
            }
            if (roleCode() !== "STUDENT" && phoneField.text.trim() === "") {
                root.registerError = roleCode() === "TEACHER" ? "请输入教师手机号" : "请输入管理员手机号"
                return
            }
            if (roleCode() === "TEACHER" && root.classOptions.length === 0) {
                root.registerError = "班级目录未加载，请确认后端已启动"
                return
            }
            if (roleCode() === "TEACHER" && root.selectedTeacherClasses.length === 0) {
                root.registerError = "请选择至少一个管理班级"
                return
            }

            var payload = {
                "username": registerUsername.text.trim(),
                "password": registerPassword.text,
                "name": registerName.text.trim(),
                "role": roleCode()
            }
            if (roleCode() === "STUDENT") {
                payload.studentNo = studentNoField.text.trim()
                payload.major = majorCombo.currentText
                payload.classNumber = classCombo.currentText
                payload.className = selectedClassName()
            } else if (roleCode() === "TEACHER") {
                payload.classNames = root.selectedTeacherClasses
                payload.subject = subjectCombo.currentText
                payload.phone = phoneField.text.trim()
            } else {
                payload.phone = phoneField.text.trim()
            }
            loginWindow.submitRegister(payload)
        }

        Flickable {
            id: registerFlick
            anchors.fill: parent
            contentWidth: width
            contentHeight: Math.max(height, formColumn.y + formColumn.height + root.formInset)
            clip: true
            interactive: contentHeight > height
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { policy: registerFlick.contentHeight > registerFlick.height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }

            Column {
                id: formColumn
                width: Math.max(360, Math.min(registerFlick.width - root.formInset * 2, 760))
                x: (registerFlick.width - width) / 2
                y: root.shortShell ? 14 : root.formInset
                spacing: root.shortShell ? 8 : (root.narrowShell ? 11 : 14)

                Rectangle {
                    width: parent.width
                    height: root.shortShell ? 78 : (root.narrowShell ? 92 : 112)
                    radius: 24
                    color: "#ffffff"
                    border.color: "#e7eef8"

                    Row {
                        anchors.centerIn: parent
                        spacing: 14
                        LogoMark {
                            width: 52
                            height: 52
                        }
                        Column {
                            spacing: 2
                            Text {
                                text: "智考星"
                                color: "#1953a8"
                                font.pixelSize: root.shortShell ? 28 : 36
                                font.bold: true
                            }
                            Text {
                                text: "创建你的考试系统账号"
                                color: "#718199"
                                font.pixelSize: root.narrowShell ? 15 : 18
                            }
                        }
                    }
                }

                Text { text: "用户名"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                AppField {
                    id: registerUsername
                    width: parent.width
                    placeholderText: "请输入登录用户名"
                }

                Text { text: "姓名"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                AppField {
                    id: registerName
                    width: parent.width
                    placeholderText: "请输入真实姓名"
                }

                Flow {
                    width: parent.width
                    spacing: 14
                    Column {
                        width: parent.width < 430 ? parent.width : (parent.width - 14) / 2
                        spacing: 8
                        Text { text: "密码"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                        AppField {
                            id: registerPassword
                            width: parent.width
                            placeholderText: "密码"
                            echoMode: TextInput.Password
                        }
                    }
                    Column {
                        width: parent.width < 430 ? parent.width : (parent.width - 14) / 2
                        spacing: 8
                        Text { text: "确认密码"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                        AppField {
                            id: confirmPassword
                            width: parent.width
                            placeholderText: "再次输入"
                            echoMode: TextInput.Password
                        }
                    }
                }

                Text { text: "身份"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                AppCombo {
                    id: roleCombo
                    width: parent.width
                    model: ["学生", "教师", "管理员"]
                    onCurrentIndexChanged: {
                        root.registerError = ""
                        root.registerStatus = ""
                    }
                }

                Column {
                    width: parent.width
                    visible: roleCode() !== "STUDENT"
                    height: visible ? implicitHeight : 0
                    spacing: 8

                    Text { text: "手机号"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                    AppField {
                        id: phoneField
                        width: parent.width
                        placeholderText: roleCode() === "TEACHER" ? "请输入教师手机号" : "请输入管理员手机号"
                        inputMethodHints: Qt.ImhDigitsOnly
                    }
                }

                Column {
                    width: parent.width
                    visible: roleCode() === "STUDENT"
                    height: visible ? implicitHeight : 0
                    spacing: 10

                    Text { text: "学号"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                    AppField {
                        id: studentNoField
                        width: parent.width
                        placeholderText: "请输入数据库中的学号"
                    }

                    Flow {
                        width: parent.width
                        spacing: 14
                        Column {
                            width: parent.width < 430 ? parent.width : (parent.width - 14) / 2
                            spacing: 8
                            Text { text: "专业"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                            AppCombo {
                                id: majorCombo
                                width: parent.width
                                model: root.majors
                                onActivated: classCombo.currentIndex = 0
                            }
                        }
                        Column {
                            width: parent.width < 430 ? parent.width : (parent.width - 14) / 2
                            spacing: 8
                            Text { text: "班级"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                            AppCombo {
                                id: classCombo
                                width: parent.width
                                model: root.studentClassOptions(majorCombo.currentText)
                            }
                        }
                    }
                }

                Column {
                    width: parent.width
                    spacing: 9
                    visible: roleCode() === "TEACHER"
                    height: visible ? implicitHeight : 0

                    Text { text: "管理班级"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                    Rectangle {
                        width: parent.width
                        height: root.shortShell ? 98 : 124
                        radius: 11
                        color: "#f5f7fb"
                        border.color: "#edf1f7"
                        clip: true

                        Flickable {
                            anchors.fill: parent
                            anchors.margins: 8
                            contentWidth: width
                            contentHeight: classFlow.implicitHeight
                            clip: true
                            boundsBehavior: Flickable.StopAtBounds
                            ScrollBar.vertical: ScrollBar {
                                policy: ScrollBar.AsNeeded
                            }

                            Flow {
                                id: classFlow
                                width: parent.width
                                height: implicitHeight
                                spacing: 6
                                Repeater {
                                    model: root.classOptions
                                    CheckDelegate {
                                        id: chip
                                        text: modelData
                                        checked: root.selectedTeacherClasses.indexOf(modelData) >= 0
                                        height: 36
                                        onToggled: root.toggleTeacherClass(modelData, checked)
                                        contentItem: Text {
                                            text: chip.text
                                            color: chip.checked ? "#ffffff" : "#24415f"
                                            font.pixelSize: root.narrowShell ? 13 : 15
                                            verticalAlignment: Text.AlignVCenter
                                            leftPadding: 8
                                            rightPadding: 8
                                        }
                                        indicator: null
                                        background: Rectangle {
                                            radius: 8
                                            color: chip.checked ? "#2d66c3" : (chip.hovered ? "#eaf2ff" : "#ffffff")
                                            border.color: chip.checked ? "#2d66c3" : "#dfe7f2"
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Text { text: "所任科目"; color: "#5e6d82"; font.pixelSize: root.labelSize; font.bold: true }
                    AppCombo {
                        id: subjectCombo
                        width: parent.width
                        model: root.subjects
                    }
                }

                AppButton {
                    width: parent.width
                    text: root.registerBusy ? "注册中..." : "注册"
                    enabled: !root.registerBusy
                    onClicked: submitRegisterForm()
                }

                AppButton {
                    width: parent.width
                    text: "返回登录"
                    secondary: true
                    onClicked: {
                        root.registerError = ""
                        root.registerStatus = ""
                        root.forgotMode = false
                        root.registerMode = false
                    }
                }

                MessageText {
                    text: root.registerError
                    visible: root.registerError.length > 0
                }
                StatusButton {
                    width: parent.width
                    text: root.registerStatus
                    onClicked: root.registerMode = false
                }
            }
        }
    }

    component ForgotPasswordForm: Item {
        property string resetStatus: ""
        property string resetError: ""

        Flickable {
            id: forgotFlick
            anchors.fill: parent
            contentWidth: width
            contentHeight: Math.max(height, forgotColumn.y + forgotColumn.height + root.formInset)
            clip: true
            interactive: contentHeight > height
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { policy: forgotFlick.contentHeight > forgotFlick.height ? ScrollBar.AsNeeded : ScrollBar.AlwaysOff }

            Column {
                id: forgotColumn
                width: Math.max(360, Math.min(forgotFlick.width - root.formInset * 2, 760))
                x: (forgotFlick.width - width) / 2
                y: Math.max(root.formInset, (forgotFlick.height - height) / 2)
                spacing: root.shortShell ? 12 : (root.narrowShell ? 16 : 22)

                Text {
                    width: parent.width
                    text: "重置密码"
                    color: "#151820"
                    font.pixelSize: root.shortShell ? 34 : (root.narrowShell ? 42 : 54)
                    font.bold: true
                }
                Text {
                    width: parent.width
                    text: "输入手机号或邮箱，获取验证码后设置新密码"
                    color: "#7b8190"
                    font.pixelSize: root.bodySize
                    wrapMode: Text.WordWrap
                }

                Text { text: "手机号 / 邮箱"; color: "#232834"; font.pixelSize: root.labelSize; font.bold: true }
                AppField {
                    id: resetAccount
                    width: parent.width
                    placeholderText: "请输入手机号或邮箱"
                }

                Flow {
                    width: parent.width
                    spacing: 12
                    AppField {
                        id: verifyCode
                        width: parent.width < 520 ? parent.width : parent.width - 182
                        placeholderText: "验证码"
                    }
                    AppButton {
                        width: parent.width < 520 ? parent.width : 166
                        text: "获取验证码"
                        secondary: true
                        onClicked: {
                            resetError = resetAccount.text.trim().length === 0 ? "请先输入手机号或邮箱" : ""
                            resetStatus = resetError.length === 0 ? "验证码已发送，请注意查收" : ""
                        }
                    }
                }

                Text { text: "新密码"; color: "#232834"; font.pixelSize: root.labelSize; font.bold: true }
                AppField {
                    id: newPassword
                    width: parent.width
                    placeholderText: "请输入新密码"
                    echoMode: TextInput.Password
                }

                AppButton {
                    width: parent.width
                    text: "重置密码"
                    onClicked: {
                        resetStatus = ""
                        resetError = ""
                        if (resetAccount.text.trim().length === 0 || verifyCode.text.trim().length === 0 || newPassword.text.length === 0) {
                            resetError = "请完整填写账号、验证码和新密码"
                            return
                        }
                        resetStatus = "✓ 密码已重置，请返回登录"
                    }
                }

                AppButton {
                    width: parent.width
                    text: "返回登录"
                    secondary: true
                    onClicked: {
                        resetStatus = ""
                        resetError = ""
                        root.forgotMode = false
                        root.registerMode = false
                    }
                }

                MessageText {
                    text: resetError
                    visible: resetError.length > 0
                }
                StatusButton {
                    width: parent.width
                    text: resetStatus
                    onClicked: {
                        root.forgotMode = false
                        root.registerMode = false
                    }
                }
            }
        }
    }
}
