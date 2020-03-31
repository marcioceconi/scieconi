#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "equipe.h"
#include "coderxml.h"
#include "arquivamento.h"
#include "autodeinfracao.h"
#include "autodeinfracaoanalisefiscal.h"
#include "avisoderecebimento.h"
#include "despachodoar.h"
#include "notifdecisaofinal.h"
#include "notifdesprovimentorecurso.h"
#include "notifimpospenademulta.h"
#include "notifimpospenalidadeparcialprocedencia.h"
#include "notifimpospenalidadeprocedencia.h"
#include "notifpagamentomultaaposdecisaofinal.h"
#include "notifparcialprovimentorecurso.h"
#include "termoapreensaoinutilizacaoaposdecisaofinal.h"
#include "termocoletaamostras.h"
#include "termointerdicaoestabelecimento.h"
#include "termointerdicaoproduto.h"
#include "termointerdicaoprodutosemautuacao.h"
#include "termoinutilizacaoimediataproduto.h"
#include "termovinculadodesinterdicaoestabelecimento.h"
#include "termovinculadodesinterdicaoproduto.h"
#include "tipificacao.h"
#include "roteiroinspecao.h"

#include "customtoolbutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vboxTOTAL = new QVBoxLayout;
    vboxTOTAL->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    centralWidget->setLayout(vboxTOTAL);

    menuNovoDocumento = new QMenu;
    menuNovoDocumento->setTitle("Novo");
    menuNovoDocumento->addAction(ui->actionAutodeInfracaoSanitaria);
    menuNovoDocumento->addAction(ui->actionAutodeInfracaoSanitariaAnaliseFiscal);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionTermodeInterdicaoCautelardeEstabelecimento);
    menuNovoDocumento->addAction(ui->actionTermodeInterdicaoCautelardeProdutos);
    menuNovoDocumento->addAction(ui->actionTermodeInterdicaoCautelardeProdutosSemAutuacaoPorDecisaoDVS);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionTermoVinculadodeDesinterdicaodeEstabelecimentos);
    menuNovoDocumento->addAction(ui->actionTermoVinculadodeDesinterdicaodeProdutos);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionTermodeColetadeAmostras);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionTermodeInutilizacaoImediatadeProdutos);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionNotificacaodeDesprovimentodeRecurso);
    menuNovoDocumento->addAction(ui->actionNotificacaodeParcialProvimentodeRecurso);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionNotificacaodeImposicaodePenalidadeProcedenciadaAutuacao);
    menuNovoDocumento->addAction(ui->actionNotificacaodeImposicaodePenalidadeParcialProcedenciadaAutuacao);
    menuNovoDocumento->addAction(ui->actionNotificacaodeImposicaodePenadeMulta);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionNotificacaodeDecisaoFinal);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionNotificacaoParaPagamentodeMultaAposDecisaoFinal);
    menuNovoDocumento->addAction(ui->actionTermodeApreensaoeInutilizacaoAposDecisaoFinal);
    /*menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionAvisodeRecebimento);
    menuNovoDocumento->addAction(ui->actionDespachoParaAR);
    menuNovoDocumento->addSeparator();
    menuNovoDocumento->addAction(ui->actionArquivamentodeProcesso);*/
    novoDocumentoCustomToolButton = new CustomToolButton;
    novoDocumentoCustomToolButton->setMenu(menuNovoDocumento);
    novoDocumentoCustomToolButton->setDefaultAction(ui->actionNovo);
    novoDocumentoCustomToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    novoDocumentoCustomToolButton->setFixedWidth(50);
    novoDocumentoCustomToolButton->setPopupMode(QToolButton::InstantPopup);
    novoDocumentoCustomToolButton->setArrowType(Qt::ArrowType::NoArrow);

    // Seta actions em mainToolBar
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->mainToolBar->addWidget(novoDocumentoCustomToolButton);
    ui->mainToolBar->addAction(ui->actionSalvar);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionCopiar);
    ui->mainToolBar->addAction(ui->actionColar);
    ui->mainToolBar->addAction(ui->actionRecortar);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionDesfazer);
    ui->mainToolBar->addAction(ui->actionRefazer);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionSair);

    if (tipoSalvar == 0) ui->actionSalvar->setEnabled(false);

    // Oculta os QDockWidgets
    ui->dockWidgetEstabelecimento->setVisible(false);
    ui->dockWidgetAutuacao->setVisible(false);
    ui->dockWidgetInterdicao->setVisible(false);
    // Seta o horário e a data atuais nos dockWidgets
    ui->dateEditAutuacao->setDate(QDate::currentDate());
    ui->dateEditInspecao->setDate(QDate::currentDate());
    ui->horarioInspecaoTimeEdit->setTime(QTime::currentTime());
    ui->dateEditInterdicaoCautelar->setDate(QDate::currentDate());
    ui->horarioInterdicaoCautelarTimeEdit->setTime(QTime::currentTime());

    // Cria a barra de ferramentas Roteiro
    toolBarRoteiro = new QToolBar("Barra de Ferramentas Roteiro");
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBarRoteiro);
    toolBarRoteiro->addAction(ui->actionNovoGrupo);
    toolBarRoteiro->addAction(ui->actionNovoItem);
    toolBarRoteiro->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBarRoteiro->setVisible(false);

    // Conecta ações de Copiar, Colar, Recortar, Desfazer e Refazer somente para QLineEdit
    connect(ui->actionCopiar, &QAction::triggered, this, [=]{
        if (qobject_cast<QLineEdit*>(qApp->focusWidget())) {
            QLineEdit *lineEditCheck = qobject_cast<QLineEdit*>(qApp->focusWidget());
            lineEditCheck->copy();
        } else if (qobject_cast<QPlainTextEdit*>(qApp->focusWidget())) {
            QPlainTextEdit *plainTextEditCheck = qobject_cast<QPlainTextEdit*>(qApp->focusWidget());
            plainTextEditCheck->copy();
        }
    });
    connect(ui->actionColar, &QAction::triggered, this, [=]{
        if (qobject_cast<QLineEdit*>(qApp->focusWidget())) {
            QLineEdit *lineEditCheck = qobject_cast<QLineEdit*>(qApp->focusWidget());
            lineEditCheck->paste();
        } else if (qobject_cast<QPlainTextEdit*>(qApp->focusWidget())) {
            QPlainTextEdit *plainTextEditCheck = qobject_cast<QPlainTextEdit*>(qApp->focusWidget());
            plainTextEditCheck->paste();
        }
    });
    connect(ui->actionRecortar, &QAction::triggered, this, [=]{
        if (qobject_cast<QLineEdit*>(qApp->focusWidget())) {
            QLineEdit *lineEditCheck = qobject_cast<QLineEdit*>(qApp->focusWidget());
            lineEditCheck->cut();
        } else if (qobject_cast<QPlainTextEdit*>(qApp->focusWidget())) {
            QPlainTextEdit *plainTextEditCheck = qobject_cast<QPlainTextEdit*>(qApp->focusWidget());
            plainTextEditCheck->cut();
        }
    });
    connect(ui->actionRefazer, &QAction::triggered, this, [=]{
        if (qobject_cast<QLineEdit*>(qApp->focusWidget())) {
            QLineEdit *lineEditCheck = qobject_cast<QLineEdit*>(qApp->focusWidget());
            lineEditCheck->redo();
        } else if (qobject_cast<QPlainTextEdit*>(qApp->focusWidget())) {
            QPlainTextEdit *plainTextEditCheck = qobject_cast<QPlainTextEdit*>(qApp->focusWidget());
            plainTextEditCheck->redo();
        }
    });
    connect(ui->actionDesfazer, &QAction::triggered, this, [=]{
        if (qobject_cast<QLineEdit*>(qApp->focusWidget())) {
            QLineEdit *lineEditCheck = qobject_cast<QLineEdit*>(qApp->focusWidget());
            lineEditCheck->undo();
        } else if (qobject_cast<QPlainTextEdit*>(qApp->focusWidget())) {
            QPlainTextEdit *plainTextEditCheck = qobject_cast<QPlainTextEdit*>(qApp->focusWidget());
            plainTextEditCheck->undo();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setaNovoDefaultOnQToolButton()
{
    novoDocumentoCustomToolButton->setDefaultAction(ui->actionNovo);
}

void MainWindow::apagaLayout(QLayout * layout)
{
    if (! layout)
          return;
       while (auto item = layout->takeAt(0)) {
          delete item->widget();
          apagaLayout(item->layout());
    }
}

void MainWindow::on_actionResetarLayout_triggered()
{
    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    tipoSalvar = 0;
    if (ui->actionSalvar->isEnabled() == true) ui->actionSalvar->setEnabled(false);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);
}

void MainWindow::on_actionSobre_triggered()
{
    static const char messageSobre[] =
        "<p><b>Informações sobre o software</b></p>"

        "<p>Versão: 1.0</p>"

        "<p>Este software foi desenvolvido para geração dos documentos"
        " utilizados pela Vigilância Sanitária do Rio Grande do Sul,"
        " especialmente os documentos para composição do Processo Administrativo"
        " Sanitário.</p>"

        "<p>Os documentos gerados para o Processo Administrativo Sanitário"
        " seguem os modelos apresentados pela Portaria SES/RS nº 50/2017,"
        " em conformidade com as intruções do Manual do Processo Administrativo Sanitário"
        " elaborado pela Secretaria Estadual da Saúde do Rio Grande do Sul</p>"

        "<p>Este software foi desenvolvido pelo Físico <strong>Márcio Ceconi</strong> da Vigilância"
        " Sanitária da 14ª Coordenadoria Regional de Saúde, de Santa Rosa/RS, utilizando a"
        " linguagem de programação C++ e o framework Qt5, além da biblioteca"
        " QuaZIP de Sergey A. Tachenov com o pacote ZIP/UNZIP C de Gilles Vollant (minizip).</p>"

        "<p>Para maiores informações, entre em contato com o desenvolvedor pelo e-mail "
        "<em><span style='color: blue;'>marcio-ceconi@saude.rs.gov.br</span></em> ou telefone (55) 3512-5277 ramal 139.</p>"

        "<p>Este programa é distribuído como software livre sob a licença GNU GPL. Se você não concorda com os "
        "termos da licença, não o utilize.</p>";

    QMessageBox::about(this, QString("Sobre"), messageSobre);
}

void MainWindow::on_actionLicenca_triggered()
{
    static const char messageLicenca[] =
            "<p>Este programa é um software livre; você pode redistribuí-lo e/ou modificá-lo sob os termos da Licença Pública Geral GNU publicada pela Free Software Foundation, em sua versão 3 da Licença ou posterior.</p>"

            "<p>Este programa é distribuído na esperança de que possa ser útil, mas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a Licença Pública Geral GNU para mais detalhes.</p>"

            "<p>Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este programa. Se não a recebeu, veja em <em>http://www.gnu.org/licenses/</em>.</p>"

            "<br/>"

            "<p>This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.</p>"

            "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details."

            "<p>You should have received a copy of the GNU General Public License along with this program.  If not, see <em>https://www.gnu.org/licenses/</em></p>";

    QMessageBox::about(this, QString("Licença"), messageLicenca);
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionSair_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionCadastroEquipe_triggered()
{
    tipoSalvar = 999;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    equipeWidget = new Equipe(this);

    QScrollArea *scrollEquipe = new QScrollArea(this);
    vboxTOTAL->addWidget(scrollEquipe);

    scrollEquipe->setWidget(equipeWidget);
}

void MainWindow::on_actionSalvar_triggered()
{
    if (tipoSalvar == 999) { // Salvar Cadastro de Equipe
        equipeWidget->salvarEquipe();
    } else if (tipoSalvar == 1) { // Auto de Infração Sanitária
        geraDocumento();
    } else if (tipoSalvar == 2) { // Auto de Infração Sanitária - Análise Fiscal
        geraDocumento();
    } else if (tipoSalvar == 3) { // Termo de Interdição Cautelar de Estabelecimentos
        geraDocumento();
    } else if (tipoSalvar == 4) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias
        geraDocumento();
    } else if (tipoSalvar == 5) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias SEM AUTUAÇÃO (POR DECISÃO DA DVS)
        geraDocumento();
    } else if (tipoSalvar == 6) { // Termo Vinculado de Desinterdição de Estabelecimento
        geraDocumento();
    } else if (tipoSalvar == 7) { // Termo Vinculado de Desinterdição de Produtos e/ou Substâncias
        geraDocumento();
    } else if (tipoSalvar == 8) { // Termo de Coleta de Amostras
        geraDocumento();
    } else if (tipoSalvar == 9) { // Termo de Inutilização Imediata de Produtos
        geraDocumento();
    } else if (tipoSalvar == 10) { // Notificação de Desprovimento de Recurso
        geraDocumento();
    } else if (tipoSalvar == 11) { // Notificação de Parcial Provimento de Recurso
        geraDocumento();
    } else if (tipoSalvar == 12) { // Notificação de Imposição de Penalidade - Procedência da Autuação
        geraDocumento();
    } else if (tipoSalvar == 13) { // Notificação de Imposição de Penalidade - Parcial Procedência da Autuação
        geraDocumento();
    } else if (tipoSalvar == 14) { // Notificação de Imposição de Pena de Multa
        geraDocumento();
    } else if (tipoSalvar == 15) { // Notificação de Decisão Final
        geraDocumento();
    } else if (tipoSalvar == 16) { // Notificação para Pagamento de Multa APÓS DECISÃO FINAL
        geraDocumento();
    } else if (tipoSalvar == 17) { // Termo de Apreensão e Inutilização APÓS DECISÃO FINAL
        geraDocumento();
    } else if (tipoSalvar == 18) { // Aviso de Recebimento
        geraDocumento();
    } else if (tipoSalvar == 19) { // Despacho para Inclusão de AR no Processo
        geraDocumento();
    } else if (tipoSalvar == 20) { // Arquivamento de Processo
        geraDocumento();
    } else if (tipoSalvar == 555) { // Relatório de Inspeção
        geraDocumento();
    } else if (tipoSalvar == 888) { // Roteiro de Inspeção
        roteiroInspecao->salvarNovoRoteiro();
    }
}

void MainWindow::on_actionAutodeInfracaoSanitaria_triggered()
{
    tipoSalvar = 1;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Auto de Infração Sanitária");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (!ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(true);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    autoInfracaoWidget = new AutodeInfracao(this);
    vboxTOTAL->addWidget(autoInfracaoWidget);
}

void MainWindow::on_actionAutodeInfracaoSanitariaAnaliseFiscal_triggered()
{
    tipoSalvar = 2;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Auto de Infração Sanitária - Análise Fiscal");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (!ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(true);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    autoInfracaoAnaliseFiscalWidget = new AutodeInfracaoAnaliseFiscal(this);
    vboxTOTAL->addWidget(autoInfracaoAnaliseFiscalWidget);
}

void MainWindow::on_actionTermodeInterdicaoCautelardeEstabelecimento_triggered()
{
    tipoSalvar = 3;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Interdição Cautelar de Estabelecimento");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (!ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(true);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoInterdicaoEstabelecimentoWidget = new TermoInterdicaoEstabelecimento(this);
    vboxTOTAL->addWidget(termoInterdicaoEstabelecimentoWidget);
}

void MainWindow::on_actionTermodeInterdicaoCautelardeProdutos_triggered()
{
    tipoSalvar = 4;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Interdição Cautelar de Produtos e/ou Substâncias");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoInterdicaoProdutoWidget = new TermoInterdicaoProduto(this);
    vboxTOTAL->addWidget(termoInterdicaoProdutoWidget);
}

void MainWindow::on_actionTermodeInterdicaoCautelardeProdutosSemAutuacaoPorDecisaoDVS_triggered()
{
    tipoSalvar = 5;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Interdição Cautelar de Produtos e/ou Substâncias SEM AUTUAÇÃO (POR DECISÃO DA DVS)");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoInterdicaoProdutoSemAutuacaoWidget = new TermoInterdicaoProdutoSemAutuacao(this);
    vboxTOTAL->addWidget(termoInterdicaoProdutoSemAutuacaoWidget);
}

void MainWindow::on_actionTermoVinculadodeDesinterdicaodeEstabelecimentos_triggered()
{
    tipoSalvar = 6;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo Vinculado de Desinterdição de Estabelecimentos");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoVinculadoDesinterdicaoEstabelecimentoWidget = new TermoVinculadoDesinterdicaoEstabelecimento(this);
    vboxTOTAL->addWidget(termoVinculadoDesinterdicaoEstabelecimentoWidget);
}

void MainWindow::on_actionTermoVinculadodeDesinterdicaodeProdutos_triggered()
{
    tipoSalvar = 7;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo Vinculado de Desinterdição de Produtos e/ou Substâncias");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoVinculadoDesinterdicaoProdutoWidget = new TermoVinculadoDesinterdicaoProduto(this);
    vboxTOTAL->addWidget(termoVinculadoDesinterdicaoProdutoWidget);
}

void MainWindow::on_actionTermodeColetadeAmostras_triggered()
{
    tipoSalvar = 8;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Coleta de Amostras");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoColetaAmostrasWidget = new TermoColetaAmostras(this);
    vboxTOTAL->addWidget(termoColetaAmostrasWidget);
}

void MainWindow::on_actionTermodeInutilizacaoImediatadeProdutos_triggered()
{
    tipoSalvar = 9;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Inutilização Imediata de Produtos");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoInutilizacaoImediataProdutoWidget = new TermoInutilizacaoImediataProduto(this);
    vboxTOTAL->addWidget(termoInutilizacaoImediataProdutoWidget);
}

void MainWindow::on_actionNotificacaodeDesprovimentodeRecurso_triggered()
{
    tipoSalvar = 10;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Desprovimento de Recurso");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifDesprovimentoRecursoWidget = new NotifDesprovimentoRecurso(this);
    vboxTOTAL->addWidget(notifDesprovimentoRecursoWidget);
}

void MainWindow::on_actionNotificacaodeParcialProvimentodeRecurso_triggered()
{
    tipoSalvar = 11;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Parcial Provimento de Recurso");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifParcialProvimentoRecursoWidget = new NotifParcialProvimentoRecurso(this);
    vboxTOTAL->addWidget(notifParcialProvimentoRecursoWidget);
}

void MainWindow::on_actionNotificacaodeImposicaodePenalidadeProcedenciadaAutuacao_triggered()
{
    tipoSalvar = 12;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Imposição de Penalidade - Procedência da Autuação");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifImposPenalidadeProcedenciaWidget = new NotifImposPenalidadeProcedencia(this);
    vboxTOTAL->addWidget(notifImposPenalidadeProcedenciaWidget);
}

void MainWindow::on_actionNotificacaodeImposicaodePenalidadeParcialProcedenciadaAutuacao_triggered()
{
    tipoSalvar = 13;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Imposição de Penalidade - Parcial Procedência da Autuação");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifImposPenalidadeParcialProcedenciaWidget = new NotifImposPenalidadeParcialProcedencia(this);
    vboxTOTAL->addWidget(notifImposPenalidadeParcialProcedenciaWidget);
}

void MainWindow::on_actionNotificacaodeImposicaodePenadeMulta_triggered()
{
    tipoSalvar = 14;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Imposição de Pena de Multa");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifImposPenaMultaWidget = new NotifImposPenadeMulta(this);
    vboxTOTAL->addWidget(notifImposPenaMultaWidget);
}

void MainWindow::on_actionNotificacaodeDecisaoFinal_triggered()
{
    tipoSalvar = 15;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação de Decisão Final");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifDecisaoFinalWidget = new NotifDecisaoFinal(this);
    vboxTOTAL->addWidget(notifDecisaoFinalWidget);
}

void MainWindow::on_actionNotificacaoParaPagamentodeMultaAposDecisaoFinal_triggered()
{
    tipoSalvar = 16;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Notificação para Pagamento de Multa APÓS DECISÃO FINAL");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    notifPagamentoMultaAposDecisaoFinalWidget = new NotifPagamentoMultaAposDecisaoFinal(this);
    vboxTOTAL->addWidget(notifPagamentoMultaAposDecisaoFinalWidget);
}

void MainWindow::on_actionTermodeApreensaoeInutilizacaoAposDecisaoFinal_triggered()
{
    tipoSalvar = 17;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Termo de Apreensão e Inutilização APÓS DECISÃO FINAL");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (!ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(true);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    termoApreensaoInutilizacaoAPosDecisaoFinalWidget = new TermoApreensaoInutilizacaoAposDecisaoFinal(this);
    vboxTOTAL->addWidget(termoApreensaoInutilizacaoAPosDecisaoFinalWidget);
}

void MainWindow::on_actionAvisodeRecebimento_triggered()
{
    tipoSalvar = 18;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Aviso de Recebimento");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    // Habilita QDockWidgets Estabelecimento e Autuação
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    avisoRecebimentoWidget = new AvisodeRecebimento(this);
    vboxTOTAL->addWidget(avisoRecebimentoWidget);

    // Seta Equipe Default no AR
    if (defaultEquipeTipo == "Estadual") {
        if (defaultEquipeNome == "Centro Estadual de Vigilância em Saúde") {
            avisoRecebimentoWidget->remetenteRazaoSocial = QString("%1 do Centro Estadual de Vigilância em Saúde").arg(defaultEquipeSetor);
        } else {
            avisoRecebimentoWidget->remetenteRazaoSocial = QString("%1 da %2").arg(defaultEquipeSetor).arg(defaultEquipeNome);
        }
    } else {
        avisoRecebimentoWidget->remetenteRazaoSocial = QString("%1 do Município de %2").arg(defaultEquipeSetor).arg(defaultEquipeCidade);
    }
    if (defaultEquipeComplemento.isEmpty()) {
        avisoRecebimentoWidget->remetenteEndereco = QString("%1, %2, %3").arg(defaultEquipeLogradouro).arg(defaultEquipeNumero).arg(defaultEquipeBairro);
    } else {
        avisoRecebimentoWidget->remetenteEndereco = QString("%1, %2, %3, %4").arg(defaultEquipeLogradouro).arg(defaultEquipeNumero).arg(defaultEquipeComplemento).arg(defaultEquipeBairro);
    }
    avisoRecebimentoWidget->remetenteCidade = defaultEquipeCidade;
    avisoRecebimentoWidget->remetenteEstado = defaultEquipeEstado;
    avisoRecebimentoWidget->remetenteCEP = defaultEquipeCEP;
    avisoRecebimentoWidget->setupEquipeDefaultParaAR();
}

void MainWindow::on_actionDespachoParaAR_triggered()
{
    tipoSalvar = 19;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Despacho para Inclusão de AR no Processo");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    despachoARWidget = new DespachodoAR(this);
    vboxTOTAL->addWidget(despachoARWidget);
}

void MainWindow::on_actionArquivamentodeProcesso_triggered()
{
    tipoSalvar = 20;
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);
    ui->statusBar->showMessage("Arquivamento de Processo");
    getEquipeDefaultWithoutInterface();

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);

    arquivamentoWidget = new Arquivamento(this);
    vboxTOTAL->addWidget(arquivamentoWidget);
}

