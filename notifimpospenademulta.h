#ifndef NOTIFIMPOSPENADEMULTA_H
#define NOTIFIMPOSPENADEMULTA_H

#include <QWidget>

namespace Ui {
class NotifImposPenadeMulta;
}

class NotifImposPenadeMulta : public QWidget
{
    Q_OBJECT

public:
    explicit NotifImposPenadeMulta(QWidget *parent = nullptr);
    ~NotifImposPenadeMulta();

    QStringList getVariablesFromLayout();
private:
    Ui::NotifImposPenadeMulta *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFIMPOSPENADEMULTA_H
