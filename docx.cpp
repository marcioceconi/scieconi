#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupEstruturaDOCX()
{
    // Cria diretórios necessários
    if (!QDir("modelos").exists()) {
        QDir().mkdir("modelos");
    }
    if (!QDir("modelos/DOCX").exists()) {
        QDir().mkdir("modelos/DOCX");
    }
    if (!QDir("modelos/DOCX/_rels").exists()) {
        QDir().mkdir("modelos/DOCX/_rels");
    }
    if (!QDir("modelos/DOCX/docProps").exists()) {
        QDir().mkdir("modelos/DOCX/docProps");
    }
    if (!QDir("modelos/DOCX/word").exists()) {
        QDir().mkdir("modelos/DOCX/word");
    }
    if (!QDir("modelos/DOCX/word/_rels").exists()) {
        QDir().mkdir("modelos/DOCX/word/_rels");
    }
    if (!QDir("modelos/DOCX/word/media").exists()) {
        QDir().mkdir("modelos/DOCX/word/media");
    }
    if (!QDir("modelos/DOCX/word/theme").exists()) {
        QDir().mkdir("modelos/DOCX/word/theme");
    }

    // Salva brasão da equipe no diretório modelos/DOCX/word/media e renomeia arquivo para image1
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
    QFile::copy(defaultEquipeBrasao, QString("modelos/DOCX/word/media/image1.%1").arg(extensaoImage));

    createDOCXContentTypesXml();
    createDOCXAppXml();
    createDOCXCoreXml();
    createDOCXFontTableXml();
    createDOCXSettingsXml();
    createDOCXStylesXml();
    createDOCXWebSettingsXml();
    createDOCXTheme1Xml();
    createDOCXDocumentXmlRels();
    createDOCXRels();
}

