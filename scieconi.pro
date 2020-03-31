#-------------------------------------------------
#
# Project created by QtCreator 2020-02-13T08:40:09
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = scieconi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        customtoolbutton.cpp \
        docx.cpp \
        geradocumentos.cpp \
        main.cpp \
        mainwindow.cpp \
        equipe.cpp \
        coderxml.cpp \
        autodeinfracao.cpp \
        arquivamento.cpp \
        autodeinfracaoanalisefiscal.cpp \
        avisoderecebimento.cpp \
        despachodoar.cpp \
        notifdecisaofinal.cpp \
        notifdesprovimentorecurso.cpp \
        notifimpospenalidadeprocedencia.cpp \
        notifimpospenalidadeparcialprocedencia.cpp \
        notifimpospenademulta.cpp \
        notifpagamentomultaaposdecisaofinal.cpp \
        notifparcialprovimentorecurso.cpp \
        odt.cpp \
        termoapreensaoinutilizacaoaposdecisaofinal.cpp \
        termocoletaamostras.cpp \
        termointerdicaoestabelecimento.cpp \
        termointerdicaoproduto.cpp \
        termointerdicaoprodutosemautuacao.cpp \
        termoinutilizacaoimediataproduto.cpp \
        termovinculadodesinterdicaoestabelecimento.cpp \
        termovinculadodesinterdicaoproduto.cpp \
        widget6437.cpp \
        roteiroinspecao.cpp

HEADERS += \
        customtoolbutton.h \
        mainwindow.h \
        equipe.h \
        coderxml.h \
        autodeinfracao.h \
        arquivamento.h \
        autodeinfracaoanalisefiscal.h \
        avisoderecebimento.h \
        despachodoar.h \
        notifdecisaofinal.h \
        notifdesprovimentorecurso.h \
        notifimpospenalidadeprocedencia.h \
        notifimpospenalidadeparcialprocedencia.h \
        notifimpospenademulta.h \
        notifpagamentomultaaposdecisaofinal.h \
        notifparcialprovimentorecurso.h \
        termoapreensaoinutilizacaoaposdecisaofinal.h \
        termocoletaamostras.h \
        termointerdicaoestabelecimento.h \
        termointerdicaoproduto.h \
        termointerdicaoprodutosemautuacao.h \
        termoinutilizacaoimediataproduto.h \
        termovinculadodesinterdicaoestabelecimento.h \
        termovinculadodesinterdicaoproduto.h \
        roteiroinspecao.h

FORMS += \
        mainwindow.ui \
        equipe.ui \
        coderxml.ui \
        autodeinfracao.ui \
        arquivamento.ui \
        autodeinfracaoanalisefiscal.ui \
        avisoderecebimento.ui \
        despachodoar.ui \
        notifdecisaofinal.ui \
        notifdesprovimentorecurso.ui \
        notifimpospenalidadeprocedencia.ui \
        notifimpospenalidadeparcialprocedencia.ui \
        notifimpospenademulta.ui \
        notifpagamentomultaaposdecisaofinal.ui \
        notifparcialprovimentorecurso.ui \
        termoapreensaoinutilizacaoaposdecisaofinal.ui \
        termocoletaamostras.ui \
        termointerdicaoestabelecimento.ui \
        termointerdicaoproduto.ui \
        termointerdicaoprodutosemautuacao.ui \
        termoinutilizacaoimediataproduto.ui \
        termovinculadodesinterdicaoestabelecimento.ui \
        termovinculadodesinterdicaoproduto.ui \
        roteiroinspecao.ui

win32:RC_ICONS += hospital.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# INCLUSÃO DE ZLIB E QUAZIP PARA COMPRESSÃO DOS ARQUIVOS
LIBS += -L"C:/Users/marcio-ceconi/Desktop/GIT/SCIECONI/scieconi/lib" -lz -lquazip
INCLUDEPATH += "C:/Users/marcio-ceconi/Desktop/GIT/SCIECONI/scieconi/include/quazip"

RESOURCES += \
    resources.qrc
