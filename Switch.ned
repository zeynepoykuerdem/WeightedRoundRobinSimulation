simple Switch
{
    parameters:
        @display("i=block/switch;q=queue");
        int numClients;
        double bandwithToServer;
        int maxQueueSize;
        double weights0;
        double weights1;
        double weights2;
        double weights3;
        
    gates:
        input in[numClients];
        output out;
    
}
