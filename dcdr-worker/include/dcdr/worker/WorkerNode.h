#pragma once

#include <memory>
#include <dcdr/utils/ArgsParser.h>

namespace Dcdr::Worker
{
    class WorkerNode
    {
    public:
        WorkerNode(const Utils::ArgsParser& args);
        ~WorkerNode();

        void run();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}