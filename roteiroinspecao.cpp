#include "roteiroinspecao.h"
#include "ui_roteiroinspecao.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

RoteiroInspecao::RoteiroInspecao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoteiroInspecao)
{
    ui->setupUi(this);

    vboxGroupRoteiro = new QVBoxLayout;
    vboxGroupRoteiro->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ui->groupBoxRoteiro->setLayout(vboxGroupRoteiro);

    listaItensGrupos.clear();
    listaLineEditPtr.clear();
}

RoteiroInspecao::~RoteiroInspecao()
{
    delete ui;
}

void RoteiroInspecao::createNovoGrupo()
{
    grupoLineEdit = new QLineEdit;
    grupoLineEdit->setStyleSheet("QLineEdit{border: 1px solid black; font-size: 11pt; font-weight: bold; background-color: rgb(82,240,0);}");
    grupoLineEdit->setPlaceholderText("Insira o nome do grupo ...");
    grupoLineEdit->setFixedSize(1105, 30);

    QPushButton *botaoExcluirGrupo = new QPushButton("Excluir Grupo");
    botaoExcluirGrupo->setIcon(QPixmap(":/imagens/delete.png"));
    botaoExcluirGrupo->setFixedSize(95, 30);

    QHBoxLayout *hboxGrupo = new QHBoxLayout;
    hboxGrupo->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    hboxGrupo->addWidget(grupoLineEdit);
    hboxGrupo->addWidget(botaoExcluirGrupo);

    vboxGroupRoteiro->addLayout(hboxGrupo);

    listaItensGrupos.append(QString("grupo"));
    listaLineEditPtr.append(grupoLineEdit);
    int currentIndex = listaItensGrupos.count()-1;

    connect(botaoExcluirGrupo, &QPushButton::clicked, this, [=]{
        QLayoutItem *item = nullptr;
        while ((item = hboxGrupo->takeAt(0)) != nullptr) {
            //delete item->widget();
            item->widget()->hide();
        }
        vboxGroupRoteiro->removeItem(hboxGrupo);
        listaItensGrupos[currentIndex] = QString("grupoDELETADO");
    });
}

void RoteiroInspecao::createNovoItem()
{
    irregLineEdit = new QLineEdit;
    irregLineEdit->setPlaceholderText("Insira a irregularidade ...");
    irregLineEdit->setFixedSize(600, 25);
    dispoLineEdit = new QLineEdit;
    dispoLineEdit->setPlaceholderText("Insira os dispositivos legais infringidos ...");
    dispoLineEdit->setFixedSize(500, 25);

    QPushButton *botaoExcluirItem = new QPushButton("Excluir Item");
    botaoExcluirItem->setIcon(QPixmap(":/imagens/delete.png"));
    botaoExcluirItem->setFixedSize(95, 25);

    QHBoxLayout *hboxItem = new QHBoxLayout;
    hboxItem->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    hboxItem->addWidget(irregLineEdit);
    hboxItem->addWidget(dispoLineEdit);
    hboxItem->addWidget(botaoExcluirItem);

    vboxGroupRoteiro->addLayout(hboxItem);

    listaItensGrupos.append("item");
    listaLineEditPtr.append(irregLineEdit);
    listaLineEditPtr.append(dispoLineEdit);
    int currentIndex = listaItensGrupos.count()-1;

    connect(botaoExcluirItem, &QPushButton::clicked, this, [=]{
        QLayoutItem *item = nullptr;
        while ((item = hboxItem->takeAt(0)) != nullptr) {
            //delete item->widget();
            item->widget()->hide();
        }
        vboxGroupRoteiro->removeItem(hboxItem);
        listaItensGrupos[currentIndex] = QString("itemDELETADO");
    });
}

