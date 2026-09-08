#include "Server.hpp"

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

    /*

        Session
    
    */


    Session::Session(tcp::socket socket, std::uint64_t id)
        : ws(std::move(socket)),
        stream_id(id)
    {
    }
    void Session::start()
    {
        auto self = shared_from_this();

        ws.async_accept(
            [self](beast::error_code ec)
            {
                if (ec)
                {
                    std::cerr
                        << "WebSocket accept error: "
                        << ec.message()
                        << "\n";

                    return;
                }

                std::cout
                    << "Video stream connected. ID: "
                    << self->stream_id
                    << "\n";

                // Start receiving data
                self->read();
            });
    }
    void Session::read()
    {
        auto self = shared_from_this();

        ws.async_read(
            buffer,

            [self](beast::error_code ec,
                std::size_t bytes_transferred)
            {
                if (ec == websocket::error::closed)
                {
                    std::cout
                        << "Stream "
                        << self->stream_id
                        << " disconnected\n";

                    return;
                }

                if (ec)
                {
                    std::cerr
                        << "Read error: "
                        << ec.message()
                        << "\n";

                    return;
                }


                // Make sure client sent binary data
                if (!self->ws.got_binary())
                {
                    std::cerr
                        << "Stream "
                        << self->stream_id
                        << " sent non-binary data\n";

                    self->buffer.consume(bytes_transferred);

                    self->read();
                    return;
                }


                // Copy binary WebSocket message
                std::vector<std::uint8_t> data(bytes_transferred);

                net::buffer_copy(
                    net::buffer(data),
                    self->buffer.data()
                );

                self->buffer.consume(bytes_transferred);


                // Send data toward video/ML pipeline
                self->handle_video_chunk(std::move(data));


                // IMPORTANT:
                // start waiting for next chunk
                self->read();
            });
    }


    void Session::handle_video_chunk(
        std::vector<std::uint8_t> data)
    {
        std::cout
            << "Stream "
            << stream_id
            << " received "
            << data.size()
            << " bytes\n";


        // DON'T run heavy ML here.
        //
        // Later:
        //
        // ml_queue.push({
        //     stream_id,
        //     std::move(data)
        // });
    }

    /*

        Server
    
    */



    Server::Server(const std::string& host, unsigned short port)
        : acceptor(io_context, tcp::endpoint(net::ip::make_address(host), port))
    {
    }
    void Server::start()
    {
        accept();
        std::cout << "Server started on " << acceptor.local_endpoint() << std::endl;
        io_context.run();
    }
    void Server::stop()
    {
        io_context.stop();
    }
    void Server::accept()
    {
        acceptor.async_accept(
            [this](beast::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    auto id = next_stream_id.fetch_add(1);
                    auto ws = std::make_shared<Session>(std::move(socket), id);
                    std::cout << "New connection accepted. Stream ID: " << id << std::endl;
                    ws->start();
                }
                else{
                    
                    std::cerr
                        << "Accept error: "
                        << ec.message()
                        << "\n";
                }
                accept();
            });
    }

}