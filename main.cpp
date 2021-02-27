#include <iostream>
#include "server/TCPServer.h"
#include "server/SessionHandler.h"
#include "client/TCPClient.h"
#include "client/ClientProtocol.h"
#include "server/ServerProtocol.h"
using namespace boost::asio;
int main() {



    std::thread serverThread([](){
        auto server = std::make_shared<TCPServer<SessionHandler<ServerProtocol>>>(9981);

        server->start();
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread clientThread([](){
        auto client = std::make_shared<TCPClient<ClientProtocol>>("127.0.0.1",9981);
        client->connect();

    });

    clientThread.join();
    serverThread.join();






    return 0;
}
