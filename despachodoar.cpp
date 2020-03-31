#include "despachodoar.h"
#include "ui_despachodoar.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

DespachodoAR::DespachodoAR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DespachodoAR)
{
    ui->setupUi(this);
}

DespachodoAR::~DespachodoAR()
{
    delete ui;
}

void MainWindow::despachoARODT(QString fn)
{
    QFile file("modelos/Despacho do AR ODT/content.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);

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
    stream.writeAttribute("style:name", "Mangal1");
    stream.writeAttribute("svg:font-family", "Mangal");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Liberation Serif");
    stream.writeAttribute("svg:font-family", "'Liberation Serif'");
    stream.writeAttribute("style:font-family-generic", "roman");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Times New Roman");
    stream.writeAttribute("svg:font-family", "'Times New Roman'");
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
    stream.writeAttribute("style:name", "Mangal");
    stream.writeAttribute("svg:font-family", "Mangal");
    stream.writeAttribute("style:font-family-generic", "system");
    stream.writeAttribute("style:font-pitch", "variable");
    stream.writeEndElement(); // style:font-face

    stream.writeStartElement("style:font-face");
    stream.writeAttribute("style:name", "Microsoft YaHei");
    stream.writeAttribute("svg:font-family", "'Microsoft YaHei'");
    stream.writeAttribute("style:font-family-generic", "system");
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
    stream.writeAttribute("style:name", "P1");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Header");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P2");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Header");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("officeooo:rsid", "00184e93");
    stream.writeAttribute("officeooo:paragraph-rsid", "00184e93");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P3");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-weight", "normal");
    stream.writeAttribute("officeooo:rsid", "001a41b1");
    stream.writeAttribute("officeooo:paragraph-rsid", "001a41b1");
    stream.writeAttribute("style:font-weight-asian", "normal");
    stream.writeAttribute("style:font-weight-complex", "normal");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P4");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("officeooo:rsid", "00184e93");
    stream.writeAttribute("officeooo:paragraph-rsid", "001c11c7");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P5");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "justify");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-weight", "normal");
    stream.writeAttribute("officeooo:rsid", "001a41b1");
    stream.writeAttribute("officeooo:paragraph-rsid", "001a41b1");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("style:font-weight-asian", "normal");
    stream.writeAttribute("style:font-weight-complex", "normal");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P6");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Header");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeAttribute("fo:padding", "0.049cm");
    stream.writeAttribute("fo:border-left", "none");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.79pt solid #000000");
    stream.writeAttribute("style:shadow", "none");
    stream.writeAttribute("style:writing-mode", "page");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("officeooo:rsid", "00184e93");
    stream.writeAttribute("officeooo:paragraph-rsid", "00184e93");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "P7");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Header");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:text-align", "center");
    stream.writeAttribute("style:justify-single-word", "false");
    stream.writeAttribute("fo:padding", "0.049cm");
    stream.writeAttribute("fo:border-left", "none");
    stream.writeAttribute("fo:border-right", "none");
    stream.writeAttribute("fo:border-top", "none");
    stream.writeAttribute("fo:border-bottom", "0.79pt solid #000000");
    stream.writeAttribute("style:shadow", "none");
    stream.writeAttribute("style:writing-mode", "page");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Times New Roman");
    stream.writeAttribute("fo:font-size", "11pt");
    stream.writeAttribute("fo:font-weight", "bold");
    stream.writeAttribute("officeooo:rsid", "00207be8");
    stream.writeAttribute("officeooo:paragraph-rsid", "00207be8");
    stream.writeAttribute("style:font-size-asian", "11pt");
    stream.writeAttribute("style:font-weight-asian", "bold");
    stream.writeAttribute("style:font-size-complex", "11pt");
    stream.writeAttribute("style:font-weight-complex", "bold");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T1");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "001c1a08");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T2");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:background-color", "#ffff00");
    stream.writeAttribute("loext:char-shading-value", "0");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T3");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "001c1a08");
    stream.writeAttribute("fo:background-color", "#ffff00");
    stream.writeAttribute("loext:char-shading-value", "0");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T4");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "001fdafc");
    stream.writeAttribute("fo:background-color", "#ffff00");
    stream.writeAttribute("loext:char-shading-value", "0");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T5");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("loext:char-shading-value", "0");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T6");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "00207be8");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("loext:char-shading-value", "0");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T7");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "00207be8");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "T8");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("officeooo:rsid", "001fdafc");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "fr1");
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:parent-style-name", "Graphics");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("fo:margin-left", "0cm");
    stream.writeAttribute("fo:margin-right", "0cm");
    stream.writeAttribute("style:vertical-pos", "top");
    stream.writeAttribute("style:vertical-rel", "baseline");
    stream.writeAttribute("fo:padding", "0.002cm");
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

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "fr2");
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:parent-style-name", "Graphics");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("style:run-through", "foreground");
    stream.writeAttribute("style:wrap", "none");
    stream.writeAttribute("style:vertical-pos", "top");
    stream.writeAttribute("style:vertical-rel", "paragraph");
    stream.writeAttribute("style:horizontal-pos", "center");
    stream.writeAttribute("style:horizontal-rel", "paragraph");
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

    stream.writeStartElement("office:forms");
    stream.writeAttribute("form:automatic-focus", "false");
    stream.writeAttribute("form:apply-design-mode", "false");
    stream.writeEndElement(); // office:forms

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

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P4");
    stream.writeCharacters("PROCESSO N°");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T8");
    stream.writeCharacters("00/0000-0000000-0");
    stream.writeEndElement(); // text:span
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("Certifico que expedi, via postal com AR,");

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T7");
    stream.writeCharacters("o(a) __________________________________");
    stream.writeEndElement(); // text:span
    stream.writeCharacters("no dia ___ de ____ de ____.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P5");
    stream.writeCharacters("Certifico que juntei o AR no Processo no dia ___ de ___ de ____.");
    stream.writeEndElement(); // text:p

    stream.writeStartElement("text:p");
    stream.writeAttribute("text:style-name", "P3");

    stream.writeStartElement("draw:frame");
    stream.writeAttribute("draw:style-name", "fr2");
    stream.writeAttribute("draw:name", "Figura2");
    stream.writeAttribute("text:anchor-type", "paragraph");
    stream.writeAttribute("svg:width", "12.409cm");
    stream.writeAttribute("svg:height", "17.701cm");
    stream.writeAttribute("draw:z-index", "1");

    stream.writeStartElement("draw:image");
    stream.writeAttribute("xlink:href", "Pictures/100000000000077000000A98A8B607AC2763BFAB.png");
    stream.writeAttribute("xlink:type", "simple");
    stream.writeAttribute("xlink:show", "embed");
    stream.writeAttribute("xlink:actuate", "onLoad");
    stream.writeEndElement(); // draw:image
    stream.writeEndElement(); // draw:frame

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T5");
    stream.writeCharacters("_____");
    stream.writeEndElement(); // text:span

    stream.writeStartElement("text:span");
    stream.writeAttribute("text:style-name", "T6");
    stream.writeCharacters("__________");
    stream.writeEndElement(); // text:span
    stream.writeCharacters("– VISA – 14ª CRS");
    stream.writeEndElement(); // text:p
    stream.writeEndElement(); // office:text
    stream.writeEndElement(); // office:body
    stream.writeEndElement(); // office:document-content

    stream.writeEndDocument();

    file.close();

    QString dirToCompress = "modelos/Despacho do AR ODT";
    JlCompress::compressDir(fn, dirToCompress, true);
}

