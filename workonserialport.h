#ifndef WORKONSERIALPORT_H
#define WORKONSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>

class workOnSerialPort : public QObject
{
    Q_OBJECT

public:
    workOnSerialPort(QSerialPort *serialPort, QObject *parent );

    ~workOnSerialPort( void );

public slots:
    /**
     * @brief writeDataToPort - запись данных в прот
     * @param data - данные
     */
    void writeDataToPort(QByteArray data);

private:
    QSerialPort         *m_serialPort;
    QByteArray          *m_data;
    QTimer              *myTimer;

    /**
     * @brief Обработчик последовательнго порта (вызывается по сигналу QSerialPort::readyRead)
     */
    void onSerialPortReadyRead( void );

signals:

    void reportMessage(QString str);

    void recivedMessage(QString str);
};

#endif // WORKONSERIALPORT_H
