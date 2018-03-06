#pragma once

#include <memory>

namespace Dcdr::Worker
{
    class WorkerNode
    {
    public:
        WorkerNode();
        ~WorkerNode();

        void run();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}