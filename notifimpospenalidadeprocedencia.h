#ifndef NOTIFIMPOSPENALIDADEPROCEDENCIA_H
#define NOTIFIMPOSPENALIDADEPROCEDENCIA_H

#include <QWidget>

namespace Ui {
class NotifImposPenalidadeProcedencia;
}

class NotifImposPenalidadeProcedencia : public QWidget
{
    Q_OBJECT

public:
    explicit NotifImposPenalidadeProcedencia(QWidget *parent = nullptr);
    ~NotifImposPenalidadeProcedencia();

    QStringList getVariablesFromLayout();
private slots:
    void on_checkBoxInterdicaoParcialEstab_stateChanged(int);

private:
    Ui::NotifImposPenalidadeProcedencia *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFIMPOSPENALIDADEPROCEDENCIA_H
