#include "setting.h"

Setting::Setting(QObject *parent,
                 QObject *homeViewer,
                 QObject *tankViewer,
                 QObject *settingViewer,
                 QObject *statisticViewer,
                 BME280Item *bme280,
                 ADS1115Item *ads1115_1,
                 ADS1115Item *ads1115_2,
                 DataManager *dataManager):
    QObject(parent),
    _tankObjectNameArray(GlobaleStaticValue::initTankObjectName()),
    _homeViewObject(GlobaleStaticValue::initHomeViewObject()),
    _settingFileName(GlobaleStaticValue::settingFile),
    _setting(new QSettings (GlobaleStaticValue::settingFile, QSettings::IniFormat)),
    _Tank1(new Tank(GlobalEnumerate::TANK1, this->_tankObjectNameArray[GlobalEnumerate::TANK1])),
    _Tank2(new Tank(GlobalEnumerate::TANK2, this->_tankObjectNameArray[GlobalEnumerate::TANK2])),
    _Tank3(new Tank(GlobalEnumerate::TANK3, this->_tankObjectNameArray[GlobalEnumerate::TANK3])),
    _Tank4(new Tank(GlobalEnumerate::TANK4, this->_tankObjectNameArray[GlobalEnumerate::TANK4])),
    _Tank5(new Tank(GlobalEnumerate::TANK5, this->_tankObjectNameArray[GlobalEnumerate::TANK5])),
    _Tank6(new Tank(GlobalEnumerate::TANK6, this->_tankObjectNameArray[GlobalEnumerate::TANK6])),
    _tankIsVisible(true),
    _homeViewer(homeViewer),
    _tankViewer(tankViewer),
    _settingViewer(settingViewer),
    _statisticViewer(statisticViewer),
    _bme280(bme280),
    _ads1115_1(ads1115_1),
    _ads1115_2(ads1115_2),
    _dataManager(dataManager)
{

    qmlRegisterType<Setting>("io.qt.Setting", 1, 0, "Setting");

    //set personnal path for the setting.ini file
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, SAVED_PATH_FILE);

    //load parameter from this init file
    this->loadSettings();

    //set the object parameters from the init file
    this->initSetting();

    //save the parameter from the init file
    this->saveSettings();

}

void Setting::receivedTankIsVisible(const int objectID, const bool isVisible)
{
    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setIsVisible(isVisible);
        break;
    }

    QMetaObject::invokeMethod(this->_tankViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

    QMetaObject::invokeMethod(this->_homeViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setupTraceIsSelected",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    this->saveSettings();
}

void Setting::receivedTankTitleChanged(const int objectID, const QString titleText)
{
    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK1, this->_Tank1->title());
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK2, this->_Tank2->title());
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK3, this->_Tank3->title());
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK4, this->_Tank4->title());
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK5, this->_Tank5->title());
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setTitle(titleText);
        this->initHomeViewObject(GlobalEnumerate::HOMETANK6, this->_Tank6->title());
        break;
    }


    QMetaObject::invokeMethod(this->_homeViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    this->saveSettings();
}

void Setting::receivedTankVolumeMaxChanged(const QString objectName, const int volumeMax)
{

    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
    {
        this->_Tank1->setVolumeMax(volumeMax);
        this->_ads1115_1->setTankChan0VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK2 :
    {
        this->_Tank2->setVolumeMax(volumeMax);
        this->_ads1115_1->setTankChan1VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK3 :
    {
        this->_Tank3->setVolumeMax(volumeMax);
        this->_ads1115_1->setTankChan2VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK4 :
    {
        this->_Tank4->setVolumeMax(volumeMax);
        this->_ads1115_1->setTankChan3VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK5 :
    {
        this->_Tank5->setVolumeMax(volumeMax);
        this->_ads1115_2->setTankChan0VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK6 :
    {
        this->_Tank6->setVolumeMax(volumeMax);
        this->_ads1115_2->setTankChan1VolumeMax(volumeMax);
        break;
    }
    }

    this->saveSettings();
}

void Setting::receivedWarningLowLevelFromTank(const QString objectName, const bool isActive)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    if(isActive)
    {
        QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                                  Q_ARG(QVariant, objectID),
                                  Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX)
                                  );
    }
    else
    {
        QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                                  Q_ARG(QVariant, objectID),
                                  Q_ARG(QVariant, DEVICE_COLOR_READY_HEX)
                                  );

    }
}

void Setting::receivedTankWarningLowLevelChanged(const QString objectName, const int lowLevel)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setLowLevelValue(lowLevel);
        break;
    }

    this->saveSettings();
}

