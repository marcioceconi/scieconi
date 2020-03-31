#include "coderxml.h"
#include "ui_coderxml.h"

#include <QMessageBox>

CoderXML::CoderXML(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoderXML)
{
    ui->setupUi(this);
}

CoderXML::~CoderXML()
{
    delete ui;
}

void CoderXML::on_pushButtonConverter_clicked()
{
    QString entrada = ui->entradaPlainTextEdit->toPlainText();

    QStringList entradaLinhas = entrada.split("\n");
    QString saida;
    saida.clear();

    saida.append(QString("stream.setAutoFormatting(false);\n"));
    saida.append(QString("\nstream.writeStartDocument();\n"));

    int countOpenTags = 0, countCloseTags = 0, countSlashes = 0, countAspas = 0;
    bool validSlash = true;
    for (int i=0; i<entradaLinhas.count(); i++) {
        countOpenTags = 0;
        countCloseTags = 0;
        countSlashes = 0;
        countAspas = 0;
        validSlash = true;
        QString parcial = entradaLinhas[i];
        for (int k=0; k<parcial.count(); k++) {
            if (parcial[k] == "<") countOpenTags++;
            if (parcial[k] == ">") countCloseTags++;
            if (parcial[k] == "\"") countAspas++;
        }
        if (countAspas > 1) {
            for (int k=0; k<parcial.count(); k++) {
                if (parcial[k] == "\"") {
                    if (validSlash == true) {
                        validSlash = false;
                    } else {
                        validSlash = true;
                    }
                }
                if (parcial[k] == "/" && validSlash == true) {
                    countSlashes++;
                }
            }
        } else {
            for (int k=0; k<parcial.count(); k++) {
                if (parcial[k] == "/") countSlashes++;
            }
        }
        // Corrige countSlashes
        if (countSlashes > 1) countSlashes = 1;
        if (countOpenTags==0 && countCloseTags==0 /*&& countSlashes==0*/) { // SOMENTE CHAR [CASE 7]
            saida.append(QString("stream.writeCharacters(\"%1\");\n").arg(parcial));
        } else if (countOpenTags==1 && countCloseTags==1 && countSlashes==1 && parcial[0]!="<" && parcial[parcial.count()-1]==">" && parcial[parcial.count()-2]!="/") { // CHARACTER COM UMA ÚNICA TAG DE FECHAMENTO [CASE 6]
            int posOpenTag = 0;
            for (int j=0; j<parcial.count(); j++) {
                if (parcial[j] == "<") posOpenTag = j;
            }
            QString parte1, parte2;
            parte1.clear();
            parte2.clear();
            for (int j=0; j<posOpenTag; j++) {
                parte1.append(parcial[j]);
            }
            for (int j=posOpenTag+2; j<parcial.count()-1; j++) {
                parte2.append(parcial[j]);
            }
            saida.append(QString("stream.writeCharacters(\"%1\")\n").arg(parte1));
            saida.append(QString("stream.writeEndElement(); // %1\n").arg(parte2));
        } else if (countOpenTags==1 && countCloseTags==1 && countSlashes==1 && parcial[0]=="<" && parcial[parcial.count()-1]==">" && parcial[1]=="/") { // SOMENTE TAG DE FECHAMENTO [CASE 2]
            QString parte1;
            parte1.clear();
            for (int j=2; j<parcial.count()-1; j++) {
                parte1.append(parcial[j]);
            }
            saida.append(QString("stream.writeEndElement(); // %1\n").arg(parte1));
        } else if (countOpenTags==1 && countCloseTags==1 && countSlashes==0 && parcial[0]=="<" && parcial[parcial.count()-1]==">" && parcial[parcial.count()-2]!="/") { // SOMENTE TAG DE ABERTURA, PODENDO TER ARGUMENTOS [CASE 1]
            QString parcialSemTags;
            parcialSemTags.clear();
            for (int j=1; j<parcial.count()-1; j++) {
                parcialSemTags.append(parcial[j]);
            }
            QStringList parcialSemEspacos;
            parcialSemEspacos.clear();
            parcialSemEspacos = separaEspacos(parcialSemTags);
            //parcialSemEspacos = parcialSemTags.split(" ");
            saida.append(QString("\nstream.writeStartElement(\"%1\");\n").arg(parcialSemEspacos[0]));
            if (parcialSemEspacos.count() > 1) {
                QString atributo;
                QStringList atributoColunas;
                for (int j=1; j<parcialSemEspacos.count(); j++) {
                    atributo = parcialSemEspacos[j];
                    atributoColunas.clear();
                    atributoColunas = atributo.split("=");
                    saida.append(QString("stream.writeAttribute(\"%1\", %2);\n").arg(atributoColunas[0]).arg(atributoColunas[1]));
                }
            }
        } else if (countOpenTags==1 && countCloseTags==1 && countSlashes==1 && parcial[0]=="<" && parcial[1]!="/" && parcial[parcial.count()-1]==">" && parcial[parcial.count()-2]=="/") { // ABRE E FECHA TAG COM ARGUMENTOS E SEM CHAR [CASE 3]
            QString parcialSemTags;
            parcialSemTags.clear();
            for (int j=1; j<parcial.count()-2; j++) {
                parcialSemTags.append(parcial[j]);
            }
            QStringList parcialSemEspacos;
            parcialSemEspacos.clear();
            parcialSemEspacos = separaEspacos(parcialSemTags);
            //parcialSemEspacos = parcialSemTags.split(" ");
            saida.append(QString("\nstream.writeStartElement(\"%1\");\n").arg(parcialSemEspacos[0]));
            if (parcialSemEspacos.count() > 1) {
                QString atributo;
                QStringList atributoColunas;
                for (int j=1; j<parcialSemEspacos.count(); j++) {
                    atributo = parcialSemEspacos[j];
                    atributoColunas.clear();
                    atributoColunas = atributo.split("=");
                    saida.append(QString("stream.writeAttribute(\"%1\", %2);\n").arg(atributoColunas[0]).arg(atributoColunas[1]));
                }
            }
            saida.append(QString("stream.writeEndElement(); // %1\n").arg(parcialSemEspacos[0]));
        } else if (countOpenTags==1 && countCloseTags==1 /*&& countSlashes==0*/ && parcial[0]=="<" && parcial[parcial.count()-1]!=">" && parcial[parcial.count()-2]!="/") { // SOMENTE ABRE TAG COM CHAR AO FINAL [CASE 5]
            int posCloseTag = 0;
            for (int j=0; j<parcial.count(); j++) {
                if (parcial[j]==">") posCloseTag = j;
            }
            QString parcialAteFechaTag, parcialAposFechaTag;
            parcialAteFechaTag.clear();
            parcialAposFechaTag.clear();
            for (int j=1; j<posCloseTag; j++) {
                parcialAteFechaTag.append(parcial[j]);
            }
            for (int j=posCloseTag+1; j<parcial.count(); j++) {
                parcialAposFechaTag.append(parcial[j]);
            }
            saida.append(QString("\nstream.writeStartElement(\"%1\");\n").arg(parcialAteFechaTag));
            saida.append(QString("stream.writeCharacters(\"%1\");\n").arg(parcialAposFechaTag));
        } else if (countOpenTags==2 && countCloseTags==2 && countSlashes==1 && parcial[0]=="<" && parcial[parcial.count()-1]==">") { // ABRE E FECHA TAG COM ARGUMENTOS E CHARACTERS [CASE 4]
            int posFirstOpenTag=0, posSecondOpenTag=0, posFirstCloseTag=0, posSecondCloseTag=0;
            posFirstOpenTag = 0;
            posSecondCloseTag = parcial.count()-1;
            for (int j=1; j<parcial.count(); j++) {
                if (parcial[j]=="<") posSecondOpenTag = j;
            }
            for (int j=1; j<parcial.count()-1; j++) {
                if (parcial[j]==">") posFirstCloseTag = j;
            }
            QString primeiraTag, segundaTag, charEntreTags;
            primeiraTag.clear();
            segundaTag.clear();
            charEntreTags.clear();
            for (int j=posFirstOpenTag+1; j<posFirstCloseTag; j++) {
                primeiraTag.append(parcial[j]);
            }
            for (int j=posSecondOpenTag+2; j<posSecondCloseTag; j++) {
                segundaTag.append(parcial[j]);
            }
            // Primeira Tag (Abertura e Argumentos)
            QString parcialSemTags;
            parcialSemTags = primeiraTag;
            QStringList parcialSemEspacos;
            parcialSemEspacos.clear();
            parcialSemEspacos = separaEspacos(parcialSemTags);
            //parcialSemEspacos = parcialSemTags.split(" ");
            saida.append(QString("\nstream.writeStartElement(\"%1\");\n").arg(parcialSemEspacos[0]));
            if (parcialSemEspacos.count() > 1) {
                QString atributo;
                QStringList atributoColunas;
                for (int j=1; j<parcialSemEspacos.count(); j++) {
                    atributo = parcialSemEspacos[j];
                    atributoColunas.clear();
                    atributoColunas = atributo.split("=");
                    saida.append(QString("stream.writeAttribute(\"%1\", %2);\n").arg(atributoColunas[0]).arg(atributoColunas[1]));
                }
            }
            // Character entre Tags
            if (posSecondOpenTag-posFirstCloseTag > 1) {
                for (int j=posFirstCloseTag+1; j<posSecondOpenTag; j++) {
                    charEntreTags.append(parcial[j]);
                }
                saida.append(QString("stream.writeCharacters(\"%1\");\n").arg(charEntreTags));
            }
            // Segunda Tag (Fechamento)
            saida.append(QString("stream.writeEndElement(); // %1\n").arg(segundaTag));
        }
    }

    saida.append(QString("\nstream.writeEndDocument();"));


   ui->saidaPlainTextEdit->setPlainText(saida);
}

