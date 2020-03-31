#include "termointerdicaoproduto.h"
#include "ui_termointerdicaoproduto.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

TermoInterdicaoProduto::TermoInterdicaoProduto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermoInterdicaoProduto)
{
    ui->setupUi(this);

    ui->dataInterdicaoDateEdit->setDate(QDate::currentDate());
    ui->horarioInterdicaoDateEdit->setTime(QTime::currentTime());

    vboxScrollIrreg = new QVBoxLayout;
    ui->groupBoxIrreg->setLayout(vboxScrollIrreg);

    // Configura comboBoxRoteiroInspecao
    setupRoteirosDisponiveis();
}

TermoInterdicaoProduto::~TermoInterdicaoProduto()
{
    delete ui;
}

void TermoInterdicaoProduto::on_comboBoxRoteiroInspecao_currentIndexChanged(int index)
{
    if (index != 0) {
        checkBoxIrregList.clear();
        setupRoteiroLayout(index);
    } else {
        checkBoxIrregList.clear();
        apagaLayout(vboxScrollIrreg);
    }
}

void TermoInterdicaoProduto::apagaLayout(QLayout * layout)
{
    if (! layout)
          return;
       while (auto item = layout->takeAt(0)) {
          delete item->widget();
          apagaLayout(item->layout());
    }
}

void TermoInterdicaoProduto::setupRoteiroLayout(int index)
{
    apagaLayout(vboxScrollIrreg);

    QFile arq(listaUrlRoteiros[index]);

    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: arquivo com roteiro de inspeção não pôde ser aberto");
        return;
    }

    QTextStream inRot(&arq);

    listaGruposRoteiro.clear();
    listaIrregRoteiro.clear();
    listaDispoRoteiro.clear();

    QString line;
    QStringList colunas;
    while (!inRot.atEnd()) {
        line = inRot.readLine();
        colunas.clear();
        colunas = line.split("|");
        if (colunas[0] == "grupo") { // Grupo
            listaGruposRoteiro.append(colunas[1]);
            QLabel *labelGrupo = new QLabel(colunas[1]);
            labelGrupo->setFixedHeight(31);
            labelGrupo->setStyleSheet("QLabel{border: 1px solid black; font-size: 11pt; font-weight: bold; background-color: rgb(82,240,0);}");
            vboxScrollIrreg->addWidget(labelGrupo);
        } else if (colunas[0] == "item") { // Item
            listaIrregRoteiro.append(colunas[1]);
            listaDispoRoteiro.append(colunas[2]);
            QCheckBox *checkItem = createQCheckBoxWithWordWrap(this, colunas[1]);
            vboxScrollIrreg->addWidget(checkItem);
            checkBoxIrregList.append(checkItem);
        }
    }

    arq.close();

    QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    vboxScrollIrreg->addSpacerItem(spacer);
}

QCheckBox* TermoInterdicaoProduto::createQCheckBoxWithWordWrap(QWidget *parent, const QString &text)
{
    QCheckBox *checkBox = new QCheckBox(parent);
    checkBox->setFixedHeight(20);
    checkBox->setStyleSheet("QCheckBox {"
                            "font-size: 11pt;}"
                            "QCheckBox::indicator {"
                            "width: 30px;"
                            "height: 30px;}"
                            "QCheckBox::checked {"
                            "color: rgb(150,150,150);}"
                            "QCheckBox:hover {"
                            "color: green;}");
    checkBox->setText(text);

    return checkBox;
}

void TermoInterdicaoProduto::setupRoteirosDisponiveis()
{
    QFile file("roteiros.config");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo roteiros.config");
        return;
    }

    QTextStream in(&file);

    listaNomesRoteiros.clear();
    listaUrlRoteiros.clear();

    // Inicializa listaNomesRoteiros e listaUrlRoteiros
    listaNomesRoteiros.append("-- Selecione o Roteiro de Inspeção --");
    listaUrlRoteiros.append("");

    QString line;
    QStringList colunas;
    while (!in.atEnd()) {
        line = in.readLine();
        colunas = line.split(";");
        listaNomesRoteiros.append(colunas[0]);
        listaUrlRoteiros.append(colunas[1]);
    }

    file.close();

    ui->comboBoxRoteiroInspecao->addItems(listaNomesRoteiros);
}

QStringList TermoInterdicaoProduto::getSelectedCheckBoxesIrreg()
{
    QString irregSaida, dispoSaida;
    irregSaida.clear();
    dispoSaida.clear();

    QStringList selectedIrregList, selectedDispoList;
    selectedIrregList.clear();
    selectedDispoList.clear();
    for (int i=0; i<checkBoxIrregList.count(); i++) {
        if (checkBoxIrregList[i]->checkState() == Qt::CheckState::Checked) {
            selectedIrregList.append(listaIrregRoteiro[i]);
            selectedDispoList.append(listaDispoRoteiro[i]);
        }
    }

    if (selectedIrregList.count() == 0) {
        return QStringList{"",""};
    } else if (selectedIrregList.count() == 1) {
        irregSaida = selectedIrregList[0];
        dispoSaida = selectedDispoList[0];
    } else if (selectedIrregList.count() == 2) {
        irregSaida = QString("1) %1; 2) %2").arg(selectedIrregList[0]).arg(selectedIrregList[1]);
        dispoSaida = QString("1) %1; 2) %2").arg(selectedDispoList[0]).arg(selectedDispoList[1]);
    } else { // Mais do que 2 irregularidades selecionadas
        irregSaida = QString("1) %1").arg(selectedIrregList[0]);
        dispoSaida = QString("1) %1").arg(selectedDispoList[0]);
        for (int i=1; i<selectedIrregList.count(); i++) {
            irregSaida.append(QString("; %1) %2").arg(i+1).arg(selectedIrregList[i]));
            dispoSaida.append(QString("; %1) %2").arg(i+1).arg(selectedDispoList[i]));
        }
    }

    return QStringList{irregSaida, dispoSaida};
}

QStringList TermoInterdicaoProduto::converteQDateEmStringList(QDate date)
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

QString TermoInterdicaoProduto::converteQTimeEmString(QTime time)
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

QStringList TermoInterdicaoProduto::getVariablesFromLayout()
{
    QString nTermo = ui->numTermoCautelarLineEdit->text();
    QString nAuto = ui->numAutoLineEdit->text();
    QStringList dateInterd = converteQDateEmStringList(ui->dataInterdicaoDateEdit->date());
    QString horaInterd = converteQTimeEmString(ui->horarioInterdicaoDateEdit->time());
    QString nomeDeposit = ui->nomeDepositarioLineEdit->text();
    QString enderecoDeposit = ui->enderecoDepositarioLineEdit->text();
    QString produtosInterd = ui->produtosInterditadosPlainTextEdit->toPlainText();
    QString usarVer;
    if (ui->checkBoxUsarVerso->checkState() == Qt::CheckState::Checked) {
        usarVer = "sim";
    } else {
        usarVer = "não";
    }
    QString nomeServ = ui->nomeServidorLineEdit->text();
    QString idServ = ui->idServidorLineEdit->text();

    return QStringList{nTermo, nAuto, nomeServ, idServ, nomeDeposit, enderecoDeposit, usarVer, produtosInterd, dateInterd[0], dateInterd[1], dateInterd[2], horaInterd};
    /*
     * 0 - numTermoInterd
     * 1 - numAuto
     * 2 - nomeServidor
     * 3 - idServidor
     * 4 - nomeDepositario
     * 5 - enderecoDepositario
     * 6 - usarVerso
     * 7 - produtosInterditados
     * 8 - diaInterd
     * 9 - mesInterd
     * 10 - anoInterd
     * 11 - horarioInterd
    */
}

