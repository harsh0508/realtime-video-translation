#pragma once


#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <set>
#include <shared_mutex>
#include <string>
#include <thread>


namespace socketServer{


    namespace net = boost::asio;            
    namespace beast = boost::beast;         
    namespace websocket = boost::beast::websocket; 
    using tcp = net::ip::tcp;           

    struct Server{

        net::io_context io_context;
        tcp::acceptor acceptor;

        Server(const std::string& host, unsigned short port)
            : acceptor(io_context, tcp::endpoint(net::ip::make_address(host), port))
        {}

        void Start(){}
        void Stop(){}


        private:
            void accept(){
                acceptor.async_accept(
                    [this](beast::error_code ec, tcp::socket socket){
                        if(!ec){
                            auto ws = std::make_shared<websocket::stream<tcp::socket>>(std::move(socket));
                            ws->async_accept(
                                [this, ws](beast::error_code ec){
                                    if(!ec){
                                        std::cout << "New WebSocket connection accepted\n";
                                        // Handle the WebSocket connection here
                                    } else {
                                        std::cerr << "WebSocket accept error: " << ec.message() << "\n";
                                    }
                                }
                            );
                        }
                        accept();
                    }
                );
            }
    }; 
    

}

