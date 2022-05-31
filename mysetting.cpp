#include "mysetting.h"

mySetting::mySetting(QObject *parent, QString nameFile)
{
    settings = new QSettings(QApplication::applicationFilePath().append(nameFile).append(".conf"), QSettings::IniFormat, parent);

}

mySetting::~mySetting()
{
    settings->deleteLater();
    settings = nullptr;
}


void mySetting::setComboBoxBaudRate(int index)
{
    settings->setValue("ComboBox/BaudRate",index);
}

void mySetting::setComboBoxDataBits(int index)
{
    settings->setValue("ComboBox/DataBits",index);
}

void mySetting::setComboBoxParity(int index)
{
    settings->setValue("ComboBox/Parity",index);
}

void mySetting::setComboBoxStopBits(int index)
{
    settings->setValue("ComboBox/StopBits",index);
}

void mySetting::setComboBoxFlowControl(int index)
{
    settings->setValue("ComboBox/FlowControl",index);
}

int mySetting::getComboBoxBaudRate()
{
    return settings->value("ComboBox/BaudRate").toInt();
}

int mySetting::getComboBoxDataBits()
{
    return settings->value("ComboBox/DataBits").toInt();
}

int mySetting::getComboBoxParity()
{
    return settings->value("ComboBox/Parity").toInt();
}

int mySetting::getComboBoxStopBits()
{
    return settings->value("ComboBox/StopBits").toInt();
}

int mySetting::getComboBoxFlowControl()
{
    return settings->value("ComboBox/FlowControl").toInt();
}

void mySetting::saveAdressCOM(QString str)
{
    settings->setValue("ComPort/Port",str);
}

QString mySetting::getAdressCOM()
{
    return settings->value("ComPort/Port").toString();
}
