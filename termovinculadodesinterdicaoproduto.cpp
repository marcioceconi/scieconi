#include "termovinculadodesinterdicaoproduto.h"
#include "ui_termovinculadodesinterdicaoproduto.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

TermoVinculadoDesinterdicaoProduto::TermoVinculadoDesinterdicaoProduto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermoVinculadoDesinterdicaoProduto)
{
    ui->setupUi(this);

    ui->dataDesinterdicaoDateEdit->setDate(QDate::currentDate());
    ui->dataInterdicaoDateEdit->setDate(QDate::currentDate());
    ui->horarioDesinterdicaoTimeEdit->setTime(QTime::currentTime());
}

TermoVinculadoDesinterdicaoProduto::~TermoVinculadoDesinterdicaoProduto()
{
    delete ui;
}

QStringList TermoVinculadoDesinterdicaoProduto::converteQDateEmStringList(QDate date)
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

QString TermoVinculadoDesinterdicaoProduto::converteQTimeEmString(QTime time)
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

QStringList TermoVinculadoDesinterdicaoProduto::getVariablesFromLayout()
{
    QStringList dateInterd = converteQDateEmStringList(ui->dataDesinterdicaoDateEdit->date());
    QStringList dateDesinterd = converteQDateEmStringList(ui->dataInterdicaoDateEdit->date());
    QString horaDesinterd = converteQTimeEmString(ui->horarioDesinterdicaoTimeEdit->time());
    QString produtosDesint = ui->produtosDesinterditadosplainTextEdit->toPlainText();
    QString irregSanad = ui->irregSanadasPlainTextEdit->toPlainText();
    QString nTermo = ui->numTermoInterdLineEdit->text();
    QString numProc = ui->numProcessoLineEdit->text();
    QString nomeServ = ui->nomeServidorLineEdit->text();
    QString idServ = ui->idServidorLineEdit->text();
    QString numTermoDesint = ui->numTermoDesinterdicaoLineEdit->text();
    QString usarVer;
    if (ui->checkBoxUsarVerso->checkState() == Qt::CheckState::Checked) {
        usarVer = "sim";
    } else {
        usarVer = "não";
    }

    return QStringList{nTermo, numProc, nomeServ, idServ, produtosDesint, irregSanad, dateDesinterd[0], dateDesinterd[1], dateDesinterd[2], horaDesinterd, dateInterd[0], dateInterd[1], dateInterd[2], usarVer, numTermoDesint};
    /*
     * 0 - numTermoInterd
     * 1 - numProcesso
     * 2 - nomeServidor
     * 3 - idServidor
     * 4 - produtosDesinterditados
     * 5 - irregularidadesSanadas
     * 6 - diaDesinterd
     * 7 - mesDesinterd
     * 8 - anoDesinterd
     * 9 - horarioDesinterd
     * 10 - diaInterd
     * 11 - mesInterd
     * 12 - anoInterd
     * 13 - usarVerso
     * 14 - numTermoDesinterdicao
    */
}

