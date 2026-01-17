#include "radarchartwidget.h"
#include <QPainter>

RadarChartWidget::RadarChartWidget(QWidget *parent) : QWidget{parent}
{
    m_dimensions = {"能力1", "能力2", "能力3", "能力4", "能力5", "能力6"};
    m_maxValues = {100, 100, 100, 100, 100, 100};
    m_values = {80, 60, 90, 70, 50, 85};
    m_centerRadius = 20;
    m_ringCount = 5;

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("background-color: white;");
}

//留作拓展
void RadarChartWidget::setData(const QStringList &dimensions, const QVector<int> &maxValues, const QVector<int> &values)
{
    if (dimensions.size() != maxValues.size() || dimensions.size() != values.size()) return;
    m_dimensions = dimensions;
    m_maxValues = maxValues;
    m_values = values;
    update(); // 重绘
}

/*
 * 介绍: 绘制雷达环线
 * 输入参数: painter - 绘制画笔 center - 雷达中心 maxRadius - 雷达最大半径
 * 返回值:
 */
void RadarChartWidget::drawRings(QPainter &painter, const QPointF &center, qreal maxRadius)
{
    painter.save();
    QPen ringPen(Qt::lightGray, 1, Qt::DashDotLine);
    painter.setPen(ringPen);

    int dimensionCount = m_dimensions.size();
    if (dimensionCount < 3) return;

    qreal ringInterval = maxRadius / m_ringCount; //每环间隔
    for(int ring = 1; ring < m_ringCount; ++ring)
    {
        qreal ringRadius = m_centerRadius + ring * ringInterval;

        QVector<QPointF> ringPoints; // 保存所有正多边形的顶点

        //实现环形与维度轴线向匹配
        for(int i = 0; i < dimensionCount; ++i)
        {
            qreal angle = 2 * M_PI * i / dimensionCount - M_PI / 2;
            QPointF vertex(center.x() + ringRadius * cos(angle), center.y() + ringRadius * sin(angle));
            ringPoints.append(vertex);
        }

        //绘制刻度环
        painter.drawPolygon(ringPoints.data(), ringPoints.size());

        // 最右侧顶点索引
        int Index = 0;
        qreal maxCos = cos(2 * M_PI * 0 / dimensionCount - M_PI / 2);
        for (int i = 1; i < dimensionCount; ++i)
        {
            qreal currentCos = cos(2 * M_PI * i / dimensionCount - M_PI / 2);
            if (currentCos > maxCos) {
                maxCos = currentCos;
                Index = i;
            }
        }
        QPointF rightVertex = ringPoints[Index];
        QString text = QString("%1").arg(ring * 100 / m_ringCount);
        painter.drawText(QRectF(rightVertex.x() + 10, rightVertex.y() - 10, 40, 20), // 文本区域
            Qt::AlignLeft | Qt::AlignVCenter,
            text);
    }
    painter.restore();
}

/*
 * 介绍: 绘制雷达轴线
 * 输入参数: painter - 绘制画笔 center - 雷达中心 maxRadius - 雷达最大半径
 * 返回值:
 */
void RadarChartWidget::drawAxes(QPainter &painter, const QPointF &center, qreal maxRadius)
{
    painter.save();
    QPen axisPen(Qt::gray, 2);
    painter.setPen(axisPen);

    int dimemsionCount = m_dimensions.size();
    //根据角度绘制雷达的轴线
    for(int i = 0; i < dimemsionCount; ++i)
    {
        qreal angle = 2 * M_PI * i / dimemsionCount - M_PI / 2;
        QPointF axisEnd(center.x() + maxRadius * cos(angle), center.y() + maxRadius * sin(angle));
        painter.drawLine(center, axisEnd);
    }
    painter.restore();
}

/*
 * 介绍: 绘制雷达顶点标签
 * 输入参数: painter - 绘制画笔 center - 雷达中心 maxRadius - 雷达最大半径
 * 返回值:
 */
