//==========================================================
#include <QCoreApplication>
#include <QDebug>
#include <QtTest>
//==========================================================
// add necessary includes here
#include "ZEvt2SpeDataConverter.h"
//==========================================================
class Test_evt2speDataConverter : public QObject
{
    Q_OBJECT

public:
    Test_evt2speDataConverter();
    ~Test_evt2speDataConverter();

private slots:
    void zp_convert();
};
//==========================================================
Test_evt2speDataConverter::Test_evt2speDataConverter() {}
//==========================================================
Test_evt2speDataConverter::~Test_evt2speDataConverter() {}
//==========================================================
void Test_evt2speDataConverter::zp_convert()
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

    //    qint32 buffer = 0x00000000;
    //    for (int i = 0; i < dataByteArray.size(); ++i)
    //    {
    //        stream >> buffer;
    //        qDebug() << buffer;
    //    }

    ZEvt2SpeDataConverter converter;
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
QTEST_MAIN(Test_evt2speDataConverter)

#include "tst_evt2spedataconverter.moc"
