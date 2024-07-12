#include "mylib.h"


#include "ImageProcessor.h"
#include "data_prd.h"

ImageProcessor::ImageProcessor(const QString& folderPath, int fileCount, QObject *parent)
    : QThread(parent), m_folderPath(folderPath), m_fileCount(fileCount)
{
}

const std::vector<int>& ImageProcessor::getBrightnessList_r() const
{
    return m_brightnessList_r;
}

const std::vector<int>& ImageProcessor::getBrightnessList_g() const
{
    return m_brightnessList_g;
}

const std::vector<int>& ImageProcessor::getBrightnessList_b() const
{
    return m_brightnessList_b;
}

void ImageProcessor::run()
{
    // 将 QString 转换为标准 C 字符串
    QByteArray folderPathBytes = m_folderPath.toLocal8Bit();
    const char* folderPathCStr = folderPathBytes.data();

    // 获取排序后的 JPG 文件路径
    const char** filePaths = GetSortedJpgFilesByDateC(folderPathCStr);

    if (filePaths == nullptr) {
        emit processingFinished();
        return;
    }

    for (int i = 0; filePaths[i] != nullptr; ++i) {
        int brightness_r = getBritness_XJPG(filePaths[i], 2); // R通道
        int brightness_g = getBritness_XJPG(filePaths[i], 1); // G通道
        int brightness_b = getBritness_XJPG(filePaths[i], 0); // B通道
        m_brightnessList_r.push_back(brightness_r);
        m_brightnessList_g.push_back(brightness_g);
        m_brightnessList_b.push_back(brightness_b);


        // 更新进度条
        emit progressUpdated(i + 1);

        // 确保UI能够响应
        QThread::msleep(10); // 可选，调节此值以实现适当的进度显示
    }

    // 释放动态分配的内存
    for (int i = 0; filePaths[i] != nullptr; ++i) {
        delete[] filePaths[i];
    }
    delete[] filePaths;

    emit processingFinished();
}


