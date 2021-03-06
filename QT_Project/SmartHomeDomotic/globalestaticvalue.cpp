#include "globalestaticvalue.h"

GlobaleStaticValue::GlobaleStaticValue()
{

}
//Welcome static text
QString GlobaleStaticValue::welcomeText = "******************************************\n"
                                          "   Welcom on the Smart Home Domotic\n"
                                          "******************************************\n";

//warning static text
QString GlobaleStaticValue::errorCounterTxt = "nb of active error";

//sensor read interval time in miliseconde
quint16 GlobaleStaticValue::delaiToReadValue = 10000;    // on graph are 8640 point, 10000 -> 24hours reccording with one value every 10 seconds

//text value for the saved file
QString GlobaleStaticValue::saveGroupeNameApplicationSettingTxt = "APP_SETTING";
QString GlobaleStaticValue::ADS115_5V_ValueInPlus = "ADS115_5V_InPlus";
QString GlobaleStaticValue::saveIDTxt = "ID";
QString GlobaleStaticValue::saveObjectNameTxt = "ObjectName";
QString GlobaleStaticValue::saveTitleTxt = "Title";
QString GlobaleStaticValue::saveVisibleTxt = "Visible";
QString GlobaleStaticValue::saveLiquideInsideTxt = "LiquideInside";
QString GlobaleStaticValue::saveVolumeMaxTxt = "VolumeMax";
QString GlobaleStaticValue::saveLowLevelWarningTxt = "LowLevelWarning";
QString GlobaleStaticValue::saveHeightVMaxValueTxt = "HeightVMax";

//saved static date-time format
QString GlobaleStaticValue::saveTimeFormatMinuteTXT = "yyyy-MM-dd_HH-mm-00";
QString GlobaleStaticValue::saveTimeFormatHourTXT= "yyyy-MM-dd_HH";
QString GlobaleStaticValue::saveTimeFormatDayTXT= "yyyy-MM-dd";
QString GlobaleStaticValue::saveTimeFormatMonthTXT= "yyyy-MM";

//saved static saved folder
QString GlobaleStaticValue::saveDataMainTxt = "Data_Path_folder";
QString GlobaleStaticValue::saveDataMain = "./Data/";
//QString GlobaleStaticValue::saveDataMain = "/home/smarthomedomotic/Data/";

//saved static temp file
QString GlobaleStaticValue::saveTempFileTxt = "Save_Temp_File_Name_and_Path";
QString GlobaleStaticValue::saveTempFile = "./Data/tempData.csv";
//QString GlobaleStaticValue::saveTempFile = "/home/smarthomedomotic/Data/tempData.csv";

//setting file
QString GlobaleStaticValue::settingFileTxt= "Setting_File_Name_and_Path";
QString GlobaleStaticValue::settingFile = "./Setting/settings.ini";
//QString GlobaleStaticValue::settingFile = "/home/smarthomedomotic/Setting/settings.ini";

//Machine States static text
QString GlobaleStaticValue::stateNotFounded = "NOT FOUNDED";
QString GlobaleStaticValue::stateFounded = "FOUNDED";
QString GlobaleStaticValue::stateInit = "INIT";
QString GlobaleStaticValue::stateOnProgramming = "on programming...";
QString GlobaleStaticValue::stateCheckProgramming = "check programming...";
QString GlobaleStaticValue::stateProgrammingSuccessful = "programming successful";
QString GlobaleStaticValue::stateOnReading = "ON READING";
QString GlobaleStaticValue::stateReady = "READY";

//ADS1115 static text
QString GlobaleStaticValue::ADS1115_1Title = "ADS1115_1";
QString GlobaleStaticValue::ADS1115_2Title = "ADS1115_2";
QString GlobaleStaticValue::ADS1115_Chan0 = "chan 0";
QString GlobaleStaticValue::ADS1115_Chan1 = "chan 1";
QString GlobaleStaticValue::ADS1115_Chan2 = "chan 2";
QString GlobaleStaticValue::ADS1115_Chan3 = "chan 3";
QString GlobaleStaticValue::ADS1115_Liter = "lt";
QString GlobaleStaticValue::ADS1115_Volt = " V";

