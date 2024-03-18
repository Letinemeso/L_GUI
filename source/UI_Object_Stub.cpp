#include <UI_Object_Stub.h>

using namespace LGui;


UI_Object_Stub::UI_Object_Stub()
{

}

UI_Object_Stub::~UI_Object_Stub()
{
    delete[] tags;
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

    if(scale_type == "horizontal")
    {
        scale.x *= window_ratio.x;
    }
    else if(scale_type == "vertical")
    {
        scale.y *= window_ratio.y;
    }
    else if(scale_type == "both")
    {
        scale.x *= window_ratio.x;
        scale.y *= window_ratio.y;
    }
    else if(scale_type == "proportional")
    {
        float multiplier = window_ratio.x;
        if(window_ratio.y < multiplier)
            multiplier = window_ratio.y;
        scale.x *= multiplier;
        scale.y *= multiplier;
    }
    else
    {
        L_ASSERT(scale_type == "none");    //  unknown scale type!
    }

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
}
