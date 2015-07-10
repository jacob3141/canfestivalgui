/*********************************************************
 *                                                       *
 *  Advanced Ring Buffer Redundant Application for CAN   *
 *                                                       *
 *********************************************************
 *                      ArbraCan.c                       *
 *********************************************************
 * This program is free software; you can redistribute   *
 * it and/or modify it under the terms of the GNU General*
 * Public License as published by the Free Software      *
 * Foundation; either version 2 of the License, or (at   *
 * your option) any later version.                       *
 *                                                       *
 * This program is distributed in the hope that it will  *
 * be useful, but WITHOUT ANY WARRANTY; without even the *
 * implied warranty of MERCHANTABILITY or FITNESS FOR A  *
 * PARTICULAR PURPOSE.  See the GNU General Public       *
 * License for more details.                             *
 *                                                       *
 * You should have received a copy of the GNU General    *
 * Public License along with this program; if not, write *
 * to 	The Free Software Foundation, Inc.               *
 *	675 Mass Ave                                     *
 *	Cambridge                                        *
 *	MA 02139                                         *
 * 	USA.                                             *
 *********************************************************
 *                                                       *
 *      Author: Edouard TISSERANT                        *
 *      Contact: edouard.tisserant@esstin.u-nancy.fr     *
 *      Version: 1.0                                     *
 *      Modification date:                               *
 *      Description:                                     *
 *-------------------------------------------------------*
 * Header file for ArbraCan.c and structure definitions  *
 * to communicate with it.                               *
 *                                                       *
 *********************************************************/ 

#ifndef __can_h__
#define __can_h__

// Prevent holes
#pragma pack(1)

union SHORT {
	        struct { unsigned char b0,b1; } b;
	        unsigned short w;
	       };

typedef struct {
	union SHORT cob_id;		// l'ID du mesg
	char rtr;				// remote transmission request
	char len;				// message length
	unsigned char data[8];  // data 
} Message;

#endif
