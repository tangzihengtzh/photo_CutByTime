#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QLineSeries>
#include "mylib.h"
#include <QProgressBar>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include "data_prd.h"
#include "SampledImageProcessor.h"
#include <QDebug>


QT_CHARTS_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar_0->setValue(0);
    // 初始化 QGraphicsView 控件数组
    currentIndex = 0;
    photoViews[0] = ui->photo_show0;
    photoViews[1] = ui->photo_show1;
    photoViews[2] = ui->photo_show2;
    photoViews[3] = ui->photo_show3;
    photoViews[4] = ui->photo_show4;
    photoViews[5] = ui->photo_show5;
    photoViews[6] = ui->photo_show6;
    photoViews[7] = ui->photo_show7;
    photoViews[8] = ui->photo_show8;
    photoViews[9] = ui->photo_show9;
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    // 从输入文本框获取文件夹路径
    QString folderPath = ui->path_folder->toPlainText();

    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a folder path.");
        return;
    }

    // 获取排序后的 JPG 文件路径，计算总文件数以设置进度条范围
    const char** filePaths = GetSortedJpgFilesByDateC(folderPath.toLocal8Bit().data());
    if (filePaths == nullptr) {
        QMessageBox::warning(this, "Error", "Failed to retrieve file paths.");
        return;
    }
    int fileCount = 0;
    while (filePaths[fileCount] != nullptr) {
        fileCount++;
    }
    freeSortedJpgFiles(filePaths);

    // 设置进度条范围
    ui->progressBar_0->setRange(0, fileCount);
    ui->progressBar_0->setValue(0);

    // 创建并启动ImageProcessor线程
    imageProcessor = new ImageProcessor(folderPath, fileCount, this);
    connect(imageProcessor, &ImageProcessor::progressUpdated, this, &MainWindow::updateProgressBar);
    //connect(imageProcessor, &ImageProcessor::processingFinished, this, &MainWindow::handleProcessingFinished_r);
    connect(imageProcessor, &ImageProcessor::processingFinished, this, &MainWindow::handleProcessingFinished_rgb);
    imageProcessor->start();
}


void MainWindow::on_pushButton_2_clicked()
{
    // 从输入文本框获取文件夹路径
    QString folderPath = ui->path_folder->toPlainText();

    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a folder path.");
        return;
    }

    // 获取排序后的 JPG 文件路径，计算总文件数以设置进度条范围
    const char** filePaths = GetSortedJpgFilesByDateC(folderPath.toLocal8Bit().data());
    if (filePaths == nullptr) {
        QMessageBox::warning(this, "Error", "Failed to retrieve file paths.");
        return;
    }
    int fileCount = 0;
    while (filePaths[fileCount] != nullptr) {
        fileCount++;
    }
    freeSortedJpgFiles(filePaths);

    // 设置进度条范围
    ui->progressBar_0->setRange(0, fileCount);
    ui->progressBar_0->setValue(0);

    // 创建并启动ImageProcessor线程
    imageProcessor = new ImageProcessor(folderPath, fileCount, this);
    connect(imageProcessor, &ImageProcessor::progressUpdated, this, &MainWindow::updateProgressBar);
    connect(imageProcessor, &ImageProcessor::processingFinished, this, &MainWindow::handleProcessingFinished_g);
    imageProcessor->start();
}

void MainWindow::on_pushButton_3_clicked()
{
    // 从输入文本框获取文件夹路径
    QString folderPath = ui->path_folder->toPlainText();

    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a folder path.");
        return;
    }

    // 获取排序后的 JPG 文件路径，计算总文件数以设置进度条范围
    const char** filePaths = GetSortedJpgFilesByDateC(folderPath.toLocal8Bit().data());
    if (filePaths == nullptr) {
        QMessageBox::warning(this, "Error", "Failed to retrieve file paths.");
        return;
    }
    int fileCount = 0;
    while (filePaths[fileCount] != nullptr) {
        fileCount++;
    }
    freeSortedJpgFiles(filePaths);

    // 设置进度条范围
    ui->progressBar_0->setRange(0, fileCount);
    ui->progressBar_0->setValue(0);

    // 创建并启动ImageProcessor线程
    imageProcessor = new ImageProcessor(folderPath, fileCount, this);
    connect(imageProcessor, &ImageProcessor::progressUpdated, this, &MainWindow::updateProgressBar);
    connect(imageProcessor, &ImageProcessor::processingFinished, this, &MainWindow::handleProcessingFinished_b);
    imageProcessor->start();
}

