#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::geraDocumento()
{
    QString fn;

    if (tipoSalvar == 1) { // Auto de Infração Sanitária
        if (readVariaveisNecessarias() == true) {
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                QMessageBox mensagemBox;
                mensagemBox.setWindowTitle("Atenção");
                mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção</strong></FONT>."));
                mensagemBox.exec();
            } else {
                setupWidget6437();
            }
        }
    } else if (tipoSalvar == 2) { // Auto de Infração Sanitária - Análise Fiscal
        if (readVariaveisNecessarias() == true) {
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                QMessageBox mensagemBox;
                mensagemBox.setWindowTitle("Atenção");
                mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção</strong></FONT>."));
                mensagemBox.exec();
            } else {
                fn.clear();
                fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
                if (fn.isEmpty()) {
                    return;
                } else {
                    if (fn.endsWith(".docx")) {
                        autodeInfracaoAnaliseFiscalDOCX(fn);
                    } else if (fn.endsWith(".odt")) {
                        autodeInfracaoAnaliseFiscalODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 3) { // Termo de Interdição Cautelar de Estabelecimentos
        if (readVariaveisNecessarias() == true) {
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                QMessageBox mensagemBox;
                mensagemBox.setWindowTitle("Atenção");
                mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção</strong></FONT>."));
                mensagemBox.exec();
            } else {
                fn.clear();
                fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
                if (fn.isEmpty()) {
                    return;
                } else {
                    if (fn.endsWith(".docx")) {
                        termoInderdicaoCautelarEstabelecimentoDOCX(fn);
                    } else if (fn.endsWith(".odt")) {
                        termoInderdicaoCautelarEstabelecimentoODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 4) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias
        if (readVariaveisNecessarias() == true) {
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                QMessageBox mensagemBox;
                mensagemBox.setWindowTitle("Atenção");
                mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção</strong></FONT>."));
                mensagemBox.exec();
            } else {
                fn.clear();
                fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
                if (fn.isEmpty()) {
                    return;
                } else {
                    if (fn.endsWith(".docx")) {
                        if (usarVerso == "sim" || usarVerso == "Sim") {
                            termoInderdicaoCautelarProdutoDOCX(fn);
                        } else {
                            termoInderdicaoCautelarProdutoSemVersoDOCX(fn);
                        }
                    } else if (fn.endsWith(".odt")) {
                        if (usarVerso == "sim" || usarVerso == "Sim") {
                            termoInderdicaoCautelarProdutoODT(fn);
                        } else {
                            termoInderdicaoCautelarProdutoSemVersoODT(fn);
                        }

                    }
                }
            }
        }
    } else if (tipoSalvar == 5) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias SEM AUTUAÇÃO (POR DECISÃO DA DVS)
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoInderdicaoCautelarProdutoSemAutuacaoDOCX(fn);
                    } else {
                        termoInderdicaoCautelarProdutoSemAutuacaoSemVersoDOCX(fn);
                    }
                } else if (fn.endsWith(".odt")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoInderdicaoCautelarProdutoSemAutuacaoODT(fn);
                    } else {
                        termoInderdicaoCautelarProdutoSemAutuacaoSemVersoODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 6) { // Termo Vinculado de Desinterdição de Estabelecimento
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    termoVinculadoDesinterdicaoEstabelecimentoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    termoVinculadoDesinterdicaoEstabelecimentoODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 7) { // Termo Vinculado de Desinterdição de Produtos e/ou Substâncias
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoVinculadoDesinterdicaoProdutoDOCX(fn);
                    } else {
                        termoVinculadoDesinterdicaoProdutoSemVersoDOCX(fn);
                    }
                } else if (fn.endsWith(".odt")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoVinculadoDesinterdicaoProdutoODT(fn);
                    } else {
                        termoVinculadoDesinterdicaoProdutoSemVersoODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 8) { // Termo de Coleta de Amostras
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    termoColetaAmostrasDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    termoColetaAmostrasODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 9) { // Termo de Inutilização Imediata de Produtos
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoInutilizacaoImediataProdutosDOCX(fn);
                    } else {
                        termoInutilizacaoImediataProdutosSemVersoDOCX(fn);
                    }
                } else if (fn.endsWith(".odt")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoInutilizacaoImediataProdutosSemVersoODT(fn);
                    } else {
                        termoInutilizacaoImediataProdutosSemVersoODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 10) { // Notificação de Desprovimento de Recurso
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoDesprovimentoRecursoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoDesprovimentoRecursoODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 11) { // Notificação de Parcial Provimento de Recurso
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoParcialProvimentoRecursoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoParcialProvimentoRecursoODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 12) { // Notificação de Imposição de Penalidade - Procedência da Autuação
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoImposPenalidadeProcedenciaDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoImposPenalidadeProcedenciaODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 13) { // Notificação de Imposição de Penalidade - Parcial Procedência da Autuação
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoImposPenalidadeParcialProcedenciaDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoImposPenalidadeParcialProcedenciaODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 14) { // Notificação de Imposição de Pena de Multa
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoImposPenaMultaDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoImposPenaMultaODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 15) { // Notificação de Decisão Final
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoDecisaoFinalDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoDecisaoFinalODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 16) { // Notificação para Pagamento de Multa APÓS DECISÃO FINAL
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    notificacaoPagamentoMultaAposDecisaoFinalDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    notificacaoPagamentoMultaAposDecisaoFinalODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 17) { // Termo de Apreensão e Inutilização APÓS DECISÃO FINAL
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoApreensaoInutilizacaoAposDecisaoFinalDOCX(fn);
                    } else {
                        termoApreensaoInutilizacaoAposDecisaoFinalSemVersoDOCX(fn);
                    }
                } else if (fn.endsWith(".odt")) {
                    if (usarVerso == "sim" || usarVerso == "Sim") {
                        termoApreensaoInutilizacaoAposDecisaoFinalODT(fn);
                    } else {
                        termoApreensaoInutilizacaoAposDecisaoFinalSemVersoODT(fn);
                    }
                }
            }
        }
    } else if (tipoSalvar == 18) { // Aviso de Recebimento
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    avisoRecebimentoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    avisoRecebimentoODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 19) { // Despacho para Inclusão de AR no Processo
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    despachoARDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    despachoARODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 20) { // Arquivamento de Processo
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    arquivamentoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    arquivamentoODT(fn);
                }
            }
        }
    } else if (tipoSalvar == 555) { // Relatório de Inspeção
        if (readVariaveisNecessarias() == true) {
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {

                } else if (fn.endsWith(".odt")) {

                }
            }
        }
    }
}

