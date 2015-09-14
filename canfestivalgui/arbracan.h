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

#ifndef __arbracan_h__
#define __arbracan_h__

#define MESS_BUFF_SIZE	256
#define PRIORITY_LEVELS	8

/* ioctl's for canboard. */
#define SCHAR_MAJOR		91
#define CANBOARD_IOCTL_BASE	0x7a
#define CANBOARD_READ	_IOR(CANBOARD_IOCTL_BASE, 0, unsigned long)
#define CANBOARD_WRITE	_IOW(CANBOARD_IOCTL_BASE, 2, unsigned long)
#define CANBOARD_STATUS	_IOR(CANBOARD_IOCTL_BASE, 4, unsigned long)

/* No blocking access in RealTime OS*/
#define CANBOARD_READ_BLOCK	_IOR(CANBOARD_IOCTL_BASE, 1, unsigned long)
#define CANBOARD_WRITE_BLOCK	_IOW(CANBOARD_IOCTL_BASE, 3, unsigned long)

#define Rx 0
#define Tx 1

#endif
