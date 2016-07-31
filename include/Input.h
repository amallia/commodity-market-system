#pragma once

namespace cms {
    class Input {
    protected:
       static std::string commandExecute(std::string s);

    public:
        virtual void run() = 0;
    };
}