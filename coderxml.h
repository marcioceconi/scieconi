#ifndef CODERXML_H
#define CODERXML_H

#include <QWidget>

namespace Ui {
class CoderXML;
}

class CoderXML : public QWidget
{
    Q_OBJECT

public:
    explicit CoderXML(QWidget *parent = nullptr);
    ~CoderXML();

private slots:
    void on_pushButtonConverter_clicked();
    void on_pushButtonLimpar_clicked();

private:
    Ui::CoderXML *ui;
    QStringList separaEspacos(QString stringComEspacos);
};

#endif // CODERXML_H