void Setting::receivedTankLiquideFillupChanged(const QString objectName, const int liquideFillup)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
    {
        this->_Tank1->setLiquideFillup(liquideFillup);
        this->_ads1115_1->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK2 :
    {
        this->_Tank2->setLiquideFillup(liquideFillup);
        this->_ads1115_1->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK3 :
    {
        this->_Tank3->setLiquideFillup(liquideFillup);
        this->_ads1115_1->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK4 :
    {
        this->_Tank4->setLiquideFillup(liquideFillup);
        this->_ads1115_1->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK5 :
    {
        this->_Tank5->setLiquideFillup(liquideFillup);
        this->_ads1115_2->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK6 :
    {
        this->_Tank6->setLiquideFillup(liquideFillup);
        this->_ads1115_2->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    }

    this->saveSettings();
}

void Setting::receivedTankHeightMaxLevelChanged(const QString objectName, const int heightVMax)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    }

    this->saveSettings();
}

void Setting::receivedTankActualVolumeChanged(const int objectID, const int volumeActual)
{

    QString str = QString::number(volumeActual) + " " + GlobaleStaticValue::ADS1115_Liter;

    QMetaObject::invokeMethod(this->_tankViewer, "setTankVolumeActual",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, volumeActual)
                              );
    QMetaObject::invokeMethod(this->_homeViewer, "setTankVolumeActual",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, str)
                              );
}

void Setting::receivedGraphReccordTimesChanged(const int reccordTime)
{
    quint64 refreshTime = 0;
    quint64 graphicRange = 0;

    if(reccordTime <= 0)
    {
        graphicRange = 100;
        refreshTime = graphicRange*1000/NB_OF_PIXELS_IN_PLOT;
    }
    else
    {
        graphicRange = reccordTime*3600;
        refreshTime = graphicRange*1000/NB_OF_PIXELS_IN_PLOT;
    }

    qDebug() << Q_FUNC_INFO << "graphicRange" << graphicRange << ", refreshTime" << refreshTime;
    this->_dataManager->setDelay(refreshTime);

    QMetaObject::invokeMethod(this->_statisticViewer, "setGraphicRange",
                              Q_ARG(QVariant, graphicRange)
                              );
}

void Setting::receivedOnCalibrationMode(const bool onCalibration)
{
    qDebug() << Q_FUNC_INFO << onCalibration;
    this->_ads1115_1->setOnCalibration(onCalibration);

    QMetaObject::invokeMethod(this->_statisticViewer, "setOnClaibration",
                              Q_ARG(QVariant, onCalibration)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setOnClaibration",
                              Q_ARG(QVariant, onCalibration)
                              );
}

