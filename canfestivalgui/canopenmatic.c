/*********************************************************
 *                                                       *
 * CanOpen Master Application Transfer Interface Concept *
 *                                                       *
 *********************************************************
 *                    CanOpenMatic.c                     *
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
 * to     The Free Software Foundation, Inc.               *
 *    675 Mass Ave                                     *
 *    Cambridge                                        *
 *    MA 02139                                         *
 *     USA.                                             *
 *********************************************************
 *                                                       *
 *      Author: Edouard TISSERANT                        *
 *      Contact: edouard.tisserant@esstin.u-nancy.fr     *
 *      Version: 1.0                                     *
 *      Modification date:                               *
 *      Description:                                     *
 *-------------------------------------------------------*
 * This is the main functions of the CanOpenMatic API    *
 *                                                       *
 *********************************************************/

// #define DEBUG
#ifdef DEBUG
#ifdef __KERNEL__
#define MSG(string, args...) printk("%s:%d", __FILE__, __LINE__); printk(string, ##args)
#else
#include "stdio.h"
#define MSG(string, args...) printf("%s:%d", __FILE__, __LINE__); printf(string, ##args)
#endif
#else
#define MSG(string, args...)
#endif

#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/string.h>
#else
#include <stddef.h> /* for NULL */
#include <string.h>
#endif

#include "can.h"
#include "canopenmatic.h"

#include <stdio.h>
#include <stdlib.h>


// Array of message processing information
const proceed_info proceed_infos[]={
    {NMT,        "NMT",        NULL},
    {SYNC,        "SYNC",      NULL},
    {TIME_STAMP,    "TIME_STAMP",    NULL},
    {PDO1tx,    "PDO1tx",    ProceedPDO},
    {PDO1rx,    "PDO1rx",    NULL},
    {PDO2tx,    "PDO2tx",    ProceedPDO},
    {PDO2rx,    "PDO2rx",    NULL},
    {PDO3tx,    "PDO3tx",    ProceedPDO},
    {PDO3rx,    "PDO3rx",    NULL},
    {PDO4tx,    "PDO4tx",    ProceedPDO},
    {PDO4rx,    "PDO4rx",    NULL},
    {SDOtx,        "SDOtx",    ProceedSDO},
    {SDOrx,        "SDOrx",    NULL},
    {0xD,        "Unknown",    NULL},
    {NODE_GUARD,    "NODE GUARD",    ProceedNODE_GUARD},
    {0xF,        "Unknown",    NULL}
};

//Array of transfers
static s_transfer transfers[MAX_CAN_BUS_ID][SDO_MAX_NODE_ID] = {[0 ... MAX_CAN_BUS_ID-1] = {[0 ... SDO_MAX_NODE_ID-1] = S_TRANSFER_INITIALIZER}};

//Array of process varables
static s_process_var process_var[MAX_CAN_BUS_ID][2][PDO_MAX_NODE_ID] = {[0 ... MAX_CAN_BUS_ID-1] = {[0 ... 1] = {[0 ... SDO_MAX_NODE_ID-1] = S_PROCESS_VAR_INITIALIZER}}};

//Network Management Table
static int NMTable[MAX_CAN_BUS_ID][NMT_MAX_NODE_ID] = {[0 ... MAX_CAN_BUS_ID-1] = {[0 ... NMT_MAX_NODE_ID-1] = -1}};

// Message_Handler : call the receive function
// and call the implied process function
// Parameters : the function used to receive can messages.
int Message_Handler(int bus_id)
{
    Message m;
    int fc;                //the function code

    MSG("Message_Handler\n");

    if(f_can_receive!=NULL){
        if(!(f_can_receive)(bus_id, &m)){
            fc = GET_FUNCTION_CODE(m);
            if(proceed_infos[fc].process_function!=NULL){
                return (proceed_infos[fc].process_function)(bus_id,&m,&proceed_infos[fc],1);
            }
        }
    }

    return -1;                // If something were wrong
}


// muss da die laenge der CANMessage nicht immer 8 Byte betragen!?!? auch wenn nicht alle
// datenbytes benoetigt werden...
int Send_SDO(int bus_id, s_SDO sdo, int dir)
{
    Message m;

    MSG("Send_SDO\n");

    m.cob_id.w = sdo.ID | ((dir == Rx ? SDOrx : SDOtx)  << 7);
    m.rtr = 0x00;
    m.len = sdo.len;
    memcpy(&m.data, &sdo.body, m.len);
    return f_can_send(bus_id,&m);
}