void RoteiroInspecao::salvarNovoRoteiro()
{
    // Testa se todas as informações necessárias estão preenchidas
    QString nomeArq = ui->nomeRoteiroLineEdit->text();
    // Remove possíveis ';' do nomeArq
    nomeArq.replace(";","");
    if (!nomeArq.isEmpty()) {
        QFile rotArq("roteiros.config");
        rotArq.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream inRotArq(&rotArq);
        bool existeRoteiro = false;
        QString line;
        line.clear();
        QStringList colunas;
        colunas.clear();
        while (!inRotArq.atEnd()) {
            line = inRotArq.readLine();
            colunas = line.split(";");
            if (colunas[0] == nomeArq) existeRoteiro = true;
        }
        rotArq.close();
        if (existeRoteiro == false) {
            bool allValidQLineEdit = true;

            saidaList.clear();
            int counter = 0, counterLineEdit = 0, contaItensValidos = 0;
            while (counter < listaItensGrupos.count()) {
                if (listaItensGrupos[counter] == "grupo") {
                    if (listaLineEditPtr[counterLineEdit]->text().isEmpty()) allValidQLineEdit = false;
                    saidaList.append(QString("grupo|%1").arg(listaLineEditPtr[counterLineEdit]->text()));
                    counter++;
                    counterLineEdit++;
                } else if (listaItensGrupos[counter] == "item") {
                    if (listaLineEditPtr[counterLineEdit]->text().isEmpty() || listaLineEditPtr[counterLineEdit+1]->text().isEmpty()) allValidQLineEdit = false;
                    saidaList.append(QString("item|%1|%2").arg(listaLineEditPtr[counterLineEdit]->text()).arg(listaLineEditPtr[counterLineEdit+1]->text()));
                    counter++;
                    counterLineEdit = counterLineEdit + 2;
                    contaItensValidos++;
                } else if (listaItensGrupos[counter] == "grupoDELETADO") {
                    counter++;
                    counterLineEdit++;
                } else if (listaItensGrupos[counter] == "itemDELETADO") {
                    counter++;
                    counterLineEdit = counterLineEdit + 2;
                }
            }
            if (contaItensValidos > 0) {
                if (allValidQLineEdit == true) {
                    QString nomeArqSemEspacos = nomeArq;
                    nomeArqSemEspacos.replace(" ", "");
                    QFile arq(QString("roteiros/%1.txt").arg(nomeArqSemEspacos));
                    arq.open(QIODevice::WriteOnly | QIODevice::Text);

                    QTextStream out(&arq);

                    for (int i=0; i<saidaList.count(); i++) {
                        out << saidaList[i] << endl;
                    }

                    arq.close();

                    QFile file("roteiros.config");
                    file.open(QIODevice::Append | QIODevice::Text);

                    QTextStream outFile(&file);

                    outFile << QString("%1;roteiros/%2.txt").arg(nomeArq).arg(nomeArqSemEspacos) << endl;

                    file.close();
                    // Mensagem de Salvo com Sucesso
                    QMessageBox mensagemBox;
                    mensagemBox.setWindowTitle("Salvo com sucesso");
                    mensagemBox.setWindowIcon(QIcon(":/imagens/hospital.png"));
                    mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                    mensagemBox.setText(QString("Roteiro <FONT COLOR='#0C610C'><strong>%1</strong></FONT> salvo com sucesso!").arg(nomeArq));
                    mensagemBox.exec();
                } else {
                    QMessageBox mensagemBox;
                    mensagemBox.setWindowTitle("Atenção");
                    mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                    mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                    mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: Existem campos não preenchidos no roteiro. Preencha-os ou os exclua antes de salvar o roteiro."));
                    mensagemBox.exec();
                    return;
                }
            } else {
                QMessageBox mensagemBox;
                mensagemBox.setWindowTitle("Atenção");
                mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
                mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
                mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: No mínimo <FONT COLOR='#ff0000'><strong>uma irregularidade</strong></FONT> deve ser inserida no roteiro."));
                mensagemBox.exec();
                return;
            }
        } else {
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: Já existe um roteiro com o nome <FONT COLOR='#ff0000'><strong>%1</strong></FONT>. Escolha outro <FONT COLOR='#ff0000'><strong>Nome do Roteiro</strong></FONT> ou exclua o roteiro antigo.").arg(nomeArq));
            mensagemBox.exec();
            return;
        }
    } else {
        QMessageBox mensagemBox;
        mensagemBox.setWindowTitle("Atenção");
        mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
        mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
        mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O <FONT COLOR='#ff0000'><strong>Nome do Roteiro</strong></FONT> não pode permanecer em branco."));
        mensagemBox.exec();
        return;
    }
}
