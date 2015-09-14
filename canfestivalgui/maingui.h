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

#include <QWidget>
#include <QList>
#include <QLineEdit>

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

namespace Ui {
    class MainGui;
}

class LogThread;
class ProcessVarGui;
class MainGui : public QWidget
{
    Q_OBJECT

public:
    MainGui( QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );
    ~MainGui();

public slots:
    void canBINClicked( );
    void canDECClicked( );
    void canHEXClicked( );
    void canopenDictBinClicked( );
    void canopenDictDecClicked( );
    void canopenDictHexClicked( );
    void canopenDictRead( );
    void canopenDictWrite( );
    void canopenPDOBinClicked( );
    void canopenPDODecClicked( );
    void canopenPDOHexClicked( );
    void canopenPVarBinClicked( );
    void canopenPVarDecClicked( );
    void canopenPVarDownload( );
    void canopenPVarHexClicked( );
    void canopenPVarShow( );
    void canopenPVarWrite( );
    void canopenSDOBinClicked( );
    void canopenSDODecClicked( );
    void canopenSDOHexClicked( );
    void clearCANSentLog( );
    void clearCanReceiveLog( );
    void initModule( );
    void portChanged( );
    void sendCan( );
    void sendNMT( );
    void sendPDO( );
    void sendSDO( );
    void sendSync( );
    void simulationNo( );
    void simulationYes( );

    void canopenPVarRead();
    void readCan();
    void restartNode();
    void viewTransferTable();
protected:
    Ui::MainGui *ui;

private:
    int getLength(QList<QLineEdit *> & );
    int openDevice( );
    int closeDevice( );

    void toHex( QList<QLineEdit*>*, int, int );
    void toBin(QList<QLineEdit *> *, int, int );
    void toDec( QList<QLineEdit*>*, int, int );

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
};


extern void setWait(int);
extern int getWait();

