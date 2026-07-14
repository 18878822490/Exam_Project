import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#f4f9ff"

    property string pageTitle: typeof homeTitle === "undefined" ? "工作台" : homeTitle
    property string pageDescription: typeof homeDescription === "undefined" ? "欢迎使用智考星考试系统。" : homeDescription

    Rectangle {
        x: -160
        y: -180
        width: 520
        height: 520
        radius: 260
        color: "#8be2dd"
        opacity: 0.24
    }

    Rectangle {
        id: shell
        anchors.fill: parent
        anchors.margins: 28
        radius: 26
        color: "#ffffff"
        border.color: "#dbe7f7"
        clip: true

        RowLayout {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                Layout.preferredWidth: Math.max(260, Math.min(330, root.width * 0.26))
                Layout.fillHeight: true
                color: "#1f5daf"

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#2f7bd6" }
                    GradientStop { position: 1.0; color: "#17427f" }
                }

                Column {
                    anchors.fill: parent
                    anchors.margins: 28
                    spacing: 20

                    Row {
                        spacing: 10
                        Image {
                            width: 42
                            height: 42
                            source: "qrc:/assets/brand-logo-mark.png"
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                            mipmap: true
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "智考星"
                            color: "white"
                            font.pixelSize: 24
                            font.bold: true
                        }
                    }

                    Text {
                        text: pageTitle
                        color: "white"
                        font.pixelSize: 24
                        font.bold: true
                    }

                    Text {
                        width: parent.width
                        text: pageDescription
                        color: "#d7e6ff"
                        wrapMode: Text.WordWrap
                        font.pixelSize: 14
                        lineHeight: 1.35
                    }

                    Repeater {
                        model: ["概览", "考试", "班级", "成绩"]
                        Rectangle {
                            width: parent.width
                            height: 42
                            radius: 12
                            color: index === 0 ? "#44ffffff" : "transparent"
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 14
                                text: modelData
                                color: "white"
                                font.pixelSize: 14
                                font.bold: index === 0
                            }
                        }
                    }

                    Item { height: 1; width: 1 }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#f7fbff"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 34
                    spacing: 22

                    Text {
                        text: pageTitle
                        color: "#172033"
                        font.pixelSize: 30
                        font.bold: true
                    }

                    Text {
                        text: pageDescription
                        color: "#607086"
                        font.pixelSize: 15
                    }

                    GridLayout {
                        Layout.fillWidth: true
                        columns: 3
                        columnSpacing: 16
                        rowSpacing: 16

                        Repeater {
                            model: [
                                ["今日考试", "0", "等待后续业务接入"],
                                ["班级人数", "--", "按角色展示关联数据"],
                                ["平均分", "--", "成绩模块接入后显示"]
                            ]
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 138
                                radius: 16
                                color: "#ffffff"
                                border.color: "#e4edf8"

                                Column {
                                    anchors.fill: parent
                                    anchors.margins: 18
                                    spacing: 8
                                    Text { text: modelData[0]; color: "#607086"; font.pixelSize: 14 }
                                    Text { text: modelData[1]; color: "#1953a8"; font.pixelSize: 32; font.bold: true }
                                    Text { text: modelData[2]; color: "#8a97ab"; font.pixelSize: 12; wrapMode: Text.WordWrap }
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        radius: 18
                        color: "#ffffff"
                        border.color: "#e4edf8"

                        Text {
                            anchors.centerIn: parent
                            text: "这里将继续使用同一套 QML 风格扩展功能页面"
                            color: "#607086"
                            font.pixelSize: 16
                        }
                    }
                }
            }
        }
    }
}
