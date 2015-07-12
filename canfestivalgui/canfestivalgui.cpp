/****************************************************************************
   Copyright (C) 2002 by Raphael Zulliger
   Copyright (C) 2015, Jacob Dawid <jacob@omg-it.works>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#include "canfestivalgui.h"
#include "maingui.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <curses.h>

#include "include/Can.h"
#include "include/ArbraCan.h"
#include "include/CanOpenMatic.h"

#include <qmessagebox.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qstring.h>
#include <qspinbox.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>

#include "ui_maingui.h"

/*********************************************************************************************
/ the following lines are for using the canopenmatic library, which is a C library...
*********************************************************************************************/

/**-------------------------------------------------------------------------------------------
// some variables...
/-------------------------------------------------------------------------------------------*/
int wait=0;                         // 0: write/read is non-blocking, so if no canmessage is in the receive buffer, the
                                    // read/write functions do not block the program
static int fd0;                     // the candevice
static int canMsgNr=0;              // the count of sent messages
static bool simulation = true;      // switch between: "real" can-traffic and only simulation
                                    // (e.g. for learning the canopen protocol)
static Q3TextView*  canLog=0;        // a pointer to the log window. all sent messages are logged into a view on the gui


/**------------------------------------------------------------------------------------------
// this function is called once by the gui, so the non-class members of the gui do know
// the pointer of the log window
//------------------------------------------------------------------------------------------*/
void setWindowParams( Q3TextView* canLog_ )
{
    canLog = canLog_;
}

/**-------------------------------------------------------------------------------------------
// a function to set the write/read flag (blocking or non-blocking)
//------------------------------------------------------------------------------------------*/
void setWait( int wait_ )
{
    wait = wait_;
}

/**-------------------------------------------------------------------------------------------
// a function to get the actual value of the read/write flag
//------------------------------------------------------------------------------------------*/
int getWait( )
{
    return wait;
}

/**-------------------------------------------------------------------------------------------
// a function to set the flag if the gui operates in simulation mode or not
//------------------------------------------------------------------------------------------*/
void setSimulation( bool simulation_ )
{
    simulation = simulation_;
}

/**-------------------------------------------------------------------------------------------
// this function reads the buffer of the pci-can board in the PC
//------------------------------------------------------------------------------------------*/
int f_can_receive(int notused, Message *m){
    int res;

    if( !simulation ) {
        if(wait)
            res = ioctl(fd0,CANBOARD_READ_BLOCK,m);
        else
            res = ioctl(fd0,CANBOARD_READ,m);
    } else {
        // in simulation mode, no messages can be read
        res = -1;
    }
    return res;
}

/**-------------------------------------------------------------------------------------------
// the function to write can-messages to the bus (trhough the pci-can board)
//------------------------------------------------------------------------------------------*/
int f_can_send(int notused, Message *m){
    int res;
    char text[73];

    if( canLog )
    {   // if a logwindow was defined (should be!)
        QString tempData;

        // copies the data of the can-message into a useful string (useful: convenience for the user)
        for( int i=0; i<m->len; i++ ) {
            sprintf( text, "%.2x|", m->data[i] );
            tempData.append( QString( text ) );
            tempData.append( "-" );
        }
        tempData.truncate( tempData.length( ) - 1 );
        // writes the can-message to the logwindow
        canLog->append( QString( ).sprintf( "%.4d> Id: %.4x RTR: %d Data: %s", canMsgNr++, m->cob_id.w, m->rtr, tempData.toLatin1().constData() ) );
        canLog->center( 0, canLog->contentsHeight( ) );
        canLog->viewport( )->repaint( );
        canLog->hide( );
        canLog->show( );
    }

    if( !simulation )
    {   // send the can-message to the pci-can board
        if(wait)
            res = ioctl(fd0,CANBOARD_WRITE_BLOCK,m);
        else
            res = ioctl(fd0,CANBOARD_WRITE,m);
    }
    else
    {
        // if we're in simulation mode, just return 0, so everybody's happy
        res = 0;
    }
    return res;
}


/**-------------------------------------------------------------------------------------------
// this function opens the connection to the pci-can board. the connection is done by
// opening the file /dev/canx, where x is 0 or 1 (related to port 0 and 1). it returns
// the file-handler to the can-port.
//------------------------------------------------------------------------------------------*/
int f_can_open( char* thebusname ){
    fd0 = open(thebusname,O_RDWR);
    return fd0;
}

/**-------------------------------------------------------------------------------------------
// here the connection to the can-port will be closed
//------------------------------------------------------------------------------------------*/
int f_can_close(){
    return close(fd0);
}




