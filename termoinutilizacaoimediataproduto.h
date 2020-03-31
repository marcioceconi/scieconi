#ifndef TERMOINUTILIZACAOIMEDIATAPRODUTO_H
#define TERMOINUTILIZACAOIMEDIATAPRODUTO_H

#include <QWidget>

namespace Ui {
class TermoInutilizacaoImediataProduto;
}

class TermoInutilizacaoImediataProduto : public QWidget
{
    Q_OBJECT

public:
    explicit TermoInutilizacaoImediataProduto(QWidget *parent = nullptr);
    ~TermoInutilizacaoImediataProduto();

    QStringList getVariablesFromLayout();
private:
    Ui::TermoInutilizacaoImediataProduto *ui;
    QString converteQTimeEmString(QTime time);
    QStringList converteQDateEmStringList(QDate date);
};

#endif // TERMOINUTILIZACAOIMEDIATAPRODUTO_H
