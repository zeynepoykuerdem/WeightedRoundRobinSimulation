/*
 * Client.cc
 *
 *  Created on: Feb 24, 2025
 *      Author: zeyne
 */


#include <omnetpp.h>

using namespace omnetpp;

class Client : public cSimpleModule
{
private:
    cMessage *sendPacketEvent;
    double lambda;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};



void Client::initialize()
{
    sendPacketEvent= new cMessage("sendPacket");
    lambda=par(lambda).doubleValue();
    /**
     * clients sending fixed size packets following the poisson distribution
     */

     scheduleAt(simTime()+exponential(lambda),sendPacketEvent);
}

void Client:: handleMessage(cMessage *msg){
    send(msg,"out");
}



Define_Module(Client);
