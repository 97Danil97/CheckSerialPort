#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDateTime>
#include "mysetting.h"
#include "workonserialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief MainWindow - конструктор класса
     * \param parent - указатель на класс "родителя"
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief ~MainWindow - деструктор класса
     * \param parent - указатель на класс "родителя"
     */
    ~MainWindow();

private slots:

    void on_buttonStartStop_clicked();

    /*!
     * \brief setConnect - метод устанавливает связь сигналов со слотами
     */
    void setConnect();

    /*!
     * \brief unConnect - метод разрывает связь сигналов со слотами
     */
    void unConnect();

    /*!
     * \brief onReportMessage - метод информирует об отправленном запросе
     * \param str - Отправленное сообщение
     */
    void onReportMessage(QString str);

    /*!
     * \brief onRecivedMessage - метод информирует о принятом сообщении
     * \param str - Принятое сообщение
     */
    void onRecivedMessage(QString str);

    /*!
     * \brief setupSettingRS232 - метод установки настроек RS порта
     * \param str - Принятое сообщение
     */
    void setupSettingRS232(QSerialPort *mySerialPort);

    /*!
     * \brief setupComboBox - метод устанавливает значения в выпадающие списки
     */
    void setupComboBox();

    /*!
     * \brief saveSettingRS232 - метод сохранения последних настроек RS порта
     */
    void saveSettingRS232();

    /*!
     * \brief onRecivedMessage - метод получения последних настроек RS порта
     * \param str - Принятое сообщение
     */
    void getSettingRS232();

    void on_comboBoxNumberOfBytes_currentIndexChanged(int index);

    void on_pushButtonSendMessage_clicked();

signals:
    /*!
     * \brief reportMessagetoRS - сигнал отправки сообщения
     */
    void reportMessagetoRS(QByteArray);


private:
    Ui::MainWindow *ui;

    workOnSerialPort *m_serialPort;

    mySetting *settings;

    /// Количество байт
    int numberOfBytes;

    /// Открыт(закрыт) порт
    bool isStart;

};
#endif // MAINWINDOW_H