void MainWindow::handleProcessingFinished_b()
{
    std::vector<int> brightnessList = imageProcessor->getBrightnessList_b();

    // 创建QLineSeries并添加数据点
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (int i = 0; i < brightnessList.size(); ++i) {
        series->append(i, brightnessList[i]);
    }

    // 创建QChart并添加QLineSeries
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("B Channel Brightness Over Files");

    // 创建并设置X轴
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setRange(0, brightnessList.size() - 1);
    axisX->setTickType(QtCharts::QValueAxis::TicksDynamic);
    axisX->setTickInterval((brightnessList.size() > 10) ? 5 : 1);
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    // 创建并设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setRange(0, 255);
    axisY->setLabelFormat("%d");
    chart->setAxisY(axisY, series);

    // 设置QChart到QChartView控件
    ui->data_b->setChart(chart);
    ui->data_b->setRenderHint(QPainter::Antialiasing);

    // 释放ImageProcessor对象
    imageProcessor->deleteLater();
    imageProcessor = nullptr;
}



void MainWindow::handleProcessingFinished_g()
{
    std::vector<int> brightnessList = imageProcessor->getBrightnessList_g(); // 切换通道

    // 创建QLineSeries并添加数据点
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (int i = 0; i < brightnessList.size(); ++i) {
        series->append(i, brightnessList[i]);
    }

    // 创建QChart并添加QLineSeries
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("G Channel Brightness Over Files");

    // 创建并设置X轴
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setRange(0, brightnessList.size() - 1);
    axisX->setTickType(QtCharts::QValueAxis::TicksDynamic);
    axisX->setTickInterval((brightnessList.size() > 10) ? 5 : 1);
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    // 创建并设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setRange(0, 255);
    axisY->setLabelFormat("%d");
    chart->setAxisY(axisY, series);

    // 设置QChart到QChartView控件
    ui->data_g->setChart(chart);
    ui->data_g->setRenderHint(QPainter::Antialiasing);

    // 释放ImageProcessor对象
    imageProcessor->deleteLater();
    imageProcessor = nullptr;
}

