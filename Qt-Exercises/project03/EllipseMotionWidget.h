#ifndef ELLIPSEMOTIONWIDGET_H
#define ELLIPSEMOTIONWIDGET_H

#include "qpainter.h"
#include <QWidget>
#include <cmath>

class EllipseMotionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EllipseMotionWidget(QWidget *parent = nullptr);
    //运动图标设置
    void setIcon(const QString &iconPath){m_icon.load(iconPath);update();}

protected:

//将虚拟距离转换为现实距离
QPointF worldToPixel(const QPointF &worldPoint) const
{
    qreal usablePixelWidth = width() - 2 * m_margin;
    qreal usablePixelHeight = height() - 2 * m_margin;

    //X、Y轴映射
    qreal pixelX = m_margin + (worldPoint.x() - m_worldXMin) / (m_worldXMax - m_worldXMin) * usablePixelWidth;
    qreal pixelY = m_margin + (m_worldYMax - worldPoint.y()) / (m_worldYMax - m_worldYMin) * usablePixelHeight;

    return QPointF(pixelX, pixelY);
}

void drawCoordinateSystem(QPainter &painter);

void drawEllipseTrajectory(QPainter &painter);

void drawMovingIcon(QPainter &painter);

private:
    QPointF m_ellipseCenter;
    qreal m_ellipseA;
    qreal m_ellipseB;
    qreal m_angle; //当前角度
    qreal m_speed; //运动速度
    QTimer *m_timer;
    QPixmap m_icon;

    qreal m_worldXMin,m_worldXMax;
    qreal m_worldYMin,m_worldYMax;
    qreal m_margin;//控件页边距
signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        drawEllipseTrajectory(painter);

        drawCoordinateSystem(painter);

        drawMovingIcon(painter);
    };
};

#endif // ELLIPSEMOTIONWIDGET_H
