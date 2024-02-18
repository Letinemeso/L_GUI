#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Module.h>

#include <Draw_Modules/Draw_Module.h>

#include <Modules/Physics_Module_2D.h>


namespace LGui
{

    class Data_Extraction_Module : public LEti::Module      //  this class may be pointless
    {
    public:
        INIT_VARIABLE(LGui::Data_Extraction_Module, LEti::Module)

    private:
        LR::Draw_Module* m_attached_draw_module = nullptr;
        LPhys::Physics_Module_2D* m_attached_physics_module = nullptr;

    public:
        Data_Extraction_Module();
        ~Data_Extraction_Module();

    public:
        inline void attach_draw_module(LR::Draw_Module* _ptr) { m_attached_draw_module = _ptr; }
        inline void attach_physics_module(LPhys::Physics_Module_2D* _ptr) { m_attached_physics_module = _ptr; }

    public:
        void update(float _dt) override { }

    };



    class Data_Extraction_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Data_Extraction_Module_Stub, LEti::Module_Stub)

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
