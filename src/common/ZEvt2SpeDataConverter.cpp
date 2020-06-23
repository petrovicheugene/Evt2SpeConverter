//==========================================================
#include "ZEvt2SpeDataConverter.h"
#include <QMessageBox>
//==========================================================
ZEvt2SpeDataConverter::ZEvt2SpeDataConverter(QObject* parent) : QObject(parent)
{
    zv_channelCountSift = 0x100; // 256 byte
    zv_byteOrder = QDataStream::LittleEndian;
    zv_speHeaderLineNumber = 20;
    zv_fillerString += "\n";
}
//==========================================================
bool ZEvt2SpeDataConverter::zp_convert(QDataStream& dataStream,
                                       QStringList& speStringList)
{
    // write spe header
    speStringList << "Converted from .evt\n";

    for (int i = 1; i < zv_speHeaderLineNumber; ++i)
    {
        speStringList << zv_fillerString;
    }

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
void ZEvt2SpeDataConverter::zp_setByteOrder(QDataStream::ByteOrder byteOrder)
{
    zv_byteOrder = byteOrder;
}
//==========================================================
void ZEvt2SpeDataConverter::zp_setChannelCountShift(CHANNEL_COUNT_UNIT shift)
{
    zv_channelCountSift = shift;
}
//==========================================================
void ZEvt2SpeDataConverter::zp_setFillerString(const QString& fillerString)
{
    zv_fillerString = fillerString;
    if (!zv_fillerString.endsWith("\n"))
    {
        zv_fillerString += "\n";
    }
}
//==========================================================
