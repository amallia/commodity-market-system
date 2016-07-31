#pragma once

#include <boost/asio.hpp>

#include "Input.h"

namespace cms {
    class NetworkInput : public Input {
        friend class MultiThreadInput;

    private:
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::endpoint endpoint;
        boost::asio::ip::tcp::acceptor acceptor;

        void newConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr);

    public:
        NetworkInput(int port);

        void run();

    };
}