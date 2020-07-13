//==========================================================
#include "ZEvtContextConverterSettingsManager.h"

#include <QSettings>
//==========================================================
ZEvtContextConverterSettingsManager::ZEvtContextConverterSettingsManager(QObject *parent) : QObject(parent)
{
    zv_outputFolderPathKey = "outputFolderPath";
    zv_outputFileTemplateKey = "outputFileTemplate";

    zv_settings = new QSettings("TechnoAnalyt", "Evt2SpeContextConverter");
}
//==========================================================
ZEvtContextConverterSettingsManager::~ZEvtContextConverterSettingsManager()
{
    while (!zv_settings->group().isEmpty())
    {
        zv_settings->endGroup();
    }
}
//==========================================================
QString ZEvtContextConverterSettingsManager::zp_outputFolderPath() const
{
    return zv_settings->value(zv_outputFolderPathKey).toString();
}
//==========================================================
void ZEvtContextConverterSettingsManager::zp_setOutputFolderPath(
    const QString& path)
{
    zv_settings->setValue(zv_outputFolderPathKey, path);
}
//==========================================================
QString ZEvtContextConverterSettingsManager::zp_outputFileNameTemplate() const
{
    return zv_settings->value(zv_outputFileTemplateKey).toString();
}
//==========================================================
void ZEvtContextConverterSettingsManager::zp_setOutputFileNameTemplate(
    const QString& templ)
{
    zv_settings->setValue(zv_outputFileTemplateKey, templ);
}
//==========================================================
