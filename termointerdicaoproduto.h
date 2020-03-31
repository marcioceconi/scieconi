#ifndef TERMOINTERDICAOPRODUTO_H
#define TERMOINTERDICAOPRODUTO_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class TermoInterdicaoProduto;
}

class TermoInterdicaoProduto : public QWidget
{
    Q_OBJECT

public:
    explicit TermoInterdicaoProduto(QWidget *parent = nullptr);
    ~TermoInterdicaoProduto();

    QStringList getSelectedCheckBoxesIrreg();

    QStringList getVariablesFromLayout();
private slots:
    void setupRoteiroLayout(int index);
    void on_comboBoxRoteiroInspecao_currentIndexChanged(int index);

private:
    Ui::TermoInterdicaoProduto *ui;

    QList<QCheckBox*> checkBoxIrregList;
    QStringList listaNomesRoteiros, listaUrlRoteiros;
    QStringList listaGruposRoteiro, listaIrregRoteiro, listaDispoRoteiro;
    QVBoxLayout *vboxScrollIrreg;

    QCheckBox* createQCheckBoxWithWordWrap(QWidget *parent, const QString &text);
    void setupRoteirosDisponiveis();
    void apagaLayout(QLayout *layout);
    QStringList converteQDateEmStringList(QDate date);
    QString converteQTimeEmString(QTime time);
};

#endif // TERMOINTERDICAOPRODUTO_H