int Send_PDO(int bus_id, s_PDO pdo, int dir)
{
    Message m;

    MSG("Send_PDO\n");

    // Map 4*128 IDs to PDO 1, 2, 3 and 4

    m.cob_id.w = (pdo.ID & 0x7f) | (((pdo.ID & 0x0180) << 1) + ((dir == Rx ? PDOnrx : PDOntx) << 7));
    m.rtr = dir;
    m.len = pdo.len;
    memcpy(&m.data, &pdo.data, m.len);
    return f_can_send(bus_id,&m);
}

int Send_Sync(int bus_id)
{
    Message m;

    MSG("Send_Sync\n");

    m.cob_id.w = 0x0080;
    m.rtr = 0x00;
    m.len = 0;
    return f_can_send(bus_id,&m);
}

int Send_NMT(int bus_id,int Node_ID, char cs)
{
    Message m;

    MSG("Send_NMT\n");

    m.cob_id.w = 0x0000; /*(NMT) << 7*/
    m.rtr = 0x00;
    m.len = 2;
    m.data[0] = cs;
    m.data[1] = (char)Node_ID;
    return f_can_send(bus_id,&m);
}

int Send_NODE_GUARD(int bus_id, int ID)
{
    Message m;

    MSG("Send_NODE_GUARD\n");

    m.cob_id.w = ID | NODE_GUARD << 7;
    m.rtr = 0xff;
    m.len = 0;
    return f_can_send(bus_id,&m);
}

int Flux_MGR(int bus_id, int ID) //Flux Manager
{
    int i, res;
    char t, n, c, e, s;
    s_SDO sdo;

    MSG("Flux_MGR\n");

    res = -1;

    sdo.ID = ID;

    if(TS_HAVE_TO_DO(transfers[bus_id][ID].state)){
            switch(TS_ACTIVITY(transfers[bus_id][ID].state)){
            // state bit: 01
            case TS_ACTIVATED:    // Initiate a Domain (up/down)load
                sdo.body.data.init.index = transfers[bus_id][ID].index;
                sdo.body.data.init.subindex = transfers[bus_id][ID].subindex;
                // wenn donwload bit auf 0 steht -> downlaod (also schreiben in den anderen)
                if(TS_IS_DOWNLOAD(transfers[bus_id][ID].state)){
                    // Number of bytes < 5 -> expedited tranfer
                    if(transfers[bus_id][ID].count < 5){
                        n = 4 - transfers[bus_id][ID].count;
                        e = 1;  // data bytes contain data to be downloaded...
                        s = 1;  //
                        sdo.len = 8 - n; // oder: sdo.len = transfers[bus_id][ID].count;
                        for(i=0; i<4-n; i++){
                            sdo.body.data.init.data[i] = transfers[bus_id][ID].data[i];
                        }
                        transfers[bus_id][ID].offset = transfers[bus_id][ID].count; // Next call will finish.
                    } else { // Normal transfer
                        n = 0;
                        e = 0;  // data bytes contain byte-counter
                        s = 1;  //
                        sdo.len = 8;
                        for(i=0; i<4-n; i++){  // re-idianees
                            sdo.body.data.init.data[i] = (transfers[bus_id][ID].count & (0xff << (i*8))) >> (i*8);
                        }
                        transfers[bus_id][ID].offset = 0;
                    }
                    sdo.body.SCS = IDD_client(n,e,s);
                // also doch upload ( also auslesen eines entfernten geraetes)
                } else {
                    sdo.len = 4;
                    sdo.body.SCS = IDU_client;
                    transfers[bus_id][ID].offset = 0;
                }
                res = Send_SDO(bus_id, sdo, Rx);
                TS_SET_ACTIVITY(transfers[bus_id][ID].state, TS_WORKING | TS_WAIT_SERVER)
                break;
            case TS_WORKING:    // Follow Domain (up/down)load
                // daten werden gedowloaded
                if(TS_IS_DOWNLOAD(transfers[bus_id][ID].state)){
                    i = transfers[bus_id][ID].count - transfers[bus_id][ID].offset;
                    if(i <= 0){ // Download Finished
                        res = 0;
                        transfers[bus_id][ID].state = TS_FREE;
                        break;
                    } else { // Follow segmented transfer
                        if(i>7){
                            n = 0;        // There is no unused byte
                            c = 0;        // It is not the last message
                        } else {
                            n = 7 - i;    // There could have unused bytes
                            c = 1;        // This is the last message
                        }
                        sdo.len = 8 - n;
                        for(i=0; i<7-n; i++){
                            sdo.body.data.segment.data[i] = transfers[bus_id][ID].data[(int)transfers[bus_id][(int)sdo.ID].offset++];
                        }
                        t = (transfers[bus_id][ID].state ^= TS_TOGGLE);
                        sdo.body.SCS = DDS_client(t,n,c);
                    }
                } else { // daten werden uploaded
                    sdo.len = 1;
                    sdo.body.SCS = UDS_client;
                }
                res = Send_SDO(bus_id, sdo, Rx);
                TS_SET_ACTIVITY(transfers[bus_id][ID].state, TS_WORKING | TS_WAIT_SERVER)
                break;
            default:    // Transfer not in use or transfer error. Blub blub...
                break;
        }
    }
    return res;
}

