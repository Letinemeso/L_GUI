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
        ADD_FIELD(glm::vec3, intended_window_size)
        ADD_FIELD(std::string, scale_type)
        ADD_FIELD(glm::vec3, offset)
        ADD_FIELD(bool, scale_offset_horizontally)
        ADD_FIELD(bool, scale_offset_vertically)
        ADD_FIELD(LDS::Vector<std::string>, tags)
        FIELDS_END

    public:
        glm::vec3 intended_window_size;

        std::string scale_type = "none";     //  can be "horizontal", "vertical", "both", "proportional"

        glm::vec3 offset{0.0f, 0.0f, 0.0f};
        bool scale_offset_horizontally = false;
        bool scale_offset_vertically = false;

    public:
        LDS::Vector<std::string> tags;

    public:
        UI_Object_Stub();
        ~UI_Object_Stub();

    private:
        void M_apply_window_scaling(LEti::Object* _product) const;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
