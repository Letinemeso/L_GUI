#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Module.h>

#include <Draw_Modules/Default_Draw_Module.h>

#include <Modules/Physics_Module_2D.h>

#include <Extracted_Data.h>


namespace LGui
{

    class Data_Extraction_Module : public LEti::Module
    {
    public:
        DECLARE_VARIABLE;

    public:
        using Extraction_Function_Type = LST::Function<void(Extracted_Data&)>;
        using Update_Logic_Function = LST::Function<void(const Extraction_Function_Type&)>;

    private:
        Extraction_Function_Type m_data_extraction_func;
        Update_Logic_Function m_update_logic_func;

    public:
        Data_Extraction_Module();
        ~Data_Extraction_Module();

    private:
        LR::Draw_Module_Base* m_attached_draw_module = nullptr;
        LPhys::Physics_Module_2D* m_attached_physics_module = nullptr;

    public:
        inline void attach_draw_module(LR::Draw_Module_Base* _ptr) { m_attached_draw_module = _ptr; }
        inline void attach_physics_module(LPhys::Physics_Module_2D* _ptr) { m_attached_physics_module = _ptr; }

        inline void set_data_extraction_func(const Extraction_Function_Type& _data_extraction_func) { m_data_extraction_func = _data_extraction_func; }
        inline void set_update_logic_func(const Update_Logic_Function& _update_logic_func) { m_update_logic_func = _update_logic_func; }

    public:
        void update(float _dt) override;

    };



    class Data_Extraction_Module_Stub : public LV::Builder_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        Data_Extraction_Module::Extraction_Function_Type data_extraction_func;
        Data_Extraction_Module::Update_Logic_Function update_logic_func;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}
