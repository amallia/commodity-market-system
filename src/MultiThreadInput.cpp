#include <boost/thread/lock_guard.hpp>
#include <boost/thread/thread.hpp>

#include "MultiThreadInput.h"
#include "Command.h"

namespace cms {

    MultiThreadInput::MultiThreadInput(int port) : NetworkInput(port), firstConnection(true),clientsNo(0) { }

    void MultiThreadInput::clientConnect() {
        boost::lock_guard<boost::mutex> guard(mtx);
        firstConnection = false;
        clientsNo++;
    }

    void MultiThreadInput::clientDisconnect() {
        boost::lock_guard<boost::mutex> guard(mtx);
        clientsNo--;
    }

    bool MultiThreadInput::running() {
        boost::lock_guard<boost::mutex> guard(mtx);
        return (firstConnection || clientsNo != 0);
    }

    void MultiThreadInput::newConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr) {
        NetworkInput::newConnection(socket_ptr);
        clientDisconnect();
    }

    void MultiThreadInput::handleThread() {
        try {
            while (true) {
                boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr(new boost::asio::ip::tcp::socket(io_service));
                acceptor.accept(*socket_ptr);
                clientConnect();
                boost::thread thread(boost::bind(&MultiThreadInput::newConnection, this, socket_ptr));
            }
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void MultiThreadInput::run() {
        boost::thread thread(boost::bind(&MultiThreadInput::handleThread,this));
        while (running());
    }
}