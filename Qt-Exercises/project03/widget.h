#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSlider>
#include "circleprogress.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //绘制堆叠条形图
    void DrawStackedBar();

private:
    Ui::Widget *ui;

    //滑块封装
    QSlider* createSlider()
    {
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setRange(0, 100);
        slider->setValue(0);
        slider->setTickInterval(10); // 刻度间隔
        // slider->setTickPosition(QSlider::TicksBelow); // 刻度在下方
        return slider;
    }

    CircleProgress *m_progressWidget; //窗口
    QSlider *m_sliders[3]; //自定义滑块存储空间
    QLabel *m_sliderLabels[3]; //滑块数值存储空间
    QLabel* m_textLabels[3]; // 文本标签

private slots:
    void onSliderChanged()
    {
        // 获取三个滑块的值
        int v1 = m_sliders[0]->value();
        int v2 = m_sliders[1]->value();
        int v3 = m_sliders[2]->value();

        // 更新滑块值标签
        m_sliderLabels[0]->setText(QString::number(v1));
        m_sliderLabels[1]->setText(QString::number(v2));
        m_sliderLabels[2]->setText(QString::number(v3));

        // 计算平均值（四舍五入）
        int avg = qRound((v1 + v2 + v3) / 3.0);

        // 更新进度图
        m_progressWidget->setProgress(avg);
    }
};
#endif // WIDGET_H
