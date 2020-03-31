#ifndef ROTEIROINSPECAO_H
#define ROTEIROINSPECAO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class RoteiroInspecao;
}

class RoteiroInspecao : public QWidget
{
    Q_OBJECT

public:
    explicit RoteiroInspecao(QWidget *parent = nullptr);
    ~RoteiroInspecao();

    void createNovoGrupo();
    void createNovoItem();
    void salvarNovoRoteiro();
private:
    Ui::RoteiroInspecao *ui;

    QVBoxLayout *vboxGroupRoteiro;

    QStringList listaItensGrupos;
    QLineEdit *irregLineEdit, *dispoLineEdit, *grupoLineEdit;
    QList<QLineEdit*> listaLineEditPtr;

    QStringList saidaList;
};

#endif // ROTEIROINSPECAO_H
