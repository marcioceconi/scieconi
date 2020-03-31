#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupEstruturaODT()
{
    // Cria diretórios necessários
    if (!QDir("modelos").exists()) {
        QDir().mkdir("modelos");
    }
    if (!QDir("modelos/ODT").exists()) {
        QDir().mkdir("modelos/ODT");
    }
    if (!QDir("modelos/ODT/media").exists()) {
        QDir().mkdir("modelos/ODT/media");
    }
    if (!QDir("modelos/ODT/META-INF").exists()) {
        QDir().mkdir("modelos/ODT/META-INF");
    }

    // Salva brasão da equipe no diretório modelos/ODT/media e renomeia arquivo para image1
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
    QFile::copy(defaultEquipeBrasao, QString("modelos/ODT/media/image1.%1").arg(extensaoImage));

    // Cria arquivo styles.xml em modelos/ODT
    createODTStylesXml();
    // Cria arquivo settings.xml em modelos/ODT
    createODTSettingsXml();
    // Cria arquivo mimetype em modelos/ODT
    createODTMimetype();
    // Cria arquivo meta.xml em modelos/ODT
    createODTMetaXml();
    // Cria arquivo manifest.xml em modelos/ODT/META-INF
    createODTManifestXml();
}

void MainWindow::createODTStylesXml()
{
    QFile file("modelos/ODT/styles.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("office:document-styles");
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

    stream.writeStartElement("office:styles");

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "table");

    stream.writeStartElement("style:table-properties");
    stream.writeAttribute("fo:margin-left", "0in");
    stream.writeAttribute("table:border-model", "collapsing");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("table:align", "left");
    stream.writeEndElement(); // style:table-properties
    stream.writeEndElement(); // style:default-style

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "table-column");

    stream.writeStartElement("style:table-column-properties");
    stream.writeAttribute("style:use-optimal-column-width", "true");
    stream.writeEndElement(); // style:table-column-properties
    stream.writeEndElement(); // style:default-style

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "table-row");

    stream.writeStartElement("style:table-row-properties");
    stream.writeAttribute("style:min-row-height", "0in");
    stream.writeAttribute("style:use-optimal-row-height", "true");
    stream.writeAttribute("fo:keep-together", "auto");
    stream.writeEndElement(); // style:table-row-properties
    stream.writeEndElement(); // style:default-style

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "table-cell");

    stream.writeStartElement("style:table-cell-properties");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("style:glyph-orientation-vertical", "auto");
    stream.writeAttribute("style:vertical-align", "top");
    stream.writeAttribute("fo:wrap-option", "wrap");
    stream.writeEndElement(); // style:table-cell-properties
    stream.writeEndElement(); // style:default-style

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:keep-with-next", "auto");
    stream.writeAttribute("fo:keep-together", "auto");
    stream.writeAttribute("fo:widows", "2");
    stream.writeAttribute("fo:orphans", "2");
    stream.writeAttribute("fo:break-before", "auto");
    stream.writeAttribute("text:number-lines", "true");
    stream.writeAttribute("fo:border", "none");
    stream.writeAttribute("fo:padding", "0in");
    stream.writeAttribute("style:shadow", "none");
    stream.writeAttribute("style:line-break", "strict");
    stream.writeAttribute("style:punctuation-wrap", "hanging");
    stream.writeAttribute("style:text-autospace", "ideograph-alpha");
    stream.writeAttribute("style:snap-to-layout-grid", "true");
    stream.writeAttribute("fo:text-align", "start");
    stream.writeAttribute("style:writing-mode", "lr-tb");
    stream.writeAttribute("style:vertical-align", "baseline");
    stream.writeAttribute("fo:line-height", "100%");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("style:tab-stop-distance", "0.4923in");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Liberation Serif");
    stream.writeAttribute("style:font-name-asian", "SimSun");
    stream.writeAttribute("style:font-name-complex", "Lucida Sans");
    stream.writeAttribute("fo:font-weight", "normal");
    stream.writeAttribute("style:font-weight-asian", "normal");
    stream.writeAttribute("style:font-weight-complex", "normal");
    stream.writeAttribute("fo:font-style", "normal");
    stream.writeAttribute("style:font-style-asian", "normal");
    stream.writeAttribute("style:font-style-complex", "normal");
    stream.writeAttribute("fo:text-transform", "none");
    stream.writeAttribute("fo:font-variant", "normal");
    stream.writeAttribute("style:text-line-through-type", "none");
    stream.writeAttribute("style:text-outline", "false");
    stream.writeAttribute("style:font-relief", "none");
    stream.writeAttribute("style:use-window-font-color", "true");
    stream.writeAttribute("fo:letter-spacing", "normal");
    stream.writeAttribute("style:text-scale", "100%");
    stream.writeAttribute("style:letter-kerning", "true");
    stream.writeAttribute("style:text-position", "0% 100%");
    stream.writeAttribute("fo:font-size", "12pt");
    stream.writeAttribute("style:font-size-asian", "12pt");
    stream.writeAttribute("style:font-size-complex", "12pt");
    stream.writeAttribute("fo:background-color", "transparent");
    stream.writeAttribute("style:text-underline-type", "none");
    stream.writeAttribute("style:text-underline-color", "font-color");
    stream.writeAttribute("style:text-emphasize", "none");
    stream.writeAttribute("fo:language", "pt");
    stream.writeAttribute("fo:country", "BR");
    stream.writeAttribute("style:language-asian", "zh");
    stream.writeAttribute("style:country-asian", "CN");
    stream.writeAttribute("style:language-complex", "hi");
    stream.writeAttribute("style:country-complex", "IN");
    stream.writeAttribute("style:text-combine", "none");
    stream.writeAttribute("fo:hyphenate", "true");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:default-style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Normal");
    stream.writeAttribute("style:display-name", "Normal");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Fonteparág.padrão");
    stream.writeAttribute("style:display-name", "Fonte parág. padrão");
    stream.writeAttribute("style:family", "text");
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Standard");
    stream.writeAttribute("style:display-name", "Standard");
    stream.writeAttribute("style:family", "paragraph");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Heading");
    stream.writeAttribute("style:display-name", "Heading");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");
    stream.writeAttribute("style:next-style-name", "Textbody");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:keep-with-next", "always");
    stream.writeAttribute("fo:margin-top", "0.1666in");
    stream.writeAttribute("fo:margin-bottom", "0.0833in");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("style:font-name", "Liberation Sans");
    stream.writeAttribute("style:font-name-asian", "Microsoft YaHei");
    stream.writeAttribute("fo:font-size", "14pt");
    stream.writeAttribute("style:font-size-asian", "14pt");
    stream.writeAttribute("style:font-size-complex", "14pt");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Textbody");
    stream.writeAttribute("style:display-name", "Text body");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("fo:margin-bottom", "0.0972in");
    stream.writeAttribute("fo:line-height", "120%");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Lista");
    stream.writeAttribute("style:display-name", "Lista");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Textbody");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Legenda");
    stream.writeAttribute("style:display-name", "Legenda");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("text:number-lines", "false");
    stream.writeAttribute("fo:margin-top", "0.0833in");
    stream.writeAttribute("fo:margin-bottom", "0.0833in");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:font-style", "italic");
    stream.writeAttribute("style:font-style-asian", "italic");
    stream.writeAttribute("style:font-style-complex", "italic");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Index");
    stream.writeAttribute("style:display-name", "Index");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("text:number-lines", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "TableContents");
    stream.writeAttribute("style:display-name", "Table Contents");
    stream.writeAttribute("style:family", "paragraph");
    stream.writeAttribute("style:parent-style-name", "Standard");

    stream.writeStartElement("style:paragraph-properties");
    stream.writeAttribute("text:number-lines", "false");
    stream.writeEndElement(); // style:paragraph-properties

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:hyphenate", "false");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:name", "Internetlink");
    stream.writeAttribute("style:display-name", "Internet link");
    stream.writeAttribute("style:family", "text");

    stream.writeStartElement("style:text-properties");
    stream.writeAttribute("fo:color", "#000080");
    stream.writeAttribute("style:text-underline-type", "single");
    stream.writeAttribute("style:text-underline-style", "solid");
    stream.writeAttribute("style:text-underline-width", "auto");
    stream.writeAttribute("style:text-underline-mode", "continuous");
    stream.writeAttribute("style:text-underline-color", "font-color");
    stream.writeEndElement(); // style:text-properties
    stream.writeEndElement(); // style:style

    stream.writeStartElement("text:notes-configuration");
    stream.writeAttribute("text:note-class", "footnote");
    stream.writeAttribute("text:start-value", "0");
    stream.writeAttribute("style:num-format", "1");
    stream.writeAttribute("text:start-numbering-at", "document");
    stream.writeAttribute("text:footnotes-position", "page");
    stream.writeEndElement(); // text:notes-configuration

    stream.writeStartElement("text:notes-configuration");
    stream.writeAttribute("text:note-class", "endnote");
    stream.writeAttribute("text:start-value", "0");
    stream.writeAttribute("style:num-format", "i");
    stream.writeAttribute("text:start-numbering-at", "document");
    stream.writeAttribute("text:footnotes-position", "document");
    stream.writeEndElement(); // text:notes-configuration

    stream.writeStartElement("style:default-page-layout");

    stream.writeStartElement("style:page-layout-properties");
    stream.writeAttribute("style:layout-grid-standard-mode", "true");
    stream.writeEndElement(); // style:page-layout-properties
    stream.writeEndElement(); // style:default-page-layout

    stream.writeStartElement("style:style");
    stream.writeAttribute("style:family", "graphic");
    stream.writeAttribute("style:name", "Graphics");
    stream.writeEndElement(); // style:style

    stream.writeStartElement("style:default-style");
    stream.writeAttribute("style:family", "graphic");

    stream.writeStartElement("style:graphic-properties");
    stream.writeAttribute("draw:fill", "solid");
    stream.writeAttribute("draw:fill-color", "#4472c4");
    stream.writeAttribute("draw:opacity", "100%");
    stream.writeAttribute("draw:stroke", "solid");
    stream.writeAttribute("svg:stroke-width", "0.01389in");
    stream.writeAttribute("svg:stroke-color", "#2f528f");
    stream.writeAttribute("svg:stroke-opacity", "100%");
    stream.writeAttribute("draw:stroke-linejoin", "miter");
    stream.writeAttribute("svg:stroke-linecap", "butt");
    stream.writeEndElement(); // style:graphic-properties
    stream.writeEndElement(); // style:default-style
    stream.writeEndElement(); // office:styles

    stream.writeStartElement("office:automatic-styles");

    stream.writeStartElement("style:page-layout");
    stream.writeAttribute("style:name", "PL0");

    stream.writeStartElement("style:page-layout-properties");
    stream.writeAttribute("fo:page-width", "8.268in");
    stream.writeAttribute("fo:page-height", "11.693in");
    stream.writeAttribute("style:print-orientation", "portrait");
    stream.writeAttribute("fo:margin-top", "0.7875in");
    stream.writeAttribute("fo:margin-left", "0.3937in");
    stream.writeAttribute("fo:margin-bottom", "0.7875in");
    stream.writeAttribute("fo:margin-right", "0.3937in");
    stream.writeAttribute("style:num-format", "1");
    stream.writeAttribute("style:writing-mode", "lr-tb");

    stream.writeStartElement("style:footnote-sep");
    stream.writeAttribute("style:width", "0.007in");
    stream.writeAttribute("style:rel-width", "33%");
    stream.writeAttribute("style:color", "#000000");
    stream.writeAttribute("style:line-style", "solid");
    stream.writeAttribute("style:adjustment", "left");
    stream.writeEndElement(); // style:footnote-sep
    stream.writeEndElement(); // style:page-layout-properties
    stream.writeEndElement(); // style:page-layout
    stream.writeEndElement(); // office:automatic-styles

    stream.writeStartElement("office:master-styles");

    stream.writeStartElement("style:master-page");
    stream.writeAttribute("style:name", "MP0");
    stream.writeAttribute("style:page-layout-name", "PL0");
    stream.writeEndElement(); // style:master-page
    stream.writeEndElement(); // office:master-styles
    stream.writeEndElement(); // office:document-styles

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createODTSettingsXml()
{
    QFile file("modelos/ODT/settings.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("office:document-settings");
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
    stream.writeEndElement(); // office:document-settings

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createODTMimetype()
{
    QFile file("modelos/ODT/mimetype");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << QString("application/vnd.oasis.opendocument.text");

    file.close();
}

void MainWindow::createODTMetaXml()
{
    QFile file("modelos/ODT/meta.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("office:document-meta");
    stream.writeAttribute("xmlns:office", "urn:oasis:names:tc:opendocument:xmlns:office:1.0");
    stream.writeAttribute("xmlns:meta", "urn:oasis:names:tc:opendocument:xmlns:meta:1.0");
    stream.writeAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    stream.writeAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
    stream.writeAttribute("office:version", "1.2");

    stream.writeStartElement("office:meta");

    stream.writeStartElement("meta:generator");
    stream.writeCharacters("MicrosoftOffice/15.0 MicrosoftWord");
    stream.writeEndElement(); // meta:generator

    stream.writeStartElement("dc:creator");
    stream.writeEndElement(); // dc:creator

    stream.writeStartElement("meta:creation-date");
    stream.writeCharacters("2018-12-26T15:15:00Z");
    stream.writeEndElement(); // meta:creation-date

    stream.writeStartElement("dc:date");
    stream.writeCharacters("2020-02-28T00:52:00Z");
    stream.writeEndElement(); // dc:date

    stream.writeStartElement("meta:template");
    stream.writeAttribute("xlink:href", "Normal.dotm");
    stream.writeAttribute("xlink:type", "simple");
    stream.writeEndElement(); // meta:template

    stream.writeStartElement("meta:editing-cycles");
    stream.writeCharacters("5");
    stream.writeEndElement(); // meta:editing-cycles

    stream.writeStartElement("meta:editing-duration");
    stream.writeCharacters("PT600S");
    stream.writeEndElement(); // meta:editing-duration

    stream.writeStartElement("meta:document-statistic");
    stream.writeAttribute("meta:page-count", "1");
    stream.writeAttribute("meta:paragraph-count", "6");
    stream.writeAttribute("meta:word-count", "479");
    stream.writeAttribute("meta:character-count", "3064");
    stream.writeAttribute("meta:row-count", "21");
    stream.writeAttribute("meta:non-whitespace-character-count", "2591");
    stream.writeEndElement(); // meta:document-statistic
    stream.writeEndElement(); // office:meta
    stream.writeEndElement(); // office:document-meta

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createODTManifestXml()
{
    QFile file("modelos/ODT/META-INF/manifest.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("manifest:manifest");
    stream.writeAttribute("xmlns:manifest", "urn:oasis:names:tc:opendocument:xmlns:manifest:1.0");

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", "/");
    stream.writeAttribute("manifest:media-type", "application/vnd.oasis.opendocument.text");
    stream.writeEndElement(); // manifest:file-entry

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", "content.xml");
    stream.writeAttribute("manifest:media-type", "text/xml");
    stream.writeEndElement(); // manifest:file-entry

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", "styles.xml");
    stream.writeAttribute("manifest:media-type", "text/xml");
    stream.writeEndElement(); // manifest:file-entry

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", "settings.xml");
    stream.writeAttribute("manifest:media-type", "text/xml");
    stream.writeEndElement(); // manifest:file-entry

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", "meta.xml");
    stream.writeAttribute("manifest:media-type", "text/xml");
    stream.writeEndElement(); // manifest:file-entry

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

    stream.writeStartElement("manifest:file-entry");
    stream.writeAttribute("manifest:full-path", QString("media/image1.%1").arg(extensaoImage));
    stream.writeAttribute("manifest:media-type", QString("image/%1").arg(extensaoImage));
    stream.writeEndElement(); // manifest:file-entry
    stream.writeEndElement(); // manifest:manifest

    stream.writeEndDocument();

    file.close();
}
