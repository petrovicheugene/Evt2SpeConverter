//======================================================
#ifndef ZCONVERTATIONSETTINGSWIDGET_H
#define ZCONVERTATIONSETTINGSWIDGET_H
//======================================================
#include <QWidget>

#include "ZVariableManager.h"
//======================================================
class QAction;
class QLineEdit;
class QPushButton;

//======================================================
class ZEvt2SpeSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZEvt2SpeSettingsWidget(QWidget* parent = nullptr);
    void zp_setVariableManager(ZVariableManager* variableManager);

signals:

    void zg_invokeClosing();

private slots:
    void zh_onBrowseButton();
    void zh_onDefaultOutputPathButtonClick();
    void zh_onSaveButtonClick();
    void zh_onCloseButtonClick();
    void zh_insertNameTemplateVariable();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    // VARS
    ZVariableManager* zv_variableManager;
    QLineEdit* zv_outputPathLineEdit;
    QPushButton* zv_browseButton;
    QLineEdit* zv_outputFileNameTemplateLineEdit;
    QPushButton* zv_defaultOutputPathButton;
    QPushButton* zv_defaultOutputFileNameTemplateButton;
    QString zv_errorString;
    QPushButton* zv_saveButton;
    QPushButton* zv_closelButton;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();
    QList<QAction*> zh_createVarInsertionActions(const QStringList& variableList) const;
    bool zh_isDataCorrect();
    bool zh_isOutputPathCorrect(QString& msg) const;
    bool zh_isOutputFileNameTemplateCorrect(QString& msg) const;

    void zh_restoreDataToSettings();
    void zh_saveDataToSettings() const;
    QString zh_currentDir() const;
};
//======================================================
#endif // ZCONVERTATIONSETTINGSWIDGET_H
