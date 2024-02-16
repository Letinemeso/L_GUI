#pragma once

#include <Object_Constructor.h>

#include <Object.h>

#include <Window/Window_Controller.h>
#include <Draw_Modules/Draw_Module_Base.h>
#include <Modules/Physics_Module_2D.h>

#include <Data_Extraction_Module.h>


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
        ADD_FIELD(std::string*, tags)
        ADD_FIELD(unsigned int, tags_amount)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("draw_module_stub", draw_module_stub)
        ADD_CHILD("physics_module_stub", physics_module_stub)
        ADD_CHILD("data_extractor_stub", data_extractor_stub)
        CHILDS_END


    public:
        glm::vec3 intended_window_size;

        std::string scale_type = "none";     //  can be "horizontal", "vertical", "both", "proportional"

        glm::vec3 offset{0.0f, 0.0f, 0.0f};
        bool scale_offset_horizontally = false;
        bool scale_offset_vertically = false;

    public:
        std::string* tags = nullptr;
        unsigned int tags_amount = 0;

    public:
        LR::Draw_Module_Stub* draw_module_stub = nullptr;
        LPhys::Physics_Module_2D_Stub* physics_module_stub = nullptr;
        Data_Extraction_Module_Stub* data_extractor_stub = nullptr;

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