void MainWindow::termoVinculadoDesinterdicaoProdutoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias ODT/content.xml");
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
    stream.writeAttribute("style:column-width", "1.0631in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn3");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.6763in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn4");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.0888in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn5");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.1541in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn6");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.1152in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn7");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.3826in");
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
    stream.writeAttribute("style:name", "TableRow8");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell9");
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
    stream.writeAttribute("style:name", "P10");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:break-before", "page");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T11");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell12");
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
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T17");
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
    stream.writeAttribute("style:name", "P18");
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
    stream.writeAttribute("style:name", "TableCell19");
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
    stream.writeAttribute("style:name", "P20");
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
    stream.writeAttribute("style:name", "P21");
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
    stream.writeAttribute("style:name", "TableRow22");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
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
    stream.writeAttribute("style:name", "P25");
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
    stream.writeAttribute("style:name", "TableRow26");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4187in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell27");
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

    stream.writeStartElement("style:text-properties");
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
    stream.writeAttribute("fo:border-right", "none");
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
    stream.writeAttribute("style:name", "TableCell35");
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
    stream.writeAttribute("style:name", "P36");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow37");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell38");
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
    stream.writeAttribute("style:name", "TableCell40");
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
    stream.writeAttribute("style:name", "P41");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow42");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.2013in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell43");
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
    stream.writeAttribute("style:name", "TableCell45");
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
    stream.writeAttribute("style:name", "P46");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow47");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
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
    stream.writeAttribute("style:name", "TableRow64");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell65");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
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
    stream.writeAttribute("style:name", "P66");
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
    stream.writeAttribute("style:name", "TableRow67");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell68");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0069in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P69");
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
    stream.writeAttribute("style:name", "P70");
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
    stream.writeAttribute("style:name", "P71");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P72");
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
    stream.writeAttribute("fo:line-height", "150%");
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
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell77");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P78");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
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
    stream.writeAttribute("style:name", "TableRow86");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell87");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
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
    stream.writeAttribute("style:name", "P88");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("style:name", "TableRow90");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell91");
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
    stream.writeAttribute("style:name", "P92");
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
    stream.writeAttribute("style:name", "P93");
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
    stream.writeAttribute("style:name", "TableCell94");
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
    stream.writeAttribute("style:name", "P95");
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
    stream.writeAttribute("style:name", "P97");
    stream.writeAttribute("style:parent-style-name", "Standard");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T98");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T99");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn101");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.6361in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn102");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.1041in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn103");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.2604in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn104");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.4798in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Table100");
    stream.writeAttribute("style:family", "table");

    stream.writeStartElement("style:table-properties");
    stream.writeAttribute("style:width", "7.4805in");
    stream.writeAttribute("fo:margin-left", "0in");
    stream.writeAttribute("table:align", "left");
    stream.writeEndElement(); // style:table-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow105");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell106");
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
    stream.writeAttribute("style:name", "P107");
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
    stream.writeAttribute("style:name", "P108");
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
    stream.writeAttribute("style:name", "P109");
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
    stream.writeAttribute("style:name", "P110");
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
    stream.writeAttribute("style:name", "P111");
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
    stream.writeAttribute("style:name", "TableRow146");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell147");
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
    stream.writeAttribute("style:name", "P148");
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
    stream.writeAttribute("style:name", "TableRow149");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell150");
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
    stream.writeAttribute("style:name", "P151");
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
    stream.writeAttribute("style:name", "P152");
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
    stream.writeAttribute("style:name", "P153");
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
    stream.writeAttribute("style:name", "P154");
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
    stream.writeAttribute("style:name", "TableCell155");
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
    stream.writeAttribute("style:name", "P156");
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
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell160");
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
    stream.writeAttribute("style:name", "P161");
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
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow165");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell166");
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
    stream.writeAttribute("style:name", "P167");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("style:name", "TableRow169");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell170");
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
    stream.writeAttribute("style:name", "P171");
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
    stream.writeAttribute("style:name", "P172");
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
    stream.writeAttribute("style:name", "TableCell173");
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
    stream.writeAttribute("style:name", "P175");
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
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow8");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell9");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P10");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T11");

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
    stream.writeAttribute("table:style-name", "TableCell12");
    stream.writeAttribute("table:number-columns-spanned", "3");

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P14");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P16");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "T17");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P18");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    } else {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P14");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P18");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell19");
    stream.writeAttribute("table:number-columns-spanned", "2");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P20");
    stream.writeCharacters("PROCESSO Nº");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P21");
    stream.writeCharacters(QString("%1").arg(numProcesso));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
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
    stream.writeCharacters("TERMO VINCULADO DE DESINTERDIÇÃO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P25");
    stream.writeCharacters("DE PRODUTOS E/OU SUBSTÂNCIAS");
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

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow26");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell27");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P28");
    stream.writeCharacters("IDENTIFICAÇÃO DO RESPONSÁVEL");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow29");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell30");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P31");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow32");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell33");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P34");
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

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell35");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P36");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow37");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell38");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P39");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell40");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P41");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow42");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell43");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P44");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell45");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P46");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow47");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell48");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P49");
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote, data de fabricação e/ou prazo de validade, conforme verso do presente Termo, interditado(s) na data de %5 de %6 de %7, através do Termo de Interdição Cautelar de Produtos e/ou Substâncias nº %8, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %9. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));

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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow64");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell65");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P66");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow67");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell68");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P69");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P70");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P71");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P72");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P73");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P74");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P75");
    stream.writeCharacters(QString("Nome: %1").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P76");
    stream.writeCharacters(QString("Identidade Funcional: %1").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell77");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P78");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P79");
    stream.writeCharacters("RECEBI A 1ª VIA EM _____/_____/_______.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P80");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P81");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P82");
    stream.writeCharacters("RESPONSÁVEL");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P83");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P84");
    stream.writeCharacters("Nome: ______________________________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P85");
    stream.writeCharacters("RG/CPF:");

    stream.writeStartElement("text:s");
    stream.writeEndElement(); // text:s
    stream.writeCharacters("____________________________________________.");
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
    stream.writeAttribute("table:style-name", "TableRow86");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell87");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P88");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P89");
    stream.writeCharacters("QUANDO O RESPONSÁVEL RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow90");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell91");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P92");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P93");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell94");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P95");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P96");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

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

    stream.writeStartElement("text:soft-page-break");
    stream.writeEndElement(); // text:soft-page-break

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P97");
    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T99");
    stream.writeCharacters(QString("O rol abaixo integra o histórico do presente Termo Vinculado de Desinterdição de Produtos e/ou Substâncias Nº %1, para todos os efeitos legais.").arg(numTermoDesinterd));
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p

    stream.writeStartElement("table:table");
    stream.writeAttribute("table:style-name", "Table100");

    stream.writeStartElement("table:table-columns");

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn101");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn102");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn103");
    stream.writeEndElement(); // table:table-column

    stream.writeStartElement("table:table-column");
    stream.writeAttribute("table:style-name", "TableColumn104");
    stream.writeEndElement(); // table:table-column
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow105");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell106");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P107");
    stream.writeCharacters(QString("%1").arg(produtosDesinterditados));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P145");
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
    stream.writeAttribute("table:style-name", "TableRow146");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell147");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P148");
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
    stream.writeAttribute("table:style-name", "TableRow149");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell150");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P151");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P152");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P153");
    stream.writeCharacters("SERVIDOR AUTUANTE");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P154");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell155");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P156");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P157");
    stream.writeCharacters("_______________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P158");
    stream.writeCharacters("DETENTOR");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P159");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell160");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P161");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P162");
    stream.writeCharacters("_____________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P163");
    stream.writeCharacters("DEPOSITÁRIO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P164");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow165");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell166");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P167");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P168");
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

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow169");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell170");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P171");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P172");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell173");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P174");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P175");
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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoVinculadoDesinterdicaoProdutoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias DOCX/word/document.xml");
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
    stream.writeAttribute("w:w", "1531");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3854");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "128");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3102");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "166");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1991");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "170EA463");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "2ADD14DC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("wp14:anchorId", "3C89EB87");
    stream.writeAttribute("wp14:editId", "121D67E6");

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
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7E76104A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "125BD4F5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
        stream.writeAttribute("w14:paraId", "68056809");
        stream.writeAttribute("w14:textId", "47DA097B");
        stream.writeAttribute("w:rsidR", "00A429C8");
        stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
        stream.writeAttribute("w14:paraId", "12AA8C7A");
        stream.writeAttribute("w14:textId", "2B384488");
        stream.writeAttribute("w:rsidR", "00FD5593");
        stream.writeAttribute("w:rsidRDefault", "00FD5593");

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
        stream.writeEndElement(); // w:p
    }

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3275017B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "4DC687DA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("PROCESSO Nº");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "4DC687DA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters(numProcesso);
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "25109DDA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "27C516EC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00917C30");
    stream.writeAttribute("w:rsidRDefault", "00917C30");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
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
    stream.writeAttribute("w14:paraId", "4F0D34F9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("TERMO VINCULADO DE DESINTERDIÇÃO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "48B61B1C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("DE PRODUTOS E/OU SUBSTÂNCIAS");
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
    stream.writeAttribute("w14:paraId", "0D3AD52B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00917C30");
    stream.writeAttribute("w:rsidRDefault", "00917C30");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "39A66AD8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "098475C3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("IDENTIFICAÇÃO DO RESPONSÁVEL");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "65908814");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "405DB25E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "7D96053A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "8782");
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
    stream.writeAttribute("w14:paraId", "74C14F7D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "371361A7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "4EBF9D42");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
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
    stream.writeAttribute("w14:paraId", "7F537FCC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "415AAD85");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "1E4A56D7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "2800D3EE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "42CF1AF7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "594A7D6B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00054BB5");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "24F2392B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote, data de fabricação e/ou prazo de validade, conforme a seguir verso do presente Termo, interditado(s) na data de %5 de %6 de %7, através do Termo de Interdição Cautelar de Produtos e/ou Substâncias nº %8, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %9. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "1ABAF982");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00054BB5");

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
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "19BA4A24");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "2F0CC7DC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00054BB5");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5385");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "1202AD12");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "0BB651E6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

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
    stream.writeCharacters("de");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6C70AD88");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "39BE3776");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "516289D9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "4C4F3DD2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "17038206");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "7C9FE6C2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:w", "5387");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "1D64A4BA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "39103DFA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "3F266175");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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

    stream.writeStartElement("w:bookmarkStart");
    stream.writeAttribute("w:id", "0");
    stream.writeAttribute("w:name", "_GoBack");
    stream.writeEndElement(); // w:bookmarkStart

    stream.writeStartElement("w:bookmarkEnd");
    stream.writeAttribute("w:id", "0");
    stream.writeEndElement(); // w:bookmarkEnd
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3E75A3D7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "421B3CE2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("RESPONSÁVEL");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "29FB7269");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "2E60E47C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "562A47AE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "646BE3F1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00054BB5");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

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
    stream.writeAttribute("w14:paraId", "185C211C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "1C32D040");
    stream.writeAttribute("w14:textId", "0595D6D4");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("QUANDO O RESPONSÁVEL ");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "gramStart");
    stream.writeEndElement(); // w:proofErr

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
    stream.writeCharacters("RECUSAR-SE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "gramEnd");
    stream.writeEndElement(); // w:proofErr

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
    stream.writeCharacters(" A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w14:paraId", "54521D25");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "7F6F3E47");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "4EA7A533");
    stream.writeAttribute("w14:textId", "40A49931");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w:val", "4");
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
    stream.writeAttribute("w14:paraId", "68607334");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "295245F2");
    stream.writeAttribute("w14:textId", "7AC3B285");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "1A147356");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "1D997B78");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "24225A2D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "54EA30EF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "19ACD769");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:lastRenderedPageBreak");
    stream.writeEndElement(); // w:lastRenderedPageBreak

    stream.writeStartElement("w:t");
    stream.writeCharacters(QString("O rol abaixo integra o histórico do presente Termo Vinculado de Desinterdição de Produtos e/ou Substâncias Nº %1, para todos os efeitos legais.").arg(numTermoDesinterd));
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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "4F0D8A04");
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
    stream.writeAttribute("w14:paraId", "16D09A35");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters(QString("%1").arg(produtosDesinterditados));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5C1C91AD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "7414957A");
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
    stream.writeAttribute("w14:paraId", "55749212");
    stream.writeAttribute("w14:textId", "757D481A");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "58FBE67F");
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
    stream.writeAttribute("w14:paraId", "54B75A76");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "19164580");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "0674F0CF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "4F46D63E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "6B95E655");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "70B2349A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "7F98DD2B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "2669CA1C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "437B6804");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "7052451B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "1F320CFB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "5E28A983");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "77726F3A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "52C68328");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "75D13F33");
    stream.writeAttribute("w14:textId", "4ACB1A88");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w14:paraId", "4E2CC548");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "03DC126B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "1D3D31D4");
    stream.writeAttribute("w14:textId", "53750199");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "25954C61");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "6CA9EE6D");
    stream.writeAttribute("w14:textId", "7193F042");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "7C21ECE4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00A429C8");

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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}

