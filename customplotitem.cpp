#include "customplotitem.h"

CustomPlotItem::CustomPlotItem(QQuickItem* parent) : QQuickPaintedItem(parent)
    , m_CustomPlot(nullptr)
{
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize);
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();
    updateCustomPlotSize();
}

void CustomPlotItem::drawGraph(QVector<double> x, QVector<double> y, double xMin, double xMax, double yMin, double yMax)
{
    m_CustomPlot = new QCustomPlot();
    m_CustomPlot->addGraph();
    m_CustomPlot->graph(0)->setPen(QPen(Qt::green));
    m_CustomPlot->graph(0)->setData(x, y);
    m_CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDot));

    m_CustomPlot->xAxis->setLabel("Частота");
    m_CustomPlot->yAxis->setLabel("S11");
    m_CustomPlot->xAxis->setRange(xMin, xMax);
    m_CustomPlot->yAxis->setRange(yMin, yMax);

    m_CustomPlot->setInteractions(QCP::iRangeDrag); // возможность перемещать плоскость мышью
    connect(m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot);
    updateCustomPlotSize();
}

void CustomPlotItem::paint( QPainter* painter)
{
    if (m_CustomPlot)
    {
        QPixmap picture(boundingRect().size().toSize());
        QCPPainter qcpPainter(&picture);

        m_CustomPlot->toPainter(&qcpPainter);

        painter->drawPixmap(QPoint(), picture);
    }
}

void CustomPlotItem::mousePressEvent(QMouseEvent* event)
{
    routeMouseEvents(event);
}

void CustomPlotItem::mouseReleaseEvent(QMouseEvent* event)
{
    routeMouseEvents(event);
}

void CustomPlotItem::mouseMoveEvent(QMouseEvent* event)
{
    routeMouseEvents(event);
}

void CustomPlotItem::routeMouseEvents(QMouseEvent* event)
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent(event->type(), event->localPos(), event->button(),
                                                event->buttons(), event->modifiers());
        QCoreApplication::postEvent(m_CustomPlot, newEvent);
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry(0, 0, width(), height());
    }
}

void CustomPlotItem::onCustomReplot()
{
    update();
}
