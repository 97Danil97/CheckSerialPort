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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_buttonStartStop_clicked();

    void setConnect();

    void unConnect();

    void onReportMessage(QString str);

    void onRecivedMessage(QString str);

    void setupSettingRS232(QSerialPort *mySerialPort);

    void setupComboBox();

    void saveSettingRS232();

    void getSettingRS232();

    void on_comboBoxNumberOfBytes_currentIndexChanged(int index);

    void on_pushButtonSendMessage_clicked();

signals:
    void reportMessagetoCan(QByteArray);


private:
    Ui::MainWindow *ui;
    workOnSerialPort *m_serialPort;

    mySetting *settings;

    int numberOfBytes;
    bool isStart;

};
#endif // MAINWINDOW_H
