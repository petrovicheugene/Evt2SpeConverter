//========================================================
#ifndef ZEVT2SPECONVERTER_H
#define ZEVT2SPECONVERTER_H
//========================================================
#include "ZEvtSpectrumDataExtractor.h"
#include <QObject>
//========================================================
class ZEvt2SpeConverter : public QObject
{
    Q_OBJECT
public:
    explicit ZEvt2SpeConverter(QObject* parent = nullptr);
    explicit ZEvt2SpeConverter(ZEvtSpectrumDataExtractor* converter,
                               QObject* parent = nullptr);

    void zp_setSpectrumDataExtractor(ZEvtSpectrumDataExtractor* extractor);
    void zp_convertFiles(const QStringList& filePathList);
    QString zp_errorString() const;

signals:

private:
    //VARS
    ZEvtSpectrumDataExtractor* zv_spectrumDataExtractor;
    QString zv_errorString;
    int zv_speHeaderLineNumber;

    //FUNCS
    bool zh_convertFile(const QString& evtFilePath);
    void zh_createSpeHeader(QStringList& headerStringList) const;
    QString zh_targetFile(const QString& evtFilePath);
};
//========================================================
#endif // ZEVT2SPECONVERTER_H
