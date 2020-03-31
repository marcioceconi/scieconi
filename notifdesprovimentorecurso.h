#ifndef NOTIFDESPROVIMENTORECURSO_H
#define NOTIFDESPROVIMENTORECURSO_H

#include <QWidget>

namespace Ui {
class NotifDesprovimentoRecurso;
}

class NotifDesprovimentoRecurso : public QWidget
{
    Q_OBJECT

public:
    explicit NotifDesprovimentoRecurso(QWidget *parent = nullptr);
    ~NotifDesprovimentoRecurso();

    QStringList getVariablesFromLayout();
private:
    Ui::NotifDesprovimentoRecurso *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFDESPROVIMENTORECURSO_H
