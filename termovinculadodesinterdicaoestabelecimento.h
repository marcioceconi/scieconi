#ifndef TERMOVINCULADODESINTERDICAOESTABELECIMENTO_H
#define TERMOVINCULADODESINTERDICAOESTABELECIMENTO_H

#include <QWidget>

namespace Ui {
class TermoVinculadoDesinterdicaoEstabelecimento;
}

class TermoVinculadoDesinterdicaoEstabelecimento : public QWidget
{
    Q_OBJECT

public:
    explicit TermoVinculadoDesinterdicaoEstabelecimento(QWidget *parent = nullptr);
    ~TermoVinculadoDesinterdicaoEstabelecimento();

    QStringList getVariablesFromLayout();
private:
    Ui::TermoVinculadoDesinterdicaoEstabelecimento *ui;
    QString converteQTimeEmString(QTime time);
    QStringList converteQDateEmStringList(QDate date);
};

#endif // TERMOVINCULADODESINTERDICAOESTABELECIMENTO_H
