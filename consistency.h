#ifndef CONSISTENCY_H
#define CONSISTENCY_H

#include <QMainWindow>
#include "ui_consistency.h"

#include "formatting.h"
#include "tojson.h"
#include "testdialog.h"

namespace Ui {
class Consistency;
}

class Consistency : public QMainWindow
{
    Q_OBJECT

public:
    explicit Consistency(QWidget *parent = nullptr);
    ~Consistency();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_actionFormatting_triggered();

    void on_actionXML_to_JSON_triggered();

    void on_actionCompress_triggered();

    void on_actionSave_triggered();

private:
    Ui::Consistency *ui;
    Formatting *cFormat;
    ToJSON *cToJSON;
    TestDialog *testDialogC;
};

#endif // CONSISTENCY_H
