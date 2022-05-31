#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isStart = false;
    numberOfBytes = 0;
    m_serialPort = nullptr;
    settings = new mySetting(this, "Settings");

    ///Инициализация ComboBox
    setupComboBox();
    getSettingRS232();

}

MainWindow::~MainWindow()
{
    saveSettingRS232();
    m_serialPort->deleteLater();
    m_serialPort = nullptr;
    settings = nullptr;
    delete ui;
}

void MainWindow::on_buttonStartStop_clicked()
{
    if(isStart != true){
        QSerialPort *mySerialPort = new QSerialPort(ui->lineEditSerialPort->text());
        mySerialPort->open(QIODevice::ReadWrite);
        setupSettingRS232(mySerialPort);
        ui->labelReport->setText("Отправка: на порт- " + ui->lineEditSerialPort->text());
        m_serialPort = new workOnSerialPort(mySerialPort, this);
        setConnect();
        ui->buttonStartStop->setText("Закрыть порт");
        isStart = true;
    }else{
        unConnect();
        m_serialPort->deleteLater();
        m_serialPort = nullptr;
        ui->buttonStartStop->setText("Открыть порт");
        isStart = false;
        ui->listWidgetRecived->clear();
        ui->listWidgetReport->clear();
    }
}


void MainWindow::setConnect()
{
    connect(m_serialPort, &workOnSerialPort::reportMessage, this, &MainWindow::onReportMessage);
    connect(m_serialPort, &workOnSerialPort::recivedMessage, this, &MainWindow::onRecivedMessage);
    connect(this, &MainWindow::reportMessagetoCan, m_serialPort, &workOnSerialPort::writeDataToPort);
}

void MainWindow::unConnect()
{
    disconnect(m_serialPort, &workOnSerialPort::reportMessage, this, &MainWindow::onReportMessage);
    disconnect(m_serialPort, &workOnSerialPort::recivedMessage, this, &MainWindow::onRecivedMessage);
    disconnect(this, &MainWindow::reportMessagetoCan, m_serialPort, &workOnSerialPort::writeDataToPort);
}

void MainWindow::onReportMessage(QString str)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QDateTime::currentDateTime().toString("ss: ") + str);
    item->setBackground(QBrush(QColor(160,255,160,255)));
    ui->listWidgetReport->addItem(item);
    ui->listWidgetReport->scrollToBottom();
}

void MainWindow::onRecivedMessage(QString str)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QDateTime::currentDateTime().toString("ss: ") + str);
    item->setBackground(QBrush(QColor(34,182,171,255)));
    ui->listWidgetRecived->addItem(item);
    ui->listWidgetRecived->scrollToBottom();
}

