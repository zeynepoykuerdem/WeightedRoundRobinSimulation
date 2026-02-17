/*
 * Switch.cc
 *
 *  Created on: Feb 24, 2025
 *      Author: zeyne
 */




#include <omnetpp.h>

using namespace omnetpp;

class Switch : public cSimpleModule
{
private:
    int maxQueueSize;
    int numClients;
    double bandwithToServer;
    std::vector<cQueue*> queues;
    std:: vector<double> weights;
    cHistogram throughputsStats;
    cOutVector throughputsVector;




protected:
    virtual void initialize()override;
    virtual void handleMessage(cMessage *msg)override;
    void processQueues();
    virtual void finish() override;


};


void Switch::initialize(){
    numClients=par("numClients");
    maxQueueSize= par("maxQueueSize");
    bandwithToServer= par("bandwithToServer");

    queues.resize(numClients);
    weights.resize(numClients);

    weights[0] = par("weights0").doubleValue();
    weights[1] = par("weights1").doubleValue();
    weights[2] = par("weights2").doubleValue();
    weights[3] = par("weights3").doubleValue();

    for (int i=0;i<numClients;++i){
         queues[i] = new cQueue();
         queues[i]->setName(("Queue "+std::to_string(i)).c_str());
         EV << "Queue " << i << " has weight: " << weights[i] << "\n";


      }
    throughputsVector.setName("throughputsVector");
    throughputsStats.setName("throughputsStats");


}


void Switch :: handleMessage(cMessage *msg){
      int clientID=msg->getArrivalGate()->getIndex();
      if(clientID>=0 && clientID<numClients){
                  if( queues[clientID]->getLength()<maxQueueSize){
                      queues[clientID]->insert(msg);
                  }else {
                      delete msg;
                      EV<<"Queue"<<clientID<<"is full, dropped the packet.\n";
                  }


        processQueues();



        }

    }




void Switch:: processQueues (){
    double weightSum=0;

    for (double w: weights){
        weightSum+=w;
    }
    int numofCycles=5;
    for (int cycle=0; cycle<numofCycles;cycle++){
        EV << "Cycle " << cycle + 1 << " starts.\n";
        for (int i=0; i< numClients; i++){
               int numPacketToSendServer=(int)((weights[i]/weightSum)*bandwithToServer);
               EV<<"Client"<<i<<"must send "<<numPacketToSendServer<<"\n";

               // 20/100 * 100
               int packetsSent=0;
               while (!queues[i]->isEmpty() && packetsSent < numPacketToSendServer) {
                           send((cMessage*)queues[i]->pop(), "out");
                           packetsSent++;
                           EV << "Sending packet from Client " << i << " to server. Total sent: " << packetsSent << "\n";
                           throughputsVector.record(packetsSent);
                           throughputsStats.collect(packetsSent);


                       }

        }


    }









}
void Switch::finish() {
    for (int i = 0; i < numClients; ++i) {
        delete queues[i];
    }
    recordScalar("Total Throughput",throughputsStats.getMean());
    throughputsStats.recordAs("client Throughputs");
}


Define_Module(Switch);

