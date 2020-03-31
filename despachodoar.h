#ifndef DESPACHODOAR_H
#define DESPACHODOAR_H

#include <QWidget>

namespace Ui {
class DespachodoAR;
}

class DespachodoAR : public QWidget
{
    Q_OBJECT

public:
    explicit DespachodoAR(QWidget *parent = nullptr);
    ~DespachodoAR();

private:
    Ui::DespachodoAR *ui;
};

#endif // DESPACHODOAR_H
