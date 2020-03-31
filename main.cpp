#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    w.setWindowState(Qt::WindowState::WindowMaximized);
    w.setWindowTitle("Gerenciamento de Documentos da Vigilância Sanitária");
    w.setWindowIcon(QIcon(":/imagens/hospital.png"));

    w.show();

    return a.exec();
}