void MainWindow::setupSettingRS232(QSerialPort *mySerialPort)
{
    qDebug() << "setupSettingRS232";
    qDebug() << "------------------------------";
    mySerialPort->setParent(this);
    switch (ui->comboBoxBaudRate->currentIndex()) {
    case 0:
        mySerialPort->setBaudRate(QSerialPort::Baud1200);
        qDebug() <<"setBaudRate(QSerialPort::Baud1200);";
        break;
    case 1:
        mySerialPort->setBaudRate(QSerialPort::Baud2400);
        qDebug() <<"setBaudRate(QSerialPort::Baud2400)";
        break;
    case 2:
        mySerialPort->setBaudRate(QSerialPort::Baud4800);
        qDebug() <<"setBaudRate(QSerialPort::Baud4800)";
        break;
    case 3:
        mySerialPort->setBaudRate(QSerialPort::Baud9600);
        qDebug() <<"setBaudRate(QSerialPort::Baud9600)";
        break;
    case 4:
        mySerialPort->setBaudRate(QSerialPort::Baud19200);
        qDebug() <<"setBaudRate(QSerialPort::Baud19200)";
        break;
    case 5:
        mySerialPort->setBaudRate(QSerialPort::Baud38400);
        qDebug() <<"setBaudRate(QSerialPort::Baud38400)";
        break;
    case 6:
        mySerialPort->setBaudRate(QSerialPort::Baud57600);
        qDebug() <<"setBaudRate(QSerialPort::Baud57600)";
        break;
    case 7:
        mySerialPort->setBaudRate(QSerialPort::Baud115200);
        qDebug() <<"setBaudRate(QSerialPort::Baud115200)";
        break;
    case 8:
        mySerialPort->setBaudRate(QSerialPort::UnknownBaud);
        qDebug() << "setBaudRate(QSerialPort::UnknownBaud)";
        break;
    default:
        mySerialPort->setBaudRate(QSerialPort::Baud115200);
        qDebug() << "->setBaudRate(QSerialPort::Baud115200)";
    }

    switch (ui->comboBoxDataBits->currentIndex()) {
    case 0:
        mySerialPort->setDataBits(QSerialPort::Data5);
        qDebug() <<"setDataBits(QSerialPort::Data5)";
        break;
    case 1:
        mySerialPort->setDataBits(QSerialPort::Data6);
        qDebug() <<"setDataBits(QSerialPort::Data6)";
        break;
    case 2:
        mySerialPort->setDataBits(QSerialPort::Data7);
        qDebug() <<"setDataBits(QSerialPort::Data7)";
        break;
    case 3:
        mySerialPort->setDataBits(QSerialPort::Data8);
        qDebug() <<"setDataBits(QSerialPort::Data8)";
        break;
    case 4:
        mySerialPort->setDataBits(QSerialPort::UnknownDataBits);
        qDebug() <<"setDataBits(QSerialPort::UnknownDataBits)";
        break;
    default:
        mySerialPort->setDataBits(QSerialPort::Data8);
        qDebug() <<"setDataBits(QSerialPort::Data8)";
    }

    switch (ui->comboBoxParity->currentIndex()) {
    case 0:
        mySerialPort->setParity(QSerialPort::NoParity);
        qDebug() <<"setParity(QSerialPort::NoParity);";
        break;
    case 1:
        mySerialPort->setParity(QSerialPort::EvenParity);
        qDebug() <<"setParity(QSerialPort::EvenParity)";
        break;
    case 2:
        mySerialPort->setParity(QSerialPort::OddParity);
        qDebug() <<"setParity(QSerialPort::OddParity)";
        break;
    case 3:
        mySerialPort->setParity(QSerialPort::SpaceParity);
        qDebug() <<"setParity(QSerialPort::SpaceParity)";
        break;
    case 4:
        mySerialPort->setParity(QSerialPort::MarkParity);
        qDebug() <<"setParity(QSerialPort::MarkParity)";
        break;
    case 5:
        mySerialPort->setParity(QSerialPort::UnknownParity);
        qDebug() <<"setParity(QSerialPort::UnknownParity)";
        break;
    default:
        mySerialPort->setParity(QSerialPort::OddParity);
        qDebug() <<"setParity(QSerialPort::OddParity)";
    }

    switch (ui->comboBoxStopBits->currentIndex()) {
    case 0:
        mySerialPort->setStopBits(QSerialPort::OneStop);
        qDebug() <<"setStopBits(QSerialPort::OneStop)";
        break;
    case 1:
        mySerialPort->setStopBits(QSerialPort::OneAndHalfStop);
        qDebug() <<"setStopBits(QSerialPort::OneAndHalfStop)";
        break;
    case 2:
        mySerialPort->setStopBits(QSerialPort::TwoStop);
        qDebug() <<"setStopBits(QSerialPort::TwoStop)";
        break;
    case 3:
        mySerialPort->setStopBits(QSerialPort::UnknownStopBits);
        qDebug() <<"setStopBits(QSerialPort::UnknownStopBits)";
        break;
    default:
        mySerialPort->setStopBits(QSerialPort::OneStop);
        qDebug() <<"setStopBits(QSerialPort::OneStop)";

    }

    switch (ui->comboBoxFlowControl->currentIndex()) {
    case 0:
        mySerialPort->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() <<"setFlowControl(QSerialPort::NoFlowControl)";
        break;
    case 1:
        mySerialPort->setFlowControl(QSerialPort::HardwareControl);
        qDebug() <<"setFlowControl(QSerialPort::HardwareControl)";
        break;
    case 2:
        mySerialPort->setFlowControl(QSerialPort::SoftwareControl);
        qDebug() <<"setFlowControl(QSerialPort::SoftwareControl)";
        break;
    case 3:
        mySerialPort->setFlowControl(QSerialPort::UnknownFlowControl);
        qDebug() <<"setFlowControl(QSerialPort::UnknownFlowControl)";
        break;
    default:
        mySerialPort->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() <<"setFlowControl(QSerialPort::NoFlowControl)";
    }

    qDebug() << "------------------------------";

}

void MainWindow::setupComboBox()
{
    QStringList boudRate = { "Baud1200",
        "Baud2400",
        "Baud4800",
        "Baud9600",
        "Baud19200",
        "Baud38400",
        "Baud57600",
        "Baud115200",
        "UnknownBaud"};
    ui->comboBoxBaudRate->addItems(boudRate);

    QStringList dataBits = {"Data5",
        "Data6",
        "Data7",
        "Data8",
        "UnknownDataBits"};
    ui->comboBoxDataBits->addItems(dataBits);

    QStringList parity = {"NoParity",
        "EvenParity",
        "OddParity",
        "SpaceParity",
        "MarkParity",
        "UnknownParity"};
    ui->comboBoxParity->addItems(parity);

    QStringList stopBits = {"OneStop",
        "OneAndHalfStop",
        "TwoStop",
        "UnknownStopBits"};
    ui->comboBoxStopBits->addItems(stopBits);

    QStringList flowControl = {"NoFlowControl",
        "HardwareControl",
        "SoftwareControl",
        "UnknownFlowControl"};
    ui->comboBoxFlowControl->addItems(flowControl);

    QStringList numberOfBytes = {"0","1","2","3","4","5","6","7","8","9"};

    ui->comboBoxNumberOfBytes->addItems(numberOfBytes);

}

