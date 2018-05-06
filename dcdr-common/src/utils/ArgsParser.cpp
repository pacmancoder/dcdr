#include <dcdr/utils/ArgsParser.h>
#include <dcdr/Exception.h>

using namespace Dcdr::Utils;

ArgsParser::ArgsParser(int argc, char* argv[]) :
        args_(), abbr_()

{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if (arg.find("--") != 0 || i >= argc - 1)
        {
            throw Dcdr::DcdrException("Common", "ArgsParsing", "Wrong arguments format");
        }
        std::string option(argv[++i]);

        args_[arg.substr(2)] = option;
    }
}


const std::string& ArgsParser::get_argument(const std::string &arg, const std::string& defaultValue) const
{
    auto foundValue = args_.find(arg);
    if (foundValue == args_.cend())
    {
        return defaultValue;
    }

    return args_.at(arg);
}

