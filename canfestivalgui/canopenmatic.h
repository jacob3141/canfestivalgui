/*********************************************************
 *                                                       *
 * CanOpen Master Application Transfer Interface Concept *
 *                                                       *
 *********************************************************
 *                    CanOpenMatic.h                     *
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
 * Header file for CanOpenMatic                          *
 *                                                       *
 *********************************************************/ 

#ifndef __canopenmatic_h__
#define __canopenmatic_h__

// Byte alignment !
/* #pragma pack(1) */

// Some usefull macros
	// To test if all seted bits of a mask are set in a state byte too. 
#define ALL_SET(state,mask) \
	((~state & mask)? 0 /* there was a bad bit */ : 1 /* all are good*/ )
#define Rx 0
#define Tx 1


// Misc constants
#define MAX_CAN_BUS_ID 2
#define SDO_MAX_NODE_ID 128
// !!!!!!!!!! what is?
#define SDO_MAX_DOMAIN_LEN 32
#define PDO_MAX_LEN 8
#define PDO_MAX_NODE_ID 4*128
#define NMT_MAX_NODE_ID 128

//CANOpen usefull helpers
#define GET_NODE_ID(m) (m.cob_id.b.b0 & 0x7f)
#define GET_FUNCTION_CODE(m) (m.cob_id.b.b1 & 0x07) << 1 |(m.cob_id.b.b0 & 0x80) >> 7

// Function Codes
#define NMT	   0x0
#define SYNC       0x1
#define TIME_STAMP 0x2
#define PDO1tx     0x3
#define PDO1rx     0x4
#define PDO2tx     0x5
#define PDO2rx     0x6
#define PDO3tx     0x7
#define PDO3rx     0x8
#define PDO4tx     0x9
#define PDO4rx     0xA
#define SDOtx      0xB
#define SDOrx      0xC
#define NODE_GUARD 0xE

// Function Codes Patterns
#define PDOnrx     0x4
#define PDOntx     0x3

typedef struct s_proc_info{
	char function_code;
	char name[20];
	int (*process_function)(int,Message *,const struct s_proc_info *,int);
} proceed_info;

//
// SDO Command Specifier Patterns and (un)packing macros
//
//Initiate Domain Download request
#define IDD_client(n,e,s) (0x20 | ((n & 0x03) << 2) | ((e & 0x01) << 1) | (s & 0x01))
//Domain Download Segment request
#define DDS_client(t,n,c) (0x00 | ((t & 0x01) << 4) | ((n & 0x07) << 1) | (c & 0x01))
//Initiate Domain Upload request
#define IDU_client 0x40
//Domain Upload Segment request
#define UDS_client 0x60

//Initiate Domain Download response
#define IDD_server 0x60		//0110
//Domain Download Segment response
//!!!!!!!!! stimmet die sache?!!!!!???? also ich wuer saege, da fehlt das huere: t
#define DDS_server 0x20 	//0010
//Initiate Domain Upload response
#define IDU_server 0x40		//0100
// !!!!!!!!!!was isch das cs!???
#define IDU_server_params(cs,n,e,s) n = (cs & 0x0c) >> 2; e = (cs & 0x02) >> 1; s = cs & 0x01;
//Domain Upload Segment response
#define UDS_server 0x00		//0000
#define UDS_server_params(cs,t,n,c) t = (cs & 0x10) >> 4; n = (cs & 0x0e) >> 1; c = cs & 0x01;

#define IS_SEGMENTED_RESPONSE(SCS)	!(SCS & 0x40)	//0100
#define IS_DOWNLOAD_RESPONSE(SCS)	(SCS & 0x20)	//0010

//Abort Domain Transfer
#define ADT_server 0x80		//1000

//
// NMT Command Specifier
//
#define NMT_Start_Node	0x01
#define NMT_Stop_Node	0x02
#define NMT_Enter_PreOperational	0x80
#define NMT_Reset_Node	0x81
#define NMT_Reset_Comunication	0x82

//The SDO structure
// !!!!!!!!!!!was soll das?!
struct struct_s_SDO {
	char ID;		//Node ID
	char len;		//body len
	struct {
		char SCS;		//SDO command specifier
		union {
			struct {	//for domain initaiation
				unsigned short index;
				unsigned char subindex;
				char data[4];
			}init;
			struct {	//for data segment
				char data[7];
			}segment;
		}data;
	} body ;
} __attribute__((packed));

