#include "termointerdicaoestabelecimento.h"
#include "ui_termointerdicaoestabelecimento.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

TermoInterdicaoEstabelecimento::TermoInterdicaoEstabelecimento(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermoInterdicaoEstabelecimento)
{
    ui->setupUi(this);

    vboxScrollIrreg = new QVBoxLayout;
    ui->groupBoxIrreg->setLayout(vboxScrollIrreg);

    // Configura comboBoxRoteiroInspecao
    setupRoteirosDisponiveis();
}

TermoInterdicaoEstabelecimento::~TermoInterdicaoEstabelecimento()
{
    delete ui;
}

void TermoInterdicaoEstabelecimento::on_comboBoxRoteiroInspecao_currentIndexChanged(int index)
{
    if (index != 0) {
        checkBoxIrregList.clear();
        setupRoteiroLayout(index);
    } else {
        checkBoxIrregList.clear();
        apagaLayout(vboxScrollIrreg);
    }
}

void TermoInterdicaoEstabelecimento::apagaLayout(QLayout * layout)
{
    if (! layout)
          return;
       while (auto item = layout->takeAt(0)) {
          delete item->widget();
          apagaLayout(item->layout());
    }
}

void TermoInterdicaoEstabelecimento::setupRoteiroLayout(int index)
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
        colunas = line.split("|");
        listaGruposRoteiro.append(colunas[0]);
        listaIrregRoteiro.append(colunas[1]);
        listaDispoRoteiro.append(colunas[2]);
    }

    arq.close();

    QString grupoAnt;
    grupoAnt = "DEFAULT";
    for (int i=0; i<listaGruposRoteiro.count(); i++) {
        if (QString::compare(listaGruposRoteiro[i], grupoAnt) != STR_EQUAL) {
            QLabel *labelGrupo = new QLabel(listaGruposRoteiro[i]);
            labelGrupo->setFixedHeight(31);
            labelGrupo->setStyleSheet("QLabel{border: 1px solid black; font-size: 11pt; font-weight: bold; background-color: rgb(82,240,0);}");
            vboxScrollIrreg->addWidget(labelGrupo);
        }
        grupoAnt = listaGruposRoteiro[i];
        QCheckBox *checkItem = createQCheckBoxWithWordWrap(this, listaIrregRoteiro[i]);
        vboxScrollIrreg->addWidget(checkItem);
        checkBoxIrregList.append(checkItem);
    }

    QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    vboxScrollIrreg->addSpacerItem(spacer);
}

QCheckBox* TermoInterdicaoEstabelecimento::createQCheckBoxWithWordWrap(QWidget *parent, const QString &text)
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

void TermoInterdicaoEstabelecimento::setupRoteirosDisponiveis()
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

QStringList TermoInterdicaoEstabelecimento::getSelectedCheckBoxesIrreg()
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

