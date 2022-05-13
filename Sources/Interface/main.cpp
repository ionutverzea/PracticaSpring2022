#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "dependencies/Algorithms.h"
#include <opencv2\opencv.hpp> 



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString pathToQss = app.applicationDirPath() + "\\Diffnes.qss";
    QString pathToLicense = app.applicationDirPath() + "\\License.txt";
    // Set the app style sheet
    QFile styleSheetFile(pathToQss);


   // QFile StyleSheetFile("D://projects//interface//interface//Diffnes.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    app.setStyleSheet(styleSheet);

   
    auto a = Algo::ColorChannel::Blue;

    MainWindow w;
    w.show();
    return app.exec();
}