void MainWindow::termoInderdicaoCautelarProdutoSemVersoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo de Interdição Cautelar de Produtos ou Substâncias SEM VERSO ODT/content.xml");
    QFile file("modelos/ODT/content.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("office:document-content");
    stream.writeAttribute("xmlns:office", "urn:oasis:names:tc:opendocument:xmlns:office:1.0");
    stream.writeAttribute("xmlns:style", "urn:oasis:names:tc:opendocument:xmlns:style:1.0");
    stream.writeAttribute("xmlns:text", "urn:oasis:names:tc:opendocument:xmlns:text:1.0");
    stream.writeAttribute("xmlns:table", "urn:oasis:names:tc:opendocument:xmlns:table:1.0");
    stream.writeAttribute("xmlns:draw", "urn:oasis:names:tc:opendocument:xmlns:drawing:1.0");
    stream.writeAttribute("xmlns:fo", "urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0");
    stream.writeAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
    stream.writeAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    stream.writeAttribute("xmlns:meta", "urn:oasis:names:tc:opendocument:xmlns:meta:1.0");
    stream.writeAttribute("xmlns:number", "urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0");
    stream.writeAttribute("xmlns:svg", "urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0");
    stream.writeAttribute("xmlns:chart", "urn:oasis:names:tc:opendocument:xmlns:chart:1.0");
    stream.writeAttribute("xmlns:dr3d", "urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0");
    stream.writeAttribute("xmlns:math", "http://www.w3.org/1998/Math/MathML");
    stream.writeAttribute("xmlns:form", "urn:oasis:names:tc:opendocument:xmlns:form:1.0");
    stream.writeAttribute("xmlns:script", "urn:oasis:names:tc:opendocument:xmlns:script:1.0");
    stream.writeAttribute("xmlns:ooo", "http://openoffice.org/2004/office");
    stream.writeAttribute("xmlns:ooow", "http://openoffice.org/2004/writer");
    stream.writeAttribute("xmlns:oooc", "http://openoffice.org/2004/calc");
    stream.writeAttribute("xmlns:dom", "http://www.w3.org/2001/xml-events");
    stream.writeAttribute("xmlns:xforms", "http://www.w3.org/2002/xforms");
    stream.writeAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    stream.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    stream.writeAttribute("xmlns:rpt", "http://openoffice.org/2005/report");
    stream.writeAttribute("xmlns:of", "urn:oasis:names:tc:opendocument:xmlns:of:1.2");
    stream.writeAttribute("xmlns:xhtml", "http://www.w3.org/1999/xhtml");
    stream.writeAttribute("xmlns:grddl", "http://www.w3.org/2003/g/data-view#");
    stream.writeAttribute("xmlns:officeooo", "http://openoffice.org/2009/office");
    stream.writeAttribute("xmlns:tableooo", "http://openoffice.org/2009/table");
    stream.writeAttribute("xmlns:drawooo", "http://openoffice.org/2010/draw");
    stream.writeAttribute("xmlns:calcext", "urn:org:documentfoundation:names:experimental:calc:xmlns:calcext:1.0");
    stream.writeAttribute("xmlns:loext", "urn:org:documentfoundation:names:experimental:office:xmlns:loext:1.0");
    stream.writeAttribute("xmlns:field", "urn:openoffice:names:experimental:ooo-ms-interop:xmlns:field:1.0");
    stream.writeAttribute("xmlns:formx", "urn:openoffice:names:experimental:ooxml-odf-interop:xmlns:form:1.0");
    stream.writeAttribute("xmlns:css3t", "http://www.w3.org/TR/css3-text/");
    stream.writeAttribute("office:version", "1.2");

    stream.writeStartElement("office:scripts");
    stream.writeEndElement(); // office:scripts

    stream.writeStartElement("office:font-face-decls");

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Liberation Serif");
    stream.writeAttribute("svg:font-family", "'Liberation Serif'");
    stream.writeAttribute("style:font-family-generic", "roman");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Liberation Sans");
    stream.writeAttribute("svg:font-family", "'Liberation Sans'");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Lucida Sans");
    stream.writeAttribute("svg:font-family", "'Lucida Sans'");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Microsoft YaHei");
    stream.writeAttribute("svg:font-family", "'Microsoft YaHei'");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "SimSun");
    stream.writeAttribute("svg:font-family", "SimSun");
    stream.writeAttribute("style:font-family-generic", "system");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face
    stream.writeEndElement(); // office:font-face-decls

    stream.writeStartElement("office:automatic-styles");

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1");
    stream.writeAttribute("style:family", "table");
    stream.writeAttribute("style:master-page-name", "MP0");

    stream.writeStartElement("style:table-properties");
    stream.writeAttribute("style:width", "19.001cm");
    stream.writeAttribute("fo:margin-left", "0cm");
    stream.writeAttribute("style:page-number", "auto");
    stream.writeAttribute("table:align", "left");
    stream.writeEndElement(); // style:table-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.702cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.B");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "3.993cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.C");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.805cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.D");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.226cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.E");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.976cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.F");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.496cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.G");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.293cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.H");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "3.51cm");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A1");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.G1");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.B2");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.3");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "1.064cm");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A3");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A4");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A5");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.H5");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A6");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.E6");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.7");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.512cm");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A7");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.E7");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A8");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.9");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "1.088cm");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A10");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.C10");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.F10");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A11");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.A12");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding", "0.097cm");
    stream.writeAttribute("fo:border-left", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Tabela1.D12");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:padding-left", "0.018cm");
    stream.writeAttribute("fo:padding-right", "0.018cm");
    stream.writeAttribute("fo:padding-top", "0cm");
    stream.writeAttribute("fo:padding-bottom", "0cm");
    stream.writeAttribute("fo:border-left", "none");
    stream.writeAttribute("fo:border-right", "0.25pt solid #000000");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.25pt solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P1");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeAttribute("fo:break-before", "page");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P2");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P3");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P4");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P5");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P6");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P7");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Table_20_Contents");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P8");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Text_20_body");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:margin-top", "0cm");
    stream.writeAttribute("fo:margin-bottom", "0cm");
    stream.writeAttribute("loext:contextual-spacing", "false");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T1");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T2");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:letter-kerning", "false");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T3");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T4");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "000533ba");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "fr1");
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:parent-style-name", "Graphics");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("style:vertical-pos", "from-top");
    stream.writeAttribute("style:horizontal-pos", "from-left");
    stream.writeAttribute("style:horizontal-rel", "paragraph-content");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("draw:fill", "none");
    stream.writeAttribute("draw:fill-color", "#ffffff");
    stream.writeAttribute("fo:padding", "0cm");
    stream.writeAttribute("fo:border", "none");
    stream.writeAttribute("style:mirror", "none");
    stream.writeAttribute("fo:clip", "rect(0cm, 0cm, 0cm, 0cm)");
    stream.writeAttribute("draw:luminance", "0%");
    stream.writeAttribute("draw:contrast", "0%");
    stream.writeAttribute("draw:red", "0%");
    stream.writeAttribute("draw:green", "0%");
    stream.writeAttribute("draw:blue", "0%");
    stream.writeAttribute("draw:gamma", "100%");
    stream.writeAttribute("draw:color-inversion", "false");
    stream.writeAttribute("draw:image-opacity", "100%");
    stream.writeAttribute("draw:color-mode", "standard");
    stream.writeEndElement(); // style:graphic-properties
    stream.writeEndElement(); // style:style
    stream.writeEndElement(); // office:automatic-styles

    stream.writeStartElement("office:body");

    stream.writeStartElement("office:text");

    stream.writeStartElement("text:sequence-decls");

    stream.writeStartElement("text:sequence-decl");
    stream.writeAttribute("text:display-outline-level", "0");
    stream.writeAttribute("text:name", "Illustration");
    stream.writeEndElement(); // text:sequence-decl

    stream.writeStartElement("text:sequence-decl");
    stream.writeAttribute("text:display-outline-level", "0");
    stream.writeAttribute("text:name", "Table");
    stream.writeEndElement(); // text:sequence-decl

    stream.writeStartElement("text:sequence-decl");
    stream.writeAttribute("text:display-outline-level", "0");
    stream.writeAttribute("text:name", "Text");
    stream.writeEndElement(); // text:sequence-decl

    stream.writeStartElement("text:sequence-decl");
    stream.writeAttribute("text:display-outline-level", "0");
    stream.writeAttribute("text:name", "Drawing");
    stream.writeEndElement(); // text:sequence-decl
    stream.writeEndElement(); // text:sequence-decls

    stream.writeStartElement("table:table");
    stream.writeAttribute("table:name", "Tabela1");
    stream.writeAttribute("table:style-name", "Tabela1");

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.A");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.B");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.C");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.D");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.E");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.F");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.G");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "Tabela1.H");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A1");
    stream.writeAttribute("table:number-rows-spanned", "2");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P1");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "Fonte_20_parág._20_padrão");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T1");

    stream.writeStartElement("draw:frame");
    stream.writeAttribute("draw:style-name", "fr1");
    stream.writeAttribute("draw:name", "Figura1");
    stream.writeAttribute("text:anchor-type", "as-char");
    stream.writeAttribute("svg:y", "0cm");
    stream.writeAttribute("svg:width", "2.131cm");
    stream.writeAttribute("style:rel-width", "scale");
    stream.writeAttribute("svg:height", "2.651cm");
    stream.writeAttribute("style:rel-height", "scale");
    stream.writeAttribute("draw:z-index", "0");

    QString extensaoImage;
    if (defaultEquipeBrasao.endsWith(".gif")) {
        extensaoImage = "gif";
    } else if (defaultEquipeBrasao.endsWith(".jpg")) {
        extensaoImage = "jpg";
    } else if (defaultEquipeBrasao.endsWith(".jpeg")) {
        extensaoImage = "jpeg";
    } else if (defaultEquipeBrasao.endsWith(".png")) {
        extensaoImage = "png";
    }

    stream.writeStartElement("draw:image");
    stream.writeAttribute("xlink:href", QString("media/image1.%1").arg(extensaoImage));
    stream.writeAttribute("xlink:type", "simple");
    stream.writeAttribute("xlink:show", "embed");
    stream.writeAttribute("xlink:actuate", "onLoad");
    stream.writeEndElement(); // draw:image
    stream.writeEndElement(); // draw:frame
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A1");
    stream.writeAttribute("table:number-columns-spanned", "5");
    stream.writeAttribute("office:value-type", "string");

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P7");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "Fonte_20_parág._20_padrão");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "T2");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    } else {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P2");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.G1");
    stream.writeAttribute("table:number-rows-spanned", "2");
    stream.writeAttribute("table:number-columns-spanned", "2");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P7");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "Fonte_20_parág._20_padrão");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T3");
    stream.writeCharacters(QString("Nº %1").arg(numTermoInterd));
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:span

    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.B2");
    stream.writeAttribute("table:number-columns-spanned", "5");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P2");
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE PRODUTOS");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P2");
    stream.writeCharacters("E/OU SUBSTÂNCIAS");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "Tabela1.3");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A3");
    stream.writeAttribute("table:number-columns-spanned", "8");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P2");
    stream.writeCharacters("IDENTIFICAÇÃO DO DETENTOR");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A4");
    stream.writeAttribute("table:number-columns-spanned", "8");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("NOME/RAZÃO SOCIAL: %1").arg(estabRazaoSocial));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A5");
    stream.writeAttribute("table:number-columns-spanned", "7");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("ENDEREÇO: %1").arg(estabEndereco));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.H5");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A6");
    stream.writeAttribute("table:number-columns-spanned", "4");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.E6");
    stream.writeAttribute("table:number-columns-spanned", "4");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "Tabela1.7");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A7");
    stream.writeAttribute("table:number-columns-spanned", "4");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.E7");
    stream.writeAttribute("table:number-columns-spanned", "4");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A8");
    stream.writeAttribute("table:number-columns-spanned", "8");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P8");
    stream.writeCharacters(QString("Ao(s) %1 dias do mês de %2 do ano de %3, às %4 minutos, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º, da Lei Federal nº 6437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote(s), data de fabricação e/ou prazo de validade, conforme a seguir: ").arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd));

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P8");
    stream.writeCharacters(QString("%1").arg(produtosInterditados));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P8");
    stream.writeCharacters(QString(" pela(s) seguinte(s) irregularidade(s): %1, tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %2").arg(irregularidades).arg(dispositivos));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P8");
    stream.writeCharacters(QString(", conforme Auto de Infração Sanitária nº %1. O(s) produto(s) e/ou substância(s) interditado(s) fica(m) em poder de %2, situado na %3, que se compromete a não vender, remover, dar ao consumo, desviar ou substituir, até ulterior deliberação da autoridade sanitária competente desta Secretaria, constituindo-se em seu fiel depositário para todos os efeitos da Lei Civil e ficando bem ciente que deverá apresentar o(s) aludido(s) produto(s) e/ou substância(s), quando solicitado, sob pena de responsabilização no âmbito administrativo.").arg(numAuto).arg(nomeDepositario).arg(enderecoDepositario));
    stream.writeEndElement(); // text:span

    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "Tabela1.9");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A3");
    stream.writeAttribute("table:number-columns-spanned", "8");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P2");
    stream.writeCharacters("CIÊNCIA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A10");
    stream.writeAttribute("table:number-columns-spanned", "2");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P6");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters(QString("Nome: %1.").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters(QString("Identidade Funcional: %1.").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.C10");
    stream.writeAttribute("table:number-columns-spanned", "3");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P6");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("Nome: __________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("RG/CPF: ________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.F10");
    stream.writeAttribute("table:number-columns-spanned", "3");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P6");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("Nome: ____________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("RG/CPF: __________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A11");
    stream.writeAttribute("table:number-columns-spanned", "8");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.A12");
    stream.writeAttribute("table:number-columns-spanned", "3");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "Tabela1.D12");
    stream.writeAttribute("table:number-columns-spanned", "5");
    stream.writeAttribute("office:value-type", "string");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row
    stream.writeEndElement(); // table:table

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // office:text
    stream.writeEndElement(); // office:body
    stream.writeEndElement(); // office:document-content

    stream.writeEndDocument();

    file.close();

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Produtos ou Substâncias SEM VERSO ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoInderdicaoCautelarProdutoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo de Interdição Cautelar de Produtos ou Substâncias DOCX/word/document.xml");
    QFile file("modelos/DOCX/word/document.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:document");
    stream.writeAttribute("xmlns:wpc", "http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas");
    stream.writeAttribute("xmlns:cx", "http://schemas.microsoft.com/office/drawing/2014/chartex");
    stream.writeAttribute("xmlns:cx1", "http://schemas.microsoft.com/office/drawing/2015/9/8/chartex");
    stream.writeAttribute("xmlns:cx2", "http://schemas.microsoft.com/office/drawing/2015/10/21/chartex");
    stream.writeAttribute("xmlns:cx3", "http://schemas.microsoft.com/office/drawing/2016/5/9/chartex");
    stream.writeAttribute("xmlns:cx4", "http://schemas.microsoft.com/office/drawing/2016/5/10/chartex");
    stream.writeAttribute("xmlns:cx5", "http://schemas.microsoft.com/office/drawing/2016/5/11/chartex");
    stream.writeAttribute("xmlns:cx6", "http://schemas.microsoft.com/office/drawing/2016/5/12/chartex");
    stream.writeAttribute("xmlns:cx7", "http://schemas.microsoft.com/office/drawing/2016/5/13/chartex");
    stream.writeAttribute("xmlns:cx8", "http://schemas.microsoft.com/office/drawing/2016/5/14/chartex");
    stream.writeAttribute("xmlns:mc", "http://schemas.openxmlformats.org/markup-compatibility/2006");
    stream.writeAttribute("xmlns:aink", "http://schemas.microsoft.com/office/drawing/2016/ink");
    stream.writeAttribute("xmlns:am3d", "http://schemas.microsoft.com/office/drawing/2017/model3d");
    stream.writeAttribute("xmlns:o", "urn:schemas-microsoft-com:office:office");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:m", "http://schemas.openxmlformats.org/officeDocument/2006/math");
    stream.writeAttribute("xmlns:v", "urn:schemas-microsoft-com:vml");
    stream.writeAttribute("xmlns:wp14", "http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing");
    stream.writeAttribute("xmlns:wp", "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
    stream.writeAttribute("xmlns:w10", "urn:schemas-microsoft-com:office:word");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    stream.writeAttribute("xmlns:w14", "http://schemas.microsoft.com/office/word/2010/wordml");
    stream.writeAttribute("xmlns:w15", "http://schemas.microsoft.com/office/word/2012/wordml");
    stream.writeAttribute("xmlns:w16cex", "http://schemas.microsoft.com/office/word/2018/wordml/cex");
    stream.writeAttribute("xmlns:w16cid", "http://schemas.microsoft.com/office/word/2016/wordml/cid");
    stream.writeAttribute("xmlns:w16", "http://schemas.microsoft.com/office/word/2018/wordml");
    stream.writeAttribute("xmlns:w16se", "http://schemas.microsoft.com/office/word/2015/wordml/symex");
    stream.writeAttribute("xmlns:wpg", "http://schemas.microsoft.com/office/word/2010/wordprocessingGroup");
    stream.writeAttribute("xmlns:wpi", "http://schemas.microsoft.com/office/word/2010/wordprocessingInk");
    stream.writeAttribute("xmlns:wne", "http://schemas.microsoft.com/office/word/2006/wordml");
    stream.writeAttribute("xmlns:wps", "http://schemas.microsoft.com/office/word/2010/wordprocessingShape");
    stream.writeAttribute("mc:Ignorable", "w14 w15 w16se w16cid w16 w16cex wp14");

    stream.writeStartElement("w:body");

    stream.writeStartElement("w:tbl");

    stream.writeStartElement("w:tblPr");

    stream.writeStartElement("w:tblW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tblW

    stream.writeStartElement("w:tblLayout");
    stream.writeAttribute("w:type", "fixed");
    stream.writeEndElement(); // w:tblLayout

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tblCellMar

    stream.writeStartElement("w:tblLook");
    stream.writeAttribute("w:val", "04A0");
    stream.writeAttribute("w:firstRow", "1");
    stream.writeAttribute("w:lastRow", "0");
    stream.writeAttribute("w:firstColumn", "1");
    stream.writeAttribute("w:lastColumn", "0");
    stream.writeAttribute("w:noHBand", "0");
    stream.writeAttribute("w:noVBand", "1");
    stream.writeEndElement(); // w:tblLook
    stream.writeEndElement(); // w:tblPr

    stream.writeStartElement("w:tblGrid");

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1532");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "2264");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1590");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "128");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1687");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1415");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "166");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1990");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "25E31C9A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1532");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:vMerge");
    stream.writeAttribute("w:val", "restart");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0E9FB82E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:noProof");
    stream.writeEndElement(); // w:noProof

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:drawing");

    stream.writeStartElement("wp:inline");
    stream.writeAttribute("distT", "0");
    stream.writeAttribute("distB", "0");
    stream.writeAttribute("distL", "0");
    stream.writeAttribute("distR", "0");
    stream.writeAttribute("wp14:anchorId", "0B9395A2");
    stream.writeAttribute("wp14:editId", "37E016E8");

    stream.writeStartElement("wp:extent");
    stream.writeAttribute("cx", "767159");
    stream.writeAttribute("cy", "954359");
    stream.writeEndElement(); // wp:extent

    stream.writeStartElement("wp:effectExtent");
    stream.writeAttribute("l", "0");
    stream.writeAttribute("t", "0");
    stream.writeAttribute("r", "0");
    stream.writeAttribute("b", "0");
    stream.writeEndElement(); // wp:effectExtent

    stream.writeStartElement("wp:docPr");
    stream.writeAttribute("id", "1");
    stream.writeAttribute("name", "Figura1");
    stream.writeEndElement(); // wp:docPr

    stream.writeStartElement("wp:cNvGraphicFramePr");
    stream.writeEndElement(); // wp:cNvGraphicFramePr

    stream.writeStartElement("a:graphic");
    stream.writeAttribute("xmlns:a", "http://schemas.openxmlformats.org/drawingml/2006/main");

    stream.writeStartElement("a:graphicData");
    stream.writeAttribute("uri", "http://schemas.openxmlformats.org/drawingml/2006/picture");

    stream.writeStartElement("pic:pic");
    stream.writeAttribute("xmlns:pic", "http://schemas.openxmlformats.org/drawingml/2006/picture");

    stream.writeStartElement("pic:nvPicPr");

    stream.writeStartElement("pic:cNvPr");
    stream.writeAttribute("id", "0");
    stream.writeAttribute("name", "");
    stream.writeEndElement(); // pic:cNvPr

    stream.writeStartElement("pic:cNvPicPr");
    stream.writeEndElement(); // pic:cNvPicPr
    stream.writeEndElement(); // pic:nvPicPr

    stream.writeStartElement("pic:blipFill");

    stream.writeStartElement("a:blip");
    stream.writeAttribute("r:embed", "rId6");

    stream.writeStartElement("a:lum");
    stream.writeEndElement(); // a:lum

    stream.writeStartElement("a:alphaModFix");
    stream.writeEndElement(); // a:alphaModFix
    stream.writeEndElement(); // a:blip

    stream.writeStartElement("a:srcRect");
    stream.writeEndElement(); // a:srcRect

    stream.writeStartElement("a:stretch");

    stream.writeStartElement("a:fillRect");
    stream.writeEndElement(); // a:fillRect
    stream.writeEndElement(); // a:stretch
    stream.writeEndElement(); // pic:blipFill

    stream.writeStartElement("pic:spPr");

    stream.writeStartElement("a:xfrm");

    stream.writeStartElement("a:off");
    stream.writeAttribute("x", "0");
    stream.writeAttribute("y", "0");
    stream.writeEndElement(); // a:off

    stream.writeStartElement("a:ext");
    stream.writeAttribute("cx", "767159");
    stream.writeAttribute("cy", "954359");
    stream.writeEndElement(); // a:ext
    stream.writeEndElement(); // a:xfrm

    stream.writeStartElement("a:prstGeom");
    stream.writeAttribute("prst", "rect");

    stream.writeStartElement("a:avLst");
    stream.writeEndElement(); // a:avLst
    stream.writeEndElement(); // a:prstGeom
    stream.writeEndElement(); // pic:spPr
    stream.writeEndElement(); // pic:pic
    stream.writeEndElement(); // a:graphicData
    stream.writeEndElement(); // a:graphic
    stream.writeEndElement(); // wp:inline
    stream.writeEndElement(); // w:drawing
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "20697DAD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    if (defaultEquipeTipo == "Estadual") {
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
    } else {
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
    }
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0A071BD6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("SECRETARIA DA SAÚDE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("w:p");
        stream.writeAttribute("w14:paraId", "4DC386E1");
        stream.writeAttribute("w14:textId", "55D25A2B");
        stream.writeAttribute("w:rsidR", "00094496");
        stream.writeAttribute("w:rsidRDefault", "00CE1B98");

        stream.writeStartElement("w:pPr");

        stream.writeStartElement("w:pStyle");
        stream.writeAttribute("w:val", "TableContents");
        stream.writeEndElement(); // w:pStyle

        stream.writeStartElement("w:jc");
        stream.writeAttribute("w:val", "center");
        stream.writeEndElement(); // w:jc

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr
        stream.writeEndElement(); // w:pPr

        stream.writeStartElement("w:r");

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr

        stream.writeStartElement("w:t");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r
        stream.writeEndElement(); // w:p

        stream.writeStartElement("w:p");
        stream.writeAttribute("w14:paraId", "01DA00E9");
        stream.writeAttribute("w14:textId", "27F919FC");
        stream.writeAttribute("w:rsidR", "00B77085");
        stream.writeAttribute("w:rsidRDefault", "00B77085");

        stream.writeStartElement("w:pPr");

        stream.writeStartElement("w:pStyle");
        stream.writeAttribute("w:val", "TableContents");
        stream.writeEndElement(); // w:pStyle

        stream.writeStartElement("w:jc");
        stream.writeAttribute("w:val", "center");
        stream.writeEndElement(); // w:jc

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr
        stream.writeEndElement(); // w:pPr

        stream.writeStartElement("w:r");

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:kern");
        stream.writeAttribute("w:val", "0");
        stream.writeEndElement(); // w:kern

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr

        stream.writeStartElement("w:t");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r

        stream.writeStartElement("w:bookmarkStart");
        stream.writeAttribute("w:id", "0");
        stream.writeAttribute("w:name", "_GoBack");
        stream.writeEndElement(); // w:bookmarkStart

        stream.writeStartElement("w:bookmarkEnd");
        stream.writeAttribute("w:id", "0");
        stream.writeEndElement(); // w:bookmarkEnd
        stream.writeEndElement(); // w:p
    }

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "611A5109");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "2156");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:vMerge");
    stream.writeAttribute("w:val", "restart");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "49A3A44E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nº %1").arg(numTermoInterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    /*stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r*/
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "39FA73A1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1532");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:vMerge");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "14CD18BD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "008109A6");
    stream.writeAttribute("w:rsidRDefault", "008109A6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1B3AC781");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE PRODUTOS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "39046639");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("E/OU SUBSTÂNCIAS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "2156");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:vMerge");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "78D261AF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "008109A6");
    stream.writeAttribute("w:rsidRDefault", "008109A6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "2F1B3A96");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "603");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5832C778");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("IDENTIFICAÇÃO DO DETENTOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "0CE252DF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "42A346DD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("NOME/RAZÃO SOCIAL: %1").arg(estabRazaoSocial));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "5325B61D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "8782");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "7");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6191EC88");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("ENDEREÇO: %1").arg(estabEndereco));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1990");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "362C0E19");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "5FB419AC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "68C858FD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5258");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "690AD5AC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "0104EC20");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "290");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1B49D4CC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5258");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7A754C81");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "68A3D9E3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "34E33376");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Ao(s) %1 dias do mês de %2 do ano de %3, às %4, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º da Lei Federal nº 6.437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(s) produtos(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote, data de fabricação e/ou prazo de validade, conforme verso do presente Termo pela(s) seguinte(s) irregularidade(s) %5, tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %6, conforme Auto de Infração Sanitária nº %7. O(s) produto(s) e/ou subtância(s) interditado(s) fica(m) em poder de %8, situado na %9, que se compromete a não vender, remover, dar ao consumo, desviar ou substituir, até ulterior deliberação da autoridade sanitária competente desta Secretaria, constituindo-se em seu fiel despositário para todos os efeitos da Lei Civil e ficando bem ciente que deverá apresentar o(s) aludido(s) produto(s) e/ou subtância(s), quando solicitado, sob pena de responsabilização no âmbito administrativo.")
    .arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd).arg(irregularidades).arg(dispositivos).arg(numAuto).arg(nomeDepositario).arg(enderecoDepositario));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0B39F350");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "493800F1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0488FA94");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1601B378");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5A4EC2CE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("pela(s) seguinte(s) irregularidade(s): ____________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1A944C3A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "463D1C6B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "31781C6C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "67E7361F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("___________________, tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): _____________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2C1429C4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1C930A43");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4FFD7FCF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________, conforme Auto de Infração Sanitária nº ______/_____. O(s) produto(s) e/ou substância(s) interditado(s) fica(m) em poder de");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4B1D0F60");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("______________________________________________________, situado na __________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "34E3B449");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1E882944");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_________________, que se compromete a não vender, remover, dar ao consumo, desviar ou substituir, até ulterior deliberação da autoridade sanitária competente desta Secretaria, constituindo-se em seu fiel depositário para todos os efeitos da Lei Civil e ficando bem ciente que deverá apresentar o(s) aludido(s) produto(s) e/ou substância(s), quando solicitado, sob pena de responsabilização no âmbito administrativo.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "789CB59B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "617");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "70EABE8A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("CIÊNCIA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "1E98C734");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3796");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2EEFF6B8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "46D8AA9D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0116249A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4986DA12");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5568D23C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nome: %1.").arg(nomeServidor));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "31562A1B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Identidade Funcional: %1.").arg(idServidor));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3405");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "519A0D46");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1DFC0A80");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "692BA2B2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4A0D6A78");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7FBA5555");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("Nome: __________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2A68929E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("RG/CPF: ________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3571");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "08CD913E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5149A2D5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "10F89EC6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2CEFB9CB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "03B76C81");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("Nome: ____________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2ECA367B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("RG/CPF: __________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w14:paraId", "459E7727");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "60BE5827");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3506169E");
    stream.writeAttribute("w14:textId", "797E11A3");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w14:paraId", "0B35CFFD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "637C99C5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7776B241");
    stream.writeAttribute("w14:textId", "497D4B5B");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "09AB0EAC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1FA15490");
    stream.writeAttribute("w14:textId", "03A580F0");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr
    stream.writeEndElement(); // w:tbl

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6B4DDF25");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "25766F53");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4B9997BF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5E5F56FF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0A9961F6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("O rol abaixo integra o histórico do presente Termo de Interdição Cautelar de Produtos e/ou Substâncias Nº %1, para todos os efeitos legais.").arg(numTermoInterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:tbl");

    stream.writeStartElement("w:tblPr");

    stream.writeStartElement("w:tblW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tblW

    stream.writeStartElement("w:tblLayout");
    stream.writeAttribute("w:type", "fixed");
    stream.writeEndElement(); // w:tblLayout

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tblCellMar

    stream.writeStartElement("w:tblLook");
    stream.writeAttribute("w:val", "04A0");
    stream.writeAttribute("w:firstRow", "1");
    stream.writeAttribute("w:lastRow", "0");
    stream.writeAttribute("w:firstColumn", "1");
    stream.writeAttribute("w:lastColumn", "0");
    stream.writeAttribute("w:noHBand", "0");
    stream.writeAttribute("w:noVBand", "1");
    stream.writeEndElement(); // w:tblLook
    stream.writeEndElement(); // w:tblPr

    stream.writeStartElement("w:tblGrid");

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3796");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1590");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1815");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3571");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "493BD64A");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "394FCE5E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("%1").arg(produtosInterditados));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "45ACC83C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "108A88B5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2DAB323D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1BB327A1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4303FA52");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0AA6E36D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3F6F7296");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "318BC1DB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5998AE79");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "516A2F79");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "71AC14CA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "71A66F6F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "190DDE74");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "441BB59F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7613786A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "63FF6AAC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "58AC458A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "63F49F0A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3A862FA7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "48DEFE85");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2DD720E4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "311585DF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "21BD9AF3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "01EE1514");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "25AB479B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "36E6C6A6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4E5FA7C5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "46B405C3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "034DD17A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5B69DB4F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "070F4311");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6F8C93BA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7F0C3B61");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "134EFF56");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "58A64CE6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7EE0F868");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "17A69A5B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6D7C502D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/

    /*stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "551CB440");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________________________________________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p*/
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "55B0752F");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "617");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1798A2F6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("RUBRICAS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w14:paraId", "1324D357");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3796");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6D8C604B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3D56FD61");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4D434DE0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2A0F69D6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3405");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2C5BF9F4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5F90DCDB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5375A7E2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "63B65946");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3571");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "658BB9E7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3C67CD34");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "75380826");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "019D85DB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w14:paraId", "70222AA0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "000E485A");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "760E878E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5C45783A");
    stream.writeAttribute("w14:textId", "2F19B9B4");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");
    stream.writeAttribute("w:rsidP", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w14:paraId", "4022311F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "000E485A");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2BECB611");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");
    stream.writeAttribute("w:rsidP", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:lastRenderedPageBreak");
    stream.writeEndElement(); // w:lastRenderedPageBreak

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "25109982");
    stream.writeAttribute("w14:textId", "6997B7C5");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");
    stream.writeAttribute("w:rsidP", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3EE622F3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");
    stream.writeAttribute("w:rsidP", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "08DDCD86");
    stream.writeAttribute("w14:textId", "7C720197");
    stream.writeAttribute("w:rsidR", "000E485A");
    stream.writeAttribute("w:rsidRDefault", "000E485A");
    stream.writeAttribute("w:rsidP", "000E485A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr
    stream.writeEndElement(); // w:tbl

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "69CA28FE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00094496");

    stream.writeStartElement("w:pgSz");
    stream.writeAttribute("w:w", "11906");
    stream.writeAttribute("w:h", "16838");
    stream.writeEndElement(); // w:pgSz

    stream.writeStartElement("w:pgMar");
    stream.writeAttribute("w:top", "1134");
    stream.writeAttribute("w:right", "567");
    stream.writeAttribute("w:bottom", "1134");
    stream.writeAttribute("w:left", "567");
    stream.writeAttribute("w:header", "720");
    stream.writeAttribute("w:footer", "720");
    stream.writeAttribute("w:gutter", "0");
    stream.writeEndElement(); // w:pgMar

    stream.writeStartElement("w:cols");
    stream.writeAttribute("w:space", "720");
    stream.writeEndElement(); // w:cols
    stream.writeEndElement(); // w:sectPr
    stream.writeEndElement(); // w:body
    stream.writeEndElement(); // w:document

    stream.writeEndDocument();

    file.close();

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Produtos ou Substâncias DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}

