/****************************************************************************
** Form interface generated from reading ui file './maingui.ui'
**
** Created: Tue Jun 18 15:39:09 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>
#include <Qt3Support/Q3TextView>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QSpinBox;
class QTabWidget;
class Q3TextView;

class MainGui : public QWidget
{
    Q_OBJECT

public:
    MainGui( QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );
    ~MainGui();

    QGroupBox* GroupBox1;
    QLabel* canPortLabel;
    QSpinBox* canPort;
    QButtonGroup* ButtonGroup4;
    QRadioButton* SimulationNoRadioButton;
    QRadioButton* SimulationYesRadioButton;
    QPushButton* initModuleButton;
    QGroupBox* datalog;
    QPushButton* clearCANopenLogButton;
    QGroupBox* canMessageLogBox;
    Q3TextView* canLogView;
    QGroupBox* GroupBox11;
    QPushButton* PushButton65;
    Q3TextView* canReceiveLog;
    QGroupBox* sendMessagesBox;
    QTabWidget* TabWidget4;
    QWidget* tab;
    QLabel* TextLabel2_2;
    QLabel* TextLabel3_2;
    QLineEdit* canData0;
    QLineEdit* canData1;
    QLineEdit* canData2;
    QLineEdit* canData3;
    QLineEdit* canData7;
    QLineEdit* canData6;
    QLineEdit* canData5;
    QLineEdit* canData4;
    QLineEdit* canIdentifier;
    QPushButton* sendCanButton;
    QButtonGroup* canMessageDataType;
    QRadioButton* canHexFormat;
    QRadioButton* canBinFormat;
    QRadioButton* canDecFormat;
    QCheckBox* canRTR;
    QCheckBox* canCountOfByteActiv;
    QSpinBox* canCountOfByte;
    QPushButton* readCanButton;
    QWidget* tab_2;
    QCheckBox* canopenPDOWFlag;
    QCheckBox* canopenPDOReadWrite;
    QLabel* canopenDeviceIdLabel_3;
    QSpinBox* canopenPDODeviceId;
    QLabel* canopenDataLabel_3;
    QLineEdit* canopenPDOData0;
    QLineEdit* canopenPDOData1;
    QLineEdit* canopenPDOData2;
    QLineEdit* canopenPDOData3;
    QLineEdit* canopenPDOData7;
    QLineEdit* canopenPDOData6;
    QLineEdit* canopenPDOData5;
    QLineEdit* canopenPDOData4;
    QButtonGroup* canopenPDODatatypeGroup;
    QRadioButton* canopenPDOHexFormat;
    QRadioButton* canopenPDOBinFormat;
    QRadioButton* canopenPDODecFormat;
    QPushButton* sendPDOButton;
    QWidget* tab_3;
    QSpinBox* canopenSDODeviceId;
    QLabel* canopenDeviceIdLabel_3_3;
    QLabel* canopenDataLabel_3_2;
    QLabel* TextLabel1;
    QLineEdit* canopenSDOData4;
    QLineEdit* canopenSDOData7;
    QLineEdit* canopenSDOData6;
    QLineEdit* canopenSDOData5;
    QLineEdit* canopenSDOData3;
    QLineEdit* canopenSDOData2;
    QLineEdit* canopenSDOData1;
    QComboBox* canopenSDOCommandSpecifier;
    QCheckBox* canopenSDOReadWrite;
    QCheckBox* canopenSDOWFlag;
    QButtonGroup* canopenSDOExpedited;
    QRadioButton* RadioButton92;
    QRadioButton* canopenSDONormal;
    QButtonGroup* canopenSDODatatypeGroup;
    QRadioButton* canopenSDOBinFormat;
    QRadioButton* canopenSDOHexFormat;
    QRadioButton* canopenSDODecFormat;
    QPushButton* sendSDOButton;
    QWidget* tab_4;
    QComboBox* nmtState;
    QLabel* nmtStateLabel_3;
    QSpinBox* canopenNMTDeviceId;
    QLabel* canopenDeviceIdLabel_3_2;
    QPushButton* sendNMTButton;
    QWidget* tab_5;
    QPushButton* sendSyncButton;
    QWidget* tab_6;
    QLabel* canopenDeviceIdLabel_3_2_2;
    QPushButton* readDictEntry;
    QLabel* TextLabel1_2;
    QLabel* TextLabel2;
    QButtonGroup* canopenDictDatatypeGroup;
    QRadioButton* canopenDictHexFormat;
    QRadioButton* canopenDictBinFormat;
    QRadioButton* canopenDictDecFormat;
    QLabel* TextLabel3;
    QLineEdit* canopenDictData1;
    QLineEdit* canopenDictData2;
    QLineEdit* canopenDictData3;
    QLineEdit* canopenDictData4;
    QLineEdit* canopenDictData5;
    QLineEdit* canopenDictData6;
    QLineEdit* canopenDictData7;
    QLineEdit* canopenDictData8;
    QLineEdit* canopenDictData9;
    QLineEdit* canopenDictData10;
    QLineEdit* canopenDictData11;
    QLineEdit* canopenDictData12;
    QLineEdit* canopenDictData13;
    QLineEdit* canopenDictData14;
    QLineEdit* canopenDictSubIndex;
    QLineEdit* canopenDictIndex;
    QSpinBox* canopenDictDeviceId;
    QLineEdit* canopenDictData0;
    QPushButton* writeDictEntry;
    QPushButton* viewTransferTableButton;
    QWidget* tab_7;
    QLabel* canopenDeviceIdLabel_3_4;
    QPushButton* writePVarButton;
    QLineEdit* canopenPVarData1;
    QLineEdit* canopenPVarData6;
    QLabel* canopenDataLabel_3_3;
    QLineEdit* canopenPVarData3;
    QLineEdit* canopenPVarData0;
    QLineEdit* canopenPVarData4;
    QLineEdit* canopenPVarData2;
    QLineEdit* canopenPVarData5;
    QLineEdit* canopenPVarData7;
    QPushButton* downloadPVarButton;
    QButtonGroup* canopenPDODatatypeGroup_2;
    QRadioButton* canopenPVarHexFormat;
    QRadioButton* canopenPVarBinFormat;
    QRadioButton* canopenPVarDecFormat;
    QButtonGroup* ButtonGroup8;
    QRadioButton* canopenPVarLater;
    QRadioButton* canopenPVarNow;
    QSpinBox* canopenPVarDeviceId;
    QPushButton* showPVarButton;
    QPushButton* readPVarButton;

public slots:
    virtual void canBINClicked( );
    virtual void canDECClicked( );
    virtual void canHEXClicked( );
    virtual void canopenDictBinClicked( );
    virtual void canopenDictDecClicked( );
    virtual void canopenDictHexClicked( );
    virtual void canopenDictRead( );
    virtual void canopenDictWrite( );
    virtual void canopenPDOBinClicked( );
    virtual void canopenPDODecClicked( );
    virtual void canopenPDOHexClicked( );
    virtual void canopenPVarBinClicked( );
    virtual void canopenPVarDecClicked( );
    virtual void canopenPVarDownload( );
    virtual void canopenPVarHexClicked( );
    virtual void canopenPVarShow( );
    virtual void canopenPVarWrite( );
    virtual void canopenSDOBinClicked( );
    virtual void canopenSDODecClicked( );
    virtual void canopenSDOHexClicked( );
    virtual void clearCANSentLog( );
    virtual void clearCanReceiveLog( );
    virtual void initModule( );
    virtual void new_slot();
    virtual void portChanged( );
    virtual void readCan( );
    virtual void restartNode( );
    virtual void sendCan( );
    virtual void sendNMT( );
    virtual void sendPDO( );
    virtual void sendSDO( );
    virtual void sendSync( );
    virtual void simulationNo( );
    virtual void simulationYes( );
    virtual void viewTransferTable( );

};

#endif // FORM1_H
