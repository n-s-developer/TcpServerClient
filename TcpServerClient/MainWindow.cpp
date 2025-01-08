#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Periyodik olarak çağrılacak fonksiyonu bağlantılıyoruz
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    // Timer'ı başlatıyoruz (1000 ms = 1 saniye)
    timer->start(1000); // her 1 saniyede bir 'onTimeout' fonksiyonu çalışacak
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButtonStartServer_clicked()
{
   bool success = false;

    bool result = server->Start(ui->LineEditServerPort->text().toInt(&success), ui->LineEditServerBindingIp->text().toStdString() );

    if (result == true)
    {
        ui->labelResult->setText("Successfuly Start Server");
    }
    else
    {
        ui->labelResult->setText("Start Server Failed");
    }
}


void MainWindow::on_PushButtonBindServer_clicked()
{
    bool result = server->Bind();

    if (result == true)
    {
        ui->labelResult->setText("Successfuly Bind Server");
    }
    else
    {
        ui->labelResult->setText("Bind Server Failed");
    }
}


void MainWindow::on_PushButtonStartListening_clicked()
{
    bool result = server->Listen();

    if (result == true)
    {
        ui->labelResult->setText("Successfuly Start Listening");

        /*std::thread ListenThread([] {
            ui->textBrowserServerScreen->insertPlainText(server->);
        });

        ListenThread.join();*/
    }
    else
    {
        ui->labelResult->setText("Server Listening Failed");
    }
}


void MainWindow::on_PushButtonStartClient_clicked()
{
    bool result = client->Start();


    if (result == true)
    {
        ui->labelResult->setText("Successfuly Start Client");
    }
    else
    {
        ui->labelResult->setText("Start Client Failed");
    }
}


void MainWindow::on_PushButtonConnectToServer_clicked()
{
    bool success = false;

    bool result = client->ConnectToServer(ui->LineEditServerPort->text().toInt(&success), ui->LineEditServerBindingIp->text().toStdString() );

    if ( (result == true) &&
         (success == true) )
    {
        ui->labelResult->setText("Successfuly Connect To Server");
    }
    else
    {
        ui->labelResult->setText("Connect To Server is failed");
    }
}


void MainWindow::on_PushButtonCloseServer_clicked()
{
    server->Close();
}


void MainWindow::on_PushButtonSendServerMsg_clicked()
{
    bool result = server->SendMsg(ui->lineEditServerMsg->text().toStdString() );

    if (result == true)
    {
        ui->labelResult->setText("Successfuly SEND To Client");
    }
    else
    {
        ui->labelResult->setText("SEND to Client Failed");
    }
}


void MainWindow::on_PushButtonSendClientMsg_clicked()
{
    bool result = client->SendMsg(ui->lineEditClientMsg->text().toStdString() );

    if (result == true)
    {
        ui->labelResult->setText("Successfuly SEND To Server");
    }
    else
    {
        ui->labelResult->setText("SEND to Server Failed");
    }
}

void MainWindow::onTimeout()
{
    qDebug() << "Periyodik fonksiyon çalıştı!";

    ui->labelResult->setText(QString::fromStdString(server->Message) );
}