//********************************************************************************************
// the GUI-code is following now
//********************************************************************************************

/**-------------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------------*/
CANFestivalGui::CANFestivalGui()
{
    // initialize some vars to standardvalues
    fd = -1;
    wait = 1;
    mLogThread = NULL;
    driverLoaded = false;

    // the following lines sets the gui into a standard state
    canopenPrevDataType = HEX;
    canopenDictPrevDataType = HEX;
    canopenPVarPrevDataType = HEX;
    canPrevDataType = HEX;

    // fills the "helper"-lists with their childs...
    // this helper-lists are useful to perform operations which are for every datafield. (e.g. set them to 0)
    canopenPDODataList.append( ui->canopenPDOData0 );
    canopenPDODataList.append( ui->canopenPDOData1 );
    canopenPDODataList.append( ui->canopenPDOData2 );
    canopenPDODataList.append( ui->canopenPDOData3 );
    canopenPDODataList.append( ui->canopenPDOData4 );
    canopenPDODataList.append( ui->canopenPDOData5 );
    canopenPDODataList.append( ui->canopenPDOData6 );
    canopenPDODataList.append( ui->canopenPDOData7 );

    canopenSDODataList.append( ui->canopenSDOData1 );
    canopenSDODataList.append( ui->canopenSDOData2 );
    canopenSDODataList.append( ui->canopenSDOData3 );
    canopenSDODataList.append( ui->canopenSDOData4 );
    canopenSDODataList.append( ui->canopenSDOData5 );
    canopenSDODataList.append( ui->canopenSDOData6 );
    canopenSDODataList.append( ui->canopenSDOData7 );

    canopenDictDataList.append( ui->canopenDictData0 );
    canopenDictDataList.append( ui->canopenDictData1 );
    canopenDictDataList.append( ui->canopenDictData2 );
    canopenDictDataList.append( ui->canopenDictData3 );
    canopenDictDataList.append( ui->canopenDictData4 );
    canopenDictDataList.append( ui->canopenDictData5 );
    canopenDictDataList.append( ui->canopenDictData6 );
    canopenDictDataList.append( ui->canopenDictData7 );
    canopenDictDataList.append( ui->canopenDictData8 );
    canopenDictDataList.append( ui->canopenDictData9 );
    canopenDictDataList.append( ui->canopenDictData10 );
    canopenDictDataList.append( ui->canopenDictData11 );
    canopenDictDataList.append( ui->canopenDictData12 );
    canopenDictDataList.append( ui->canopenDictData13 );
    canopenDictDataList.append( ui->canopenDictData14 );

    canopenPVarDataList.append( ui->canopenPVarData0 );
    canopenPVarDataList.append( ui->canopenPVarData1 );
    canopenPVarDataList.append( ui->canopenPVarData2 );
    canopenPVarDataList.append( ui->canopenPVarData3 );
    canopenPVarDataList.append( ui->canopenPVarData4 );
    canopenPVarDataList.append( ui->canopenPVarData5 );
    canopenPVarDataList.append( ui->canopenPVarData6 );
    canopenPVarDataList.append( ui->canopenPVarData7 );

    canDataList.append( ui->canData0 );
    canDataList.append( ui->canData1 );
    canDataList.append( ui->canData2 );
    canDataList.append( ui->canData3 );
    canDataList.append( ui->canData4 );
    canDataList.append( ui->canData5 );
    canDataList.append( ui->canData6 );
    canDataList.append( ui->canData7 );

    // sends the pointer of the logwindow to the non-gui code (see above)
    setWindowParams( ui->canLogView );

    // init the module (load candriver & open canport)
    initModule( );

    // creates the gui which is able to show all (at the moment only the transmit values) process vars
    mPVarGui = new ProcessVarGui( );
}


/**-------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------*/
CANFestivalGui::~CANFestivalGui()
{
    delete mLogThread;
    delete mPVarGui;
}


