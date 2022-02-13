#ifndef FORMATTING_H
#define FORMATTING_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class Formatting;
}

class Formatting : public QMainWindow
{
    Q_OBJECT

    static vector<string> formattedXML;

public:
    explicit Formatting(QWidget *parent = nullptr);
    ~Formatting();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_actionConsistency_triggered();

    void on_actionXML_To_JSON_triggered();

    void on_actionCompress_triggered();

    void on_actionSave_triggered();

private:
    Ui::Formatting *ui;
};

#endif // FORMATTING_H
