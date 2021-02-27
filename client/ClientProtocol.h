//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_CLIENTPROTOCOL_H
#define ZHUQUE_CLIENTPROTOCOL_H
#include "../base/Protocol.h"

class ClientProtocol: public  ProtocolHandler{

private:
    std::string TAG{"ClientProtocol"};

public:
    ClientProtocol(std::shared_ptr<tcp::socket> s):ProtocolHandler(s){

    }
    void onReceiveData(std::vector<std::byte> data) override{
        std::vector<char> list;
        for(auto & item:data){
            list.push_back((char)item);
        }
        Log::d(TAG,"onReceive "+std::string(list.begin(),list.end()));
    }
    void onReady() override{

        sendData("Hello");



    }

};


#endif //ZHUQUE_CLIENTPROTOCOL_H
