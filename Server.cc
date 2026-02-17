/*
 * Server.cc
 *
 *  Created on: Mar 13, 2025
 *      Author: zeyne
 */


#include <omnetpp.h>

using namespace omnetpp;

class Server : public cSimpleModule
{
protected:
    virtual void handleMessage(cMessage *msg) override;
};



void Server::handleMessage(cMessage *msg)
{
EV<<"Received Packet: "<<msg->getName()<<"\n";
delete msg;
}



Define_Module(Server);
