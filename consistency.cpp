#include "consistency.h"
#include "ui_consistency.h"
#include "mainwindow.h"
#include <QScreen>
#include <QDebug>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <QPixmap>
//#include "consistfunction.h"
//#include "consistfunction.cpp"

#include <fstream>
#include <stack>
#include <vector>
//#include "tags.h"

#include <QPropertyAnimation>

#include "options.h"
#include <unistd.h>

using namespace std;

Options *options;

// Consistency Functions
/*
vector<string> Xml_FileCorrection(vector<string>& Xml_File)
{

    int lines_iterator=0;
    int lines_Number=Xml_File.size();
    vector<string> errors_contained;
    string line;
    stack<tags> collector;

        //the file iterator
        while (lines_iterator < lines_Number)
        {
            line = Xml_File[lines_iterator];
            int character_iterator=0;
            //the line iterator
            while(line[character_iterator]!='\0')
            {
                if(line[character_iterator]=='<')
                {
                    string tag;
                    if(line[character_iterator+1]=='/')
                    {
                        character_iterator=character_iterator+2;
                        while(line[character_iterator-1]!='>')
                        {
                            tag.push_back(line[character_iterator++]);
                        }
            CheckOnTag:
                        if(!collector.empty())
                        {
                            if(tag == (collector.top()).data)
                            {
                                collector.pop();
                            }
                            else
                            {
                                bool missing_openingtag=1;
                                stack<tags> temp_collector =collector;
                                temp_collector.pop();
                                while(!(temp_collector.empty()))
                                {
                                    //check if the missing is a closing tag
                                    if(tag==((temp_collector.top()).data))
                                    {
                                        //the correction of the missing closing tag
                                        tags temp_tag = collector.top();
                                        collector.pop();
                                        string temp_line=Xml_File[temp_tag.line];
                                        temp_tag.data = "</" + temp_tag.data;
                                        temp_line.insert(temp_tag.end,temp_tag.data);
                                        Xml_File[temp_tag.line]=temp_line;



                                        //sends the error to the GUI window
                                        errors_contained.push_back("# There Is A Missing Closing Tag "+temp_tag.data);
                                        missing_openingtag=0;
                                        goto CheckOnTag;
                                    }
                                    temp_collector.pop();
                                }
                                if (missing_openingtag==1)
                                {
                                    //the correction of the missing opening tag
                                    tags temp_tag = collector.top();
                                    string temp_line=Xml_File[temp_tag.line];
                                    tag= "<" + tag;
                                    temp_line.insert(temp_tag.end,tag);
                                    Xml_File[temp_tag.line]=temp_line;

                                    //sends the error to the GUI window
                                    errors_contained.push_back("# There Is A Missing Opening Tag "+tag);
                                }
                            }
                        }
                        else
                        {
                            //the correction of the missing opening tag while the stack is empty
                            string temp_line=Xml_File[0];
                            tag = "<" + tag;
                            temp_line.insert(0,tag);
                            Xml_File[0]=temp_line;

                            //sends the error to the GUI window
                            errors_contained.push_back("# There Is A Missing Opening Tag "+tag);
                        }
                    }
                    else
                    {
                       if(line[character_iterator+1]!='?')
                       {
                            //get the opening tag and push it in the stack with all the required data about it
                            tags *ptr;
                            character_iterator=character_iterator+1;
                            while(line[character_iterator-1]!='>')
                            {
                                if(line[character_iterator]==' ')
                                {
                                    tag.push_back('>');
                                    break;
                                }
                                tag.push_back(line[character_iterator++]);
                            }

                                ptr = new tags(tag,lines_iterator,character_iterator);
                                collector.push(*ptr);
                       }
                       else
                       {
                           break;
                       }

                    }
                }
                else
                {
                    character_iterator++;
                }
            }
            lines_iterator++;
        }
        // handling the missing closing tags of the tags in the stack
        while(!(collector.empty()))
        {
            //the correction of the missing closing tag
            string temp_tag = (collector.top()).data;
            collector.pop();
            temp_tag = "</" + temp_tag;
            Xml_File.push_back(temp_tag);

            //sends the error to the GUI window
            errors_contained.push_back("# There Is A Missing Closing Tag "+temp_tag);

        }

        // return a vector containing all the correction done
        return errors_contained;
}


vector<string> Xml_FileOpener(string file_path)
{

    string inline1;
    vector<string> openedxmlfile;
    ifstream xmlfile;
    xmlfile.open(file_path);

    if (!xmlfile.fail())
    {
        while(!xmlfile.eof())
        {
            getline(xmlfile,inline1);
            openedxmlfile.push_back(inline1);
        }

    }
    xmlfile.close();
    return openedxmlfile;
}
*/



