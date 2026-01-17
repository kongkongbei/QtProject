#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTableWidgetSelectionRange>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QtCharts>
#include <QLineSeries>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableWidget->clear();
    InitScoresTable();

    ReadTab(ui->tableWidget, &tabData);
    InitCharts(ui->tabWidget->count());
    setupConnections();

}

Widget::~Widget()
{
    delete ui;
}

/*
 * 介绍: 初始化统计表
 * 输入参数:
 * 返回值:
 */
void Widget::InitScoresTable()
{
    //设置表格大小
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(5);

    //添加字符串到表头信息
    QStringList listHeader;
    listHeader << tr("0-59") << tr("60-69") << tr("70-79") << tr("80-89") << tr("90-100");
    ui->tableWidget->setHorizontalHeaderLabels(listHeader);

    //设置表头高度
    ui->tableWidget->horizontalHeader()->setFixedHeight(30);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40); //设置行高

    //添加基本信息至表格
    SetTableRow(0, tr("语文"), tr("50"), tr("25"), tr("25"), tr("25"), tr("25"));
    SetTableRow(1, tr("数学"), tr("25"), tr("50"), tr("25"), tr("25"), tr("25"));
    SetTableRow(2, tr("英语"), tr("25"), tr("25"), tr("50"), tr("25"), tr("25"));

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems); //使能表格单选功能

    //表格宽度自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setFrameShape(QFrame::NoFrame);
}

/*
 * 介绍: 创建条状&折线图，并在index的标签页添加上图表
 * 输入参数: index-需要添加的标签页索引
 * 返回值:
 */
void Widget::CreatBarChart(int index)
{    
    //创建数据集并添加数据
    QBarSet *barSet = new QBarSet("柱状图");

    //将对应的科目的数据读取进来
    for(int i = 0; i < 5; i++)
    {
        *barSet << tabData.at(index*5 + i);
        // qDebug() << (index*5 + i);
    }

    //创建折线图并加入数据
    QLineSeries *lineSeries = new QLineSeries();
    for(int i = 0; i < 5; i++)
    {
        lineSeries->append(i, tabData.at(index*5 + i));
    }

    //创建柱状图并加入数据
    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);

    //创建图表并添加系列
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->addSeries(lineSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();

    //创建坐标x轴并关联相关数据
    QStringList categories = {"0-59", "60-69", "70-79", "80-89", "90-100"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisX);

    //创建坐标y轴并关联相关数据
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,100);
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
    lineSeries->attachAxis(axisY);

    //将图表信息压入栈中
    tabBarChartsInfo.append(barSeries);
    tabLineChartInfo.append(lineSeries);

    //将图表放入视图中
    QChartView *chartView = new QChartView(chart);
    DrawCharts(chartView, index);
}

/*
 * 介绍: 创建饼状图，并在index的标签页添加上图表
 * 输入参数: index-需要添加的标签页索引
 * 返回值:
 */
void Widget::CreatPieChart(int index)
{
    int colorIndex = 0;
    QList<QColor> colors = {QColor("#FF6B6B"), QColor("#4ECDC4"),
                            QColor("#45B7D1"), QColor("#FFA07A"), QColor("#98D8C8")};

    //设置饼状态图表信息
    QPieSeries *series = new QPieSeries();
    series->append("0-59", tabData.at(index*5 + 0));
    series->append("60-69", tabData.at(index*5 + 1));
    series->append("70-79", tabData.at(index*5 + 2));
    series->append("80-89", tabData.at(index*5 + 3));
    series->append("80-89", tabData.at(index*5 + 4));

    for (QPieSlice *slice : series->slices())
    {
        // 设置切片颜色
        slice->setBrush(colors[colorIndex % colors.size()]);

        // 设置边框
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);

        colorIndex++;
    }

    //将饼状图压入栈中
    tabPieChartsInfo.append(series);

    //将图放入chart中
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    DrawCharts(chartView, index);
}

/*
 * 介绍: 将图表绘制在标签页上
 * 输入参数: charts-需要绘制的图表 index-选定的标签页面
 * 返回值:
 */
void Widget::DrawCharts(QChartView *charts, int index)
{
    //设置图表动画类型
    charts->setRenderHint(QPainter::Antialiasing);

    //横向布局
    QHBoxLayout *layout;

    //根据页码将图像加入对应标签页中
    switch(index)
    {
        case 0:
            layout = ui->horizontalLayout;
            layout->addWidget(charts);
            break;
        case 1:
            layout = ui->horizontalLayout_2;
            layout->addWidget(charts);
            break;
        case 2:
            layout = ui->horizontalLayout_3;
            layout->addWidget(charts);
            break;
    }
}

/*
 * 介绍: 初始化标签页图表
 * 输入参数: index-标签页页数
 * 返回值:
 */
void Widget::InitCharts(int index)
{
    for (int i = 0; i < index; i++)
    {
        CreatBarChart(i);
        CreatPieChart(i);
    }
    // qDebug() << tabChartsInfo;
}

/*
 * 介绍: 初始化信号槽连接
 * 输入参数:
 * 返回值:
 */
void Widget::setupConnections()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::updataChart);
}

/*
 * 介绍: 更新条状图中的数据
 * 输入参数: series-指定的数据图表 newData-新数据
 * 返回值:
 */
void Widget::updateBarSeriesData(QBarSeries *series, QList<int> &newData)
{
    QBarSet *barSet = series->barSets().at(0);
    for(int i = 0; i < 5 ; i++)
    {
        // qDebug() << barSet;
        barSet->replace(i, newData.at(i));
    }
}

