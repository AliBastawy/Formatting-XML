#include "tojson.h"
#include "ui_tojson.h"
#include "mainwindow.h"
#include <QScreen>
#include <QDebug>
#include <QFileDialog>
#include <QWidget>

#include "options.h"
#include "consistency.h"
#include "tojson.h"
#include "testdialog.h"

#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <stdlib.h>
#include<stdio.h>
#include "Nodes_Tree.h"
#include <iostream>
#include <fstream>
#include "tree.h"
#include "XML_Formater.h"
#include "XML_JSON.h"


using namespace std;

Options *tOptions;
Consistency *tConsistency;
Formatting *tFormat;
TestDialog *testDialogT;

ToJSON::ToJSON(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToJSON)
{
    ui->setupUi(this);
    QWidget::showFullScreen();
//    move(screen()->geometry().center() - frameGeometry().center());
    move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));

    QSize size = qApp->screens()[0]->size();
    qDebug() << "Height ->" << size.height();
    qDebug() << "Width ->" << size.width();

//    ui->textEdit_2->set

    QPixmap pic(":/Images/next.png");

    ui->label_5->setPixmap(pic);
    ui->label_5->setScaledContents(true);

    ui->textEdit->setPlainText(MainWindow::getXML());
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);

    // Function of Converting XML TO JSON

    ofstream Output_File("output.xml");

        ifstream Input_File(MainWindow::getFilePath());
        vector<string> temp;


        XML_Formater f1;
        f1.xml_cutter(Input_File, &temp);

        for (int i = 0; i < temp.size(); i++)
        {
            Output_File << temp[i] << endl;
        }
        Output_File.close();


        class tree t1;
        Nodes_Tree * t2;
        t2 = new Nodes_Tree();

        ifstream Output_File_Formatted("output.xml");

        XML_JSON j1;
        j1.tree_Void(t2, Output_File_Formatted);
        j1.Set_Repeated_Tags_Void(t2->root);
        j1.Adjust_Spacing_Levels_Void(t2->root);

        Output_File_Formatted.close();

        ofstream Output_File_JSON("output.xml");
        j1.Print_JSON_Void(t2->root, Output_File_JSON);

        Output_File_JSON.close();

        string inline1;
        vector<string> openedxmlfile;
        ifstream xmlfile;
        xmlfile.open("output.xml");

        if (!xmlfile.fail())
        {
            while(!xmlfile.eof())
            {
                getline(xmlfile,inline1);
                openedxmlfile.push_back(inline1);
            }

        }
        xmlfile.seekg(0, ios::end);
        MainWindow::setFileSize(xmlfile.tellg());
        xmlfile.close();

        string t;
        for (int i = 0; i < openedxmlfile.size(); i++)
        {
            t += openedxmlfile[i] + "\n";
//            qDebug() << QString::fromStdString(openedxmlfile[i]);
            // cout << t << endl;
            // Output_File_JSON << temp[i];
        }


    ui->textEdit_2->setPlainText(QString::fromStdString(t));
//    ui->textEdit_2->verticalScrollBar()->setSliderPosition();
}

ToJSON::~ToJSON()
{
    delete ui;
}

void ToJSON::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a File");
    MainWindow::setFilePath(file);

    if (!file.isEmpty() && file.toStdString().substr(file.length()-3) == "xml")
    {
        QFile sFile(file);
        if (sFile.open(QFile::ReadOnly | QFile::Text))
        {
            MainWindow::openFunction(&sFile);

            sFile.close();

//            ui->textEdit->setPlainText(MainWindow::getXML());

            // Function of Youssef Khaled

        }
    }
}


void ToJSON::on_pushButton_clicked()
{
    hide();
    tOptions = new Options(this);
    tOptions->show();
}


void ToJSON::on_actionConsistency_triggered()
{
    hide();
    tConsistency = new Consistency(this);
    tConsistency->show();
}


void ToJSON::on_actionFormatting_triggered()
{
    hide();
    tFormat = new Formatting(this);
    tFormat->show();
}


void ToJSON::on_actionCompress_triggered()
{
    testDialogT = new TestDialog(this);
    testDialogT->setModal(true);
    testDialogT->show();
}


void ToJSON::on_actionSave_triggered()
{
    QString s = QFileDialog::getSaveFileName(
    this,
    "save json file",
    "output.xml");
}

