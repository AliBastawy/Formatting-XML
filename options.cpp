#include "options.h"
#include "ui_options.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QFileDialog>
#include <QDebug>
#include <string>

using namespace std;

Options::Options(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
//    move(screen()->geometry().center() - frameGeometry().center());
    move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));

}

Options::~Options()
{
    delete ui;
}

// Open File Button
void Options::on_actionOpen_triggered()
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

        }
    }
}

// Consistency Button
void Options::on_pushButton_clicked()
{
    hide();
    con = new Consistency(this);
    con->show();
}

// Formatting Button
void Options::on_pushButton_2_clicked()
{
//    hide();
    formatting = new Formatting(this);
    formatting->show();
}

// Convert To JSON Button
void Options::on_pushButton_3_clicked()
{
    hide();
    toJson = new ToJSON(this);
    toJson->show();
}

// Compress File Button
void Options::on_pushButton_4_clicked()
{
//    hide();
//    compress = new Compress(this);
//    compress->show();


    testDialog = new TestDialog(this);
    testDialog->setModal(true);
    testDialog->show();

//    QDialog my_progress_dialog( this );
//    my_progress_dialog.setModal( true );
//    my_progress_dialog.show();
}

// Graph Representation Button
void Options::on_pushButton_5_clicked()
{
    hide();
    graph = new Graph(this);
    graph->show();
}
