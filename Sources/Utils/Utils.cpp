#include <iostream>
#include "Utils.h"

namespace Utils 
{
    bool ConvertMat2QImage(cv::Mat& src, QImage& dest)
    {
        //Se verifică dacă parametrul src reprezintă o imagine de intrare validă
        if (src.rows < 1 || src.cols < 1)
            return false;
        if (!src.data)
        {
            std::cout << "Error loading image... \n";
            return false;
        }


        ///Documentation link: https://doc.qt.io/qt-5/qimage.html#QImage-4
        if (src.channels() == 1)
        {
            double scale = 255.00;
            dest = QImage(src.cols, src.rows, QImage::Format_Indexed8);

            for (size_t r = 0; r < src.rows; ++r)
            {
                uchar* pSrc = src.ptr<uchar>(r);
                QRgb* destrow = (QRgb*)dest.scanLine(r);

                for (size_t c = 0; c < src.cols; ++c)
                {
                    unsigned int color = pSrc[c];
                    destrow[c] = qRgb(color, color, color);

                }
            }
        }
        else if (src.channels() == 3)
        {
            dest = QImage(src.cols, src.rows, QImage::Format_RGB888);

            for (size_t r = 0; r < src.rows; ++r)
            {
                cv::Vec3b* pSrc = src.ptr<cv::Vec3b>(r);

                for (size_t c = 0; c < src.cols; ++c)
                {
                    uchar blue = pSrc[c][0];
                    uchar green = pSrc[c][1];
                    uchar red = pSrc[c][2];

                    dest.setPixelColor(c, r, QColor(red, green, blue));
                }
            }
        }
        else
        {
            std::cout << "Unimplemented" << std::endl;
            return false;
        }

        return true;
    }

    bool ConvertQImage2Mat(QImage& src, cv::Mat& dest)
    {
        //Se verifică dacă parametrul src reprezintă o imagine de intrare validă
        if (src.isNull() == 1)
            return false;
        if (src.format() == QImage::Format::Format_RGB888)
        {
            cv::Mat view(src.height(), src.width(), CV_8UC3, (void*)src.constBits(), src.bytesPerLine());
            cvtColor(view, dest, cv::COLOR_RGB2BGR);

        }

        else if (src.format() == QImage::Format_Indexed8)
        {
            cv::Mat view(src.height(), src.width(), CV_8UC1, (void*)src.constBits(), src.bytesPerLine());
            view.copyTo(dest);
        }
        else
        {
            std::cout << "Unimplemented" << std::endl;
            return false;
        }

        return true;
    }
}