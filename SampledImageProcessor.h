#ifndef SAMPLEDIMAGEPROCESSOR_H
#define SAMPLEDIMAGEPROCESSOR_H

#pragma once

#include <QThread>
#include <QString>
#include <vector>
#include <string>

class SampledImageProcessor : public QThread
{
    Q_OBJECT

public:
    SampledImageProcessor(const std::vector<std::string>& filePaths, QObject *parent = nullptr);
    const std::vector<int>& getBrightnessList_r() const;
    const std::vector<int>& getBrightnessList_g() const;
    const std::vector<int>& getBrightnessList_b() const;

signals:
    void progressUpdated(int value);
    void processingFinished();

protected:
    void run() override;

private:
    std::vector<std::string> m_filePaths;
    std::vector<int> m_brightnessList_r;
    std::vector<int> m_brightnessList_g;
    std::vector<int> m_brightnessList_b;
};






#endif // SAMPLEDIMAGEPROCESSOR_H
