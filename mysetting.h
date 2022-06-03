#ifndef MYSETTING_H
#define MYSETTING_H

#include<QSettings>
#include <QApplication>

class mySetting
{
public:

    /*!
     * \brief mySetting - конструктор класса
     * \param parent - указатель на класс "родителя"
     * \param nameFile - имя файла настроек
     */
    mySetting(QObject *parent,QString nameFile);

    ~mySetting( void );

    QSettings *settings;


    /*!
     * \brief setComboBoxBaudRate - сохранение настройки BaudRate в файл
     * \param index - индекс ComboBox
     */
    void setComboBoxBaudRate(int index);

    /*!
     * \brief setComboBoxDataBits - сохранение настройки DataBits в файл
     * \param index - индекс ComboBox
     */
    void setComboBoxDataBits(int index);

    /*!
     * \brief setComboBoxParity - сохранение настройки Parity в файл
     * \param index - индекс ComboBox
     */
    void setComboBoxParity(int index);

    /*!
     * \brief setComboBoxStopBits - сохранение настройки StopBits в файл
     * \param index - индекс ComboBox
     */
    void setComboBoxStopBits(int index);

    /*!
     * \brief setComboBoxFlowControl - сохранение настройки FlowControl в файл
     * \param index - индекс ComboBox
     */
    void setComboBoxFlowControl(int index);

    /*!
     * \brief getComboBoxBaudRate - получение настройки BaudRate из файла
     */
    int getComboBoxBaudRate();

    /*!
     * \brief getComboBoxDataBits - получение настройки DataBits из файла
     */
    int getComboBoxDataBits();

    /*!
     * \brief getComboBoxParity - получение настройки Parity из файла
     */
    int getComboBoxParity();

    /*!
     * \brief getComboBoxStopBits - получение настройки StopBits из файла
     */
    int getComboBoxStopBits();

    /*!
     * \brief getComboBoxFlowControl - получение настройки FlowControl из файла
     */
    int getComboBoxFlowControl();

    /*!
     * \brief saveAdressCOM - сохранение адреса RS порта в файла
     */
    void saveAdressCOM(QString str);

    /*!
     * \brief getAdressCOM - получение адреса RS порта из файла
     */
    QString getAdressCOM();
};

#endif // MYSETTING_H
