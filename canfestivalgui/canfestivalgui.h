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

#pragma once

#include <maingui.h>

#include <QList>
#include <QLineEdit>

#include "logthread.h"
#include "processvargui.h"

#define BUSNAME_SIZE 40
#define CMD_SIZE 100
#define STATE_BADCOUNT -3
#define STATE_FAULT -2
#define STATE_FINISHED -1
#define STATE_OK 0
#define STATE_STOP 1
#define STATE_PERIODIC 2
#define STATE_ASYNC 3
#define STATE_Rx 4
#define STATE_Tx 5

/**
  *@author Raphael Zulliger
  */

class LogThread;

class CANFestivalGui : public MainGui  {
private:
    int wait;
    int fd;
    char busname[40];

    // while changing datatype (hex/bin/dec) we have to convert the values to the new format.
    // therefore it is neccessary to know the previous data format
    // 0->hex
    // 1->bin
    // 2->dec
    char canopenPrevDataType;
    char canPrevDataType;
    char canopenDictPrevDataType;
    char canopenPVarPrevDataType;

    bool simulation;
    bool driverLoaded;
    enum {HEX, BIN, DEC};
    QList<QLineEdit*> canopenPDODataList;
    QList<QLineEdit*> canopenSDODataList;
    QList<QLineEdit*> canopenDictDataList;
    QList<QLineEdit*> canopenPVarDataList;
    QList<QLineEdit*> canDataList;

    LogThread* mLogThread;

    ProcessVarGui*    mPVarGui;

    // private Memberfunctions...
    int getLength(QList<QLineEdit *> & );
    int openDevice( );
    int closeDevice( );

    void toHex( QList<QLineEdit*>*, int, int );
    void toBin(QList<QLineEdit *> *, int, int );
    void toDec( QList<QLineEdit*>*, int, int );

public:
    CANFestivalGui();
    ~CANFestivalGui();

    // Data format changes...
    virtual void canBINClicked( );
    virtual void canDECClicked( );
    virtual void canHEXClicked( );

    virtual void canopenPDOBinClicked( );
    virtual void canopenPDOHexClicked( );
    virtual void canopenPDODecClicked( );

    virtual void canopenSDOBinClicked( );
    virtual void canopenSDOHexClicked( );
    virtual void canopenSDODecClicked( );

    virtual void canopenDictBinClicked( );
    virtual void canopenDictDecClicked( );
    virtual void canopenDictHexClicked( );

    virtual void canopenPVarBinClicked( );
    virtual void canopenPVarDecClicked( );
    virtual void canopenPVarHexClicked( );

    // Device related
    virtual void initModule( );
    virtual void portChanged( );

    virtual void simulationNo( );
    virtual void simulationYes( );

    // Buttons...
    virtual void sendCan( );
//    virtual void readCan( );
    virtual void sendNMT( );
    virtual void sendPDO( );
    virtual void sendSDO( );
    virtual void sendSync( );

    virtual void canopenDictWrite( );
    virtual void canopenDictRead( );

    virtual void canopenPVarRead( );
    virtual void canopenPVarWrite( );
    virtual void canopenPVarDownload( );
    virtual void canopenPVarShow( );

    virtual void clearCANSentLog( );
    virtual void clearCanReceiveLog( );
};


void setWait( int );
int getWait( );
