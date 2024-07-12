#include "mylib.h"

#include "SampledImageProcessor.h"
#include "data_prd.h"

SampledImageProcessor::SampledImageProcessor(const std::vector<std::string>& filePaths, QObject *parent)
    : QThread(parent), m_filePaths(filePaths)
{
}

const std::vector<int>& SampledImageProcessor::getBrightnessList_r() const
{
    return m_brightnessList_r;
}

const std::vector<int>& SampledImageProcessor::getBrightnessList_g() const
{
    return m_brightnessList_g;
}

const std::vector<int>& SampledImageProcessor::getBrightnessList_b() const
{
    return m_brightnessList_b;
}

void SampledImageProcessor::run()
{
    for (const auto& filePath : m_filePaths) {
        int brightness_r = getBritness_XJPG(filePath.c_str(), 2); // R通道
        int brightness_g = getBritness_XJPG(filePath.c_str(), 1); // G通道
        int brightness_b = getBritness_XJPG(filePath.c_str(), 0); // B通道
        m_brightnessList_r.push_back(brightness_r);
        m_brightnessList_g.push_back(brightness_g);
        m_brightnessList_b.push_back(brightness_b);

        // 更新进度条
        emit progressUpdated(m_brightnessList_r.size());

        // 确保UI能够响应
        QThread::msleep(10); // 可选，调节此值以实现适当的进度显示
    }

    emit processingFinished();
}