void MainWindow::createDOCXContentTypesXml()
{
    QFile file("modelos/DOCX/[Content_Types].xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("Types");
    stream.writeAttribute("xmlns", "http://schemas.openxmlformats.org/package/2006/content-types");

    stream.writeStartElement("Default");
    stream.writeAttribute("Extension", "rels");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-package.relationships+xml");
    stream.writeEndElement(); // Default

    stream.writeStartElement("Default");
    stream.writeAttribute("Extension", "xml");
    stream.writeAttribute("ContentType", "application/xml");
    stream.writeEndElement(); // Default

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/document.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/styles.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/docProps/app.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.extended-properties+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/settings.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml");
    stream.writeEndElement(); // Override

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

    stream.writeStartElement("Default");
    stream.writeAttribute("Extension", QString("%1").arg(extensaoImage));
    stream.writeAttribute("ContentType", QString("image/%1").arg(extensaoImage));
    stream.writeEndElement(); // Default

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/theme/theme1.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.theme+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/fontTable.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/word/webSettings.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-officedocument.wordprocessingml.webSettings+xml");
    stream.writeEndElement(); // Override

    stream.writeStartElement("Override");
    stream.writeAttribute("PartName", "/docProps/core.xml");
    stream.writeAttribute("ContentType", "application/vnd.openxmlformats-package.core-properties+xml");
    stream.writeEndElement(); // Override
    stream.writeEndElement(); // Types

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXAppXml()
{
    QFile file("modelos/DOCX/docProps/app.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("Properties");
    stream.writeAttribute("xmlns", "http://schemas.openxmlformats.org/officeDocument/2006/extended-properties");
    stream.writeAttribute("xmlns:vt", "http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes");

    stream.writeStartElement("Template");
    stream.writeCharacters("Normal.dotm");
    stream.writeEndElement(); // Template

    stream.writeStartElement("TotalTime");
    stream.writeCharacters("12");
    stream.writeEndElement(); // TotalTime

    stream.writeStartElement("Pages");
    stream.writeCharacters("1");
    stream.writeEndElement(); // Pages

    stream.writeStartElement("Words");
    stream.writeCharacters("479");
    stream.writeEndElement(); // Words

    stream.writeStartElement("Characters");
    stream.writeCharacters("2589");
    stream.writeEndElement(); // Characters

    stream.writeStartElement("Application");
    stream.writeCharacters("Microsoft Office Word");
    stream.writeEndElement(); // Application

    stream.writeStartElement("DocSecurity");
    stream.writeCharacters("0");
    stream.writeEndElement(); // DocSecurity

    stream.writeStartElement("Lines");
    stream.writeCharacters("21");
    stream.writeEndElement(); // Lines

    stream.writeStartElement("Paragraphs");
    stream.writeCharacters("6");
    stream.writeEndElement(); // Paragraphs

    stream.writeStartElement("ScaleCrop");
    stream.writeCharacters("false");
    stream.writeEndElement(); // ScaleCrop

    stream.writeStartElement("Company");
    stream.writeEndElement(); // Company

    stream.writeStartElement("LinksUpToDate");
    stream.writeCharacters("false");
    stream.writeEndElement(); // LinksUpToDate

    stream.writeStartElement("CharactersWithSpaces");
    stream.writeCharacters("3062");
    stream.writeEndElement(); // CharactersWithSpaces

    stream.writeStartElement("SharedDoc");
    stream.writeCharacters("false");
    stream.writeEndElement(); // SharedDoc

    stream.writeStartElement("HyperlinksChanged");
    stream.writeCharacters("false");
    stream.writeEndElement(); // HyperlinksChanged

    stream.writeStartElement("AppVersion");
    stream.writeCharacters("12.0000");
    stream.writeEndElement(); // AppVersion
    stream.writeEndElement(); // Properties

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXCoreXml()
{
    QFile file("modelos/DOCX/docProps/core.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("cp:coreProperties");
    stream.writeAttribute("xmlns:cp", "http://schemas.openxmlformats.org/package/2006/metadata/core-properties");
    stream.writeAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
    stream.writeAttribute("xmlns:dcterms", "http://purl.org/dc/terms/");
    stream.writeAttribute("xmlns:dcmitype", "http://purl.org/dc/dcmitype/");
    stream.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

    stream.writeStartElement("dc:title");
    stream.writeEndElement(); // dc:title

    stream.writeStartElement("dc:subject");
    stream.writeEndElement(); // dc:subject

    stream.writeStartElement("dc:creator");
    stream.writeEndElement(); // dc:creator

    stream.writeStartElement("dc:description");
    stream.writeEndElement(); // dc:description

    stream.writeStartElement("cp:lastModifiedBy");
    stream.writeEndElement(); // cp:lastModifiedBy

    stream.writeStartElement("cp:revision");
    stream.writeCharacters("5");
    stream.writeEndElement(); // cp:revision

    stream.writeStartElement("dcterms:created");
    stream.writeAttribute("xsi:type", "dcterms:W3CDTF");
    stream.writeCharacters("2018-12-26T15:15:00Z");
    stream.writeEndElement(); // dcterms:created

    stream.writeStartElement("dcterms:modified");
    stream.writeAttribute("xsi:type", "dcterms:W3CDTF");
    stream.writeCharacters("2020-02-27T18:55:00Z");
    stream.writeEndElement(); // dcterms:modified

    stream.writeStartElement("dc:language");
    stream.writeCharacters("pt-BR");
    stream.writeEndElement(); // dc:language
    stream.writeEndElement(); // cp:coreProperties

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXFontTableXml()
{
    QFile file("modelos/DOCX/word/fontTable.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:fonts");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Liberation Serif");

    stream.writeStartElement("w:altName");
    stream.writeAttribute("w:val", "Times New Roman");
    stream.writeEndElement(); // w:altName

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "02020603050405020304");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "roman");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E0000AFF");
    stream.writeAttribute("w:usb1", "500078FF");
    stream.writeAttribute("w:usb2", "00000021");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "000001BF");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "SimSun");

    stream.writeStartElement("w:altName");
    stream.writeAttribute("w:val", "宋体");
    stream.writeEndElement(); // w:altName

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "02010600030101010101");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "86");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "auto");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "00000003");
    stream.writeAttribute("w:usb1", "288F0000");
    stream.writeAttribute("w:usb2", "00000016");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "00040001");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Lucida Sans");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "020B0602030504020204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "swiss");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "00000003");
    stream.writeAttribute("w:usb1", "00000000");
    stream.writeAttribute("w:usb2", "00000000");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "00000001");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Times New Roman");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "02020603050405020304");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "roman");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E0002AFF");
    stream.writeAttribute("w:usb1", "C0007841");
    stream.writeAttribute("w:usb2", "00000009");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "000001FF");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Liberation Sans");

    stream.writeStartElement("w:altName");
    stream.writeAttribute("w:val", "Arial");
    stream.writeEndElement(); // w:altName

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "020B0604020202020204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "swiss");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E0000AFF");
    stream.writeAttribute("w:usb1", "500078FF");
    stream.writeAttribute("w:usb2", "00000021");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "000001BF");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Microsoft YaHei");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "020B0503020204020204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "86");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "swiss");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "80000287");
    stream.writeAttribute("w:usb1", "280F3C52");
    stream.writeAttribute("w:usb2", "00000016");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "0004001F");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Tahoma");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "020B0604030504040204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "swiss");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E1002EFF");
    stream.writeAttribute("w:usb1", "C000605B");
    stream.writeAttribute("w:usb2", "00000029");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "000101FF");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Mangal");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "02040503050203030202");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "roman");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "00008003");
    stream.writeAttribute("w:usb1", "00000000");
    stream.writeAttribute("w:usb2", "00000000");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "00000001");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Times New Roman;serif");

    stream.writeStartElement("w:altName");
    stream.writeAttribute("w:val", "Times New Roman");
    stream.writeEndElement(); // w:altName

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "00000000000000000000");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "roman");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:notTrueType");
    stream.writeEndElement(); // w:notTrueType

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "default");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "00000000");
    stream.writeAttribute("w:usb1", "00000000");
    stream.writeAttribute("w:usb2", "00000000");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "00000000");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Cambria");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "02040503050406030204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "roman");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E00002FF");
    stream.writeAttribute("w:usb1", "400004FF");
    stream.writeAttribute("w:usb2", "00000000");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "0000019F");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font

    stream.writeStartElement("w:font");
    stream.writeAttribute("w:name", "Calibri");

    stream.writeStartElement("w:panose1");
    stream.writeAttribute("w:val", "020F0502020204030204");
    stream.writeEndElement(); // w:panose1

    stream.writeStartElement("w:charset");
    stream.writeAttribute("w:val", "00");
    stream.writeEndElement(); // w:charset

    stream.writeStartElement("w:family");
    stream.writeAttribute("w:val", "swiss");
    stream.writeEndElement(); // w:family

    stream.writeStartElement("w:pitch");
    stream.writeAttribute("w:val", "variable");
    stream.writeEndElement(); // w:pitch

    stream.writeStartElement("w:sig");
    stream.writeAttribute("w:usb0", "E00002FF");
    stream.writeAttribute("w:usb1", "4000ACFF");
    stream.writeAttribute("w:usb2", "00000001");
    stream.writeAttribute("w:usb3", "00000000");
    stream.writeAttribute("w:csb0", "0000019F");
    stream.writeAttribute("w:csb1", "00000000");
    stream.writeEndElement(); // w:sig
    stream.writeEndElement(); // w:font
    stream.writeEndElement(); // w:fonts

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXSettingsXml()
{
    QFile file("modelos/DOCX/word/settings.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:settings");
    stream.writeAttribute("xmlns:o", "urn:schemas-microsoft-com:office:office");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:m", "http://schemas.openxmlformats.org/officeDocument/2006/math");
    stream.writeAttribute("xmlns:v", "urn:schemas-microsoft-com:vml");
    stream.writeAttribute("xmlns:w10", "urn:schemas-microsoft-com:office:word");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    stream.writeAttribute("xmlns:sl", "http://schemas.openxmlformats.org/schemaLibrary/2006/main");

    stream.writeStartElement("w:zoom");
    stream.writeAttribute("w:percent", "110");
    stream.writeEndElement(); // w:zoom

    stream.writeStartElement("w:proofState");
    stream.writeAttribute("w:spelling", "clean");
    stream.writeEndElement(); // w:proofState

    stream.writeStartElement("w:defaultTabStop");
    stream.writeAttribute("w:val", "709");
    stream.writeEndElement(); // w:defaultTabStop

    stream.writeStartElement("w:hyphenationZone");
    stream.writeAttribute("w:val", "425");
    stream.writeEndElement(); // w:hyphenationZone

    stream.writeStartElement("w:characterSpacingControl");
    stream.writeAttribute("w:val", "doNotCompress");
    stream.writeEndElement(); // w:characterSpacingControl

    stream.writeStartElement("w:compat");

    stream.writeStartElement("w:useFELayout");
    stream.writeEndElement(); // w:useFELayout
    stream.writeEndElement(); // w:compat

    stream.writeStartElement("w:rsids");

    stream.writeStartElement("w:rsidRoot");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsidRoot

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "00B11C5D");
    stream.writeEndElement(); // w:rsid
    stream.writeEndElement(); // w:rsids

    stream.writeStartElement("m:mathPr");

    stream.writeStartElement("m:mathFont");
    stream.writeAttribute("m:val", "Cambria Math");
    stream.writeEndElement(); // m:mathFont

    stream.writeStartElement("m:brkBin");
    stream.writeAttribute("m:val", "before");
    stream.writeEndElement(); // m:brkBin

    stream.writeStartElement("m:brkBinSub");
    stream.writeAttribute("m:val", "--");
    stream.writeEndElement(); // m:brkBinSub

    stream.writeStartElement("m:smallFrac");
    stream.writeAttribute("m:val", "off");
    stream.writeEndElement(); // m:smallFrac

    stream.writeStartElement("m:dispDef");
    stream.writeEndElement(); // m:dispDef

    stream.writeStartElement("m:lMargin");
    stream.writeAttribute("m:val", "0");
    stream.writeEndElement(); // m:lMargin

    stream.writeStartElement("m:rMargin");
    stream.writeAttribute("m:val", "0");
    stream.writeEndElement(); // m:rMargin

    stream.writeStartElement("m:defJc");
    stream.writeAttribute("m:val", "centerGroup");
    stream.writeEndElement(); // m:defJc

    stream.writeStartElement("m:wrapIndent");
    stream.writeAttribute("m:val", "1440");
    stream.writeEndElement(); // m:wrapIndent

    stream.writeStartElement("m:intLim");
    stream.writeAttribute("m:val", "subSup");
    stream.writeEndElement(); // m:intLim

    stream.writeStartElement("m:naryLim");
    stream.writeAttribute("m:val", "undOvr");
    stream.writeEndElement(); // m:naryLim
    stream.writeEndElement(); // m:mathPr

    stream.writeStartElement("w:themeFontLang");
    stream.writeAttribute("w:val", "pt-BR");
    stream.writeEndElement(); // w:themeFontLang

    stream.writeStartElement("w:clrSchemeMapping");
    stream.writeAttribute("w:bg1", "light1");
    stream.writeAttribute("w:t1", "dark1");
    stream.writeAttribute("w:bg2", "light2");
    stream.writeAttribute("w:t2", "dark2");
    stream.writeAttribute("w:accent1", "accent1");
    stream.writeAttribute("w:accent2", "accent2");
    stream.writeAttribute("w:accent3", "accent3");
    stream.writeAttribute("w:accent4", "accent4");
    stream.writeAttribute("w:accent5", "accent5");
    stream.writeAttribute("w:accent6", "accent6");
    stream.writeAttribute("w:hyperlink", "hyperlink");
    stream.writeAttribute("w:followedHyperlink", "followedHyperlink");
    stream.writeEndElement(); // w:clrSchemeMapping

    stream.writeStartElement("w:shapeDefaults");

    stream.writeStartElement("o:shapedefaults");
    stream.writeAttribute("v:ext", "edit");
    stream.writeAttribute("spidmax", "2050");
    stream.writeEndElement(); // o:shapedefaults

    stream.writeStartElement("o:shapelayout");
    stream.writeAttribute("v:ext", "edit");

    stream.writeStartElement("o:idmap");
    stream.writeAttribute("v:ext", "edit");
    stream.writeAttribute("data", "1");
    stream.writeEndElement(); // o:idmap
    stream.writeEndElement(); // o:shapelayout
    stream.writeEndElement(); // w:shapeDefaults

    stream.writeStartElement("w:decimalSymbol");
    stream.writeAttribute("w:val", ",");
    stream.writeEndElement(); // w:decimalSymbol

    stream.writeStartElement("w:listSeparator");
    stream.writeAttribute("w:val", ";");
    stream.writeEndElement(); // w:listSeparator
    stream.writeEndElement(); // w:settings

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXStylesXml()
{
    QFile file("modelos/DOCX/word/styles.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:styles");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");

    stream.writeStartElement("w:docDefaults");

    stream.writeStartElement("w:rPrDefault");

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Liberation Serif");
    stream.writeAttribute("w:eastAsia", "SimSun");
    stream.writeAttribute("w:hAnsi", "Liberation Serif");
    stream.writeAttribute("w:cs", "Lucida Sans");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "24");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "24");
    stream.writeEndElement(); // w:szCs

    stream.writeStartElement("w:lang");
    stream.writeAttribute("w:val", "pt-BR");
    stream.writeAttribute("w:eastAsia", "zh-CN");
    stream.writeAttribute("w:bidi", "hi-IN");
    stream.writeEndElement(); // w:lang
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:rPrDefault

    stream.writeStartElement("w:pPrDefault");
    stream.writeEndElement(); // w:pPrDefault
    stream.writeEndElement(); // w:docDefaults

    stream.writeStartElement("w:latentStyles");
    stream.writeAttribute("w:defLockedState", "0");
    stream.writeAttribute("w:defUIPriority", "99");
    stream.writeAttribute("w:defSemiHidden", "1");
    stream.writeAttribute("w:defUnhideWhenUsed", "1");
    stream.writeAttribute("w:defQFormat", "0");
    stream.writeAttribute("w:count", "267");

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Normal");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "0");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 2");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 3");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 4");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 5");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 6");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 7");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 8");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "heading 9");
    stream.writeAttribute("w:uiPriority", "9");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 1");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 2");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 3");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 4");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 5");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 6");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 7");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 8");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "toc 9");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "caption");
    stream.writeAttribute("w:uiPriority", "35");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Title");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "10");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Default Paragraph Font");
    stream.writeAttribute("w:uiPriority", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Subtitle");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "11");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Strong");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "22");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Emphasis");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "20");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Table Grid");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "59");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Placeholder Text");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "No Spacing");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "1");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Revision");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "List Paragraph");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "34");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Quote");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "29");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Intense Quote");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "30");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 1");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 2");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 3");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 4");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 5");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Shading Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "60");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light List Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "61");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Light Grid Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "62");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 1 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "63");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Shading 2 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "64");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 1 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "65");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium List 2 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "66");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 1 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "67");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 2 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "68");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Medium Grid 3 Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "69");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Dark List Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "70");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Shading Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "71");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful List Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "72");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Colorful Grid Accent 6");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "73");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Subtle Emphasis");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "19");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Intense Emphasis");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "21");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Subtle Reference");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "31");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Intense Reference");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "32");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Book Title");
    stream.writeAttribute("w:semiHidden", "0");
    stream.writeAttribute("w:uiPriority", "33");
    stream.writeAttribute("w:unhideWhenUsed", "0");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "Bibliography");
    stream.writeAttribute("w:uiPriority", "37");
    stream.writeEndElement(); // w:lsdException

    stream.writeStartElement("w:lsdException");
    stream.writeAttribute("w:name", "TOC Heading");
    stream.writeAttribute("w:uiPriority", "39");
    stream.writeAttribute("w:qFormat", "1");
    stream.writeEndElement(); // w:lsdException
    stream.writeEndElement(); // w:latentStyles

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:default", "1");
    stream.writeAttribute("w:styleId", "Normal");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "character");
    stream.writeAttribute("w:default", "1");
    stream.writeAttribute("w:styleId", "Fontepargpadro");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Default Paragraph Font");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:uiPriority");
    stream.writeAttribute("w:val", "1");
    stream.writeEndElement(); // w:uiPriority

    stream.writeStartElement("w:semiHidden");
    stream.writeEndElement(); // w:semiHidden

    stream.writeStartElement("w:unhideWhenUsed");
    stream.writeEndElement(); // w:unhideWhenUsed
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "table");
    stream.writeAttribute("w:default", "1");
    stream.writeAttribute("w:styleId", "Tabelanormal");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Normal Table");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:uiPriority");
    stream.writeAttribute("w:val", "99");
    stream.writeEndElement(); // w:uiPriority

    stream.writeStartElement("w:semiHidden");
    stream.writeEndElement(); // w:semiHidden

    stream.writeStartElement("w:unhideWhenUsed");
    stream.writeEndElement(); // w:unhideWhenUsed

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:tblPr");

    stream.writeStartElement("w:tblInd");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:tblInd

    stream.writeStartElement("w:tblCellMar");

    stream.writeStartElement("w:top");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:top

    stream.writeStartElement("w:left");
    stream.writeAttribute("w:w", "108");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:left

    stream.writeStartElement("w:bottom");
    stream.writeAttribute("w:w", "0");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:bottom

    stream.writeStartElement("w:right");
    stream.writeAttribute("w:w", "108");
    stream.writeAttribute("w:type", "dxa");
    stream.writeEndElement(); // w:right
    stream.writeEndElement(); // w:tblCellMar
    stream.writeEndElement(); // w:tblPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "numbering");
    stream.writeAttribute("w:default", "1");
    stream.writeAttribute("w:styleId", "Semlista");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "No List");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:uiPriority");
    stream.writeAttribute("w:val", "99");
    stream.writeEndElement(); // w:uiPriority

    stream.writeStartElement("w:semiHidden");
    stream.writeEndElement(); // w:semiHidden

    stream.writeStartElement("w:unhideWhenUsed");
    stream.writeEndElement(); // w:unhideWhenUsed
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "character");
    stream.writeAttribute("w:customStyle", "1");
    stream.writeAttribute("w:styleId", "LinkdaInternet");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Link da Internet");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:color");
    stream.writeAttribute("w:val", "000080");
    stream.writeEndElement(); // w:color

    stream.writeStartElement("w:u");
    stream.writeAttribute("w:val", "single");
    stream.writeEndElement(); // w:u
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:styleId", "Ttulo");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Title");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:next");
    stream.writeAttribute("w:val", "Corpodetexto");
    stream.writeEndElement(); // w:next

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:keepNext");
    stream.writeEndElement(); // w:keepNext

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:before", "240");
    stream.writeAttribute("w:after", "120");
    stream.writeEndElement(); // w:spacing
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Liberation Sans");
    stream.writeAttribute("w:eastAsia", "Microsoft YaHei");
    stream.writeAttribute("w:hAnsi", "Liberation Sans");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "28");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "28");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:styleId", "Corpodetexto");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Body Text");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:after", "140");
    stream.writeAttribute("w:line", "288");
    stream.writeAttribute("w:lineRule", "auto");
    stream.writeEndElement(); // w:spacing
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:styleId", "Lista");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "List");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Corpodetexto");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:customStyle", "1");
    stream.writeAttribute("w:styleId", "Caption");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Caption");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:suppressLineNumbers");
    stream.writeEndElement(); // w:suppressLineNumbers

    stream.writeStartElement("w:spacing");
    stream.writeAttribute("w:before", "120");
    stream.writeAttribute("w:after", "120");
    stream.writeEndElement(); // w:spacing
    stream.writeEndElement(); // w:pPr

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:i");
    stream.writeEndElement(); // w:i

    stream.writeStartElement("w:iCs");
    stream.writeEndElement(); // w:iCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:customStyle", "1");
    stream.writeAttribute("w:styleId", "ndice");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Índice");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:suppressLineNumbers");
    stream.writeEndElement(); // w:suppressLineNumbers
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:customStyle", "1");
    stream.writeAttribute("w:styleId", "Contedodatabela");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Conteúdo da tabela");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:qFormat");
    stream.writeEndElement(); // w:qFormat

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "005D3254");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:pPr");

    stream.writeStartElement("w:suppressLineNumbers");
    stream.writeEndElement(); // w:suppressLineNumbers
    stream.writeEndElement(); // w:pPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "paragraph");
    stream.writeAttribute("w:styleId", "Textodebalo");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Balloon Text");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Normal");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:link");
    stream.writeAttribute("w:val", "TextodebaloChar");
    stream.writeEndElement(); // w:link

    stream.writeStartElement("w:uiPriority");
    stream.writeAttribute("w:val", "99");
    stream.writeEndElement(); // w:uiPriority

    stream.writeStartElement("w:semiHidden");
    stream.writeEndElement(); // w:semiHidden

    stream.writeStartElement("w:unhideWhenUsed");
    stream.writeEndElement(); // w:unhideWhenUsed

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "00B11C5D");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Tahoma");
    stream.writeAttribute("w:hAnsi", "Tahoma");
    stream.writeAttribute("w:cs", "Mangal");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "16");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "14");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:style

    stream.writeStartElement("w:style");
    stream.writeAttribute("w:type", "character");
    stream.writeAttribute("w:customStyle", "1");
    stream.writeAttribute("w:styleId", "TextodebaloChar");

    stream.writeStartElement("w:name");
    stream.writeAttribute("w:val", "Texto de balão Char");
    stream.writeEndElement(); // w:name

    stream.writeStartElement("w:basedOn");
    stream.writeAttribute("w:val", "Fontepargpadro");
    stream.writeEndElement(); // w:basedOn

    stream.writeStartElement("w:link");
    stream.writeAttribute("w:val", "Textodebalo");
    stream.writeEndElement(); // w:link

    stream.writeStartElement("w:uiPriority");
    stream.writeAttribute("w:val", "99");
    stream.writeEndElement(); // w:uiPriority

    stream.writeStartElement("w:semiHidden");
    stream.writeEndElement(); // w:semiHidden

    stream.writeStartElement("w:rsid");
    stream.writeAttribute("w:val", "00B11C5D");
    stream.writeEndElement(); // w:rsid

    stream.writeStartElement("w:rPr");

    stream.writeStartElement("w:rFonts");
    stream.writeAttribute("w:ascii", "Tahoma");
    stream.writeAttribute("w:hAnsi", "Tahoma");
    stream.writeAttribute("w:cs", "Mangal");
    stream.writeEndElement(); // w:rFonts

    stream.writeStartElement("w:sz");
    stream.writeAttribute("w:val", "16");
    stream.writeEndElement(); // w:sz

    stream.writeStartElement("w:szCs");
    stream.writeAttribute("w:val", "14");
    stream.writeEndElement(); // w:szCs
    stream.writeEndElement(); // w:rPr
    stream.writeEndElement(); // w:style
    stream.writeEndElement(); // w:styles

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXWebSettingsXml()
{
    QFile file("modelos/DOCX/word/webSettings.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("w:webSettings");
    stream.writeAttribute("xmlns:r", "http://schemas.openxmlformats.org/officeDocument/2006/relationships");
    stream.writeAttribute("xmlns:w", "http://schemas.openxmlformats.org/wordprocessingml/2006/main");
    stream.writeEndElement(); // w:webSettings

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXTheme1Xml()
{
    QFile file("modelos/DOCX/word/theme/theme1.xml");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("a:theme");
    stream.writeAttribute("xmlns:a", "http://schemas.openxmlformats.org/drawingml/2006/main");
    stream.writeAttribute("name", "Tema do Office");

    stream.writeStartElement("a:themeElements");

    stream.writeStartElement("a:clrScheme");
    stream.writeAttribute("name", "Escritório");

    stream.writeStartElement("a:dk1");

    stream.writeStartElement("a:sysClr");
    stream.writeAttribute("val", "windowText");
    stream.writeAttribute("lastClr", "000000");
    stream.writeEndElement(); // a:sysClr
    stream.writeEndElement(); // a:dk1

    stream.writeStartElement("a:lt1");

    stream.writeStartElement("a:sysClr");
    stream.writeAttribute("val", "window");
    stream.writeAttribute("lastClr", "FFFFFF");
    stream.writeEndElement(); // a:sysClr
    stream.writeEndElement(); // a:lt1

    stream.writeStartElement("a:dk2");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "1F497D");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:dk2

    stream.writeStartElement("a:lt2");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "EEECE1");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:lt2

    stream.writeStartElement("a:accent1");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "4F81BD");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent1

    stream.writeStartElement("a:accent2");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "C0504D");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent2

    stream.writeStartElement("a:accent3");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "9BBB59");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent3

    stream.writeStartElement("a:accent4");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "8064A2");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent4

    stream.writeStartElement("a:accent5");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "4BACC6");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent5

    stream.writeStartElement("a:accent6");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "F79646");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:accent6

    stream.writeStartElement("a:hlink");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "0000FF");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:hlink

    stream.writeStartElement("a:folHlink");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "800080");
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:folHlink
    stream.writeEndElement(); // a:clrScheme

    stream.writeStartElement("a:fontScheme");
    stream.writeAttribute("name", "Escritório");

    stream.writeStartElement("a:majorFont");

    stream.writeStartElement("a:latin");
    stream.writeAttribute("typeface", "Cambria");
    stream.writeEndElement(); // a:latin

    stream.writeStartElement("a:ea");
    stream.writeAttribute("typeface", "");
    stream.writeEndElement(); // a:ea

    stream.writeStartElement("a:cs");
    stream.writeAttribute("typeface", "");
    stream.writeEndElement(); // a:cs

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Jpan");
    stream.writeAttribute("typeface", "ＭＳ ゴシック");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hang");
    stream.writeAttribute("typeface", "맑은 고딕");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hans");
    stream.writeAttribute("typeface", "宋体");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hant");
    stream.writeAttribute("typeface", "新細明體");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Arab");
    stream.writeAttribute("typeface", "Times New Roman");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hebr");
    stream.writeAttribute("typeface", "Times New Roman");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Thai");
    stream.writeAttribute("typeface", "Angsana New");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Ethi");
    stream.writeAttribute("typeface", "Nyala");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Beng");
    stream.writeAttribute("typeface", "Vrinda");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Gujr");
    stream.writeAttribute("typeface", "Shruti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Khmr");
    stream.writeAttribute("typeface", "MoolBoran");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Knda");
    stream.writeAttribute("typeface", "Tunga");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Guru");
    stream.writeAttribute("typeface", "Raavi");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Cans");
    stream.writeAttribute("typeface", "Euphemia");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Cher");
    stream.writeAttribute("typeface", "Plantagenet Cherokee");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Yiii");
    stream.writeAttribute("typeface", "Microsoft Yi Baiti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Tibt");
    stream.writeAttribute("typeface", "Microsoft Himalaya");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Thaa");
    stream.writeAttribute("typeface", "MV Boli");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Deva");
    stream.writeAttribute("typeface", "Mangal");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Telu");
    stream.writeAttribute("typeface", "Gautami");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Taml");
    stream.writeAttribute("typeface", "Latha");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Syrc");
    stream.writeAttribute("typeface", "Estrangelo Edessa");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Orya");
    stream.writeAttribute("typeface", "Kalinga");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Mlym");
    stream.writeAttribute("typeface", "Kartika");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Laoo");
    stream.writeAttribute("typeface", "DokChampa");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Sinh");
    stream.writeAttribute("typeface", "Iskoola Pota");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Mong");
    stream.writeAttribute("typeface", "Mongolian Baiti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Viet");
    stream.writeAttribute("typeface", "Times New Roman");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Uigh");
    stream.writeAttribute("typeface", "Microsoft Uighur");
    stream.writeEndElement(); // a:font
    stream.writeEndElement(); // a:majorFont

    stream.writeStartElement("a:minorFont");

    stream.writeStartElement("a:latin");
    stream.writeAttribute("typeface", "Calibri");
    stream.writeEndElement(); // a:latin

    stream.writeStartElement("a:ea");
    stream.writeAttribute("typeface", "");
    stream.writeEndElement(); // a:ea

    stream.writeStartElement("a:cs");
    stream.writeAttribute("typeface", "");
    stream.writeEndElement(); // a:cs

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Jpan");
    stream.writeAttribute("typeface", "ＭＳ 明朝");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hang");
    stream.writeAttribute("typeface", "맑은 고딕");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hans");
    stream.writeAttribute("typeface", "宋体");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hant");
    stream.writeAttribute("typeface", "新細明體");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Arab");
    stream.writeAttribute("typeface", "Arial");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Hebr");
    stream.writeAttribute("typeface", "Arial");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Thai");
    stream.writeAttribute("typeface", "Cordia New");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Ethi");
    stream.writeAttribute("typeface", "Nyala");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Beng");
    stream.writeAttribute("typeface", "Vrinda");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Gujr");
    stream.writeAttribute("typeface", "Shruti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Khmr");
    stream.writeAttribute("typeface", "DaunPenh");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Knda");
    stream.writeAttribute("typeface", "Tunga");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Guru");
    stream.writeAttribute("typeface", "Raavi");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Cans");
    stream.writeAttribute("typeface", "Euphemia");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Cher");
    stream.writeAttribute("typeface", "Plantagenet Cherokee");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Yiii");
    stream.writeAttribute("typeface", "Microsoft Yi Baiti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Tibt");
    stream.writeAttribute("typeface", "Microsoft Himalaya");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Thaa");
    stream.writeAttribute("typeface", "MV Boli");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Deva");
    stream.writeAttribute("typeface", "Mangal");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Telu");
    stream.writeAttribute("typeface", "Gautami");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Taml");
    stream.writeAttribute("typeface", "Latha");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Syrc");
    stream.writeAttribute("typeface", "Estrangelo Edessa");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Orya");
    stream.writeAttribute("typeface", "Kalinga");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Mlym");
    stream.writeAttribute("typeface", "Kartika");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Laoo");
    stream.writeAttribute("typeface", "DokChampa");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Sinh");
    stream.writeAttribute("typeface", "Iskoola Pota");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Mong");
    stream.writeAttribute("typeface", "Mongolian Baiti");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Viet");
    stream.writeAttribute("typeface", "Arial");
    stream.writeEndElement(); // a:font

    stream.writeStartElement("a:font");
    stream.writeAttribute("script", "Uigh");
    stream.writeAttribute("typeface", "Microsoft Uighur");
    stream.writeEndElement(); // a:font
    stream.writeEndElement(); // a:minorFont
    stream.writeEndElement(); // a:fontScheme

    stream.writeStartElement("a:fmtScheme");
    stream.writeAttribute("name", "Escritório");

    stream.writeStartElement("a:fillStyleLst");

    stream.writeStartElement("a:solidFill");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:solidFill

    stream.writeStartElement("a:gradFill");
    stream.writeAttribute("rotWithShape", "1");

    stream.writeStartElement("a:gsLst");

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "0");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "50000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "300000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "35000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "37000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "300000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "100000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "15000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "350000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs
    stream.writeEndElement(); // a:gsLst

    stream.writeStartElement("a:lin");
    stream.writeAttribute("ang", "16200000");
    stream.writeAttribute("scaled", "1");
    stream.writeEndElement(); // a:lin
    stream.writeEndElement(); // a:gradFill

    stream.writeStartElement("a:gradFill");
    stream.writeAttribute("rotWithShape", "1");

    stream.writeStartElement("a:gsLst");

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "0");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "51000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "130000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "80000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "93000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "130000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "100000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "94000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "135000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs
    stream.writeEndElement(); // a:gsLst

    stream.writeStartElement("a:lin");
    stream.writeAttribute("ang", "16200000");
    stream.writeAttribute("scaled", "0");
    stream.writeEndElement(); // a:lin
    stream.writeEndElement(); // a:gradFill
    stream.writeEndElement(); // a:fillStyleLst

    stream.writeStartElement("a:lnStyleLst");

    stream.writeStartElement("a:ln");
    stream.writeAttribute("w", "9525");
    stream.writeAttribute("cap", "flat");
    stream.writeAttribute("cmpd", "sng");
    stream.writeAttribute("algn", "ctr");

    stream.writeStartElement("a:solidFill");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "95000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "105000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:solidFill

    stream.writeStartElement("a:prstDash");
    stream.writeAttribute("val", "solid");
    stream.writeEndElement(); // a:prstDash
    stream.writeEndElement(); // a:ln

    stream.writeStartElement("a:ln");
    stream.writeAttribute("w", "25400");
    stream.writeAttribute("cap", "flat");
    stream.writeAttribute("cmpd", "sng");
    stream.writeAttribute("algn", "ctr");

    stream.writeStartElement("a:solidFill");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:solidFill

    stream.writeStartElement("a:prstDash");
    stream.writeAttribute("val", "solid");
    stream.writeEndElement(); // a:prstDash
    stream.writeEndElement(); // a:ln

    stream.writeStartElement("a:ln");
    stream.writeAttribute("w", "38100");
    stream.writeAttribute("cap", "flat");
    stream.writeAttribute("cmpd", "sng");
    stream.writeAttribute("algn", "ctr");

    stream.writeStartElement("a:solidFill");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:solidFill

    stream.writeStartElement("a:prstDash");
    stream.writeAttribute("val", "solid");
    stream.writeEndElement(); // a:prstDash
    stream.writeEndElement(); // a:ln
    stream.writeEndElement(); // a:lnStyleLst

    stream.writeStartElement("a:effectStyleLst");

    stream.writeStartElement("a:effectStyle");

    stream.writeStartElement("a:effectLst");

    stream.writeStartElement("a:outerShdw");
    stream.writeAttribute("blurRad", "40000");
    stream.writeAttribute("dist", "20000");
    stream.writeAttribute("dir", "5400000");
    stream.writeAttribute("rotWithShape", "0");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "000000");

    stream.writeStartElement("a:alpha");
    stream.writeAttribute("val", "38000");
    stream.writeEndElement(); // a:alpha
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:outerShdw
    stream.writeEndElement(); // a:effectLst
    stream.writeEndElement(); // a:effectStyle

    stream.writeStartElement("a:effectStyle");

    stream.writeStartElement("a:effectLst");

    stream.writeStartElement("a:outerShdw");
    stream.writeAttribute("blurRad", "40000");
    stream.writeAttribute("dist", "23000");
    stream.writeAttribute("dir", "5400000");
    stream.writeAttribute("rotWithShape", "0");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "000000");

    stream.writeStartElement("a:alpha");
    stream.writeAttribute("val", "35000");
    stream.writeEndElement(); // a:alpha
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:outerShdw
    stream.writeEndElement(); // a:effectLst
    stream.writeEndElement(); // a:effectStyle

    stream.writeStartElement("a:effectStyle");

    stream.writeStartElement("a:effectLst");

    stream.writeStartElement("a:outerShdw");
    stream.writeAttribute("blurRad", "40000");
    stream.writeAttribute("dist", "23000");
    stream.writeAttribute("dir", "5400000");
    stream.writeAttribute("rotWithShape", "0");

    stream.writeStartElement("a:srgbClr");
    stream.writeAttribute("val", "000000");

    stream.writeStartElement("a:alpha");
    stream.writeAttribute("val", "35000");
    stream.writeEndElement(); // a:alpha
    stream.writeEndElement(); // a:srgbClr
    stream.writeEndElement(); // a:outerShdw
    stream.writeEndElement(); // a:effectLst

    stream.writeStartElement("a:scene3d");

    stream.writeStartElement("a:camera");
    stream.writeAttribute("prst", "orthographicFront");

    stream.writeStartElement("a:rot");
    stream.writeAttribute("lat", "0");
    stream.writeAttribute("lon", "0");
    stream.writeAttribute("rev", "0");
    stream.writeEndElement(); // a:rot
    stream.writeEndElement(); // a:camera

    stream.writeStartElement("a:lightRig");
    stream.writeAttribute("rig", "threePt");
    stream.writeAttribute("dir", "t");

    stream.writeStartElement("a:rot");
    stream.writeAttribute("lat", "0");
    stream.writeAttribute("lon", "0");
    stream.writeAttribute("rev", "1200000");
    stream.writeEndElement(); // a:rot
    stream.writeEndElement(); // a:lightRig
    stream.writeEndElement(); // a:scene3d

    stream.writeStartElement("a:sp3d");

    stream.writeStartElement("a:bevelT");
    stream.writeAttribute("w", "63500");
    stream.writeAttribute("h", "25400");
    stream.writeEndElement(); // a:bevelT
    stream.writeEndElement(); // a:sp3d
    stream.writeEndElement(); // a:effectStyle
    stream.writeEndElement(); // a:effectStyleLst

    stream.writeStartElement("a:bgFillStyleLst");

    stream.writeStartElement("a:solidFill");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:solidFill

    stream.writeStartElement("a:gradFill");
    stream.writeAttribute("rotWithShape", "1");

    stream.writeStartElement("a:gsLst");

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "0");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "40000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "350000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "40000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "45000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "99000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "350000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "100000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "20000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "255000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs
    stream.writeEndElement(); // a:gsLst

    stream.writeStartElement("a:path");
    stream.writeAttribute("path", "circle");

    stream.writeStartElement("a:fillToRect");
    stream.writeAttribute("l", "50000");
    stream.writeAttribute("t", "-80000");
    stream.writeAttribute("r", "50000");
    stream.writeAttribute("b", "180000");
    stream.writeEndElement(); // a:fillToRect
    stream.writeEndElement(); // a:path
    stream.writeEndElement(); // a:gradFill

    stream.writeStartElement("a:gradFill");
    stream.writeAttribute("rotWithShape", "1");

    stream.writeStartElement("a:gsLst");

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "0");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:tint");
    stream.writeAttribute("val", "80000");
    stream.writeEndElement(); // a:tint

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "300000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs

    stream.writeStartElement("a:gs");
    stream.writeAttribute("pos", "100000");

    stream.writeStartElement("a:schemeClr");
    stream.writeAttribute("val", "phClr");

    stream.writeStartElement("a:shade");
    stream.writeAttribute("val", "30000");
    stream.writeEndElement(); // a:shade

    stream.writeStartElement("a:satMod");
    stream.writeAttribute("val", "200000");
    stream.writeEndElement(); // a:satMod
    stream.writeEndElement(); // a:schemeClr
    stream.writeEndElement(); // a:gs
    stream.writeEndElement(); // a:gsLst

    stream.writeStartElement("a:path");
    stream.writeAttribute("path", "circle");

    stream.writeStartElement("a:fillToRect");
    stream.writeAttribute("l", "50000");
    stream.writeAttribute("t", "50000");
    stream.writeAttribute("r", "50000");
    stream.writeAttribute("b", "50000");
    stream.writeEndElement(); // a:fillToRect
    stream.writeEndElement(); // a:path
    stream.writeEndElement(); // a:gradFill
    stream.writeEndElement(); // a:bgFillStyleLst
    stream.writeEndElement(); // a:fmtScheme
    stream.writeEndElement(); // a:themeElements

    stream.writeStartElement("a:objectDefaults");
    stream.writeEndElement(); // a:objectDefaults

    stream.writeStartElement("a:extraClrSchemeLst");
    stream.writeEndElement(); // a:extraClrSchemeLst
    stream.writeEndElement(); // a:theme

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXDocumentXmlRels()
{
    QFile file("modelos/DOCX/word/_rels/document.xml.rels");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("Relationships");
    stream.writeAttribute("xmlns", "http://schemas.openxmlformats.org/package/2006/relationships");

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId1");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles");
    stream.writeAttribute("Target", "styles.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId2");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings");
    stream.writeAttribute("Target", "settings.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId3");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/webSettings");
    stream.writeAttribute("Target", "webSettings.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId4");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/fontTable");
    stream.writeAttribute("Target", "fontTable.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId5");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme");
    stream.writeAttribute("Target", "theme/theme1.xml");
    stream.writeEndElement(); // Relationship

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

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId6");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/image");
    stream.writeAttribute("Target", QString("media/image1.%1").arg(extensaoImage));
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId7");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink");
    stream.writeAttribute("Target", QString("mailto:%1").arg(defaultEquipeEmail));
    stream.writeAttribute("TargetMode", "External");
    stream.writeEndElement(); // Relationship

    stream.writeEndElement(); // Relationships

    stream.writeEndDocument();

    file.close();
}

void MainWindow::createDOCXRels()
{
    QFile file("modelos/DOCX/_rels/.rels");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(false);

    stream.writeStartDocument();

    stream.writeStartElement("Relationships");
    stream.writeAttribute("xmlns", "http://schemas.openxmlformats.org/package/2006/relationships");

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId3");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties");
    stream.writeAttribute("Target", "docProps/app.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId2");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties");
    stream.writeAttribute("Target", "docProps/core.xml");
    stream.writeEndElement(); // Relationship

    stream.writeStartElement("Relationship");
    stream.writeAttribute("Id", "rId1");
    stream.writeAttribute("Type", "http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument");
    stream.writeAttribute("Target", "word/document.xml");
    stream.writeEndElement(); // Relationship
    stream.writeEndElement(); // Relationships

    stream.writeEndDocument();

    file.close();
}
