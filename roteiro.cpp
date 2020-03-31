#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupCriarNovoRoteiro()
{
    tipoSalvar = 888;
    listaGruposRoteiro.clear();
    listaIrregRoteiro.clear();
    listaDispoRoteiro.clear();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (!toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(true);
    }

    scrollRoteiro = new QScrollArea;
    vboxScrollRoteiro = new QVBoxLayout;
    vboxScrollRoteiro->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vboxGrupoRoteiro = new QVBoxLayout;
    vboxGrupoRoteiro->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    apagaLayout(vboxScrollRoteiro);
    apagaLayout(vboxGrupoRoteiro);

    QGroupBox *grupoRoteiro = new QGroupBox;
    grupoRoteiro->setLayout(vboxGrupoRoteiro);

    scrollRoteiro->setLayout(vboxScrollRoteiro);
    vboxTOTAL->addWidget(scrollRoteiro);

    QLineEdit *nomeRoteiroLineEdit = new QLineEdit;
    nomeRoteiroLineEdit->setStyleSheet("QLineEdit{font-size: 11pt;}");
    nomeRoteiroLineEdit->setFixedSize(600, 31);
    nomeRoteiroLineEdit->setPlaceholderText("Insira um nome para o Roteiro de Inspeção ...");
    QLabel *labelNomeRoteiro = new QLabel("Nome do Roteiro:");
    labelNomeRoteiro->setStyleSheet("QLabel{font-weight: bold; font-size: 11pt; color: rgb(255,0,0);}");
    labelNomeRoteiro->setFixedWidth(130);
    QHBoxLayout *hboxNomeRoteiro = new QHBoxLayout;
    hboxNomeRoteiro->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hboxNomeRoteiro->addWidget(labelNomeRoteiro);
    hboxNomeRoteiro->addWidget(nomeRoteiroLineEdit);

    QSpacerItem *spacerItem = new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    spacerItemRoteiro = new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);

    vboxScrollRoteiro->addLayout(hboxNomeRoteiro);
    vboxScrollRoteiro->addSpacerItem(spacerItem);
    vboxScrollRoteiro->addWidget(grupoRoteiro);
    vboxScrollRoteiro->addSpacerItem(spacerItemRoteiro);

    connect(ui->actionNovoGrupo, &QAction::triggered, this, &MainWindow::createNovoGrupo);
    connect(ui->actionNovoItem, &QAction::triggered, this, &MainWindow::createNovoItem);
}

void MainWindow::setupEditarRoteiroExistente()
{
    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(false);
    }

    tipoSalvar = 888;
}

void MainWindow::setupExcluirRoteiroExistente()
{
    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(false);
    }
}

void MainWindow::createNovoGrupo()
{
    QLineEdit *grupoLineEdit = new QLineEdit();
    grupoLineEdit->setStyleSheet("QLineEdit{border: 1px solid black; font-size: 11pt; font-weight: bold; background-color: rgb(82,240,0);}");
    grupoLineEdit->setFixedHeight(31);
    grupoLineEdit->setPlaceholderText("Insira o nome do grupo ...");

    listaGruposRoteiro.append(grupoLineEdit);

    QHBoxLayout *hboxGrupo = new QHBoxLayout;
    hboxGrupo->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hboxGrupo->addWidget(grupoLineEdit);

    vboxGrupoRoteiro->addLayout(hboxGrupo);
}

void MainWindow::createNovoItem()
{
    QLineEdit *irregLineEdit = new QLineEdit();
    irregLineEdit->setFixedSize(600, 20);
    QLineEdit *dispoLineEdit = new QLineEdit();
    dispoLineEdit->setFixedSize(600, 20);

    irregLineEdit->setPlaceholderText("Insira a irregularidade ...");
    dispoLineEdit->setPlaceholderText("Insira os dispositivos legais infringidos ...");

    QHBoxLayout *hboxItem = new QHBoxLayout;
    hboxItem->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hboxItem->addWidget(irregLineEdit);
    hboxItem->addWidget(dispoLineEdit);

    listaIrregRoteiro.append(irregLineEdit);
    listaDispoRoteiro.append(dispoLineEdit);

    vboxGrupoRoteiro->addLayout(hboxItem);
}
