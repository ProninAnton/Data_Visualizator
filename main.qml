import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml 2.0
import QtQuick.Dialogs 1.2
import CustomPlotItem 1.0

Window {
    width: 1024
    height: 640
    visible: true
    title: qsTr("Визуализация сигналов")

    Connections {
        target: fpWrapper
        onCalculationReady: {
            customGraph.drawGraph();
            topBar.enableButton();
        }
        onFileError: {
            errorDialog.text = error
            errorDialog.open()
            topBar.enableButton();
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

    CustomPlotItem {
        id:customGraph
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        width: parent.width
        Component.onCompleted: initCustomPlot()

        function drawGraph() {
            fpWrapper.drawGraph(CustomPlotItem)
        }
    }

    MessageDialog {
        id: errorDialog
        modality: Qt.WindowModal
        icon: StandardIcon.Information
        title: "Ошибка!"
        text: "Вы не выбрали файл!"
    }
}


