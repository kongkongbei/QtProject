#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString formatFilesize(qint64 bytes);
    bool ifCompressFile(const QFileInfo &fileInfo);

private slots:

private:
    Ui::MainWindow *ui;

    QFileSystemModel *fileSystemModel;
    QString currentPath;

    QString getFileType(const QFileInfo &fileInfo);
    void loadDirectoryModel(QStandardItemModel *model, const QString &dirPath, QString &currentDir);
};
#endif // MAINWINDOW_H