/**-------------------------------------------------------------------------------------------
// module initializer
// description:
//      Initializes the module: loads the driver (insmod) if neccessary and opens the device
//      located in /dev/ (e.g. /dev/can0 or /dev/can1).
//      if the module is allready initialized, it deinitializes it (removes the driver and
//      closes the device)
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::initModule( )
{
    if( !driverLoaded )
    {
        // load the driver. if allready loaded, a message to stdout occurs...
        system( "/sbin/insmod /home/rzullige/CanFestival/ArbraCan/arbracan.o can_silent=0 can_rate=125" );
        driverLoaded = true;

        // open the canport (/dev/canx)
        if( ( fd = openDevice( ) ) < 0 )
        {
            QMessageBox::information( this, "CANFestival GUI", "The CANport couln't be opened" );
            return;
        }

        ui->initModuleButton->setText( "&De-Initialize CANPort" );
        // set simulation mode to false, so real CAN message can be transmitted/received
        simulation = false;
        setSimulation( simulation );
        // start log thread, which receives and shows all can messages (sniffer)
        mLogThread = new LogThread( ui->canReceiveLog, this );
        mLogThread->start( );
    }
    else
    {   // unload driver module and close canport
        // stop logging thread (it would be useless in simulation mode)
        if(mLogThread) {
            mLogThread->stop( );
            mLogThread = NULL;
        }
        // close device
        if( closeDevice( ) < 0 )
            QMessageBox::information( this, "CANFestival GUI", "The CANport couln't be closed" );

        // unload driver module for the can pci card (maybe not possible if the second port is opened by an other process)
        system( "/sbin/modprobe -r arbracan" );

        // gui things
        ui->initModuleButton->setText( "&Initialize CANPort" );
        driverLoaded = false;

        // set simulation mode to true
        setSimulation( simulation = true );
        fd = -1;
    }
}


/**-------------------------------------------------------------------------------------------
// the port value in the gui has changed
// description:
//      the pci-7841 board has two different can-ports. if the user of this program chooses an
//      other canport (e.g. 1 instead of 0) this function does close the old connection to
//      the port used before and opens a connection to the new port number
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::portChanged( )
{
    closeDevice( );
    openDevice( );
}


/**-------------------------------------------------------------------------------------------
// sends a can message
// description:
//      this operation send a canmessage (not CANopen!) to the pci-can board. therefore this
//      operation has to fill the correct data (corresponding to the values wriiten in the
//      gui) into the can-message struct.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::sendCan( )
{
    Message m;
    unsigned char data[8];
    int ID;

    if( ui->canCountOfByteActiv->isChecked( ) )
    {   // the user has given a message length ( from 0 up to 8 bytes)
        m.len = ui->canCountOfByte->text( ).toInt( );
    }
    else
    {   // the length of the value is calculated automatically
        m.len = getLength( canDataList );
    }

    // converts the data written in the gui to integer values (remember: the gui is able to
    // handle hex, decimal and binary values
    for( int i=0; i<m.len; i++ ) {
        if( ui->canHexFormat->isChecked( ) ) {
            data[i] = strtol( canDataList.at( i )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canBinFormat->isChecked( ) ) {
            data[i] = strtol( canDataList.at( i )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canDataList.at( i )->text( ).toInt( );
        }
    }

    // converts the can identifier into decimal data
    if( ui->canHexFormat->isChecked( ) ) {
        ID = strtol( ui->canIdentifier->text( ).toStdString().c_str(), NULL, 16 );
    } else if( ui->canBinFormat->isChecked( ) ) {
        ID = strtol( ui->canIdentifier->text( ).toStdString().c_str(), NULL, 2 );
    } else {
        ID = ui->canIdentifier->text( ).toInt( );
    }
    m.cob_id.w = ID;

    // sets the RTR bit (retrieve bit)
    if( ui->canRTR->isChecked( ) ) {
        m.rtr = 0x01;
    } else {
        m.rtr = 0x00;
    }
    // copies the data into the can-message struct (could have be done directly...)
    memcpy(&(m.data), &(data[0]), m.len);

    // now send the data onto the bus
    f_can_send( 0, &m );
}



/**-------------------------------------------------------------------------------------------
// sends a NMT message
// description:
//      this operation sends a CANopen-NMT (network management) message onto the can-bus.
//      there are several different NMT commands. this program is able to send all of them
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::sendNMT( )
{
    int ID;
    unsigned char data[8];

    // corresponding to the choosen nmt-command, fill in the correct data into the can-message
    // struct
    if( ui->nmtState->currentText( ).compare( "Start Remote Node" ) == 0 )
    {
        data[0] = 0x01;
    }
    else if( ui->nmtState->currentText( ).compare( "Stop Remote Node" ) == 0 )
    {
        data[0] = 0x02;
    }
    else if( ui->nmtState->currentText( ).compare( "Pre Operational State" ) == 0 )
    {
        data[0] = (int)128;
    }
    else if( ui->nmtState->currentText( ).compare( "Reset Node" ) == 0 )
    {
        data[0] = (int)129;
    }
    else if( ui->nmtState->currentText( ).compare( "Reset Communication" ) == 0 )
    {
        data[0] = (int)130;
    }

    // get the can-identifier. (0 means: for all slaves)
    ID = ui->canopenNMTDeviceId->text( ).toInt( );

    // send the data to the canopenmatic function Send_NMT which does some conversions and
    // sends the message on the can-bus
    Send_NMT(0, ID, data[0]);
}


/**-------------------------------------------------------------------------------------------
// sends a canopen-sync message
// description:
//      sends a sync message onto the can-bus. a sync message is received by all slaves
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::sendSync( )
{
    Send_Sync( 0 );
}


/**-------------------------------------------------------------------------------------------
// sends a PDO
// description:
//      sends a canopen-pdo (process data object) over the can-bus.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::sendPDO( )
{
    int msgd;
    unsigned char data[8];
    s_PDO pdo;

    // gets the id and the datalength
    pdo.ID = ui->canopenPDODeviceId->text( ).toInt( );
    pdo.len = getLength( canopenPDODataList );

    // gets the direction. pdos can be sent and received (if supported by the slave)
    if( ui->canopenPDOReadWrite->isChecked( ) == true )
        msgd = Tx;
    else
        msgd = Rx;

    // copies the data from the gui into a temporary datafield. conversion from hex/bin to decimal are
    // also done if neccessary
    for( int i=0; i<pdo.len; i++ ) {
        if( ui->canopenPDOHexFormat->isChecked( ) ) {
            data[i] = strtol( canopenPDODataList.at( i )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canopenPDOBinFormat->isChecked( ) ) {
            data[i] = strtol( canopenPDODataList.at( i )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canopenPDODataList.at( i )->text( ).toInt( );
        }
    }

    // copies the data into the can-message struct and send them to the canopenmatic function which
    // does some more processing and sends the data onto the can-bus
    memcpy(&(pdo.data), &(data[0]), pdo.len);
    Send_PDO(0, pdo, msgd);
}

/**-------------------------------------------------------------------------------------------
// sends an SDO onto the bus
// description:
//      should send an canopen-SDO onto the can-bus. !!! this function is not implemented
//      correctly and not tested !!! to access the object directory of an other module, use
//      read/write dictionary entries instead!
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::sendSDO( )
{
    int msgd;
    unsigned char n, e, s, t, c;
    unsigned char data[8];

    s_SDO sdo;
    sdo.ID = ui->canopenSDODeviceId->text( ).toInt( );
    // + 1 wegen dem Command Specifier...
    sdo.len = getLength( canopenSDODataList ) + 1;
    if( ui->canopenSDOReadWrite->isChecked( ) == true ) {
        msgd = Rx;
    } else {
        msgd = Tx;
    }

    n = 8 - (sdo.len-1);
    ui->canopenSDONormal->isChecked( ) ? e=0: e=1;
    s = 0; // !!!!!!!!!!! was isch das ueberhaupt?!
    t = 0; // !!!!!!!!!!! fix this...
    c = 1; // should also be changed !!!!!!!!!!!!

    if( ui->canopenSDOCommandSpecifier->currentText( ).compare( "Init Domain Download" ) == 0 ) {
        if( msgd == Tx ) {
            data[0] = IDD_client( n, e, s );
        } else {
            data[0] = IDD_server;
        }
    } else if( ui->canopenSDOCommandSpecifier->currentText( ).compare( "Download Domain Segment" ) == 0 ) {
        if( msgd == Tx ) {
            data[0] = DDS_client( t, n, c );
        } else {
            data[0] = DDS_server;
        }
    } else if( ui->canopenSDOCommandSpecifier->currentText( ).compare( "Init Domain Upload" ) == 0 ) {
        QMessageBox::information( this, "kdsfjsl", "lauft no nued..." );
    } else if( ui->canopenSDOCommandSpecifier->currentText( ).compare( "Upload Domain Segment" ) == 0 ) {
        QMessageBox::information( this, "kdsfjsl", "lauft no nued..." );
    } else if( ui->canopenSDOCommandSpecifier->currentText( ).compare( "Abort Domain Transfer" ) == 0 ) {
        data[0] = ADT_server;
    }
    for( int i=1; i<sdo.len-1; i++ ) {
        if( ui->canopenSDOHexFormat->isChecked( ) ) {
            data[i] = strtol( canopenSDODataList.at( i-1 )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canopenSDOBinFormat->isChecked( ) ) {
            data[i] = strtol( canopenSDODataList.at( i-1 )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canopenSDODataList.at( i-1 )->text( ).toInt( );
        }
    }

    memcpy(&(sdo.body), &(data[0]), sdo.len);
    Send_SDO(0, sdo, msgd);
}



/**-------------------------------------------------------------------------------------------
// writes a dictionary entry
// description:
//      helps to write dictionary entries to other canopen devices.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenDictWrite( )
{
    unsigned short tempIndex;
    char            tempSubIndex;
    char            data[15];

    // converts the data-values from the gui into integer values
    for( int i=0; i<getLength( canopenDictDataList ); i++ ) {
        if( ui->canopenDictHexFormat->isChecked( ) ) {
            data[i] = strtol( canopenDictDataList.at( i )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canopenDictBinFormat->isChecked( ) ) {
            data[i] = strtol( canopenDictDataList.at( i )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canopenDictDataList.at( i )->text( ).toInt( );
        }
    }

    // gets and converts the index number of the entry
    if( ui->canopenDictHexFormat->isChecked( ) ) {
        tempIndex = strtol( ui->canopenDictIndex->text( ).toStdString().c_str(), NULL, 16 );
    } else if( ui->canopenDictBinFormat->isChecked( ) ) {
        tempIndex = strtol( ui->canopenDictIndex->text( ).toStdString().c_str(), NULL, 2 );
    } else {
        tempIndex = ui->canopenDictIndex->text( ).toInt( );
    }

    // gets and converts the subindex number of the entry
    if( ui->canopenDictHexFormat->isChecked( ) ) {
        tempSubIndex = strtol( ui->canopenDictSubIndex->text( ).toStdString().c_str(), NULL, 16 );
    } else if( ui->canopenDictBinFormat->isChecked( ) ) {
        tempSubIndex = strtol( ui->canopenDictSubIndex->text( ).toStdString().c_str(), NULL, 2 );
    } else {
        tempSubIndex = ui->canopenDictSubIndex->text( ).toInt( );
    }

    // calls the canopenmatic function which does the rest for us... including sending the can-message
    WriteDictionaryEntry(0,
                         ui->canopenDictDeviceId->text( ).toInt( ),
                         tempIndex,
                         tempSubIndex,
                         getLength( canopenDictDataList ),
                         data);
}



/**-------------------------------------------------------------------------------------------
// reads a dictionary entry
// description:
//      reads a dictionary entry from an other canopen device.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenDictRead( )
{
    unsigned short tempIndex;
    char            tempSubIndex;
    char            data[SDO_MAX_DOMAIN_LEN];

    // sets all values to 0
    for( int i=0; i<SDO_MAX_DOMAIN_LEN; i++ )
        data[i] = 0;

    // converts the data filds from the gui into integer values
    // as far as i know: when reading dict. entries no values are sent to the slave...
//    for( int i=0; i<getLength( canopenDictDataList ); i++ ) {
//        if( canopenDictHexFormat->isChecked( ) ) {
//            data[i] = strtol( canopenDictDataList.at( i )->text( ), NULL, 16 );
//        } else if( canopenDictBinFormat->isChecked( ) ) {
//            data[i] = strtol( canopenDictDataList.at( i )->text( ), NULL, 2 );
//        } else {
//            data[i] = canopenDictDataList.at( i )->text( ).toInt( );
//        }
//    }

    // gets and converts the indexnumber of the dictionary entry
    if( ui->canopenDictHexFormat->isChecked( ) ) {
        tempIndex = strtol( ui->canopenDictIndex->text( ).toStdString().c_str(), NULL, 16 );
    } else if( ui->canopenDictBinFormat->isChecked( ) ) {
        tempIndex = strtol( ui->canopenDictIndex->text( ).toStdString().c_str(), NULL, 2 );
    } else {
        tempIndex = ui->canopenDictIndex->text( ).toInt( );
    }

    // gets and converts the subindexnumber of the dictionary entry
    if( ui->canopenDictHexFormat->isChecked( ) ) {
        tempSubIndex = strtol( ui->canopenDictSubIndex->text( ).toStdString().c_str(), NULL, 16 );
    } else if( ui->canopenDictBinFormat->isChecked( ) ) {
        tempSubIndex = strtol( ui->canopenDictSubIndex->text( ).toStdString().c_str(), NULL, 2 );
    } else {
        tempSubIndex = ui->canopenDictSubIndex->text( ).toInt( );
    }

    // temporary stops the thread which sniffes the can-bus (this thread reads all received can-bus
    // messages and shows them in the logwindow)
    if( mLogThread )
        mLogThread->getSem( );
    // set f_can_receive to block (so reading the canbus blocks until a message was received)
    int tempWait = getWait( );
    setWait( 1 );

    // calls the function of canopenmatic which performs the rest for us...
    if( ReadDictionaryEntry( 0,
                         ui->canopenDictDeviceId->text( ).toInt( ),
                         tempIndex,
                         tempSubIndex,
                         data ) == 0 )
    {   // if read of dictionary entry was successful...
        QString intValue;
        QString textValue;
        QString hexValue;

        textValue = "Text: ";
        intValue = "Int: ";
        hexValue = "Hex: ";

        char text[5];

        // processes the received data, so it is useful for the user. after processing the data are shown in the gui
        //
        for( int i=0; i<SDO_MAX_DOMAIN_LEN; i++ ) {
            sprintf( text, "%.2d|", data[i] );
            intValue.append( text );
            sprintf( text, "%c", data[i] );
            textValue.append( text );
            sprintf( text, "%.2x|", data[i] );
            hexValue.append( text );
        }
        QMessageBox::information( this, "Dictionary Read Result (integer)", intValue + "\n" + textValue + "\n" + hexValue );
    }
    // sets the read/write flag (blocking or non-blocking) to the previous value
    setWait( tempWait );
    if( mLogThread )
        mLogThread->putSem( );
}


/**-------------------------------------------------------------------------------------------
// reads a PDO
// description:
//      reads a canopen-pdo (process variable) from the can-bus
//      !!! this operation is not implemented correctly yet, because !!! use pdo-transfer
//      instead (and set the read-flag in the gui)
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenPVarRead( )
{
    char data[8];
    int len;

    // gets and converts the data from the gui
    for( int i=0; i<getLength( canopenPVarDataList ); i++ ) {
        if( ui->canopenPVarHexFormat->isChecked( ) ) {
            data[i] = strtol( canopenPVarDataList.at( i )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canopenPVarBinFormat->isChecked( ) ) {
            data[i] = strtol( canopenPVarDataList.at( i )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canopenPVarDataList.at( i )->text( ).toInt( );
        }
    }

    // gets the length of data
    len = ReadProcessVar( 0, ui->canopenPVarDeviceId->text( ).toInt( ), data);

    QString intValue = "Int: ";
    QString textValue = "Text: ";
    char tempText[5];

    //
    for( int i=0; i<len; i++ ) {
        sprintf( tempText, "%.2d|", data[i] );
        intValue.append( tempText );
        sprintf( tempText, "%c", data[i] );
        textValue.append( tempText );
    }
    QMessageBox::information( this, "Process Var", intValue + "\n" + textValue );
}


/**-------------------------------------------------------------------------------------------
// write pdo
// description:
//      transmits a canopen-pdo (process variable) onto the can-bus
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenPVarWrite( )
{
    int sendTime;
    char data[8];

    // check wheter the variable should be sent immediatly or later...
    ui->canopenPVarNow->isChecked( )? sendTime=NOW : sendTime=LATER;

    // gets and converts the data from the gui
    for( int i=0; i<getLength( canopenPVarDataList ); i++ ) {
        if( ui->canopenPVarHexFormat->isChecked( ) ) {
            data[i] = strtol( canopenPVarDataList.at( i )->text( ).toStdString().c_str(), NULL, 16 );
        } else if( ui->canopenPVarBinFormat->isChecked( ) ) {
            data[i] = strtol( canopenPVarDataList.at( i )->text( ).toStdString().c_str(), NULL, 2 );
        } else {
            data[i] = canopenPVarDataList.at( i )->text( ).toInt( );
        }
    }

    // stops the log thread (which reads all received can-messages) temporary
    if( mLogThread )
        mLogThread->getSem( );
    // call the canopenmatic function which does the rest for us
    WriteProcessVar( sendTime, 0,
                    ui->canopenPVarDeviceId->text( ).toInt( ),
                    getLength( canopenPVarDataList ),
                    data);
    // continues the log thread
    if( mLogThread )
        mLogThread->putSem( );
}



/**-------------------------------------------------------------------------------------------
// downloads all processvars
// description:
//      downloads all processvars which was sent by the attribute "later" (see above)
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenPVarDownload( )
{
    // stops the log thread temporary
    if( mLogThread )
        mLogThread->getSem( );
    // calls the canopenmatic function
    DownloadProcessVars( 0 );
    // continues the log thread
    if( mLogThread )
        mLogThread->putSem( );
}


/**-------------------------------------------------------------------------------------------
// shows all process vars
// description:
//      opens a new window which shows all processvars (the one transmitted and the one
//      received) !!! only the transmitted values are shown correctly !!! sorry :-(
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::canopenPVarShow( )
{
    mPVarGui->show( );
}


/**-------------------------------------------------------------------------------------------
// gets the length of datas
// description:
//      this is a helper function, which calculates the count of data to send onto the canbus.
//      getting this value is done very simple: the last occurence of a value different than
//      zero is the last data-field... this means: if one would send data like:
//      0x12 0x45 0x00, the length is only 2 because 0x00 will not be sent :-( to avoid
//      such troubles, the gui supports an additional field, where the user can force to send
//      a number of bytes (in this case 3)
//------------------------------------------------------------------------------------------*/
int CANFestivalGui::getLength( QList<QLineEdit*>& theList )
{
    QLineEdit*  theLine;
    uint i = theList.length();

    theLine = theList.last( );
    while( ( theLine->text( ).toInt( ) == 0 ) || ( theLine->text( ).isEmpty( ) ) ) {
        if(i > 0) {
            i--;
            theLine = theList.at(i);
        } else {
            break;
        }
    }

    if( i == 0 )
        i = 1;

    return i;
}


