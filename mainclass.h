#ifndef MAINCLASS_H
#define MAINCLASS_H
#include <QtCore>
#include <QtGui>

class MainClass
{
    static QString xmlText;
public:
    MainClass();

    void setXML(QString xml)
    {
        xmlText = xml;
    }

    QString getXML()
    {
        return xmlText;
    }
};

#endif // MAINCLASS_H
