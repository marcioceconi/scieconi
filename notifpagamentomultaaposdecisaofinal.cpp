#include "notifpagamentomultaaposdecisaofinal.h"
#include "ui_notifpagamentomultaaposdecisaofinal.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

NotifPagamentoMultaAposDecisaoFinal::NotifPagamentoMultaAposDecisaoFinal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotifPagamentoMultaAposDecisaoFinal)
{
    ui->setupUi(this);

    ui->dataNotifDateEdit->setDate(QDate::currentDate());
    ui->dataAutoDateEdit->setDate(QDate::currentDate());
}

NotifPagamentoMultaAposDecisaoFinal::~NotifPagamentoMultaAposDecisaoFinal()
{
    delete ui;
}

QStringList NotifPagamentoMultaAposDecisaoFinal::getVariablesFromLayout()
{
    QString valMulta = ui->valorMultaLineEdit->text();
    QString valMultaPorExtenso = ui->valorMultaPorExtensoLineEdit->text();
    QString nAuto = ui->numAutoLineEdit->text();
    QString nProcesso = ui->numProcessoLineEdit->text();
    QString nomeServ = ui->nomeServidorLineEdit->text();
    QString idServ = ui->idServidorLineEdit->text();
    QStringList dateNotifList = converteQDateEmStringList(ui->dataNotifDateEdit->date());
    QStringList dateAutoList = converteQDateEmStringList(ui->dataAutoDateEdit->date());

    return QStringList{valMulta, valMultaPorExtenso, nAuto, nProcesso, nomeServ, idServ, dateNotifList[0], dateNotifList[1], dateNotifList[2], dateAutoList[0], dateAutoList[1], dateAutoList[2]};
    /*
     * 0 - valMulta
     * 1 - valMultaPorExtenso
     * 2 - numAuto
     * 3 - numProcesso
     * 4 - nomeServ
     * 5 - idServ
     * 6 - diaNotif
     * 7 - mesNotif
     * 8 - anoNotif
     * 9 - diaAuto
     * 10 - mesAuto
     * 11 - anoAuto
    */
}

QStringList NotifPagamentoMultaAposDecisaoFinal::converteQDateEmStringList(QDate date)
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