void Setting::initSetting()
{
    this->initTankObjectName(this->_Tank1->objectID(),this->_Tank1->objectName());
    this->initTankObjectName(this->_Tank2->objectID(),this->_Tank2->objectName());
    this->initTankObjectName(this->_Tank3->objectID(),this->_Tank3->objectName());
    this->initTankObjectName(this->_Tank4->objectID(),this->_Tank4->objectName());
    this->initTankObjectName(this->_Tank5->objectID(),this->_Tank5->objectName());
    this->initTankObjectName(this->_Tank6->objectID(),this->_Tank6->objectName());

    this->initTankIsVisible(this->_Tank1->objectID(), this->_Tank1->isVisible());
    this->initTankIsVisible(this->_Tank2->objectID(), this->_Tank2->isVisible());
    this->initTankIsVisible(this->_Tank3->objectID(), this->_Tank3->isVisible());
    this->initTankIsVisible(this->_Tank4->objectID(), this->_Tank4->isVisible());
    this->initTankIsVisible(this->_Tank5->objectID(), this->_Tank5->isVisible());
    this->initTankIsVisible(this->_Tank6->objectID(), this->_Tank6->isVisible());

    this->initTankTitleText(this->_Tank1->objectID(),this->_Tank1->title());
    this->initTankTitleText(this->_Tank2->objectID(),this->_Tank2->title());
    this->initTankTitleText(this->_Tank3->objectID(),this->_Tank3->title());
    this->initTankTitleText(this->_Tank4->objectID(),this->_Tank4->title());
    this->initTankTitleText(this->_Tank5->objectID(),this->_Tank5->title());
    this->initTankTitleText(this->_Tank6->objectID(),this->_Tank6->title());

    this->initHomeViewObject(GlobalEnumerate::HOMEBME280, _homeViewObject[GlobalEnumerate::HOMEBME280]);
    this->initHomeViewObject(GlobalEnumerate::HOMETANK1, this->_Tank1->title());
    this->initHomeViewObject(GlobalEnumerate::HOMETANK2, this->_Tank2->title());
    this->initHomeViewObject(GlobalEnumerate::HOMETANK3, this->_Tank3->title());
    this->initHomeViewObject(GlobalEnumerate::HOMETANK4, this->_Tank4->title());
    this->initHomeViewObject(GlobalEnumerate::HOMETANK5, this->_Tank5->title());
    this->initHomeViewObject(GlobalEnumerate::HOMETANK6, this->_Tank6->title());
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR1, _homeViewObject[GlobalEnumerate::HOMESENSOR1]);
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR2, _homeViewObject[GlobalEnumerate::HOMESENSOR2]);
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR3, _homeViewObject[GlobalEnumerate::HOMESENSOR3]);
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR4, _homeViewObject[GlobalEnumerate::HOMESENSOR4]);
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR5, _homeViewObject[GlobalEnumerate::HOMESENSOR5]);
    this->initHomeViewObject(GlobalEnumerate::HOMESENSOR6, _homeViewObject[GlobalEnumerate::HOMESENSOR6]);
    this->initHomeViewObject(GlobalEnumerate::HOMEAD1115_1, _homeViewObject[GlobalEnumerate::HOMEAD1115_1]);
    this->initHomeViewObject(GlobalEnumerate::HOMEAD1115_2, _homeViewObject[GlobalEnumerate::HOMEAD1115_2]);

    this->initTankVolumeMax(this->_Tank1->objectID(),this->_Tank1->volumeMax());
    this->initTankVolumeMax(this->_Tank2->objectID(),this->_Tank2->volumeMax());
    this->initTankVolumeMax(this->_Tank3->objectID(),this->_Tank3->volumeMax());
    this->initTankVolumeMax(this->_Tank4->objectID(),this->_Tank4->volumeMax());
    this->initTankVolumeMax(this->_Tank5->objectID(),this->_Tank5->volumeMax());
    this->initTankVolumeMax(this->_Tank6->objectID(),this->_Tank6->volumeMax());

    this->initTankLiquideInside(this->_Tank1->objectID(),this->_Tank1->LiquideFillup());
    this->initTankLiquideInside(this->_Tank2->objectID(),this->_Tank2->LiquideFillup());
    this->initTankLiquideInside(this->_Tank3->objectID(),this->_Tank3->LiquideFillup());
    this->initTankLiquideInside(this->_Tank4->objectID(),this->_Tank4->LiquideFillup());
    this->initTankLiquideInside(this->_Tank5->objectID(),this->_Tank5->LiquideFillup());
    this->initTankLiquideInside(this->_Tank6->objectID(),this->_Tank6->LiquideFillup());

    this->initHeightVMaxValue(this->_Tank1->objectID(),this->_Tank1->volumeMaxHeightInMilimeter());
    this->initHeightVMaxValue(this->_Tank2->objectID(),this->_Tank2->volumeMaxHeightInMilimeter());
    this->initHeightVMaxValue(this->_Tank3->objectID(),this->_Tank3->volumeMaxHeightInMilimeter());
    this->initHeightVMaxValue(this->_Tank4->objectID(),this->_Tank4->volumeMaxHeightInMilimeter());
    this->initHeightVMaxValue(this->_Tank5->objectID(),this->_Tank5->volumeMaxHeightInMilimeter());
    this->initHeightVMaxValue(this->_Tank6->objectID(),this->_Tank6->volumeMaxHeightInMilimeter());

    this->initTankWarningLowLevel(this->_Tank1->objectID(),this->_Tank1->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank2->objectID(),this->_Tank2->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank3->objectID(),this->_Tank3->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank4->objectID(),this->_Tank4->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank5->objectID(),this->_Tank5->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank6->objectID(),this->_Tank6->lowLevelValue());

    //init ADS1115 for volume calculation
    this->_ads1115_1->setTankIDchan0(this->_Tank1->objectID());
    this->_ads1115_1->setTankIDchan1(this->_Tank2->objectID());
    this->_ads1115_1->setTankIDchan2(this->_Tank3->objectID());
    this->_ads1115_1->setTankIDchan3(this->_Tank4->objectID());
    this->_ads1115_2->setTankIDchan0(this->_Tank5->objectID());
    this->_ads1115_2->setTankIDchan1(this->_Tank6->objectID());

    //init trace in plt
    //nbTraceInPlot
    this->_nbTrace = this->calculNbTraceInPlot();

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceNomberInGraph",
                              Q_ARG(QVariant, this->_nbTrace)
                              );

    this->initTankColorInHomePage(this->_Tank1->objectID());
    this->initTankColorInHomePage(this->_Tank2->objectID());
    this->initTankColorInHomePage(this->_Tank3->objectID());
    this->initTankColorInHomePage(this->_Tank4->objectID());
    this->initTankColorInHomePage(this->_Tank5->objectID());
    this->initTankColorInHomePage(this->_Tank6->objectID());

    this->_dataManager->startReading();
}

