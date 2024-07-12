#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "SampledImageProcessor.h"


#include "ImageProcessor.h"

QT_CHARTS_USE_NAMESPACE


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void updateProgressBar(int value);
    void handleProcessingFinished_r(); // 通道
    void handleProcessingFinished_g(); //
    void handleProcessingFinished_b(); //
    void handleProcessingFinished_rgb();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    ImageProcessor *imageProcessor;
    SampledImageProcessor *sampledImageProcessor; // 新增的指针
    //void createChartView(QChartView *chartView, const std::vector<int> &data, const QString &title);

    int currentIndex; // 用于记录当前展示图片的索引
    QStringList filePaths; // 用于存储排序后的文件路径
    QGraphicsView* photoViews[10]; // 用于存储 QGraphicsView 控件

    // 全局变量
        std::vector<const char*> selectedImagePaths;
        int selectedImageCount = 0;

};
#endif // MAINWINDOW_H
