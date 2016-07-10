#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dicomdirfile.h>
#include <dicomimage.h>
#include <QListWidgetItem>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_studiesList_itemClicked(QListWidgetItem *item);

    void on_seriesList_itemClicked(QListWidgetItem *item);

    void on_prevImagesButton_clicked();

    void on_nextImagesButton_clicked();

    //void displayImage();

    void showImage();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QImage image;
    //QTimer* timer;

    DICOMDIRFile* dicomFile = nullptr;

    std::vector<DICOMImage*> images;
    unsigned int currentImage = 0;
};

#endif // MAINWINDOW_H
