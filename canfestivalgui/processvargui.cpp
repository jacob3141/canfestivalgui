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

#include "processvargui.h"
#include "ui_processvargui.h"



#include <iostream>

#include "can.h"
#include "arbracan.h"
#include "canopenmatic.h"

/*
 *  Constructs a ProcessVarGui which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ProcessVarGui::ProcessVarGui(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::ProcessVarGui) {
    _ui->setupUi(this);

    QStringList horizontalRxHeaderLabels;
    horizontalRxHeaderLabels
        << "State"
        << "Count"
        << "D0"
        << "D1"
        << "D2"
        << "D3"
        << "D4"
        << "D5"
        << "D6"
        << "D7";

    _ui->rxTable->setColumnCount(horizontalRxHeaderLabels.count());
    _ui->rxTable->setHorizontalHeaderLabels(horizontalRxHeaderLabels);

    QStringList verticalRxHeaderLabels;
    verticalRxHeaderLabels
        << "PDO1"
        << "PDO2"
        << "PDO3"
        << "PDO4";

    _ui->rxTable->setRowCount(verticalRxHeaderLabels.count());
    _ui->rxTable->setVerticalHeaderLabels(verticalRxHeaderLabels);

    // signals and slots connections
    connect( _ui->canopenPVarViewIdentifier, SIGNAL( valueChanged(int) ), this, SLOT( canopenIdChanged( ) ) );
    connect( _ui->PushButton1, SIGNAL( clicked() ), this, SLOT( canopenIdChanged( ) ) );

    // fill in data of canopen-Device 0
    fillInData( 0 );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ProcessVarGui::~ProcessVarGui()
{
    // no need to delete child widgets, Qt does it all for us
}

void ProcessVarGui::canopenIdChanged( )
{
    fillInData( _ui->canopenPVarViewIdentifier->text( ).toInt( ) );
}

void ProcessVarGui::fillInData( int id )
{
    int row=0;
    s_process_var processVar;
    struct status {
        int state;
        char descr[100];
    }__attribute__((packed));

    status statusTab[] = { { 0x00, "Free" },
                           { 0x01, "Download Request" },
                           { 0x02, "Download" },
                           { 0x03, "Download" },
                           { 0x04, "Unknow State" },
                           { 0x05, "Unknow State" },
                           { 0x06, "Unknow State" },
                           { 0x07, "Unknow State" },
                           { 0x08, "Unknow State" },
                           { 0x09, "Download Request, waiting for server" },
                           { 0x0a, "Unknow State" },
                           { 0x0b, "Unknow State" },
                           { 0x0c, "Unknow State" },
                           { 0x0d, "Unknow State" },
                           { 0x0e, "Unknow State" },
                           { 0x0f, "Unknow State" }};

    // fill in all transmit data
    processVar = getProcessVar( 0, Tx, id );

    for( int col=2; col<10; col++ ) {
        _ui->txTable->setItem(row, col,new QTableWidgetItem(
            QString("%1").arg((unsigned char)processVar.data[col-2])
         ));
    }
    _ui->txTable->setItem(row, 0,new QTableWidgetItem(
        QString("%1").arg(statusTab[processVar.state&&0x0F].descr)
    ));

    _ui->txTable->setItem(row, 1,new QTableWidgetItem(
        QString("%1").arg(processVar.count)
    ));

    // fill in all receive data
    processVar = getProcessVar( 0, Rx, id );

    for( int col=2; col<10; col++ ) {
        _ui->rxTable->setItem(row, col,new QTableWidgetItem(
            QString("%1").arg((unsigned char)processVar.data[col-2])
         ));
    }
    _ui->rxTable->setItem(row, 0,new QTableWidgetItem(
        QString("%1").arg(statusTab[processVar.state&&0x0F].descr)
    ));

    _ui->rxTable->setItem(row, 1,new QTableWidgetItem(
        QString("%1").arg(processVar.count)
    ));
}

