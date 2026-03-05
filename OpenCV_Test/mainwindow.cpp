#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    string path = "C:\\Users\\kongk\\Desktop\\1.jpg";
    cv::Mat img = imread(path, 1);
    if( img.empty() )
    {
        cout << "Could not read the image: " << path << endl;
    }
    cv::namedWindow("Example_Im", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example_Im",img);
}

MainWindow::~MainWindow()
{
    delete ui;
}
