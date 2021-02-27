//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_SERVERPROTOCOL_H
#define ZHUQUE_SERVERPROTOCOL_H
#include "../base/Protocol.h"

#include <utility>

class ServerProtocol: public ProtocolHandler{
private:
    std::string TAG{"ServerProtocol"};
public:
    ServerProtocol(std::shared_ptr<tcp::socket> s):ProtocolHandler(s){

    }
    void onReceiveData(std::vector<std::byte> data) override{
        std::vector<char> list;
        for(auto & item:data){
            list.push_back((char)item);
        }
        std::string receiveMessage(list.cbegin(),list.cend());
        Log::d(TAG,"onReceive "+receiveMessage);
        sendData("I am server.");
    }
};


#endif //ZHUQUE_SERVERPROTOCOL_H
