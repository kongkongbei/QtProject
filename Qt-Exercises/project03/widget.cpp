#include "widget.h"
#include "ui_widget.h"
#include <QtCharts>
#include "circleprogress.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    DrawStackedBar();

    m_progressWidget = new CircleProgress();

    //初始化滑块
    m_sliders[0] = createSlider();
    m_sliders[1] = createSlider();
    m_sliders[2] = createSlider();

    //滑块文本标签
    m_textLabels[0] = new QLabel("理论学习");
    m_textLabels[1] = new QLabel("模拟训练");
    m_textLabels[2] = new QLabel("实际训练");

    // 数值标签（显示滑块当前值，初始为0）
    for (int i = 0; i < 3; ++i)
    {
        m_sliderLabels[i] = new QLabel("0%");
        m_sliderLabels[i]->setFixedWidth(30); // 固定宽度，避免抖动
        m_sliderLabels[i]->setAlignment(Qt::AlignRight); // 数值右对齐，更美观
    }

    // 布局管理
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(30);

    //上半部分占比60%
    ui->verticalLayout_5->addWidget(m_progressWidget, 6);

    QWidget *sliderContainer = new QWidget();
    QVBoxLayout *sliderLayout = new QVBoxLayout(sliderContainer);
    sliderLayout->setSpacing(20); // 滑块之间的间距

    for (int i = 0; i < 3; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        hLayout->setSpacing(10); // 组件之间的间距

        // 添加组件：数值标签（左）→ 文本标签（中）→ 滑块（右）
        hLayout->addWidget(m_sliderLabels[i]);    // 数值在左
        hLayout->addWidget(m_textLabels[i]);      // 文本在中
        hLayout->addWidget(m_sliders[i]);         // 滑块在右（占剩余空间）
        hLayout->setStretch(2, 1); // 滑块占更多空间，避免被挤压

        sliderLayout->addLayout(hLayout);
    }

    ui->verticalLayout_5->addWidget(sliderContainer, 4);
    ui->verticalLayout_5->setContentsMargins(20, 20, 20, 20);

    connect(m_sliders[0], &QSlider::valueChanged, this, &Widget::onSliderChanged);
    connect(m_sliders[1], &QSlider::valueChanged, this, &Widget::onSliderChanged);
    connect(m_sliders[2], &QSlider::valueChanged, this, &Widget::onSliderChanged);

    onSliderChanged();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DrawStackedBar()
{
    //创建各个数据集
    QBarSet *barTheory = new QBarSet("理论学习");
    QBarSet *barSimul = new QBarSet("模拟训练");
    QBarSet *barTrain = new QBarSet("实际训练");

    *barTheory << 1 << 0 << 1 << 2 << 1 << 2 << 1;
    *barSimul << 3 << 1 << 1 << 4 << 0 << 1 << 2;
    *barTrain << 5 << 4 << 3 << 6 << 5 << 2 << 1;

    //数据集压栈
    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(barTheory);
    series->append(barSimul);
    series->append(barTrain);

    //图表建立
    QChart *chart = new QChart();
    chart->addSeries(series);
    // chart->setTitle("每日学习时长");
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    //设置X轴
    QStringList categories = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    //设置Y轴
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 24);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //打开图例
    chart->legend()->setVisible(true);

    //创建图表视图并显示
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = ui->verticalLayout;
    layout->addWidget(chartView);

}
