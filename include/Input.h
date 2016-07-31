#pragma once

namespace cms {
    class Input {
    protected:
       static std::string commandExecute(const std::string& s);

    public:
        virtual void run() = 0;
    };
}