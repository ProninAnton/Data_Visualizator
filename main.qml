import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml 2.0
import QtQuick.Dialogs 1.2

Window {
    id:mainWind
    width: 640
    height: 480
    visible: true
    title: qsTr("Визуализация записей сигналов")

    Connections {
        target: fileProcessing
        onCalculationReady: {
            dataGraph.drawGraph(typeName);
        }
        onFileError: {
            errorDialog.text = error
            errorDialog.open()
        }
        onShowDateTime: {
            topBar.setDate(fileDate);
            topBar.setTime(fileTime);
        }
    }

    FilePanel {
        id: topBar
        anchors.top: parent.top
        anchors.topMargin: 20
        height: 30
    }

    DataGraph {
        id: dataGraph
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        width: parent.width
    }

    MessageDialog {
        id: errorDialog
        modality: Qt.WindowModal
        icon: StandardIcon.Information
        title: "Ошибка!"
        text: "Вы не выбрали файл!"
    }
}
