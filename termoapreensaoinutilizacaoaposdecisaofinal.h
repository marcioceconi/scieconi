#ifndef TERMOAPREENSAOINUTILIZACAOAPOSDECISAOFINAL_H
#define TERMOAPREENSAOINUTILIZACAOAPOSDECISAOFINAL_H

#include <QWidget>

namespace Ui {
class TermoApreensaoInutilizacaoAposDecisaoFinal;
}

class TermoApreensaoInutilizacaoAposDecisaoFinal : public QWidget
{
    Q_OBJECT

public:
    explicit TermoApreensaoInutilizacaoAposDecisaoFinal(QWidget *parent = nullptr);
    ~TermoApreensaoInutilizacaoAposDecisaoFinal();

    QStringList getVariablesFromLayout();
private:
    Ui::TermoApreensaoInutilizacaoAposDecisaoFinal *ui;
    QStringList converteQDateEmStringList(QDate date);
    QString converteQTimeEmString(QTime time);
};

#endif // TERMOAPREENSAOINUTILIZACAOAPOSDECISAOFINAL_H
