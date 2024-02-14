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
        DECLARE_VARIABLE;

    public:
        glm::vec3 intended_window_size;

        bool scale_horizontally = false;
        bool scale_vertically = false;

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
