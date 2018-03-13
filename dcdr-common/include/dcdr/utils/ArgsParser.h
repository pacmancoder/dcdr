#pragma once

#include <map>
#include <string>

namespace Dcdr::Utils
{
    class ArgsParser
    {
    public:
        ArgsParser(int argc, char* argv[]);

        const std::string& get_argument(const std::string& arg) const;

    private:
        std::map<std::string, std::string> args_;
        std::map<std::string, std::string> abbr_;
    };
}