void CoderXML::on_pushButtonLimpar_clicked()
{
    ui->entradaPlainTextEdit->clear();
    ui->saidaPlainTextEdit->clear();
}

QStringList CoderXML::separaEspacos(QString stringComEspacos)
{
    QStringList saidaList;
    saidaList.clear();

    QString copiaCorrigida;
    copiaCorrigida.clear();

    bool foundAbreAspas = false;
    bool foundFechaAspas = false;

    QList<int> listaPos;
    listaPos.clear();

    for (int i=0; i<stringComEspacos.count(); i++) {
        if (stringComEspacos[i]=="\"") {
            if (foundAbreAspas == false && foundFechaAspas == false) {
                foundAbreAspas = true;
                foundFechaAspas = false;
            } else if (foundAbreAspas == false && foundFechaAspas == true) {
                foundAbreAspas = true;
                foundFechaAspas = false;
            } else if (foundAbreAspas == true && foundFechaAspas == false) {
                foundAbreAspas = false;
                foundFechaAspas = true;
            }
        }
        if (foundAbreAspas == true && foundFechaAspas == false) {
            if (stringComEspacos[i] == " ") listaPos.append(i);
        }
    }

    copiaCorrigida = stringComEspacos;
    if (listaPos.count() > 0) {
        for (int i=0; i<listaPos.count(); i++) {
            copiaCorrigida.replace(listaPos[i], 1, "|");
        }
    }

    saidaList = copiaCorrigida.split(" ");
    for (int i=0; i<saidaList.count(); i++) {
        saidaList[i].replace("|", " ");
    }

    return saidaList;
}
