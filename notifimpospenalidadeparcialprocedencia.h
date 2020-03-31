#ifndef NOTIFIMPOSPENALIDADEPARCIALPROCEDENCIA_H
#define NOTIFIMPOSPENALIDADEPARCIALPROCEDENCIA_H

#include <QWidget>

namespace Ui {
class NotifImposPenalidadeParcialProcedencia;
}

class NotifImposPenalidadeParcialProcedencia : public QWidget
{
    Q_OBJECT

public:
    explicit NotifImposPenalidadeParcialProcedencia(QWidget *parent = nullptr);
    ~NotifImposPenalidadeParcialProcedencia();

    QStringList getVariablesFromLayout();
private slots:
    void on_checkBoxInterdicaoParcialEstab_stateChanged(int);

private:
    Ui::NotifImposPenalidadeParcialProcedencia *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFIMPOSPENALIDADEPARCIALPROCEDENCIA_H
