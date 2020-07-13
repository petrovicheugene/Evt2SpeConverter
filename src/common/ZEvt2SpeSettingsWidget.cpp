//======================================================
#include "ZEvt2SpeSettingsWidget.h"
#include "ZEvtContextConverterSettingsManager.h"
#include "ZWinPathValidator.h"

#include <QAction>
#include <QApplication>
#include <QContextMenuEvent>
#include <QDebug>
#include <QDialogButtonBox>
#include <QEvent>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStandardPaths>
#include <QVBoxLayout>

//======================================================
ZEvt2SpeSettingsWidget::ZEvt2SpeSettingsWidget(QWidget* parent) : QWidget(parent)
{
    zh_createComponents();
    zh_createConnections();
    zh_restoreDataToSettings();
}
//======================================================
void ZEvt2SpeSettingsWidget::zp_setVariableManager(ZVariableManager* variableManager)
{
    if (zv_variableManager)
    {
        delete zv_variableManager;
    }
    zv_variableManager = variableManager;
}
//======================================================
bool ZEvt2SpeSettingsWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent* contextEvent = static_cast<QContextMenuEvent*>(event);
        if (obj == zv_outputFileNameTemplateLineEdit)
        {
            QMenu* menu = zv_outputFileNameTemplateLineEdit->createStandardContextMenu();
            menu->addSeparator();

            QMenu* insertVarMenu = new QMenu(tr("Insert variable"));
            insertVarMenu->addActions(
                zh_createVarInsertionActions(zv_variableManager->zp_variableList()));

            menu->addMenu(insertVarMenu);
            menu->exec(contextEvent->globalPos());
            return true;
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_createComponents()
{
    zv_variableManager = new ZVariableManager(this);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QFormLayout* controlLayout = new QFormLayout;
    mainLayout->addLayout(controlLayout);

    // output folder path
    zv_outputPathLineEdit = new QLineEdit;
    zv_outputPathLineEdit->installEventFilter(this);

    zv_browseButton = new QPushButton;
    zv_browseButton->setText(tr("Browse..."));
    QHBoxLayout* lineLayout = new QHBoxLayout;
    lineLayout->setMargin(0);
    lineLayout->addWidget(zv_outputPathLineEdit);
    lineLayout->addWidget(zv_browseButton);
    controlLayout->addRow(tr("Output folder:"), lineLayout);

    // output name template
    zv_outputFileNameTemplateLineEdit = new QLineEdit;
    zv_outputFileNameTemplateLineEdit->installEventFilter(this);
    controlLayout->addRow(tr("Output file name template:"), zv_outputFileNameTemplateLineEdit);

    // basement
    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    mainLayout->addWidget(buttonBox);
    zv_defaultOutputPathButton = new QPushButton;
    zv_defaultOutputPathButton->setText(tr("By default"));
    zv_saveButton = new QPushButton;
    zv_saveButton->setText(tr("Save"));
    zv_closelButton = new QPushButton;
    zv_closelButton->setText(tr("Close"));
    buttonBox->addButton(zv_defaultOutputPathButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(zv_saveButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(zv_closelButton, QDialogButtonBox::ActionRole);
}
//======================================================
QList<QAction*> ZEvt2SpeSettingsWidget::zh_createVarInsertionActions(
    const QStringList& variableList) const
{
    QList<QAction*> actions;
    foreach (QString var, variableList)
    {
        QAction* action = new QAction(var);
        action->setData(QVariant("%" + var + "%"));
        connect(action,
                &QAction::triggered,
                this,
                &ZEvt2SpeSettingsWidget::zh_insertNameTemplateVariable);
        actions.append(action);
    }

    return actions;
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_createConnections()
{
    connect(zv_browseButton,
            &QPushButton::clicked,
            this,
            &ZEvt2SpeSettingsWidget::zh_onBrowseButton);
    connect(zv_defaultOutputPathButton,
            &QPushButton::clicked,
            this,
            &ZEvt2SpeSettingsWidget::zh_onDefaultOutputPathButtonClick);
    connect(zv_saveButton,
            &QPushButton::clicked,
            this,
            &ZEvt2SpeSettingsWidget::zh_onSaveButtonClick);
    connect(zv_closelButton,
            &QPushButton::clicked,
            this,
            &ZEvt2SpeSettingsWidget::zh_onCloseButtonClick);
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_onBrowseButton()
{
    QString currentDirString = zh_currentDir();
    QString path = QFileDialog::getExistingDirectory(this, tr("Folder selection"), currentDirString);
    if (path.isEmpty())
    {
        return;
    }

    zv_outputPathLineEdit->setText(path);
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_onDefaultOutputPathButtonClick()
{
    zv_outputPathLineEdit->setText(zv_variableManager->zp_defaultOutputPath());
    zv_outputFileNameTemplateLineEdit->setText(zv_variableManager->zp_defaultFileNameTemplate());
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_onSaveButtonClick()
{
    if (!zh_isDataCorrect())
    {
        QString msg = tr("Incorrect data.\n%1").arg(zv_errorString);
        QMessageBox::critical(this, tr("Error"), msg, QMessageBox::Ok);
        return;
    }

    zh_saveDataToSettings();
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_onCloseButtonClick()
{
    emit zg_invokeClosing();
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_insertNameTemplateVariable()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action)
    {
        return;
    }

    zv_outputFileNameTemplateLineEdit->insert(action->data().toString());
}
//======================================================
bool ZEvt2SpeSettingsWidget::zh_isDataCorrect()
{
    bool res = true;
    QString msg;
    zv_errorString.clear();
    // path check

    if (!zh_isOutputPathCorrect(msg))
    {
        zv_errorString += msg + "\n";
        res = false;
    }

    msg.clear();
    if (!zh_isOutputFileNameTemplateCorrect(msg))
    {
        zv_errorString += msg + "\n";
        res = false;
    }

    return res;
}
//======================================================
bool ZEvt2SpeSettingsWidget::zh_isOutputPathCorrect(QString& msg) const
{
    ZWinPathValidator pathValidator;
    ZWinPathValidator::PathType pathType = pathValidator.zp_validatePath(
        zv_outputPathLineEdit->text());
    if (pathType == ZWinPathValidator::PT_INVALID)
    {
        msg = tr("In output folder path: \"%1\"\n").arg(pathValidator.zp_error());
        return false;
    }

    return true;
}
//======================================================
bool ZEvt2SpeSettingsWidget::zh_isOutputFileNameTemplateCorrect(QString& msg) const
{
    if (!zv_variableManager->zp_checkFileNameTemplate(zv_outputFileNameTemplateLineEdit->text()))
    {
        msg = zv_variableManager->zp_error();
        return false;
    }

    return true;
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_restoreDataToSettings()
{
    ZEvtContextConverterSettingsManager manager;
    zv_outputPathLineEdit->setText(manager.zp_outputFolderPath());
    zv_outputFileNameTemplateLineEdit->setText(manager.zp_outputFileNameTemplate());
}
//======================================================
void ZEvt2SpeSettingsWidget::zh_saveDataToSettings() const
{
    ZEvtContextConverterSettingsManager manager;
    manager.zp_setOutputFolderPath(zv_outputPathLineEdit->text());
    manager.zp_setOutputFileNameTemplate(zv_outputFileNameTemplateLineEdit->text());
    qInfo().noquote() << "Data saved";
}
//======================================================
QString ZEvt2SpeSettingsWidget::zh_currentDir() const
{
    if (!zv_outputPathLineEdit->text().isEmpty())
    {
        QFileInfo fileInfo(zv_outputPathLineEdit->text());
        if (fileInfo.isDir() && fileInfo.isAbsolute())
        {
            return zv_outputPathLineEdit->text();
        }
    }

    QString path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).value(0);
    if (path.isEmpty())
    {
        path = QDir::currentPath();
    }

    return path;
}
//======================================================