//BME 280 static text
QString GlobaleStaticValue::bme280Title = "BME_280";
QString GlobaleStaticValue::bme280Temperature = "Temp";
QString GlobaleStaticValue::bme280Humidity = "Hum";
QString GlobaleStaticValue::bme280Pressure = "Press";
QString GlobaleStaticValue::bme280DegCelcuis = "°C";
QString GlobaleStaticValue::bme280PerCent = "%";
QString GlobaleStaticValue::bme280Milibar = "mb";

//pressure capteur values
quint16 GlobaleStaticValue::pressureCapteurRangeMaxInPlus = 26500;
quint16 GlobaleStaticValue::pressureCapteurHeightMaxWater = 5000;

//density T/m^3
double GlobaleStaticValue::densityWater = 1;
double GlobaleStaticValue::densityOil = 0.84;
double GlobaleStaticValue::densityOilECO = 0.84;

static QString titleTank1 = "Tank_1";
static QString titleTank2 = "Tank_2";
static QString titleTank3 = "Tank_3";
static QString titleTank4 = "Tank_4";
static QString titleTank5 = "Tank_5";
static QString titleTank6 = "Tank_6";

//home view object name
static QString BME280Name = "BME 280";
static QString sensor1Name = "Sensor 1";
static QString sensor2Name = "Sensor 2";
static QString sensor3Name = "Sensor 3";
static QString sensor4Name = "Sensor 4";
static QString sensor5Name = "Sensor 5";
static QString sensor6Name = "Sensor 6";
static QString ad1115_1Name = "AD1115 1";
static QString ad1115_2Name = "AD1115 2";

static QString errNoError = "no error";
static QString errLowLevelReached = "low level reached";

QMap<int, QString> GlobaleStaticValue::initTankObjectName()
{
    QMap<int, QString> ret;
    ret.insert(GlobalEnumerate::TANK1, titleTank1);
    ret.insert(GlobalEnumerate::TANK2, titleTank2);
    ret.insert(GlobalEnumerate::TANK3, titleTank3);
    ret.insert(GlobalEnumerate::TANK4, titleTank4);
    ret.insert(GlobalEnumerate::TANK5, titleTank5);
    ret.insert(GlobalEnumerate::TANK6, titleTank6);
    return ret;
}

QMap<int, QString> GlobaleStaticValue::initHomeViewObject()
{
    QMap<int, QString> ret;
    ret.insert(GlobalEnumerate::HOMEBME280, BME280Name);
    ret.insert(GlobalEnumerate::HOMETANK1, titleTank1);
    ret.insert(GlobalEnumerate::HOMETANK2, titleTank2);
    ret.insert(GlobalEnumerate::HOMETANK3, titleTank3);
    ret.insert(GlobalEnumerate::HOMETANK4, titleTank4);
    ret.insert(GlobalEnumerate::HOMETANK5, titleTank5);
    ret.insert(GlobalEnumerate::HOMETANK6, titleTank6);
    ret.insert(GlobalEnumerate::HOMESENSOR1, sensor1Name);
    ret.insert(GlobalEnumerate::HOMESENSOR2, sensor2Name);
    ret.insert(GlobalEnumerate::HOMESENSOR3, sensor3Name);
    ret.insert(GlobalEnumerate::HOMESENSOR4, sensor4Name);
    ret.insert(GlobalEnumerate::HOMESENSOR5, sensor5Name);
    ret.insert(GlobalEnumerate::HOMESENSOR6, sensor6Name);
    ret.insert(GlobalEnumerate::HOMEAD1115_1, ad1115_1Name);
    ret.insert(GlobalEnumerate::HOMEAD1115_2, ad1115_2Name);
    return ret;
}

QMap<int, QString> GlobaleStaticValue::initErrorPossible()
{
    QMap<int, QString> ret;
    ret.insert(GlobalEnumerate::ERR_NO_ERROR, errNoError);
    ret.insert(GlobalEnumerate::ERR_LOW_LEVEL_REACHED, errLowLevelReached);
    return ret;
}


