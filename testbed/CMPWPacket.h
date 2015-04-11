/* 
 * File:   CMPWPacket.h
 * Author: mayue
 *
 * Created on April 1, 2015, 11:04 PM
 */

#ifndef CMPWPACKET_H
#define	CMPWPACKET_H
struct packet{
    char src;
    char destination;
    char cmd;
    char seq;
    char quorum[16];
   
};
typedef packet PACKET;


#endif	/* CMPWPACKET_H */