QStringList MainWindow::converteQDateEmStringList(QDate date)
{
    QString diaSaida, mesSaida, anoSaida;
    diaSaida.clear();
    mesSaida.clear();
    anoSaida.clear();
    QString data1 = date.toString();
    QStringList colunasData1 = {""};
    colunasData1 = data1.split(" ");
    diaSaida = colunasData1[2];
    if (diaSaida.count() == 1) diaSaida = QString("0%1").arg(diaSaida);
    mesSaida = colunasData1[1];
    anoSaida = colunasData1[3];
    if (QString::compare(mesSaida, "jan") == STR_EQUAL) mesSaida = "janeiro";
    if (QString::compare(mesSaida, "fev") == STR_EQUAL || QString::compare(mesSaida, "feb") == STR_EQUAL) mesSaida = "fevereiro";
    if (QString::compare(mesSaida, "mar") == STR_EQUAL) mesSaida = "março";
    if (QString::compare(mesSaida, "abr") == STR_EQUAL || QString::compare(mesSaida, "apr") == STR_EQUAL) mesSaida = "abril";
    if (QString::compare(mesSaida, "mai") == STR_EQUAL || QString::compare(mesSaida, "may") == STR_EQUAL) mesSaida = "maio";
    if (QString::compare(mesSaida, "jun") == STR_EQUAL) mesSaida = "junho";
    if (QString::compare(mesSaida, "jul") == STR_EQUAL) mesSaida = "julho";
    if (QString::compare(mesSaida, "ago") == STR_EQUAL || QString::compare(mesSaida, "aug") == STR_EQUAL) mesSaida = "agosto";
    if (QString::compare(mesSaida, "set") == STR_EQUAL || QString::compare(mesSaida, "sep") == STR_EQUAL) mesSaida = "setembro";
    if (QString::compare(mesSaida, "out") == STR_EQUAL || QString::compare(mesSaida, "oct") == STR_EQUAL) mesSaida = "outubro";
    if (QString::compare(mesSaida, "nov") == STR_EQUAL) mesSaida = "novembro";
    if (QString::compare(mesSaida, "dez") == STR_EQUAL || QString::compare(mesSaida, "dec") == STR_EQUAL) mesSaida = "dezembro";
    QStringList dataListSaida = {diaSaida, mesSaida, anoSaida};
    return dataListSaida;
}

QString MainWindow::converteQTimeEmString(QTime time)
{
    QString horarioSaida;
    horarioSaida.clear();
    QString horarioStr;
    horarioStr = time.toString();
    QStringList colunasHora = {""};
    colunasHora = horarioStr.split(":");
    if (QString::compare(colunasHora[1], "00") == STR_EQUAL || QString::compare(colunasHora[1], "0") == STR_EQUAL) {
        if (QString::compare(colunasHora[0], "01") == STR_EQUAL || QString::compare(colunasHora[0], "1") == STR_EQUAL) {
            horarioSaida = QString("%1 hora").arg(colunasHora[0]);
        } else {
            horarioSaida = QString("%1 horas").arg(colunasHora[0]);
        }
    } else {
        if (QString::compare(colunasHora[0], "01") == STR_EQUAL || QString::compare(colunasHora[0], "1") == STR_EQUAL) {
            if (QString::compare(colunasHora[1], "01") == STR_EQUAL || QString::compare(colunasHora[1], "1") == STR_EQUAL) {
                horarioSaida = QString("%1 hora e %2 minuto").arg(colunasHora[0]).arg(colunasHora[1]);
            } else {
                horarioSaida = QString("%1 hora e %2 minutos").arg(colunasHora[0]).arg(colunasHora[1]);
            }
        } else {
            if (QString::compare(colunasHora[1], "01") == STR_EQUAL || QString::compare(colunasHora[1], "1") == STR_EQUAL) {
                horarioSaida = QString("%1 horas e %2 minuto").arg(colunasHora[0]).arg(colunasHora[1]);
            } else {
                horarioSaida = QString("%1 horas e %2 minutos").arg(colunasHora[0]).arg(colunasHora[1]);
            }
        }
    }
    return horarioSaida;
}