void MainWindow::termoInderdicaoCautelarProdutoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo de Interdição Cautelar de Produtos ou Substâncias ODT/content.xml");
    QFile file("modelos/ODT/content.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("office:document-content");
    stream.writeAttribute("xmlns:anim", "urn:oasis:names:tc:opendocument:xmlns:animation:1.0");
    stream.writeAttribute("xmlns:chart", "urn:oasis:names:tc:opendocument:xmlns:chart:1.0");
    stream.writeAttribute("xmlns:config", "urn:oasis:names:tc:opendocument:xmlns:config:1.0");
    stream.writeAttribute("xmlns:db", "urn:oasis:names:tc:opendocument:xmlns:database:1.0");
    stream.writeAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    stream.writeAttribute("xmlns:dr3d", "urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0");
    stream.writeAttribute("xmlns:draw", "urn:oasis:names:tc:opendocument:xmlns:drawing:1.0");
    stream.writeAttribute("xmlns:fo", "urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0");
    stream.writeAttribute("xmlns:form", "urn:oasis:names:tc:opendocument:xmlns:form:1.0");
    stream.writeAttribute("xmlns:grddl", "http://www.w3.org/2003/g/data-view#");
    stream.writeAttribute("xmlns:math", "http://www.w3.org/1998/Math/MathML");
    stream.writeAttribute("xmlns:meta", "urn:oasis:names:tc:opendocument:xmlns:meta:1.0");
    stream.writeAttribute("xmlns:number", "urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0");
    stream.writeAttribute("xmlns:office", "urn:oasis:names:tc:opendocument:xmlns:office:1.0");
    stream.writeAttribute("xmlns:presentation", "urn:oasis:names:tc:opendocument:xmlns:presentation:1.0");
    stream.writeAttribute("xmlns:script", "urn:oasis:names:tc:opendocument:xmlns:script:1.0");
    stream.writeAttribute("xmlns:smil", "urn:oasis:names:tc:opendocument:xmlns:smil-compatible:1.0");
    stream.writeAttribute("xmlns:style", "urn:oasis:names:tc:opendocument:xmlns:style:1.0");
    stream.writeAttribute("xmlns:svg", "urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0");
    stream.writeAttribute("xmlns:table", "urn:oasis:names:tc:opendocument:xmlns:table:1.0");
    stream.writeAttribute("xmlns:text", "urn:oasis:names:tc:opendocument:xmlns:text:1.0");
    stream.writeAttribute("xmlns:xforms", "http://www.w3.org/2002/xforms");
    stream.writeAttribute("xmlns:xhtml", "http://www.w3.org/1999/xhtml");
    stream.writeAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
    stream.writeAttribute("office:version", "1.2");

    stream.writeStartElement("office:font-face-decls");

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Liberation Serif");
    stream.writeAttribute("svg:font-family", "Liberation Serif");
    stream.writeAttribute("style:font-family-generic", "roman");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 2 6 3 5 4 5 2 3 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "SimSun");
    stream.writeAttribute("svg:font-family", "SimSun");
    stream.writeAttribute("style:font-family-generic", "system");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 1 6 0 3 1 1 1 1 1");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Lucida Sans");
    stream.writeAttribute("svg:font-family", "Lucida Sans");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 11 6 2 3 5 4 2 2 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Times New Roman");
    stream.writeAttribute("svg:font-family", "Times New Roman");
    stream.writeAttribute("style:font-family-generic", "roman");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 2 6 3 5 4 5 2 3 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Liberation Sans");
    stream.writeAttribute("svg:font-family", "Liberation Sans");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 11 6 4 2 2 2 2 2 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Microsoft YaHei");
    stream.writeAttribute("svg:font-family", "Microsoft YaHei");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 11 5 3 2 2 4 2 2 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Calibri Light");
    stream.writeAttribute("svg:font-family", "Calibri Light");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 15 3 2 2 2 4 3 2 4");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Calibri");
    stream.writeAttribute("svg:font-family", "Calibri");
    stream.writeAttribute("style:font-family-generic", "swiss");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeAttribute("svg:panose-1", "2 15 5 2 2 2 4 3 2 4");
    stream.writeEndElement(); // style:font-face
    stream.writeEndElement(); // office:font-face-decls

    stream.writeStartElement("office:automatic-styles");

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn2");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.0638in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn3");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.5722in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn4");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.1041in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn5");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.0888in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn6");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.1715in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn7");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.9826in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn8");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.1152in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn9");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.3819in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Table1");
    stream.writeAttribute("style:family", "table");
    stream.writeAttribute("style:master-page-name", "MP0");

    stream.writeStartElement("style:table-properties");
    stream.writeAttribute("style:width", "7.4805in");
    stream.writeAttribute("fo:margin-left", "0in");
    stream.writeAttribute("table:align", "left");
    stream.writeEndElement(); // style:table-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow10");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell11");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P12");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:break-before", "page");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T13");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell14");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P15");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P16");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P17");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P18");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T19");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("style:letter-kerning", "false");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P20");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell21");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P22");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T23");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T24");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow25");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell26");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P27");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P28");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow29");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4187in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell30");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P31");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow32");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell33");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P34");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow35");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell36");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P37");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell38");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P39");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow40");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell41");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P42");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell43");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P44");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow45");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.2013in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell46");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P47");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell48");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P49");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow50");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell51");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P52");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P53");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P54");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P55");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P56");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P57");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P58");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P59");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P60");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P61");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P62");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P63");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P64");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P65");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P66");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P67");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow68");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell69");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P70");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow71");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell72");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P73");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P74");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P75");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P76");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P77");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P78");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell79");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P80");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P81");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P82");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P83");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P84");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P85");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell86");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P87");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P88");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P89");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P90");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P91");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P92");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow93");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell94");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "none");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P95");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P96");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow97");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell98");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P99");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P100");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell101");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "none");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0in");
    stream.writeAttribute("fo:padding-left", "0.0069in");
    stream.writeAttribute("fo:padding-bottom", "0in");
    stream.writeAttribute("fo:padding-right", "0.0069in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P102");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P103");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P104");
    stream.writeAttribute("style:parent-style-name", "Standard");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn106");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.6361in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn107");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.1041in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn108");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.2604in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn109");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.4798in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Table105");
    stream.writeAttribute("style:family", "table");

    stream.writeStartElement("style:table-properties");
    stream.writeAttribute("style:width", "7.4805in");
    stream.writeAttribute("fo:margin-left", "0in");
    stream.writeAttribute("table:align", "left");
    stream.writeEndElement(); // style:table-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow110");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell111");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P112");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P113");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P114");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P115");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P116");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P117");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P118");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P119");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P120");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P121");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P122");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P123");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P124");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P125");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P126");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P127");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P128");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P129");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P130");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P131");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P132");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P133");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P134");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P135");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P136");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P137");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P138");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P139");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P140");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P141");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P142");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P143");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P144");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P145");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P146");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P147");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P148");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P149");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P150");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P151");
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "115%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow152");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell153");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P154");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow155");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell156");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P157");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P158");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P159");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P160");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell161");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P162");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P163");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P164");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P165");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell166");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P167");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P168");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P169");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P170");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow171");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell172");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "none");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P173");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P174");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow175");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell176");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P177");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P178");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell179");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "none");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0in");
    stream.writeAttribute("fo:padding-left", "0.0069in");
    stream.writeAttribute("fo:padding-bottom", "0in");
    stream.writeAttribute("fo:padding-right", "0.0069in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P180");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P181");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:name", "a0");
    stream.writeAttribute("style:parent-style-name", "Graphics");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("fo:border", "0.01042in none");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("fo:clip", "rect(0in, 0in, 0in, 0in)");
    stream.writeAttribute("draw:luminance", "0%");
    stream.writeAttribute("draw:contrast", "0%");
    stream.writeAttribute("draw:image-opacity", "100%");
    stream.writeEndElement(); // style:graphic-properties
    stream.writeEndElement(); // style:style
    stream.writeEndElement(); // office:automatic-styles

    stream.writeStartElement("office:body");

    stream.writeStartElement("office:text");
    stream.writeAttribute("text:use-soft-page-breaks", "true");

    stream.writeStartElement("table:table");
    stream.writeAttribute("table:style-name", "Table1");

    stream.writeStartElement("table:table-columns");

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn2");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn3");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn4");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn5");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn6");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn7");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn8");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn9");
    stream.writeEndElement(); // table:table-column
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow10");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell11");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P12");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T13");

    stream.writeStartElement("draw:frame");
    stream.writeAttribute("draw:style-name", "a0");
    stream.writeAttribute("draw:name", "Figura1");
    stream.writeAttribute("text:anchor-type", "as-char");
    stream.writeAttribute("svg:x", "0in");
    stream.writeAttribute("svg:y", "0in");
    stream.writeAttribute("svg:width", "0.83898in");
    stream.writeAttribute("svg:height", "1.0437in");
    stream.writeAttribute("style:rel-width", "scale");
    stream.writeAttribute("style:rel-height", "scale");

    QString extensaoImage;
    if (defaultEquipeBrasao.endsWith(".gif")) {
        extensaoImage = "gif";
    } else if (defaultEquipeBrasao.endsWith(".jpg")) {
        extensaoImage = "jpg";
    } else if (defaultEquipeBrasao.endsWith(".jpeg")) {
        extensaoImage = "jpeg";
    } else if (defaultEquipeBrasao.endsWith(".png")) {
        extensaoImage = "png";
    }

    stream.writeStartElement("draw:image");
    stream.writeAttribute("xlink:href", QString("media/image1.%1").arg(extensaoImage));
    stream.writeAttribute("xlink:type", "simple");
    stream.writeAttribute("xlink:show", "embed");
    stream.writeAttribute("xlink:actuate", "onLoad");
    stream.writeEndElement(); // draw:image

    stream.writeStartElement("svg:title");
    stream.writeEndElement(); // svg:title

    stream.writeStartElement("svg:desc");
    stream.writeEndElement(); // svg:desc
    stream.writeEndElement(); // draw:frame
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell14");
    stream.writeAttribute("table:number-columns-spanned", "5");

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P16");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P17");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P18");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "T19");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P20");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    } else {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P16");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P20");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell21");
    stream.writeAttribute("table:number-columns-spanned", "2");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P22");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T23");
    stream.writeCharacters(QString("Nº %1").arg(numAuto));
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow25");

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Normal");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell26");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P27");
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE PRODUTOS");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P28");
    stream.writeCharacters("E/OU SUBSTÂNCIAS");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Normal");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow29");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell30");
    stream.writeAttribute("table:number-columns-spanned", "8");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P31");
    stream.writeCharacters("IDENTIFICAÇÃO DO DETENTOR");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow32");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell33");
    stream.writeAttribute("table:number-columns-spanned", "8");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P34");
    stream.writeCharacters(QString("NOME/RAZÃO SOCIAL: %1").arg(estabRazaoSocial));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow35");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell36");
    stream.writeAttribute("table:number-columns-spanned", "7");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P37");
    stream.writeCharacters(QString("ENDEREÇO: %1").arg(estabEndereco));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell38");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P39");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow40");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell41");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P42");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell43");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P44");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow45");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell46");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P47");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell48");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P49");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow50");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell51");
    stream.writeAttribute("table:number-columns-spanned", "8");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P52");
    stream.writeCharacters(QString("Ao(s) %1 dias do mês de %2 do ano de %3, às %4, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º, da Lei Federal nº 6437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote(s), data de fabricação e/ou prazo de validade, conforme verso do presente Termo, pela(s) seguinte(s) irregularidade(s): ").arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd));

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P53");
    stream.writeCharacters(QString("%1").arg(irregularidades));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P61");
    stream.writeCharacters(QString(", tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %1, conforme Auto de Infração Sanitária nº %2. O(s) produto(s) e/ou substância(s) interditado(s) fica(m) em poder de %3, situado na %4").arg(dispositivos).arg(numAuto).arg(nomeDepositario).arg(enderecoDepositario));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P67");
    stream.writeCharacters(", que se compromete a não vender, remover, dar ao consumo, desviar ou substituir, até ulterior deliberação da autoridade sanitária competente desta Secretaria, constituindo-se em seu fiel depositário para todos os efeitos da Lei Civil e ficando bem ciente que deverá apresentar o(s) aludido(s) produto(s) e/ou substância(s), quando solicitado, sob pena de responsabilização no âmbito administrativo.");
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow68");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell69");
    stream.writeAttribute("table:number-columns-spanned", "8");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P70");
    stream.writeCharacters("CIÊNCIA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow71");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell72");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P73");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P74");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P75");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P76");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P77");
    stream.writeCharacters(QString("Nome: %1.").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P78");
    stream.writeCharacters(QString("Identidade Funcional: %1.").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell79");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P80");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P81");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P82");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P83");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P84");
    stream.writeCharacters("Nome: __________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P85");
    stream.writeCharacters("RG/CPF: ________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell86");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P87");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P88");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P89");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P90");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P91");
    stream.writeCharacters("Nome: ____________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P92");
    stream.writeCharacters("RG/CPF: __________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow93");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell94");
    stream.writeAttribute("table:number-columns-spanned", "8");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P95");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P96");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow97");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell98");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P99");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P100");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell101");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P102");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P103");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row
    stream.writeEndElement(); // table:table

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P104");
    stream.writeCharacters(QString("O rol abaixo integra o histórico do presente Termo de Interdição Cautelar de Produtos e/ou Substâncias Nº %1, para todos os efeitos legais.").arg(numTermoInterd));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("table:table");
    stream.writeAttribute("table:style-name", "Table105");

    stream.writeStartElement("table:table-columns");

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn106");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn107");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn108");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn109");
    stream.writeEndElement(); // table:table-column
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow110");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell111");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P112");
    stream.writeCharacters(QString("%1").arg(produtosInterditados));
    stream.writeEndElement(); // text:p

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow152");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell153");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P154");
    stream.writeCharacters("RUBRICAS");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow155");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell156");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P157");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P158");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P159");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P160");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell161");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P162");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P163");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P164");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P165");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell166");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P167");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P168");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P169");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P170");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow171");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell172");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P173");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P174");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("text:soft-page-break");
    stream.writeEndElement(); // text:soft-page-break

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow175");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell176");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P177");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P178");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell179");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P180");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P181");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row
    stream.writeEndElement(); // table:table

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Standard");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // office:text
    stream.writeEndElement(); // office:body
    stream.writeEndElement(); // office:document-content

    stream.writeEndDocument();

    file.close();

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Produtos ou Substâncias ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoInderdicaoCautelarProdutoSemVersoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo de Interdição Cautelar de Produtos ou Substâncias SEM VERSO DOCX/word/document.xml");
    QFile file("modelos/DOCX/word/document.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:document");
    stream.writeAttribute("xmlns:ve", "http://schemas.openxmlformats.org/markup-compatibility/2006");
    stream.writeAttribute("xmlns:o", "urn:schemas-microsoft-com:office:office");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:m", "http://schemas.openxmlformats.org/officeDocument/2006/math");
    stream.writeAttribute("xmlns:v", "urn:schemas-microsoft-com:vml");
    stream.writeAttribute("xmlns:wp", "http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing");
    stream.writeAttribute("xmlns:w10", "urn:schemas-microsoft-com:office:word");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    stream.writeAttribute("xmlns:wne", "http://schemas.microsoft.com/office/word/2006/wordml");

    stream.writeStartElement("w:body");

    stream.writeStartElement("w:tbl");

    stream.writeStartElement("w:tblPr");

    stream.writeStartElement("w:tblW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tblW

    stream.writeStartElement("w:tblLayout");
    stream.writeAttribute("w:type", "fixed");
    stream.writeEndElement(); // w:tblLayout

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "10");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tblCellMar

    stream.writeStartElement("w:tblLook");
    stream.writeAttribute("w:val", "04A0");
    stream.writeEndElement(); // w:tblLook
    stream.writeEndElement(); // w:tblPr

    stream.writeStartElement("w:tblGrid");

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1532");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "2264");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1590");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "128");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1687");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1415");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "166");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1990");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1532");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:vMerge");
    stream.writeAttribute("w:val", "restart");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:noProof");
    stream.writeEndElement(); // w:noProof

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs

    stream.writeStartElement("w:lang");
    stream.writeAttribute("w:eastAsia", "pt-BR");
    stream.writeAttribute("w:bidi", "ar-SA");
    stream.writeEndElement(); // w:lang
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:drawing");

    stream.writeStartElement("wp:inline");
    stream.writeAttribute("distT", "0");
    stream.writeAttribute("distB", "0");
    stream.writeAttribute("distL", "0");
    stream.writeAttribute("distR", "0");

    stream.writeStartElement("wp:extent");
    stream.writeAttribute("cx", "767159");
    stream.writeAttribute("cy", "954359");
    stream.writeEndElement(); // wp:extent

    stream.writeStartElement("wp:effectExtent");
    stream.writeAttribute("l", "0");
    stream.writeAttribute("t", "0");
    stream.writeAttribute("r", "0");
    stream.writeAttribute("b", "0");
    stream.writeEndElement(); // wp:effectExtent

    stream.writeStartElement("wp:docPr");
    stream.writeAttribute("id", "1");
    stream.writeAttribute("name", "Figura1");
    stream.writeEndElement(); // wp:docPr

    stream.writeStartElement("wp:cNvGraphicFramePr");
    stream.writeEndElement(); // wp:cNvGraphicFramePr

    stream.writeStartElement("a:graphic");
    stream.writeAttribute("xmlns:a", "http://schemas.openxmlformats.org/drawingml/2006/main");

    stream.writeStartElement("a:graphicData");
    stream.writeAttribute("uri", "http://schemas.openxmlformats.org/drawingml/2006/picture");

    stream.writeStartElement("pic:pic");
    stream.writeAttribute("xmlns:pic", "http://schemas.openxmlformats.org/drawingml/2006/picture");

    stream.writeStartElement("pic:nvPicPr");

    stream.writeStartElement("pic:cNvPr");
    stream.writeAttribute("id", "0");
    stream.writeAttribute("name", "");
    stream.writeEndElement(); // pic:cNvPr

    stream.writeStartElement("pic:cNvPicPr");
    stream.writeEndElement(); // pic:cNvPicPr
    stream.writeEndElement(); // pic:nvPicPr

    stream.writeStartElement("pic:blipFill");

    stream.writeStartElement("a:blip");
    stream.writeAttribute("r:embed", "rId6");

    stream.writeStartElement("a:lum");
    stream.writeEndElement(); // a:lum

    stream.writeStartElement("a:alphaModFix");
    stream.writeEndElement(); // a:alphaModFix
    stream.writeEndElement(); // a:blip

    stream.writeStartElement("a:srcRect");
    stream.writeEndElement(); // a:srcRect

    stream.writeStartElement("a:stretch");

    stream.writeStartElement("a:fillRect");
    stream.writeEndElement(); // a:fillRect
    stream.writeEndElement(); // a:stretch
    stream.writeEndElement(); // pic:blipFill

    stream.writeStartElement("pic:spPr");

    stream.writeStartElement("a:xfrm");

    stream.writeStartElement("a:off");
    stream.writeAttribute("x", "0");
    stream.writeAttribute("y", "0");
    stream.writeEndElement(); // a:off

    stream.writeStartElement("a:ext");
    stream.writeAttribute("cx", "767159");
    stream.writeAttribute("cy", "954359");
    stream.writeEndElement(); // a:ext
    stream.writeEndElement(); // a:xfrm

    stream.writeStartElement("a:prstGeom");
    stream.writeAttribute("prst", "rect");

    stream.writeStartElement("a:avLst");
    stream.writeEndElement(); // a:avLst
    stream.writeEndElement(); // a:prstGeom
    stream.writeEndElement(); // pic:spPr
    stream.writeEndElement(); // pic:pic
    stream.writeEndElement(); // a:graphicData
    stream.writeEndElement(); // a:graphic
    stream.writeEndElement(); // wp:inline
    stream.writeEndElement(); // w:drawing
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    if (defaultEquipeTipo == "Estadual") {
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
    } else {
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
    }
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("SECRETARIA DA SAÚDE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("w:p");
        stream.writeAttribute("w:rsidR", "00094496");
        stream.writeAttribute("w:rsidRDefault", "00CE1B98");

        stream.writeStartElement("w:pPr");

        stream.writeStartElement("w:pStyle");
        stream.writeAttribute("w:val", "TableContents");
        stream.writeEndElement(); // w:pStyle

        stream.writeStartElement("w:jc");
        stream.writeAttribute("w:val", "center");
        stream.writeEndElement(); // w:jc

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr
        stream.writeEndElement(); // w:pPr

        stream.writeStartElement("w:r");

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr

        stream.writeStartElement("w:t");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r
        stream.writeEndElement(); // w:p

        stream.writeStartElement("w:p");
        stream.writeAttribute("w:rsidR", "00B77085");
        stream.writeAttribute("w:rsidRDefault", "00B77085");

        stream.writeStartElement("w:pPr");

        stream.writeStartElement("w:pStyle");
        stream.writeAttribute("w:val", "TableContents");
        stream.writeEndElement(); // w:pStyle

        stream.writeStartElement("w:jc");
        stream.writeAttribute("w:val", "center");
        stream.writeEndElement(); // w:jc

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr
        stream.writeEndElement(); // w:pPr

        stream.writeStartElement("w:r");

        stream.writeStartElement("w:rPr");

        stream.writeStartElement("w:b");
        stream.writeEndElement(); // w:b

        stream.writeStartElement("w:bCs");
        stream.writeEndElement(); // w:bCs

        stream.writeStartElement("w:kern");
        stream.writeAttribute("w:val", "0");
        stream.writeEndElement(); // w:kern

        stream.writeStartElement("w:sz");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:sz

        stream.writeStartElement("w:szCs");
        stream.writeAttribute("w:val", "20");
        stream.writeEndElement(); // w:szCs
        stream.writeEndElement(); // w:rPr

        stream.writeStartElement("w:t");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r

        stream.writeStartElement("w:bookmarkStart");
        stream.writeAttribute("w:id", "0");
        stream.writeAttribute("w:name", "_GoBack");
        stream.writeEndElement(); // w:bookmarkStart

        stream.writeStartElement("w:bookmarkEnd");
        stream.writeAttribute("w:id", "0");
        stream.writeEndElement(); // w:bookmarkEnd
        stream.writeEndElement(); // w:p
    }

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "2156");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:vMerge");
    stream.writeAttribute("w:val", "restart");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nº %1").arg(numTermoInterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1532");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:vMerge");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "008109A6");
    stream.writeAttribute("w:rsidRDefault", "008109A6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE PRODUTOS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("E/OU SUBSTÂNCIAS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "2156");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:vMerge");
    stream.writeEndElement(); // w:vMerge

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "008109A6");
    stream.writeAttribute("w:rsidRDefault", "008109A6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "603");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("IDENTIFICAÇÃO DO DETENTOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("NOME/RAZÃO SOCIAL: %1").arg(estabRazaoSocial));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "8782");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "7");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("ENDEREÇO: %1").arg(estabEndereco));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1990");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5258");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "290");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5258");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "276");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Ao(s) %1 dias do mês de %2 do ano de %3, às %4, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º, da Lei Federal nº 6437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote(s), data de fabricação e/ou prazo de validade, conforme a seguir: %5, pela(s) seguinte(s) irregularidade(s): %6, tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %7, conforme Auto de Infração Sanitária nº %8. O(s) produto(s) e/ou substância(s) interditado(s) fica(m) em poder de %9, situado na %10, que se compromete a não vender, remover, dar ao consumo, desviar ou substituir, até ulterior deliberação da autoridade sanitária competente desta Secretaria, constituindo-se em seu fiel depositário para todos os efeitos da Lei Civil e ficando bem ciente que deverá apresentar o(s) aludido(s) produto(s) e/ou substância(s), quando solicitado, sob pena de responsabilização no âmbito administrativo.")
    .arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd).arg(produtosInterditados).arg(irregularidades).arg(dispositivos).arg(numAuto).arg(nomeDepositario).arg(enderecoDepositario));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "617");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("CIÊNCIA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3796");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Nome: %1").arg(nomeServidor));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("Identidade Funcional: %1").arg(idServidor));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3405");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("Nome: __________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("RG/CPF: ________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "3571");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("Nome: ____________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00CE1B98");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:line", "360");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("RG/CPF: __________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "8");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("QUANDO O DETENTOR OU O DEPOSITÁRIO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidTr", "0071747E");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tcBorders

    stream.writeStartElement("w:tcMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "55");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcMar
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5386");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "5");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tcBorders
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "0071747E");
    stream.writeAttribute("w:rsidRDefault", "0071747E");
    stream.writeAttribute("w:rsidP", "0071747E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "TableContents");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "20");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr
    stream.writeEndElement(); // w:tbl

    stream.writeStartElement("w:p");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidRDefault", "00094496");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00094496");
    stream.writeAttribute("w:rsidSect", "001A0CF1");

    stream.writeStartElement("w:pgSz");
    stream.writeAttribute("w:w", "11906");
    stream.writeAttribute("w:h", "16838");
    stream.writeEndElement(); // w:pgSz

    stream.writeStartElement("w:pgMar");
    stream.writeAttribute("w:top", "1134");
    stream.writeAttribute("w:right", "567");
    stream.writeAttribute("w:bottom", "1134");
    stream.writeAttribute("w:left", "567");
    stream.writeAttribute("w:header", "720");
    stream.writeAttribute("w:footer", "720");
    stream.writeAttribute("w:gutter", "0");
    stream.writeEndElement(); // w:pgMar

    stream.writeStartElement("w:cols");
    stream.writeAttribute("w:space", "720");
    stream.writeEndElement(); // w:cols
    stream.writeEndElement(); // w:sectPr
    stream.writeEndElement(); // w:body
    stream.writeEndElement(); // w:document

    stream.writeEndDocument();

    file.close();

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Produtos ou Substâncias SEM VERSO DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}




