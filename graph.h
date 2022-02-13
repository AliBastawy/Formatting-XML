#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include "ui_graph.h"
#include <QPainter>

namespace Ui {
class Graph;
}

class Graph : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
