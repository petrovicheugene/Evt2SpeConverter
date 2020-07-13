//==========================================================
#ifndef ZEVTCONTEXTCONVERTERSETTINGSMANAGER_H
#define ZEVTCONTEXTCONVERTERSETTINGSMANAGER_H
//==========================================================
#include <QObject>
//==========================================================
class QSettings;
//==========================================================
class ZEvtContextConverterSettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit ZEvtContextConverterSettingsManager(QObject* parent = nullptr);
    ~ZEvtContextConverterSettingsManager();
    QString zp_outputFolderPath() const;
    void zp_setOutputFolderPath(const QString& path);
    QString zp_outputFileNameTemplate() const;
    void zp_setOutputFileNameTemplate(const QString& templ);

signals:

private:
    QSettings* zv_settings;
    QString zv_outputFolderPathKey;
    QString zv_outputFileTemplateKey;
};
//==========================================================
#endif // ZEVTCONTEXTCONVERTERSETTINGSMANAGER_H
