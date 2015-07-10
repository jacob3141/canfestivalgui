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

#include <QThread>
#include <QSemaphore>
#include <Q3TextView>

#include "canfestivalgui.h"

#include "include/Can.h"
#include "include/CanOpenMatic.h"


class CANFestivalGui;
class LogThread : public QThread  {
private:
    Q3TextView*      mCanReceiveLog;
    CANFestivalGui* mGui;
    QSemaphore*     mpReadLogSem;    // semaphore for accessing the log-textfield
    int             mCanMsgNr;
    bool            mMach;
    bool            mRun;
public:
    LogThread( Q3TextView*, CANFestivalGui* );
    ~LogThread( );

    virtual void run( );
    void getSem( ) { mpReadLogSem++; }
    void putSem( ) { mpReadLogSem--; }
    void stop( ) { mRun = false; }
};
