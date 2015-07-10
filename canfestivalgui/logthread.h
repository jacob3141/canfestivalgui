/***************************************************************************
                          logthread.h  -  description
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

#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <qthread.h>
#include <qtextview.h>

#include "canfestivalgui.h"

#include "include/Can.h"
#include "include/CanOpenMatic.h"

/**
  *@author Raphael Zulliger
  */

class CANFestivalGui;
class LogThread : public QThread  {
private:
    QTextView*      mCanReceiveLog;
    CANFestivalGui* mGui;
    QSemaphore*     mpReadLogSem;    // semaphore for accessing the log-textfield
    int             mCanMsgNr;
    bool            mMach;
    bool            mRun;
public: 
	LogThread( QTextView*, CANFestivalGui* );
	~LogThread( );

    virtual void run( );
    void getSem( ) { mpReadLogSem++; }
    void putSem( ) { mpReadLogSem--; }
    void stop( ) { mRun = false; }
};

#endif