void MainWindow::saveSettingRS232()
{
    settings->saveAdressCOM(ui->lineEditSerialPort->text());
    settings->setComboBoxBaudRate(ui->comboBoxBaudRate->currentIndex());
    settings->setComboBoxDataBits(ui->comboBoxDataBits->currentIndex());
    settings->setComboBoxParity(ui->comboBoxParity->currentIndex());
    settings->setComboBoxStopBits(ui->comboBoxStopBits->currentIndex());
    settings->setComboBoxFlowControl(ui->comboBoxFlowControl->currentIndex());
}

void MainWindow::getSettingRS232()
{
    ui->lineEditSerialPort->setText(settings->getAdressCOM());
    ui->comboBoxBaudRate->setCurrentIndex(settings->getComboBoxBaudRate());
    ui->comboBoxDataBits->setCurrentIndex(settings->getComboBoxDataBits());
    ui->comboBoxParity->setCurrentIndex(settings->getComboBoxParity());
    ui->comboBoxStopBits->setCurrentIndex(settings->getComboBoxStopBits());
    ui->comboBoxFlowControl->setCurrentIndex(settings->getComboBoxFlowControl());
}



void MainWindow::on_comboBoxNumberOfBytes_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->lineEditbyte->setEnabled(false);
        ui->lineEditbyte_2->setEnabled(false);
        ui->lineEditbyte_3->setEnabled(false);
        ui->lineEditbyte_4->setEnabled(false);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 0;
        break;
    case 1:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(false);
        ui->lineEditbyte_3->setEnabled(false);
        ui->lineEditbyte_4->setEnabled(false);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 1;
        break;
    case 2:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(false);
        ui->lineEditbyte_4->setEnabled(false);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 2;
        break;
    case 3:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(false);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 3;
        break;
    case 4:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 4;
        break;
    case 5:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(true);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 5;
        break;
    case 6:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(true);
        ui->lineEditbyte_6->setEnabled(true);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 6;
        break;
    case 7:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(true);
        ui->lineEditbyte_6->setEnabled(true);
        ui->lineEditbyte_7->setEnabled(true);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 7;
        break;
    case 8:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(true);
        ui->lineEditbyte_6->setEnabled(true);
        ui->lineEditbyte_7->setEnabled(true);
        ui->lineEditbyte_8->setEnabled(true);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 8;
        break;
    case 9:
        ui->lineEditbyte->setEnabled(true);
        ui->lineEditbyte_2->setEnabled(true);
        ui->lineEditbyte_3->setEnabled(true);
        ui->lineEditbyte_4->setEnabled(true);
        ui->lineEditbyte_5->setEnabled(true);
        ui->lineEditbyte_6->setEnabled(true);
        ui->lineEditbyte_7->setEnabled(true);
        ui->lineEditbyte_8->setEnabled(true);
        ui->lineEditbyte_9->setEnabled(true);
        numberOfBytes = 9;
        break;
    default:
        ui->lineEditbyte->setEnabled(false);
        ui->lineEditbyte_2->setEnabled(false);
        ui->lineEditbyte_3->setEnabled(false);
        ui->lineEditbyte_4->setEnabled(false);
        ui->lineEditbyte_5->setEnabled(false);
        ui->lineEditbyte_6->setEnabled(false);
        ui->lineEditbyte_7->setEnabled(false);
        ui->lineEditbyte_8->setEnabled(false);
        ui->lineEditbyte_9->setEnabled(false);
        numberOfBytes = 0;
    }
}


void MainWindow::on_pushButtonSendMessage_clicked()
{
    bool ok;
    int digit;
    QByteArray array;
    switch (numberOfBytes) {
    case 0:
        break;
    case 1:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 2:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 3:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        qDebug() << "1: " << QString::number(digit,16);
        qDebug() << "1: " << array.toHex().toUpper().data();

        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        qDebug() << "2: " << QString::number(digit,16);
        qDebug() << "2: " << array.toHex().toUpper().data();

        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        qDebug() << "3: " << QString::number(digit,16);
        qDebug() << "3: " << array.toHex().toUpper().data();

        emit reportMessagetoCan(array);

        qDebug() << "Repotr: " << array.toHex().toUpper().data();
        break;
    case 4:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 5:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_5->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 6:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_5->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_6->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 7:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_5->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_6->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_7->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 8:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_5->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_6->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_7->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_8->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    case 9:
        digit = ui->lineEditbyte->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_2->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_3->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_4->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_5->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_6->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_7->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_8->text().toInt(&ok,16);
        array.append(digit);
        digit = ui->lineEditbyte_9->text().toInt(&ok,16);
        array.append(digit);
        emit reportMessagetoCan(array);
        break;
    }
}
