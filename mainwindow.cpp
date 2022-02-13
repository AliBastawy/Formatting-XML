#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QFileDialog>
#include <QDebug>
#include <QMetaType>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "consistfunction.h"

using namespace std;

QString MainWindow::xmlText = "";
vector<string> MainWindow::xmlVector;
QString MainWindow::filePath;
int MainWindow::fileSize;
string MainWindow::correctedXML;
vector<string> MainWindow::corrections;
vector<string> MainWindow::xmlFile;
QString MainWindow::oldXML;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    move(screen()->geometry().center() - frameGeometry().center());
    move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Open File Button
void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a File");
    MainWindow::setFilePath(file);

    // If there is an error in the XML then correct it and make the path to the new Corrected XML file
    new consistFunction();

    if (!file.isEmpty() && file.toStdString().substr(file.length()-3) == "xml")
    {
        QFile sFile(file);
        if (sFile.open(QFile::ReadOnly | QFile::Text))
        {

            MainWindow::openFunction(&sFile);

            sFile.close();

            hide();
            op = new Options(this);
            op->show();

        }

    }
}

// Next Button
void MainWindow::on_pushButton_2_clicked()
{
    QString file = ui->lineEdit->text();
    MainWindow::setFilePath(file);

    if (!file.isEmpty())
    {
        QFile sFile(file);
        if (sFile.open(QFile::ReadOnly | QFile::Text))
        {

            MainWindow::openFunction(&sFile);

            sFile.close();

            hide();
            op = new Options(this);
            op->show();

        }

    }
}

