#include <iostream>
#include "Algorithms.h"
#include "Utils.h"
#include <stdlib.h>
#include <stdbool.h>

// main entry point into the application

int main()
{
	//WORK IN PROGRESS!! 
	

	cv::Mat inImage;
	std::string path = "..\\..\\PracticaSpring2022\\Resources\\trollhunters.jpg";
	inImage = imread(path, cv::IMREAD_COLOR);
	

	cv::Mat outImage;

	/*int option;
	std::cout << "1. Original image" << std::endl;
	std::cout << "2. Averaging algorithm" << std::endl;
	std::cout << "3. Luma/Luminance algorithm" << std::endl;
	std::cout << "4. Desaturation algorithm" << std::endl;
	std::cout << "5. Minimum decomposition algorithm" << std::endl;
	std::cout << "6. Maximum decomposition algorithm" << std::endl;
	std::cout << "7. Custom # of gray shades algorithm" << std::endl;
	std::cout << "8. Single color channel algorithm" << std::endl;
	std::cout << "Enter the option: " << std::endl;
	std::cin >> option;
	std::cout << std::endl;*/

	Algo::Averaging(inImage, outImage);
	Algo::DisplayImage(outImage, Algo::FilterName::averaging);

	return 0;
}