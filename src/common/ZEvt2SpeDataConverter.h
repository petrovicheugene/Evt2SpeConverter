//==========================================================
#ifndef ZEVT2SPEDATACONVERTER_H
#define ZEVT2SPEDATACONVERTER_H
//==========================================================
#include <QDataStream>
#include <QObject>
//==========================================================
class ZEvt2SpeDataConverter : public QObject
{
    Q_OBJECT
public:
    typedef qint64 CHANNEL_COUNT_UNIT;
    explicit ZEvt2SpeDataConverter(QObject* parent = nullptr);

    bool zp_convert(QDataStream& srcByteArray, QStringList& speStringList);
    void zp_setByteOrder(QDataStream::ByteOrder byteOrder);
    void zp_setChannelCountShift(CHANNEL_COUNT_UNIT shift);
    void zp_setFillerString(const QString& fillerString);

signals:

private:
    // VARS
    CHANNEL_COUNT_UNIT zv_channelCountSift;
    QDataStream::ByteOrder zv_byteOrder;
    int zv_speHeaderLineNumber;
    QString zv_fillerString;
    // FUNCS
};
//==========================================================
#endif // ZEVT2SPEDATACONVERTER_H
