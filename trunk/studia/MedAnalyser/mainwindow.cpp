#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include <imebradicomdirfile.h>
#include <dicomstudy.h>

#include <QTimer>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

#include "medimageanalyser.h"

#include <string>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Timer = new QTimer(this);
    //connect(Timer, SIGNAL(timeout()), this, SLOT(displayImage()));
    //Timer->start();
}

MainWindow::~MainWindow()
{
    delete dicomFile;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"C:\\Users\\adamt_000\\Downloads\\dicom_images\\matlab\\examples\\sample_data\\DICOM\\cd1","All files (*.*)");
    //QMessageBox::information(this,tr("File name"), filename);

    dicomFile = new ImebraDICOMDIRFile(filename.toStdString());
    dicomFile->parseDICOMDIR();

    auto patients = dicomFile->getPatients();
    for(auto it = patients.begin(); it != patients.end(); ++it) {
        DICOMPatient* patient = *it;
        ui->comboBox->addItem(QString::fromStdString(patient->getName()), QVariant::fromValue(patient));
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    DICOMPatient* patient = ui->comboBox->itemData(index).value<DICOMPatient*>();
    //QMessageBox::information( this, tr("Application Name"), QString::fromStdString(patient->getName()));

    ui->studiesList->clear();
    ui->seriesList->clear();
    for(DICOMStudy* study : patient->getStudies()) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(study->getName()));
        item->setData(Qt::UserRole, QVariant::fromValue(study));
        ui->studiesList->addItem(item);
        //QMessageBox::information( this, tr("Add item"), QString::fromStdString(study->getName()));
    }
}

void MainWindow::on_studiesList_itemClicked(QListWidgetItem *item)
{
    DICOMStudy* study = item->data(Qt::UserRole).value<DICOMStudy*>();

    ui->seriesList->clear();
    for(DICOMSeries* series : study->getSeries()) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(series->getName()));
        item->setData(Qt::UserRole, QVariant::fromValue(series));
        ui->seriesList->addItem(item);
    }
}

void MainWindow::on_seriesList_itemClicked(QListWidgetItem *item)
{
    DICOMSeries* series = item->data(Qt::UserRole).value<DICOMSeries*>();
    images = series->getImages();
    currentImage = 0;
    showImage();
}

void MainWindow::on_prevImagesButton_clicked()
{
    if(images.size() > 0) {
        if(currentImage > 0)
            currentImage--;
    }

    showImage();
}

void MainWindow::on_nextImagesButton_clicked()
{
    if(images.size() > 0) {
        if(currentImage < images.size())
            currentImage++;
    }

    showImage();
}

void MainWindow::showImage()
{
    if(currentImage < images.size()) {
        DICOMImage* im = images.at(currentImage);
        ui->lineEdit->setText(QString::fromStdString(im->getFilePath()));
        im->openImageFile();
        //QMessageBox::information( this, tr("Add item"), QString::fromStdString(im->getFilePath()));

        Mat img = im->getImage();

        //cv::resize(img, img, Size(512, 384), 0, 0, INTER_LINEAR);
        cv::cvtColor(img,img,CV_BGR2RGB); //Qt reads in RGB whereas CV in BGR
        QImage image((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        ui->displayImage->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    MedImageAnalyser& imageAnalyser = MedImageAnalyser::getInstance();

    DICOMImage* im = images.at(currentImage);
    im->openImageFile();

    Mat img = im->getImage();
    int cannyValue = ui->horizontalSlider->value();

    ImageSlice slice(img,img);
    imageAnalyser.convertImage(slice,cannyValue);
    Mat procImage = slice.getInPhaseImage();
    cv::cvtColor(procImage,procImage,CV_BGR2RGB); //Qt reads in RGB whereas CV in BGR
    QImage image((uchar*)procImage.data, procImage.cols, procImage.rows, procImage.step, QImage::Format_RGB888);
    ui->displayImage->setPixmap(QPixmap::fromImage(image));
}