/**-------------------------------------------------------------------------------------------
// opens the canport (/dev/canx)
// description:
//      this operation helps to open the can device (one of the ports on the pci-can board)
//------------------------------------------------------------------------------------------*/
int CANFestivalGui::openDevice( )
{
    if( fd < 0 )
    {
        // copies the port number from the gui into the string
        sprintf( busname, "%s%i", "/dev/can", ui->canPort->text( ).toInt( ) );
        if( ( fd = f_can_open( busname ) ) < 0 )  {
            QMessageBox::information( this, "CANFestival GUI",
                            "couln't open CAN Device" );
            return -1;
        }
    }
    return fd;
}


/**-------------------------------------------------------------------------------------------
// close the can-port
// description:
//      closes the connection to the canport
//------------------------------------------------------------------------------------------*/
int CANFestivalGui::closeDevice( )
{
    return f_can_close( );
}


/**-------------------------------------------------------------------------------------------
// change into simulation mode
// description:
//      helps to change into simulation-only mode. therfore various gui elements has to
//      be hidden. does not open the canport
//      connection! pressing the initialize CANPort button in the gui is needed.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::simulationNo( )
{
    // some gui things
    ui->canPortLabel->setEnabled( true );
    ui->canPort->setEnabled( true );
    ui->initModuleButton->setEnabled( true );
    ui->SimulationNoRadioButton->setChecked( true );
}



/**-------------------------------------------------------------------------------------------
// change into "real" operational mode
// description:
//      helps to change from simulation mode into operation mode.
//------------------------------------------------------------------------------------------*/
void CANFestivalGui::simulationYes( )
{
    ui->canPortLabel->setEnabled( false );
    ui->canPort->setEnabled( false );
    ui->initModuleButton->setEnabled( false );
    ui->SimulationYesRadioButton->setChecked( true );

    // does the rest: closes the connection to the canport and unload can-pci board driver
    initModule( );
}



