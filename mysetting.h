#ifndef MYSETTING_H
#define MYSETTING_H

#include<QSettings>
#include <QApplication>

class mySetting
{
public:
    mySetting(QObject *parent,QString nameFile);

    ~mySetting( void );

    QSettings *settings;



    void setComboBoxBaudRate(int index);
    void setComboBoxDataBits(int index);
    void setComboBoxParity(int index);
    void setComboBoxStopBits(int index);
    void setComboBoxFlowControl(int index);

    int getComboBoxBaudRate();
    int getComboBoxDataBits();
    int getComboBoxParity();
    int getComboBoxStopBits();
    int getComboBoxFlowControl();

    void saveAdressCOM(QString str);
    QString getAdressCOM();
};

#endif // MYSETTING_H
