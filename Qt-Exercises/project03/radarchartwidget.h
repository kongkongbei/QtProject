#ifndef RADARCHARTWIDGET_H
#define RADARCHARTWIDGET_H

#include <QWidget>
#include<QPainter>

class RadarChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RadarChartWidget(QWidget *parent = nullptr);
    void setData(const QStringList &dimensions, const QVector<int> &maxValues, const QVector<int> &values);
signals:

private:
    //绘制雷达刻度线
    void drawRings(QPainter &painter, const QPointF &center, qreal maxRadius);

    //绘制维度轴线图
    void drawAxes(QPainter &painter, const QPointF &center, qreal maxRadius);

    //绘制能力文本
    void drawDimensionLabels(QPainter &painter, const QPointF &center, qreal maxRadius);

    //绘制数据多边形
    void drawDataPolygon(QPainter &painter, const QPointF &center, qreal maxRadius);

    QStringList m_dimensions; //维度名称
    QVector<int> m_maxValues; //各维度最大值
    QVector<int> m_values; //各维度实际值
    qreal m_centerRadius; //中心空白区域半径
    int m_ringCount; //刻度环数量

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPointF center(width() / 2.0 , height() / 2.0);
        qreal maxRadius = qMin(width(), height()) / 2.0 - 50;

        drawRings(painter, center, maxRadius);

        drawAxes(painter, center, maxRadius);

        drawDimensionLabels(painter, center, maxRadius);

        drawDataPolygon(painter, center, maxRadius);
    }
};



#endif // RADARCHARTWIDGET_H
