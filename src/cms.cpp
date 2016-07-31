#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include "CLI.h"
#include "NetworkInput.h"
#include "MultiThreadInput.h"
#include "parser.h"
#include "utils.h"


const std::string header = "                                  \n"
        "  /$$$$$$$ /$$$$$$/$$$$   /$$$$$$$\n"
        " /$$_____/| $$_  $$_  $$ /$$_____/\n"
        "| $$      | $$ \\ $$ \\ $$|  $$$$$$ \n"
        "| $$      | $$ | $$ | $$ \\____  $$\n"
        "|  $$$$$$$| $$ | $$ | $$ /$$$$$$$/\n"
        " \\_______/|__/ |__/ |__/|_______/ \n";

const std::string welcomeMsg = "Welcome to Commodity Market System - CMS<GO>";

int main(int argc, char *argv[]) {
    try {
        boost::shared_ptr<cms::Input> input_ptr;
        std::cout << header << std::endl;
        std::cout << welcomeMsg << std::endl;
        if (argc == 2 && strcmp(argv[1], "base") == 0) {
            input_ptr = boost::shared_ptr<cms::Input>(new cms::CLI());
        } else if (argc == 3 && boost::equals(std::string(std::string(argv[1])), "ext1") && cms::isInteger(argv[2])) {
            input_ptr = boost::shared_ptr<cms::Input>(new cms::NetworkInput(cms::toInt(argv[2])));
        } else if (argc == 3 && boost::equals(std::string(std::string(argv[1])), "ext2") && cms::isInteger(argv[2])) {
            input_ptr = boost::shared_ptr<cms::Input>(new cms::MultiThreadInput(cms::toInt(argv[2])));
        } else {
            std::cout << "Usage: ./cms base|ext1|ext2 <portNo>" << std::endl;
            return 0;
        }
        input_ptr->run();
        return 0;
    } catch (const std::exception &e) {
        return -1;
    }
}