void MainWindow::handleProcessingFinished_rgb()
{
    std::vector<int> brightnessList_r = imageProcessor->getBrightnessList_r();
    std::vector<int> brightnessList_g = imageProcessor->getBrightnessList_g();
    std::vector<int> brightnessList_b = imageProcessor->getBrightnessList_b();

    // 创建QLineSeries并添加数据点
    QtCharts::QLineSeries *series_r = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *series_g = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *series_b = new QtCharts::QLineSeries();
    for (int i = 0; i < brightnessList_r.size(); ++i) {
        series_r->append(i, brightnessList_r[i]);
        series_g->append(i, brightnessList_g[i]);
        series_b->append(i, brightnessList_b[i]);
    }

    // 计算合适的间隔
    int sampleCount = brightnessList_r.size();
    int interval = sampleCount / 20;
    if (interval < 1) interval = 1;

    // ================================r
    QtCharts::QChart *chart_r = new QtCharts::QChart();
    chart_r->legend()->hide();
    chart_r->addSeries(series_r);
    chart_r->createDefaultAxes();
    chart_r->setTitle("R Channel Brightness Over Files");
    QtCharts::QValueAxis *axisX_r = new QtCharts::QValueAxis;
    axisX_r->setRange(0, sampleCount - 1);
    axisX_r->setTickInterval(interval);
    axisX_r->setLabelFormat("%d");
    chart_r->setAxisX(axisX_r, series_r);
    QtCharts::QValueAxis *axisY_r = new QtCharts::QValueAxis;
    axisY_r->setRange(0, 255);
    axisY_r->setLabelFormat("%d");
    chart_r->setAxisY(axisY_r, series_r);
    ui->data_r->setChart(chart_r);
    ui->data_r->setRenderHint(QPainter::Antialiasing);

    // ================================g
    QtCharts::QChart *chart_g = new QtCharts::QChart();
    chart_g->legend()->hide();
    chart_g->addSeries(series_g);
    chart_g->createDefaultAxes();
    chart_g->setTitle("G Channel Brightness Over Files");
    QtCharts::QValueAxis *axisX_g = new QtCharts::QValueAxis;
    axisX_g->setRange(0, sampleCount - 1);
    axisX_g->setTickInterval(interval);
    axisX_g->setLabelFormat("%d");
    chart_g->setAxisX(axisX_g, series_g);
    QtCharts::QValueAxis *axisY_g = new QtCharts::QValueAxis;
    axisY_g->setRange(0, 255);
    axisY_g->setLabelFormat("%d");
    chart_g->setAxisY(axisY_g, series_g);
    ui->data_g->setChart(chart_g);
    ui->data_g->setRenderHint(QPainter::Antialiasing);

    // ================================b
    QtCharts::QChart *chart_b = new QtCharts::QChart();
    chart_b->legend()->hide();
    chart_b->addSeries(series_b);
    chart_b->createDefaultAxes();
    chart_b->setTitle("B Channel Brightness Over Files");
    QtCharts::QValueAxis *axisX_b = new QtCharts::QValueAxis;
    axisX_b->setRange(0, sampleCount - 1);
    axisX_b->setTickInterval(interval);
    axisX_b->setLabelFormat("%d");
    chart_b->setAxisX(axisX_b, series_b);
    QtCharts::QValueAxis *axisY_b = new QtCharts::QValueAxis;
    axisY_b->setRange(0, 255);
    axisY_b->setLabelFormat("%d");
    chart_b->setAxisY(axisY_b, series_b);
    ui->data_b->setChart(chart_b);
    ui->data_b->setRenderHint(QPainter::Antialiasing);

    // 释放ImageProcessor对象
    imageProcessor->deleteLater();
    imageProcessor = nullptr;
}


//void MainWindow::handleProcessingFinished_rgb()
//{
//    std::vector<int> brightnessList_r = imageProcessor->getBrightnessList_r();
//    std::vector<int> brightnessList_g = imageProcessor->getBrightnessList_g();
//    std::vector<int> brightnessList_b = imageProcessor->getBrightnessList_b();

//    // 创建QLineSeries并添加数据点
//    QtCharts::QLineSeries *series_r = new QtCharts::QLineSeries();
//    QtCharts::QLineSeries *series_g = new QtCharts::QLineSeries();
//    QtCharts::QLineSeries *series_b = new QtCharts::QLineSeries();
//    for (int i = 0; i < brightnessList_r.size(); ++i) {
//        series_r->append(i, brightnessList_r[i]);
//        series_g->append(i, brightnessList_g[i]);
//        series_b->append(i, brightnessList_b[i]);
//    }

//    // ================================r
//    QtCharts::QChart *chart_r = new QtCharts::QChart();
//    chart_r->legend()->hide();
//    chart_r->addSeries(series_r);
//    chart_r->createDefaultAxes();
//    chart_r->setTitle("R Channel Brightness Over Files");
//    QtCharts::QValueAxis *axisX_r = new QtCharts::QValueAxis;
//    axisX_r->setRange(0, brightnessList_r.size() - 1);
//    axisX_r->setTickType(QtCharts::QValueAxis::TicksDynamic);
//    axisX_r->setTickInterval((brightnessList_r.size() > 10) ? 5 : 1);
//    axisX_r->setLabelFormat("%d");
//    chart_r->setAxisX(axisX_r, series_r);
//    QtCharts::QValueAxis *axisY_r = new QtCharts::QValueAxis;
//    axisY_r->setRange(0, 255);
//    axisY_r->setLabelFormat("%d");
//    chart_r->setAxisY(axisY_r, series_r);
//    ui->data_r->setChart(chart_r);
//    ui->data_r->setRenderHint(QPainter::Antialiasing);

