//==========================================================
#include "MainWindow.h"
#include "ZEvt2SpeSettingsWidget.h"
#include <QApplication>
#include <QStatusBar>
//==========================================================
MainWindow::MainWindow(QWidget* parent) : ZBaseMainWindow(parent)
{
    setWindowTitle(qApp->applicationDisplayName());

    zh_createComponents();
    zh_createConnections();
    zh_restoreSettings();
}
//==========================================================
MainWindow::~MainWindow()
{
    zh_saveSettings();
}
//==========================================================
void MainWindow::zh_createComponents()
{
    zv_evt2SpeSettingsWidget = new ZEvt2SpeSettingsWidget;
    setCentralWidget(zv_evt2SpeSettingsWidget);
    statusBar();
}
//==========================================================
void MainWindow::zh_createConnections()
{
    connect(zv_evt2SpeSettingsWidget,
            &ZEvt2SpeSettingsWidget::zg_invokeClosing,
            this,
            &MainWindow::close);
    connect(this,
            &MainWindow::zg_standardLogMessage,
            this,
            &MainWindow::zh_outputMessageToStstusBar);
}
//==========================================================
void MainWindow::zh_outputMessageToStstusBar(QtMsgType type, const QString& msg)
{
    statusBar()->showMessage(msg, 5000);
}
//==========================================================
