#ifndef AVISODERECEBIMENTO_H
#define AVISODERECEBIMENTO_H

#include <QWidget>

namespace Ui {
class AvisodeRecebimento;
}

class AvisodeRecebimento : public QWidget
{
    Q_OBJECT

public:
    explicit AvisodeRecebimento(QWidget *parent = nullptr);
    ~AvisodeRecebimento();

    void setupEquipeDefaultParaAR();
    QString remetenteRazaoSocial, remetenteEndereco, remetenteCidade, remetenteCEP, remetenteEstado;

    QStringList getVariablesFromLayout();
private:
    Ui::AvisodeRecebimento *ui;
};

#endif // AVISODERECEBIMENTO_H
