#include "termovinculadodesinterdicaoestabelecimento.h"
#include "ui_termovinculadodesinterdicaoestabelecimento.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

TermoVinculadoDesinterdicaoEstabelecimento::TermoVinculadoDesinterdicaoEstabelecimento(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermoVinculadoDesinterdicaoEstabelecimento)
{
    ui->setupUi(this);

    ui->dataDesinterdicaoDateEdit->setDate(QDate::currentDate());
    ui->dataInterdicaoDateEdit->setDate(QDate::currentDate());
    ui->horarioDesinterdicaoTimeEdit->setTime(QTime::currentTime());
}

TermoVinculadoDesinterdicaoEstabelecimento::~TermoVinculadoDesinterdicaoEstabelecimento()
{
    delete ui;
}

QStringList TermoVinculadoDesinterdicaoEstabelecimento::converteQDateEmStringList(QDate date)
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

QString TermoVinculadoDesinterdicaoEstabelecimento::converteQTimeEmString(QTime time)
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

QStringList TermoVinculadoDesinterdicaoEstabelecimento::getVariablesFromLayout()
{
    QStringList dateInterd = converteQDateEmStringList(ui->dataInterdicaoDateEdit->date());
    QStringList dateDesinterd = converteQDateEmStringList(ui->dataDesinterdicaoDateEdit->date());
    QString horaDesinterd = converteQTimeEmString(ui->horarioDesinterdicaoTimeEdit->time());
    QString setorDesinterd = ui->setorDesinterditadoLineEdit->text();
    QString nTermo = ui->numTermoInterdLineEdit->text();
    QString numProc = ui->numProcessoLineEdit->text();
    QString nomeServ = ui->nomeServidorLineEdit->text();
    QString idServ = ui->idServidorLineEdit->text();
    QString irregSanadas = ui->irregSanadasPlainTextEdit->toPlainText();

    return QStringList{nTermo, numProc, setorDesinterd, nomeServ, idServ, dateDesinterd[0], dateDesinterd[1], dateDesinterd[2], horaDesinterd, dateInterd[0], dateInterd[1], dateInterd[2], irregSanadas};
    /*
     * 0 - numTermoInterd
     * 1 - numeroProcesso
     * 2 - setorDesinterditado
     * 3 - nomeServidor
     * 4 - idServidor
     * 5 - diaDesinterd
     * 6 - mesDesinterd
     * 7 - anoDesinterd
     * 8 - horarioDesinterd
     * 9 - diaInterd
     * 10 - mesInterd
     * 11 - anoInterd
     * 12 - irregularidadesSanadas
    */
}

