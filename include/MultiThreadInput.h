#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "NetworkInput.h"

namespace cms {
    class MultiThreadInput : public NetworkInput {

    private:
        boost::mutex mtx;
        bool firstConnection;
        unsigned int clientsNo;
        void clientConnect();
        void clientDisconnect();
        bool running();
        void newConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr);
        void handleThread();

    public:
        MultiThreadInput(int port);
        void run();
    };
}