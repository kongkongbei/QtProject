#include "EllipseMotionWidget.h"
#include "qstyle.h"
#include <QPainter>
#include <QTimer>

EllipseMotionWidget::EllipseMotionWidget(QWidget *parent)
    : QWidget{parent}
{
    //初始化坐标系参数
    m_worldXMin = -4000;
    m_worldXMax = 8000;
    m_worldYMin = -3000;
    m_worldYMax = 6000;
    m_margin = 60;

    m_ellipseCenter = QPointF(2000, 600);
    m_ellipseA = 3000;
    m_ellipseB = 1800;
    m_angle = 0;
    m_speed = 0.02; //每帧角度增量

    m_icon.load(":/icon.png");
    if(m_icon.isNull())
    {
        m_icon = QPixmap(30, 30);
        m_icon.fill(Qt::transparent);
        QPainter dot(&m_icon);
        dot.setRenderHint(QPainter::Antialiasing);
        dot.setBrush(Qt::red);
        dot.drawEllipse(m_icon.rect().adjusted(1, 1, -1, -1));
    }

    //设置尺策略
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFont(QFont("Arial", 8));

    m_timer = new QTimer(this);

    //角度更新
    connect(m_timer, &QTimer::timeout, this, [=](){
        m_angle += m_speed;
        if(m_angle >= 2 * M_PI) m_angle= 0;
        update();
    });
    m_timer->start(30);

    //设置背景颜色
    setStyleSheet("background-color: white;");
    // style()->unpolish(this);
    // style()->polish(this);
}

/*
 * 介绍: 绘制运动曲线
 * 输入参数: painter - 绘制画笔
 * 返回值:
 */
void EllipseMotionWidget::drawEllipseTrajectory(QPainter &painter) {
    QPen ellisePen(Qt::blue, 1);
    painter.setPen(ellisePen);

    QPointF lastPixel;
    for (int i = 0; i <= 100; ++i) {
        qreal angle = 2 * M_PI * i / 100;
        QPointF worldPoint(m_ellipseCenter.x() + m_ellipseA * cos(angle),
                           m_ellipseCenter.y() + m_ellipseB * sin(angle));
        // 转换为像素坐标
        QPointF currentPixel = worldToPixel(worldPoint);
        // 绘制线段（连接相邻点）
        if (i > 0) {
            painter.drawLine(lastPixel, currentPixel);
        }
        lastPixel = currentPixel;
    }
}

/*
 * 介绍: 绘制坐标轴
 * 输入参数: painter - 绘制画笔
 * 返回值:
 */
void EllipseMotionWidget::drawCoordinateSystem(QPainter &painter) {
    const qreal tickLength = 5; // 刻度线长度
    const qreal gridStepX = 1200;
    const qreal gridStepY = 1800;

    QPen axisPen(Qt::black, 2); // 坐标轴画笔
    QPen tickPen(Qt::gray, 1);  // 刻度线画笔
    QPen gridPen(Qt::lightGray, 1);
    QBrush textBrush(Qt::black); // 刻度值画笔


    // 绘制坐标像素起点
    QPointF axisOriginPixel(m_margin, height() - m_margin);
    // 坐标轴世界起点
    QPointF axisOriginWorld(m_worldXMin,m_worldYMin);

    // 绘制双轴
    painter.setPen(axisPen);
    QPointF xAxisEndPixel(width() - m_margin, height() - m_margin); // X轴终点（像素）
    painter.drawLine(axisOriginPixel, xAxisEndPixel);
    QPointF yAxisEndPixel(m_margin, m_margin); // Y轴终点（像素）
    painter.drawLine(axisOriginPixel, yAxisEndPixel);

    //绘制网格线
    painter.setPen(gridPen);
    //垂直网格线
    for (int x = m_worldXMin; x <= m_worldXMax; x += gridStepX)
    {
        QPointF gridWorldStart(x, m_worldYMin);   // 网格线起点（世界坐标）
        QPointF gridWorldEnd(x, m_worldYMax);     // 网格线终点（世界坐标）
        QPointF gridPixelStart = worldToPixel(gridWorldStart);
        QPointF gridPixelEnd = worldToPixel(gridWorldEnd);
        painter.drawLine(gridPixelStart, gridPixelEnd);
    }
    //水平网格线
    for (int y = m_worldYMin; y <= m_worldYMax; y += gridStepY)
    {
        QPointF gridWorldStart(m_worldXMin, y);   // 网格线起点（世界坐标）
        QPointF gridWorldEnd(m_worldXMax, y);     // 网格线终点（世界坐标）
        QPointF gridPixelStart = worldToPixel(gridWorldStart);
        QPointF gridPixelEnd = worldToPixel(gridWorldEnd);
        painter.drawLine(gridPixelStart, gridPixelEnd);
    }

    painter.setPen(tickPen);
    painter.setBrush(textBrush);

    //绘制X轴和刻度
    for (int x = m_worldXMin; x <= m_worldXMax; x += gridStepX)
    {
        QPointF tickWorld(x, m_worldYMin);
        QPointF tickPixel = worldToPixel(tickWorld);

        // 绘制刻度线
        painter.drawLine(tickPixel, QPointF(tickPixel.x(), tickPixel.y() - tickLength));

        // 绘制刻度值
        QString text = QString::number(x);
        QRect textRect(tickPixel.x() - 20, tickPixel.y() + 8, 40, 15); // 文本区域(避免重叠)
        painter.drawText(textRect, Qt::AlignCenter, text);
    }
    //绘制Y轴和刻度
    for (int y = m_worldYMin; y <= m_worldYMax; y += gridStepY)
    {
        QPointF tickWorld(m_worldXMin, y); // 刻度世界坐标（Y刻度在X最小值处）
        QPointF tickPixel = worldToPixel(tickWorld);
        // 刻度线（向右延伸，因为Y轴在左侧）
        painter.drawLine(tickPixel, QPointF(tickPixel.x() + tickLength, tickPixel.y()));
        // 刻度值（在Y轴左侧，居中对齐）
        QString text = QString::number(y);
        QRect textRect(tickPixel.x() - 40, tickPixel.y() - 8, 35, 15);
        painter.drawText(textRect, Qt::AlignRight, text);
    }


    //标记坐标轴名称
    painter.drawText((xAxisEndPixel.x()-30) / 2, xAxisEndPixel.y()+50, "X"); // X轴名称
    painter.drawText(yAxisEndPixel.x()-30, yAxisEndPixel.y() / 2, "Y"); // Y轴名称
}

/*
 * 介绍: 绘制运动图标
 * 输入参数: painter - 绘制画笔
 * 返回值:
 */
void EllipseMotionWidget::drawMovingIcon(QPainter &painter) {
    // 计算世界坐标下的当前位置
    QPointF worldPoint(m_ellipseCenter.x() + m_ellipseA * cos(m_angle),
                       m_ellipseCenter.y() + m_ellipseB * sin(m_angle));

    // 转换为像素坐标
    QPointF pixelPoint = worldToPixel(worldPoint);

    // 绘制图标
    if (m_icon.isNull())
        return;
    QSize iconSize(30, 30);
    QPixmap scaledIcon =
        m_icon.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPointF iconTopLeft(pixelPoint.x() - scaledIcon.width() / 2.0,
                        pixelPoint.y() - scaledIcon.height() / 2.0);
    painter.drawPixmap(iconTopLeft, scaledIcon);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);
    painter.drawEllipse(pixelPoint, 3, 3);
}
