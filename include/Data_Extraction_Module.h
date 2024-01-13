#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Module.h>

#include <Draw_Modules/Default_Draw_Module.h>

#include <Modules/Physics_Module_2D.h>


namespace LGui
{

    class Data_Extraction_Module : public LEti::Module      //  this class may be pointless
    {
    public:
        DECLARE_VARIABLE;

    private:
        LR::Draw_Module_Base* m_attached_draw_module = nullptr;
        LPhys::Physics_Module_2D* m_attached_physics_module = nullptr;

    public:
        Data_Extraction_Module();
        ~Data_Extraction_Module();

    public:
        inline void attach_draw_module(LR::Draw_Module_Base* _ptr) { m_attached_draw_module = _ptr; }
        inline void attach_physics_module(LPhys::Physics_Module_2D* _ptr) { m_attached_physics_module = _ptr; }

    };



    class Data_Extraction_Module_Stub : public LEti::Module_Stub
    {
    public:
        DECLARE_VARIABLE;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