//    // ================================g
//    QtCharts::QChart *chart_g = new QtCharts::QChart();
//    chart_g->legend()->hide();
//    chart_g->addSeries(series_g);
//    chart_g->createDefaultAxes();
//    chart_g->setTitle("G Channel Brightness Over Files");
//    QtCharts::QValueAxis *axisX_g = new QtCharts::QValueAxis;
//    axisX_g->setRange(0, brightnessList_g.size() - 1);
//    axisX_g->setTickType(QtCharts::QValueAxis::TicksDynamic);
//    axisX_g->setTickInterval((brightnessList_g.size() > 10) ? 5 : 1);
//    axisX_g->setLabelFormat("%d");
//    chart_g->setAxisX(axisX_g, series_g);
//    QtCharts::QValueAxis *axisY_g = new QtCharts::QValueAxis;
//    axisY_g->setRange(0, 255);
//    axisY_g->setLabelFormat("%d");
//    chart_g->setAxisY(axisY_g, series_g);
//    ui->data_g->setChart(chart_g);
//    ui->data_g->setRenderHint(QPainter::Antialiasing);

//    // ================================b
//    QtCharts::QChart *chart_b = new QtCharts::QChart();
//    chart_b->legend()->hide();
//    chart_b->addSeries(series_b);
//    chart_b->createDefaultAxes();
//    chart_b->setTitle("B Channel Brightness Over Files");
//    QtCharts::QValueAxis *axisX_b = new QtCharts::QValueAxis;
//    axisX_b->setRange(0, brightnessList_b.size() - 1);
//    axisX_b->setTickType(QtCharts::QValueAxis::TicksDynamic);
//    axisX_b->setTickInterval((brightnessList_b.size() > 10) ? 5 : 1);
//    axisX_b->setLabelFormat("%d");
//    chart_b->setAxisX(axisX_b, series_b);
//    QtCharts::QValueAxis *axisY_b = new QtCharts::QValueAxis;
//    axisY_b->setRange(0, 255);
//    axisY_b->setLabelFormat("%d");
//    chart_b->setAxisY(axisY_b, series_b);
//    ui->data_b->setChart(chart_b);
//    ui->data_b->setRenderHint(QPainter::Antialiasing);

//    // 释放ImageProcessor对象
//    imageProcessor->deleteLater();
//    imageProcessor = nullptr;
//}


void MainWindow::updateProgressBar(int value)
{
    ui->progressBar_0->setValue(value);
}

void MainWindow::handleProcessingFinished_r()
{
    std::vector<int> brightnessList = imageProcessor->getBrightnessList_r();

    // 创建QLineSeries并添加数据点
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    for (int i = 0; i < brightnessList.size(); ++i) {
        series->append(i, brightnessList[i]);
    }

    // 创建QChart并添加QLineSeries
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("R Channel Brightness Over Files");

    // 创建并设置X轴
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setRange(0, brightnessList.size() - 1);
    axisX->setTickType(QtCharts::QValueAxis::TicksDynamic);
    axisX->setTickInterval((brightnessList.size() > 10) ? 5 : 1);
    axisX->setLabelFormat("%d");
    chart->setAxisX(axisX, series);

    // 创建并设置Y轴
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setRange(0, 255);
    axisY->setLabelFormat("%d");
    chart->setAxisY(axisY, series);

    // 设置QChart到QChartView控件
    ui->data_r->setChart(chart);
    ui->data_r->setRenderHint(QPainter::Antialiasing);

    // 释放ImageProcessor对象
    imageProcessor->deleteLater();
    imageProcessor = nullptr;
}


//void MainWindow::on_pushButton_4_clicked()
//{
//    // 从输入文本框获取文件夹路径
//    QString folderPath = ui->path_folder->toPlainText();

//    if (folderPath.isEmpty()) {
//        QMessageBox::warning(this, "Error", "Please enter a folder path.");
//        return;
//    }

//    // 获取排序后的 JPG 文件路径
//    const char** filePathsArray = GetSortedJpgFilesByDateC(folderPath.toLocal8Bit().data());
//    if (filePathsArray == nullptr) {
//        QMessageBox::warning(this, "Error", "Failed to retrieve file paths.");
//        return;
//    }

