#ifndef AUTODEINFRACAO_H
#define AUTODEINFRACAO_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class AutodeInfracao;
}

class AutodeInfracao : public QWidget
{
    Q_OBJECT

public:
    explicit AutodeInfracao(QWidget *parent = nullptr);
    ~AutodeInfracao();

    QStringList getSelectedCheckBoxesIrreg();

private slots:
    void setupRoteiroLayout(int index);
    void on_comboBoxRoteiroInspecao_currentIndexChanged(int index);

private:
    Ui::AutodeInfracao *ui;

    QList<QCheckBox*> checkBoxIrregList;
    QStringList listaNomesRoteiros, listaUrlRoteiros;
    QStringList listaGruposRoteiro, listaIrregRoteiro, listaDispoRoteiro;
    QVBoxLayout *vboxScrollIrreg;

    QCheckBox* createQCheckBoxWithWordWrap(QWidget *parent, const QString &text);
    void setupRoteirosDisponiveis();
    void apagaLayout(QLayout *layout);
};

#endif // AUTODEINFRACAO_H
