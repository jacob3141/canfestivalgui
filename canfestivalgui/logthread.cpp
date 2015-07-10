/***************************************************************************
                          logthread.cpp  -  description
                             -------------------
    begin                : Tue May 14 2002
    copyright            : (C) 2002 by Raphael Zulliger
    email                : rzullige@hsr.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "logthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <qevent.h>
#include <qpoint.h>

LogThread::LogThread( QTextView* logView, CANFestivalGui* theGui )
{
    mCanReceiveLog = logView;
    mGui = theGui;
    mpReadLogSem = new QSemaphore( 1 );
    mRun = true;

    mCanMsgNr = 0;
}

LogThread::~LogThread()
{

}

void LogThread::run( )
{
    Message m;
    char    text[255];
    QString tempData;
    int tempWait;

    while( mRun == true ) {
        // try to get the Semaphore
        mpReadLogSem++;
        tempWait = getWait( );
        setWait( 0 );
        if( f_can_receive( 0, &m ) == 0 ) {
            for( int i=0; i<m.len; i++ ) {
                snprintf( text, 254, "%x | ", m.data[i] );
                tempData.append( text );
            }
            tempData.truncate( tempData.length( ) - 1 );
            mCanReceiveLog->append( QString::QString( ).sprintf( "Received Message (hex): CAN-ID %4x     Data: %s", m.cob_id.w, tempData.latin1( ) ) );
            // it seams theres a BUG! with these 4 operations the content is shown correctly... BUT: if too much
            // inputs from the CANbus occurs, the program may crash :-(
            // to avoid this crash, comment the following 4 lines out and recompile the program.
            mCanReceiveLog->center( 0, mCanReceiveLog->contentsHeight( ) );
            mCanReceiveLog->viewport( )->repaint( );
            mCanReceiveLog->hide( );
            mCanReceiveLog->show( );
            tempData = "";
        }
        setWait( tempWait );
        // release semaphore
        mpReadLogSem--;
        usleep( 10 );
    }
    return;
}