void Setting::initTankObjectName(int objectID, QString objectName)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankObjectName",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, objectName)
                              );

}

void Setting::initTankColorInHomePage(int objectID)
{
    QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, DEVICE_COLOR_READY_HEX)
                              );
}

void Setting::initTankTitleText(int objectID, QString titleText)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_homeViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );
}

void Setting::initHomeViewObject(int objectID, QString obbjectName)
{
    QMetaObject::invokeMethod(this->_homeViewer, "setAllTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, obbjectName)
                              );
}

void Setting::initTankIsVisible(int objectID, bool isVisible)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    QMetaObject::invokeMethod(this->_tankViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

    QMetaObject::invokeMethod(this->_homeViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    QMetaObject::invokeMethod(this->_statisticViewer, "setupTraceIsSelected",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
}

void Setting::initTankVolumeMax(int objectID, int volumeMax)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankVolumeMax",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, volumeMax)
                              );
    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
        this->_ads1115_1->setTankChan0VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK2:
        this->_ads1115_1->setTankChan1VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK3:
        this->_ads1115_1->setTankChan2VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK4:
        this->_ads1115_1->setTankChan3VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK5:
        this->_ads1115_2->setTankChan0VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK6:
        this->_ads1115_2->setTankChan1VolumeMax(volumeMax);
        break;
    default:
        break;
    }
}

void Setting::initTankWarningLowLevel(int objectID, int warningLowLevel)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setWarningLowLevel",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, warningLowLevel)
                              );
}

void Setting::initTankLiquideInside(int objectID, int tankLiquideInside)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankLiquideInside",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, tankLiquideInside)
                              );

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
        this->_ads1115_1->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK2:
        this->_ads1115_1->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK3:
        this->_ads1115_1->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK4:
        this->_ads1115_1->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK5:
        this->_ads1115_2->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK6:
        this->_ads1115_2->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    default:
        break;
    }
}

void Setting::initHeightVMaxValue(int objectID, int HeightVMaxValue)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setHeightVMaxValue",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, HeightVMaxValue)
                              );

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
        this->_ads1115_1->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK2:
        this->_ads1115_1->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK3:
        this->_ads1115_1->setTankChan2VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK4:
        this->_ads1115_1->setTankChan3VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK5:
        this->_ads1115_2->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK6:
        this->_ads1115_2->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    default:
        break;
    }
}

quint8 Setting::calculNbTraceInPlot()
{
    return(this->_Tank1->isVisible()+
           this->_Tank2->isVisible()+
           this->_Tank3->isVisible()+
           this->_Tank4->isVisible()+
           this->_Tank5->isVisible()+
           this->_Tank6->isVisible()
           );
}

void Setting::saveSettings()
{
    //save application setting values
    QString groupeNameSetting = GlobaleStaticValue::saveGroupeNameApplicationSettingTxt;
    this->_setting->beginGroup(groupeNameSetting);
    //ADS1115, 5v value in puls for the 4-10ma to 0-5v converter
    this->_setting->setValue(GlobaleStaticValue::ADS115_5V_ValueInPlus, this->_setting->value(GlobaleStaticValue::ADS115_5V_ValueInPlus, 26500).toInt());
    //path for saved data folder
    this->_setting->setValue(GlobaleStaticValue::saveDataMainTxt, this->_dataManager->directoryDatafileName());
    //path for setting file
    this->_setting->setValue(GlobaleStaticValue::settingFileTxt, this->_setting->value(GlobaleStaticValue::settingFile, GlobaleStaticValue::settingFile).toString());
    this->_setting->endGroup();

    //save all value for tank1
    this->saveTankSetting(this->_Tank1);

    //save all value for tank2
    this->saveTankSetting(this->_Tank2);

    //save all value for tank3
    this->saveTankSetting(this->_Tank3);

    //save all value for tank4
    this->saveTankSetting(this->_Tank4);

    //save all value for tank5
    this->saveTankSetting(this->_Tank5);

    //save all value for tank6
    this->saveTankSetting(this->_Tank6);

}

