import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

//Объект отображения верхней панели
Item {
    property string date: ""
    property string time: ""
    Rectangle {
        id: topBar
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: topRow.height
        Row {
            id: topRow
            spacing: 6
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            width: parent.width

            Button {
                text: "Выбрать файл"
                anchors.verticalCenter: parent.verticalCenter
                onClicked: fileProcessing.openFile()
            }

            Text {
                id: dateText
                text: "Дата: " + date
                anchors.verticalCenter: parent.verticalCenter
                visible: false
            }Text {
                id: timeText
                text: "Время: " + time
                anchors.verticalCenter: parent.verticalCenter
                visible: false
            }
        }
    }

    function setDate(date) {
        if (date === "") {
            dateText.visible = false
        }
        else {
            dateText.visible = true
            dateText.text = "Дата: " + date
        }
    }

    function setTime(time) {
        if (time === "") {
            timeText.visible = false
        }
        else {
            timeText.visible = true
            timeText.text = "Время: " + time
        }
    }

    MessageDialog {
        id: warningDialog
        modality: Qt.WindowModal
        icon: StandardIcon.Information
        title: "Предупреждение!"
        text: "Вы не выбрали файл!"
    }
}