void MainWindow::notificacaoPagamentoMultaAposDecisaoFinalODT(QString fn)
{
    setupEstruturaODT();

    //QFile file("modelos/Notificação para Pagamento de Multa APÓS DECISÃO FINAL ODT/content.xml");
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
    stream.writeAttribute("style:name", "TableCell17");
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
    stream.writeAttribute("style:name", "P18");
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
    stream.writeAttribute("style:name", "P19");
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
    stream.writeAttribute("style:name", "TableRow20");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.3125in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell21");
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
    stream.writeAttribute("style:name", "P22");
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
    stream.writeAttribute("style:name", "TableRow23");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.2944in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell24");
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

    stream.writeStartElement("style:text-properties");
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
    stream.writeAttribute("fo:border-right", "none");
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
    stream.writeAttribute("style:parent-style-name", "Textbody");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("fo:margin-bottom", "0in");
    stream.writeAttribute("fo:line-height", "150%");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T47");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T48");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T49");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T50");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T51");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:color", "#000000");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T52");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T53");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T54");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T55");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T56");
    stream.writeAttribute("style:parent-style-name", "Fonteparág.padrão");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableRow57");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0.3069in");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell58");
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
    stream.writeAttribute("style:name", "P59");
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
    stream.writeAttribute("style:name", "TableRow60");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell61");
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
    stream.writeAttribute("style:name", "P62");
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
    stream.writeAttribute("style:name", "P63");
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
    stream.writeAttribute("style:name", "P64");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("style:name", "TableCell70");
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
    stream.writeAttribute("style:name", "TableRow79");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell80");
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
    stream.writeAttribute("style:name", "P81");
    stream.writeAttribute("style:parent-style-name", "TableContents");
    stream.writeAttribute("style:family", "paragraph");

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
    stream.writeAttribute("style:name", "TableRow83");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:use-optimal-row-height", "false");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell84");
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
    stream.writeAttribute("fo:text-align", "center");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-size", "10pt");
    stream.writeAttribute("style:font-size-asian", "10pt");
    stream.writeAttribute("style:font-size-complex", "10pt");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableCell87");
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
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:name", "a0");
    stream.writeAttribute("style:parent-style-name", "Graphics");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("fo:border", "none");
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
        stream.writeCharacters(defaultEquipeNome.toUpper());
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P15");
        stream.writeCharacters(defaultEquipeNucleo.toUpper());
        stream.writeEndElement(); // text:p

        stream.writeStartElement("text:p");
        stream.writeAttribute("text:style-name", "P16");
        stream.writeCharacters(defaultEquipeSetor.toUpper());
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
        stream.writeAttribute("text:style-name", "P16");
        stream.writeCharacters(defaultEquipeSetor.toUpper());
        stream.writeEndElement(); // text:p
    }

    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell17");
    stream.writeAttribute("table:number-rows-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P18");
    stream.writeCharacters("PROCESSO Nº");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P19");
    stream.writeCharacters(numProcesso);
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow20");

    stream.writeStartElement("table:covered-table-cell");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "Normal");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell21");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P22");
    stream.writeCharacters("NOTIFICAÇÃO PARA PAGAMENTO");

    stream.writeStartElement("text:s");
    stream.writeEndElement(); // text:s
    stream.writeCharacters("DE MULTA");
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
    stream.writeAttribute("table:style-name", "TableRow23");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell24");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P25");
    stream.writeCharacters("NOTIFICADO");
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
    stream.writeAttribute("table:style-name", "TableRow26");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell27");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P28");
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
    stream.writeAttribute("table:style-name", "TableRow29");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell30");
    stream.writeAttribute("table:number-columns-spanned", "4");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P31");
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
    stream.writeAttribute("table:style-name", "TableCell32");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P33");
    stream.writeCharacters(QString("CEP: %1").arg(estabCEP));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow34");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell35");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P36");
    stream.writeCharacters(QString("MUNICÍPIO: %1").arg(estabCidade));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell37");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P38");
    stream.writeCharacters(QString("CNPJ ou CPF: %1").arg(estabCnpjCpf));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow39");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell40");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P41");
    stream.writeCharacters(QString("RAMO DE ATIVIDADE: %1").arg(estabRamoAtiv));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell42");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P43");
    stream.writeCharacters(QString("Nº ALVARÁ SANITÁRIO: %1").arg(numAlvara));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow44");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell45");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P46");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T47");
    stream.writeCharacters("Em cumprimento ao disposto no artigo 33, da Lei Federal nº 6437/77, de 20 de agosto de 1977, fica notificado(a) o infrator");

    stream.writeStartElement("text:s");
    stream.writeEndElement(); // text:s
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T48");
    stream.writeCharacters(QString("acima qualificado(a) para, no prazo de 30 (trinta) dias a contar do recebimento desta, efetuar o pagamento da quantia de R$ %1 (%2), correspondente à MULTA imposta em decorrência de infração apurada em Processo Administrativo Sanitário,").arg(valorMulta).arg(valorMultaPorExtenso));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T49");
    stream.writeCharacters(QString(" instaurado a partir da lavratura do Auto de Infração Sanitária nº %1, de %2 de %3 de %4. O pagamento deverá ser efetuado por meio de Guia de Arrecadação, a qual poderá ser obtida no “site” da Secretaria da Fazenda na Internet ").arg(numAuto).arg(diaAuto).arg(mesAuto).arg(anoAuto));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:a");
    stream.writeAttribute("xlink:href", "http://www.sefaz.rs.gov.br/");
    stream.writeAttribute("office:target-frame-name", "_top");
    stream.writeAttribute("xlink:show", "replace");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T51");
    stream.writeCharacters("http://www.sefaz.rs.gov.br");
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:a

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T52");
    stream.writeCharacters(", seguindo os seguintes passos: 1- no canto superior esquerdo, na aba Serviços e Informações, clicar em “Buscar por Assunto”, “Pagamento de Tributos (Guia de Arrecadação)”, “Pagamento ");
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T53");
    stream.writeCharacters("de Taxas e Demais Receitas”, “Emissão de Guia de Arrecadação – GA Taxas/demais Receitas por órgão Prestador de Serviço”; 2- na opção Órgão do Estado, clicar em “Secretaria Estadual da Saúde”, “Avançar”; 3- na opção “Prestador do Serviço”, clicar em ");
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T54");
    stream.writeCharacters("“Fundo Estadual de Saúde”, “Avançar”; 4- na opção “Taxa de Serviço”, clicar na opção “Multas Previstas na Legislação Sanitária – Fund Est Saúde”, “Avançar”; 5- Preencher os dados solicitados. No campo “Referência”, inserir o número do Processo Administrativo Sanitário");
    stream.writeEndElement(); // text:span

    QString nomeEquipeFormatado, enderecoEquipeFormatado;
    if (defaultEquipeTipo == "Estadual") {
        if (defaultEquipeNome == "Centro Estadual de Vigilância em Saúde") {
            nomeEquipeFormatado = QString("%1 do %2").arg(defaultEquipeSetor).arg(defaultEquipeNome);
        } else {
            nomeEquipeFormatado = QString("%1 da %2").arg(defaultEquipeSetor).arg(defaultEquipeNome);
        }
    } else {
        nomeEquipeFormatado = QString("%1 do Município de %2").arg(defaultEquipeSetor).arg(defaultEquipeCidade);
    }
    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T55");
    stream.writeCharacters(QString(". Clicar em “Avançar”; 6- Gerar a guia de arrecadação e imprimir. A cópia da Guia de Arrecadação, devidamente quitada, deverá ser encaminhada a(o) %1, no(a) %2").arg(nomeEquipeFormatado).arg(enderecoEquipeFormatado));
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T56");
    stream.writeCharacters(", no prazo de até 05 (cinco) dias após o pagamento. A não comprovação do pagamento da multa poderá implicar no seu encaminhamento para inscrição como débito em dívida ativa do Estado.");
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
    stream.writeAttribute("table:style-name", "TableRow57");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell58");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P59");
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
    stream.writeAttribute("table:style-name", "TableRow60");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell61");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P62");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P63");
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaNotif).arg(mesNotif).arg(anoNotif));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P64");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P65");
    stream.writeCharacters("___________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P66");
    stream.writeCharacters("ASSINATURA");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P67");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P68");
    stream.writeCharacters(QString("Nome: %1").arg(nomeServidor));
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P69");
    stream.writeCharacters(QString("Identidade Funcional: %1").arg(idServidor));
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell70");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P71");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P72");
    stream.writeCharacters("RECEBI A 1ª VIA EM _____/_____/_______.");
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
    stream.writeCharacters("INFRATOR");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P76");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P77");
    stream.writeCharacters("Nome: ______________________________________________.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P78");
    stream.writeCharacters("RG/CPF: ____________________________________________.");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell
    stream.writeEndElement(); // table:table-row

    stream.writeStartElement("table:table-row");
    stream.writeAttribute("table:style-name", "TableRow79");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell80");
    stream.writeAttribute("table:number-columns-spanned", "5");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P81");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P82");
    stream.writeCharacters("QUANDO O INFRATOR RECUSAR-SE A ASSINAR OU FOR ANALFABETO:");
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
    stream.writeAttribute("table:style-name", "TableRow83");

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell84");
    stream.writeAttribute("table:number-columns-spanned", "2");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P85");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P86");
    stream.writeCharacters("TESTEMUNHA");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // table:table-cell

    stream.writeStartElement("table:covered-table-cell");
    stream.writeEndElement(); // table:covered-table-cell

    stream.writeStartElement("table:table-cell");
    stream.writeAttribute("table:style-name", "TableCell87");
    stream.writeAttribute("table:number-columns-spanned", "3");

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P88");
    stream.writeCharacters("__________________________________________");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P89");
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

    //QString dirToCompress = "modelos/Notificação para Pagamento de Multa APÓS DECISÃO FINAL ODT";
    QString dirToCompress = "modelos/ODT";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/ODT");
    dir.removeRecursively();
}

