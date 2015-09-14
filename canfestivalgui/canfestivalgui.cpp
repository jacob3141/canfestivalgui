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





void CANFestivalGui::initModule( ) {
    if( !driverLoaded ) {
        // load the driver. if allready loaded, a message to stdout occurs...
        system( "/sbin/insmod /home/rzullige/CanFestival/ArbraCan/arbracan.o can_silent=0 can_rate=125" );
        driverLoaded = true;

        // open the canport (/dev/canx)
        if( ( fd = openDevice( ) ) < 0 ) {
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


