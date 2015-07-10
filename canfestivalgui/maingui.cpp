/****************************************************************************
** Form implementation generated from reading ui file './maingui.ui'
**
** Created: Tue Jun 18 15:39:10 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "maingui.h"

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qtextview.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a MainGui which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
MainGui::MainGui( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "form1" );
    resize( 996, 689 ); 
    setCaption( tr( "CANFestival Gui" ) );

    GroupBox1 = new QGroupBox( this, "GroupBox1" );
    GroupBox1->setGeometry( QRect( 10, 0, 620, 100 ) ); 
    GroupBox1->setTitle( tr( "Hardware" ) );

    canPortLabel = new QLabel( GroupBox1, "canPortLabel" );
    canPortLabel->setGeometry( QRect( 260, 45, 108, 17 ) ); 
    canPortLabel->setText( tr( "CAN Port to use:" ) );

    canPort = new QSpinBox( GroupBox1, "canPort" );
    canPort->setGeometry( QRect( 380, 40, 58, 25 ) ); 
    canPort->setMaxValue( 1 );
    canPort->setValue( 1 );
    QToolTip::add(  canPort, tr( "Choose the CAN port you want" ) );

    ButtonGroup4 = new QButtonGroup( GroupBox1, "ButtonGroup4" );
    ButtonGroup4->setGeometry( QRect( 10, 30, 180, 50 ) ); 
    ButtonGroup4->setTitle( tr( "Only Simulation" ) );

    SimulationNoRadioButton = new QRadioButton( ButtonGroup4, "SimulationNoRadioButton" );
    SimulationNoRadioButton->setGeometry( QRect( 90, 20, 42, 21 ) ); 
    SimulationNoRadioButton->setText( tr( "&No" ) );
    SimulationNoRadioButton->setChecked( TRUE );

    SimulationYesRadioButton = new QRadioButton( ButtonGroup4, "SimulationYesRadioButton" );
    SimulationYesRadioButton->setGeometry( QRect( 20, 20, 49, 21 ) ); 
    SimulationYesRadioButton->setText( tr( "&Yes" ) );
    SimulationYesRadioButton->setChecked( FALSE );

    initModuleButton = new QPushButton( GroupBox1, "initModuleButton" );
    initModuleButton->setGeometry( QRect( 451, 40, 150, 21 ) ); 
    initModuleButton->setText( tr( "&Initialize CANPort" ) );
    QToolTip::add(  initModuleButton, tr( "Load/Unload the driver module" ) );

    datalog = new QGroupBox( this, "datalog" );
    datalog->setGeometry( QRect( 640, 0, 370, 440 ) ); 
    datalog->setTitle( tr( "Data logger" ) );

    clearCANopenLogButton = new QPushButton( datalog, "clearCANopenLogButton" );
    clearCANopenLogButton->setGeometry( QRect( 10, 410, 340, 21 ) ); 
    clearCANopenLogButton->setText( tr( "Clear Can send messages" ) );

    canMessageLogBox = new QGroupBox( datalog, "canMessageLogBox" );
    canMessageLogBox->setGeometry( QRect( 10, 20, 350, 380 ) ); 
    canMessageLogBox->setTitle( tr( "All CAN SENT Messages (including CANopen)" ) );

    canLogView = new QTextView( canMessageLogBox, "canLogView" );
    canLogView->setGeometry( QRect( 10, 20, 330, 350 ) ); 
    canLogView->setDragAutoScroll( TRUE );

    GroupBox11 = new QGroupBox( this, "GroupBox11" );
    GroupBox11->setGeometry( QRect( 10, 450, 1000, 210 ) ); 
    GroupBox11->setTitle( tr( "CAN Bus receive Log" ) );

    PushButton65 = new QPushButton( GroupBox11, "PushButton65" );
    PushButton65->setGeometry( QRect( 930, 20, 50, 171 ) ); 
    PushButton65->setText( tr( "C&lear" ) );

    canReceiveLog = new QTextView( GroupBox11, "canReceiveLog" );
    canReceiveLog->setGeometry( QRect( 10, 20, 910, 170 ) ); 

    sendMessagesBox = new QGroupBox( this, "sendMessagesBox" );
    sendMessagesBox->setGeometry( QRect( 10, 110, 620, 330 ) ); 
    sendMessagesBox->setTitle( tr( "Send Messages" ) );

    TabWidget4 = new QTabWidget( sendMessagesBox, "TabWidget4" );
    TabWidget4->setGeometry( QRect( 10, 40, 600, 280 ) ); 

    tab = new QWidget( TabWidget4, "tab" );

    TextLabel2_2 = new QLabel( tab, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 10, 30, 90, 17 ) ); 
    TextLabel2_2->setText( tr( "CAN Identifier" ) );

    TextLabel3_2 = new QLabel( tab, "TextLabel3_2" );
    TextLabel3_2->setGeometry( QRect( 130, 30, 65, 17 ) ); 
    TextLabel3_2->setText( tr( "CAN Data" ) );

    canData0 = new QLineEdit( tab, "canData0" );
    canData0->setGeometry( QRect( 130, 50, 80, 22 ) ); 
    canData0->setText( tr( "0x0" ) );
    canData0->setMaxLength( 8 );
    canData0->setAlignment( int( QLineEdit::AlignRight ) );

    canData1 = new QLineEdit( tab, "canData1" );
    canData1->setGeometry( QRect( 220, 50, 80, 22 ) ); 
    canData1->setText( tr( "0x0" ) );
    canData1->setMaxLength( 8 );
    canData1->setAlignment( int( QLineEdit::AlignRight ) );

    canData2 = new QLineEdit( tab, "canData2" );
    canData2->setGeometry( QRect( 310, 50, 80, 22 ) ); 
    canData2->setText( tr( "0x0" ) );
    canData2->setMaxLength( 8 );
    canData2->setAlignment( int( QLineEdit::AlignRight ) );

    canData3 = new QLineEdit( tab, "canData3" );
    canData3->setGeometry( QRect( 400, 50, 80, 22 ) ); 
    canData3->setText( tr( "0x0" ) );
    canData3->setMaxLength( 8 );
    canData3->setAlignment( int( QLineEdit::AlignRight ) );

    canData7 = new QLineEdit( tab, "canData7" );
    canData7->setGeometry( QRect( 400, 80, 80, 22 ) ); 
    canData7->setText( tr( "0x0" ) );
    canData7->setMaxLength( 8 );
    canData7->setAlignment( int( QLineEdit::AlignRight ) );

    canData6 = new QLineEdit( tab, "canData6" );
    canData6->setGeometry( QRect( 310, 80, 80, 22 ) ); 
    canData6->setText( tr( "0x0" ) );
    canData6->setMaxLength( 8 );
    canData6->setAlignment( int( QLineEdit::AlignRight ) );

    canData5 = new QLineEdit( tab, "canData5" );
    canData5->setGeometry( QRect( 220, 80, 80, 22 ) ); 
    canData5->setText( tr( "0x0" ) );
    canData5->setMaxLength( 8 );
    canData5->setAlignment( int( QLineEdit::AlignRight ) );

    canData4 = new QLineEdit( tab, "canData4" );
    canData4->setGeometry( QRect( 130, 80, 80, 22 ) ); 
    canData4->setText( tr( "0x0" ) );
    canData4->setMaxLength( 8 );
    canData4->setAlignment( int( QLineEdit::AlignRight ) );

    canIdentifier = new QLineEdit( tab, "canIdentifier" );
    canIdentifier->setGeometry( QRect( 10, 50, 100, 22 ) ); 
    canIdentifier->setText( tr( "0x0" ) );
    canIdentifier->setMaxLength( 11 );
    canIdentifier->setAlignment( int( QLineEdit::AlignRight ) );

    sendCanButton = new QPushButton( tab, "sendCanButton" );
    sendCanButton->setGeometry( QRect( 10, 210, 120, 30 ) ); 
    sendCanButton->setText( tr( "&Send CAN" ) );

    canMessageDataType = new QButtonGroup( tab, "canMessageDataType" );
    canMessageDataType->setGeometry( QRect( 500, 20, 90, 90 ) ); 
    canMessageDataType->setTitle( tr( "Data Typ" ) );

    canHexFormat = new QRadioButton( canMessageDataType, "canHexFormat" );
    canHexFormat->setGeometry( QRect( 10, 20, 49, 21 ) ); 
    canHexFormat->setText( tr( "Hex" ) );
    canHexFormat->setChecked( TRUE );

    canBinFormat = new QRadioButton( canMessageDataType, "canBinFormat" );
    canBinFormat->setGeometry( QRect( 10, 40, 44, 21 ) ); 
    canBinFormat->setText( tr( "Bin" ) );

    canDecFormat = new QRadioButton( canMessageDataType, "canDecFormat" );
    canDecFormat->setGeometry( QRect( 10, 60, 50, 21 ) ); 
    canDecFormat->setText( tr( "Dec" ) );

    canRTR = new QCheckBox( tab, "canRTR" );
    canRTR->setGeometry( QRect( 10, 120, 143, 26 ) ); 
    canRTR->setText( tr( "RTR (Checked: 1)" ) );

    canCountOfByteActiv = new QCheckBox( tab, "canCountOfByteActiv" );
    canCountOfByteActiv->setGeometry( QRect( 10, 160, 141, 19 ) ); 
    canCountOfByteActiv->setText( tr( "Send Count of Bytes:" ) );

    canCountOfByte = new QSpinBox( tab, "canCountOfByte" );
    canCountOfByte->setEnabled( TRUE );
    canCountOfByte->setGeometry( QRect( 170, 157, 56, 23 ) ); 
    canCountOfByte->setMaxValue( 8 );
    canCountOfByte->setMinValue( 1 );
    canCountOfByte->setValue( 8 );

    readCanButton = new QPushButton( tab, "readCanButton" );
    readCanButton->setGeometry( QRect( 160, 210, 121, 31 ) ); 
    readCanButton->setText( tr( "&Read CAN" ) );
    TabWidget4->insertTab( tab, tr( "&CAN Message" ) );

    tab_2 = new QWidget( TabWidget4, "tab_2" );

    canopenPDOWFlag = new QCheckBox( tab_2, "canopenPDOWFlag" );
    canopenPDOWFlag->setGeometry( QRect( 250, 10, 250, 26 ) ); 
    canopenPDOWFlag->setText( tr( "Listen w message before send" ) );

    canopenPDOReadWrite = new QCheckBox( tab_2, "canopenPDOReadWrite" );
    canopenPDOReadWrite->setGeometry( QRect( 250, 40, 147, 26 ) ); 
    canopenPDOReadWrite->setText( tr( "Read (activ)/Write" ) );

    canopenDeviceIdLabel_3 = new QLabel( tab_2, "canopenDeviceIdLabel_3" );
    canopenDeviceIdLabel_3->setGeometry( QRect( 20, 20, 131, 17 ) ); 
    canopenDeviceIdLabel_3->setText( tr( "CANopen Device ID" ) );

    canopenPDODeviceId = new QSpinBox( tab_2, "canopenPDODeviceId" );
    canopenPDODeviceId->setGeometry( QRect( 160, 16, 58, 25 ) ); 
    canopenPDODeviceId->setMaxValue( 127 );
    canopenPDODeviceId->setValue( 1 );

    canopenDataLabel_3 = new QLabel( tab_2, "canopenDataLabel_3" );
    canopenDataLabel_3->setGeometry( QRect( 20, 90, 97, 17 ) ); 
    canopenDataLabel_3->setText( tr( "CANopen Data" ) );

    canopenPDOData0 = new QLineEdit( tab_2, "canopenPDOData0" );
    canopenPDOData0->setGeometry( QRect( 60, 120, 80, 22 ) ); 
    canopenPDOData0->setText( tr( "0x0" ) );
    canopenPDOData0->setMaxLength( 8 );
    canopenPDOData0->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData1 = new QLineEdit( tab_2, "canopenPDOData1" );
    canopenPDOData1->setGeometry( QRect( 150, 120, 80, 22 ) ); 
    canopenPDOData1->setText( tr( "0x0" ) );
    canopenPDOData1->setMaxLength( 8 );
    canopenPDOData1->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData2 = new QLineEdit( tab_2, "canopenPDOData2" );
    canopenPDOData2->setGeometry( QRect( 240, 120, 80, 22 ) ); 
    canopenPDOData2->setText( tr( "0x0" ) );
    canopenPDOData2->setMaxLength( 8 );
    canopenPDOData2->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData3 = new QLineEdit( tab_2, "canopenPDOData3" );
    canopenPDOData3->setGeometry( QRect( 330, 120, 80, 22 ) ); 
    canopenPDOData3->setText( tr( "0x0" ) );
    canopenPDOData3->setMaxLength( 8 );
    canopenPDOData3->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData7 = new QLineEdit( tab_2, "canopenPDOData7" );
    canopenPDOData7->setGeometry( QRect( 330, 150, 80, 22 ) ); 
    canopenPDOData7->setText( tr( "0x0" ) );
    canopenPDOData7->setMaxLength( 8 );
    canopenPDOData7->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData6 = new QLineEdit( tab_2, "canopenPDOData6" );
    canopenPDOData6->setGeometry( QRect( 240, 150, 80, 22 ) ); 
    canopenPDOData6->setText( tr( "0x0" ) );
    canopenPDOData6->setMaxLength( 8 );
    canopenPDOData6->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData5 = new QLineEdit( tab_2, "canopenPDOData5" );
    canopenPDOData5->setGeometry( QRect( 150, 150, 80, 22 ) ); 
    canopenPDOData5->setText( tr( "0x0" ) );
    canopenPDOData5->setMaxLength( 8 );
    canopenPDOData5->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDOData4 = new QLineEdit( tab_2, "canopenPDOData4" );
    canopenPDOData4->setGeometry( QRect( 60, 150, 80, 22 ) ); 
    canopenPDOData4->setText( tr( "0x0" ) );
    canopenPDOData4->setMaxLength( 8 );
    canopenPDOData4->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPDODatatypeGroup = new QButtonGroup( tab_2, "canopenPDODatatypeGroup" );
    canopenPDODatatypeGroup->setGeometry( QRect( 480, 100, 80, 90 ) ); 
    canopenPDODatatypeGroup->setTitle( tr( "Data Typ" ) );

    canopenPDOHexFormat = new QRadioButton( canopenPDODatatypeGroup, "canopenPDOHexFormat" );
    canopenPDOHexFormat->setGeometry( QRect( 10, 20, 49, 21 ) ); 
    canopenPDOHexFormat->setText( tr( "Hex" ) );
    canopenPDOHexFormat->setChecked( TRUE );

    canopenPDOBinFormat = new QRadioButton( canopenPDODatatypeGroup, "canopenPDOBinFormat" );
    canopenPDOBinFormat->setGeometry( QRect( 10, 40, 44, 21 ) ); 
    canopenPDOBinFormat->setText( tr( "Bin" ) );

    canopenPDODecFormat = new QRadioButton( canopenPDODatatypeGroup, "canopenPDODecFormat" );
    canopenPDODecFormat->setGeometry( QRect( 10, 60, 50, 21 ) ); 
    canopenPDODecFormat->setText( tr( "Dec" ) );

    sendPDOButton = new QPushButton( tab_2, "sendPDOButton" );
    sendPDOButton->setGeometry( QRect( 10, 210, 120, 29 ) ); 
    sendPDOButton->setText( tr( "&Send PDO" ) );
    TabWidget4->insertTab( tab_2, tr( "&PDO" ) );

    tab_3 = new QWidget( TabWidget4, "tab_3" );

    canopenSDODeviceId = new QSpinBox( tab_3, "canopenSDODeviceId" );
    canopenSDODeviceId->setGeometry( QRect( 160, 16, 58, 25 ) ); 
    canopenSDODeviceId->setMaxValue( 127 );
    canopenSDODeviceId->setValue( 1 );

    canopenDeviceIdLabel_3_3 = new QLabel( tab_3, "canopenDeviceIdLabel_3_3" );
    canopenDeviceIdLabel_3_3->setGeometry( QRect( 20, 20, 131, 17 ) ); 
    canopenDeviceIdLabel_3_3->setText( tr( "CANopen Device ID" ) );

    canopenDataLabel_3_2 = new QLabel( tab_3, "canopenDataLabel_3_2" );
    canopenDataLabel_3_2->setGeometry( QRect( 20, 120, 97, 17 ) ); 
    canopenDataLabel_3_2->setText( tr( "CANopen Data" ) );

    TextLabel1 = new QLabel( tab_3, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 20, 80, 123, 17 ) ); 
    TextLabel1->setText( tr( "Command Specifier" ) );

    canopenSDOData4 = new QLineEdit( tab_3, "canopenSDOData4" );
    canopenSDOData4->setGeometry( QRect( 400, 120, 80, 22 ) ); 
    canopenSDOData4->setText( tr( "0x0" ) );
    canopenSDOData4->setMaxLength( 8 );
    canopenSDOData4->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData7 = new QLineEdit( tab_3, "canopenSDOData7" );
    canopenSDOData7->setGeometry( QRect( 310, 150, 80, 22 ) ); 
    canopenSDOData7->setText( tr( "0x0" ) );
    canopenSDOData7->setMaxLength( 8 );
    canopenSDOData7->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData6 = new QLineEdit( tab_3, "canopenSDOData6" );
    canopenSDOData6->setGeometry( QRect( 220, 150, 80, 22 ) ); 
    canopenSDOData6->setText( tr( "0x0" ) );
    canopenSDOData6->setMaxLength( 8 );
    canopenSDOData6->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData5 = new QLineEdit( tab_3, "canopenSDOData5" );
    canopenSDOData5->setGeometry( QRect( 130, 150, 80, 22 ) ); 
    canopenSDOData5->setText( tr( "0x0" ) );
    canopenSDOData5->setMaxLength( 8 );
    canopenSDOData5->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData3 = new QLineEdit( tab_3, "canopenSDOData3" );
    canopenSDOData3->setGeometry( QRect( 310, 120, 80, 22 ) ); 
    canopenSDOData3->setText( tr( "0x0" ) );
    canopenSDOData3->setMaxLength( 8 );
    canopenSDOData3->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData2 = new QLineEdit( tab_3, "canopenSDOData2" );
    canopenSDOData2->setGeometry( QRect( 220, 120, 80, 22 ) ); 
    canopenSDOData2->setText( tr( "0x0" ) );
    canopenSDOData2->setMaxLength( 8 );
    canopenSDOData2->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOData1 = new QLineEdit( tab_3, "canopenSDOData1" );
    canopenSDOData1->setGeometry( QRect( 130, 120, 80, 22 ) ); 
    canopenSDOData1->setText( tr( "0x0" ) );
    canopenSDOData1->setMaxLength( 8 );
    canopenSDOData1->setAlignment( int( QLineEdit::AlignRight ) );

    canopenSDOCommandSpecifier = new QComboBox( FALSE, tab_3, "canopenSDOCommandSpecifier" );
    canopenSDOCommandSpecifier->insertItem( tr( "Init Domain Download" ) );
    canopenSDOCommandSpecifier->insertItem( tr( "Download Domain Segment" ) );
    canopenSDOCommandSpecifier->insertItem( tr( "Init Domain Upload" ) );
    canopenSDOCommandSpecifier->insertItem( tr( "Upload Domain Segment" ) );
    canopenSDOCommandSpecifier->insertItem( tr( "Abort Domain Transfer" ) );
    canopenSDOCommandSpecifier->setGeometry( QRect( 160, 80, 260, 20 ) ); 

    canopenSDOReadWrite = new QCheckBox( tab_3, "canopenSDOReadWrite" );
    canopenSDOReadWrite->setGeometry( QRect( 230, 40, 147, 26 ) ); 
    canopenSDOReadWrite->setText( tr( "Read (activ)/Write" ) );

    canopenSDOWFlag = new QCheckBox( tab_3, "canopenSDOWFlag" );
    canopenSDOWFlag->setGeometry( QRect( 230, 10, 250, 26 ) ); 
    canopenSDOWFlag->setText( tr( "Listen w message before send" ) );

    canopenSDOExpedited = new QButtonGroup( tab_3, "canopenSDOExpedited" );
    canopenSDOExpedited->setGeometry( QRect( 470, 10, 110, 70 ) ); 
    canopenSDOExpedited->setTitle( tr( "Transfer" ) );

    RadioButton92 = new QRadioButton( canopenSDOExpedited, "RadioButton92" );
    RadioButton92->setGeometry( QRect( 10, 40, 87, 21 ) ); 
    RadioButton92->setText( tr( "Expedited" ) );

    canopenSDONormal = new QRadioButton( canopenSDOExpedited, "canopenSDONormal" );
    canopenSDONormal->setGeometry( QRect( 10, 20, 69, 21 ) ); 
    canopenSDONormal->setText( tr( "Normal" ) );
    canopenSDONormal->setChecked( TRUE );

    canopenSDODatatypeGroup = new QButtonGroup( tab_3, "canopenSDODatatypeGroup" );
    canopenSDODatatypeGroup->setGeometry( QRect( 500, 110, 80, 90 ) ); 
    canopenSDODatatypeGroup->setTitle( tr( "Data Typ" ) );

    canopenSDOBinFormat = new QRadioButton( canopenSDODatatypeGroup, "canopenSDOBinFormat" );
    canopenSDOBinFormat->setGeometry( QRect( 10, 40, 44, 21 ) ); 
    canopenSDOBinFormat->setText( tr( "Bin" ) );

    canopenSDOHexFormat = new QRadioButton( canopenSDODatatypeGroup, "canopenSDOHexFormat" );
    canopenSDOHexFormat->setGeometry( QRect( 10, 20, 49, 21 ) ); 
    canopenSDOHexFormat->setText( tr( "Hex" ) );
    canopenSDOHexFormat->setChecked( TRUE );

    canopenSDODecFormat = new QRadioButton( canopenSDODatatypeGroup, "canopenSDODecFormat" );
    canopenSDODecFormat->setGeometry( QRect( 10, 60, 50, 21 ) ); 
    canopenSDODecFormat->setText( tr( "Dec" ) );

    sendSDOButton = new QPushButton( tab_3, "sendSDOButton" );
    sendSDOButton->setEnabled( FALSE );
    sendSDOButton->setGeometry( QRect( 10, 210, 120, 29 ) ); 
    sendSDOButton->setText( tr( "&Send SDO" ) );
    TabWidget4->insertTab( tab_3, tr( "S&DO" ) );

    tab_4 = new QWidget( TabWidget4, "tab_4" );

    nmtState = new QComboBox( FALSE, tab_4, "nmtState" );
    nmtState->insertItem( tr( "Start Remote Node" ) );
    nmtState->insertItem( tr( "Stop Remote Node" ) );
    nmtState->insertItem( tr( "Pre Operational State" ) );
    nmtState->insertItem( tr( "Reset Node" ) );
    nmtState->insertItem( tr( "Reset Communication" ) );
    nmtState->setEnabled( TRUE );
    nmtState->setGeometry( QRect( 180, 90, 281, 21 ) ); 

    nmtStateLabel_3 = new QLabel( tab_4, "nmtStateLabel_3" );
    nmtStateLabel_3->setGeometry( QRect( 50, 90, 69, 17 ) ); 
    nmtStateLabel_3->setText( tr( "NMT State" ) );

    canopenNMTDeviceId = new QSpinBox( tab_4, "canopenNMTDeviceId" );
    canopenNMTDeviceId->setGeometry( QRect( 160, 16, 58, 25 ) ); 
    canopenNMTDeviceId->setMaxValue( 127 );
    canopenNMTDeviceId->setValue( 1 );

    canopenDeviceIdLabel_3_2 = new QLabel( tab_4, "canopenDeviceIdLabel_3_2" );
    canopenDeviceIdLabel_3_2->setGeometry( QRect( 20, 20, 131, 17 ) ); 
    canopenDeviceIdLabel_3_2->setText( tr( "CANopen Device ID" ) );

    sendNMTButton = new QPushButton( tab_4, "sendNMTButton" );
    sendNMTButton->setGeometry( QRect( 10, 210, 120, 30 ) ); 
    sendNMTButton->setText( tr( "&Send NMT" ) );
    TabWidget4->insertTab( tab_4, tr( "&NMT" ) );

    tab_5 = new QWidget( TabWidget4, "tab_5" );

    sendSyncButton = new QPushButton( tab_5, "sendSyncButton" );
    sendSyncButton->setGeometry( QRect( 10, 210, 120, 30 ) ); 
    sendSyncButton->setText( tr( "&Send Sync" ) );
    TabWidget4->insertTab( tab_5, tr( "S&ync" ) );

    tab_6 = new QWidget( TabWidget4, "tab_6" );

    canopenDeviceIdLabel_3_2_2 = new QLabel( tab_6, "canopenDeviceIdLabel_3_2_2" );
    canopenDeviceIdLabel_3_2_2->setGeometry( QRect( 20, 20, 131, 17 ) ); 
    canopenDeviceIdLabel_3_2_2->setText( tr( "CANopen Device ID" ) );

    readDictEntry = new QPushButton( tab_6, "readDictEntry" );
    readDictEntry->setGeometry( QRect( 10, 210, 120, 30 ) ); 
    readDictEntry->setText( tr( "&Read Entry" ) );

    TextLabel1_2 = new QLabel( tab_6, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 20, 60, 36, 17 ) ); 
    TextLabel1_2->setText( tr( "Index" ) );

    TextLabel2 = new QLabel( tab_6, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 18, 95, 59, 17 ) ); 
    TextLabel2->setText( tr( "Subindex" ) );

    canopenDictDatatypeGroup = new QButtonGroup( tab_6, "canopenDictDatatypeGroup" );
    canopenDictDatatypeGroup->setGeometry( QRect( 500, 10, 80, 90 ) ); 
    canopenDictDatatypeGroup->setTitle( tr( "Data Typ" ) );

    canopenDictHexFormat = new QRadioButton( canopenDictDatatypeGroup, "canopenDictHexFormat" );
    canopenDictHexFormat->setGeometry( QRect( 10, 20, 49, 21 ) ); 
    canopenDictHexFormat->setText( tr( "Hex" ) );
    canopenDictHexFormat->setChecked( TRUE );

    canopenDictBinFormat = new QRadioButton( canopenDictDatatypeGroup, "canopenDictBinFormat" );
    canopenDictBinFormat->setGeometry( QRect( 10, 40, 44, 21 ) ); 
    canopenDictBinFormat->setText( tr( "Bin" ) );

    canopenDictDecFormat = new QRadioButton( canopenDictDatatypeGroup, "canopenDictDecFormat" );
    canopenDictDecFormat->setGeometry( QRect( 10, 60, 50, 21 ) ); 
    canopenDictDecFormat->setText( tr( "Dec" ) );

    TextLabel3 = new QLabel( tab_6, "TextLabel3" );
    TextLabel3->setGeometry( QRect( 28, 125, 30, 17 ) ); 
    TextLabel3->setText( tr( "Data" ) );

    canopenDictData1 = new QLineEdit( tab_6, "canopenDictData1" );
    canopenDictData1->setGeometry( QRect( 220, 120, 80, 22 ) ); 
    canopenDictData1->setText( tr( "0x0" ) );
    canopenDictData1->setMaxLength( 8 );
    canopenDictData1->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData2 = new QLineEdit( tab_6, "canopenDictData2" );
    canopenDictData2->setGeometry( QRect( 310, 120, 80, 22 ) ); 
    canopenDictData2->setText( tr( "0x0" ) );
    canopenDictData2->setMaxLength( 8 );
    canopenDictData2->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData3 = new QLineEdit( tab_6, "canopenDictData3" );
    canopenDictData3->setGeometry( QRect( 400, 120, 80, 22 ) ); 
    canopenDictData3->setText( tr( "0x0" ) );
    canopenDictData3->setMaxLength( 8 );
    canopenDictData3->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData4 = new QLineEdit( tab_6, "canopenDictData4" );
    canopenDictData4->setGeometry( QRect( 490, 120, 80, 22 ) ); 
    canopenDictData4->setText( tr( "0x0" ) );
    canopenDictData4->setMaxLength( 8 );
    canopenDictData4->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData5 = new QLineEdit( tab_6, "canopenDictData5" );
    canopenDictData5->setGeometry( QRect( 130, 150, 80, 22 ) ); 
    canopenDictData5->setText( tr( "0x0" ) );
    canopenDictData5->setMaxLength( 8 );
    canopenDictData5->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData6 = new QLineEdit( tab_6, "canopenDictData6" );
    canopenDictData6->setGeometry( QRect( 220, 150, 80, 22 ) ); 
    canopenDictData6->setText( tr( "0x0" ) );
    canopenDictData6->setMaxLength( 8 );
    canopenDictData6->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData7 = new QLineEdit( tab_6, "canopenDictData7" );
    canopenDictData7->setGeometry( QRect( 310, 150, 80, 22 ) ); 
    canopenDictData7->setText( tr( "0x0" ) );
    canopenDictData7->setMaxLength( 8 );
    canopenDictData7->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData8 = new QLineEdit( tab_6, "canopenDictData8" );
    canopenDictData8->setGeometry( QRect( 400, 150, 80, 22 ) ); 
    canopenDictData8->setText( tr( "0x0" ) );
    canopenDictData8->setMaxLength( 8 );
    canopenDictData8->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData9 = new QLineEdit( tab_6, "canopenDictData9" );
    canopenDictData9->setGeometry( QRect( 490, 150, 80, 22 ) ); 
    canopenDictData9->setText( tr( "0x0" ) );
    canopenDictData9->setMaxLength( 8 );
    canopenDictData9->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData10 = new QLineEdit( tab_6, "canopenDictData10" );
    canopenDictData10->setGeometry( QRect( 130, 180, 80, 22 ) ); 
    canopenDictData10->setText( tr( "0x0" ) );
    canopenDictData10->setMaxLength( 8 );
    canopenDictData10->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData11 = new QLineEdit( tab_6, "canopenDictData11" );
    canopenDictData11->setGeometry( QRect( 220, 180, 80, 22 ) ); 
    canopenDictData11->setText( tr( "0x0" ) );
    canopenDictData11->setMaxLength( 8 );
    canopenDictData11->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData12 = new QLineEdit( tab_6, "canopenDictData12" );
    canopenDictData12->setGeometry( QRect( 310, 180, 80, 22 ) ); 
    canopenDictData12->setText( tr( "0x0" ) );
    canopenDictData12->setMaxLength( 8 );
    canopenDictData12->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData13 = new QLineEdit( tab_6, "canopenDictData13" );
    canopenDictData13->setGeometry( QRect( 400, 180, 80, 22 ) ); 
    canopenDictData13->setText( tr( "0x0" ) );
    canopenDictData13->setMaxLength( 8 );
    canopenDictData13->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictData14 = new QLineEdit( tab_6, "canopenDictData14" );
    canopenDictData14->setGeometry( QRect( 490, 180, 80, 22 ) ); 
    canopenDictData14->setText( tr( "0x0" ) );
    canopenDictData14->setMaxLength( 8 );
    canopenDictData14->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictSubIndex = new QLineEdit( tab_6, "canopenDictSubIndex" );
    canopenDictSubIndex->setGeometry( QRect( 130, 90, 80, 22 ) ); 
    canopenDictSubIndex->setText( tr( "0x00" ) );
    canopenDictSubIndex->setMaxLength( 8 );
    canopenDictSubIndex->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictIndex = new QLineEdit( tab_6, "canopenDictIndex" );
    canopenDictIndex->setGeometry( QRect( 70, 60, 140, 22 ) ); 
    canopenDictIndex->setText( tr( "0x0000" ) );
    canopenDictIndex->setMaxLength( 16 );
    canopenDictIndex->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDictDeviceId = new QSpinBox( tab_6, "canopenDictDeviceId" );
    canopenDictDeviceId->setGeometry( QRect( 160, 16, 58, 25 ) ); 
    canopenDictDeviceId->setMaxValue( 127 );
    canopenDictDeviceId->setValue( 1 );

    canopenDictData0 = new QLineEdit( tab_6, "canopenDictData0" );
    canopenDictData0->setGeometry( QRect( 130, 120, 80, 22 ) ); 
    canopenDictData0->setText( tr( "0x0" ) );
    canopenDictData0->setMaxLength( 8 );
    canopenDictData0->setAlignment( int( QLineEdit::AlignRight ) );

    writeDictEntry = new QPushButton( tab_6, "writeDictEntry" );
    writeDictEntry->setGeometry( QRect( 160, 210, 120, 30 ) ); 
    writeDictEntry->setText( tr( "&Write Entry" ) );

    viewTransferTableButton = new QPushButton( tab_6, "viewTransferTableButton" );
    viewTransferTableButton->setEnabled( FALSE );
    viewTransferTableButton->setGeometry( QRect( 310, 210, 156, 29 ) ); 
    viewTransferTableButton->setText( tr( "&View Transfertable" ) );
    TabWidget4->insertTab( tab_6, tr( "&Dictionary" ) );

    tab_7 = new QWidget( TabWidget4, "tab_7" );

    canopenDeviceIdLabel_3_4 = new QLabel( tab_7, "canopenDeviceIdLabel_3_4" );
    canopenDeviceIdLabel_3_4->setGeometry( QRect( 20, 20, 131, 17 ) ); 
    canopenDeviceIdLabel_3_4->setText( tr( "CANopen Device ID" ) );

    writePVarButton = new QPushButton( tab_7, "writePVarButton" );
    writePVarButton->setGeometry( QRect( 10, 170, 186, 29 ) ); 
    writePVarButton->setText( tr( "&Write Process Variable" ) );

    canopenPVarData1 = new QLineEdit( tab_7, "canopenPVarData1" );
    canopenPVarData1->setGeometry( QRect( 220, 70, 80, 22 ) ); 
    canopenPVarData1->setText( tr( "0x0" ) );
    canopenPVarData1->setMaxLength( 8 );
    canopenPVarData1->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData6 = new QLineEdit( tab_7, "canopenPVarData6" );
    canopenPVarData6->setGeometry( QRect( 310, 100, 80, 22 ) ); 
    canopenPVarData6->setText( tr( "0x0" ) );
    canopenPVarData6->setMaxLength( 8 );
    canopenPVarData6->setAlignment( int( QLineEdit::AlignRight ) );

    canopenDataLabel_3_3 = new QLabel( tab_7, "canopenDataLabel_3_3" );
    canopenDataLabel_3_3->setGeometry( QRect( 20, 70, 97, 17 ) ); 
    canopenDataLabel_3_3->setText( tr( "CANopen Data" ) );

    canopenPVarData3 = new QLineEdit( tab_7, "canopenPVarData3" );
    canopenPVarData3->setGeometry( QRect( 400, 70, 80, 22 ) ); 
    canopenPVarData3->setText( tr( "0x0" ) );
    canopenPVarData3->setMaxLength( 8 );
    canopenPVarData3->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData0 = new QLineEdit( tab_7, "canopenPVarData0" );
    canopenPVarData0->setGeometry( QRect( 130, 70, 80, 22 ) ); 
    canopenPVarData0->setText( tr( "0x0" ) );
    canopenPVarData0->setMaxLength( 8 );
    canopenPVarData0->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData4 = new QLineEdit( tab_7, "canopenPVarData4" );
    canopenPVarData4->setGeometry( QRect( 130, 100, 80, 22 ) ); 
    canopenPVarData4->setText( tr( "0x0" ) );
    canopenPVarData4->setMaxLength( 8 );
    canopenPVarData4->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData2 = new QLineEdit( tab_7, "canopenPVarData2" );
    canopenPVarData2->setGeometry( QRect( 310, 70, 80, 22 ) ); 
    canopenPVarData2->setText( tr( "0x0" ) );
    canopenPVarData2->setMaxLength( 8 );
    canopenPVarData2->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData5 = new QLineEdit( tab_7, "canopenPVarData5" );
    canopenPVarData5->setGeometry( QRect( 220, 100, 80, 22 ) ); 
    canopenPVarData5->setText( tr( "0x0" ) );
    canopenPVarData5->setMaxLength( 8 );
    canopenPVarData5->setAlignment( int( QLineEdit::AlignRight ) );

    canopenPVarData7 = new QLineEdit( tab_7, "canopenPVarData7" );
    canopenPVarData7->setGeometry( QRect( 400, 100, 80, 22 ) ); 
    canopenPVarData7->setText( tr( "0x0" ) );
    canopenPVarData7->setMaxLength( 8 );
    canopenPVarData7->setAlignment( int( QLineEdit::AlignRight ) );

    downloadPVarButton = new QPushButton( tab_7, "downloadPVarButton" );
    downloadPVarButton->setGeometry( QRect( 10, 210, 222, 29 ) ); 
    downloadPVarButton->setText( tr( "&Download Process Variables" ) );

    canopenPDODatatypeGroup_2 = new QButtonGroup( tab_7, "canopenPDODatatypeGroup_2" );
    canopenPDODatatypeGroup_2->setGeometry( QRect( 500, 10, 80, 90 ) ); 
    canopenPDODatatypeGroup_2->setTitle( tr( "Data Typ" ) );

    canopenPVarHexFormat = new QRadioButton( canopenPDODatatypeGroup_2, "canopenPVarHexFormat" );
    canopenPVarHexFormat->setGeometry( QRect( 10, 20, 49, 21 ) ); 
    canopenPVarHexFormat->setText( tr( "Hex" ) );
    canopenPVarHexFormat->setChecked( TRUE );

    canopenPVarBinFormat = new QRadioButton( canopenPDODatatypeGroup_2, "canopenPVarBinFormat" );
    canopenPVarBinFormat->setGeometry( QRect( 10, 40, 44, 21 ) ); 
    canopenPVarBinFormat->setText( tr( "Bin" ) );

    canopenPVarDecFormat = new QRadioButton( canopenPDODatatypeGroup_2, "canopenPVarDecFormat" );
    canopenPVarDecFormat->setGeometry( QRect( 10, 60, 50, 21 ) ); 
    canopenPVarDecFormat->setText( tr( "Dec" ) );

    ButtonGroup8 = new QButtonGroup( tab_7, "ButtonGroup8" );
    ButtonGroup8->setGeometry( QRect( 320, 10, 150, 50 ) ); 
    ButtonGroup8->setTitle( tr( "Send time" ) );

    canopenPVarLater = new QRadioButton( ButtonGroup8, "canopenPVarLater" );
    canopenPVarLater->setGeometry( QRect( 80, 20, 57, 21 ) ); 
    canopenPVarLater->setText( tr( "&Later" ) );

    canopenPVarNow = new QRadioButton( ButtonGroup8, "canopenPVarNow" );
    canopenPVarNow->setGeometry( QRect( 10, 20, 52, 21 ) ); 
    canopenPVarNow->setText( tr( "&Now" ) );
    canopenPVarNow->setChecked( TRUE );

    canopenPVarDeviceId = new QSpinBox( tab_7, "canopenPVarDeviceId" );
    canopenPVarDeviceId->setGeometry( QRect( 160, 16, 58, 25 ) ); 
    canopenPVarDeviceId->setMaxValue( 127 );
    canopenPVarDeviceId->setValue( 1 );

    showPVarButton = new QPushButton( tab_7, "showPVarButton" );
    showPVarButton->setGeometry( QRect( 360, 210, 212, 29 ) ); 
    showPVarButton->setText( tr( "S&how all Process Variables" ) );

    readPVarButton = new QPushButton( tab_7, "readPVarButton" );
    readPVarButton->setEnabled( FALSE );
    readPVarButton->setGeometry( QRect( 380, 170, 184, 29 ) ); 
    readPVarButton->setText( tr( "&Read Process Variable" ) );
    TabWidget4->insertTab( tab_7, tr( "Process &Vars" ) );

    // signals and slots connections
    connect( canPort, SIGNAL( valueChanged(int) ), this, SLOT( portChanged( ) ) );
    connect( SimulationNoRadioButton, SIGNAL( clicked() ), this, SLOT( simulationNo( ) ) );
    connect( sendCanButton, SIGNAL( clicked() ), this, SLOT( sendCan( ) ) );
    connect( sendPDOButton, SIGNAL( clicked() ), this, SLOT( sendPDO( ) ) );
    connect( sendNMTButton, SIGNAL( clicked() ), this, SLOT( sendNMT( ) ) );
    connect( canHexFormat, SIGNAL( clicked() ), this, SLOT( canHEXClicked( ) ) );
    connect( canDecFormat, SIGNAL( clicked() ), this, SLOT( canDECClicked( ) ) );
    connect( canBinFormat, SIGNAL( clicked() ), this, SLOT( canBINClicked( ) ) );
    connect( sendSDOButton, SIGNAL( clicked() ), this, SLOT( sendSDO( ) ) );
    connect( sendSyncButton, SIGNAL( clicked() ), this, SLOT( sendSync( ) ) );
    connect( canopenPDOHexFormat, SIGNAL( clicked() ), this, SLOT( canopenPDOHexClicked( ) ) );
    connect( canopenPDOBinFormat, SIGNAL( clicked() ), this, SLOT( canopenPDOBinClicked( ) ) );
    connect( canopenPDODecFormat, SIGNAL( clicked() ), this, SLOT( canopenPDODecClicked( ) ) );
    connect( canopenSDOHexFormat, SIGNAL( clicked() ), this, SLOT( canopenSDOHexClicked( ) ) );
    connect( canopenSDOBinFormat, SIGNAL( clicked() ), this, SLOT( canopenSDOBinClicked( ) ) );
    connect( canopenSDODecFormat, SIGNAL( clicked() ), this, SLOT( canopenSDODecClicked( ) ) );
    connect( canopenDictHexFormat, SIGNAL( clicked() ), this, SLOT( canopenDictHexClicked( ) ) );
    connect( canopenDictBinFormat, SIGNAL( clicked() ), this, SLOT( canopenDictBinClicked( ) ) );
    connect( canopenDictDecFormat, SIGNAL( clicked() ), this, SLOT( canopenDictDecClicked( ) ) );
    connect( readDictEntry, SIGNAL( clicked() ), this, SLOT( canopenDictRead( ) ) );
    connect( writeDictEntry, SIGNAL( clicked() ), this, SLOT( canopenDictWrite( ) ) );
    connect( viewTransferTableButton, SIGNAL( clicked() ), this, SLOT( viewTransferTable( ) ) );
    connect( canopenPVarHexFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarHexClicked( ) ) );
    connect( canopenPVarBinFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarBinClicked( ) ) );
    connect( canopenPVarDecFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarDecClicked( ) ) );
    connect( writePVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarWrite( ) ) );
    connect( downloadPVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarDownload( ) ) );
    connect( showPVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarShow( ) ) );
    connect( readCanButton, SIGNAL( clicked() ), this, SLOT( readCan( ) ) );
    connect( PushButton65, SIGNAL( clicked() ), this, SLOT( clearCanReceiveLog( ) ) );
    connect( SimulationYesRadioButton, SIGNAL( clicked() ), this, SLOT( simulationYes( ) ) );
    connect( clearCANopenLogButton, SIGNAL( clicked() ), this, SLOT( clearCANSentLog( ) ) );
    connect( initModuleButton, SIGNAL( clicked() ), this, SLOT( initModule( ) ) );

    // tab order
    setTabOrder( canopenPDODeviceId, canopenPDOData0 );
    setTabOrder( canopenPDOData0, canopenPDOData1 );
    setTabOrder( canopenPDOData1, canopenPDOData2 );
    setTabOrder( canopenPDOData2, canopenPDOData3 );
    setTabOrder( canopenPDOData3, canopenPDOData4 );
    setTabOrder( canopenPDOData4, canopenPDOData5 );
    setTabOrder( canopenPDOData5, canopenPDOData6 );
    setTabOrder( canopenPDOData6, canopenPDOData7 );
    setTabOrder( canopenPDOData7, sendPDOButton );
    setTabOrder( sendPDOButton, canopenPDOWFlag );
    setTabOrder( canopenPDOWFlag, canopenPDOReadWrite );
    setTabOrder( canopenPDOReadWrite, canopenPDOHexFormat );
    setTabOrder( canopenPDOHexFormat, canopenPDOBinFormat );
    setTabOrder( canopenPDOBinFormat, canopenPDODecFormat );
    setTabOrder( canopenPDODecFormat, canopenDictDeviceId );
    setTabOrder( canopenDictDeviceId, canopenDictIndex );
    setTabOrder( canopenDictIndex, canopenDictSubIndex );
    setTabOrder( canopenDictSubIndex, canopenDictData0 );
    setTabOrder( canopenDictData0, canopenDictData1 );
    setTabOrder( canopenDictData1, canopenDictData2 );
    setTabOrder( canopenDictData2, canopenDictData3 );
    setTabOrder( canopenDictData3, canopenDictData4 );
    setTabOrder( canopenDictData4, canopenDictData5 );
    setTabOrder( canopenDictData5, canopenDictData6 );
    setTabOrder( canopenDictData6, canopenDictData7 );
    setTabOrder( canopenDictData7, canopenDictData8 );
    setTabOrder( canopenDictData8, canopenDictData9 );
    setTabOrder( canopenDictData9, canopenDictData10 );
    setTabOrder( canopenDictData10, canopenDictData11 );
    setTabOrder( canopenDictData11, canopenDictData12 );
    setTabOrder( canopenDictData12, canopenDictData13 );
    setTabOrder( canopenDictData13, canopenDictData14 );
    setTabOrder( canopenDictData14, readDictEntry );
    setTabOrder( readDictEntry, writeDictEntry );
    setTabOrder( writeDictEntry, viewTransferTableButton );
    setTabOrder( viewTransferTableButton, canIdentifier );
    setTabOrder( canIdentifier, canData0 );
    setTabOrder( canData0, canData1 );
    setTabOrder( canData1, canData2 );
    setTabOrder( canData2, canData3 );
    setTabOrder( canData3, canData4 );
    setTabOrder( canData4, canData5 );
    setTabOrder( canData5, canData6 );
    setTabOrder( canData6, canData7 );
    setTabOrder( canData7, canRTR );
    setTabOrder( canRTR, sendCanButton );
    setTabOrder( sendCanButton, readCanButton );
    setTabOrder( readCanButton, TabWidget4 );
    setTabOrder( TabWidget4, canopenSDODeviceId );
    setTabOrder( canopenSDODeviceId, canopenSDOCommandSpecifier );
    setTabOrder( canopenSDOCommandSpecifier, canopenSDOData1 );
    setTabOrder( canopenSDOData1, canopenSDOData2 );
    setTabOrder( canopenSDOData2, canopenSDOData3 );
    setTabOrder( canopenSDOData3, canopenSDOData4 );
    setTabOrder( canopenSDOData4, canopenSDOData5 );
    setTabOrder( canopenSDOData5, canopenSDOData6 );
    setTabOrder( canopenSDOData6, canopenSDOData7 );
    setTabOrder( canopenSDOData7, canopenNMTDeviceId );
    setTabOrder( canopenNMTDeviceId, nmtState );
    setTabOrder( nmtState, sendNMTButton );
    setTabOrder( sendNMTButton, canopenPVarDeviceId );
    setTabOrder( canopenPVarDeviceId, canopenPVarData0 );
    setTabOrder( canopenPVarData0, canopenPVarData1 );
    setTabOrder( canopenPVarData1, canopenPVarData2 );
    setTabOrder( canopenPVarData2, canopenPVarData3 );
    setTabOrder( canopenPVarData3, canopenPVarData4 );
    setTabOrder( canopenPVarData4, canopenPVarData5 );
    setTabOrder( canopenPVarData5, canopenPVarData6 );
    setTabOrder( canopenPVarData6, canopenPVarData7 );
    setTabOrder( canopenPVarData7, writePVarButton );
    setTabOrder( writePVarButton, readPVarButton );
    setTabOrder( readPVarButton, downloadPVarButton );
    setTabOrder( downloadPVarButton, showPVarButton );
    setTabOrder( showPVarButton, canPort );
    setTabOrder( canPort, initModuleButton );
    setTabOrder( initModuleButton, SimulationNoRadioButton );
    setTabOrder( SimulationNoRadioButton, canHexFormat );
    setTabOrder( canHexFormat, canBinFormat );
    setTabOrder( canBinFormat, canDecFormat );
    setTabOrder( canDecFormat, sendSDOButton );
    setTabOrder( sendSDOButton, canopenSDOReadWrite );
    setTabOrder( canopenSDOReadWrite, canopenSDOWFlag );
    setTabOrder( canopenSDOWFlag, canopenSDONormal );
    setTabOrder( canopenSDONormal, canopenSDOHexFormat );
    setTabOrder( canopenSDOHexFormat, canopenSDODecFormat );
    setTabOrder( canopenSDODecFormat, sendSyncButton );
    setTabOrder( sendSyncButton, canopenDictHexFormat );
    setTabOrder( canopenDictHexFormat, canopenDictBinFormat );
    setTabOrder( canopenDictBinFormat, canopenDictDecFormat );
    setTabOrder( canopenDictDecFormat, canopenPVarHexFormat );
    setTabOrder( canopenPVarHexFormat, canopenPVarBinFormat );
    setTabOrder( canopenPVarBinFormat, canopenPVarDecFormat );
    setTabOrder( canopenPVarDecFormat, canopenPVarNow );
    setTabOrder( canopenPVarNow, clearCANopenLogButton );
    setTabOrder( clearCANopenLogButton, canLogView );
    setTabOrder( canLogView, PushButton65 );
    setTabOrder( PushButton65, canReceiveLog );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
MainGui::~MainGui()
{
    // no need to delete child widgets, Qt does it all for us
}

void MainGui::canBINClicked( )
{
    qWarning( "MainGui::canBINClicked( ): Not implemented yet!" );
}

void MainGui::canDECClicked( )
{
    qWarning( "MainGui::canDECClicked( ): Not implemented yet!" );
}

void MainGui::canHEXClicked( )
{
    qWarning( "MainGui::canHEXClicked( ): Not implemented yet!" );
}

void MainGui::canopenDictBinClicked( )
{
    qWarning( "MainGui::canopenDictBinClicked( ): Not implemented yet!" );
}

void MainGui::canopenDictDecClicked( )
{
    qWarning( "MainGui::canopenDictDecClicked( ): Not implemented yet!" );
}

void MainGui::canopenDictHexClicked( )
{
    qWarning( "MainGui::canopenDictHexClicked( ): Not implemented yet!" );
}

void MainGui::canopenDictRead( )
{
    qWarning( "MainGui::canopenDictRead( ): Not implemented yet!" );
}

void MainGui::canopenDictWrite( )
{
    qWarning( "MainGui::canopenDictWrite( ): Not implemented yet!" );
}

void MainGui::canopenPDOBinClicked( )
{
    qWarning( "MainGui::canopenPDOBinClicked( ): Not implemented yet!" );
}

void MainGui::canopenPDODecClicked( )
{
    qWarning( "MainGui::canopenPDODecClicked( ): Not implemented yet!" );
}

void MainGui::canopenPDOHexClicked( )
{
    qWarning( "MainGui::canopenPDOHexClicked( ): Not implemented yet!" );
}

void MainGui::canopenPVarBinClicked( )
{
    qWarning( "MainGui::canopenPVarBinClicked( ): Not implemented yet!" );
}

void MainGui::canopenPVarDecClicked( )
{
    qWarning( "MainGui::canopenPVarDecClicked( ): Not implemented yet!" );
}

void MainGui::canopenPVarDownload( )
{
    qWarning( "MainGui::canopenPVarDownload( ): Not implemented yet!" );
}

void MainGui::canopenPVarHexClicked( )
{
    qWarning( "MainGui::canopenPVarHexClicked( ): Not implemented yet!" );
}

void MainGui::canopenPVarShow( )
{
    qWarning( "MainGui::canopenPVarShow( ): Not implemented yet!" );
}

void MainGui::canopenPVarWrite( )
{
    qWarning( "MainGui::canopenPVarWrite( ): Not implemented yet!" );
}

void MainGui::canopenSDOBinClicked( )
{
    qWarning( "MainGui::canopenSDOBinClicked( ): Not implemented yet!" );
}

void MainGui::canopenSDODecClicked( )
{
    qWarning( "MainGui::canopenSDODecClicked( ): Not implemented yet!" );
}

void MainGui::canopenSDOHexClicked( )
{
    qWarning( "MainGui::canopenSDOHexClicked( ): Not implemented yet!" );
}

void MainGui::clearCANSentLog( )
{
    qWarning( "MainGui::clearCANSentLog( ): Not implemented yet!" );
}

void MainGui::clearCanReceiveLog( )
{
    qWarning( "MainGui::clearCanReceiveLog( ): Not implemented yet!" );
}

void MainGui::initModule( )
{
    qWarning( "MainGui::initModule( ): Not implemented yet!" );
}

void MainGui::new_slot()
{
    qWarning( "MainGui::new_slot(): Not implemented yet!" );
}

void MainGui::portChanged( )
{
    qWarning( "MainGui::portChanged( ): Not implemented yet!" );
}

void MainGui::readCan( )
{
    qWarning( "MainGui::readCan( ): Not implemented yet!" );
}

void MainGui::restartNode( )
{
    qWarning( "MainGui::restartNode( ): Not implemented yet!" );
}

void MainGui::sendCan( )
{
    qWarning( "MainGui::sendCan( ): Not implemented yet!" );
}

void MainGui::sendNMT( )
{
    qWarning( "MainGui::sendNMT( ): Not implemented yet!" );
}

void MainGui::sendPDO( )
{
    qWarning( "MainGui::sendPDO( ): Not implemented yet!" );
}

void MainGui::sendSDO( )
{
    qWarning( "MainGui::sendSDO( ): Not implemented yet!" );
}

void MainGui::sendSync( )
{
    qWarning( "MainGui::sendSync( ): Not implemented yet!" );
}

void MainGui::simulationNo( )
{
    qWarning( "MainGui::simulationNo( ): Not implemented yet!" );
}

void MainGui::simulationYes( )
{
    qWarning( "MainGui::simulationYes( ): Not implemented yet!" );
}

void MainGui::viewTransferTable( )
{
    qWarning( "MainGui::viewTransferTable( ): Not implemented yet!" );
}

#include "maingui.moc"
