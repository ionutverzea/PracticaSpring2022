#pragma once
#include <opencv2\opencv.hpp>  

#ifdef ALGORITHMS_EXPORT
	#define ALGORITHMS_API __declspec(dllexport)
#else
	#define ALGORITHMS_API __declspec(dllimport)
#endif

namespace Algo {


	bool ALGORITHMS_API Averaging(const cv::Mat&inImage, cv::Mat&outImage);
	bool ALGORITHMS_API Luminance(const cv::Mat& inImage, cv::Mat& outImage);
	bool ALGORITHMS_API Desaturation(const cv::Mat& inImage, cv::Mat& outImage);
	bool ALGORITHMS_API Maximum_decomposition(const cv::Mat& inImage, cv::Mat& outImage);
	bool ALGORITHMS_API Minimum_decomposition(const cv::Mat& inImage, cv::Mat& outImage);

	enum ColorChannel
	{
		Blue = 0,
		Green,
		Red
	};
	bool ALGORITHMS_API Single_color_channel(const cv::Mat& inImage, cv::Mat& outImage, ColorChannel colorCh = ColorChannel::Green);
	bool ALGORITHMS_API Custom_gray_shades(const cv::Mat& inImage, cv::Mat& outImage, int conversionFactor);

	enum FilterName
	{
		averaging, luminance, desaturation, maximumDecomposition, minimumDecomposition, singleColorChannel, customGrayShades
	};

	bool ALGORITHMS_API DisplayImage(cv::Mat& outImage, FilterName filterName);

	
	


	

}