void MainWindow::termoInderdicaoCautelarEstabelecimentoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo de Interdição Cautelar de Estabelecimento ODT/content.xml");
    QFile file("modelos/ODT/content.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);

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
    stream.writeAttribute("style:column-width", "1.175in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn3");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.5652in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn4");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.0902in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn5");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.7576in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn6");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.8923in");
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
    stream.writeAttribute("style:name", "TableRow7");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.8618in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell8");
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
    stream.writeAttribute("style:name", "P9");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:break-before", "page");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T10");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
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
    stream.writeAttribute("style:vertical-align", "middle");
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
    stream.writeAttribute("style:name", "P13");
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
    stream.writeAttribute("style:name", "P14");
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
    stream.writeAttribute("style:name", "P15");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T16");
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
    stream.writeAttribute("style:name", "TableCell18");
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
    stream.writeAttribute("style:name", "P19");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T20");
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
    stream.writeAttribute("style:name", "T21");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow22");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.3125in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell23");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "middle");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P24");
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
    stream.writeAttribute("style:name", "TableRow25");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.3909in");
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
    stream.writeAttribute("style:name", "TableRow28");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell29");
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
    stream.writeAttribute("style:name", "P30");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow31");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell32");
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
    stream.writeAttribute("style:name", "P33");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell34");
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
    stream.writeAttribute("style:name", "P35");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow36");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell37");
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
    stream.writeAttribute("style:name", "P38");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell39");
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
    stream.writeAttribute("style:name", "P40");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow41");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell42");
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
    stream.writeAttribute("style:name", "P43");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell44");
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
    stream.writeAttribute("style:name", "P45");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow46");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell47");
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
    stream.writeAttribute("style:name", "P48");
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
    stream.writeAttribute("style:name", "P49");
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
    stream.writeAttribute("style:name", "P50");
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
    stream.writeAttribute("style:name", "P51");
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
    stream.writeAttribute("style:name", "TableRow58");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell59");
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
    stream.writeAttribute("style:name", "P60");
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
    stream.writeAttribute("style:name", "TableRow61");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell62");
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
    stream.writeAttribute("style:name", "P63");
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
    stream.writeAttribute("style:name", "P64");
    stream.writeAttribute("style:parent-style-name", "Standard");
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
    stream.writeAttribute("style:name", "P65");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P66");
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
    stream.writeAttribute("style:name", "P67");
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
    stream.writeAttribute("style:name", "P68");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P69");
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
    stream.writeAttribute("style:name", "P70");
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
    stream.writeAttribute("style:name", "TableCell71");
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
    stream.writeAttribute("style:name", "P72");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
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
    stream.writeAttribute("fo:text-align", "center");
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
    stream.writeAttribute("style:name", "P79");
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
    stream.writeAttribute("style:name", "TableRow80");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell81");
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
    stream.writeAttribute("style:name", "P82");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow84");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell85");
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
    stream.writeAttribute("style:name", "P86");
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
    stream.writeAttribute("style:name", "TableCell88");
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
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow7");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell8");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P9");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T10");

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
    stream.writeAttribute("table:style-name", "TableCell11");
    stream.writeAttribute("table:number-columns-spanned", "3");

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P12");
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P14");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "T16");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P17");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    } else {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P12");
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P17");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell18");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P19");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T20");
    stream.writeCharacters(QString("Nº %1").arg(numTermoInterd));
    stream.writeEndElement(); // text:span

    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow22");

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Normal");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell23");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P24");
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE ESTABELECIMENTO SOB VIGILÂNCIA SANITÁRIA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Normal");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow25");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell26");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P27");
    stream.writeCharacters("IDENTIFICAÇÃO DO");

    stream.writeStartElement("text:s");
    stream.writeEndElement(); // text:s
    stream.writeCharacters("ESTABELECIMENTO");
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

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow28");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell29");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P30");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow31");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell32");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P33");
    stream.writeCharacters(QString("ENDEREÇO: %1").arg(estabEndereco));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell34");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P35");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow36");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell37");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P38");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell39");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P40");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow41");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell42");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P43");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell44");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P45");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow46");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell47");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P48");
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º, da Lei Federal nº 6437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(a) %5 para a finalidade de suspensão de(a) %6 pela(s) seguinte(s) irregularidade(s): ").arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd).arg(estabSetorAutuado).arg(finalidadeSuspensao));

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P49");
    stream.writeCharacters(QString("%1").arg(irregularidades));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "P54");
    stream.writeCharacters(QString(", tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %1, conforme Auto de Infração Sanitária nº %2. Sem prejuízo das sanções de natureza civil ou penal cabíveis, o descumprimento desta interdição cautelar poderá acarretar responsabilização no âmbito administrativo.").arg(dispositivos).arg(numAuto));
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow58");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell59");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P60");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow61");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell62");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P63");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P64");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaInterd).arg(mesInterd).arg(anoInterd));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P65");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P66");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P67");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P68");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P69");
    stream.writeCharacters(QString("Nome: %1.").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P70");
    stream.writeCharacters(QString("Identidade Funcional: %1.").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell71");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P72");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P73");
    stream.writeCharacters("RECEBI A 1ª VIA EM _____/_____/_______.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P74");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P75");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P76");
    stream.writeCharacters("AUTUADO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P77");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P78");
    stream.writeCharacters("Nome: ______________________________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P79");
    stream.writeCharacters("RG/CPF: ____________________________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow80");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell81");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P82");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P83");
    stream.writeCharacters("QUANDO O AUTUADO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
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

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow84");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell85");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P86");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P87");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell88");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P89");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P90");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

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

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Estabelecimento ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoInderdicaoCautelarEstabelecimentoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo de Interdição Cautelar de Estabelecimento DOCX/word/document.xml");
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
    stream.writeAttribute("w:val", "0000");
    stream.writeAttribute("w:firstRow", "0");
    stream.writeAttribute("w:lastRow", "0");
    stream.writeAttribute("w:firstColumn", "0");
    stream.writeAttribute("w:lastColumn", "0");
    stream.writeAttribute("w:noHBand", "0");
    stream.writeAttribute("w:noVBand", "0");
    stream.writeEndElement(); // w:tblLook
    stream.writeEndElement(); // w:tblPr

    stream.writeStartElement("w:tblGrid");

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1692");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3694");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "130");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "2531");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "2725");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "68D7481D");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "1241");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1692");
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
    stream.writeAttribute("w14:paraId", "33B00331");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("wp14:anchorId", "75B3D46B");
    stream.writeAttribute("wp14:editId", "0EE8FA1F");

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
    stream.writeAttribute("w:w", "6355");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "3");
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

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "02772D98");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w14:paraId", "311CDBF0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3B2E571D");
    stream.writeAttribute("w14:textId", "4148A265");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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

    if (defaultEquipeTipo == "Estadual") {
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
            stream.writeAttribute("w14:paraId", "1A8ADBC7");
            stream.writeAttribute("w14:textId", "7E599601");
            stream.writeAttribute("w:rsidR", "002B03A7");
            stream.writeAttribute("w:rsidRDefault", "002B03A7");

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

            stream.writeStartElement("w:p");
            stream.writeAttribute("w14:paraId", "7BD0C49B");
            stream.writeAttribute("w14:textId", "77777777");
            stream.writeAttribute("w:rsidR", "0001788E");
            stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    }

    /**/

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
    stream.writeAttribute("w:w", "2725");
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
    stream.writeAttribute("w14:paraId", "13135CAE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "631A1C11");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "450");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "1692");
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
    stream.writeAttribute("w14:paraId", "25F676A0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "001601F6");
    stream.writeAttribute("w:rsidRDefault", "001601F6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "6355");
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

    stream.writeStartElement("w:vAlign");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:vAlign
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7B3195CA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("TERMO DE INTERDIÇÃO CAUTELAR DE ESTABELECIMENTO SOB VIGILÂNCIA SANITÁRIA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "2725");
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
    stream.writeAttribute("w14:paraId", "384C5308");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "001601F6");
    stream.writeAttribute("w:rsidRDefault", "001601F6");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "35317B64");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "563");
    stream.writeEndElement(); // w:trHeight
    stream.writeEndElement(); // w:trPr

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
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
    stream.writeAttribute("w14:paraId", "7BB3A0EC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("IDENTIFICAÇÃO DO ESTABELECIMENTO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "24636DE7");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
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
    stream.writeAttribute("w14:paraId", "46577655");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "66D5C0BD");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "8047");
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
    stream.writeAttribute("w14:paraId", "157BF44A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:w", "2725");
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
    stream.writeAttribute("w14:paraId", "4F57654B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "0B96A02A");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5516");
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
    stream.writeAttribute("w14:paraId", "31501257");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:w", "5256");
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
    stream.writeAttribute("w14:paraId", "67DC5ADC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "46C1E342");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5516");
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
    stream.writeAttribute("w14:paraId", "2C8B1080");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:w", "5256");
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
    stream.writeAttribute("w14:paraId", "6E04BC8A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "0EE42A20");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
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
    stream.writeAttribute("w14:paraId", "17382ED3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(QString("Ao(s) %1 dias do mês de %2 do ano de %3, às %4, no exercício da fiscalização sanitária, com fundamento no art. 23, § 4º, da Lei Federal nº 6437/77, interditei cautelarmente, pelo prazo máximo de 90 (noventa) dias, o(a) %5 para a finalidade de suspensão de(a) %6 pela(s) seguinte(s) irregularidade(s): ").arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(horarioInterd).arg(estabSetorAutuado).arg(finalidadeSuspensao));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

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
    stream.writeCharacters(QString("%1").arg(irregularidades));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

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
    stream.writeCharacters(QString(", tendo havido infração, respectivamente, ao(s) seguinte(s) dispositivo(s) legal(is): %1").arg(dispositivos));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

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
    stream.writeCharacters(QString(", conforme Auto de Infração Sanitária nº %1. Sem prejuízo das sanções de natureza civil ou penal cabíveis, o descumprimento desta interdição cautelar poderá acarretar responsabilização no âmbito administrativo.").arg(numAuto));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "038F5292");
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
    stream.writeAttribute("w14:paraId", "6230C200");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w14:paraId", "246734BE");
    stream.writeAttribute("w14:textId", "77777777");

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
    stream.writeAttribute("w14:paraId", "2C5F52FA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "5FFF138A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
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
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaInterd).arg(mesInterd).arg(anoInterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "579D835A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "50C4F4F4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "2EF605A4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w14:paraId", "2F43259E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "3E06EB5A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w14:paraId", "2A7FA414");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeAttribute("w14:paraId", "7DC65892");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "3D40D9EB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("RECEBI A 1ª VIA EM _____/_____/_______.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7BF4D007");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "79DD9D91");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "45F2BBC9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("AUTUADO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0C1AEE75");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

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
    stream.writeAttribute("w14:paraId", "003AA938");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("Nome: ______________________________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "657A6AFC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0078659A");

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
    stream.writeCharacters("RG/CPF: ____________________________________________.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w14:paraId", "2899B9E9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00A0118F");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
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
    stream.writeAttribute("w14:paraId", "29E88B5E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");

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
    stream.writeAttribute("w14:paraId", "17A4CEAE");
    stream.writeAttribute("w14:textId", "7900A4F5");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");
    stream.writeAttribute("w:rsidP", "00A0118F");

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
    stream.writeCharacters("QUANDO O AUTUADO RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w14:paraId", "3C6CE51F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00A0118F");

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
    stream.writeAttribute("w14:paraId", "2764AA10");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");
    stream.writeAttribute("w:rsidP", "00A0118F");

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
    stream.writeAttribute("w14:paraId", "3FA594D4");
    stream.writeAttribute("w14:textId", "5BDCF67C");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");
    stream.writeAttribute("w:rsidP", "00A0118F");

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
    stream.writeAttribute("w:val", "3");
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
    stream.writeAttribute("w14:paraId", "46E8E89C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");
    stream.writeAttribute("w:rsidP", "00A0118F");

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
    stream.writeAttribute("w14:paraId", "4E4B5E49");
    stream.writeAttribute("w14:textId", "70308249");
    stream.writeAttribute("w:rsidR", "00A0118F");
    stream.writeAttribute("w:rsidRDefault", "00A0118F");
    stream.writeAttribute("w:rsidP", "00A0118F");

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
    stream.writeAttribute("w14:paraId", "2C7DEB2C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0001788E");
    stream.writeAttribute("w:rsidRDefault", "0001788E");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "0001788E");

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

    //QString dirToCompress = "modelos/Termo de Interdição Cautelar de Estabelecimento DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}