void MainWindow::despachoARDOCX(QString fn)
{
    QFile file("modelos/Despacho do AR DOCX/word/document.xml");
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

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "3DCA9712");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00171BF3");
    stream.writeAttribute("w:rsidRDefault", "00BE1E8F");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:bookmarkStart");
    stream.writeAttribute("w:id", "0");
    stream.writeAttribute("w:name", "_GoBack");
    stream.writeEndElement(); // w:bookmarkStart

    stream.writeStartElement("w:bookmarkEnd");
    stream.writeAttribute("w:id", "0");
    stream.writeEndElement(); // w:bookmarkEnd

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:b");
    stream.writeEndElement(); // w:b

    stream.writeStartElement("w:bCs");
    stream.writeEndElement(); // w:bCs
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("PROCESSO N° 00/0000-0000000-0");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "20125AA4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00171BF3");
    stream.writeAttribute("w:rsidRDefault", "00BE1E8F");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("Certifico que expedi, via postal com AR, o(a) __________________________________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(" no dia ___ de ____ ");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("de");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellEnd");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(" ____.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "7B2C1BE4");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00171BF3");
    stream.writeAttribute("w:rsidRDefault", "00BE1E8F");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "both");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters("Certifico que juntei o AR no Processo no dia ___ de ___");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellStart");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("de");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:proofErr");
    stream.writeAttribute("w:type", "spellEnd");
    stream.writeEndElement(); // w:proofErr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(" ____.");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:p");
    stream.writeAttribute("w14:paraId", "6637039F");
    stream.writeAttribute("w14:textId", "77777777");
    stream.writeAttribute("w:rsidR", "00171BF3");
    stream.writeAttribute("w:rsidRDefault", "00BE1E8F");

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:pStyle");
    stream.writeAttribute("w:val", "Standard");
    stream.writeEndElement(); // w:pStyle

    stream.writeStartElement("w:jc");
    stream.writeAttribute("w:val", "center");
    stream.writeEndElement(); // w:jc

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:noProof");
    stream.writeEndElement(); // w:noProof
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:drawing");

    stream.writeStartElement("wp:anchor");
    stream.writeAttribute("distT", "0");
    stream.writeAttribute("distB", "0");
    stream.writeAttribute("distL", "114300");
    stream.writeAttribute("distR", "114300");
    stream.writeAttribute("simplePos", "0");
    stream.writeAttribute("relativeHeight", "251658240");
    stream.writeAttribute("behindDoc", "0");
    stream.writeAttribute("locked", "0");
    stream.writeAttribute("layoutInCell", "1");
    stream.writeAttribute("allowOverlap", "1");
    stream.writeAttribute("wp14:anchorId", "6792C619");
    stream.writeAttribute("wp14:editId", "04C69709");

    stream.writeStartElement("wp:simplePos");
    stream.writeAttribute("x", "0");
    stream.writeAttribute("y", "0");
    stream.writeEndElement(); // wp:simplePos

    stream.writeStartElement("wp:positionH");
    stream.writeAttribute("relativeFrom", "column");

    stream.writeStartElement("wp:align");
    stream.writeCharacters("center");
    stream.writeEndElement(); // wp:align
    stream.writeEndElement(); // wp:positionH

    stream.writeStartElement("wp:positionV");
    stream.writeAttribute("relativeFrom", "paragraph");

    stream.writeStartElement("wp:align");
    stream.writeCharacters("top");
    stream.writeEndElement(); // wp:align
    stream.writeEndElement(); // wp:positionV

    stream.writeStartElement("wp:extent");
    stream.writeAttribute("cx", "4467240");
    stream.writeAttribute("cy", "6372360");
    stream.writeEndElement(); // wp:extent

    stream.writeStartElement("wp:effectExtent");
    stream.writeAttribute("l", "0");
    stream.writeAttribute("t", "0");
    stream.writeAttribute("r", "9510");
    stream.writeAttribute("b", "9390");
    stream.writeEndElement(); // wp:effectExtent

    stream.writeStartElement("wp:wrapTopAndBottom");
    stream.writeEndElement(); // wp:wrapTopAndBottom

    stream.writeStartElement("wp:docPr");
    stream.writeAttribute("id", "2");
    stream.writeAttribute("name", "Figura2");
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
    stream.writeAttribute("cx", "4467240");
    stream.writeAttribute("cy", "6372360");
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
    stream.writeEndElement(); // wp:anchor
    stream.writeEndElement(); // w:drawing
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeCharacters("_______________");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r

    stream.writeStartElement("w:r");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Times New Roman");
    stream.writeAttribute("w:hAnsi", "Times New Roman");
    stream.writeEndElement(); // w:rFonts
    stream.writeEndElement(); // w:rPr

    stream.writeStartElement("w:t");
    stream.writeAttribute("xml:space", "preserve");
    stream.writeCharacters(" – VISA – 14ª CRS");
    stream.writeEndElement(); // w:t
    stream.writeEndElement(); // w:r
    stream.writeEndElement(); // w:p

    stream.writeStartElement("w:sectPr");
    stream.writeAttribute("w:rsidR", "00171BF3");

    stream.writeStartElement("w:headerReference");
    stream.writeAttribute("w:type", "default");
    stream.writeAttribute("r:id", "rId7");
    stream.writeEndElement(); // w:headerReference

    stream.writeStartElement("w:pgSz");
    stream.writeAttribute("w:w", "11906");
    stream.writeAttribute("w:h", "16838");
    stream.writeEndElement(); // w:pgSz

    stream.writeStartElement("w:pgMar");
    stream.writeAttribute("w:top", "1134");
    stream.writeAttribute("w:right", "1134");
    stream.writeAttribute("w:bottom", "1134");
    stream.writeAttribute("w:left", "1134");
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

    QString dirToCompress = "modelos/Despacho do AR DOCX";
    JlCompress::compressDir(fn, dirToCompress, true);
}
