#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileIconProvider>
#include <QFile>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>

/*
 *  描述：格式化文件大小
 *  输入参数：byte - 文件大小
 *  返回值：格式化后的字符串
 */
QString MainWindow::formatFilesize(qint64 bytes)
{
    if (bytes < 1024) return QString("%1 B").arg(bytes);
    else if (bytes < 1024 * 1024) return QString("%1 KB").arg(bytes / 1024.0, 0, 'f', 1);
    else if (bytes < 1024 * 1024 * 1024) return QString("%1 MB").arg(bytes / (1024.0 * 1024), 0, 'f', 1);
    else return QString("%1 GB").arg(bytes / (1024.0 * 1024 * 1024), 0, 'f', 1);
}


/*
 *  描述：判断是否为压缩文件
 *  输入参数：fileInfo - 路径下的文件信息
 *  返回值：TRUE or FALSE
 */
bool MainWindow::ifCompressFile(const QFileInfo &fileInfo)
{
    if (fileInfo.isDir()) return false; //文件夹不参与判断
    QString suffix = fileInfo.suffix().toLower(); //将文件后缀取出，并转为小写
    return (suffix == "7z" || suffix == "zip" || suffix == "rar");
}

/*
 *  描述：根据QFileInfo中的信息判断文件类
 *  输入参数：fileInfo - 目录下的文件信息
 *  返回值：文件后缀
 */
QString MainWindow::getFileType(const QFileInfo &fileInfo)
{
    if (fileInfo.isDir())
    {
        return "文件夹";
    }

    QString suffix = fileInfo.suffix().toLower();
    return suffix;
}

/*
 *  描述：为tableview加载文件信息
 *  输入参数：model - 加载的模型 dirPath - 默认路径 currentDir - 最近路径
 *  返回值：NULL
 */
void MainWindow::loadDirectoryModel(QStandardItemModel *model, const QString &dirPath, QString &currentDir)
{
    //更新目录同时清除数据
    currentDir = dirPath;
    model->clear();

    //设置表头
    QStringList tableHeader;
    tableHeader << "文件名" << "大小" << "类型" << "修改日期" << "路径";
    model->setHorizontalHeaderLabels(tableHeader);

    //判断目录是否存在
    QDir fileDir(dirPath);
    {
        if(!fileDir.exists())
        {
            qWarning() << "目录不存在:" << dirPath;
            return;
        }
    }

    //添加“返回上级”项
    if (fileDir.cdUp()) //当不存在上级时则不会建立此列
    {
        QString parentDir = fileDir.absolutePath();
        fileDir.cd(dirPath);

        QList<QStandardItem*> firstRow; // 存储第一行信息

        //名称列
        QStandardItem *firstNameItem = new QStandardItem("📁..(上级目录)");
        firstNameItem->setEditable(false);
        firstRow.append(firstNameItem);

        //大小列
        QStandardItem *firstSizeItem = new QStandardItem("");
        firstSizeItem->setEditable(false);
        firstRow.append(firstSizeItem);

        //类型列
        QStandardItem *firstTypeItem = new QStandardItem("");
        firstTypeItem->setEditable(false);
        firstRow.append(firstTypeItem);

        //修改时间列
        QStandardItem *firstTimeItem = new QStandardItem("");
        firstTimeItem->setEditable(false);
        firstRow.append(firstTimeItem);

        //路径列
        QStandardItem *firstPathItem = new QStandardItem(parentDir);
        firstPathItem->setEditable(false);
        firstRow.append(firstPathItem);

        model->appendRow(firstRow);
    }

    //加载当前目录的文件夹和压缩文件
    QFileInfoList dirList = fileDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name); // 目录
    QFileInfoList fileList = fileDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name); // 文件

    //筛选压缩文件
    QFileInfoList compressFileList;
    for (const QFileInfo &file : std::as_const(fileList))
    {
        if (ifCompressFile(file))
        {
            compressFileList.append(file);
        }
    }

    //加载目录
    for (const QFileInfo &dirInfo : std::as_const(dirList))
    {
        QList<QStandardItem*> rowItems;

        //名称列
        QStandardItem *nameItem = new QStandardItem(QString("📁 %1").arg(dirInfo.fileName()));
        nameItem->setEditable(false);
        rowItems.append(nameItem);

        //大小列
        QStandardItem *sizeItem = new QStandardItem(QString(""));
        sizeItem->setEditable(false);
        rowItems.append(sizeItem);

        //类型列
        QStandardItem *typeItem = new QStandardItem("文件夹");
        typeItem->setEditable(false);
        rowItems.append(typeItem);

        //修改日期列
        QStandardItem *timeItem = new QStandardItem(dirInfo.lastModified().toString("yyyy-MM-dd"));
        timeItem->setEditable(false);
        rowItems.append(timeItem);

        //路径列
        QStandardItem *pathItem = new QStandardItem(dirInfo.absoluteFilePath());
        pathItem->setEditable(false);
        rowItems.append(pathItem);

        model->appendRow(rowItems);
    }

    //加载文件
    for (const QFileInfo &fileInfo : compressFileList)
    {
        QList<QStandardItem*> rowItems;

        //文件名称
        QStandardItem *nameItem = new QStandardItem(QString("🗜 %1").arg(fileInfo.fileName()));
        nameItem->setEditable(false);
        rowItems.append(nameItem);

        //大小列
        QStandardItem *sizeItem = new QStandardItem(formatFilesize(fileInfo.size()));
        sizeItem->setEditable(false);
        rowItems.append(sizeItem);

        //类型列
        QStandardItem *typeItem = new QStandardItem(getFileType(fileInfo));
        typeItem->setEditable(false);
        rowItems.append(typeItem);

        //修改日期列
        QStandardItem *timeItem = new QStandardItem(fileInfo.lastModified().toString("yyyy-MM-dd"));
        timeItem->setEditable(false);
        rowItems.append(timeItem);

        //路径列
        QStandardItem *pathItem = new QStandardItem(fileInfo.absoluteFilePath());
        pathItem->setEditable(false);
        rowItems.append(pathItem);

        model->appendRow(rowItems);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置表格视图模式
    ui->fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->fileTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->fileTable->horizontalHeader()->setStretchLastSection(true);
    ui->fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->fileTable->verticalHeader()->setVisible(false);
    ui->fileTable->setColumnWidth(0, 40); //图标列固定宽度
    ui->fileTable->setSortingEnabled(true);

    // 设置并绑定表格模型
    QStandardItemModel *model = new QStandardItemModel(this);
    QString currentDir;
    QString defultDir("C:/Users/kongk/Desktop");
    loadDirectoryModel(model, defultDir, currentDir);
    ui->fileTable->setModel(model);

    ui->pathEdit->setText(currentDir);

    connect(ui->fileTable, &QTableView::doubleClicked, [&](const QModelIndex &index)
    {

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
