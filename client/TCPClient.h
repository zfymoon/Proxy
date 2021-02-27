//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_TCPCLIENT_H
#define ZHUQUE_TCPCLIENT_H
#include <boost/asio.hpp>
#include <utility>
#include "../base/Log.h"
using namespace boost::asio::ip;
using namespace boost::asio;

const int CLIENT_READ_BUFFER_SIZE = 1024 * 4;
template <typename T>
class TCPClient:public std::enable_shared_from_this<TCPClient<T>> {
private:
    const std::string TAG{"TCPClient"};
    io_context _ioContext;
    std::shared_ptr<tcp::socket> _socket;
    std::string _addr;
    int _port;
    std::shared_ptr<T> _protocolHandler;
    std::array<std::byte,CLIENT_READ_BUFFER_SIZE> _readBuffer{};
public:
    TCPClient(std::string addr,int port):
        _socket(std::make_shared<tcp::socket>(_ioContext)),
        _addr(std::move(addr)),
        _port(port),
        _protocolHandler(std::make_shared<T>(_socket)){
    }
    void connect(){
        auto self = this->shared_from_this();
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_addr),_port);
        _socket->async_connect(endpoint,[=](boost::system::error_code code){
            Log::e(TAG,"connect");
        });
        _protocolHandler->onReady();
    }
};


#endif //ZHUQUE_TCPCLIENT_H
