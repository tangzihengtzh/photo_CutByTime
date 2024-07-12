#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#pragma once

#include <QThread>
#include <QString>
#include <vector>

class ImageProcessor : public QThread
{
    Q_OBJECT

public:
    ImageProcessor(const QString& folderPath, int fileCount, QObject *parent = nullptr);
    const std::vector<int>& getBrightnessList_r() const;
    const std::vector<int>& getBrightnessList_g() const;
    const std::vector<int>& getBrightnessList_b() const;

signals:
    void progressUpdated(int value);
    void processingFinished();

protected:
    void run() override;

private:
    QString m_folderPath;
    int m_fileCount;
    std::vector<int> m_brightnessList_r;
    std::vector<int> m_brightnessList_g;
    std::vector<int> m_brightnessList_b;
};



#endif // IMAGEPROCESSOR_H
