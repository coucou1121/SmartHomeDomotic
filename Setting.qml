import QtQuick 2.4

import io.qt.Setting 1.0

import io.qt.GlobalEnumerate 1.0

SettingForm
{
    signal sendTankIsVisible(int tankObjectID, bool isVisible)
    signal sendTankTitleChanged(int tankObjectID, string title)

    property string memotextFieldTank1: "1"
    property string memotextFieldTank2: "2"
    property string memotextFieldTank3: "3"
    property string memotextFieldTank4: "4"
    property string memotextFieldTank5: "5"
    property string memotextFieldTank6: "6"


    textFieldTank1.onFocusChanged:
    {
        memotextFieldTank1 = textFieldTank1Text
    }

    textFieldTank2.onFocusChanged:
    {
        memotextFieldTank2 = textFieldTank2Text
    }

    textFieldTank3.onFocusChanged:
    {
        memotextFieldTank3 = textFieldTank3Text
    }

    textFieldTank4.onFocusChanged:
    {
        memotextFieldTank4 = textFieldTank4Text
    }

    textFieldTank5.onFocusChanged:
    {
        memotextFieldTank5 = textFieldTank5Text
    }

    textFieldTank6.onFocusChanged:
    {
        memotextFieldTank6 = textFieldTank6Text
    }

    textFieldTank1.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK1, textFieldTank1Text)
    }

    textFieldTank2.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK2, textFieldTank2Text)
    }

    textFieldTank3.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK3, textFieldTank3Text)
    }

    textFieldTank4.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK4, textFieldTank4Text)
    }

    textFieldTank5.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK5, textFieldTank5Text)
    }

    textFieldTank6.onTextChanged:
    {
        sendTankTitleChanged(E_TankObjectName.TANK6, textFieldTank6Text)
    }

    textFieldTank1.onAccepted:
    {
        textFieldTank1.focus=false
    }

    textFieldTank2.onAccepted:
    {
        textFieldTank2.focus=false
    }

    textFieldTank3.onAccepted:
    {
        textFieldTank3.focus=false
    }

    textFieldTank4.onAccepted:
    {
        textFieldTank4.focus=false
    }

    textFieldTank5.onAccepted:
    {
        textFieldTank5.focus=false
    }

    textFieldTank6.onAccepted:
    {
        textFieldTank6.focus=false
    }

    Keys.onEscapePressed:
    {
        textFieldTank1Text = memotextFieldTank1
        textFieldTank2Text = memotextFieldTank2
        textFieldTank3Text = memotextFieldTank3
        textFieldTank4Text = memotextFieldTank4
        textFieldTank5Text = memotextFieldTank5
        textFieldTank6Text = memotextFieldTank6
        textFieldTank1.focus=false
        textFieldTank2.focus=false
        textFieldTank3.focus=false
        textFieldTank4.focus=false
        textFieldTank5.focus=false
        textFieldTank6.focus=false
    }


    function memoriseOtherTitleText()
    {
        if(!textFieldTank1.activeFocus)
        {
            memotextFieldTank1 = textFieldTank1Text

        }
        if(!textFieldTank2.activeFocus)
        {
            memotextFieldTank2 = textFieldTank2Text

        }
        if(!textFieldTank3.activeFocus)
        {
            memotextFieldTank3 = textFieldTank3Text

        }

        if(!textFieldTank4.activeFocus)
        {
            memotextFieldTank4 = textFieldTank4Text

        }

        if(!textFieldTank5.activeFocus)
        {
            memotextFieldTank5 = textFieldTank5Text

        }

        if(!textFieldTank6.activeFocus)
        {
            memotextFieldTank6 = textFieldTank6Text

        }
    }

    function setTankTitleText(tankObjectID, titleText)
    {
        //        console.log("setTankIsVisible ID: " + tankObjectID + " ,is visible" + isVisible)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            textFieldTank1Text = titleText;
            memotextFieldTank1 = titleText;
            break;
        case E_TankObjectName.TANK2:
            textFieldTank2Text = titleText;
            memotextFieldTank2 = titleText;
            break;
        case E_TankObjectName.TANK3:
            textFieldTank3Text = titleText;
            memotextFieldTank3 = titleText;
            break;
        case E_TankObjectName.TANK4:
            textFieldTank4Text = titleText;
            memotextFieldTank4 = titleText;
            break;
        case E_TankObjectName.TANK5:
            textFieldTank5Text = titleText;
            memotextFieldTank5 = titleText;
            break;
        case E_TankObjectName.TANK6:
            textFieldTank6Text = titleText;
            memotextFieldTank6 = titleText;
            break;
        }
    }

    function setTankIsVisible(tankObjectID, isVisible)
    {
        //        console.log("setTankIsVisible ID: " + tankObjectID + " ,is visible" + isVisible)

        switch(tankObjectID)
        {
        case E_TankObjectName.TANK1:
            checkBoxTank1Checked = isVisible;
            break;
        case E_TankObjectName.TANK2:
            checkBoxTank2Checked = isVisible;
            break;
        case E_TankObjectName.TANK3:
            checkBoxTank3Checked = isVisible;
            break;
        case E_TankObjectName.TANK4:
            checkBoxTank4Checked = isVisible;
            break;
        case E_TankObjectName.TANK5:
            checkBoxTank5Checked = isVisible;
            break;
        case E_TankObjectName.TANK6:
            checkBoxTank6Checked = isVisible;
            break;
        }
    }
}