typedef struct struct_s_SDO s_SDO;

//The PDO structure
struct struct_s_PDO {
	unsigned short ID;		//Node ID
	char len;		//body len
	char data[8];
} __attribute__((packed));
// !!!!!!!!! was bedeutet __attrib....?

typedef struct struct_s_PDO s_PDO;


// The Transfer structure
struct struct_s_transfer {
	char state;
	unsigned short index;
	unsigned char subindex;
	char count;
	char offset;
	char data[SDO_MAX_DOMAIN_LEN];
} __attribute__((packed));
typedef struct struct_s_transfer s_transfer;

#define S_TRANSFER_INITIALIZER {0,0,0,0,0,{[0 ... SDO_MAX_DOMAIN_LEN - 1] = 0}}

// The process_var structure
struct struct_s_process_var {
	char state;
	char count;
	char data[PDO_MAX_LEN];
}__attribute__((packed));

typedef struct struct_s_process_var s_process_var;

#define S_PROCESS_VAR_INITIALIZER {0,0,{[0 ... PDO_MAX_LEN - 1] = 0}}

//When do you want to send
#define NOW 1
#define LATER 0

// Different SDO transfer states
// Bits 0-1 (working state) 
#define TS_ACTIVITY(state)	(state & 0x03)
#define TS_IS_ON(state)	(state & 0x01)
#define TS_SET_ACTIVITY(state, activity)	state = ((state & ~0x03) | activity);
#define TS_INACTIV	0x00
#define TS_ACTIVATED	0x01
#define TS_WORKING	0x03
#define TS_ERROR	0x02

// Bits 0-2 (Action)
// download oder upload? 1: download, 0: upload
#define TS_IS_DOWNLOAD(state)	!(state & 0x04)
#define TS_FREE	0x00

// variable muss gedownloaded werden
#define TS_DOWNLOAD	0x01
#define TS_DOWNLOADING	0x02
#define TS_FINISHED	0x04
#define TS_UPLOAD	0x05
#define TS_UPLOADING	0x06
// Bit 3
#define TS_WAIT_SERVER	0x08
#define TS_HAVE_TO_DO(state)	!(state & 0x08)
#define TS_TOGGLE	0x10

// Prototypes
#ifdef __cplusplus
extern "C" {
#endif
int Message_Handler(int);
// senden eines nackten SDOs. macht keinen eintrag in tabelle. liest keine eintraege aus tabellen
int Send_SDO(int, s_SDO, int);
// senden eines nackten PDOs. macht keinen eintrag in tabelle. liest keine eintraege aus tabellen
int Send_PDO(int, s_PDO, int);
// senden eines nackten Syncs. macht keinen eintrag in tabelle. liest keine eintraege aus tabellen
int Send_Sync(int);
// senden eines nackten MNTs. macht keinen eintrag in tabelle. liest keine eintraege aus tabellen
int Send_NMT(int, int, char);
// da gehts um SDOs
// wird nur ausgefuehrt, wenn TS_WAIT_SERVER == 0 ist. Also: TS_HAVE_TO_DO == 1 ist.
// 2 verschiedene moeglichkeiten:
// 1.
// 2.
int Flux_MGR(int, int);

// alle gleiche argumente, damit sie mittels tabelle einfach gestartet werden koennen
//
int ProceedSDO       (int, Message *,const proceed_info *, int);
int ProceedPDO       (int, Message *,const proceed_info *, int);
int ProceedNODE_GUARD(int, Message *,const proceed_info *, int);

int Process_MGR(int, int);

int WriteProcessVar(int, int, int, unsigned int, char *);
int DownloadProcessVars(int);
int ReadProcessVar(int, int, char *);

int WriteDictionaryEntry(int, int , unsigned short , char , unsigned int , void *);
int ReadDictionaryEntry(int, int , unsigned short , char , char *);

int ReadNodeState(int, int);

// senden bzw. empfangen von reinen can nachrichten
int f_can_receive(int, Message *);
int f_can_send(int, Message *);
s_process_var getProcessVar( int, int, int );

#ifdef __cplusplus
}
#endif


#endif