void MainWindow::termoVinculadoDesinterdicaoProdutoSemVersoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias SEM VERSO ODT/content.xml");
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
    stream.writeAttribute("style:column-width", "1.0631in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn3");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.6763in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn4");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.0888in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn5");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "2.1541in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn6");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "0.1152in");
    stream.writeAttribute("style:use-optimal-column-width", "false");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableColumn7");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:column-width", "1.3826in");
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
    stream.writeAttribute("style:name", "TableRow8");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell9");
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
    stream.writeAttribute("style:name", "P10");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:break-before", "page");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T11");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell12");
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
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T17");
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
    stream.writeAttribute("style:name", "P18");
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
    stream.writeAttribute("style:name", "TableCell19");
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
    stream.writeAttribute("style:name", "P20");
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
    stream.writeAttribute("style:name", "P21");
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
    stream.writeAttribute("style:name", "TableRow22");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P23");
    stream.writeAttribute("style:parent-style-name", "Normal");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "true");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell24");
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
    stream.writeAttribute("style:name", "P25");
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
    stream.writeAttribute("style:name", "P26");
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
    stream.writeAttribute("style:name", "P27");
    stream.writeAttribute("style:parent-style-name", "Normal");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "true");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow28");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4187in");
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
    stream.writeAttribute("style:vertical-align", "middle");
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
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
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
    stream.writeAttribute("style:name", "TableRow34");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell35");
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
    stream.writeAttribute("style:name", "P36");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell37");
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
    stream.writeAttribute("style:name", "TableRow39");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell40");
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
    stream.writeAttribute("style:name", "P41");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell42");
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
    stream.writeAttribute("style:name", "TableRow44");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.2013in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell45");
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
    stream.writeAttribute("style:name", "P46");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
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
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow49");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell50");
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
    stream.writeAttribute("style:name", "TableRow66");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.4284in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell67");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
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
    stream.writeAttribute("style:name", "P68");
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
    stream.writeAttribute("style:name", "TableRow69");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell70");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0034in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0069in solid #000000");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("fo:padding-top", "0.0381in");
    stream.writeAttribute("fo:padding-left", "0.0381in");
    stream.writeAttribute("fo:padding-bottom", "0.0381in");
    stream.writeAttribute("fo:padding-right", "0.0381in");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P71");
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
    stream.writeAttribute("style:name", "P72");
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
    stream.writeAttribute("style:name", "P73");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-left", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-bottom", "0.0069in solid #000000");
    stream.writeAttribute("fo:border-right", "0.0034in solid #000000");
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
    stream.writeAttribute("fo:text-align", "center");
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
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P86");
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
    stream.writeAttribute("style:name", "P87");
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
    stream.writeAttribute("style:name", "TableRow88");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell89");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:border-top", "0.0069in solid #000000");
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
    stream.writeAttribute("style:name", "P90");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow92");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell93");
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
    stream.writeAttribute("style:name", "P94");
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
    stream.writeAttribute("style:name", "P95");
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
    stream.writeAttribute("style:name", "TableCell96");
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
    stream.writeAttribute("style:name", "P97");
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
    stream.writeAttribute("style:name", "P98");
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
    stream.writeEndElement(); // table:table-columns

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow8");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell9");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P10");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T11");

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
    stream.writeAttribute("table:style-name", "TableCell12");
    stream.writeAttribute("table:number-columns-spanned", "3");

    if (defaultEquipeTipo == "Estadual") {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters("ESTADO DO RIO GRANDE DO SUL");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P14");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNome.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P16");

        stream.writeStartElement("text:span");
        stream.writeAttribute("text:style-name", "T17");
        stream.writeCharacters(QString("%1").arg(defaultEquipeNucleo.toUpper()));
        stream.writeEndElement(); // text:span
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P18");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    } else {
        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P13");
        stream.writeCharacters(QString("PREFEITURA MUNICIPAL DE %1").arg(defaultEquipeCidade.toUpper()));
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P14");
        stream.writeCharacters("SECRETARIA DA SAÚDE");
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P18");
        stream.writeCharacters(QString("%1").arg(defaultEquipeSetor.toUpper()));
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell19");
    stream.writeAttribute("table:number-columns-spanned", "2");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P20");
    stream.writeCharacters("PROCESSO Nº");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P21");
    stream.writeCharacters(numProcesso);
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow22");

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P23");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell24");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P25");
    stream.writeCharacters("TERMO VINCULADO DE DESINTERDIÇÃO");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P26");
    stream.writeCharacters("DE PRODUTOS E/OU SUBSTÂNCIAS");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P27");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow28");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell29");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P30");
    stream.writeCharacters("IDENTIFICAÇÃO DO RESPONSÁVEL");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow31");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell32");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P33");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow34");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell35");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P36");
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

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell37");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P38");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow39");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell40");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P41");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell42");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P43");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow44");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell45");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P46");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell47");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P48");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow49");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell50");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P51");
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote, data de fabricação e/ou prazo de validade, conforme a seguir: %5, interditado(s) na data de %6 de %7 de %8, através do Termo de Interdição Cautelar de Produtos e/ou Substâncias nº %9, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %10. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(produtosDesinterditados).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));

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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow66");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell67");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P68");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow69");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell70");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P71");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P72");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P73");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P74");
    stream.writeCharacters("___________________________________");
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
    stream.writeCharacters(QString("Nome: %1").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P78");
    stream.writeCharacters(QString("Identidade Funcional: %1").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell79");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P80");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P81");
    stream.writeCharacters("RECEBI A 1ª VIA EM _____/_____/_______.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P82");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P83");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P84");
    stream.writeCharacters("RESPONSÁVEL");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P85");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P86");
    stream.writeCharacters("Nome: ______________________________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P87");
    stream.writeCharacters("RG/CPF: ____________________________________________.");
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
    stream.writeAttribute("table:style-name", "TableRow88");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell89");
    stream.writeAttribute("table:number-columns-spanned", "6");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P90");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P91");
    stream.writeCharacters("QUANDO O");

    stream.writeStartElement("text:s");
    stream.writeEndElement(); // text:s
    stream.writeCharacters("RESPONSÁVEL RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
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
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow92");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell93");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P94");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P95");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell96");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P97");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P98");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias SEM VERSO ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoVinculadoDesinterdicaoProdutoSemVersoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias SEM VERSO DOCX/word/document.xml");
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
    stream.writeAttribute("w:w", "1531");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3854");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "128");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "3102");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "166");
    stream.writeEndElement(); // w:gridCol

    stream.writeStartElement("w:gridCol");
    stream.writeAttribute("w:w", "1991");
    stream.writeEndElement(); // w:gridCol
    stream.writeEndElement(); // w:tblGrid

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "21B0D5B2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "52212363");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("wp14:anchorId", "72ABA914");
    stream.writeAttribute("wp14:editId", "3E82490B");

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
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "5C576F32");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "2151B007");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
        stream.writeAttribute("w14:paraId", "55DAAE5F");
        stream.writeAttribute("w14:textId", "77777777");
        stream.writeAttribute("w:rsidR", "00A429C8");
        stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
        stream.writeAttribute("w14:paraId", "41604455");
        stream.writeAttribute("w14:textId", "77777777");
        stream.writeAttribute("w:rsidR", "00FD5593");
        stream.writeAttribute("w:rsidRDefault", "00FD5593");

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
        stream.writeEndElement(); // w:p
    }

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "252A5835");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "6486AF3C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("PROCESSO Nº");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6486AF3C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters(numProcesso);
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "5FF895C0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "1802C557");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00917C30");
    stream.writeAttribute("w:rsidRDefault", "00917C30");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "7084");
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
    stream.writeAttribute("w14:paraId", "3D594C82");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("TERMO VINCULADO DE DESINTERDIÇÃO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "25D8F005");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("DE PRODUTOS E/OU SUBSTÂNCIAS");
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
    stream.writeAttribute("w14:paraId", "0E7CACA9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00917C30");
    stream.writeAttribute("w:rsidRDefault", "00917C30");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "35432D69");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "5E95D618");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("IDENTIFICAÇÃO DO RESPONSÁVEL");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "3092E0BF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "6D31F50D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "61EA5D36");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "8782");
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
    stream.writeAttribute("w14:paraId", "0DC4BDF5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "4FB806D1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "1A2485D5");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5514");
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
    stream.writeAttribute("w14:paraId", "7706BFEC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "58FDC2BC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "187FE3B2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "062F0690");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "551B6F0B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "06F85D7F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00C23CA3");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w14:paraId", "7D4EF050");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(s) produto(s) e/ou substância(s) identificado(s) pelo(s) número(s) de lote, data de fabricação e/ou prazo de validade, conforme a seguir: %5, interditado(s) na data de %6 de %7 de %8, através do Termo de Interdição Cautelar de Produtos e/ou Substâncias nº %9, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %10. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(produtosDesinterditados).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "64CC648F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00C23CA3");

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
    stream.writeAttribute("w:val", "6");
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
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "01278956");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "7B7254C3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00C23CA3");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "5385");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "2");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "2");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "000000");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "103AA442");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "34BC42E8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "355F8A56");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "2D4AC6BB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "28B6C455");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "0696C6E7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "61592D1C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "352476EB");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:w", "5387");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "4");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
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
    stream.writeAttribute("w14:paraId", "52F2F6DA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "4DF4EF19");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "48856D1F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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

    stream.writeStartElement("w:bookmarkStart");
    stream.writeAttribute("w:id", "0");
    stream.writeAttribute("w:name", "_GoBack");
    stream.writeEndElement(); // w:bookmarkStart

    stream.writeStartElement("w:bookmarkEnd");
    stream.writeAttribute("w:id", "0");
    stream.writeEndElement(); // w:bookmarkEnd
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "41B80C56");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "4CBE236C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeCharacters("RESPONSÁVEL");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3561BA74");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "013AD447");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w14:paraId", "48EE5CFE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");

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
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w14:paraId", "155117BD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00C23CA3");

    stream.writeStartElement("w:tc");

    stream.writeStartElement("w:tcPr");

    stream.writeStartElement("w:tcW");
    stream.writeAttribute("w:w", "10772");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tcW

    stream.writeStartElement("w:gridSpan");
    stream.writeAttribute("w:val", "6");
    stream.writeEndElement(); // w:gridSpan

    stream.writeStartElement("w:tcBorders");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:val", "single");
    stream.writeAttribute("w:sz", "4");
    stream.writeAttribute("w:space", "0");
    stream.writeAttribute("w:color", "auto");
    stream.writeEndElement(); // w:top

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
    stream.writeAttribute("w14:paraId", "6C2AB5FF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

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
    stream.writeAttribute("w14:paraId", "3D94ECE6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00030CAB");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("QUANDO O RESPONSÁVEL ");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "gramStart");
    stream.writeEndElement(); // w:proofErr

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
    stream.writeCharacters("RECUSAR-SE");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "gramEnd");
    stream.writeEndElement(); // w:proofErr

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
    stream.writeCharacters(" A ASSINAR OU FOR ANALFABETO:");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w14:paraId", "66019898");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0008726B");

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
    stream.writeAttribute("w14:paraId", "63085B84");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "52ABB716");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w:val", "4");
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
    stream.writeAttribute("w14:paraId", "209BA28F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "0DB7FA14");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0008726B");
    stream.writeAttribute("w:rsidRDefault", "0008726B");
    stream.writeAttribute("w:rsidP", "0008726B");

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
    stream.writeAttribute("w14:paraId", "6647FC6C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidRDefault", "00A429C8");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00A429C8");
    stream.writeAttribute("w:rsidSect", "001E3326");

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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Produtos ou Substâncias SEM VERSO DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}
