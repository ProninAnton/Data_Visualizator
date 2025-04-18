import QtQuick 2.0
import QtCharts 2.1

//Объект отрисовки графика
ChartView {
    id: chartView
    property bool openGL: true

    ValueAxis {
        id: axisX
        tickCount: 6
        labelFormat: "%g"
    }

    ValueAxis {
        id: axisY
        tickCount: 10
        labelFormat: "%g"
    }

    function drawGraph(typeName) {
        chartView.removeAllSeries();
        zastavka.visible = false

        var series = chartView.createSeries(ChartView.SeriesTypeLine, typeName,
                                             axisX, axisY);
        series.useOpenGL = chartView.openGL;

        fileProcessing.drawGraph(chartView.series(0), axisX, axisY);
        chartView.zoom(0.95);
    }
    Text {
        id: zastavka
        text: qsTr("Загрузите файл, чтобы построить график!")
        textFormat: {
            minimumPointSize = 24
            color = "blue"
        }
        anchors.centerIn: parent
    }
}
