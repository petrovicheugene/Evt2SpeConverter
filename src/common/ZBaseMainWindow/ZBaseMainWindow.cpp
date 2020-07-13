//======================================================
#include "ZBaseMainWindow.h"
#include "ZHelpBrowser.h"
#include "ZTranslatorManager.h"

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QDebug>
#include <QDir>
#include <QDockWidget>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>
#include <QWidgetAction>
//======================================================
ZBaseMainWindow::ZBaseMainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle(qApp->applicationDisplayName());

    ZTranslatorManager languageManager;
    languageManager.zp_installTranslatorsToApplication();

    zv_helpBrowser = nullptr;
    // Menus
    zv_languageMenu = new QMenu;
    zv_languageMenu->setIcon(QIcon(":/images/ZImages/earthGlobe-16.png"));
    zv_dockWidgetMenu = nullptr;

    zh_createBaseActions();
    zh_createBaseConnections();
}
//======================================================
void ZBaseMainWindow::zp_handleStandardLogMessage(QtMsgType type,
                                                  const QMessageLogContext& context,
                                                  const QString& msg) const
{
    // send message to ApplicationLogger
    emit zg_standardLogMessage(type, msg);
}
//======================================================
void ZBaseMainWindow::zh_createBaseActions()
{
    zv_helpAction = new QAction(tr("Help"), this);
    zv_aboutAction = new QAction(tr("About"), this);
    zv_aboutQtAction = new QAction(tr("About Qt"), this);
    zv_exitAction = new QAction(tr("Exit"), this);
}
//======================================================
void ZBaseMainWindow::zh_createBaseConnections()
{
    connect(zv_helpAction, &QAction::triggered, this, &ZBaseMainWindow::zh_help);
    connect(zv_aboutAction, &QAction::triggered, this, &ZBaseMainWindow::zh_about);
    connect(zv_aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(zv_exitAction, &QAction::triggered, this, &ZBaseMainWindow::zh_exit);
    connect(zv_languageMenu, &QMenu::aboutToShow, this, &ZBaseMainWindow::zh_fillLanguageMenu);
}
//==============================================
void ZBaseMainWindow::zh_saveSettings() const
{
    QSettings settings;
    settings.setValue(zv_appGeometryString, saveGeometry());
    settings.setValue(zv_appStateString, saveState());
}
//==============================================
void ZBaseMainWindow::zh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value(zv_appGeometryString).toByteArray());
    restoreState(settings.value(zv_appStateString).toByteArray());
}
//======================================================
void ZBaseMainWindow::zh_help()
{
    if (zv_helpBrowser == nullptr)
    {
        QUrl source = QUrl(".htm");
        QStringList searchList;

        QDir dir = QApplication::applicationDirPath();
        dir.cd("Doc");
        searchList << dir.absolutePath(); // << ":/docs"; Streams.files
        dir.cd(QString("%1.files").arg(qApp->property("glAppExeBaseName").toString()));
        searchList << dir.absolutePath() << ":/docs";

        zv_helpBrowser = ZHelpBrowser::zp_instance(searchList, source, centralWidget());
        zv_helpBrowser->setAttribute(Qt::WA_GroupLeader);
        zv_helpBrowser->show();
    } else if (!zv_helpBrowser->isVisible())
    {
        zv_helpBrowser->setVisible(true);
    }
}
//======================================================
void ZBaseMainWindow::zh_about()
{
    QString title = tr("About %1").arg(qApp->applicationDisplayName());
    QString description = qApp->property("appDescription").toString();
    QString htmlText = QString("<table border=0 cellspacing = 15>"
                               "<tr>"
                               "<td align = left><img src=:/images/appIcon.png></td>"
                               "<td align = left><h1 align = center>%1</h1>"
                               "</td>"
                               "</tr>"
                               "</table>"
                               "<p>%6 - %2</p>"
                               "<p>%3</p>"
                               "<p>%7<br> "
                               "Company website: <a href=\"http://%8/\">%8</a><br>"
                               "%5: %4<br>"
                               "Author's email: <a "
                               "href=mailto:petrovich.eugene@gmail.com?Subject=My%20Subject>"
                               "petrovich.eugene@gmail.com</a></p>")
                           .arg(qApp->applicationDisplayName(),
                                qApp->applicationVersion(),
                                description,
                                tr("Eugene Petrovich"),
                                tr("Author"),
                                tr("Version"),
                                qApp->property("appCopyright").toString(),
                                qApp->organizationDomain(),
                                qApp->property("appCopyright").toString());

    QMessageBox::about(centralWidget(), title, htmlText);
}
//======================================================
void ZBaseMainWindow::zh_exit()
{
    close();
}
//======================================================
bool ZBaseMainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (!obj || !event)
    {
        return QMainWindow::eventFilter(obj, event);
    }

    //
    if (event->type() == QEvent::MouseButtonRelease
        && obj->metaObject()->className() == QString("QMenu"))
    {
        QMenu* menu = qobject_cast<QMenu*>(obj);
        if (!menu)
        {
            return QMainWindow::eventFilter(obj, event);
        }

        QAction* action = menu->activeAction();
        if (!action)
        {
            return QMainWindow::eventFilter(obj, event);
        }

        action->toggle();

        return true;
    }

    return QMainWindow::eventFilter(obj, event);
}
//======================================================
void ZBaseMainWindow::zh_appendActionsToMenu(QMenu* menu, int menuIdentifier)
{
    if (menuIdentifier == MI_FILE)
    {
        if (!menu->actions().isEmpty())
        {
            menu->addSeparator();
        }

        // language
        ZTranslatorManager translatorManager;
        QString currentLanguage;
        bool ok = false;
        translatorManager.zp_currentLanguageName(currentLanguage, &ok);
        if (ok)
        {
            zv_languageMenu->setTitle(currentLanguage);
        }

        zv_languageMenu->setToolTip(tr("Application language"));

        menu->addMenu(zv_languageMenu);

        menu->addAction(zv_exitAction);
        menu->addSeparator();
        return;
    }

    if (menuIdentifier == MI_ACTIONS)
    {
        if (!menu->actions().isEmpty())
        {
            menu->addSeparator();
        }

        return;
    }

    if (menuIdentifier == MI_VIEW)
    {
        if (!menu->actions().isEmpty())
        {
            menu->addSeparator();
        }

        QObjectList childList = this->children();
        foreach (QObject* object, childList)
        {
            if (object->metaObject()->className() == QString("QDockWidget"))
            {
                if (!zv_dockWidgetMenu)
                {
                    zv_dockWidgetMenu = new QMenu;
                    zv_dockWidgetMenu->setTitle(tr("Dockwidgets"));
                    zv_dockWidgetMenu->installEventFilter(this);
                    menu->addMenu(zv_dockWidgetMenu);
                }

                QDockWidget* dock = dynamic_cast<QDockWidget*>(object);
                QAction* viewAction = new QAction(zv_dockWidgetMenu);
                viewAction->setCheckable(true);
                viewAction->setChecked(dock->isVisible());
                viewAction->setText(dock->windowTitle());
                connect(dock, &QDockWidget::visibilityChanged, viewAction, &QAction::setChecked);
                connect(viewAction, &QAction::toggled, dock, &QDockWidget::setVisible);
                zv_dockWidgetMenu->addAction(viewAction);
            }
        }

        return;
    }

    if (menuIdentifier == MI_HELP)
    {
        if (!menu->actions().isEmpty())
        {
            menu->addSeparator();
        }

        menu->addAction(zv_helpAction);
        menu->addAction(zv_aboutAction);
        menu->addAction(zv_aboutQtAction);

        menu->addSeparator();
        return;
    }
}
//======================================================
void ZBaseMainWindow::zh_fillLanguageMenu()
{
    zv_languageMenu->clear();
    ZTranslatorManager translatorManager;
    QStringList availableLanguageNameList;
    translatorManager.zp_availableLanguageNameList(availableLanguageNameList);

    foreach (QString languageName, availableLanguageNameList)
    {
        QAction* action = zv_languageMenu->addAction(languageName);
        connect(action, &QAction::triggered, this, &ZBaseMainWindow::zh_appLanguageControl);
    }
}
//======================================================
void ZBaseMainWindow::zh_appLanguageControl()
{
    if (!sender())
    {
        return;
    }

    QAction* action = dynamic_cast<QAction*>(sender());
    if (!action)
    {
        return;
    }

    ZTranslatorManager translatorManager;
    QString currentLanguageName;
    bool ok = false;
    translatorManager.zp_currentLanguageName(currentLanguageName, &ok);

    if (ok && action->text() == currentLanguageName)
    {
        return;
    }

    ok = false;
    translatorManager.zp_setApplicationLanguage(action->text(), &ok);
    QString msg;
    if (ok)
    {
        msg = tr("The language of application has been changed.\n"
                 "In order for the changes to take effect, please restart the application.");
    } else
    {
        msg = translatorManager.zp_lastError().isEmpty() ? tr("Unknown language settings error.")
                                                         : translatorManager.zp_lastError();
    }

    QString title = tr("Language settings");
    QMessageBox::information(this, title, msg, QMessageBox::Ok);
}
//======================================================
