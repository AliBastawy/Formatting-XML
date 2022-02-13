#ifndef COMPRESS_H
#define COMPRESS_H

#include <QMainWindow>

namespace Ui {
class Compress;
}

class Compress : public QMainWindow
{
    Q_OBJECT

public:
    explicit Compress(QWidget *parent = nullptr);
    ~Compress();

private:
    Ui::Compress *ui;
};

#endif // COMPRESS_H
