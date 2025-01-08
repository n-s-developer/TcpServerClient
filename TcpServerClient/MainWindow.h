#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ServerIfc.h>
#include <ServerCls.h>
#include <ClientIfc.h>
#include <ClientCls.h>
#include <string>
#include <thread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PushButtonStartServer_clicked();

    void on_PushButtonBindServer_clicked();

    void on_PushButtonStartListening_clicked();

    void on_PushButtonStartClient_clicked();

    void on_PushButtonConnectToServer_clicked();

    void on_PushButtonCloseServer_clicked();

    void on_PushButtonSendServerMsg_clicked();

    void on_PushButtonSendClientMsg_clicked();

private:
    Ui::MainWindow *ui;
    // ServerIfc* server = new ServerCls();
    // ClientIfc* client = new ClientCls();

    ServerCls* server = new ServerCls();
    ClientCls* client = new ClientCls();

    QTimer *timer = new QTimer();

private slots:
    void onTimeout();

};
#endif // MAINWINDOW_H
