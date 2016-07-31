#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

#include "Command.h"
#include "parser.h"
#include "NetworkInput.h"

namespace cms {
    NetworkInput::NetworkInput(int port) try : endpoint(boost::asio::ip::tcp::v4(), port),
                                               acceptor(io_service, endpoint) { } catch (
            const boost::system::system_error &error) {
        std::cout << "Unable to start a TCP server. " << error.what() << std::endl;
    }

    void NetworkInput::newConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr) {
        std::string message("Type 'q' or 'quit' and then hit return to close the connection\n");
        boost::asio::write(*socket_ptr, boost::asio::buffer(message, message.size()));

        for (; ;) {
            char data[COMMAND_LIMIT + 2] = {};
            boost::system::error_code error;
            socket_ptr->read_some(boost::asio::buffer(data), error);
            std::string message(data);
            // Remove newline and crlf depending on client used
            if(boost::algorithm::ends_with(message, "\r\n")){
                message.erase(message.length()-2);
            }else if(boost::algorithm::ends_with(message, "\n")){
                message.erase(message.length()-1);
            }
            if (error == boost::asio::error::eof || boost::iequals(message, "q") ||
                boost::iequals(std::string(message), "quit"))
                break;
            else if (error)
                throw boost::system::system_error(error); // Some other error.
            std::string output = Input::commandExecute(message);
            boost::asio::write(*socket_ptr, boost::asio::buffer(output, output.size()));
        }
    }

    void NetworkInput::run() {
        try {
            boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr(new boost::asio::ip::tcp::socket(io_service));
            acceptor.accept(*socket_ptr);
            newConnection(socket_ptr);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}