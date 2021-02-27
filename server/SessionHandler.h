//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_SESSIONHANDLER_H
#define ZHUQUE_SESSIONHANDLER_H
#include <boost/asio.hpp>
#include "../base/Log.h"
using namespace boost::asio::ip;
using namespace boost::asio;


const int READ_BUFFER_SIZE = 1024 * 4;
template <typename T>
class SessionHandler:public std::enable_shared_from_this<SessionHandler<T>> {
private:
    const std::string TAG{"SessionHandler"};
    std::shared_ptr<tcp::socket> _socket;
    std::array<std::byte,READ_BUFFER_SIZE> _readBuffer{};
    std::shared_ptr<T> _protocolHandler;
public:
    explicit SessionHandler(tcp::socket socket):
        _socket(std::make_shared<tcp::socket>(std::move(socket))),
        _protocolHandler(std::make_shared<T>(_socket)){
        Log::d(TAG,"session start");

    }
    void start(){
        auto self = this->shared_from_this();
        _protocolHandler->onReady();
    }
};


#endif //ZHUQUE_SESSIONHANDLER_H
