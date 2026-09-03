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

    Server::Server(const std::string& host, unsigned short port)
        : acceptor(io_context, tcp::endpoint(net::ip::make_address(host), port))
    {
    }
    Server::~Server()
    {
        Stop();
    }
    Server::start()
    {
        accept();
        io_context.run();
    }
    Server::stop()
    {
        io_context.stop();
    }
    Server::accept()
    {
        acceptor.async_accept(
            [this](beast::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    auto ws = std::make_shared<websocket::stream<tcp::socket>>(std::move(socket));
                    ws->async_accept(
                        [this, ws](beast::error_code ec)
                        {
                            if (!ec)
                            {
                                std::cout << "New WebSocket connection accepted\n";
                                // Handle the WebSocket connection here
                            }
                            else
                            {
                                std::cerr << "WebSocket accept error: " << ec.message() << "\n";
                            }
                        });
                }
                accept();
            });
    }

}