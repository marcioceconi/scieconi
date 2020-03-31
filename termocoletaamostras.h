#ifndef TERMOCOLETAAMOSTRAS_H
#define TERMOCOLETAAMOSTRAS_H

#include <QWidget>

namespace Ui {
class TermoColetaAmostras;
}

class TermoColetaAmostras : public QWidget
{
    Q_OBJECT

public:
    explicit TermoColetaAmostras(QWidget *parent = nullptr);
    ~TermoColetaAmostras();

    QStringList getVariablesFromLayout();
private slots:
    void on_simCheckBox_stateChanged(int arg1);

    void on_naoCheckBox_stateChanged(int arg1);

private:
    Ui::TermoColetaAmostras *ui;
    QString converteQTimeEmString(QTime time);
    QStringList converteQDateEmStringList(QDate date);
};

#endif // TERMOCOLETAAMOSTRAS_H
