#ifndef AUTODEINFRACAOANALISEFISCAL_H
#define AUTODEINFRACAOANALISEFISCAL_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class AutodeInfracaoAnaliseFiscal;
}

class AutodeInfracaoAnaliseFiscal : public QWidget
{
    Q_OBJECT

public:
    explicit AutodeInfracaoAnaliseFiscal(QWidget *parent = nullptr);
    ~AutodeInfracaoAnaliseFiscal();

    QStringList getSelectedCheckBoxesIrreg();

private slots:
    void setupRoteiroLayout(int index);

    void on_comboBoxRoteiroInspecao_currentIndexChanged(int index);

private:
    Ui::AutodeInfracaoAnaliseFiscal *ui;

    QList<QCheckBox*> checkBoxIrregList;
    QStringList listaNomesRoteiros, listaUrlRoteiros;
    QStringList listaGruposRoteiro, listaIrregRoteiro, listaDispoRoteiro;
    QVBoxLayout *vboxScrollIrreg;

    QCheckBox* createQCheckBoxWithWordWrap(QWidget *parent, const QString &text);
    void setupRoteirosDisponiveis();
    void apagaLayout(QLayout *layout);
};

#endif // AUTODEINFRACAOANALISEFISCAL_H
