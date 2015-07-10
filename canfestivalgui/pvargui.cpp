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

#include "pvargui.h"

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3Table>
#include <qspinbox.h>

#include <iostream>

#include "include/Can.h"
#include "include/ArbraCan.h"
#include "include/CanOpenMatic.h"

PVarGui::PVarGui()
{
    Q3Header *header;

    header = rxTable->horizontalHeader( );
    for( int i=0; i<2; i++ ) {
        header->setLabel( 0, "State" );
        header->setLabel( 1, "Count" );
        header->setLabel( 2, "D0" );
        header->setLabel( 3, "D1" );
        header->setLabel( 4, "D2" );
        header->setLabel( 5, "D3" );
        header->setLabel( 6, "D4" );
        header->setLabel( 7, "D5" );
        header->setLabel( 8, "D6" );
        header->setLabel( 9, "D7" );

        header = txTable->horizontalHeader( );
    }

    header = rxTable->verticalHeader( );
    for( int i=0; i<2; i++ ) {
        header->setLabel( 0, "PDO1" );
        header->setLabel( 1, "PDO2" );
        header->setLabel( 2, "PDO3" );
        header->setLabel( 3, "PDO4" );

        header = txTable->verticalHeader( );
    }

//    for( int i=0; i<rxTable->numRows( ); i++ ) {
//        rxTable->adjustRow( i );
//    }
//    for( int i=0; i<txTable->numRows( ); i++ ) {
//        txTable->adjustRow( i );
//    }

    for( int i=0; i<rxTable->numCols( ); i++ ) {
        rxTable->adjustColumn( i );
    }
    for( int i=0; i<txTable->numCols( ); i++ ) {
        txTable->adjustColumn( i );
    }

    // fill in data of canopen-Device 0
    fillInData( 0 );
}



PVarGui::~PVarGui()
{
}


void PVarGui::canopenIdChanged( )
{
    fillInData( canopenPVarViewIdentifier->text( ).toInt( ) );
}

void PVarGui::fillInData( int id )
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
        txTable->setText( row, col, QString( ).setNum( (unsigned char)processVar.data[col-2]  ) );
    }
    txTable->setText( row, 0, QString( statusTab[processVar.state&&0x0F].descr ) );
    txTable->setText( row, 1, QString( ).setNum( processVar.count ) );


    // fill in all receive data
    processVar = getProcessVar( 0, Rx, id );

    for( int col=2; col<10; col++ ) {
        rxTable->setText( row, col, QString( ).setNum( (unsigned char)processVar.data[col-2]  ) );
    }
    rxTable->setText( row, 0, QString( statusTab[processVar.state&&0x0F].descr ) );
    rxTable->setText( row, 1, QString( ).setNum( processVar.count ) );


    for( int i=0; i<rxTable->numCols( ); i++ ) {
        rxTable->adjustColumn( i );
    }
    for( int i=0; i<txTable->numCols( ); i++ ) {
        txTable->adjustColumn( i );
    }

}
