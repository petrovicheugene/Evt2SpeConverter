//==========================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//==========================================================
#include "ZBaseMainWindow.h"
//==========================================================
class ZEvt2SpeSettingsWidget;
//==========================================================
class MainWindow : public ZBaseMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void zh_outputMessageToStstusBar(QtMsgType type, const QString& msg);

private:
    // VARS
    ZEvt2SpeSettingsWidget* zv_evt2SpeSettingsWidget;

    //FUNCS
    void zh_createComponents();
    void zh_createConnections();
};
//==========================================================
#endif // MAINWINDOW_H
