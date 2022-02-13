#include "graph.h"
#include "ui_graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "graphs1.h"
#include "mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <cmath>
#include "options.h"
#include <QWidget>

using namespace std;

Options *returnOptions;


// Yapany Function

Graphs* Make_Graph(vector<string> Xml_File)
{

    Graphs *ptr;
    ptr = new Graphs(10);
    int lines_iterator = 0;
    int lines_Number = Xml_File.size();
    string line;
    bool follower = false;
    bool id = false;
    int current_id = -1;
    int index = 0;
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
                      if((line[character_iterator+1]!='?')&&(line[character_iterator+1]!='/'))
                      {
                        //get the opening tag and push it in the stack with all the required data about it
                        string tag;
                        character_iterator=character_iterator;
                        while(line[character_iterator-1]!='>')
                        {
                            if(line[character_iterator]==' ')
                            {
                                tag.push_back('>');
                                break;
                            }
                            tag.push_back(line[character_iterator++]);
                        }
                        if(tag=="<user>")
                        {
                            id = true;
                            follower=false;

                        }
                        else if((tag=="<id>")&&(id==true)&&(follower==false))
                        {
                            string idvalue;
                            int idnumber = 0;
                            while(line[character_iterator]!='<')
                            {
                                idvalue.push_back(line[character_iterator++]);
                            }
                            stringstream id_int_value(idvalue);
                            id_int_value >> idnumber;
                            ptr->add_vertex(idnumber);
                            current_id++;
                            id = false;
                            follower = true;
                            index=0;


                        }
                        else if((tag=="<id>")&&(id==false)&&(follower==true))
                        {
                            string idvalue;
                            int idnumber=0;
                            while(line[character_iterator]!='<')
                            {
                                idvalue.push_back(line[character_iterator++]);
                            }
                            stringstream id_int_value(idvalue);
                            id_int_value >> idnumber;
                            ptr->add_edge(idnumber);
                            index++;

                        }
                      }
                      else
                      {
                          break;
                      }
                }
                else
                {
                    character_iterator++;
                }
            }
            lines_iterator++;
        }
    return ptr;

}
vector<string> Xml_FileOpener3(string file_path)
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

int xCoord[10];
int yCoord[10];
vector <int> points[10];

Graphs *test;

void setGraph(Graphs *ptr) {
    test = ptr;
}

Graphs* getGraph() {
    return test;
}

Graph::Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    // Yapany Main
    string Filepath = MainWindow::getFilePath();
    Graphs *graph;
    vector <string> xmlfile;
    xmlfile = Xml_FileOpener3(Filepath);
    graph = Make_Graph(xmlfile);
    setGraph(graph);

    // Add horizontal layout
    QLabel *label[10];

//    for (int j = 0; j < 10; j++) {
//        qDebug() << "V: " << graph->vertex[j];
//    }
    qDebug() << "SIZE: " << graph->size;
    int randX, randY, atVertex = 0;

    // indent is the space between 2 nodes and the below 2 nodes
    int indent = 0;

    for (int i = 0; i < graph->capcity; i++) {
        // Means vertex must be between 0 and capacity of graph - 1
        if (graph->vertex[i] > 0 && graph->vertex[i] < graph->capcity ) {

            if (graph->vertex[i] == 1) {
                randX = 350;
                randY = 50;
                atVertex++;
            } else {

                if (graph->size % 2 == 0) {
                    if (i % 2 == 0 && i != 0) {
                        randX = 150;
                        randY = 200 + indent;
                    } else {
                        randX = 550;
                        randY = 200 + indent;
                        indent += 150;
                    }
                } else {
                    if (i == graph->size - 1) {
                        randX = 350;
                        randY = 200 + indent;
                    } else {
                        if (i % 2 == 0 && i != 0) {
                            randX = 150;
                            randY = 200 + indent;
                        } else {
                            randX = 550;
                            randY = 200 + indent;
                            indent += 150;
                        }

                    }
                }
            }

            xCoord[i]  = randX;
            yCoord[i]  = randY;
            label[i] = new QLabel(this);
            label[i]->setText(QString::number(graph->vertex[i]));
            label[i]->setAlignment(Qt::AlignCenter);
            label[i]->setGeometry(QRect(randX, randY, 71, 71));
            label[i]->setStyleSheet("border: 3px solid rgb(4, 134, 170);border-radius: 35px;background-color: rgb(255, 121, 12);");
        }
    }
    QLabel *arrowLabel[graph->size];
