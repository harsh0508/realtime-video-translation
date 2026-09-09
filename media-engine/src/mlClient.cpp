#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>
#include "mlClient.hpp"



MLClient::MLClient(boost::asio::io_context& io_context)
            : socket(io_context){
                socket.connect(stp::endpoint(this->socket_path));
}