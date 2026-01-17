#ifndef CIRCLEPROGRESS_H
#define CIRCLEPROGRESS_H

#include <QWidget>
#include <QPainter>
class CircleProgress : public QWidget
{
    Q_OBJECT
public:
    explicit CircleProgress(QWidget *parent = nullptr): QWidget(parent),m_progress(0)
    {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }

    void setProgress(int progoress) {m_progress = qBound(0, progoress, 100); update();}

    QSize sizeHint() const override
    {
        // 获取文本字体
        QFont textFont = font();
        textFont.setPointSize(20);
        textFont.setBold(true);
        QFontMetrics fm(textFont);

        // 计算最长文本（"100%"）的宽高（确保所有百分比都能容纳）
        QString maxText = "100%";
        int textWidth = fm.horizontalAdvance(maxText); // 文本宽度
        int textHeight = fm.height();                  // 文本高度（含行间距）

        // 进度图大小 = 文本最大尺寸 + 2*边距（边距=文本高度的1/2，确保圆环包裹文本）
        int margin = textHeight / 2;
        int width = qMax(textWidth, textHeight) + 2 * margin;
        return QSize(width, width); // 正方形
    }

signals:
private:
    int m_progress; //进度值

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 计算文本尺寸
        QFont textFont = font();
        textFont.setPointSize(20);
        textFont.setBold(true);
        painter.setFont(textFont);
        QFontMetrics fm(textFont);
        QString text = QString("%1%").arg(m_progress);
        int textWidth = fm.horizontalAdvance(text);
        int textHeight = fm.height();

        // 绘制区域和中心
        QPointF center(width() / 2.0, height() / 2.0);
        int maxTextDim = qMax(textWidth, textHeight);
        qreal radius = (maxTextDim / 2.0) + 100;
        qreal penWidth = textHeight / 4.0;
        penWidth = qMax(penWidth, 5.0); // 最小5px，避免过细

        //绘制背景圆环
        painter.save();
        QPen bgPen(Qt::lightGray, penWidth);
        bgPen.setCapStyle(Qt::RoundCap);
        painter.setPen(bgPen);
        painter.drawArc(center.x() - radius, center.y() - radius, radius*2, radius*2, -90*16, 360*16);
        painter.restore();

        //绘制进度圆环
        painter.save();
        QPen progressPen(QColor(50, 150, 255), penWidth);
        progressPen.setCapStyle(Qt::RoundCap);
        painter.setPen(progressPen);
        int spanAngle = m_progress * 360 * 16 / 100;
        painter.drawArc(center.x() - radius, center.y() - radius, radius*2, radius*2, -90*16, spanAngle);
        painter.restore();

        // 绘制中心进度文本
        painter.save();

        textFont.setPointSize(20);
        textFont.setBold(true);
        painter.setFont(textFont);
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, text);
        painter.restore();
    }
};

#endif // CIRCLEPROGRESS_H
