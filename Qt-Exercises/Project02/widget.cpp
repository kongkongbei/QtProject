#include "widget.h"
#include "ui_widget.h"
#include "memberinfo.h"
#include <QFileDialog>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QImage>
#include <QPageSize>
#include <QFile>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QtPrintSupport>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->dateEdit->setDisplayFormat("yyyy/MM/dd");

    InitHash();
    InitMemberInfoList();
    SetupConnections();

}

Widget::~Widget()
{
    delete ui;
}

/*
 * 介绍: 将哈希表中的键输入进列表中 - 可以再升级一版
 * 输入参数:
 * 返回值:
 */
void Widget::InitMemberInfoList()
{
    //获取所有的键
    QStringList names = memberHash.keys();

    QListWidgetItem *pListItem = new QListWidgetItem(names.first());
    pListItem->setSizeHint(QSize(0,60));

    //将信息插入ListWidget中
    ui->listWidget->addItem(pListItem);
}

/*
 * 介绍: 初始化哈希表
 * 输入参数:
 * 返回值:
 */
void Widget::InitHash()
{
    MemberInfo mem("张三", 0, "湖南省", "2003/08/31",
                   "", 2, "郴州市", "翻斗花园\n米德维奇小学\n希望峰学院\n秀尽学院", "校特等奖", "单手倒立");
    memberHash.insert(mem.readName(), mem);
    hashCount();
}

/*
 * 介绍: 获取ListWidget中的信息
 * 输入参数:
 * 返回值: 1-执行完正常返回
 */
bool Widget::ReadList()
{
    //获得选中项的文本信息
    QString strInfo;
    QListWidgetItem *currentItem;
    QList<QListWidgetItem*> selectList = ui->listWidget->selectedItems();

    if(selectList.isEmpty())
    {
        qDebug() << "NO SELECT";
    }
    else
    {
        qDebug() << "SELECT";

        //获取文本信息
        currentItem = selectList.at(0);
        strInfo = currentItem->text();

        //由文本信息获得哈希表信息
        MemberInfo tempMem;
        tempMem = memberHash[strInfo];

        //设置文本框信息
        ui->lineEdit->setText(tempMem.readName());
        ui->lineEdit_2->setText(tempMem.m_Origin);
        ui->textEdit_2->setText(tempMem.m_Address);
        ui->textEdit_3->setText(tempMem.m_Education);
        ui->textEdit_4->setText(tempMem.m_Award);
        ui->textEdit_5->setText(tempMem.m_Specialty);

        //设置下拉框信息
        ui->comboBox->setCurrentIndex(tempMem.m_Sex);
        ui->comboBox_2->setCurrentIndex(tempMem.m_Politics);

        //设置日期
        ui->dateEdit->setDate(QDate::fromString(tempMem.m_Birthday, "yyyy/MM/dd"));

        //设置头像
        QPixmap pixmap("C:/Users/kongkongbei/Desktop/QtProject/Project02/headshot/01.jpg");
        pixmap = pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label_10->setScaledContents(true);
        ui->label_10->setPixmap(pixmap);
        qDebug() << ui->label_10;
        qDebug() << pixmap;
    }
    return 1;
}

/*
 * 介绍: 添加界面中的成员信息至哈希表中
 * 输入参数:
 * 返回值:
 */
void Widget::addMemberInfo()
{
    //将数据插入哈希表中
    MemberInfo *tempMember = new MemberInfo(ui->lineEdit->text(), ui->comboBox->currentIndex(), ui->lineEdit_2->text(),
                ui->dateEdit->text(), ui->label_10->text(), ui->comboBox_2->currentIndex(),
                ui->textEdit_2->toPlainText(), ui->textEdit_3->toPlainText(), ui->textEdit_4->toPlainText(),
                ui->textEdit_5->toPlainText());
    memberHash.insert(tempMember->readName(), *tempMember);
    m_hashCount++;

    qDebug() << tempMember->m_Headshot;

    //map能解决重名问题，但是都用哈希了，蒜鸟蒜鸟

    //向ListWidget插入名称
    if(ui->lineEdit->text() == "")
    {
        QMessageBox::information(NULL, "错误", "姓名不能为空", QMessageBox::Yes);
    }
    else
    {
        //根据LineEdit控件进行索引
        QListWidgetItem *pListItem = new QListWidgetItem(ui->lineEdit->text());
        pListItem->setSizeHint(QSize(0,60));

        //将信息插入ListWidget中
        ui->listWidget->addItem(pListItem);
    }

}

