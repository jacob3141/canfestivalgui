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

#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "ui_maingui.h"


MainGui::MainGui(QWidget* parent,  const char* name, Qt::WindowFlags fl )
    : QWidget( parent),
      ui(new Ui::MainGui) {
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->canPort, SIGNAL( valueChanged(int) ), this, SLOT( portChanged( ) ) );
    connect( ui->SimulationNoRadioButton, SIGNAL( clicked() ), this, SLOT( simulationNo( ) ) );
    connect( ui->sendCanButton, SIGNAL( clicked() ), this, SLOT( sendCan( ) ) );
    connect( ui->sendPDOButton, SIGNAL( clicked() ), this, SLOT( sendPDO( ) ) );
    connect( ui->sendNMTButton, SIGNAL( clicked() ), this, SLOT( sendNMT( ) ) );
    connect( ui->canHexFormat, SIGNAL( clicked() ), this, SLOT( canHEXClicked( ) ) );
    connect( ui->canDecFormat, SIGNAL( clicked() ), this, SLOT( canDECClicked( ) ) );
    connect( ui->canBinFormat, SIGNAL( clicked() ), this, SLOT( canBINClicked( ) ) );
    connect( ui->sendSDOButton, SIGNAL( clicked() ), this, SLOT( sendSDO( ) ) );
    connect( ui->sendSyncButton, SIGNAL( clicked() ), this, SLOT( sendSync( ) ) );
    connect( ui->canopenPDOHexFormat, SIGNAL( clicked() ), this, SLOT( canopenPDOHexClicked( ) ) );
    connect( ui->canopenPDOBinFormat, SIGNAL( clicked() ), this, SLOT( canopenPDOBinClicked( ) ) );
    connect( ui->canopenPDODecFormat, SIGNAL( clicked() ), this, SLOT( canopenPDODecClicked( ) ) );
    connect( ui->canopenSDOHexFormat, SIGNAL( clicked() ), this, SLOT( canopenSDOHexClicked( ) ) );
    connect( ui->canopenSDOBinFormat, SIGNAL( clicked() ), this, SLOT( canopenSDOBinClicked( ) ) );
    connect( ui->canopenSDODecFormat, SIGNAL( clicked() ), this, SLOT( canopenSDODecClicked( ) ) );
    connect( ui->canopenDictHexFormat, SIGNAL( clicked() ), this, SLOT( canopenDictHexClicked( ) ) );
    connect( ui->canopenDictBinFormat, SIGNAL( clicked() ), this, SLOT( canopenDictBinClicked( ) ) );
    connect( ui->canopenDictDecFormat, SIGNAL( clicked() ), this, SLOT( canopenDictDecClicked( ) ) );
    connect( ui->readDictEntry, SIGNAL( clicked() ), this, SLOT( canopenDictRead( ) ) );
    connect( ui->writeDictEntry, SIGNAL( clicked() ), this, SLOT( canopenDictWrite( ) ) );
    connect( ui->viewTransferTableButton, SIGNAL( clicked() ), this, SLOT( viewTransferTable( ) ) );
    connect( ui->canopenPVarHexFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarHexClicked( ) ) );
    connect( ui->canopenPVarBinFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarBinClicked( ) ) );
    connect( ui->canopenPVarDecFormat, SIGNAL( clicked() ), this, SLOT( canopenPVarDecClicked( ) ) );
    connect( ui->writePVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarWrite( ) ) );
    connect( ui->downloadPVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarDownload( ) ) );
    connect( ui->showPVarButton, SIGNAL( clicked() ), this, SLOT( canopenPVarShow( ) ) );
    connect( ui->readCanButton, SIGNAL( clicked() ), this, SLOT( readCan( ) ) );
    connect( ui->PushButton65, SIGNAL( clicked() ), this, SLOT( clearCanReceiveLog( ) ) );
    connect( ui->SimulationYesRadioButton, SIGNAL( clicked() ), this, SLOT( simulationYes( ) ) );
    connect( ui->clearCANopenLogButton, SIGNAL( clicked() ), this, SLOT( clearCANSentLog( ) ) );
    connect( ui->initModuleButton, SIGNAL( clicked() ), this, SLOT( initModule( ) ) );
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

