#ifndef TIPIFICACAO_H
#define TIPIFICACAO_H

#include <QWidget>

namespace Ui {
class Tipificacao;
}

class Tipificacao : public QWidget
{
    Q_OBJECT

public:
    explicit Tipificacao(QWidget *parent = nullptr);
    ~Tipificacao();

    QStringList getTipificaReturn();
    bool isTipificacaoValidBool();
private slots:
    void on_comboBoxInciso6437_currentIndexChanged(int index);

    void on_pushButtonSelecionarInciso_clicked();

    void on_pushButtonOK_clicked();

    void on_pushButtonLimpar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::Tipificacao *ui;

    QList<int> selectedIncisos;
    QStringList inciso6437List = {";;",
                                  "I;construir, instalar ou fazer funcionar, em qualquer parte do território nacional, laboratórios de produção de medicamentos, drogas, insumos, cosméticos, produtos de higiene, dietéticos, correlatos, ou quaisquer outros estabelecimentos que fabriquem alimentos, aditivos para alimentos, bebidas, embalagens, saneantes e demais produtos que interessem à saúde pública, sem registro, licença e autorizações do órgão sanitário competente ou contrariando as normas legais pertinentes;advertência, interdição, cancelamento de autorização e de licença, e/ou multa",
                                 "II;construir, instalar ou fazer funcionar hospitais, postos ou casas de saúde, clínicas em geral, casas de repouso, serviços ou unidades de saúde, estabelecimentos ou organizações afins, que se dediquem à promoção, proteção e recuperação da saúde, sem licença do órgão sanitário competente ou contrariando normas legais e regulamentares pertinentes;advertência, interdição, cancelamento da licença e/ou multa",
                                 "III;instalar ou manter em funcionamento consultórios médicos, odontológicos e de pesquisas clínicas, clínicas de hemodiálise, bancos de sangue, de leite humano, de olhos, e estabelecimentos de atividades afins, institutos de esteticismo, ginástica, fisioterapia e de recuperação, balneários, estâncias hidrominerais, termais, climatéricas, de repouso, e congêneres, gabinetes ou serviços que utilizem aparelhos e equipamentos geradores de raios X, substâncias radioativas, ou radiações ionizantes e outras, estabelecimentos, laboratórios, oficinas e serviços de ótica, de aparelhos ou materiais óticos, de prótese dentária, de aparelhos ou materiais para uso odontológico, ou explorar atividades comerciais, industriais, ou filantrópicas, com a participação de agentes que exerçam profissões ou ocupações técnicas e auxiliares relacionadas com a saúde, sem licença do órgão sanitário competente ou contrariando o disposto nas demais normas legais e regulamentares pertinentes;advertência, intervenção, interdição, cancelamento da licença e/ou multa",
                                 "IV;extrair, produzir, fabricar, transformar, preparar, manipular, purificar, fracionar, embalar ou reembalar, importar, exportar, armazenar, expedir, transportar, comprar, vender, ceder ou usar alimentos, produtos alimentícios, medicamentos, drogas, insumos farmacêuticos, produtos dietéticos, de higiene, cosméticos, correlatos, embalagens, saneantes, utensílios e aparelhos que interessem à saúde pública ou individual, sem registro, licença, ou autorizações do órgão sanitário competente ou contrariando o disposto na legislação sanitária pertinente;advertência, apreensão e inutilização, interdição, cancelamento do registro, e/ou multa",
                                 "V;fazer propaganda de produtos sob vigilância sanitária, alimentos e outros, contrariando a legislação sanitária;advertência, proibição de propaganda, suspensão de venda, imposição de mensagem retificadora, suspensão de propaganda e publicidade e multa",
                                 "VI;deixar, aquele que tiver o dever legal de fazê-lo, de notificar doença ou zoonose transmissível ao homem, de acordo com o que disponham as normas legais ou regulamentares vigentes;advertência, e/ou multa",
                                 "VII;impedir ou dificultar a aplicação de medidas sanitárias relativas às doenças transmissíveis e ao sacrifício de animais domésticos considerados perigosos pelas autoridades sanitárias;advertência, e/ou multa",
                                 "VIII;reter atestado de vacinação obrigatória, deixar de executar, dificultar ou opor-se à execução de medidas sanitárias que visem à prevenção das doenças transmissíveis e sua disseminação, à preservação e à manutenção da saúde;advertência, interdição, cancelamento de licença ou autorização, e/ou multa",
                                 "IX;opor-se à exigência de provas imunológicas ou à sua execução pelas autoridades sanitárias;advertência, e/ou multa",
                                 "X;obstar ou dificultar a ação fiscalizadora das autoridades sanitárias competentes no exercício de suas funções;advertência, intervenção, interdição, cancelamento de licença e/ou multa",
                                 "XI;aviar receita em desacordo com prescrições médicas ou determinação expressa de lei e normas regulamentares;advertência, interdição, cancelamento de licença, e/ou multa",
                                 "XII;fornecer, vender ou praticar atos de comércio em relação a medicamentos, drogas e correlatos cuja venda e uso dependam de prescrição médica, sem observância dessa exigência e contrariando as normas legais e regulamentares;advertência, interdição, cancelamento da licença, e/ou multa",
                                 "XIII;retirar ou aplicar sangue, proceder a operações de plasmaferese, ou desenvolver outras atividades hemoterápicas, contrariando normas legais e regulamentares;advertência, intervenção, interdição, cancelamento da licença e registro e/ou multa",
                                 "XIV;exportar sangue e seus derivados, placentas, órgãos, glândulas ou hormônios, bem como quaisquer substâncias ou partes do corgo humano, ou utilizá-los contrariando as disposições legais e regulamentares;advertência, intervenção, interdição, cancelamento de licença e registro e/ou multa",
                                 "XV;rotular alimentos e produtos alimentícios ou bebidas bem como medicamentos, drogas, insumos farmacêuticos, produtos dietéticos, de higiene, cosméticos, perfumes, correlatos, saneantes, de correção estética e quaisquer outros contrariando as normas legais e regulamentares;advertência, inutilização, interdição, e/ou multa",
                                 "XVI;alterar o processo de fabricação dos produtos sujeitos a controle sanitário, modificar os seus componentes básicos, nome, e demais elementos objeto do registro, sem a necessária autorização do órgão sanitário competente;advertência, interdição, cancelamento do registro da licença e autorização, e/ou multa",
                                 "XVII;reaproveitar vasilhames de saneantes, seus congêneres e de outros produtos capazes de serem nocivos à saúde, no envasilhamento de alimentos, bebidas, refrigerantes, produtos dietéticos, medicamentos, drogas, produtos de higiene, cosméticos e perfumes;advertência, apreensão, inutilização, interdição, cancelamento do registro, e/ou multa",
                                 "XVIII;importar ou exportar, expor à venda ou entregar ao consumo produtos de interesse à saúde cujo prazo de validade tenha se expirado, ou apor-lhes novas datas, após expirado o prazo;advertência, apreensão, inutilização, interdição, cancelamento do registro, da licença e da autorização, e/ou multa",
                                 "XIX;industrializar produtos de interesse sanitário sem a assistência de responsável técnico, legalmente habilitado;advertência, apreensão, inutilização, interdição, cancelamento do registro, e/ou multa",
                                 "XX;utilizar, na preparação de hormônios, órgãos de animais doentes, estafados ou emagrecidos ou que apresentem sinais de decomposição no momento de serem manipulados;advertência, apreensão, inutilização, interdição, cancelamento do registro, da autorização e da licença, e/ou multa",
                                 "XXI;comercializar produtos biológicos, imunoterápicos e outros que exijam cuidados especiais de conservação, preparação, expedição, ou transporte, sem observância das condições necessárias à sua preservação;advertência, apreensão, inutilização, interdição, cancelamento do registro, e/ou multa",
                                 "XXII;aplicação, por empresas particulares, de raticidas cuja ação se produza por gás ou vapor, em galerias, bueiros, porões, sótãos ou locais de possível comunicação com residências ou freqüentados por pessoas e animais;advertência, interdição, cancelamento de licença e de autorização, e/ou multa",
                                 "XXIII;descumprimento de normas legais e regulamentares, medidas, formalidades e outras exigências sanitárias pelas empresas de transportes, seus agentes e consignatários, comandantes ou responsáveis diretos por embarcações, aeronaves, ferrovias, veículos terrestres, nacionais e estrangeiros;advertência, interdição, e/ou multa",
                                 "XXIV;inobservância das exigências sanitárias relativas a imóveis, pelos seus proprietários, ou por quem detenha legalmente a sua posse;advertência, interdição, e/ou multa",
                                 "XXV;exercer profissões e ocupações relacionadas com a saúde sem a necessária habilitação legal;interdição e/ou multa",
                                 "XXVI;cometer o exercício de encargos relacionados com a promoção, proteção e recuperação da saúde a pessoas sem a necessária habilitação legal;interdição, e/ou multa",
                                 "XXVII;proceder à cremação de cadáveres, ou utilizá-los, contrariando as normas sanitárias pertinentes;advertência, interdição, e/ou multa",
                                 "XXVIII;fraudar, falsificar ou adulterar alimentos, inclusive bebidas, medicamentos, drogas, insumos farmacêuticos, correlatos, comésticos, produtos de higiene, dietéticos, saneantes e quaisquer outros que interessem à saúde pública;advertência, apreensão, inutilização e/ou interdição do produto, suspensão de venda e/ou fabricação do produto, cancelamento do registro do produto, interdição parcial ou total do estabelecimento, cancelamento de autorização para o funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento e/ou multa",
                                 "XXIX;transgredir outras normas legais e regulamentares destinadas à proteção da saúde;advertência, apreensão, inutilização e/ou interdição do produto; suspensão de venda e/ou fabricação do produto, cancelamento do registro do produto; interdição parcial ou total do estabelecimento, cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento, proibição de propaganda e/ou multa",
                                 "XXX;expor ou entregar ao consumo humano, sal refinado, moído ou granulado, que não contenha iodo na proporção estabelecida pelo Ministério da Saúde;advertência, apreensão e/ou interdição do produto, suspensão de venda e/ou fabricação do produto, cancelamento do registro do produto e interdição parcial ou total do estabelecimento, cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento e/ou multa",
                                 "XXXI;descumprir atos emanados das autoridades sanitárias competentes visando à aplicação da legislação pertinente;advertência, apreensão, inutilização e/ou interdição do produto, suspensão de venda e/ou de fabricação do produto, cancelamento do registro do produto; interdição parcial ou total do estabelecimento; cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento, proibição de propaganda e/ou multa",
                                 "XXXII;descumprimento de normas legais e regulamentares, medidas, formalidades, outras exigências sanitárias, por pessoas física ou jurídica, que operem a prestação de serviços de interesse da saúde pública em embarcações, aeronaves, veículos terrestres, terminais alfandegados, terminais aeroportuários ou portuários, estações e passagens de fronteira e pontos de apoio de veículos terrestres;advertência, interdição, cancelamento da autorização de funcionamento e/ou multa",
                                 "XXXIII;descumprimento de normas legais e regulamentares, medidas, formalidades, outras exigências sanitárias, por empresas administradoras de terminais alfandegados, terminais aeroportuários ou portuários, estações e passagens de fronteira e pontos de apoio de veículos terrestres;advertência, interdição, cancelamento da autorização de funcionamento e/ou multa",
                                 "XXXIV;descumprimento de normas legais e regulamentares, medidas, formalidades, outras exigências sanitárias relacionadas à importação ou exportação, por pessoas física ou jurídica, de matérias-primas ou produtos sob vigilância sanitária;advertência, apreensão, inutilização, interdição, cancelamento da autorização de funcionamento, cancelamento do registro do produto e/ou multa",
                                 "XXXV;descumprimento de normas legais e regulamentares, medidas, formalidades, outras exigências sanitárias relacionadas a estabelecimentos e às boas práticas de fabricação de matérias-primas e de produtos sob vigilância sanitária;advertência, apreensão, inutilização, interdição, cancelamento da autorização de funcionamento, cancelamento do registro do produto e/ou multa",
                                 "XXXVI;proceder a mudança de estabelecimento de armazenagem de produto importado sob interdição, sem autorização do órgão sanitário competente;advertência, apreensão, inutilização, interdição, cancelamento da autorização de funcionamento, cancelamento do registro do produto e/ou multa",
                                 "XXXVII;proceder a comercialização de produto importado sob interdição;advertência, apreensão, inutilização, interdição, cancelamento da autorização de funcionamento, cancelamento do registro do produto e/ou multa",
                                 "XXXVIII;deixar de garantir, em estabelecimentos destinados à armazenagem e/ou distribuição de produtos sob vigilância sanitária, a manutenção dos padrões de identidade e qualidade de produtos importados sob interdição ou aguardando inspeção física;advertência, apreensão, inutilização, interdição, cancelamento da autorização de funcionamento, cancelamento do registro do produto e/ou multa",
                                 "XXXIX;interromper, suspender ou reduzir, sem justa causa, a produção ou distribuição de medicamentos de tarja vermelha, de uso continuado ou essencial à saúde do indivíduo, ou de tarja preta, provocando o desabastecimento do mercado;advertência, interdição total ou parcial do estabelecimento, cancelamento do registro do produto, cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento e/ou multa",
                                 "XL;deixar de comunicar ao órgão de vigilância sanitária do Ministério da Saúde a interrupção, suspensão ou redução da fabricação ou da distribuição dos medicamentos referidos no inciso XXXIX;advertência, interdição total ou parcial do estabelecimento, cancelamento do registro do produto, cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento e/ou multa",
                                 "XLI;descumprir normas legais e regulamentares, medidas, formalidades, outras exigências sanitárias, por pessoas física ou jurídica, que operem a prestação de serviços de interesse da saúde pública em embarcações, aeronaves, veículos terrestres, terminais alfandegados, terminais aeroportuários ou portuários, estações e passagens de fronteira e pontos de apoio de veículo terrestres;advertência, interdição total ou parcial do estabelecimento, cancelamento do registro do produto, cancelamento de autorização para funcionamento da empresa, cancelamento do alvará de licenciamento do estabelecimento e/ou multa",
                                 "XLII;reincidir na manutenção de focos de vetores no imóvel por descumprimento de recomendação das autoridades sanitárias;multa de 10% (dez por cento) dos valores previstos no inciso I do § 1o do art. 2o, aplicada em dobro em caso de nova reincidência"};
    QStringList incisoPenalidades6437List = {"",
                                 "advertência;interdição;cancelamento de autorização e de licença;multa",
                                 "advertência;interdição;cancelamento da licença;multa",
                                 "advertência;intervenção;interdição;cancelamento da licença;multa",
                                 "advertência;apreensão e inutilização;interdição;cancelamento do registro;multa",
                                 "advertência;proibição de propaganda;suspensão de venda;imposição de mensagem retificadora;suspensão de propaganda e publicidade;multa",
                                 "advertência;multa",
                                 "advertência;multa",
                                 "advertência;interdição;cancelamento de licença ou autorização;multa",
                                 "advertência;multa",
                                 "advertência;intervenção;interdição;cancelamento de licença;multa",
                                 "advertência;interdição;cancelamento de licença;multa",
                                 "advertência;interdição;cancelamento da licença;multa",
                                 "advertência;intervenção;interdição;cancelamento da licença e registro;multa",
                                 "advertência;intervenção;interdição;cancelamento de licença e registro;multa",
                                 "advertência;inutilização;interdição;multa",
                                 "advertência;interdição;cancelamento do registro da licença e autorização;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento do registro;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento do registro, da licença e da autorização;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento do registro;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento do registro, da autorização e da licença;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento do registro;multa",
                                 "advertência;interdição;cancelamento de licença e de autorização;multa",
                                 "advertência;interdição;multa",
                                 "advertência;interdição;multa",
                                 "interdição;multa",
                                 "interdição;multa",
                                 "advertência;interdição;multa",
                                 "advertência;apreensão;inutilização e/ou interdição do produto;suspensão de venda e/ou fabricação do produto;cancelamento do registro do produto;interdição parcial ou total do estabelecimento;cancelamento de autorização para o funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;multa",
                                 "interdição parcial ou total do estabelecimento;cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;proibição de propaganda;multa",
                                 "advertência;apreensão e/ou interdição do produto;suspensão de venda e/ou fabricação do produto;cancelamento do registro do produto e interdição parcial ou total do estabelecimento;cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;multa",
                                 "cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;proibição de propaganda;multa",
                                 "advertência;interdição;cancelamento da autorização de funcionamento;multa",
                                 "advertência;interdição;cancelamento da autorização de funcionamento;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento da autorização de funcionamento;cancelamento do registro do produto;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento da autorização de funcionamento;cancelamento do registro do produto;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento da autorização de funcionamento;cancelamento do registro do produto;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento da autorização de funcionamento;cancelamento do registro do produto;multa",
                                 "advertência;apreensão;inutilização;interdição;cancelamento da autorização de funcionamento;cancelamento do registro do produto;multa",
                                 "advertência;interdição total ou parcial do estabelecimento;cancelamento do registro do produto;cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;multa",
                                 "advertência;interdição total ou parcial do estabelecimento;cancelamento do registro do produto;cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;multa",
                                 "advertência;interdição total ou parcial do estabelecimento;cancelamento do registro do produto;cancelamento de autorização para funcionamento da empresa;cancelamento do alvará de licenciamento do estabelecimento;multa",
                                 "multa de 10% (dez por cento) dos valores previstos no inciso I do § 1o do art. 2o, aplicada em dobro em caso de nova reincidência"};

    void setupComboIncisos6437();
};

#endif // TIPIFICACAO_H