/*
 * 介绍: 删除成员信息
 * 输入参数:
 * 返回值:
 */
void Widget::deleteMemberInfo()
{
    //信息提示窗口
    QMessageBox dialog(QMessageBox::Information, "提示", "是否删除当前记录");
    dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog.button(QMessageBox::Yes)->setText("确定");
    dialog.button(QMessageBox::No)->setText("取消");

    if(dialog.exec() == QMessageBox::No)
    {
        return;
    }
    else
    {
        int row = ui->listWidget->currentRow();
        QListWidgetItem *item = ui->listWidget->takeItem(row);
        delete item;

        memberHash.remove(ui->lineEdit->text());

        //清除所有文本信息
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit_4->clear();
        ui->textEdit_5->clear();

        //组合框默认设置为第一个
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(0);

        //清除图片
        ui->label_10->clear();

        //重置时间控件
        QDate date = QDate::fromString("20000101", "yyyyMMdd");
        ui->dateEdit->setDate(date);
    }
}

/*
 * 介绍: 设置成员头像
 * 输入参数:
 * 返回值:
 */
void Widget::selectHeadshot()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择头像"),
        "C:/",
        tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QPixmap pixmap(fileName);
        pixmap = pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_10->setScaledContents(true);
        ui->label_10->setPixmap(pixmap);
    }
}

//哈希表是无序的, 所以这个函数并没有啥用
void Widget::hashCount()
{
    QHash<QString,MemberInfo>::iterator i;
    int count = 0;
    for(i = memberHash.begin(); i != memberHash.end(); ++i)
    {
        count++;
    }
    m_hashCount = count;
}

/*
 * 介绍: 设置信号与槽
 * 输入参数:
 * 返回值:
 */
void Widget::SetupConnections()
{
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Widget::ReadList);
    connect(ui->addButton, &QPushButton::clicked, this, &Widget::addMemberInfo);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Widget::deleteMemberInfo);
    connect(ui->saveButton, &QPushButton::clicked, this, &Widget::SaveMemberInfo);
    connect(ui->headshotSelectButton, &QPushButton::clicked, this, &Widget::selectHeadshot);
    connect(ui->exportButton, &QPushButton::clicked, this, &Widget::OutputMemberInfo);
}

/*
 * 介绍: 保存成员档案信息
 * 输入参数:
 * 返回值:
 */
void Widget::SaveMemberInfo()
{
    if(ui->lineEdit->text() == "")
    {
        //信息提示窗口
        QMessageBox dialog(QMessageBox::Information, "提示", "姓名不能为空");
        dialog.setStandardButtons(QMessageBox::Yes);
        dialog.button(QMessageBox::Yes)->setText("确 定");
        return;
    }
    else
    {
        if(memberHash.contains(ui->lineEdit->text()))
        {
            //将信息保存
            MemberInfo &tempMember = memberHash[ui->lineEdit->text()];
            tempMember.m_Sex = ui->comboBox->currentIndex();
            tempMember.m_Origin = ui->lineEdit_2->text();
            tempMember.m_Birthday = ui->dateEdit->text();
            tempMember.m_Headshot = ui->label_10->text();
            tempMember.m_Politics = ui->comboBox_2->currentIndex();
            tempMember.m_Address = ui->textEdit_2->toPlainText();
            tempMember.m_Education = ui->textEdit_3->toPlainText();
            tempMember.m_Award = ui->textEdit_4->toPlainText();
            tempMember.m_Specialty = ui->textEdit_5->toPlainText();
        }
        else
        {
            QMessageBox::information(NULL, "错误", "不存在该成员，无法保存", QMessageBox::Yes);
            return;
        }
    }
}

/*
 * 介绍: 将当前选择的成员信息导出为Pdf
 * 输入参数:
 * 返回值:
 */