int ProceedSDO(int bus_id, Message *m,const proceed_info *p_i, int follow)
{
    int i;
    char t, n, c, e, s;
    s_SDO sdo;

    MSG("ProceedSDO\n");

    sdo.ID = GET_NODE_ID((*m));
    sdo.len = (*m).len;
    memcpy(&sdo.body, &m->data, sdo.len);

    // If there really is a running transfer
    // And we are waiting for a message
    // And the message is not Abort
    if(TS_ACTIVITY(transfers[bus_id][(int)sdo.ID].state) == TS_WORKING &&
       !TS_HAVE_TO_DO(transfers[bus_id][(int)sdo.ID].state) &&
       !(sdo.body.SCS & ADT_server)){
        if(IS_DOWNLOAD_RESPONSE(sdo.body.SCS)){
            // FIXME : Should warn for strange & unexpected paquets...
            if(transfers[bus_id][(int)sdo.ID].count <= transfers[bus_id][(int)sdo.ID].offset){
                    transfers[bus_id][(int)sdo.ID].state = TS_FREE;
            }
       } else { // Upload -> wir erhalten daten von einem entfernten geraet.

            if(IS_SEGMENTED_RESPONSE(sdo.body.SCS)){ //segment containing data to store.
                UDS_server_params(sdo.body.SCS,t,n,c)
                // FIXME : should warn for bad toggle bit
                for(i=0; i<7-n; i++){ //FIXME : should take care of data overrun
//                    transfers[bus_id][(int)sdo.ID].data[i + transfers[bus_id][(int)sdo.ID].offset++] = sdo.body.data.segment.data[i];
                    transfers[bus_id][(int)sdo.ID].data[ (int)transfers[bus_id][(int)sdo.ID].offset++ ] = sdo.body.data.segment.data[i];
                }
                if(c)    // If last segment get in finished state.
                    transfers[bus_id][(int)sdo.ID].state = TS_FINISHED;
                    transfers[bus_id][(int)sdo.ID].count = transfers[bus_id][(int)sdo.ID].offset;
            } else {    //Initial Upload Upload Response
                IDU_server_params(sdo.body.SCS,n,e,s)
                // FIXME : should warn for crazy dictionary (sub)index
                if(e){            //expedited transfer
                    if(!s) n = 0;    // "data bytes contain data to be downloaded"
                    for(i=0; i<4-n; i++){
                        transfers[bus_id][(int)sdo.ID].data[i] = sdo.body.data.init.data[i];
                    }
                    transfers[bus_id][(int)sdo.ID].count = 4-n;
                    transfers[bus_id][(int)sdo.ID].state = TS_FINISHED;
                } else {        //normal transfer
                    if(s){
                        for(i=0; i<4-n; i++){
                            transfers[bus_id][(int)sdo.ID].count |= sdo.body.data.init.data[i] << (i*8);
                        }
                        transfers[bus_id][(int)sdo.ID].offset = 0;
                    }else{ //FIXME : e=0 et s=0  Standard ?
                        transfers[bus_id][(int)sdo.ID].offset = 0;
                        // die nachfolgenden zwei zeilen sind NICHT standardkomform!!!!!!!!
                        for(i=0; i<4; i++){
                            transfers[bus_id][(int)sdo.ID].data[(int)transfers[bus_id][(int)sdo.ID].offset++] = sdo.body.data.init.data[i];
                        }
                    }
                }
            }
        }
        // Stop waiting for this node after each received message.
        transfers[bus_id][(int)sdo.ID].state &= ~TS_WAIT_SERVER;
        if(follow) Flux_MGR(bus_id,sdo.ID);
    } else {//FIXME : should warn for unexpected message
        transfers[bus_id][(int)sdo.ID].state = TS_ERROR;
    }
    return 0;
}

