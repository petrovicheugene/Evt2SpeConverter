//======================================================
#ifndef ZVARIABLEMANAGER_H
#define ZVARIABLEMANAGER_H
//======================================================
#include <QObject>
//======================================================
class ZVariableManager : public QObject
{
    Q_OBJECT
public:
    explicit ZVariableManager(QObject *parent = nullptr);
    QString zp_defaultOutputPath();
    QString zp_defaultFileNameTemplate();
    QStringList zp_variableList() const;
    bool zp_checkFileNameTemplate(const QString& fileNameTemplate);
    QString zp_createFileNameFromTemplate(const QString& fileNameTemplate,
                                          const QString& srcFileName);
    QString zp_error() const;

signals:

private:
    // VARS
    QStringList zv_variables;
    QString zv_defaultOutputPath;
    QString zv_defaultOutputFileNameTemplate;
    QString zv_error;
    // FUNCS
    QString zh_braceVariable(const QString& variable);
};
//======================================================
#endif // ZVARIABLEMANAGER_H
