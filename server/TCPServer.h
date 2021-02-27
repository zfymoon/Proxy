//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_TCPSERVER_H
#define ZHUQUE_TCPSERVER_H
#include <boost/asio.hpp>
#include <string>
#include "../base/Log.h"


using namespace boost::asio::ip;
using namespace boost::asio;

template<typename T>
class TCPServer: public std::enable_shared_from_this<TCPServer<T>> {
private:
    const std::string TAG{"TCPServer"};
    io_context _ioContext;
    std::unique_ptr<io_context::work> _workPtr;
    int _port;
public:
    explicit TCPServer(int port):_port(port),_ioContext(){
        _workPtr = std::make_unique<io_context::work>(_ioContext);

    }
    void start(){
        Log::e(TAG,"start TCPServer");
        auto acceptor = std::make_shared<tcp::acceptor>(_ioContext,tcp::endpoint(tcp::v4(),_port));
        onReceive(acceptor);
        _ioContext.run();
    }
    void onReceive(const std::shared_ptr<tcp::acceptor>& acceptor){
        auto self = this->shared_from_this();
        acceptor->async_accept([self,acceptor](boost::system::error_code code,tcp::socket socket){
            auto handler = std::make_shared<T>(std::move(socket));
            handler->start();
            self->onReceive(acceptor);
        });
    }
    void stop(){
        _workPtr.reset();
    }

};


#endif //ZHUQUE_TCPSERVER_H
