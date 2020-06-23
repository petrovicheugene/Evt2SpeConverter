//========================================================
#ifndef ZEVT2SPECONVERTER_H
#define ZEVT2SPECONVERTER_H
//========================================================
#include "ZEvt2SpeDataConverter.h"
#include <QObject>
//========================================================
class ZEvt2SpeConverter : public QObject
{
    Q_OBJECT
public:
    explicit ZEvt2SpeConverter(QObject* parent = nullptr);
    explicit ZEvt2SpeConverter(ZEvt2SpeDataConverter* converter,
                               QObject* parent = nullptr);

    void zp_setDataConverter(ZEvt2SpeDataConverter* converter);
    void zp_convertFiles(const QStringList& filePathList);
    QString zp_errorString() const;

signals:

private:
    //VARS
    ZEvt2SpeDataConverter* zv_converter;
    QString zv_errorString;
    //FUNCS
    bool zh_convertFile(const QString& evtFilePath);
};
//========================================================
#endif // ZEVT2SPECONVERTER_H
