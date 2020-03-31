#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupWidget6437()
{
    widget6437 = new QWidget();
    widget6437->setWindowTitle("TIPIFICAÇÃO DA INFRAÇÃO");
    widget6437->resize(700, 500);
    widget6437->setWindowIcon(QPixmap(":/imagens/logo.jpg"));
    widget6437->show();

    QVBoxLayout *vboxWidget6437 = new QVBoxLayout;
    vboxWidget6437->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    widget6437->setLayout(vboxWidget6437);

    QVBoxLayout *vbox6437 = new QVBoxLayout();
    vbox6437->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QGroupBox *grupo6437 = new QGroupBox("");
    grupo6437->setLayout(vbox6437);

    vboxWidget6437->addWidget(grupo6437);

    QLabel *labelPrincipal = new QLabel("TIPIFICAÇÃO DAS INFRAÇÕES (Art. 10 da Lei 6437/77)");
    labelPrincipal->setFixedHeight(31);
    labelPrincipal->setStyleSheet("QLabel{"
                                  "border: 1px solid black;"
                                  "font-size: 11pt;"
                                  "font-weight: bold;"
                                  "background-color: rgb(255,0,0);"
                                  "color: rgb(255, 255, 0);"
                                  "}");

    QLabel *labelInciso = new QLabel("Inciso do Art. 10 da Lei 6437/77:");
    labelInciso->setFixedHeight(20);
    QLabel *labelIncisoSelecionado = new QLabel("Inciso(s) Selecionado(s):");
    labelIncisoSelecionado->setFixedHeight(20);
    labelIncisoSelecionado->setStyleSheet("QLabel{font-weight: bold;}");
    QLabel *labelPenaIncisoSelecionado = new QLabel("Penalidade(s) do(s) Inciso(s) Selecionado(s):");
    labelPenaIncisoSelecionado->setFixedHeight(20);
    labelPenaIncisoSelecionado->setStyleSheet("QLabel{font-weight: bold;}");
    QPlainTextEdit *textEditSelectedIncisos = new QPlainTextEdit();
    textEditSelectedIncisos->setFixedHeight(30);
    QPlainTextEdit *textEditSelectedPenalidades = new QPlainTextEdit();
    textEditSelectedPenalidades->setFixedHeight(80);
    QPlainTextEdit *textPenaInciso = new QPlainTextEdit();
    textPenaInciso->setFixedHeight(50);
    QPlainTextEdit *textTextoInciso = new QPlainTextEdit();
    textTextoInciso->setFixedHeight(100);

    textPenaInciso->setReadOnly(true);
    textTextoInciso->setReadOnly(true);
    textEditSelectedIncisos->setReadOnly(true);
    textEditSelectedPenalidades->setReadOnly(true);

    comboInciso = new QComboBox();
    QStringList colunas6437;
    colunas6437.clear();
    penaIncisoList.clear();
    textoIncisoList.clear();
    incisoList.clear();
    for (int i=0; i<inciso6437List.count(); i++) {
        colunas6437 = inciso6437List[i].split(";");
        comboInciso->addItem(colunas6437[0]);
        incisoList.append(colunas6437[0]);
        textoIncisoList.append(colunas6437[1]);
        penaIncisoList.append(colunas6437[2]);
    }

    QPushButton *botaoSelectInciso = new QPushButton("Selecionar Inciso");
    QPushButton *botaoLimparInciso = new QPushButton("Limpar");
    QPushButton *botaoCancelarInciso = new QPushButton("Fechar");
    QPushButton *botaoOKInciso = new QPushButton("OK");

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();
    QHBoxLayout *hbox4 = new QHBoxLayout();
    QHBoxLayout *hbox5 = new QHBoxLayout();
    QHBoxLayout *hbox6 = new QHBoxLayout();

    hbox1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hbox2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hbox3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hbox4->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hbox5->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hbox6->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    hbox1->addWidget(labelInciso);
    hbox1->addWidget(comboInciso);
    hbox1->addWidget(botaoSelectInciso);
    hbox2->addWidget(textTextoInciso);
    hbox3->addWidget(textPenaInciso);
    hbox4->addWidget(textEditSelectedIncisos);
    hbox5->addWidget(textEditSelectedPenalidades);
    hbox6->addWidget(botaoOKInciso);
    hbox6->addWidget(botaoLimparInciso);
    hbox6->addWidget(botaoCancelarInciso);

    vbox6437->addWidget(labelPrincipal);
    vbox6437->addLayout(hbox1);
    vbox6437->addLayout(hbox2);
    vbox6437->addLayout(hbox3);
    vbox6437->addWidget(labelIncisoSelecionado);
    vbox6437->addLayout(hbox4);
    vbox6437->addWidget(labelPenaIncisoSelecionado);
    vbox6437->addLayout(hbox5);
    vbox6437->addLayout(hbox6);

    QSpacerItem *spacer = new QSpacerItem(20, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding);
    vbox6437->addSpacerItem(spacer);

    // Insere inciso e penalidades default na visualização
    textTextoInciso->setPlainText(QString("Inciso %1 - %2").arg(incisoList[comboInciso->currentIndex()]).arg(textoIncisoList[comboInciso->currentIndex()]));
    textPenaInciso->setPlainText(QString("Penalidades: %1").arg(penaIncisoList[comboInciso->currentIndex()]));

    connect(comboInciso, &QComboBox::currentTextChanged, this, [=]{
        textTextoInciso->clear();
        textPenaInciso->clear();
        textTextoInciso->setPlainText(QString("Inciso %1 - %2").arg(incisoList[comboInciso->currentIndex()]).arg(textoIncisoList[comboInciso->currentIndex()]));
        textPenaInciso->setPlainText(QString("Penalidades: %1").arg(penaIncisoList[comboInciso->currentIndex()]));
    });

    textEditSelectedIncisos->clear();
    tipificacao.clear();
    selectedIncisos.clear();
    selectedIncisoPenas.clear();

    connect(botaoSelectInciso, &QPushButton::clicked, this, [=]{
        selectedIncisos.append(incisoList[comboInciso->currentIndex()]);
        selectedIncisoPenas.append(penaIncisoList[comboInciso->currentIndex()]);
        for (int i=0; i<selectedIncisos.count(); i++) {
            if (selectedIncisos.count() == 0) {
                tipificacao.clear();
                tipificacao.append(QString("NENHUM"));
            } else if (selectedIncisos.count() == 1) {
                tipificacao.clear();
                tipificacao.append(QString("%1").arg(selectedIncisos[0]));
            } else if (selectedIncisos.count() == 2) {
                tipificacao.clear();
                tipificacao.append(QString("%1 e %2").arg(selectedIncisos[0]).arg(selectedIncisos[1]));
            } else if (selectedIncisos.count() > 2) {
                if (i == selectedIncisos.count()-1) {
                    tipificacao.append(QString("e %1").arg(selectedIncisos[i]));
                } else {
                    if (i == 0) tipificacao.clear();
                    tipificacao.append(QString("%1, ").arg(selectedIncisos[i]));
                }
            }
        }
        textEditSelectedIncisos->clear();
        textEditSelectedIncisos->setPlainText(QString("%1").arg(tipificacao));

        penasTipificacao.clear();
        penaSeqListTemp.clear();
        penaSeqTemp.clear();
        for (int i=0; i<selectedIncisoPenas.count(); i++) {
            selectedIncisoPenas[i].replace(QString("e/ou"), QString(","));
            selectedIncisoPenas[i].replace(QString(" ,"), QString(","));
            selectedIncisoPenas[i].replace(QString(",,"), QString(","));
            penaSeqTemp = selectedIncisoPenas[i];
            penaSeqListTemp.append(penaSeqTemp.split(","));
        }
        allPenas.clear();
        allPenas = penaSeqListTemp;
        allPenasSemRepet.clear();
        bool foundStr = false;
        for (int i=0; i<allPenas.count(); i++) {
            for (int j=0; j<allPenasSemRepet.count() && allPenasSemRepet.count()>0 && foundStr==false; j++) {
                if (QString::compare(QString(allPenas[i]), QString(allPenasSemRepet[j])) == STR_EQUAL) {
                    foundStr = true;
                }
            }
            if (foundStr == false) {
                allPenasSemRepet.append(allPenas[i]);
            } else {
                foundStr = false;
            }
        }

        for (int i=0; i<allPenasSemRepet.count(); i++) {
            if (allPenasSemRepet.count() == 0) {
                penasTipificacao.clear();
                penasTipificacao.append(QString(""));
            } else if (allPenasSemRepet.count() == 1) {
                penasTipificacao.clear();
                penasTipificacao.append(QString("%1").arg(allPenasSemRepet[0]));
            } else if (allPenasSemRepet.count() == 2) {
                penasTipificacao.clear();
                penasTipificacao.append(QString("%1 e/ou %2").arg(allPenasSemRepet[0]).arg(allPenasSemRepet[1]));
            } else if (allPenasSemRepet.count() > 2) {
                if (i == allPenasSemRepet.count()-1) {
                    penasTipificacao.append(QString("e/ou %1").arg(allPenasSemRepet[i]));
                } else {
                    if (i == 0) penasTipificacao.clear();
                    penasTipificacao.append(QString("%1, ").arg(allPenasSemRepet[i]));
                }
            }
        }

        // Corrige espaçamento
        penasTipificacao.replace("  "," ");

        textEditSelectedPenalidades->clear();
        textEditSelectedPenalidades->setPlainText(QString("%1").arg(penasTipificacao));
    });

    connect(botaoOKInciso, &QPushButton::clicked, this, [=]{
        if (!tipificacao.isEmpty() && !penasTipificacao.isEmpty() && !textEditSelectedIncisos->toPlainText().isEmpty() && !textEditSelectedPenalidades->toPlainText().isEmpty()) {
            widget6437->close();
            QString fn;
            fn.clear();
            fn = QFileDialog::getSaveFileName(this, tr("Salvar arquivo"), QString(), tr("XML do Microsoft Word 2007-2013 (*.docx);;Documento do Open Office (*.odt)"));
            if (fn.isEmpty()) {
                return;
            } else {
                if (fn.endsWith(".docx")) {
                    autodeInfracaoDOCX(fn);
                } else if (fn.endsWith(".odt")) {
                    autodeInfracaoODT(fn);
                }
            }
        } else {
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: Deve ser selecionado <FONT COLOR='#ff0000'><strong>no mínimo 1 (um) Inciso do Art. 10 da Lei 6.437/77</strong></FONT> para tipificação da(s) infração(ões)."));
            mensagemBox.exec();
        }
    });

    connect(botaoCancelarInciso, &QPushButton::clicked, this, [=]{
        widget6437->close();
    });

    connect(botaoLimparInciso, &QPushButton::clicked, this, [=]{
        tipificacao.clear();
        penasTipificacao.clear();
        textEditSelectedIncisos->clear();
        textEditSelectedPenalidades->clear();
        selectedIncisos.clear();
        selectedIncisoPenas.clear();
        penasEmSeqList.clear();
        allPenas.clear();
        allPenasSemRepet.clear();
    });
}