// *********************************************************************************************
//  Data converting HEX->DEC, HEX->BIN, ...
//
//  the following operations do all the same: converts a value in one of the data/adress/index
//  field into an other format.
// *********************************************************************************************

void CANFestivalGui::canopenPVarBinClicked( )
{
    toBin( &canopenPVarDataList, canopenPVarPrevDataType, 8 );

    canopenPVarPrevDataType = BIN;
}


void CANFestivalGui::canopenPVarDecClicked( )
{
    toDec( &canopenPVarDataList, canopenPVarPrevDataType, 8 );

    canopenPVarPrevDataType = DEC;
}


void CANFestivalGui::canopenPVarHexClicked( )
{
    toHex( &canopenPVarDataList, canopenPVarPrevDataType, 8 );

    canopenPVarPrevDataType = HEX;
}


void CANFestivalGui::canopenDictBinClicked( )
{
    QList<QLineEdit*> tempList;

    tempList.append( ui->canopenDictIndex );
    toBin( &tempList, canopenDictPrevDataType, 16 );

    tempList.clear( );
    tempList.append( ui->canopenDictSubIndex);
    toBin( &tempList, canopenDictPrevDataType, 8 );

    toBin( &canopenDictDataList, canopenDictPrevDataType, 8 );

    canopenDictPrevDataType = BIN;
}



