/***************************************************************************
                          pvargui.h  -  description
                             -------------------
    begin                : Sun May 12 2002
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

#ifndef PVARGUI_H
#define PVARGUI_H

#include <processvargui.h>

/**
  *@author Raphael Zulliger
  */

class PVarGui : public ProcessVarGui  {
private:
    void fillInData( int );
public:
    PVarGui();
    ~PVarGui();

    virtual void canopenIdChanged( );
};

#endif
