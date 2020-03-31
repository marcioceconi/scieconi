#ifndef NOTIFPARCIALPROVIMENTORECURSO_H
#define NOTIFPARCIALPROVIMENTORECURSO_H

#include <QWidget>

namespace Ui {
class NotifParcialProvimentoRecurso;
}

class NotifParcialProvimentoRecurso : public QWidget
{
    Q_OBJECT

public:
    explicit NotifParcialProvimentoRecurso(QWidget *parent = nullptr);
    ~NotifParcialProvimentoRecurso();

    QStringList getVariablesFromLayout();
private:
    Ui::NotifParcialProvimentoRecurso *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFPARCIALPROVIMENTORECURSO_H
