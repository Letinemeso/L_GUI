#include <UI_Object_Stub.h>

using namespace LGui;


INIT_FIELDS(LGui::UI_Object_Stub, LEti::Object_Stub)

ADD_FIELD(std::string*, tags)
ADD_FIELD(unsigned int, tags_amount)

ADD_CHILD("draw_module_stub", draw_module_stub)
ADD_CHILD("physics_module_stub", physics_module_stub)
ADD_CHILD("data_extractor_stub", data_extractor_stub)

FIELDS_END


UI_Object_Stub::UI_Object_Stub()
{

}

UI_Object_Stub::~UI_Object_Stub()
{
    delete[] tags;

    delete draw_module_stub;
    delete physics_module_stub;
    delete data_extractor_stub;
}



LV::Variable_Base* UI_Object_Stub::M_construct_product() const
{
    return new LEti::Object;
}

void UI_Object_Stub::M_init_constructed_product(LV::Variable_Base *_product) const
{
    LEti::Object_Stub::M_init_constructed_product(_product);

    LEti::Object* product = (LEti::Object*)_product;

    LR::Draw_Module_Base* dm = nullptr;
    LPhys::Physics_Module_2D* pm = nullptr;
    Data_Extraction_Module* extractor = nullptr;

    if(data_extractor_stub)
    {
        extractor = (Data_Extraction_Module*)data_extractor_stub->construct();
        product->add_module(extractor);
    }

    if(draw_module_stub)
    {
        dm = (LR::Draw_Module_Base*)draw_module_stub->construct();
        product->add_module(dm);

        if(extractor)
            extractor->attach_draw_module(dm);
    }

    if(physics_module_stub)
    {
        pm = (LPhys::Physics_Module_2D*)physics_module_stub->construct();
        product->add_module(pm);

        if(extractor)
            extractor->attach_physics_module(pm);
    }
}
