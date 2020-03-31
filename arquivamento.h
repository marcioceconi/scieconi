#ifndef ARQUIVAMENTO_H
#define ARQUIVAMENTO_H

#include <QWidget>

namespace Ui {
class Arquivamento;
}

class Arquivamento : public QWidget
{
    Q_OBJECT

public:
    explicit Arquivamento(QWidget *parent = nullptr);
    ~Arquivamento();

private:
    Ui::Arquivamento *ui;
};

#endif // ARQUIVAMENTO_H