void CANFestivalGui::canopenDictDecClicked( )
{
    QList<QLineEdit*> tempList;

    tempList.append( ui->canopenDictIndex );
    toDec( &tempList, canopenDictPrevDataType, 5 );

    tempList.clear( );
    tempList.append( ui->canopenDictSubIndex);
    toDec( &tempList, canopenDictPrevDataType, 3 );

    toDec( &canopenDictDataList, canopenDictPrevDataType, 3 );

    canopenDictPrevDataType = DEC;
}


void CANFestivalGui::canopenDictHexClicked( )
{
    QList<QLineEdit*> tempList;

    tempList.append( ui->canopenDictIndex );
    toHex( &tempList, canopenDictPrevDataType, 6 );

    tempList.clear( );
    tempList.append( ui->canopenDictSubIndex);
    toHex( &tempList, canopenDictPrevDataType, 4 );

    toHex( &canopenDictDataList, canopenDictPrevDataType, 4 );

    canopenDictPrevDataType = HEX;
}


void CANFestivalGui::canBINClicked( )
{
    QList<QLineEdit*>    tempList;

    tempList.append( ui->canIdentifier );

    toBin( &canDataList, canPrevDataType, 8 );
    toBin( &tempList, canPrevDataType, 11 );

    canPrevDataType = BIN;
}


