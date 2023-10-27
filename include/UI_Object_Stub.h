#ifndef UI_OBJECT_STUB_H
#define UI_OBJECT_STUB_H

#include <Object_Constructor.h>

#include <Object_System/Object_2D.h>

#include <Draw_Modules/Draw_Module_Base.h>
#include <Modules/Physics_Module_2D.h>

namespace LGui
{

    class UI_Object_Stub : public LEti::Object_2D_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        LR::Draw_Module_Base_Stub* draw_module_stub = nullptr;
        LPhys::Physics_Module_2D_Stub* physics_module_stub = nullptr;

    public:
        UI_Object_Stub();
        ~UI_Object_Stub();

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* _product) const override;

    };

}

#endif // UI_OBJECT_STUB_H