//    int sumX[10], sumY[10];
//    for (auto s : sumX)
//        s = 0;

    for (int k = 0; k < graph->capcity; k++) {
        for (int z = 0; z < graph->capcity; z++) {
            if (graph->edges[k][z] == 1) {
                arrowLabel[k] = new QLabel(this);
                QPixmap pic(":/Images/greater");
                QTransform trans;

                float yt = yCoord[z] - yCoord[k];
                float xt = xCoord[z] - xCoord[k];

                float m = yt / xt;
                float angle = atan(m) * 180 / 3.1415;

                if (xt < 0)
                    xt *= -1;

                if (yt < 0)
                    yt *= -1;


                int xd2 = (xt/2) + min(xCoord[k], xCoord[z]);
                int yd2 = (yt/2) + min(yCoord[k], yCoord[z]);

                if (k < z) {
//                    sumX[k] = -15;
                    if (angle < 0)
                        angle += 180;
                }
                if (k > z) {
//                    sumX[k] = 55;
                    if (angle < 0)
                        angle = 360 + angle;
                    else
                        angle = 180 + angle;
                }

                trans.rotate(angle);

                // 1, 3, 5, 7
                if (graph->vertex[k] % 2 != 0 && k != 0) {
                    // 1 -> 3, 1 -> 5
                    if (k < z) {
//                        yd2 -= 15;
                        xd2 += 20;
                    }
                    // 3 -> 1, 5 -> 1
                    else {
                        yd2 += 25;
                        if (graph->vertex[k] > 3) {
                            int minus = (graph->vertex[k] - 3) / 2;
                            xd2 += 5 + 5 * minus;
                        }
                        // 5 -> 4
                        if (graph->vertex[k] == graph->size - 1 && graph->vertex[z] % 2 == 0) {
                            int minRes = graph->vertex[k] - graph->vertex[z] - 1;
                            yd2 -= 25 + minRes;
                        }
                    }
                } else if (graph->vertex[k] % 2 == 0 && k != 0) {
                    // Vertex 6 or 4 or 8 (Last Vertex)
                    if (graph->vertex[k] == graph->size - 1) {

                        xd2 += 20;
                        // 6 -> 1,3,5
                        if (graph->vertex[z] % 2 != 0 && graph->vertex[z] != 1) {
                            xd2 += 10;
                        } else if (graph->vertex[z] % 2 == 0 && graph->vertex[k] == graph->size - 1) {
//                            xd2 += 20;
                            yd2 -= 30;
                        }
//                        yd2 -= 30;
                    }
                    else if (graph->vertex[z] == graph->size - 1) {
                        int res = (graph->vertex[z] - graph->vertex[k]) / 2;
                        xd2 += res * 5 + res * 2;

                        // Same level of nodes
                        if (yCoord[k] == yCoord[z])
                            yd2 += 10;
                        else {
                            int evenToOdd = (graph->vertex[k] / 2) * 5;
                            yd2 += evenToOdd;
                        }
                        // xd2 -= 5;
                    }
                    else if (graph->vertex[z] % 2 != 0 && graph->vertex[z] != 1) {
                        // 2 -> 5, 4 -> 3
                        qDebug() << "V In  " << graph->vertex[z];
                        int evenToOdd = (graph->vertex[z]) * 5;
                        yd2 += 5 + evenToOdd;
                    }
                    else if (graph->vertex[k] > 2)
                        xd2 += 25;
                    else
                        xd2 += 35;

                    yd2 += 30;
                }

                arrowLabel[k]->setPixmap(pic.transformed(trans));
                arrowLabel[k]->setGeometry(QRect(xd2, yd2, 30, 30));
                arrowLabel[k]->setScaledContents(true);
            }
        }
    }

    if (graph->size - 1 > 7)
        QWidget::showFullScreen();

}

Graph::~Graph()
{
    delete ui;
}

void Graph::paintEvent(QPaintEvent *event)
{
    Graphs *test2 = getGraph();
    int count = 0;
    QPainter myline(this);
    // int x1, int y1, int x2, int y2
    // Draws a line from (x1, y1) to (x2, y2).
    int foundConst = 55;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (test2->edges[i][j] == 1) {
                count++;

                int constant = 35 * sqrt(3);
                int x = xCoord[j]+35;
                int x2 = xCoord[i]+35;
                int y = yCoord[j]+35;

                if (test2->edges[i][j] == test2->edges[j][i]) {
//                    if ((test2->size - 1) % 2 == 0 && test2->vertex[i] == (test2->size - 1))
//                        myline.drawLine(x2 - 35 + foundConst, yCoord[i], x - 35 + foundConst, yCoord[j]);
//                    else
                        myline.drawLine(x2, yCoord[i] + foundConst, x, yCoord[j] + foundConst);
//                    foundConst = 55;
                }

//                if ((test2->size - 1) % 2 == 0 && test2->vertex[i] == (test2->size - 1))
//                    myline.drawLine(x2 - 35 + 55, yCoord[i], x - 35 + 55, yCoord[j]);
//                else
                    myline.drawLine(x2, yCoord[i] + 15, x, yCoord[j] + 15);
            }
        }
    }

}

void Graph::on_pushButton_clicked()
{
    hide();
    returnOptions = new Options(this);
    returnOptions->show();
}

