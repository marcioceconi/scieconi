#include "tipificacao.h"
#include "ui_tipificacao.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define STR_EQUAL 0

Tipificacao::Tipificacao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tipificacao)
{
    ui->setupUi(this);

    selectedIncisos.clear();
}

Tipificacao::~Tipificacao()
{
    delete ui;
}

void Tipificacao::setupComboIncisos6437()
{
    ui->comboBoxInciso6437->addItems(inciso6437List);
}
void Tipificacao::on_comboBoxInciso6437_currentIndexChanged(int index)
{
    QStringList colunas;
    colunas.clear();
    colunas = inciso6437List[index].split(";");
    ui->incisoPlainTextEdit->setPlainText(colunas[1]);
    ui->penalidadePlainTextEdit->setPlainText(colunas[2]);
}

void Tipificacao::on_pushButtonSelecionarInciso_clicked()
{
    QStringList listaPenalidades, colunas;
    listaPenalidades.clear();
    bool found = false;
    if (ui->comboBoxInciso6437->currentIndex() != 0) {
        selectedIncisos.append(ui->comboBoxInciso6437->currentIndex());
        listaPenalidades.clear();
        selectedIncisos.append(ui->comboBoxInciso6437->currentIndex());
        for (int i=0; i<selectedIncisos.count(); i++) {
            colunas = incisoPenalidades6437List[ui->comboBoxInciso6437->currentIndex()].split(";");
            for (int j=0; j<colunas.count(); j++) {
                found = false;
                for (int k=0; k<listaPenalidades.count(); k++) {
                    if (QString::compare(listaPenalidades[k], colunas[j]) == STR_EQUAL) {
                        found = true;
                    }
                }
                if (found == false) listaPenalidades.append(colunas[j]);
            }
        }
    }
    // Exibe incisos selecionados
    QString saidaIncisos, saidaPenalidades;
    saidaIncisos.clear();
    saidaPenalidades.clear();

}

void Tipificacao::on_pushButtonOK_clicked()
{
    if (isTipificacaoValidBool() == true) {
        Tipificacao::close();
    }
}

bool Tipificacao::isTipificacaoValidBool()
{
    if (ui->incisoSelecionadoPlainTextEdit->toPlainText().isEmpty() || ui->penalidadeIncisoSelecionadoPlainTextEdit->toPlainText().isEmpty()) {
        QMessageBox mensagemBox;
        mensagemBox.setWindowTitle("Atenção");
        mensagemBox.setWindowIcon(QIcon(":/imagens/alert.png"));
        mensagemBox.setIconPixmap(QPixmap(":/imagens/alert.png").scaled(100, 80, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
        mensagemBox.setText(QString("<FONT COLOR='#ff0000'><strong>ATENÇÃO</strong></FONT>: Deve ser selecionado <FONT COLOR='#ff0000'><strong>no mínimo 1 (um) Inciso do Art. 10 da Lei 6.437/77</strong></FONT> para tipificação da(s) infração(ões)."));
        mensagemBox.exec();
        return false;
    } else {
        return true;
    }
}

QStringList Tipificacao::getTipificaReturn()
{
    QString saidaTipificacao, saidaPenalidadeTipificacao;

    saidaTipificacao = ui->incisoSelecionadoPlainTextEdit->toPlainText();
    saidaPenalidadeTipificacao = ui->penalidadeIncisoSelecionadoPlainTextEdit->toPlainText();

    return QStringList{saidaTipificacao, saidaPenalidadeTipificacao};
}

void Tipificacao::on_pushButtonLimpar_clicked()
{
    ui->comboBoxInciso6437->setCurrentIndex(0);
    ui->incisoSelecionadoPlainTextEdit->clear();
    ui->penalidadeIncisoSelecionadoPlainTextEdit->clear();
    selectedIncisos.clear();
}

void Tipificacao::on_pushButtonCancelar_clicked()
{
    selectedIncisos.clear();
    Tipificacao::close();
}
