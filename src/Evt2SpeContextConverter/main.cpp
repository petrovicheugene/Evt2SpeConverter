//==========================================================
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "ZEvt2SpeConverter.h"
//==========================================================
int main(int argc, char* argv[])
{
    // INVISIBLE RUNNING
    // Remove CONFIG += console from .pro file
    QApplication a(argc, argv);
    QCommandLineParser parser;
    parser.process(a);

    ZEvt2SpeConverter converter(new ZEvtSpectrumDataExtractor);
    converter.zp_convertFiles(parser.positionalArguments());

    return 0;
}
//==========================================================
