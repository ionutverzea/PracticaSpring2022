#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_choose_an_image_clicked();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_actionExit_triggered();

    void on_label_linkHovered(const QString &link);

private:
    Ui::MainWindow *ui;
    QPixmap image;
    QImage  *imageObject;
};
#endif // MAINWINDOW_H
