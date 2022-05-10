#include "Algorithms.h"
#include <iostream>

using namespace std;

namespace Algo {


	bool Averaging(const cv::Mat& inImage, cv::Mat& outImage)
	{
		//Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;
		}

		const int noOfChannels = inImage.channels();

		//Se verifica daca imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}
		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++) 
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				// TO DO: comparativ a se verifica cat dureaza sa accesezi memoria cu at<> vs. alte metode
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];
				uchar grayscale = (red + green + blue) / noOfChannels;

				pOutImage[c] = grayscale;
			}
		}
		return true;
	}

	bool Luminance(const cv::Mat& inImage, cv::Mat& outImage)
	{
		//Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}
		const int noOfChannels = inImage.channels();

		//Se verifica daca imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++) 
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];

				//Nume: The weighted method --> Formula: Gray = (Red * 0.3 + Green * 0.59 + Blue * 0.11)
				//Folosită în televiziunea color și în sisteme video precum PAL, SECAM si NTSC.
				//Se folosesc ponderile 0.3 pentru roșu, 0.59 pentru culoarea verde și 0.11 pentru albastru.
				//Culoarea roșie este cea mai "țipătoare, aprinsă" dintr-o imagine, iar culoarea verde dă un efect liniștitor
				//pentru ochi. De aceea, conform standardului ITU-R Rec. 601 sau BT.601, se reduce contribuția culorii roșii și 
				//se crește contribuția culorii verzi, contribuția culorii albastre fiind între acestea două.
				uchar grayscale = (0.3*red + 0.59*green + 0.11*blue);

				pOutImage[c] = grayscale;
				
			}
		}
		return true;
	}

	bool Desaturation(const cv::Mat& inImage, cv::Mat& outImage)
	{
		//Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		const int noOfChannels = inImage.channels();
		//Se verifică dacă imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++) 
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];

				//Algorimtul acesta convertește o imagine triplet de tip RGB într-un triplet HSL(hue, saturation, lightness)
				//forțând apoi saturația la 0. 
				//Altfel spus, algoritmul ia o culoare și o convertește la varianta sa cea mai slab saturată.
				//Un pixel poate fi desaturat prin găsirea mijlocului dintre maximul (R, G, B) și minimul (R, G, B).
				uchar grayscale = (max({ red, green, blue }) + min({ red, green, blue })) / 2;

				pOutImage[c] = grayscale;

			}
		}
		return true;
	}

	bool Maximum_decomposition(const cv::Mat& inImage, cv::Mat& outImage)
	{
		// Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		const int noOfChannels = inImage.channels();

		//Se verifică dacă imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++) 
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);
			

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];

				///Acest algoritm poate fi considerat o metodă mai simplă a algoritmului de desaturație.
				//Algorimtul setează fiecare pixel la valori maxime de roșu, verde și albastru.
				uchar grayscale = (max({ red, green, blue }));

				pOutImage[c] = grayscale;
			}
		}

		return true;
	}
	bool Minimum_decomposition(const cv::Mat& inImage, cv::Mat& outImage)
	{
		// Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		const int noOfChannels = inImage.channels();

		//Se verifică dacă imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++) 
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];
				
				///Acest algoritm poate fi considerat o metodă mai simplă a algoritmului de desaturație.
				//Algorimtul setează fiecare pixel la valori minime de roșu, verde și albastru.
				uchar grayscale = (min({ red, green, blue })) / 2;

				pOutImage[c] = grayscale;
			}
		}

		return true;
	}

	bool Single_color_channel(const cv::Mat& inImage, cv::Mat& outImage, ColorChannel colorCh)
	{
		// Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		const int noOfChannels = inImage.channels();

		//Se verifică dacă imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		int colorChIdx = -1;
		switch (colorCh)
		{
		case ColorChannel::Blue:
			colorChIdx = 0;
			break;
		case ColorChannel::Green:
			colorChIdx = 1;
			break;
		case ColorChannel::Red:
			colorChIdx = 2;
			break;
		}

		for (int r = 0; r < inImage.rows; r++)
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar color = pInImage[c][colorChIdx];

				//Acest algoritm folosește informația de la un singur canal, ales de utilizator (red, green or blue).
				//Algoritmul este folosit de majoritatea camerelor digitale. 
				uchar grayscale = color;

				pOutImage[c] = grayscale;
			}
		}
		return true;
	}
	bool Custom_gray_shades(const cv::Mat& inImage, cv::Mat& outImage, int conversionFactor)
	{
		// Se verifică dacă parametrul reprezintă o imagine de intrare validă
		if (inImage.rows < 1 ||
			inImage.cols < 1)
			return false;

		if (!inImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		const int noOfChannels = inImage.channels();

		//Se verifică dacă imaginea are 3 canale
		if (noOfChannels != 3)
		{
			std::cout << "No support for images with less then 3 channels!" << std::endl;
			return false;
		}

		// Alocare memorie imagine de ieșire
		outImage = cv::Mat::zeros(inImage.rows, inImage.cols, CV_8UC1);

		for (int r = 0; r < inImage.rows; r++)
		{
			const cv::Vec3b* pInImage = inImage.ptr<cv::Vec3b>(r);
			uchar* pOutImage = outImage.ptr<uchar>(r);

			for (int c = 0; c < inImage.cols; c++)
			{
				uchar blue = pInImage[c][0];
				uchar green = pInImage[c][1];
				uchar red = pInImage[c][2];

				///Acest algoritm permite utilizatorului să aleagă câte nuanțe de gri va rezulta imaginea obținută.
				//Orice valoare între 2 și 256 este acceptată. (valoarea se introduce ca parametru -> conversionFactor)
				//2 reprezintă o imagine alb-negru, în timp ce 256 reprezintă o imagine identică ca cea rezultata la algoritmul Averaging.
				uchar grayscale = (int)(((((blue + green + red) / noOfChannels) / conversionFactor) + 0.5) * conversionFactor);

				pOutImage[c] = grayscale;
			}
		}

		return true;
	}

	bool DisplayImage(cv::Mat&outImage, FilterName filterName)
	{
		//Se verifica daca parametrul outImage este valid 
		if (outImage.rows < 1 || outImage.cols < 1)
			return false;

		if (!outImage.data)
		{
			std::cout << "Error loading image... \n";
			return false;

		}

		std::string windowName = "";

		switch (filterName)
		{
		case FilterName::averaging:
			windowName = "Averaging";
			break;
		case FilterName::desaturation:
			windowName = "Desaturation";
			break;
		case FilterName::maximumDecomposition:
			windowName = "Maximum_decomposition";
			break;
		case FilterName::minimumDecomposition:
			windowName = "Minimum_decomposition";
			break;
		case FilterName::singleColorChannel:
			windowName = "Single_color_channel";
			break;
		case FilterName::customGrayShades:
			windowName = "Custom_gray_shades";
			break;
		case FilterName::luminance:
			windowName = "Luminance";
			break;
		default:
			windowName = "";
			break;
		}
		
		cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
		cv::imshow(windowName, outImage);
		cv::waitKey(0);

		return true;
	}
}