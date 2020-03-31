#ifndef TERMOVINCULADODESINTERDICAOPRODUTO_H
#define TERMOVINCULADODESINTERDICAOPRODUTO_H

#include <QWidget>

namespace Ui {
class TermoVinculadoDesinterdicaoProduto;
}

class TermoVinculadoDesinterdicaoProduto : public QWidget
{
    Q_OBJECT

public:
    explicit TermoVinculadoDesinterdicaoProduto(QWidget *parent = nullptr);
    ~TermoVinculadoDesinterdicaoProduto();

    QStringList getVariablesFromLayout();
private:
    Ui::TermoVinculadoDesinterdicaoProduto *ui;
    QString converteQTimeEmString(QTime time);
    QStringList converteQDateEmStringList(QDate date);
};

#endif // TERMOVINCULADODESINTERDICAOPRODUTO_H
