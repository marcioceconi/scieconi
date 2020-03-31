#include "equipe.h"
#include "ui_equipe.h"

Equipe::Equipe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipe)
{
    ui->setupUi(this);

    setupEquipesCadastradas();
    getEquipeDefault();
}

Equipe::~Equipe()
{
    delete ui;
}

void Equipe::getEquipeDefault()
{
    QFile arq("equipes.config");

    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipes.config");
        return;
    }

    QTextStream in(&arq);
    QString line = in.readLine();
    arq.close();

    QStringList colunas;
    colunas = line.split(";");

    // Cria QStringList equipePadraoLista e seta com os dados da equipe padrão
    equipePadraoLista = colunas;

    ui->equipePadraoLabel->clear();
    ui->equipePadraoLabel->setText(QString("%1").arg(colunas[1]));

    // Dados Cadastrais
    if (QString::compare(colunas[0],"Estadual") == STR_EQUAL) {
        if (!ui->checkBoxEstadual->isChecked()) ui->checkBoxEstadual->setCheckState(Qt::CheckState::Checked);
        if (ui->checkBoxMunicipal->isChecked()) ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Unchecked);
    } else if (QString::compare(colunas[0],"Municipal") == STR_EQUAL) {
        if (!ui->checkBoxMunicipal->isChecked()) ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Checked);
        if (ui->checkBoxEstadual->isChecked()) ui->checkBoxEstadual->setCheckState(Qt::CheckState::Unchecked);
    }
    ui->comboBoxEquipe->setCurrentText(QString("%1").arg(colunas[1]));
    ui->equipeLogradouroLineEdit->setText(colunas[2]);
    ui->equipeNumeroLineEdit->setText(colunas[3]);
    ui->equipeComplementoLineEdit->setText(colunas[4]);
    ui->equipeBairroLineEdit->setText(colunas[5]);
    ui->equipeCidadeLineEdit->setText(colunas[6]);
    ui->equipeEstadoLineEdit->setText(colunas[7]);
    ui->equipeCEPLineEdit->setText(colunas[8]);
    ui->equipeEmailLineEdit->setText(colunas[9]);
    ui->equipeNucleoLineEdit->setText(colunas[10]);
    ui->equipeSetorLineEdit->setText(colunas[11]);

    // Brasão
    QPixmap brasaoPixmap(colunas[12]);
    ui->brasaoLabel->setScaledContents(true);
    ui->brasaoLabel->setPixmap(brasaoPixmap.scaled(ui->brasaoLabel->width(), ui->brasaoLabel->height(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
    ui->caminhoBrasaoLineEdit->setText(colunas[12]);
}

void Equipe::on_pushButtonAlterarBrasao_clicked()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Escolher Brasão"), QString(), tr("Imagem (*.jpg; *.jpeg; *.png; *.gif)"));

    if (fn.isEmpty()) {
        return;
    } else {
        QString arqSemUrl;
        arqSemUrl.clear();
        bool foundBar = false;
        int posBar = 0;
        for (int i=fn.count()-1; i>0 && foundBar==false; i--) {
            if (fn[i] == "/" || fn[i] == "\\") {
                foundBar = true;
                posBar = i;
            }
        }
        for (int i=posBar+1; i<fn.count(); i++) {
            arqSemUrl.append(fn[i]);
        }
        if (QFile::exists(QString("imagens/brasao/%1").arg(arqSemUrl))) {
            QFile::remove(QString("imagens/brasao/%1").arg(arqSemUrl));
        }
        QFile::copy(fn, QString("imagens/brasao/%1").arg(arqSemUrl));
        ui->brasaoLabel->clear();
        QPixmap brasaoPixmap(QString("imagens/brasao/%1").arg(arqSemUrl));
        ui->brasaoLabel->setScaledContents(true);
        ui->brasaoLabel->setPixmap(brasaoPixmap.scaled(ui->brasaoLabel->width(), ui->brasaoLabel->height(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
        ui->caminhoBrasaoLineEdit->setText(QString("imagens/brasao/%1").arg(arqSemUrl));
    }
}

void Equipe::on_checkBoxEstadual_stateChanged()
{
    if (ui->checkBoxEstadual->isChecked()) {
        if (ui->checkBoxMunicipal->isChecked()) ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Unchecked);
        if (!ui->equipeNucleoLineEdit->isEnabled()) {
            ui->equipeNucleoLineEdit->setEnabled(true);
            if (ui->equipeNucleoLineEdit->text().isEmpty()) ui->equipeNucleoLineEdit->setText("Núcleo Regional de Vigilância em Saúde");
        }
        if (ui->equipeEstadoLineEdit->text().isEmpty()) ui->equipeEstadoLineEdit->setText("RS");
        // Se for equipe Estadual, configura Brasão do Estado como Default
        if (ui->caminhoBrasaoLineEdit->text().isEmpty()) ui->caminhoBrasaoLineEdit->setText(":/imagens/brasao.gif");
        ui->brasaoLabel->clear();
        QPixmap brasaoPixmap(":/imagens/brasao.gif");
        ui->brasaoLabel->setScaledContents(true);
        ui->brasaoLabel->setPixmap(brasaoPixmap.scaled(ui->brasaoLabel->width(), ui->brasaoLabel->height(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
    }
}

void Equipe::on_checkBoxMunicipal_stateChanged()
{
    if (ui->checkBoxMunicipal->isChecked()) {
        if (ui->checkBoxEstadual->isChecked()) ui->checkBoxEstadual->setCheckState(Qt::CheckState::Unchecked);
        if (ui->equipeNucleoLineEdit->isEnabled()) {
            ui->equipeNucleoLineEdit->setEnabled(false);
            ui->equipeNucleoLineEdit->clear();
        }
        if (ui->equipeEstadoLineEdit->text().isEmpty()) ui->equipeEstadoLineEdit->setText("RS");
    }
}

void Equipe::on_pushButtonLimpar_clicked()
{
    //ui->checkBoxEstadual->setCheckState(Qt::CheckState::Unchecked);
    //ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Unchecked);
    ui->comboBoxEquipe->setCurrentIndex(0);
    ui->equipeLogradouroLineEdit->clear();
    ui->equipeNumeroLineEdit->clear();
    ui->equipeComplementoLineEdit->clear();
    ui->equipeBairroLineEdit->clear();
    ui->equipeCidadeLineEdit->clear();
    ui->equipeEstadoLineEdit->clear();
    ui->equipeCEPLineEdit->clear();
    ui->equipeEmailLineEdit->clear();
    ui->equipeNucleoLineEdit->clear();
    ui->equipeSetorLineEdit->clear();
    ui->brasaoLabel->clear();
    ui->caminhoBrasaoLineEdit->clear();
}

void Equipe::on_pushButtonSalvar_clicked()
{
    salvarEquipe();
}

void Equipe::salvarEquipe()
{
    // Primeiro testa se todos os dados obrigatórios estão preenchidos
    QStringList dadosFaltantes;
    dadosFaltantes.clear();
    if ((!ui->checkBoxEstadual->isChecked() && ui->checkBoxMunicipal->isChecked()) || (ui->checkBoxEstadual->isChecked() && !ui->checkBoxMunicipal->isChecked())) {
        if (ui->comboBoxEquipe->currentText().isEmpty()) dadosFaltantes.append("Nome da Equipe");
        if (ui->equipeLogradouroLineEdit->text().isEmpty()) dadosFaltantes.append("Logradouro");
        if (ui->equipeNumeroLineEdit->text().isEmpty()) dadosFaltantes.append("Número");
        if (ui->equipeBairroLineEdit->text().isEmpty()) dadosFaltantes.append("Bairro");
        if (ui->equipeCidadeLineEdit->text().isEmpty()) dadosFaltantes.append("Cidade");
        if (ui->equipeEstadoLineEdit->text().isEmpty()) ui->equipeEstadoLineEdit->setText("RS");
        if (ui->equipeCEPLineEdit->text().isEmpty()) dadosFaltantes.append("CEP");
        if (ui->equipeEmailLineEdit->text().isEmpty()) dadosFaltantes.append("E-mail");
        if (ui->equipeSetorLineEdit->text().isEmpty()) ui->equipeSetorLineEdit->setText("Vigilância Sanitária");
        if (ui->caminhoBrasaoLineEdit->text().isEmpty()) dadosFaltantes.append("Brasão");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return;
        }
    } else { // Tipo de Equipe não foi preenchido
        QMessageBox mensagemBox;
        mensagemBox.setWindowTitle("Atenção");
        mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
        mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
        mensagemBox.setText("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O campo <strong>Tipo de Equipe</strong> não pode permanecer em branco!");
        mensagemBox.exec();
        return;
    }

    QFile arq("equipes.config");
    QFile arqTemp("equipesTEMP.config");

    QTextStream in(&arq);
    QTextStream out(&arqTemp);

    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipes.config");
        return;
    }
    if (!arqTemp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipesTemp.config");
        return;
    }

    QString saidaEquipe, tipoEquipeSelected;
    if (ui->checkBoxEstadual->isChecked()) {
        tipoEquipeSelected = QString("Estadual");
    } else if (ui->checkBoxMunicipal->isChecked()) {
        tipoEquipeSelected = QString("Municipal");
    }
    saidaEquipe = QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12;%13").arg(tipoEquipeSelected).arg(ui->comboBoxEquipe->currentText()).arg(ui->equipeLogradouroLineEdit->text()).arg(ui->equipeNumeroLineEdit->text()).arg(ui->equipeComplementoLineEdit->text()).arg(ui->equipeBairroLineEdit->text()).arg(ui->equipeCidadeLineEdit->text()).arg(ui->equipeEstadoLineEdit->text()).arg(ui->equipeCEPLineEdit->text()).arg(ui->equipeEmailLineEdit->text()).arg(ui->equipeNucleoLineEdit->text()).arg(ui->equipeSetorLineEdit->text()).arg(ui->caminhoBrasaoLineEdit->text());

    QStringList listaParcial;
    listaParcial.clear();
    QString lineIn, lineOut;
    QStringList colunas;
    while (!in.atEnd()) {
        lineIn = in.readLine();
        colunas = lineIn.split(";");
        if (QString::compare(colunas[1], ui->comboBoxEquipe->currentText()) == STR_EQUAL) {
            lineOut = saidaEquipe;
        } else {
            lineOut = lineIn;
        }
        out << lineOut << endl;
        listaParcial.append(lineOut);
    }

    equipesListaCompleta.clear();
    for (int i=1; i<listaParcial.count(); i++) {
        equipesListaCompleta.append(listaParcial[i]);
    }

    arq.close();
    arqTemp.close();

    arq.remove();
    arqTemp.rename("equipes.config");

    // Mensagem avisando que a equipe foi salva com sucesso
    QMessageBox mensagemBox;
    mensagemBox.setWindowTitle("Equipe Salva com Sucesso");
    mensagemBox.setWindowIcon(QIcon(":/imagens/logo.jpg"));
    mensagemBox.setIconPixmap(QPixmap(":/imagens/logo.jpg").scaled(50, 40, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
    mensagemBox.setText(QString("As alterações no cadastro da equipe <FONT COLOR='#ff0000'><strong>%1</strong></FONT> foram salvas com sucesso!").arg(ui->comboBoxEquipe->currentText()));
    mensagemBox.exec();
}

void Equipe::setupEquipesCadastradas()
{
    QFile arq("equipes.config");

    QTextStream in(&arq);

    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipes.config");
        return;
    }

    QString line;
    QStringList colunas;
    equipesListaCompleta.clear();

    // Ignora primeira linha
    line = in.readLine();

    // Lê as linhas restantes
    while (!in.atEnd()) {
        line = in.readLine();
        equipesListaCompleta.append(line);
    }

    arq.close();

    // Atualiza comboBoxEquipe
    ui->comboBoxEquipe->clear();
    for (int i=0; i<equipesListaCompleta.count(); i++) {
        colunas.clear();
        colunas = equipesListaCompleta[i].split(";");
        ui->comboBoxEquipe->addItem(colunas[1]);
    }
}

void Equipe::on_comboBoxEquipe_currentIndexChanged(int index)
{
    QStringList colunas = equipesListaCompleta[index].split(";");
    if (QString::compare(colunas[0], "Estadual") == STR_EQUAL) {
        if (!ui->checkBoxEstadual->isChecked()) ui->checkBoxEstadual->setCheckState(Qt::CheckState::Checked);
        if (ui->checkBoxMunicipal->isChecked()) ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Unchecked);
    } else if (QString::compare(colunas[0], "Municipal") == STR_EQUAL) {
        if (!ui->checkBoxMunicipal->isChecked()) ui->checkBoxMunicipal->setCheckState(Qt::CheckState::Checked);
        if (ui->checkBoxEstadual->isChecked()) ui->checkBoxEstadual->setCheckState(Qt::CheckState::Unchecked);
    }
    ui->equipeLogradouroLineEdit->setText(colunas[2]);
    ui->equipeNumeroLineEdit->setText(colunas[3]);
    ui->equipeComplementoLineEdit->setText(colunas[4]);
    ui->equipeBairroLineEdit->setText(colunas[5]);
    ui->equipeCidadeLineEdit->setText(colunas[6]);
    ui->equipeEstadoLineEdit->setText(colunas[7]);
    ui->equipeCEPLineEdit->setText(colunas[8]);
    ui->equipeEmailLineEdit->setText(colunas[9]);
    ui->equipeNucleoLineEdit->setText(colunas[10]);
    ui->equipeSetorLineEdit->setText(colunas[11]);
    ui->caminhoBrasaoLineEdit->setText(colunas[12]);
    ui->brasaoLabel->clear();
    QPixmap brasaoPixmap(colunas[12]);
    ui->brasaoLabel->setScaledContents(true);
    ui->brasaoLabel->setPixmap(brasaoPixmap.scaled(ui->brasaoLabel->width(), ui->brasaoLabel->height(), Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
}

void Equipe::on_pushButtonDefinirEquipePadrao_clicked()
{
    // Primeiro testa se todos os dados obrigatórios estão preenchidos
    QStringList dadosFaltantes;
    dadosFaltantes.clear();
    if ((!ui->checkBoxEstadual->isChecked() && ui->checkBoxMunicipal->isChecked()) || (ui->checkBoxEstadual->isChecked() && !ui->checkBoxMunicipal->isChecked())) {
        if (ui->comboBoxEquipe->currentText().isEmpty()) dadosFaltantes.append("Nome da Equipe");
        if (ui->equipeLogradouroLineEdit->text().isEmpty()) dadosFaltantes.append("Logradouro");
        if (ui->equipeNumeroLineEdit->text().isEmpty()) dadosFaltantes.append("Número");
        if (ui->equipeBairroLineEdit->text().isEmpty()) dadosFaltantes.append("Bairro");
        if (ui->equipeCidadeLineEdit->text().isEmpty()) dadosFaltantes.append("Cidade");
        if (ui->equipeEstadoLineEdit->text().isEmpty()) ui->equipeEstadoLineEdit->setText("RS");
        if (ui->equipeCEPLineEdit->text().isEmpty()) dadosFaltantes.append("CEP");
        if (ui->equipeEmailLineEdit->text().isEmpty()) dadosFaltantes.append("E-mail");
        if (ui->equipeSetorLineEdit->text().isEmpty()) ui->equipeSetorLineEdit->setText("Vigilância Sanitária");
        if (ui->caminhoBrasaoLineEdit->text().isEmpty()) dadosFaltantes.append("Brasão");
        if (!dadosFaltantes.isEmpty()) {
            QString saidaFaltantes;
            if (dadosFaltantes.count() == 1) {
                saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
            } else if (dadosFaltantes.count() == 2) {
                saidaFaltantes = QString("<strong>%1</strong> e <strong>%2</strong>").arg(dadosFaltantes[0]).arg(dadosFaltantes[1]);
            } else {
                saidaFaltantes.clear();
                for (int i=0; i<dadosFaltantes.count()-1; i++) {
                    if (i == 0) {
                        saidaFaltantes = QString("<strong>%1</strong>").arg(dadosFaltantes[0]);
                    } else {
                        saidaFaltantes.append(QString(", <strong>%1</strong>").arg(dadosFaltantes[i]));
                    }
                }
                saidaFaltantes.append(QString(" e <strong>%1</strong>").arg(dadosFaltantes[dadosFaltantes.count()-1]));
            }
            QMessageBox mensagemBox;
            mensagemBox.setWindowTitle("Atenção");
            mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
            mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
            mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O(s) seguinte(s) campo(s) não pode(m) permanecer em branco: %1.").arg(saidaFaltantes));
            mensagemBox.exec();
            return;
        }
    } else { // Tipo de Equipe não foi preenchido
        QMessageBox mensagemBox;
        mensagemBox.setWindowTitle("Atenção");
        mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
        mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
        mensagemBox.setText("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: O campo <strong>Tipo de Equipe</strong> não pode permanecer em branco!");
        mensagemBox.exec();
        return;
    }

    // Atualiza o arquivo equipes.config com a equipe padrão
    int indexPadrao = 0;
    indexPadrao = ui->comboBoxEquipe->currentIndex();

    QFile arqIn("equipes.config");
    QFile arqOut("equipesTemp.config");

    if (!arqIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipes.config");
        return;
    }
    if (!arqOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Erro: não foi possível abrir arquivo equipesTemp.config");
        return;
    }

    QTextStream inRead(&arqIn);
    QTextStream outWrite(&arqOut);

    QString line;

    outWrite << equipesListaCompleta[indexPadrao] << endl;
    equipePadraoLista = equipesListaCompleta[indexPadrao].split(";");
    ui->equipePadraoLabel->setText(equipePadraoLista[1]);
    line = inRead.readLine(); // Ignora primeira linha
    while (!inRead.atEnd()) {
        line = inRead.readLine();
        outWrite << line << endl;
    }

    arqIn.close();
    arqOut.close();

    arqIn.remove();
    arqOut.rename("equipes.config");
}