//    // 将文件路径存储到 QStringList 中
//    QStringList filePaths;
//    int fileCount = 0;
//    while (filePathsArray[fileCount] != nullptr) {
//        filePaths.append(filePathsArray[fileCount]);
//        fileCount++;
//    }

//    // 释放原始文件路径内存
//    freeSortedJpgFiles(filePathsArray);

//    // 获取用户输入的索引
//    bool ok;
//    int index = ui->idx_show->toPlainText().toInt(&ok);

//    if (!ok || index < 0 || index >= filePaths.size()) {
//        QMessageBox::warning(this, "Error", QString("Please enter a valid index. Current index: %1").arg(index));
//        return;
//    }

//    if (currentIndex >= 10) {
//        QMessageBox::warning(this, "Error", "All photo slots are filled.");
//        return;
//    }

//    // 加载图片并显示到 QGraphicsView 中
//    QString filePath = filePaths.at(index);
//    QPixmap pixmap(filePath);
//    QGraphicsScene *scene = new QGraphicsScene(this);
//    scene->addPixmap(pixmap);
//    photoViews[currentIndex]->setScene(scene);
//    photoViews[currentIndex]->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

//    // 更新当前索引
//    currentIndex++;
//}


void MainWindow::on_pushButton_4_clicked()
{
    // 从输入文本框获取文件夹路径
    QString folderPath = ui->path_folder->toPlainText();

    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a folder path.");
        return;
    }

    // 获取排序后的 JPG 文件路径
    const char** filePathsArray = GetSortedJpgFilesByDateC(folderPath.toLocal8Bit().data());
    if (filePathsArray == nullptr) {
        QMessageBox::warning(this, "Error", "Failed to retrieve file paths.");
        return;
    }

    // 将文件路径存储到 QStringList 中
    QStringList filePaths;
    int fileCount = 0;
    while (filePathsArray[fileCount] != nullptr) {
        filePaths.append(filePathsArray[fileCount]);
        fileCount++;
    }

    // 释放原始文件路径内存
    freeSortedJpgFiles(filePathsArray);

    // 获取用户输入的索引
    bool ok;
    int index = ui->idx_show->toPlainText().toInt(&ok);

    if (!ok || index < 0 || index >= filePaths.size()) {
        QMessageBox::warning(this, "Error", QString("Please enter a valid index. Current index: %1").arg(index));
        return;
    }

    if (currentIndex >= 10) {
        QMessageBox::warning(this, "Error", "All photo slots are filled.");
        return;
    }

    // 加载图片并显示到 QGraphicsView 中
    QString filePath = filePaths.at(index);
    QPixmap pixmap(filePath);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    photoViews[currentIndex]->setScene(scene);
    photoViews[currentIndex]->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

    // 更新当前索引
    currentIndex++;

    // 将选择的图片路径添加到全局变量
    std::string filePathStr = filePath.toLocal8Bit().toStdString();
    selectedImagePaths.push_back(strdup(filePathStr.c_str()));  // 使用 strdup 分配内存，并存储指针

    // 输出 selectedImagePaths 的全部内容到 debug 终端
    qDebug() << "Current selected image paths:";
    for (const char* path : selectedImagePaths) {
        qDebug() << path;
    }

    selectedImageCount++;
}


void MainWindow::on_pushButton_5_clicked()
{
    // 获取用户输入的角度值
    bool ok;
    int angle = ui->angle_input->toPlainText().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Please enter a valid angle.");
        return;
    }

    // 输出关键信息到debug终端
    qDebug() << "Selected image paths:";
    for (const char* path : selectedImagePaths) {
        qDebug() << path;
    }
    qDebug() << "Number of images:" << selectedImageCount;
    qDebug() << "Angle:" << angle;

    // 调用 create_img 函数
    int res = create_img(selectedImagePaths.data(), selectedImageCount, angle);

    // 提示用户操作完成
    QMessageBox::information(this, "Finished. Result:", QString::number(res));
}