/*
 * 介绍: 更新折线图中的数据
 * 输入参数: serise-指定的数据图表, newData-新数据
 * 返回值:
 */
void Widget::updateLineSeriesData(QLineSeries *serise, QList<int> &newData)
{
    //创建临时容器保存数据
    QVector<QPointF> tempData;
    for(int i = 0; i < 5 ; i++)
    {
        tempData << QPointF(i, newData.at(i));
    }
    // qDebug() << tempData;
    serise->replace(tempData);
}

void Widget::updatePieSeriesData(QPieSeries *serise, QList<int> &newData)
{
    QPieSlice *Slice;

    //每次删除头切片，删除5次
    for(int i = 0; i < 5 ; i++)
    {
        Slice = serise->slices().at(0);
        serise->remove(Slice);
    }

    //重新添加新数据
    serise->append("0-59", newData.at(0));
    serise->append("60-69", newData.at(1));
    serise->append("70-79", newData.at(2));
    serise->append("80-89", newData.at(3));
    serise->append("90-100", newData.at(4));
}

/*
 * 介绍: 将信息插入Tab表格中
 * 输入参数: nRow-表格行号 strSubject-竖表头信息 str0x-数据信息
 * 返回值:
 */
void Widget::SetTableRow(int nRow, QString strSubject, QString str01, QString str02, QString str03, QString str04, QString str05)
{
    //行首名字
    QTableWidgetItem *itemSubject = new QTableWidgetItem(strSubject);
    ui->tableWidget->setVerticalHeaderItem(nRow, itemSubject);

    //分数单元格设置
    QTableWidgetItem *itemstr01 = new QTableWidgetItem(str01);
    ui->tableWidget->setItem(nRow, 0, itemstr01);

    QTableWidgetItem *itemstr02 = new QTableWidgetItem(str02);
    ui->tableWidget->setItem(nRow, 1, itemstr02);

    QTableWidgetItem *itemstr03 = new QTableWidgetItem(str03);
    ui->tableWidget->setItem(nRow, 2, itemstr03);

    QTableWidgetItem *itemstr04 = new QTableWidgetItem(str04);
    ui->tableWidget->setItem(nRow, 3, itemstr04);

    QTableWidgetItem *itemstr05 = new QTableWidgetItem(str05);
    ui->tableWidget->setItem(nRow, 4, itemstr05);
}

/*
 * 介绍: 将指定的表格数据读出，并将其存储在指定容器中
 * 输入参数: tableWidget-所选表格 data-所选容器
 * 返回值: 1-函数运行完毕直接返回
 */
bool Widget::ReadTab(QTableWidget *tableWidget, QList<int> *data)
{
    //获取表格的行数列数
    int rowCount = tableWidget->rowCount();
    int columnCount = tableWidget->columnCount();

    //遍历整个表格，并将数据存入tabdata容器内
    for(int nRow = 0; nRow < rowCount; nRow++)
    {
        for(int nCol = 0; nCol < columnCount; nCol++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(nRow, nCol);
            if(item != nullptr)
            {
                bool flag;
                int value = item->text().toInt(&flag, 10);
                if(flag)
                {
                    data->append(value);
                }
                else
                {
                    qDebug() << "R" << nRow << "C" << nCol << ":内容不是整型";
                }
            }
            else
            {
                qDebug() << "R" << nRow << "C" << nCol << ":单元格为空";
            }

        }
    }
    return 1;
}

/*
 * 介绍: 将指定的表格数据读出，并将其存储在指定容器中
 * 输入参数: tableWidget-所选表格 data-所选容器 nRow-所选行
 * 返回值: 1-函数运行完毕直接返回
 */
bool Widget::ReadTabRow(QTableWidget *tableWidget, QList<int> *data, int nRow)
{
    //获取表格的列数
    int columnCount = tableWidget->columnCount();

    //遍历整个表格，并将数据存入tabdata容器内
    for(int nCol = 0; nCol < columnCount; nCol++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(nRow, nCol);
        if(item != nullptr)
        {
            bool flag;
            int value = item->text().toInt(&flag, 10);
            if(flag)
            {
                data->append(value);
            }
            else
            {
                qDebug() << "R" << nRow << "C" << nCol << ":内容不是整型";
            }
        }
        else
        {
            qDebug() << "R" << nRow << "C" << nCol << ":单元格为空";
        }

    }
    return 1;
}

/*
 * 介绍: 根据表格信息更新数据
 * 输入参数:
 * 返回值:
 */
void Widget::updataChart()
{
    tabData.clear();
    tempData.clear();

    ReadTab(ui->tableWidget, &tabData);
    ReadTabRow(ui->tableWidget, &tempData, ui->tabWidget->currentIndex());

    QLineSeries *tempLine = nullptr;
    tempLine = tabLineChartInfo.at(ui->tabWidget->currentIndex());
    updateLineSeriesData(tempLine, tempData);

    QBarSeries *tempBar = nullptr;
    tempBar = tabBarChartsInfo.at(ui->tabWidget->currentIndex());
    updateBarSeriesData(tempBar, tempData);

    QPieSeries *tempPie = nullptr;
    tempPie = tabPieChartsInfo.at(ui->tabWidget->currentIndex());
    updatePieSeriesData(tempPie, tempData);

    ui->tabWidget->currentWidget()->update();
}
