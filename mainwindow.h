#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "options.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static QString xmlText;
    static vector<std::string> xmlVector;
    static QString filePath;
    static int fileSize;
    static QString oldXML;


public:
    static string correctedXML;
    static vector<string> corrections;
    static vector<string> xmlFile;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void setXML(QString xml)
    {
        MainWindow::xmlText = xml;
//        qDebug() << MainWindow::xmlText;
    }

    static void setVectorXML(vector<std::string> xml)
    {
        MainWindow::xmlVector = xml;
//        for (int i = 0; i < xmlVector.size(); i++)
//            qDebug() << QString::fromStdString(MainWindow::xmlVector.at(i));
    }

    static QString getXML()
    {
//        if (MainWindow::corrections.size() != 0)
//            return getOldXML();
        return MainWindow::xmlText;
    }

    static void setOldXML(QString old) {
        MainWindow::oldXML = old;
    }

    static QString getOldXML() {
        return MainWindow::oldXML;
    }

    static vector<string> getVectorXML()
    {
        return MainWindow::xmlVector;
    }

    static void openFunction(QFile *sFile)
    {
        QString text;
        vector<std::string> stringXML;

        QTextStream in(sFile);

        text = in.readAll();

        // To return the pointer to the beggining of the File
        // to read line by line of the file and put it in Vector
        in.seek(0);

        for(int i = 0;!in.atEnd(); i++) {
            stringXML.push_back(in.readLine().toStdString());
        }

        // Replace the Old XML File with the new XML File
        MainWindow::setXML(text);
        MainWindow::setOldXML(text);
        MainWindow::setVectorXML(stringXML);

        MainWindow::setFileSize(sFile->size());
//        qDebug() << "sFile Size -> " << sFile->size();

//        for (int i = 0; i < xmlVector.size(); i++)
//            qDebug() << QString::fromStdString(MainWindow::xmlVector.at(i));

    }

    static void setFilePath(QString path)
    {
        MainWindow::filePath = path;
    }

    static string getFilePath()
    {
        return MainWindow::filePath.toStdString();
    }

    static void setFileSize(int size)
    {
        MainWindow::fileSize = size;
    }

    static int getFileSize()
    {
        return MainWindow::fileSize;
    }

//    static string setCorrectedXML(string correct) {

//    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Options *op;

};
#endif // MAINWINDOW_H