void MainWindow::on_actionExibir_Ocultar_DockEstab_triggered()
{
    if (ui->dockWidgetEstabelecimento->isVisible()) {
        ui->dockWidgetEstabelecimento->setVisible(false);
    } else {
        ui->dockWidgetEstabelecimento->setVisible(true);
    }
}

void MainWindow::on_actionExibir_Ocultar_DockAutuacao_triggered()
{
    if (ui->dockWidgetAutuacao->isVisible()) {
        ui->dockWidgetAutuacao->setVisible(false);
    } else {
        ui->dockWidgetAutuacao->setVisible(true);
    }
}

void MainWindow::on_actionExibir_Ocultar_DockInterdicaoCautelar_triggered()
{
    if (ui->dockWidgetInterdicao->isVisible()) {
        ui->dockWidgetInterdicao->setVisible(false);
    } else {
        ui->dockWidgetInterdicao->setVisible(true);
    }
}

void MainWindow::on_actionExibir_Ocultar_Barra_de_Ferramentas_Principal_triggered()
{
    if (ui->mainToolBar->isVisible()) {
        ui->mainToolBar->setVisible(false);
    } else {
        ui->mainToolBar->setVisible(true);
    }
}

void MainWindow::getEquipeDefaultWithoutInterface()
{
    QFile arq("equipes.config");

    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipes.config");
        return;
    }

    QTextStream in(&arq);
    QString line = in.readLine();
    arq.close();

    QStringList colunas;
    colunas = line.split(";");

    defaultEquipeTipo = colunas[0];
    defaultEquipeNome = colunas[1];
    defaultEquipeLogradouro = colunas[2];
    defaultEquipeNumero = colunas[3];
    defaultEquipeComplemento = colunas[4];
    defaultEquipeBairro = colunas[5];
    defaultEquipeCidade = colunas[6];
    defaultEquipeEstado = colunas[7];
    defaultEquipeCEP = colunas[8];
    defaultEquipeEmail = colunas[9];
    defaultEquipeNucleo = colunas[10];
    defaultEquipeSetor = colunas[11];
    defaultEquipeBrasao = colunas[12];

    if (defaultEquipeNome == "CEVS (Porto Alegre)") {
        defaultEquipeNome = QString("Centro Estadual de Vigilância em Saúde");
    } else if (defaultEquipeNome == "1ª CRS (Porto Alegre)") {
        defaultEquipeNome = QString("1ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "2ª CRS (Porto Alegre)") {
        defaultEquipeNome = QString("2ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "3ª CRS (Pelotas)") {
        defaultEquipeNome = QString("3ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "4ª CRS (Santa Maria)") {
        defaultEquipeNome = QString("4ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "5ª CRS (Caxias do Sul)") {
        defaultEquipeNome = QString("5ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "6ª CRS (Passo Fundo)") {
        defaultEquipeNome = QString("6ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "7ª CRS (Bagé)") {
        defaultEquipeNome = QString("7ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "8ª CRS (Cachoeira do Sul)") {
        defaultEquipeNome = QString("8ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "9ª CRS (Cruz Alta)") {
        defaultEquipeNome = QString("9ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "10ª CRS (Alegrete)") {
        defaultEquipeNome = QString("10ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "11ª CRS (Erechim)") {
        defaultEquipeNome = QString("11ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "12ª CRS (Santo Ângelo)") {
        defaultEquipeNome = QString("12ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "13ª CRS (Santa Cruz do Sul)") {
        defaultEquipeNome = QString("13ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "14ª CRS (Santa Rosa)") {
        defaultEquipeNome = QString("14ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "15ª CRS (Palmeiras das Missões)") {
        defaultEquipeNome = QString("15ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "16ª CRS (Lajeado)") {
        defaultEquipeNome = QString("16ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "17ª CRS (Ijuí)") {
        defaultEquipeNome = QString("17ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "18ª CRS (Osório)") {
        defaultEquipeNome = QString("18ª Coordenadoria Regional de Saúde");
    } else if (defaultEquipeNome == "19ª CRS (Frederico Westphalen)") {
        defaultEquipeNome = QString("19ª Coordenadoria Regional de Saúde");
    }
}

void MainWindow::on_actionCoder_XML_triggered()
{
    CoderXML *coderXML = new CoderXML(this);
    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) toolBarRoteiro->setVisible(false);
    vboxTOTAL->addWidget(coderXML);
}

void MainWindow::on_numAutoInfracaoLineEdit_textChanged(const QString &arg1)
{
    ui->numAutoLineEdit->setText(arg1);
}

void MainWindow::on_numAutoLineEdit_textChanged(const QString &arg1)
{
    ui->numAutoInfracaoLineEdit->setText(arg1);
}

void MainWindow::on_nomeServidorLineEdit_textChanged(const QString &arg1)
{
    ui->nomeServidorDockInterdicaoLineEdit->setText(arg1);
}

void MainWindow::on_nomeServidorDockInterdicaoLineEdit_textChanged(const QString &arg1)
{
    ui->nomeServidorLineEdit->setText(arg1);
}

void MainWindow::on_IDServidorLineEdit_textChanged(const QString &arg1)
{
    ui->IDServidorDockInterdicaoLineEdit->setText(arg1);
}

void MainWindow::on_IDServidorDockInterdicaoLineEdit_textChanged(const QString &arg1)
{
    ui->IDServidorLineEdit->setText(arg1);
}

void MainWindow::on_pushButtonLimparDockEstab_clicked()
{
    ui->cnpjLineEdit->clear();
    ui->razaoSocialLineEdit->clear();
    ui->ramoLineEdit->clear();
    ui->enderecoLineEdit->clear();
    ui->cidadeLineEdit->clear();
    ui->cepLineEdit->clear();
    ui->numAlvaraLineEdit->clear();
}

void MainWindow::on_pushButtonLimparDockAutuacao_clicked()
{
    ui->setorEstabLineEdit->clear();
    ui->numAutoLineEdit->clear();
    ui->dateEditAutuacao->setDate(QDate::currentDate());
    ui->dateEditInspecao->setDate(QDate::currentDate());
    ui->horarioInspecaoTimeEdit->setTime(QTime::currentTime());
    ui->nomeServidorLineEdit->clear();
    ui->IDServidorLineEdit->clear();
}

void MainWindow::on_pushButtonLimparDockInterdicao_clicked()
{
    ui->numTermoInterdCautelarLineEdit->clear();
    ui->numAutoInfracaoLineEdit->clear();
    ui->dateEditInterdicaoCautelar->setDate(QDate::currentDate());
    ui->horarioInterdicaoCautelarTimeEdit->setTime(QTime::currentTime());
    ui->setorEstabDockInterdicaoLineEdit->clear();
    ui->finalidadeSuspensaoLineEdit->clear();
    ui->nomeServidorDockInterdicaoLineEdit->clear();
    ui->IDServidorDockInterdicaoLineEdit->clear();
}

void MainWindow::on_actionCriarNovoRoteiro_triggered()
{
    tipoSalvar = 888;

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (!toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(true);
    }
    if (!ui->actionSalvar->isEnabled()) ui->actionSalvar->setEnabled(true);

    roteiroInspecao = new RoteiroInspecao(this);
    vboxTOTAL->addWidget(roteiroInspecao);
}

void MainWindow::on_actionEditarRoteiroExistente_triggered()
{
    tipoSalvar = 877;

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(false);
    }
}

void MainWindow::on_actionExcluirRoteiroExistente_triggered()
{
    tipoSalvar = 866;

    if (!vboxTOTAL->isEmpty()) apagaLayout(vboxTOTAL);
    if (!ui->mainToolBar->isVisible()) ui->mainToolBar->setVisible(true);
    if (ui->dockWidgetEstabelecimento->isVisible()) ui->dockWidgetEstabelecimento->setVisible(false);
    if (ui->dockWidgetAutuacao->isVisible()) ui->dockWidgetAutuacao->setVisible(false);
    if (ui->dockWidgetInterdicao->isVisible()) ui->dockWidgetInterdicao->setVisible(false);
    if (toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(false);
    }
}

void MainWindow::on_actionExibir_Ocultar_Barra_de_Ferramentas_Roteiro_triggered()
{
    if (toolBarRoteiro->isVisible()) {
        toolBarRoteiro->setVisible(false);
    } else {
        toolBarRoteiro->setVisible(true);
    }
}

void MainWindow::on_actionNovoGrupo_triggered()
{
    if (tipoSalvar == 888) { // Não faz nada se não for criação de novo roteiro
        roteiroInspecao->createNovoGrupo();
    }
}

void MainWindow::on_actionNovoItem_triggered()
{
    if (tipoSalvar == 888) { // Não faz nada se não for criação de novo roteiro
        roteiroInspecao->createNovoItem();
    }
}
