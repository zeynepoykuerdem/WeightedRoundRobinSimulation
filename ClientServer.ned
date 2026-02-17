network ClientServer
{

    submodules:
        server: Server {
            parameters:
                @display("p=322,118");
        }
        switch: Switch {
            parameters:
                @display("p=234,41");
        }
        client[4]: Client {
            parameters:
                @display("p=84,41");
        }

    connections:
        // ned dosyalarinda c/c++ for dongusunu kullanilmazmis
        client[0].out -->  switch.in[0];
        client[1].out -->  switch.in[1];
        client[2].out -->  switch.in [2];
        client [3].out --> switch.in [3];
        switch.out -->  server.in;
        


}