void Setting::saveTankSetting(Tank *tank)
{
    QString groupeName = tank->objectName();

    //save all value for tank
    this->_setting->beginGroup(groupeName);
    this->_setting->setValue(GlobaleStaticValue::saveIDTxt, tank->objectID());
    this->_setting->setValue(GlobaleStaticValue::saveObjectNameTxt, tank->objectName());
    this->_setting->setValue(GlobaleStaticValue::saveTitleTxt, tank->title());
    this->_setting->setValue(GlobaleStaticValue::saveVisibleTxt, tank->isVisible());
    this->_setting->setValue(GlobaleStaticValue::saveLiquideInsideTxt, tank->LiquideFillup());
    this->_setting->setValue(GlobaleStaticValue::saveVolumeMaxTxt, tank->volumeMax());
    this->_setting->setValue(GlobaleStaticValue::saveLowLevelWarningTxt, tank->lowLevelValue());
    this->_setting->setValue(GlobaleStaticValue::saveHeightVMaxValueTxt, tank->volumeMaxHeightInMilimeter());
    this->_setting->endGroup();
}

void Setting::loadSettings()
{
    //load application setting values
    QString groupeNameSetting = GlobaleStaticValue::saveGroupeNameApplicationSettingTxt;
    QString ADS115_5V_ValueInPlus = groupeNameSetting + "/" + GlobaleStaticValue::ADS115_5V_ValueInPlus;
    QString directoryDatafileName = groupeNameSetting + "/" + GlobaleStaticValue::saveDataMainTxt;
    QString tempFileName = groupeNameSetting + "/" + GlobaleStaticValue::saveTempFileTxt;
    QString settingFileName = groupeNameSetting + "/" + GlobaleStaticValue::saveTempFileTxt;

    this->_ads1115_1->setHighMaxValueInPuls(this->_setting->value(ADS115_5V_ValueInPlus, 26500).toInt());
    //path for saved data folder
    this->_dataManager->setDirectoryDatafileName(this->_setting->value(directoryDatafileName, GlobaleStaticValue::saveDataMain).toString());
    //path for setting file
    this->_settingFileName = this->_setting->value(settingFileName, GlobaleStaticValue::settingFile).toString();

    //load tanks values
    loadTankSetting(this->_Tank1);
    loadTankSetting(this->_Tank2);
    loadTankSetting(this->_Tank3);
    loadTankSetting(this->_Tank4);
    loadTankSetting(this->_Tank5);
    loadTankSetting(this->_Tank6);
}

void Setting::loadTankSetting(Tank *tank)
{
    QString groupeName = tank->objectName();
    QString groupeNameID = groupeName + "/" + GlobaleStaticValue::saveIDTxt;
    QString groupeNameObjectName = groupeName + "/" + GlobaleStaticValue::saveObjectNameTxt;
    QString groupeNameTitle = groupeName + "/" +GlobaleStaticValue::saveTitleTxt;
    QString groupeNameVisible = groupeName + "/" + GlobaleStaticValue::saveVisibleTxt;
    QString groupeNameLiquideInside = groupeName + "/" + GlobaleStaticValue::saveLiquideInsideTxt;
    QString groupeNameVolumeMax = groupeName + "/" + GlobaleStaticValue::saveVolumeMaxTxt;
    QString groupeNameLowLevelWarning = groupeName + "/" + GlobaleStaticValue::saveLowLevelWarningTxt;
    QString groupeNameHeighVMaxValue = groupeName + "/" + GlobaleStaticValue::saveHeightVMaxValueTxt;

    tank->setObjectName(this->_setting->value(groupeNameObjectName, tank->objectName()).toString());
    tank->setTitle(this->_setting->value(groupeNameTitle, tank->objectID()).toString());
    tank->setIsVisible(this->_setting->value(groupeNameVisible, tank->isVisible()).toBool());
    tank->setLiquideFillup(this->_setting->value(groupeNameLiquideInside, GlobalEnumerate::E_TankLiquidInside::WATER).toInt());
    tank->setVolumeMax(this->_setting->value(groupeNameVolumeMax, 1500).toInt());
    tank->setLowLevelValue(this->_setting->value(groupeNameLowLevelWarning, 500).toInt());
    tank->setVolumeMaxHeightInMilimeter(this->_setting->value(groupeNameHeighVMaxValue, 1500).toInt());
}
