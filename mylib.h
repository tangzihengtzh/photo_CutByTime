#pragma once

#ifdef MYLIB_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif

extern "C" MYLIB_API void ShowImage(const char* imagePath);

extern "C" MYLIB_API unsigned char* GenerateThumbnail(const char* imagePath, int& width, int& height, int& channels);

extern "C" {
    struct BrightnessResult {
        int* brightnessArray;
        int count;
    };

}
extern "C" MYLIB_API BrightnessResult C_getBritness_RJPG_List_Value(const char* Path_folder);
extern "C" MYLIB_API void freeBrightnessResult(BrightnessResult result);
extern "C" MYLIB_API int getBritness_RJPG(const char* imagePath);

//测量一个jpg文件的全局指定通道的亮度
// OpenCV使用BGR格式，0B/1G/2R
extern "C" MYLIB_API int getBritness_XJPG(const char* imagePath, int channel);

//合并图像
extern "C" MYLIB_API int create_img(const char** imagepath_list, int num, int agl);
