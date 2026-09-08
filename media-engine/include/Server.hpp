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
    
    class Session : public std::enable_shared_from_this<Session>
    {
    private:
        websocket::stream<tcp::socket> ws;
        beast::flat_buffer buffer;

        std::uint64_t stream_id;

        void read();

        void handle_video_chunk(std::vector<std::uint8_t> data);

    public:
        Session(tcp::socket socket, std::uint64_t id);

        void start();
    };


    struct Server{

        net::io_context io_context;
        tcp::acceptor acceptor;
        std::atomic<std::uint64_t> next_stream_id{1};


        Server(const std::string& host, unsigned short port);

        void start();
        void stop();


        private:
            void accept();
    };
}

