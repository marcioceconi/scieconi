#ifndef TERMOINTERDICAOESTABELECIMENTO_H
#define TERMOINTERDICAOESTABELECIMENTO_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class TermoInterdicaoEstabelecimento;
}

class TermoInterdicaoEstabelecimento : public QWidget
{
    Q_OBJECT

public:
    explicit TermoInterdicaoEstabelecimento(QWidget *parent = nullptr);
    ~TermoInterdicaoEstabelecimento();

    QStringList getSelectedCheckBoxesIrreg();

private slots:
    void setupRoteiroLayout(int index);

    void on_comboBoxRoteiroInspecao_currentIndexChanged(int index);

private:
    Ui::TermoInterdicaoEstabelecimento *ui;

    QList<QCheckBox*> checkBoxIrregList;
    QStringList listaNomesRoteiros, listaUrlRoteiros;
    QStringList listaGruposRoteiro, listaIrregRoteiro, listaDispoRoteiro;
    QVBoxLayout *vboxScrollIrreg;

    QCheckBox* createQCheckBoxWithWordWrap(QWidget *parent, const QString &text);
    void setupRoteirosDisponiveis();
    void apagaLayout(QLayout *layout);
};

#endif // TERMOINTERDICAOESTABELECIMENTO_H
