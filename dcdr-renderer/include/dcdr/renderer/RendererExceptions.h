#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Renderer
{
    class RendererException : public DcdrException
    {
    public:
        RendererException(const std::string& sender, const std::string& message) :
                DcdrException("Renderer", sender, message) {}
    };


    class SceneException : public RendererException
    {
    public:
        explicit SceneException(const std::string& message) :
                RendererException("Scene", message) {}
    };

}