int Process_MGR(int bus_id, int ID) //PDO Manager
{
    int res;
    s_PDO pdo;

    MSG("Process_MGR\n");

    if(process_var[bus_id][Tx][ID].state == (TS_DOWNLOAD & ~TS_WAIT_SERVER)){
        pdo.ID = ID;
        pdo.len =  process_var[bus_id][Tx][ID].count;
        memcpy(&(pdo.data), &(process_var[bus_id][Tx][ID].data), pdo.len);
        res = Send_PDO(bus_id,pdo, Rx);
        process_var[bus_id][Tx][ID].state |= TS_WAIT_SERVER;
        return res;
    }
    return -1;
}

int ProceedPDO(int bus_id, Message *m,const proceed_info *p_i, int dummy)
{
    // Hack to map PDOtx 1, 2, 3, & 4 in the same table
    int ID = GET_NODE_ID((*m)) + (((p_i->function_code)-3) << 6);

    MSG("ProceedPDO ID=%d\n",ID);

    memcpy(&(process_var[bus_id][Rx][ID].data), &m->data, (*m).len);
    process_var[bus_id][Rx][ID].count = (*m).len;
    process_var[bus_id][Rx][ID].state = ~TS_WAIT_SERVER;
    return 0;

    return -1;
}

int ProceedNODE_GUARD(int bus_id, Message *m,const proceed_info *p_i, int dummy)
{
    int ID = GET_NODE_ID((*m));

    MSG("ProceedNODE_GUARD\n");

    NMTable[bus_id][ID] = (*m).data[0] | 0x7f;
    return 0;
}


int WriteProcessVar(int when, int bus_id, int ID, unsigned int count, char *data)
{
    process_var[bus_id][Tx][ID].count = count;
    memcpy(&process_var[bus_id][Tx][ID].data, data, count);
    process_var[bus_id][Tx][ID].state = TS_DOWNLOAD & ~TS_WAIT_SERVER;
    if(when==NOW)
        return Process_MGR(bus_id,ID);
    return 0;
}

int DownloadProcessVars(int bus_id)
{
    int i;
    for(i=0; i<PDO_MAX_NODE_ID; i++)
        Process_MGR(bus_id,i);
    return 0;
}



int ReadProcessVar(int bus_id, int ID, char *data)
{
    if(process_var[bus_id][Rx][ID].state == ~TS_WAIT_SERVER){
        memcpy(data, &process_var[bus_id][Rx][ID].data, process_var[bus_id][Rx][ID].count);
        process_var[bus_id][Rx][ID].state |= TS_WAIT_SERVER;
        return process_var[bus_id][Rx][ID].count;
    }
    return -1;
}


int WriteDictionaryEntry(int bus_id, int ID, unsigned short index, char subindex, unsigned int count, void *data)
{
    transfers[bus_id][ID].index = index;
    transfers[bus_id][ID].subindex = subindex;
    transfers[bus_id][ID].count = count;
    memcpy(&transfers[bus_id][ID].data, data, count);
    transfers[bus_id][ID].state = TS_DOWNLOAD;
    Flux_MGR(bus_id, ID);
    while(TS_IS_ON(transfers[bus_id][ID].state) && !Message_Handler(bus_id));
    return (TS_IS_ON(transfers[bus_id][ID].state));
}

int ReadDictionaryEntry(int bus_id, int ID, unsigned short index, char subindex, char *data)
{
    transfers[bus_id][ID].index = index;
    transfers[bus_id][ID].subindex = subindex;
    transfers[bus_id][ID].count = 0;
    transfers[bus_id][ID].state = TS_UPLOAD;
    Flux_MGR(bus_id, ID);
    // warten bis antwort erhalten wurde...
    while(TS_IS_ON(transfers[bus_id][ID].state)&& !Message_Handler(bus_id));
    // empfangenen (angeforderte) daten kopieren
    memcpy(data, &transfers[bus_id][ID].data, transfers[bus_id][ID].count);
    return (TS_IS_ON(transfers[bus_id][ID].state));
}

int ReadNodeState(int bus_id, int ID)
{
    // FIXME: should warn for bad toggle bit.

    NMTable[bus_id][ID]=-1;
    Send_NODE_GUARD(bus_id,ID);
    while(NMTable[bus_id][ID]==-1){
        Message_Handler(bus_id);
    }
    return NMTable[bus_id][ID];
}


s_process_var getProcessVar( int busid, int dir, int pdoId )
{
    return process_var[busid][dir][pdoId];
}
