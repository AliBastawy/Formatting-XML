#ifndef TOJSON_H
#define TOJSON_H

#include <QMainWindow>

namespace Ui {
class ToJSON;
}

class ToJSON : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToJSON(QWidget *parent = nullptr);
    ~ToJSON();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_actionConsistency_triggered();

    void on_actionFormatting_triggered();

    void on_actionCompress_triggered();

    void on_actionSave_triggered();

private:
    Ui::ToJSON *ui;
};

#endif // TOJSON_H
