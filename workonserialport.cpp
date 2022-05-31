#include "workonserialport.h"

workOnSerialPort::workOnSerialPort( QSerialPort *serialPort, QObject *parent )
    : QObject(parent)
    , m_serialPort(serialPort)
{
    m_data = new QByteArray();


    //    if (m_serialPort->open(QIODevice::ReadWrite)) {
    connect(m_serialPort, &QSerialPort::readyRead, this, &workOnSerialPort::onSerialPortReadyRead);
    myTimer = new QTimer();
    myTimer->setInterval(50);
//    connect(myTimer, &QTimer::timeout, this, &Iocomm1u602::controlPanelStateRequest);

}

workOnSerialPort::~workOnSerialPort()
{
    delete m_data;
    if (m_serialPort != nullptr)
    {
        if (m_serialPort->isOpen())
        {
            m_serialPort->close();
        }
        delete m_serialPort;
        m_serialPort = nullptr;
    }

    if(myTimer != nullptr)
        myTimer->deleteLater();
}

void workOnSerialPort::writeDataToPort(QByteArray data)
{
    if (m_serialPort->isOpen()) {
        m_serialPort->write(data);
        emit reportMessage(m_data->toHex().toUpper().data());
    }
}

void workOnSerialPort::onSerialPortReadyRead()
{
    QByteArray data;
    while (m_serialPort->bytesAvailable()) {
        data = m_serialPort->readAll();
        m_data->append(data);
        emit recivedMessage(m_data->toHex().toUpper().data());
        m_data->clear();
    }

}