void RadarChartWidget::drawDimensionLabels(QPainter &painter, const QPointF &center, qreal maxRadius)
{
    painter.save();
    QFont labelFont = painter.font();
    labelFont.setBold(true);
    painter.setFont(labelFont);

    int dimensionCount = m_dimensions.size();
    for(int i = 0; i < dimensionCount; ++i)
    {
        qreal angle = 2 * M_PI * i / dimensionCount - M_PI / 2;
        QPointF labelPos(center.x() + (maxRadius + 10) * cos(angle), center.y() + (maxRadius + 10) * sin(angle));

        QRectF textRect(labelPos.x() - 40, labelPos.y() - 10, 80, 20);

        // 根据角度调整对齐方式
        Qt::Alignment align = Qt::AlignCenter;
        if (cos(angle) > 0.1) align = Qt::AlignRight | Qt::AlignVCenter;   // 右侧：左对齐
        else if (cos(angle) < -0.1) align = Qt::AlignLeft | Qt::AlignVCenter; // 左侧：右对齐
        if (sin(angle) > 0.1) align |= Qt::AlignBottom;  // 下方：底部对齐
        else if (sin(angle) < -0.1) align |= Qt::AlignTop; // 上方：顶部对齐

        painter.drawText(textRect, align, m_dimensions[i]);
    }
    painter.restore();
}

/*
 * 介绍: 绘制雷达数值连线图
 * 输入参数: painter - 绘制画笔 center - 雷达中心 maxRadius - 雷达最大半径
 * 返回值:
 */
void RadarChartWidget::drawDataPolygon(QPainter &painter, const QPointF &center, qreal maxRadius)
{
    painter.save();
    int dimensionCount = m_dimensions.size();
    if (dimensionCount < 3) return; // 至少3个维度才构成多边形

    QVector<QPointF> points;// 计算各维度数值对应的像素点
    QVector<int> values;
    for (int i = 0; i < dimensionCount; ++i)
    {
        qreal ratio = qMin((qreal)m_values[i] / m_maxValues[i], 1.0);// 数值归一化
        qreal angle = 2 * M_PI * i / dimensionCount - M_PI / 2;
        // 数值点半径：中心空白 + 比例×有效半径
        qreal pointRadius = m_centerRadius + ratio * (maxRadius - m_centerRadius);
        // 数值点像素坐标
        points.append(QPointF(center.x() + pointRadius * cos(angle),center.y() + pointRadius * sin(angle)));
        values.append(m_values[i]);
    }

    // 绘制多边形边框
    QPen polygonPen(Qt::blue, 2);
    painter.setPen(polygonPen);

    // 绘制多边形填充
    QBrush polygonBrush(QColor(0, 0, 255, 50)); // 蓝色半透明
    painter.setBrush(polygonBrush);
    painter.drawPolygon(points.data(), points.size()); // 连接所有点形成多边形

    // 标记每个数值点（实心圆点）
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    foreach (const QPointF &p, points)
    {
        painter.drawEllipse(p, 5, 5); // 5px半径的红点
    }

    //为每个点添加数值文本
    painter.setPen(QPen(Qt::black));
    painter.setBrush(Qt::NoBrush);
    QFont valueFont = painter.font();
    valueFont.setPointSize(8); // 设置文本大小
    painter.setFont(valueFont);

    for(int i = 0; i < points.size(); ++i)
    {
        const QPointF &p = points[i];
        int value = values[i];
        qreal angle = 2 * M_PI * i / dimensionCount - M_PI / 2;

        //文本偏置
        QPoint textOffset;
        if (cos(angle) >= 0) textOffset.setX(8);  // 右侧点：文本在右边
        else textOffset.setX(-8 - 30);            // 左侧点：文本在左边（预留30px宽度）
        if (sin(angle) >= 0) textOffset.setY(15); // 下方点：文本在下方
        else textOffset.setY(-5);

        //文本区域设置
        QRectF textRect(p.x() + textOffset.x(), p.y() + textOffset.y(), 30, 20);

        //文本对齐
        Qt::Alignment align = (cos(angle) >= 0) ? Qt::AlignLeft : Qt::AlignRight;
        align |= (sin(angle) >= 0) ? Qt::AlignTop : Qt::AlignBottom;

        painter.drawText(textRect, align, QString::number(value));
    }
    painter.restore();
}
