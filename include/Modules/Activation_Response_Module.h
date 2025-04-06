#pragma once

#include <Module.h>


namespace LGui
{

    class Activation_Response_Module : public LEti::Module
    {
    public:
        INIT_VARIABLE(LGui::Activation_Response_Module, LEti::Module)

    public:
        virtual void on_hovered() { }
        virtual void on_pressed() { }
        virtual void on_released() { }

    };


    class Activation_Response_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Activation_Response_Module_Stub, LEti::Module_Stub)

    public:
        INIT_BUILDER_STUB(Activation_Response_Module)

    };

}
