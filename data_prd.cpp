#include "data_prd.h"
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// 结构体定义
struct FileInfo {
    std::string path;
    FILETIME lastWriteTime;
};

// 比较函数用于排序
bool CompareByLastWriteTime(const FileInfo& a, const FileInfo& b) {
    return CompareFileTime(&a.lastWriteTime, &b.lastWriteTime) < 0;
}

const char** GetSortedJpgFilesByDateC(const char* folderPath) {
    std::vector<FileInfo> fileInfos;
    std::string searchPath = std::string(folderPath) + "\\*.jpg";
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return nullptr; // 失败时返回nullptr
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            FileInfo fileInfo;
            fileInfo.path = std::string(folderPath) + "\\" + findFileData.cFileName;
            fileInfo.lastWriteTime = findFileData.ftLastWriteTime;
            fileInfos.push_back(fileInfo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

    std::sort(fileInfos.begin(), fileInfos.end(), CompareByLastWriteTime);

    // 分配动态数组来存储文件路径
    const char** filePaths = new const char*[fileInfos.size() + 1];
    for (size_t i = 0; i < fileInfos.size(); ++i) {
        filePaths[i] = _strdup(fileInfos[i].path.c_str());
    }
    filePaths[fileInfos.size()] = nullptr; // 末尾用nullptr标记结束

    return filePaths;
}

void freeSortedJpgFiles(const char** filePaths) {
    for (size_t i = 0; filePaths[i] != nullptr; ++i) {
        free((void*)filePaths[i]);
    }
    delete[] filePaths;
}
