#ifndef NOTIFPAGAMENTOMULTAAPOSDECISAOFINAL_H
#define NOTIFPAGAMENTOMULTAAPOSDECISAOFINAL_H

#include <QWidget>

namespace Ui {
class NotifPagamentoMultaAposDecisaoFinal;
}

class NotifPagamentoMultaAposDecisaoFinal : public QWidget
{
    Q_OBJECT

public:
    explicit NotifPagamentoMultaAposDecisaoFinal(QWidget *parent = nullptr);
    ~NotifPagamentoMultaAposDecisaoFinal();

    QStringList getVariablesFromLayout();
private:
    Ui::NotifPagamentoMultaAposDecisaoFinal *ui;
    QStringList converteQDateEmStringList(QDate date);
};

#endif // NOTIFPAGAMENTOMULTAAPOSDECISAOFINAL_H
