#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHash>
#include <QCompleter>
#include <QPixmap>
#include <QMessageBox>
#include"memberinfo.h"

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

    //初始化界面
    void InitMemberInfoList();

    //初始化Hash
    void InitHash();

    //读取列表信息并显示
    bool ReadList();

    //添加成员信息
    void addMemberInfo();

    //删除成员信息
    void deleteMemberInfo();

    //选择成员头像
    void selectHeadshot();

    //计算哈希表中的成员个数
    void hashCount();

    //设置关联
    void SetupConnections();

    //保存信息
    void SaveMemberInfo();

    //导出信息
    void OutputMemberInfo();

    //pdf描框并写入文字 - 图上距离1cm = 数值单位500
    void pdfDrawAndWrite(qreal posX, qreal posY, qreal rectX, qreal rectY, QString Info, QPainter *painter, bool mode);

    //单位转化:毫米转点
    qreal mmToPoints(qreal mm) {return mm * 72.0 / 25.4;}

    //单位转化:厘米转点
    qreal cmToPoints(qreal cm) {return mmToPoints(cm * 10);}

private slots:

private:
    Ui::Widget *ui;
    QHash<QString, MemberInfo> memberHash;
    int m_hashCount;
};
#endif // WIDGET_H
