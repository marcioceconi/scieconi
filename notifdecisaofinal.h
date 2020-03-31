#ifndef NOTIFDECISAOFINAL_H
#define NOTIFDECISAOFINAL_H

#include <QWidget>

namespace Ui {
class NotifDecisaoFinal;
}

class NotifDecisaoFinal : public QWidget
{
    Q_OBJECT

public:
    explicit NotifDecisaoFinal(QWidget *parent = nullptr);
    ~NotifDecisaoFinal();

    QStringList getVariablesFromLayout();
private:
    Ui::NotifDecisaoFinal *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFDECISAOFINAL_H
