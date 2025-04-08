#pragma once

#include <Object_Constructor.h>

#include <Object.h>

#include <Window/Window_Controller.h>


namespace LGui
{

    class UI_Object_Stub : public LEti::Object_Stub
    {
    public:
        INIT_VARIABLE(LGui::UI_Object_Stub, LEti::Object_Stub)

        INIT_FIELDS
        ADD_FIELD(LDS::Vector<std::string>, tags)
        FIELDS_END

    public:
        LDS::Vector<std::string> tags;

    protected:
        INIT_BUILDER_STUB(LEti::Object)

    };

}