void CANFestivalGui::canHEXClicked( )
{
    QList<QLineEdit*>    tempList;

    tempList.append( ui->canIdentifier );

    toHex( &canDataList, canPrevDataType, 8 );
    toHex( &tempList, canPrevDataType, 11 );

    canPrevDataType = HEX;
}


void CANFestivalGui::canDECClicked( )
{
    QList<QLineEdit*>    tempList;

    tempList.append( ui->canIdentifier );

    toDec( &canDataList, canPrevDataType, 8 );
    toDec( &tempList, canPrevDataType, 11 );

    canPrevDataType = DEC;
}




void CANFestivalGui::canopenPDOBinClicked( )
{
    toBin( &canopenPDODataList, canopenPrevDataType, 8 );

    canopenPrevDataType = BIN;
}


void CANFestivalGui::canopenPDODecClicked( )
{
    toDec( &canopenPDODataList, canopenPrevDataType, 3 );

    canopenPrevDataType = DEC;
}


void CANFestivalGui::canopenPDOHexClicked( )
{
    toHex( &canopenPDODataList, canopenPrevDataType, 3 );

    canopenPrevDataType = HEX;
}


void CANFestivalGui::canopenSDOBinClicked( )
{
    toBin( &canopenSDODataList, canopenPrevDataType, 8 );

    canopenPrevDataType = BIN;
}


