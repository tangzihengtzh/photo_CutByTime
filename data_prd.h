#ifndef DATA_PRD_H
#define DATA_PRD_H

#pragma once

#ifdef DATA_PRD_EXPORTS
#define DATA_PRD_API __declspec(dllexport)
#else
#define DATA_PRD_API __declspec(dllimport)
#endif

const char** GetSortedJpgFilesByDateC(const char* folderPath);
void freeSortedJpgFiles(const char** filePaths);



#endif // DATA_PRD_H
