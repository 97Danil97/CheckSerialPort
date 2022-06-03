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

    /*!
     * \brief workOnSerialPort - конструктор класса
     * \param parent - указатель на класс "родителя"
     * \param serialPort - указатель на RS порт
     */
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

    /*!
     * \brief reportMessage - сигнал отправки сообщения
     * \param str - сообщение
     */
    void reportMessage(QString str);

    /*!
     * \brief recivedMessage - сигнал о полученом сообщении
     * \param str - сообщение
     */
    void recivedMessage(QString str);
};

#endif // WORKONSERIALPORT_H
