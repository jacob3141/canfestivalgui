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

namespace Ui {
    class MainGui;
}

class MainGui : public QWidget
{
    Q_OBJECT

public:
    MainGui( QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0 );
    ~MainGui();

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

protected:
    Ui::MainGui *ui;
};
