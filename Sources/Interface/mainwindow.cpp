#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "dependencies/Algorithms.h"
#include <opencv2\opencv.hpp> 

using namespace cv;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setVisible(false);
    ui->radioButton_green->setVisible(false);
    ui->radioButton_red->setVisible(false);
    ui->radioButton_blue->setVisible(false);
    ui->radioButton_minVal->setVisible(false);
    ui->radioButton_maxVal->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_choose_an_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString()) !=0)
    {
        QImage imageTemp;
        bool valid = imageTemp.load(filename);

        if(valid)
        {
            imageTemp = imageTemp.scaledToWidth(ui->label_webcam->width(), Qt::SmoothTransformation);
            image = QPixmap::fromImage(imageTemp);
            ui->label_webcam->setPixmap(image);

        }
        else
        {
            //Error handling
        }

    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    QImage temp = image.toImage();
    temp.save(imagePath);
}

void MainWindow::on_actionOpen_triggered()
{
#pragma region Old-Code

    /*
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
            image = image.scaledToWidth(ui->label_webcam->width(), Qt::SmoothTransformation);
            ui->label_webcam->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //Error handling
        }

    }
    */

#pragma endregion
    on_choose_an_image_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}






void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="Decompose")
    {
        ui->radioButton_minVal->setVisible(true);
        ui->radioButton_maxVal->setVisible(true);
        auto pixmap= ui->label_webcam->pixmap();
        QImage image = pixmap->toImage();
        cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
        cv::Mat outImage;
        Algo::Maximum_decomposition(mat, outImage);

        QImage imgIn = QImage((uchar*)outImage.data, outImage.cols, outImage.rows, outImage.step, QImage::Format_RGB888);
        ui->label_webcam->setPixmap(QPixmap::fromImage(imgIn));

    }

     else
    {
        ui->radioButton_minVal->setVisible(false);
        ui->radioButton_maxVal->setVisible(false);
    }


    if(arg1=="Single color channel")
    {
        ui->radioButton_green->setVisible(true);
        ui->radioButton_red->setVisible(true);
        ui->radioButton_blue->setVisible(true);
    }

     else
    {
        ui->radioButton_green->setVisible(false);
        ui->radioButton_red->setVisible(false);
        ui->radioButton_blue->setVisible(false);
    }



    if(arg1=="Specific # of shades")
    {
        ui->horizontalSlider->setVisible(true);
    }
     else{
        ui->horizontalSlider->setVisible(false);
    }

}


// fara img sa nu mearga alg
//textbox
//visual
//filtre
//help button
//implement the webcam



void MainWindow::on_label_linkHovered(const QString &link)
{
    //nothing
    //DO NOT DELETE
}

