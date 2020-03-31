#ifndef TERMOINTERDICAOPRODUTOSEMAUTUACAO_H
#define TERMOINTERDICAOPRODUTOSEMAUTUACAO_H

#include <QWidget>

namespace Ui {
class TermoInterdicaoProdutoSemAutuacao;
}

class TermoInterdicaoProdutoSemAutuacao : public QWidget
{
    Q_OBJECT

public:
    explicit TermoInterdicaoProdutoSemAutuacao(QWidget *parent = nullptr);
    ~TermoInterdicaoProdutoSemAutuacao();

    QStringList getVariablesFromLayout();

private:
    Ui::TermoInterdicaoProdutoSemAutuacao *ui;

    QString converteQTimeEmString(QTime time);
    QStringList converteQDateEmStringList(QDate date);
};

#endif // TERMOINTERDICAOPRODUTOSEMAUTUACAO_H
