//==========================================================
#include "ZEvtSpectrumDataExtractor.h"
#include <QMessageBox>
//==========================================================
ZEvtSpectrumDataExtractor::ZEvtSpectrumDataExtractor(QObject* parent)
    : QObject(parent)
{
    zv_channelCountSift = 0x100; // 256 byte
    zv_byteOrder = QDataStream::LittleEndian;
    zv_fillerString += "\n";
}
//==========================================================
bool ZEvtSpectrumDataExtractor::zp_convert(QDataStream& dataStream,
                                           QStringList& speStringList)
{
    // adjust data stream
    dataStream.setByteOrder(zv_byteOrder);
    dataStream.skipRawData(zv_channelCountSift);

    // get channel count
    qint32 channelCount = 0;
    dataStream >> channelCount;

    // get channel data
    qint32 channelValue = 0;
    for (int i = 0; i < channelCount; ++i)
    {
        dataStream >> channelValue;
        speStringList << QString::number(channelValue) + "\n";
    }

    return true;
}
//==========================================================
void ZEvtSpectrumDataExtractor::zp_setByteOrder(QDataStream::ByteOrder byteOrder)
{
    zv_byteOrder = byteOrder;
}
//==========================================================
void ZEvtSpectrumDataExtractor::zp_setChannelCountShift(CHANNEL_COUNT_UNIT shift)
{
    zv_channelCountSift = shift;
}
//==========================================================
void ZEvtSpectrumDataExtractor::zp_setFillerString(const QString& fillerString)
{
    zv_fillerString = fillerString;
    if (!zv_fillerString.endsWith("\n"))
    {
        zv_fillerString += "\n";
    }
}
//==========================================================
