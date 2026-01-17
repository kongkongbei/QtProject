#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QList>

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

private slots:
    void updataChart();

private:
    Ui::Widget *ui;
    QList<int> tabData;
    QList<int> tempData;

    //图表堆
    QList<QBarSeries*> tabBarChartsInfo;
    QList<QLineSeries*> tabLineChartInfo;
    QList<QPieSeries*> tabPieChartsInfo;

    //初始化表格信息
    void InitScoresTable();

    //创建条状图
    void CreatBarChart(int index);

    //创建饼状图
    void CreatPieChart(int index);

    //设置某行的首行和五个单元格
    void SetTableRow(int nRow, QString strSubject,
                    QString str01, QString str02,
                    QString str03, QString str04, QString str05);

    //表格数据获取函数
    bool ReadTab(QTableWidget *tableWidget, QList<int> *data);

    //获取表格的指定行数据
    bool ReadTabRow(QTableWidget *tableWidget, QList<int> *data, int nRow);

    //将图标输入至窗体上
    void DrawCharts(QChartView *charts, int index);

    //初始化所有图表
    void InitCharts(int index);

    //设置关联
    void setupConnections();

    //更新条状图的数据
    void updateBarSeriesData(QBarSeries *series, QList<int> &newData);

    //更新折线图的数据
    void updateLineSeriesData(QLineSeries *serise, QList<int> &newData);

    //更新饼状图的数据
    void updatePieSeriesData(QPieSeries *serise, QList<int> &newData);
};

#endif // WIDGET_H
