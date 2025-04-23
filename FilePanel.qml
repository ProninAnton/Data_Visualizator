import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

//Объект отображения верхней панели
Item {
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
                id: buttonLoadFile
                text: "Выбрать файл"
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    enableButton()
                    fileDialog.open()
                }
            }
            Text {
                id: dateText
                text: "Дата: "
                anchors.verticalCenter: parent.verticalCenter
                visible: false
            }Text {
                id: timeText
                text: "Время: "
                anchors.verticalCenter: parent.verticalCenter
                visible: false
            }
        }
    }
    FileDialog {
        id: fileDialog
        title: "Выберите файл"
        selectExisting: true
        nameFilters: [ "Файл измерений (*.s1p)", "All files (*)" ]
        selectedNameFilter: "Файл измерений (*.s1p)"
        onAccepted: {
            fpWrapper.openFile(fileUrl)
        }
        onRejected: {
            errorDialog.open()
            enableButton();
        }
    }

    function enableButton() {
        buttonLoadFile.enabled = (buttonLoadFile.enabled == true ? false : true)
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
}

