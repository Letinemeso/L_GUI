#include <UI_Object_Stub.h>

using namespace LGui;


INIT_FIELDS(LGui::UI_Object_Stub, LEti::Object_Stub)

ADD_FIELD(glm::vec3, intended_window_size)

ADD_FIELD(bool, scale_horizontally)
ADD_FIELD(bool, scale_vertically)

ADD_FIELD(glm::vec3, offset)
ADD_FIELD(bool, scale_offset_horizontally)
ADD_FIELD(bool, scale_offset_vertically)

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



void UI_Object_Stub::M_apply_window_scaling(LEti::Object* _product) const
{
    if(intended_window_size.x < 0.000001f && intended_window_size.y < 0.000001f)
        return;

    glm::vec3 window_ratio = glm::vec3(LR::Window_Controller::get_window_data().width, LR::Window_Controller::get_window_data().height, 0.0f) / intended_window_size;

    glm::vec3 scaled_offset = offset;
    if(scale_offset_horizontally)
        scaled_offset.x *= window_ratio.x;
    if(scale_offset_vertically)
        scaled_offset.y *= window_ratio.y;

    if(scaled_offset.x < 0.0f)
        scaled_offset.x += LR::Window_Controller::get_window_data().width;
    if(scaled_offset.y < 0.0f)
        scaled_offset.y += LR::Window_Controller::get_window_data().height;

    _product->current_state().move(scaled_offset);

    glm::vec3 scale = _product->current_state().scale();

    if(scale_horizontally)
        scale.x *= window_ratio.x;
    if(scale_vertically)
        scale.y *= window_ratio.y;

    _product->current_state().set_scale(scale);
}



LV::Variable_Base* UI_Object_Stub::M_construct_product() const
{
    return new LEti::Object;
}

void UI_Object_Stub::M_init_constructed_product(LV::Variable_Base *_product) const
{
    LEti::Object_Stub::M_init_constructed_product(_product);

    LEti::Object* product = (LEti::Object*)_product;

    M_apply_window_scaling(product);

    LR::Draw_Module* dm = nullptr;
    LPhys::Physics_Module_2D* pm = nullptr;
    Data_Extraction_Module* extractor = nullptr;

    if(data_extractor_stub)
    {
        extractor = (Data_Extraction_Module*)data_extractor_stub->construct();
        product->add_module(extractor);
    }

    if(draw_module_stub)
    {
        dm = (LR::Draw_Module*)draw_module_stub->construct();
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

        pm->update(0.0f);
        pm->update_prev_state();
    }
}
