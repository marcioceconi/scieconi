#ifndef EQUIPE_H
#define EQUIPE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#define STR_EQUAL 0

namespace Ui {
class Equipe;
}

class Equipe : public QWidget
{
    Q_OBJECT

public:
    explicit Equipe(QWidget *parent = nullptr);
    ~Equipe();

    QStringList equipePadraoLista, equipesListaCompleta;

    void getEquipeDefault();
    void salvarEquipe();

private slots:
    void on_pushButtonAlterarBrasao_clicked();
    void on_checkBoxEstadual_stateChanged();
    void on_checkBoxMunicipal_stateChanged();
    void on_pushButtonLimpar_clicked();
    void on_pushButtonSalvar_clicked();
    void on_comboBoxEquipe_currentIndexChanged(int index);
    void on_pushButtonDefinirEquipePadrao_clicked();

private:
    Ui::Equipe *ui;
    void setupEquipesCadastradas();
};

#endif // EQUIPE_H