void MainWindow::notificacaoPagamentoMultaAposDecisaoFinalDOCX(QString fn)
{
    setupEstruturaDOCX();

    //QFile file("modelos/Notificação para Pagamento de Multa APÓS DECISÃO FINAL DOCX/word/document.xml");
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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "4CBEA11C");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "7F356652");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("wp14:anchorId", "6B8A1F6C");
    stream.writeAttribute("wp14:editId", "2CE45C2F");

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
    stream.writeAttribute("w14:paraId", "3EA3524C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "1A9906DA");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
        stream.writeAttribute("w14:paraId", "7BA8997B");
        stream.writeAttribute("w14:textId", "21F21C3B");
        stream.writeAttribute("w:rsidR", "00AE1963");
        stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
        stream.writeCharacters(defaultEquipeNome.toUpper());
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r
        stream.writeEndElement(); // w:p

        stream.writeStartElement("w:p");
        stream.writeAttribute("w14:paraId", "6031B9C1");
        stream.writeAttribute("w14:textId", "7CAE9620");
        stream.writeAttribute("w:rsidR", "0076530D");
        stream.writeAttribute("w:rsidRDefault", "0076530D");

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
        stream.writeCharacters(defaultEquipeNucleo.toUpper());
        stream.writeEndElement(); // w:t
        stream.writeEndElement(); // w:r
        stream.writeEndElement(); // w:p
    }

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "0E14FE0B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters(defaultEquipeSetor.toUpper());
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
    stream.writeAttribute("w14:paraId", "5662B74C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "5662B74C");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "66AA9C2D");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "48378171");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00000000");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");
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
    stream.writeAttribute("w14:paraId", "146DB6D4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters("NOTIFICAÇÃO PARA PAGAMENTO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

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
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(" DE MULTA");
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
    stream.writeAttribute("w14:paraId", "500B9046");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00000000");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "54159B3B");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0076530D");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "424");
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
    stream.writeAttribute("w14:paraId", "3A3666E1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters("NOTIFICADO");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "49171E6B");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "5BF109F0");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "39FE3873");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "16F6CDBC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "153F5721");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "6FB0F03A");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "68C854BD");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "6867C301");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "4A2EB36A");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "71FCCC5D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "0A391030");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "7F2714C9");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "7CA5C943");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Textbody");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "0");
    stream.writeAttribute("w:line", "360");
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
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("Em cumprimento ao disposto no artigo 33, da Lei Federal nº 6437/77, de 20 de agosto de 1977, fica notificado(a) o infrator");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(QString("acima qualificado(a) para, no prazo de 30 (trinta) dias a contar do recebimento desta, efetuar o pagamento da quantia de R$ %1 (%2), correspondente à MULTA imposta em decorrência de infração apurada em Processo Administrativo Sanitário,").arg(valorMulta).arg(valorMultaPorExtenso));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(QString("instaurado a partir da lavratura do Auto de Infração Sanitária nº %1, de %2 de %3 de %4").arg(numAuto).arg(diaAuto).arg(mesAuto).arg(anoAuto));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(". O pagamento deverá ser efetuado por meio de Guia de Arrecadação, a qual poderá ser obtida no “site” da Secretaria da Fazenda na Internet");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:hyperlink");
    stream.writeAttribute("r:id", "rId7");
    stream.writeAttribute("w:history", "1");

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:color");
    stream.writeAttribute("w:val", "000000");
    stream.writeEndElement(); // w:color

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("http://www.sefaz.rs.gov.br");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:hyperlink

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters(", seguindo os seguintes passos: 1- no canto superior esquerdo, na aba Serviços e Informações, clicar em “Buscar por Assunto”, “Pagamento de Tributos (Guia de Arrecadação)”, “Pagam");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("ento de Taxas e Demais Receitas”, “Emissão de Guia de Arrecadação – GA Taxas/demais Receitas por órgão Prestador de Serviço”; 2- na opção Órgão do Estado, clicar em “Secretaria Estadual da Saúde”, “Avançar”; 3- na opção “Prestador do Serviço”, clicar em “F");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("undo Estadual de Saúde”, “Avançar”; 4- na opção “Taxa de Serviço”, clicar na opção “Multas Previstas na Legislação Sanitária – ");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("Fund Est Saúde”, “Avançar”; 5- Preencher os dados solicitados. No campo “Referência”, inserir o número do Processo Administrativo");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("Sanitário. Clicar em “Avançar”; 6- Gerar a guia de arrecadação e imprimir. A cópia da Guia de Arrecadação, devidamente quitada, deverá ser encaminhada à Vigilância Sanitária da 14ª Coordenadoria Regional de Saúde, na Avenida Rio Branco, 634, sala 39, Cent");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "22");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("ro, Santa Rosa RS, CEP 98780-100, no prazo de até 05 (cinco) dias após o pagamento. A não comprovação do pagamento da multa poderá implicar no seu encaminhamento para inscrição como débito em dívida ativa do Estado.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p
    stream.writeEndElement(); // w:tc
    stream.writeEndElement(); // w:tr

    stream.writeStartElement("w:tr");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "78F2344D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0076530D");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

    stream.writeStartElement("w:trPr");

    stream.writeStartElement("w:trHeight");
    stream.writeAttribute("w:val", "442");
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
    stream.writeAttribute("w14:paraId", "19555031");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "4A2A2E0C");
    stream.writeAttribute("w14:textId", "77777777");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "7ECD5944");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "26E68A1A");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters(QString("%1, %2 de %3 de %4.").arg(estabCidade).arg(diaNotif).arg(mesNotif).arg(anoNotif));
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellEnd");
    stream.writeEndElement(); // w:proofErr

    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "754CDFC8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "213201C8");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "167B0E88");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters("ASSINATURA");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "09E925B7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "50589AB2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "723387DC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "3DF00406");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "3BD732D2");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "49C5778F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "3788778D");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters("______");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "095F2475");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeCharacters("INFRATOR");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "220653E1");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "67CC9B21");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w14:paraId", "2F682A44");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");

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
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w14:paraId", "78DBD81F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0076530D");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "4F3556CE");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

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
    stream.writeAttribute("w14:paraId", "2F9B6E1B");
    stream.writeAttribute("w14:textId", "5F280FC8");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00A71CC0");
    stream.writeAttribute("w:rsidP", "0076530D");

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
    stream.writeCharacters("QUANDO O INFRATOR ");
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
    stream.writeAttribute("w:rsidR", "0076530D");
    stream.writeAttribute("w14:paraId", "0AAA0FF7");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidTr", "0076530D");

    stream.writeStartElement("w:tblPrEx");

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPrEx

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
    stream.writeAttribute("w14:paraId", "631DAEEC");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0076530D");
    stream.writeAttribute("w:rsidRDefault", "0076530D");
    stream.writeAttribute("w:rsidP", "0076530D");

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
    stream.writeAttribute("w14:paraId", "3F3B9E05");
    stream.writeAttribute("w14:textId", "04CC70A6");
    stream.writeAttribute("w:rsidR", "0076530D");
    stream.writeAttribute("w:rsidRDefault", "0076530D");
    stream.writeAttribute("w:rsidP", "0076530D");

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
    stream.writeAttribute("w14:paraId", "320A4CC6");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "0076530D");
    stream.writeAttribute("w:rsidRDefault", "0076530D");
    stream.writeAttribute("w:rsidP", "0076530D");

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
    stream.writeAttribute("w14:paraId", "1AAD6FE3");
    stream.writeAttribute("w14:textId", "503011CF");
    stream.writeAttribute("w:rsidR", "0076530D");
    stream.writeAttribute("w:rsidRDefault", "0076530D");
    stream.writeAttribute("w:rsidP", "0076530D");

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
    stream.writeAttribute("w14:paraId", "24FF270F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00AE1963");
    stream.writeAttribute("w:rsidRDefault", "00AE1963");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:bookmarkStart");
    stream.writeAttribute("w:id", "0");
    stream.writeAttribute("w:name", "_GoBack");
    stream.writeEndElement(); // w:bookmarkStart

    stream.writeStartElement("w:bookmarkEnd");
    stream.writeAttribute("w:id", "0");
    stream.writeEndElement(); // w:bookmarkEnd
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00AE1963");

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

    //QString dirToCompress = "modelos/Notificação para Pagamento de Multa APÓS DECISÃO FINAL DOCX";
    QString dirToCompress = "modelos/DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);

    QDir dir("modelos/DOCX");
    dir.removeRecursively();
}
