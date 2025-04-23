#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H

#include <QtQuick>
#include "qcustomplot/qcustomplot.h"

class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem(QQuickItem* parent = 0);
    virtual ~CustomPlotItem();

    void paint(QPainter* painter);

    Q_INVOKABLE void initCustomPlot();
    void drawGraph(QVector<double> x, QVector<double> y,
                   double xMin, double xMax, double yMin, double yMax);

protected:
    void routeMouseEvents(QMouseEvent* event);

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private slots:
    void onCustomReplot();
    void updateCustomPlotSize();

private:
    QCustomPlot* m_CustomPlot;
};

#endif // CUSTOMPLOTITEM_H