Consistency::Consistency(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Consistency)
{
    ui->setupUi(this);
    QString test;

    if (MainWindow::corrections.size() != 0)
        test = MainWindow::getOldXML();
    else
        test = MainWindow::getXML();

//    ui->textEdit->setPlainText(MainWindow::getXML());
    ui->textEdit->setPlainText(test);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_3->setReadOnly(true);
//    move(screen()->geometry().center() - frameGeometry().center());
    move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));

    QPixmap pic(":/Images/next.png");

    ui->label_3->setPixmap(pic);
    ui->label_3->setScaledContents(true);

    // Start Consistency Function

    // Put Correction String in Error Detected Text Edit
    string correction;

//    consistFunction *tes = new consistFunction();

    if (MainWindow::corrections.size() != 0)
    {

        for(int i =0; i < MainWindow::corrections.size();i++)
        {
            correction += MainWindow::corrections.at(i) + "\n";
        }

        ui->textEdit_3->setPlainText(QString::fromStdString(correction));
    }
    else
    {
        // When no error detected
        ui->textEdit_3->setPlainText("No Error Detected");
    }

    // Put the corrected xml in New XML Text Edit
    string correctedXML;

    for(int i =0; i < MainWindow::xmlFile.size();i++)
    {
        correctedXML += MainWindow::xmlFile.at(i) + "\n";
    }

    ui->textEdit_2->setPlainText(QString::fromStdString(correctedXML));
}

Consistency::~Consistency()
{
    delete ui;
}


void Consistency::on_actionOpen_triggered()
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

            ui->textEdit->setPlainText(MainWindow::getXML());


            // Start Consistency Function

//            string Filepath = MainWindow::getFilePath();
//            vector <string> xmlfile;
//            xmlfile = Xml_FileOpener(Filepath);

//            vector<string> corrections = Xml_FileCorrection(xmlfile);

//            // Put Correction String in Error Detected Text Edit
//            string correction;

//            if (corrections.size() != 0)
//            {

//                for(int i =0; i<corrections.size();i++)
//                {
//                    correction += corrections.at(i) + "\n";
//                }

//                ui->textEdit_3->setPlainText(QString::fromStdString(correction));
//            }
//            else
//            {
//                // When no error detected
//                ui->textEdit_3->setPlainText("No Error Detected");
//            }

//            // Put the corrected xml in New XML Text Edit
//            string correctedXML;

//            for(int i =0; i<xmlfile.size();i++)
//            {
//                correctedXML += xmlfile.at(i) + "\n";
//            }

//            ui->textEdit_2->setPlainText(QString::fromStdString(correctedXML));


        }
    }
}


void Consistency::on_pushButton_clicked()
{
    hide();
    options = new Options(this);
    options->show();
}


void Consistency::on_actionFormatting_triggered()
{
    hide();
    cFormat = new Formatting(this);
    cFormat->show();
}


void Consistency::on_actionXML_to_JSON_triggered()
{
    hide();
    cToJSON = new ToJSON(this);
    cToJSON->show();
}


void Consistency::on_actionCompress_triggered()
{
    testDialogC = new TestDialog(this);
    testDialogC->setModal(true);
    testDialogC->show();
}


void Consistency::on_actionSave_triggered()
{
    QString s = QFileDialog::getSaveFileName(
    this,
    "save consistency file",
    "output.xml");
}

