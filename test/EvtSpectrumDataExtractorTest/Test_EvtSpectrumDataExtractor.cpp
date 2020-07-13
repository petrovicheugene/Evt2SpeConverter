//==========================================================
#include <QCoreApplication>
#include <QDebug>
#include <QtTest>
//==========================================================
// add necessary includes here
#include "ZEvtSpectrumDataExtractor.h"
//==========================================================
class Test_EvtSpectrumDataExtractor : public QObject
{
    Q_OBJECT

public:
    Test_EvtSpectrumDataExtractor();
    ~Test_EvtSpectrumDataExtractor();

private slots:
    void zp_convert();
};
//==========================================================
Test_EvtSpectrumDataExtractor::Test_EvtSpectrumDataExtractor() {}
//==========================================================
Test_EvtSpectrumDataExtractor::~Test_EvtSpectrumDataExtractor() {}
//==========================================================
void Test_EvtSpectrumDataExtractor::zp_convert()
{
    char data[] = {0x03,
                   0x00,
                   0x00,
                   0x00,
                   0x4A,
                   0x00,
                   0x00,
                   0x00,
                   0x5A,
                   0x00,
                   0x00,
                   0x00,
                   0x4D,
                   0x00,
                   0x00,
                   0x00};
    QByteArray dataByteArray = QByteArray::fromRawData(data, sizeof(data));
    QDataStream stream(dataByteArray);
    stream.setByteOrder(QDataStream::LittleEndian);

    ZEvtSpectrumDataExtractor converter;
    QStringList speData;
    converter.zp_setByteOrder(QDataStream::LittleEndian);
    converter.zp_setChannelCountShift(0);
    converter.zp_convert(stream, speData);

    QStringList sample;
    sample << "74\n";
    sample << "90\n";
    sample << "77\n";

    QCOMPARE(speData, sample);
}
//==========================================================
QTEST_MAIN(Test_EvtSpectrumDataExtractor)

#include "Test_EvtSpectrumDataExtractor.moc"
