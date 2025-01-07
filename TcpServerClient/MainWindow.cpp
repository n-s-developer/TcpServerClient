#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButtonStartServer_clicked()
{
    bool success = false;

    bool result = server.StartServer(ui->LineEditServerIpAddr->text().toStdString(), ui->LineEditServerPort->text().toInt(&success) );


    if (result == true)
    {
        ui->labelResult->setText("Successfuly Start Server");
    }

}

