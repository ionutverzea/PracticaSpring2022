#pragma once
#include <opencv2\opencv.hpp>  
#include <QApplication>
#include <QtGui>
#include <QLabel>

#ifdef UTILS_EXPORT
#define UTILS_API __declspec(dllexport)
#else
#define UTILS_API __declspec(dllimport)
#endif

namespace Utils
{
	
	bool UTILS_API ConvertMat2QImage(cv::Mat& src, QImage& dest);
	bool UTILS_API ConvertQImage2Mat(QImage& src, cv::Mat& dest);
}