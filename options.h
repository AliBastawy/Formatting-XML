#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMainWindow>

#include "consistency.h"
#include "formatting.h"
#include "tojson.h"
#include "compress.h"
#include "testdialog.h"
#include "graph.h"

namespace Ui {
class Options;
}

class Options : public QMainWindow
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Options *ui;
    Consistency *con;
    Formatting *formatting;
    ToJSON *toJson;
    Compress *compress;
    TestDialog *testDialog;
    Graph *graph;
};

#endif // OPTIONS_H
