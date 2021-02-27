//
// Created by Zmoon on 2021/2/26.
//

#ifndef ZHUQUE_PROTOCOL_H
#define ZHUQUE_PROTOCOL_H

#include <string>
#include "Log.h"
#include <boost/asio.hpp>

using namespace boost::asio::ip;
/**
 * 协议解析器
 */
class ProtocolHandler:public std::enable_shared_from_this<ProtocolHandler>{
public:
    std::array<std::byte,CLIENT_READ_BUFFER_SIZE> _readBuffer{};
    std::shared_ptr<tcp::socket> socketPtr;
    explicit ProtocolHandler(std::shared_ptr<tcp::socket> s):socketPtr(std::move(s)){

    }
    virtual void onReady(){
        receive();
    }
    void receive(){
        auto self = this->shared_from_this();
        socketPtr->async_read_some(
                buffer(_readBuffer,_readBuffer.size()),
                [self](boost::system::error_code code,size_t readSize){
                    self->onReceiveData(
                            std::move(
                                    std::vector<std::byte>(
                                            self->_readBuffer.begin(),
                                            self->_readBuffer.begin()+readSize)));
                    self->receive();
                });
    }
    virtual void onReceiveData(std::vector<std::byte> data) = 0;
    void sendData(const std::string &data){
        socketPtr->write_some(boost::asio::buffer(data));
    }
};


#endif //ZHUQUE_PROTOCOL_H