void MainWindow::termoVinculadoDesinterdicaoEstabelecimentoODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Estabelecimentos ODT/content.xml");
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
    stream.writeCharacters("DE ESTABELECIMENTOS SOB VIGILÂNCIA SANITÁRIA");
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
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabCnpjCpf));
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
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(a) %5, interditado(a) na data de %6 de %7 de %8, através do Termo de Interdição Cautelar de Estabelecimento sob Vigilância Sanitária nº %9, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %10. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(estabSetorDesinterd).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));
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
    stream.writeAttribute("table:style-name", "TableRow58");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell59");
    stream.writeAttribute("table:number-columns-spanned", "6");

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
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
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
    stream.writeAttribute("table:number-columns-spanned", "4");

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

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow80");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell81");
    stream.writeAttribute("table:number-columns-spanned", "6");

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
    stream.writeAttribute("table:number-columns-spanned", "4");

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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Estabelecimentos ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::termoVinculadoDesinterdicaoEstabelecimentoDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Termo Vinculado de Desinterdição de Estabelecimentos DOCX/word/document.xml");
    QFile file("modelos/DOCX/word/document.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "1F1E1530");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "0DDC00CA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("wp14:anchorId", "334B04B1");
    stream.writeAttribute("wp14:editId", "5FFFD410");

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
    stream.writeAttribute("w14:paraId", "4C16F30D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "27771B9E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
        stream.writeAttribute("w14:paraId", "1F6B4F1F");
        stream.writeAttribute("w14:textId", "7B3DBDCA");
        stream.writeAttribute("w:rsidR", "00E4306C");
        stream.writeAttribute("w:rsidRDefault", "003004E8");

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
        stream.writeAttribute("w14:paraId", "0AA6DE54");
        stream.writeAttribute("w14:textId", "05DBF07B");
        stream.writeAttribute("w:rsidR", "001419A6");
        stream.writeAttribute("w:rsidRDefault", "001419A6");

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
    stream.writeAttribute("w14:paraId", "72C7201D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "5C280027");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "5C280027");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeCharacters(QString("%1").arg(numProcesso));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "5FB3479B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "601F9725");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "001D13D4");
    stream.writeAttribute("w:rsidRDefault", "001D13D4");
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
    stream.writeEndElement(); // w:tcPr

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "36F655F0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "234B9674");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeCharacters("DE ESTABELECIMENTOS SOB VIGILÂNCIA SANITÁRIA");
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
    stream.writeAttribute("w14:paraId", "25D7B7CF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "001D13D4");
    stream.writeAttribute("w:rsidRDefault", "001D13D4");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "4AEBDF9F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "7BCEE31E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "42AEC1F6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "55EEBBFD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "11005284");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "4553C72B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "3A0C9D6E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "1752DC5A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "546A455A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "0BF37EC4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "6518C0EF");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "60DC368B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "7B256821");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "3571AC87");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "01AE6FEA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeCharacters(QString("Ao(s) %1 dia(s) do mês de %2 do ano de %3, às %4, desinterditei o(a) %5, interditado(a) na data de %6 de %7 de %8, através do Termo de Interdição Cautelar de Estabelecimento sob Vigilância Sanitária nº %9, em razão de ter(em) sido sanada(s) a(s) seguinte(s) irregularidade(s): %10. Para constar, lavrei o presente Termo em 2 (duas) vias de igual teor e para único efeito, que vão assinadas por mim e pelo representante legal do estabelecimento.")
    .arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd).arg(horarioDesinterd).arg(estabSetorDesinterd).arg(diaInterd).arg(mesInterd).arg(anoInterd).arg(numTermoInterd).arg(irregularidadesSanadas));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeEndElement(); // w:p


    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "14924959");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "64F48B56");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "2E0A316E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "4B148C69");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "6E5B7102");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaDesinterd).arg(mesDesinterd).arg(anoDesinterd));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "450B43E6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "5C38B73A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "06DA22C3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "79743B86");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "7B1C75B8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "0DDCFF5F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "723D85CC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "3D42DC58");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "490BF1E9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "6A4C5E98");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "0ED5DD17");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "3D8F761A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "43B28682");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w14:paraId", "32DEF282");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "003004E8");

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
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w14:paraId", "319066E9");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "58171862");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

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
    stream.writeAttribute("w14:paraId", "2E98A8CC");
    stream.writeAttribute("w14:textId", "6B74E926");
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w:rsidRDefault", "003004E8");
    stream.writeAttribute("w:rsidP", "00852C26");

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
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w14:paraId", "53B6EAE3");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "00852C26");

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
    stream.writeAttribute("w14:paraId", "6F1A171E");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w:rsidRDefault", "00852C26");
    stream.writeAttribute("w:rsidP", "00852C26");

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
    stream.writeAttribute("w14:paraId", "68AB9411");
    stream.writeAttribute("w14:textId", "168E3BA5");
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w:rsidRDefault", "00852C26");
    stream.writeAttribute("w:rsidP", "00852C26");

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
    stream.writeAttribute("w14:paraId", "2E0B083B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w:rsidRDefault", "00852C26");
    stream.writeAttribute("w:rsidP", "00852C26");

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
    stream.writeAttribute("w14:paraId", "74E015F2");
    stream.writeAttribute("w14:textId", "6D880755");
    stream.writeAttribute("w:rsidR", "00852C26");
    stream.writeAttribute("w:rsidRDefault", "00852C26");
    stream.writeAttribute("w:rsidP", "00852C26");

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
    stream.writeAttribute("w14:paraId", "0BC8D975");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00E4306C");
    stream.writeAttribute("w:rsidRDefault", "00E4306C");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00E4306C");

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

    //QString dirToCompress = "modelos/Termo Vinculado de Desinterdição de Estabelecimentos DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}