void CANFestivalGui::canopenSDODecClicked( )
{
    toDec( &canopenSDODataList, canopenPrevDataType, 3 );

    canopenPrevDataType = DEC;
}


void CANFestivalGui::canopenSDOHexClicked( )
{
    toHex( &canopenSDODataList, canopenPrevDataType, 3 );

    canopenPrevDataType = HEX;
}



void CANFestivalGui::toHex(QList<QLineEdit *> *theList, int prevState, int textLength )
{
    if( prevState == BIN ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setText( "0x" + QString( ).setNum( strtol( theList->at( i )->text( ).toStdString().c_str(), NULL, 2 ), 16 ) );
            theList->at( i )->setMaxLength( textLength );
        }
    } else if( prevState == DEC ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setMaxLength( textLength );
            theList->at( i )->setText( "0x" + QString( ).setNum( theList->at( i )->text( ).toInt( ), 16 ) );
        }
    }
}

void CANFestivalGui::toBin( QList<QLineEdit*>* theList, int prevState, int textLength )
{
    for( uint i=0; i<theList->count( ); i++ ) {
        theList->at( i )->setMaxLength( textLength );
    }
    if( prevState == HEX ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setText( QString( ).setNum( strtol( theList->at( i )->text( ).toStdString().c_str(), NULL, 16 ), 2 ) );
        }
    } else if( prevState == DEC ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setText( QString( ).setNum( theList->at( i )->text( ).toInt( ), 2 ) );
        }
    }
}

void CANFestivalGui::toDec( QList<QLineEdit*>* theList, int prevState, int textLength )
{
    if( prevState == BIN ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setText( QString( ).setNum( strtol( theList->at( i )->text( ).toStdString().c_str(), NULL, 2 ) ) );
            theList->at( i )->setMaxLength( textLength );
        }
    } else if( prevState == HEX ) {
        for( uint i=0; i<theList->count( ); i++ ) {
            theList->at( i )->setText( QString( ).setNum( strtol( theList->at( i )->text( ).toStdString().c_str(), NULL, 16 ) ) );
            theList->at( i )->setMaxLength( textLength );
        }
    }
}


void CANFestivalGui::clearCANSentLog( )
{
    ui->canLogView->setText( QString( ) );
}


void CANFestivalGui::clearCanReceiveLog( )
{
    ui->canReceiveLog->setText( "" );
}