void Widget::OutputMemberInfo()
{
    //输出文件名设置
    // QString path = QCoreApplication::applicationDirPath(); //这玩意不好用
    // qDebug() << path;
    QFile pdfFile("C:/Users/kongkongbei/Desktop/QtProject/Project02/Info.pdf");
    if(!pdfFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,
                             tr("write File"),
                             tr("Cannot open file:\n%1").arg("C:/Users/kongkongbei/Desktop/QtProject/Project02/Info.pdf"));
        return;
    }

    //设置PDF文档界面 - 页边距为3cm - 页面大小为A4
    QPdfWriter *pdfWriter = new QPdfWriter(&pdfFile);
    pdfWriter->setPageSize(QPageSize::A4);
    pdfWriter->setPageMargins(QMargins(30,30,0,0));

    QPainter *pdfPainter = new QPainter(pdfWriter);

    //设置标题
    QTextOption option(Qt::AlignCenter);
    option.setWrapMode(QTextOption::WordWrap);

    //设置字体
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(22);
    font.setBold(true);

    //画笔字体设置
    pdfPainter->setFont(font);

    //绘制标题
    pdfPainter->drawText(QRect(3000, 0, 2100, 450), "成员档案", option);

    //绘制表格注释信息
    pdfDrawAndWrite(1000, 500, 750, 500, "姓名", pdfPainter, 0);
    pdfDrawAndWrite(3750, 500, 750, 500, "性别", pdfPainter, 0);
    pdfDrawAndWrite(1000, 1000, 750, 500, "籍贯", pdfPainter, 0);
    pdfDrawAndWrite(3250, 1000, 1250, 500, "出生日期", pdfPainter, 0);
    pdfDrawAndWrite(1000, 1500, 1250, 500, "政治面貌", pdfPainter, 0);
    pdfDrawAndWrite(1000, 2000, 750, 1000, "家庭\n住址", pdfPainter, 0);
    pdfDrawAndWrite(1000, 3000, 750, 1500, "教育\n经历", pdfPainter, 0);
    pdfDrawAndWrite(1000, 4500, 750, 1500, "获得\n奖项", pdfPainter, 0);
    pdfDrawAndWrite(1000, 6000, 750, 1500, "特长", pdfPainter, 0);

    //关闭画笔粗体 填写具体信息
    font.setBold(false);
    pdfPainter->setFont(font);

    pdfDrawAndWrite(1750, 500, 2750, 500, ui->lineEdit->text(), pdfPainter, 1);
    pdfDrawAndWrite(4500, 500, 2000, 500, ui->comboBox->currentText(), pdfPainter, 1);
    pdfDrawAndWrite(1750, 1000, 1500, 500, ui->lineEdit_2->text(), pdfPainter, 1);
    pdfDrawAndWrite(4500, 1000, 2000, 500, ui->dateEdit->date().toString(Qt::ISODate), pdfPainter, 1);
    pdfDrawAndWrite(2250, 1500, 4250, 500, ui->comboBox_2->currentText(), pdfPainter, 1);
    pdfDrawAndWrite(1750, 2000, 5750, 1000, ui->textEdit_2->toPlainText(), pdfPainter, 1);
    pdfDrawAndWrite(1750, 3000, 5750, 1500, ui->textEdit_3->toPlainText(), pdfPainter, 1);
    pdfDrawAndWrite(1750, 4500, 5750, 1500, ui->textEdit_4->toPlainText(), pdfPainter, 1);
    pdfDrawAndWrite(1750, 6000, 5750, 1500, ui->textEdit_5->toPlainText(), pdfPainter, 1);
    pdfDrawAndWrite(6500, 500, 1000, 1500, "", pdfPainter, 1);

    //头像路径加载
    QString path = "C:/Users/kongkongbei/Desktop/QtProject/Project02/headshot/01.jpg";
    QPixmap headshot;

    if(!headshot.load(path))
    {
        pdfPainter->end();
        delete pdfPainter;
        pdfFile.close();
        return;
    }

    //绘制头像
    QPixmap scaledHeadshot = headshot.scaled(1000, 1500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pdfPainter->drawPixmap(QRect(6500, 500, 1000, 1500), scaledHeadshot);

    //关闭绘画
    pdfPainter->end();
    delete pdfPainter;
    pdfFile.close();


    qDebug() << "文件导出成功";
}

/*
 * 介绍: 在pdf上绘制框和文本
 * 输入参数: posX - 矩形的X坐标 posY - 矩形的Y坐标 rectX - 矩形的宽度 rectY - 矩形的高 Info文本信息
 * *painter - 画笔配置 mode 图上距离1cm = 数值单位500
 * 返回值:
 */
void Widget::pdfDrawAndWrite(qreal posX, qreal posY, qreal rectX, qreal rectY, QString Info, QPainter *painter, bool mode)
{
    //设置文本尺寸
    QFont font = painter->font();
    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 2));

    //绘制方框和文本
    painter->drawRect(QRectF(posX, posY, rectX, rectY));
    if(mode == 0)
    {
        painter->drawText(QRectF(posX, posY, rectX, rectY), Qt::AlignCenter, Info);
    }
    else
    {
        painter->drawText(QRectF(posX+100, posY, rectX-100, rectY), Qt::AlignLeft | Qt::AlignVCenter, Info);
    }

}
