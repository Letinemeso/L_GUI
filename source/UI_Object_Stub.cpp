#include <UI_Object_Stub.h>

using namespace LGui;


INIT_FIELDS(LGui::UI_Object_Stub, LEti::Object_2D_Stub)

ADD_CHILD("draw_module_stub", draw_module_stub)
ADD_CHILD("physics_module_stub", physics_module_stub)

FIELDS_END


UI_Object_Stub::UI_Object_Stub()
{

}

UI_Object_Stub::~UI_Object_Stub()
{
    delete draw_module_stub;
    delete physics_module_stub;
}



LV::Variable_Base* UI_Object_Stub::M_construct_product() const
{
    return new LEti::Object_2D;
}

void UI_Object_Stub::M_init_constructed_product(LV::Variable_Base *_product) const
{
    LEti::Object_2D_Stub::M_init_constructed_product(_product);

    LEti::Object_2D* product = (LEti::Object_2D*)_product;

    LR::Draw_Module_Base* dm = (LR::Draw_Module_Base*)draw_module_stub->construct();

    LPhys::Physics_Module_2D* pm = (LPhys::Physics_Module_2D*)physics_module_stub->construct();

    product->add_module(pm);
    product->add_module(dm);
}