bool MainWindow::readVariaveisNecessarias()
{
    if (tipoSalvar == 1) { // Auto de Infração Sanitária
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        // QDockWidget Autuação
        estabSetorAutuado = ui->setorEstabLineEdit->text();
        numAuto = ui->numAutoLineEdit->text();
        QStringList dataAutoRead = converteQDateEmStringList(ui->dateEditAutuacao->date());
        diaAuto = dataAutoRead[0];
        mesAuto = dataAutoRead[1];
        anoAuto = dataAutoRead[2];
        QStringList dataInspRead = converteQDateEmStringList(ui->dateEditInspecao->date());
        diaInsp = dataInspRead[0];
        mesInsp = dataInspRead[1];
        anoInsp = dataInspRead[2];
        horarioInsp = converteQTimeEmString(ui->horarioInspecaoTimeEdit->time());
        nomeServidor = ui->nomeServidorLineEdit->text();
        idServidor = ui->IDServidorLineEdit->text();
        irregularidades = autoInfracaoWidget->getSelectedCheckBoxesIrreg()[0];
        dispositivos = autoInfracaoWidget->getSelectedCheckBoxesIrreg()[1];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (estabSetorAutuado.isEmpty()) dadosFaltantes.append("Setor(es) do Estabelecimento");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaInsp.isEmpty() || mesInsp.isEmpty() || anoInsp.isEmpty()) dadosFaltantes.append("Data da Inspeção");
        if (horarioInsp.isEmpty()) dadosFaltantes.append("Horário da Inspeção");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1. Além disso, <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção.</strong></FONT>").arg(saidaFaltantes));
            } else {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            }
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 2) { // Auto de Infração Sanitária - Análise Fiscal
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        // QDockWidget Autuação
        estabSetorAutuado = ui->setorEstabLineEdit->text();
        numAuto = ui->numAutoLineEdit->text();
        QStringList dataAutoRead = converteQDateEmStringList(ui->dateEditAutuacao->date());
        diaAuto = dataAutoRead[0];
        mesAuto = dataAutoRead[1];
        anoAuto = dataAutoRead[2];
        QStringList dataInspRead = converteQDateEmStringList(ui->dateEditInspecao->date());
        diaInsp = dataInspRead[0];
        mesInsp = dataInspRead[1];
        anoInsp = dataInspRead[2];
        horarioInsp = converteQTimeEmString(ui->horarioInspecaoTimeEdit->time());
        nomeServidor = ui->nomeServidorLineEdit->text();
        idServidor = ui->IDServidorLineEdit->text();
        irregularidades = autoInfracaoAnaliseFiscalWidget->getSelectedCheckBoxesIrreg()[0];
        dispositivos = autoInfracaoAnaliseFiscalWidget->getSelectedCheckBoxesIrreg()[1];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (estabSetorAutuado.isEmpty()) dadosFaltantes.append("Setor(es) do Estabelecimento");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaInsp.isEmpty() || mesInsp.isEmpty() || anoInsp.isEmpty()) dadosFaltantes.append("Data da Inspeção");
        if (horarioInsp.isEmpty()) dadosFaltantes.append("Horário da Inspeção");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1. Além disso, <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção.</strong></FONT>").arg(saidaFaltantes));
            } else {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            }
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 3) { // Termo de Interdição Cautelar de Estabelecimentos
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        // QDockWidget Interdição Cautelar
        numTermoInterd = ui->numTermoInterdCautelarLineEdit->text();
        numAuto = ui->numAutoInfracaoLineEdit->text();
        QStringList dataInterdRead = converteQDateEmStringList(ui->dateEditInterdicaoCautelar->date());
        diaInterd = dataInterdRead[0];
        mesInterd = dataInterdRead[1];
        anoInterd = dataInterdRead[2];
        horarioInterd = converteQTimeEmString(ui->horarioInterdicaoCautelarTimeEdit->time());
        estabSetorAutuado = ui->setorEstabDockInterdicaoLineEdit->text();
        finalidadeSuspensao = ui->finalidadeSuspensaoLineEdit->text();
        nomeServidor = ui->nomeServidorDockInterdicaoLineEdit->text();
        idServidor = ui->IDServidorDockInterdicaoLineEdit->text();
        irregularidades = termoInterdicaoEstabelecimentoWidget->getSelectedCheckBoxesIrreg()[0];
        dispositivos = termoInterdicaoEstabelecimentoWidget->getSelectedCheckBoxesIrreg()[1];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoInterd.isEmpty()) dadosFaltantes.append("Número do Termo de Interdição Cautelar");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaInterd.isEmpty() || mesInterd.isEmpty() || anoInterd.isEmpty()) dadosFaltantes.append("Data da Interdição Cautelar");
        if (horarioInterd.isEmpty()) dadosFaltantes.append("Horário da Interdição Cautelar");
        if (estabSetorAutuado.isEmpty()) dadosFaltantes.append("Setor/Serviço Interditado");
        if (finalidadeSuspensao.isEmpty()) dadosFaltantes.append("Finalidade da Suspensão");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1. Além disso, <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção.</strong></FONT>").arg(saidaFaltantes));
            } else {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            }
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 4) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numTermoInterd = termoInterdicaoProdutoWidget->getVariablesFromLayout()[0];
        numAuto = termoInterdicaoProdutoWidget->getVariablesFromLayout()[1];
        nomeServidor = termoInterdicaoProdutoWidget->getVariablesFromLayout()[2];
        idServidor = termoInterdicaoProdutoWidget->getVariablesFromLayout()[3];
        nomeDepositario = termoInterdicaoProdutoWidget->getVariablesFromLayout()[4];
        enderecoDepositario = termoInterdicaoProdutoWidget->getVariablesFromLayout()[5];
        usarVerso = termoInterdicaoProdutoWidget->getVariablesFromLayout()[6];
        produtosInterditados = termoInterdicaoProdutoWidget->getVariablesFromLayout()[7];
        diaInterd = termoInterdicaoProdutoWidget->getVariablesFromLayout()[8];
        mesInterd = termoInterdicaoProdutoWidget->getVariablesFromLayout()[9];
        anoInterd = termoInterdicaoProdutoWidget->getVariablesFromLayout()[10];
        horarioInterd = termoInterdicaoProdutoWidget->getVariablesFromLayout()[11];
        irregularidades = termoInterdicaoProdutoWidget->getSelectedCheckBoxesIrreg()[0];
        dispositivos = termoInterdicaoProdutoWidget->getSelectedCheckBoxesIrreg()[1];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoInterd.isEmpty()) dadosFaltantes.append("Número do Termo de Interdição Cautelar");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaInterd.isEmpty() || mesInterd.isEmpty() || anoInterd.isEmpty()) dadosFaltantes.append("Data da Interdição Cautelar");
        if (horarioInterd.isEmpty()) dadosFaltantes.append("Horário da Interdição Cautelar");
        if (nomeDepositario.isEmpty()) dadosFaltantes.append("Nome do Depositário");
        if (enderecoDepositario.isEmpty()) dadosFaltantes.append("Endereço do Depositário");
        if (produtosInterditados.isEmpty()) dadosFaltantes.append("Produtos Interditados");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            if (irregularidades.isEmpty() || dispositivos.isEmpty()) {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1. Além disso, <FONT COLOR='#ff0000'><strong>no mínimo 1 (uma) irregularidade deve ser selecionada no Roteiro de Inspeção.</strong></FONT>").arg(saidaFaltantes));
            } else {
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            }
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 5) { // Termo de Interdição Cautelar de Produtos e/ou Substâncias SEM AUTUAÇÃO (POR DECISÃO DA DVS)
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numTermoInterd = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[0];
        nomeServidor = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[1];
        idServidor = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[2];
        documentoDVS = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[3];
        usarVerso = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[4];
        produtosInterditados = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[5];
        diaInterd = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[6];
        mesInterd = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[7];
        anoInterd = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[8];
        horarioInterd = termoInterdicaoProdutoSemAutuacaoWidget->getVariablesFromLayout()[9];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoInterd.isEmpty()) dadosFaltantes.append("Número do Termo de Interdição Cautelar");
        if (documentoDVS.isEmpty()) dadosFaltantes.append("Documento da DVS determinando a Interdição Cautelar");
        if (diaInterd.isEmpty() || mesInterd.isEmpty() || anoInterd.isEmpty()) dadosFaltantes.append("Data da Interdição Cautelar");
        if (horarioInterd.isEmpty()) dadosFaltantes.append("Horário da Interdição Cautelar");
        if (produtosInterditados.isEmpty()) dadosFaltantes.append("Produtos Interditados");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 6) { // Termo Vinculado de Desinterdição de Estabelecimento
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numTermoInterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[0];
        numProcesso = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[1];
        estabSetorDesinterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[2];
        nomeServidor = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[3];
        idServidor = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[4];
        diaDesinterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[5];
        mesDesinterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[6];
        anoDesinterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[7];
        horarioDesinterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[8];
        diaInterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[9];
        mesInterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[10];
        anoInterd = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[11];
        irregularidadesSanadas = termoVinculadoDesinterdicaoEstabelecimentoWidget->getVariablesFromLayout()[12];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoInterd.isEmpty()) dadosFaltantes.append("Número do Termo de Interdição Cautelar");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (estabSetorDesinterd.isEmpty()) dadosFaltantes.append("Sala/Serviço/Setor Desinterditado");
        if (diaDesinterd.isEmpty() || mesDesinterd.isEmpty() || anoDesinterd.isEmpty()) dadosFaltantes.append("Data da Desinterdição Cautelar");
        if (horarioDesinterd.isEmpty()) dadosFaltantes.append("Horário da Desinterdição Cautelar");
        if (diaInterd.isEmpty() || mesInterd.isEmpty() || anoInterd.isEmpty()) dadosFaltantes.append("Data da Interdição Cautelar");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (irregularidadesSanadas.isEmpty()) dadosFaltantes.append("Irregularidades Sanadas");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 7) { // Termo Vinculado de Desinterdição de Produtos e/ou Substâncias
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numTermoInterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[0];
        numProcesso = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[1];
        nomeServidor = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[2];
        idServidor = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[3];
        produtosDesinterditados = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[4];
        irregularidadesSanadas = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[5];
        diaDesinterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[6];
        mesDesinterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[7];
        anoDesinterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[8];
        horarioDesinterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[9];
        diaInterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[10];
        mesInterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[11];
        anoInterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[12];
        usarVerso = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[13];
        numTermoDesinterd = termoVinculadoDesinterdicaoProdutoWidget->getVariablesFromLayout()[14];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoDesinterd.isEmpty()) dadosFaltantes.append("Número do Termo Vinculado de Desinterdição de Produtos e/ou Substâncias");
        if (numTermoInterd.isEmpty()) dadosFaltantes.append("Número do Termo de Interdição Cautelar");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (produtosDesinterditados.isEmpty()) dadosFaltantes.append("Produtos e/ou Substâncias Desinterditados");
        if (irregularidadesSanadas.isEmpty()) dadosFaltantes.append("Irregularidades Sanadas");
        if (diaDesinterd.isEmpty() || mesDesinterd.isEmpty() || anoDesinterd.isEmpty()) dadosFaltantes.append("Data da Desinterdição Cautelar");
        if (horarioDesinterd.isEmpty()) dadosFaltantes.append("Horário da Desinterdição Cautelar");
        if (diaInterd.isEmpty() || mesInterd.isEmpty() || anoInterd.isEmpty()) dadosFaltantes.append("Data da Interdição Cautelar");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 8) { // Termo de Coleta de Amostras
        numTermoColetaAmostras = termoColetaAmostrasWidget->getVariablesFromLayout()[0];
        nomeServidor = termoColetaAmostrasWidget->getVariablesFromLayout()[1];
        idServidor = termoColetaAmostrasWidget->getVariablesFromLayout()[2];
        amostraProduto = termoColetaAmostrasWidget->getVariablesFromLayout()[3];
        amostraMarca = termoColetaAmostrasWidget->getVariablesFromLayout()[4];
        amostraFabricante = termoColetaAmostrasWidget->getVariablesFromLayout()[5];
        amostraCnpjCpfFabricante = termoColetaAmostrasWidget->getVariablesFromLayout()[6];
        amostraEnderecoFabricante = termoColetaAmostrasWidget->getVariablesFromLayout()[7];
        amostraCidadeFabricante = termoColetaAmostrasWidget->getVariablesFromLayout()[8];
        amostraCEPFabricante = termoColetaAmostrasWidget->getVariablesFromLayout()[9];
        amostraNumRegistro = termoColetaAmostrasWidget->getVariablesFromLayout()[10];
        amostraLote = termoColetaAmostrasWidget->getVariablesFromLayout()[11];
        diaColeta = termoColetaAmostrasWidget->getVariablesFromLayout()[12];
        mesColeta = termoColetaAmostrasWidget->getVariablesFromLayout()[13];
        anoColeta = termoColetaAmostrasWidget->getVariablesFromLayout()[14];
        horarioColeta = termoColetaAmostrasWidget->getVariablesFromLayout()[15];
        diaFabricacao = termoColetaAmostrasWidget->getVariablesFromLayout()[16];
        mesFabricacao = termoColetaAmostrasWidget->getVariablesFromLayout()[17];
        anoFabricacao = termoColetaAmostrasWidget->getVariablesFromLayout()[18];
        diaValidade = termoColetaAmostrasWidget->getVariablesFromLayout()[19];
        mesValidade = termoColetaAmostrasWidget->getVariablesFromLayout()[20];
        anoValidade = termoColetaAmostrasWidget->getVariablesFromLayout()[21];
        amostraPesoVolumeUnitario = termoColetaAmostrasWidget->getVariablesFromLayout()[22];
        amostraTotalUnidadesAmostrais = termoColetaAmostrasWidget->getVariablesFromLayout()[23];
        amostraLacreProva = termoColetaAmostrasWidget->getVariablesFromLayout()[24];
        amostraLacreContraprova = termoColetaAmostrasWidget->getVariablesFromLayout()[25];
        amostraLacreTestemunho = termoColetaAmostrasWidget->getVariablesFromLayout()[26];
        amostraColetaComInterdicaoCautelar = termoColetaAmostrasWidget->getVariablesFromLayout()[27];
        amostraObservacoes = termoColetaAmostrasWidget->getVariablesFromLayout()[28];
        detentorRazaoSocial = termoColetaAmostrasWidget->getVariablesFromLayout()[29];
        detentorCnpjCpf = termoColetaAmostrasWidget->getVariablesFromLayout()[30];
        detentorEndereco = termoColetaAmostrasWidget->getVariablesFromLayout()[31];
        detentorCEP = termoColetaAmostrasWidget->getVariablesFromLayout()[32];
        detentorCidade = termoColetaAmostrasWidget->getVariablesFromLayout()[33];
        detentorRepresentanteLegal = termoColetaAmostrasWidget->getVariablesFromLayout()[34];
        detentorRgCpf = termoColetaAmostrasWidget->getVariablesFromLayout()[35];
        checkModalidadeAnaliseFiscal = termoColetaAmostrasWidget->getVariablesFromLayout()[36];
        checkModalidadeAnaliseControle = termoColetaAmostrasWidget->getVariablesFromLayout()[37];
        checkModalidadeAnaliseOrientacao = termoColetaAmostrasWidget->getVariablesFromLayout()[38];
        checkModalidadeAnaliseOutra = termoColetaAmostrasWidget->getVariablesFromLayout()[39];
        checkAnaliseFisicoQuimica = termoColetaAmostrasWidget->getVariablesFromLayout()[40];
        checkAnaliseMicrobiologica = termoColetaAmostrasWidget->getVariablesFromLayout()[41];
        checkAnaliseMicroscopica = termoColetaAmostrasWidget->getVariablesFromLayout()[42];
        checkAnaliseQuimica = termoColetaAmostrasWidget->getVariablesFromLayout()[43];
        checkAnaliseRotulagem = termoColetaAmostrasWidget->getVariablesFromLayout()[44];
        checkAnaliseSensorial = termoColetaAmostrasWidget->getVariablesFromLayout()[45];
        checkAnaliseToxicologica = termoColetaAmostrasWidget->getVariablesFromLayout()[46];
        checkAnaliseOutra = termoColetaAmostrasWidget->getVariablesFromLayout()[47];
        modalidadeAnaliseOutraTexto = termoColetaAmostrasWidget->getVariablesFromLayout()[48];
        analiseOutraTexto = termoColetaAmostrasWidget->getVariablesFromLayout()[49];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (numTermoColetaAmostras.isEmpty()) dadosFaltantes.append("Nº do Termo de Coleta de Amostras");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Fiscal Sanitário");
        if (idServidor.isEmpty()) dadosFaltantes.append("Matrícula/ID do Fiscal Sanitário");
        if (amostraProduto.isEmpty()) dadosFaltantes.append("Produto");
        if (amostraMarca.isEmpty()) dadosFaltantes.append("Marca");
        if (amostraFabricante.isEmpty()) dadosFaltantes.append("Fabricante/Produtor/Embalador/Importador");
        if (amostraCnpjCpfFabricante.isEmpty()) dadosFaltantes.append("CNPJ/CPF");
        if (amostraEnderecoFabricante.isEmpty()) dadosFaltantes.append("Endereço");
        if (amostraCidadeFabricante.isEmpty()) dadosFaltantes.append("Município");
        if (amostraCEPFabricante.isEmpty()) dadosFaltantes.append("CEP");
        if (amostraNumRegistro.isEmpty()) dadosFaltantes.append("Nº do Registro no Órgão Competente");
        if (amostraLote.isEmpty()) dadosFaltantes.append("Lote");
        if (diaColeta.isEmpty() || mesColeta.isEmpty() || anoColeta.isEmpty()) dadosFaltantes.append("Data da Coleta");
        if (horarioColeta.isEmpty()) dadosFaltantes.append("Hora da Coleta");
        if (diaFabricacao.isEmpty() || mesFabricacao.isEmpty() || anoFabricacao.isEmpty()) dadosFaltantes.append("Data de Fabricação");
        if (diaValidade.isEmpty() || mesValidade.isEmpty() || anoValidade.isEmpty()) dadosFaltantes.append("Data de Validade");
        if (amostraPesoVolumeUnitario.isEmpty()) dadosFaltantes.append("Peso/Volume Unitário");
        if (amostraTotalUnidadesAmostrais.isEmpty()) dadosFaltantes.append("Total de Unidades Amostrais");
        if (amostraLacreProva.isEmpty()) dadosFaltantes.append("Lacre Prova");
        if (amostraLacreContraprova.isEmpty()) dadosFaltantes.append("Lacre Contraprova");
        if (amostraLacreTestemunho.isEmpty()) dadosFaltantes.append("Lacre Testemunho");
        if (amostraColetaComInterdicaoCautelar == "nenhum") dadosFaltantes.append("Coleta Acompanhada de Interdição Cautelar");
        if (detentorRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social do Detentor");
        if (detentorCnpjCpf.isEmpty()) dadosFaltantes.append("CPF/CNPJ do Detentor");
        if (detentorEndereco.isEmpty()) dadosFaltantes.append("Endereço do Detentor");
        if (detentorCEP.isEmpty()) dadosFaltantes.append("CEP do Detentor");
        if (detentorCidade.isEmpty()) dadosFaltantes.append("Município do Detentor");
        if (detentorRepresentanteLegal.isEmpty()) dadosFaltantes.append("Representante Legal do Detentor");
        if (detentorRgCpf.isEmpty()) dadosFaltantes.append("RG/CPF do Representante Legal do Detentor");
        int contaModalidade = 0, contaAnalises = 0;
        if (checkModalidadeAnaliseFiscal == "sim") contaModalidade++;
        if (checkModalidadeAnaliseControle == "sim") contaModalidade++;
        if (checkModalidadeAnaliseOrientacao == "sim") contaModalidade++;
        if (checkModalidadeAnaliseOutra == "sim") contaModalidade++;
        if (checkModalidadeAnaliseOutra == "sim" && modalidadeAnaliseOutraTexto.isEmpty()) dadosFaltantes.append("Outra(s) Modalidade(s) de Análise");
        if (contaModalidade == 0) dadosFaltantes.append("Modalidade de Análise");
        if (checkAnaliseFisicoQuimica == "sim") contaAnalises++;
        if (checkAnaliseMicrobiologica == "sim") contaAnalises++;
        if (checkAnaliseMicroscopica == "sim") contaAnalises++;
        if (checkAnaliseQuimica == "sim") contaAnalises++;
        if (checkAnaliseRotulagem == "sim") contaAnalises++;
        if (checkAnaliseSensorial == "sim") contaAnalises++;
        if (checkAnaliseToxicologica == "sim") contaAnalises++;
        if (checkAnaliseOutra == "sim") contaAnalises++;
        if (checkAnaliseOutra == "sim" && analiseOutraTexto.isEmpty()) dadosFaltantes.append("Outras Análises Solicitadas");
        if (contaAnalises == 0) dadosFaltantes.append("Análises Solicitadas");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 9) { // Termo de Inutilização Imediata de Produtos
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numTermoInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[0];
        numAuto = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[1];
        numLaudoPericial = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[2];
        localInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[3];
        fabricanteProdutos = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[4];
        produtosInutilizados = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[5];
        nomeServidor = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[6];
        idServidor = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[7];
        diaInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[8];
        mesInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[9];
        anoInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[10];
        horarioInutilizacao = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[11];
        usarVerso = termoInutilizacaoImediataProdutoWidget->getVariablesFromLayout()[12];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numTermoInutilizacao.isEmpty()) dadosFaltantes.append("Número do Termo de Inutilizacação Imediata de Produtos");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (numLaudoPericial.isEmpty()) dadosFaltantes.append("Número do Laudo Pericial");
        if (localInutilizacao.isEmpty()) dadosFaltantes.append("Local da Inutilização Imediata");
        if (fabricanteProdutos.isEmpty()) dadosFaltantes.append("Produtor/Fabricante dos Produtos");
        if (produtosInutilizados.isEmpty()) dadosFaltantes.append("Produtos Inutilizados");
        if (diaInutilizacao.isEmpty() || mesInutilizacao.isEmpty() || anoInutilizacao.isEmpty()) dadosFaltantes.append("Data da Inutilização Imediata");
        if (horarioInutilizacao.isEmpty()) dadosFaltantes.append("Horário da Inutilização Imediata");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 10) { // Notificação de Desprovimento de Recurso
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numAuto = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[0];
        numProcesso = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[1];
        nomeServidor = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[2];
        idServidor = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[3];
        penalidadeImposta = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[4];
        diaAuto = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[5];
        mesAuto = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[6];
        anoAuto = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[7];
        diaNotif = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[8];
        mesNotif = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[9];
        anoNotif = notifDesprovimentoRecursoWidget->getVariablesFromLayout()[10];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Desprovimento de Recurso");
        if (penalidadeImposta.isEmpty()) dadosFaltantes.append("Penalidade(s) Imposta(s)/Mantida(s)");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 11) { // Notificação de Parcial Provimento de Recurso
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numAuto = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[0];
        numProcesso = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[1];
        nomeServidor = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[2];
        idServidor = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[3];
        penalidadeImposta = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[4];
        diaAuto = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[5];
        mesAuto = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[6];
        anoAuto = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[7];
        diaNotif = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[8];
        mesNotif = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[9];
        anoNotif = notifParcialProvimentoRecursoWidget->getVariablesFromLayout()[10];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Parcial Provimento de Recurso");
        if (penalidadeImposta.isEmpty()) dadosFaltantes.append("Penalidade(s) Imposta(s)/Mantida(s)");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 12) { // Notificação de Imposição de Penalidade - Procedência da Autuação
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numAuto = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[0];
        numProcesso = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[1];
        nomeServidor = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[2];
        idServidor = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[3];
        estabSetorInterditadoParcialmente = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[4];
        diaAuto = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[5];
        mesAuto = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[6];
        anoAuto = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[7];
        diaNotif = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[8];
        mesNotif = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[9];
        anoNotif = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[10];
        penaAdvertenciaChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[11];
        penaApreensaoChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[12];
        penaInutilizacaoChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[13];
        penaSuspensaoVendaFabricacaoChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[14];
        penaCancelamentoRegistroChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[15];
        penaInterdicaoParcialChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[16];
        penaInterdicaoTotalChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[17];
        penaProibicaoPropagandaChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[18];
        penaCancelamentoAlvaraChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[19];
        penaIntervencaoChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[20];
        penaImposicaoMensagemRetificadoraChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[21];
        penaSuspensaoPropagandaChecked = notifImposPenalidadeProcedenciaWidget->getVariablesFromLayout()[22];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (penaInterdicaoParcialChecked=="sim" && estabSetorInterditadoParcialmente.isEmpty()) dadosFaltantes.append("Área/Local/Setor Interditado");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Imposição de Penalidade");
        int contaSelected = 0;
        if (penaAdvertenciaChecked == "sim") contaSelected++;
        if (penaApreensaoChecked == "sim") contaSelected++;
        if (penaIntervencaoChecked == "sim") contaSelected++;
        if (penaInutilizacaoChecked == "sim") contaSelected++;
        if (penaInterdicaoTotalChecked == "sim") contaSelected++;
        if (penaInterdicaoParcialChecked == "sim") contaSelected++;
        if (penaCancelamentoAlvaraChecked == "sim") contaSelected++;
        if (penaProibicaoPropagandaChecked == "sim") contaSelected++;
        if (penaSuspensaoPropagandaChecked == "sim") contaSelected++;
        if (penaCancelamentoRegistroChecked == "sim") contaSelected++;
        if (penaSuspensaoVendaFabricacaoChecked == "sim") contaSelected++;
        if (penaImposicaoMensagemRetificadoraChecked == "sim") contaSelected++;
        if (contaSelected == 0) dadosFaltantes.append("Penalidade(s) Imposta(s)/Mantida(s)");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 13) { // Notificação de Imposição de Penalidade - Parcial Procedência da Autuação
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numAuto = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[0];
        numProcesso = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[1];
        nomeServidor = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[2];
        idServidor = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[3];
        estabSetorInterditadoParcialmente = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[4];
        diaAuto = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[5];
        mesAuto = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[6];
        anoAuto = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[7];
        diaNotif = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[8];
        mesNotif = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[9];
        anoNotif = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[10];
        penaAdvertenciaChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[11];
        penaApreensaoChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[12];
        penaInutilizacaoChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[13];
        penaSuspensaoVendaFabricacaoChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[14];
        penaCancelamentoRegistroChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[15];
        penaInterdicaoParcialChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[16];
        penaInterdicaoTotalChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[17];
        penaProibicaoPropagandaChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[18];
        penaCancelamentoAlvaraChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[19];
        penaIntervencaoChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[20];
        penaImposicaoMensagemRetificadoraChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[21];
        penaSuspensaoPropagandaChecked = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[22];
        motivoParcialProcedencia = notifImposPenalidadeParcialProcedenciaWidget->getVariablesFromLayout()[23];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (penaInterdicaoParcialChecked=="sim" && estabSetorInterditadoParcialmente.isEmpty()) dadosFaltantes.append("Área/Local/Setor Interditado");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Imposição de Penalidade");
        if (motivoParcialProcedencia.isEmpty()) dadosFaltantes.append("Motivo da Parcial Procedência da Autuação");
        int contaSelected = 0;
        if (penaAdvertenciaChecked == "sim") contaSelected++;
        if (penaApreensaoChecked == "sim") contaSelected++;
        if (penaIntervencaoChecked == "sim") contaSelected++;
        if (penaInutilizacaoChecked == "sim") contaSelected++;
        if (penaInterdicaoTotalChecked == "sim") contaSelected++;
        if (penaInterdicaoParcialChecked == "sim") contaSelected++;
        if (penaCancelamentoAlvaraChecked == "sim") contaSelected++;
        if (penaProibicaoPropagandaChecked == "sim") contaSelected++;
        if (penaSuspensaoPropagandaChecked == "sim") contaSelected++;
        if (penaCancelamentoRegistroChecked == "sim") contaSelected++;
        if (penaSuspensaoVendaFabricacaoChecked == "sim") contaSelected++;
        if (penaImposicaoMensagemRetificadoraChecked == "sim") contaSelected++;
        if (contaSelected == 0) dadosFaltantes.append("Penalidade(s) Imposta(s)/Mantida(s)");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 14) { // Notificação de Imposição de Pena de Multa
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        valorMulta = notifImposPenaMultaWidget->getVariablesFromLayout()[0];
        numAuto = notifImposPenaMultaWidget->getVariablesFromLayout()[1];
        numProcesso = notifImposPenaMultaWidget->getVariablesFromLayout()[2];
        nomeServidor = notifImposPenaMultaWidget->getVariablesFromLayout()[3];
        idServidor = notifImposPenaMultaWidget->getVariablesFromLayout()[4];
        diaNotif = notifImposPenaMultaWidget->getVariablesFromLayout()[5];
        mesNotif = notifImposPenaMultaWidget->getVariablesFromLayout()[6];
        anoNotif = notifImposPenaMultaWidget->getVariablesFromLayout()[7];
        diaAuto = notifImposPenaMultaWidget->getVariablesFromLayout()[8];
        mesAuto = notifImposPenaMultaWidget->getVariablesFromLayout()[9];
        anoAuto = notifImposPenaMultaWidget->getVariablesFromLayout()[10];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (valorMulta.isEmpty()) dadosFaltantes.append("Valor da Multa");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Imposição de Pena de Multa");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 15) { // Notificação de Decisão Final
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numAuto = notifDecisaoFinalWidget->getVariablesFromLayout()[0];
        numProcesso = notifDecisaoFinalWidget->getVariablesFromLayout()[1];
        nomeServidor = notifDecisaoFinalWidget->getVariablesFromLayout()[2];
        idServidor = notifDecisaoFinalWidget->getVariablesFromLayout()[3];
        penalidadeImposta = notifDecisaoFinalWidget->getVariablesFromLayout()[4];
        diaAuto = notifDecisaoFinalWidget->getVariablesFromLayout()[5];
        mesAuto = notifDecisaoFinalWidget->getVariablesFromLayout()[6];
        anoAuto = notifDecisaoFinalWidget->getVariablesFromLayout()[7];
        diaNotif = notifDecisaoFinalWidget->getVariablesFromLayout()[8];
        mesNotif = notifDecisaoFinalWidget->getVariablesFromLayout()[9];
        anoNotif = notifDecisaoFinalWidget->getVariablesFromLayout()[10];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação de Decisão Final");
        if (penalidadeImposta.isEmpty()) dadosFaltantes.append("Penalidade(s) Imposta(s)/Mantida(s)");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 16) { // Notificação para Pagamento de Multa APÓS DECISÃO FINAL
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        valorMulta = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[0];
        valorMultaPorExtenso = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[1];
        numAuto = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[2];
        numProcesso = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[3];
        nomeServidor = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[4];
        idServidor = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[5];
        diaNotif = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[6];
        mesNotif = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[7];
        anoNotif = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[8];
        diaAuto = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[9];
        mesAuto = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[10];
        anoAuto = notifPagamentoMultaAposDecisaoFinalWidget->getVariablesFromLayout()[11];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (valorMulta.isEmpty()) dadosFaltantes.append("Valor da Multa");
        if (valorMultaPorExtenso.isEmpty()) dadosFaltantes.append("Valor da Multa Por Extenso");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (diaAuto.isEmpty() || mesAuto.isEmpty() || anoAuto.isEmpty()) dadosFaltantes.append("Data da Autuação");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (diaNotif.isEmpty() || mesNotif.isEmpty() || anoNotif.isEmpty()) dadosFaltantes.append("Data da Notificação para Pagamento de Multa");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("ID do Servidor Autuante");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 17) { // Termo de Apreensão e Inutilização APÓS DECISÃO FINAL
        // QDockWidget Estabelecimento
        estabCnpjCpf = ui->cnpjLineEdit->text();
        estabRazaoSocial = ui->razaoSocialLineEdit->text();
        estabRamoAtiv = ui->ramoLineEdit->text();
        estabEndereco = ui->enderecoLineEdit->text();
        estabCidade = ui->cidadeLineEdit->text();
        estabCEP = ui->cepLineEdit->text();
        numAlvara = ui->numAlvaraLineEdit->text();
        numProcesso = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[0];
        numTermoApreensao = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[1];
        numAuto = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[2];
        nomeServidor = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[3];
        idServidor = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[4];
        fabricanteProdutos = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[5];
        produtosApreendidos = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[6];
        usarVerso = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[7];
        diaApreensao = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[8];
        mesApreensao = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[9];
        anoApreensao = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[10];
        horarioApreensao = termoApreensaoInutilizacaoAPosDecisaoFinalWidget->getVariablesFromLayout()[11];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (estabCnpjCpf.isEmpty()) dadosFaltantes.append("CNPJ ou CPF");
        if (estabRazaoSocial.isEmpty()) dadosFaltantes.append("Nome/Razão Social");
        if (estabRamoAtiv.isEmpty()) dadosFaltantes.append("Ramo de Atividade");
        if (estabEndereco.isEmpty()) dadosFaltantes.append("Endereço");
        if (estabCidade.isEmpty()) dadosFaltantes.append("Município");
        if (estabCEP.isEmpty()) dadosFaltantes.append("CEP");
        if (numAlvara.isEmpty()) dadosFaltantes.append("Número do Alvará");
        if (numProcesso.isEmpty()) dadosFaltantes.append("Número do Processo");
        if (numTermoApreensao.isEmpty()) dadosFaltantes.append("Número do Termo de Apreensão e Inutilização");
        if (numAuto.isEmpty()) dadosFaltantes.append("Número do Auto de Infração");
        if (nomeServidor.isEmpty()) dadosFaltantes.append("Nome do Servidor Autuante");
        if (idServidor.isEmpty()) dadosFaltantes.append("Matrícula/ID do Servidor Autuante");
        if (fabricanteProdutos.isEmpty()) dadosFaltantes.append("Produtos/Fabricante dos Produtos");
        if (produtosApreendidos.isEmpty()) dadosFaltantes.append("Produtos Apreendidos e Inutilizados");
        if (diaApreensao.isEmpty() || mesApreensao.isEmpty() || anoApreensao.isEmpty()) dadosFaltantes.append("Data da Apreensão e Inutilização");
        if (horarioApreensao.isEmpty()) dadosFaltantes.append("Horário da Apreensão e Inutilização");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 18) { // Aviso de Recebimento
        remetenteRazaoSocial = avisoRecebimentoWidget->getVariablesFromLayout()[0];
        remetenteEndereco = avisoRecebimentoWidget->getVariablesFromLayout()[1];
        remetenteCidade = avisoRecebimentoWidget->getVariablesFromLayout()[2];
        remetenteEstado = avisoRecebimentoWidget->getVariablesFromLayout()[3];
        remetenteCEP = avisoRecebimentoWidget->getVariablesFromLayout()[4];
        destinatarioRazaoSocial = avisoRecebimentoWidget->getVariablesFromLayout()[5];
        destinatarioEndereco = avisoRecebimentoWidget->getVariablesFromLayout()[6];
        destinatarioCidade = avisoRecebimentoWidget->getVariablesFromLayout()[7];
        destinatarioEstado = avisoRecebimentoWidget->getVariablesFromLayout()[8];
        destinatarioCEP = avisoRecebimentoWidget->getVariablesFromLayout()[9];
        conteudoCorrespondencia = avisoRecebimentoWidget->getVariablesFromLayout()[10];
        maoPropria = avisoRecebimentoWidget->getVariablesFromLayout()[11];
        // Primeiro testa se todos os dados obrigatórios estão preenchidos
        QStringList dadosFaltantes;
        dadosFaltantes.clear();
        if (remetenteRazaoSocial.isEmpty()) dadosFaltantes.append("Nome ou Razão Social do Remetente");
        if (remetenteEndereco.isEmpty()) dadosFaltantes.append("Endereço do Remetente");
        if (remetenteCidade.isEmpty()) dadosFaltantes.append("Cidade do Remetente");
        if (remetenteEstado.isEmpty()) dadosFaltantes.append("Estado do Remetente");
        if (remetenteCEP.isEmpty()) dadosFaltantes.append("CEP do Remetente");
        if (destinatarioRazaoSocial.isEmpty()) dadosFaltantes.append("Nome ou Razão Social do Destinatário");
        if (destinatarioEndereco.isEmpty()) dadosFaltantes.append("Endereço do Destinatário");
        if (destinatarioCidade.isEmpty()) dadosFaltantes.append("Cidade do Destinatário");
        if (destinatarioEstado.isEmpty()) dadosFaltantes.append("Estado do Destinatário");
        if (destinatarioCEP.isEmpty()) dadosFaltantes.append("CEP do Destinatário");
        if (conteudoCorrespondencia.isEmpty()) dadosFaltantes.append("Conteúdo da Correspondência");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return false;
        } else {
            return true;
        }
    } else if (tipoSalvar == 19) { // Despacho para Inclusão de AR no Processo

    } else if (tipoSalvar == 20) { // Arquivamento de Processo

    } else if (tipoSalvar == 555) { // Relatório de Inspeção

    }

    // Saída default
    return true;
}
