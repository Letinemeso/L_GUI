#include <Modules/Autoscale_Module.h>

#include <Object.h>

using namespace LGui;


Autoscale_Module::Autoscale_Module()
{
    m_subscription_handle = LST::Message_Translator::instance().subscribe<LR::Message__Window_Resized>([this](LR::Message__Window_Resized&)
    {
        rescale();
    });
}

Autoscale_Module::~Autoscale_Module()
{
    LST::Message_Translator::instance().unsubscribe(m_subscription_handle);
}



glm::vec3 Autoscale_Module::M_calculate_scale(Scale_Type _scale_type) const
{
    glm::vec2 window_ratio = LR::Window_Controller::instance().get_window_size() / m_intended_window_size;
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

    if(_scale_type == Scale_Type::Horizontal)
    {
        scale.x = window_ratio.x;
    }
    else if(_scale_type == Scale_Type::Vertical)
    {
        scale.y = window_ratio.y;
    }
    else if(_scale_type == Scale_Type::Both)
    {
        scale.x = window_ratio.x;
        scale.y = window_ratio.y;
    }
    else if(_scale_type == Scale_Type::Proportional)
    {
        float multiplier = window_ratio.x;
        if(window_ratio.y < multiplier)
            multiplier = window_ratio.y;
        scale.x = multiplier;
        scale.y = multiplier;
    }

    return scale;
}



void Autoscale_Module::rescale()
{
    if(m_intended_window_size.x < 0.000001f && m_intended_window_size.y < 0.000001f)
        return;

    L_ASSERT(transformation_data());

    glm::vec2 scaled_offset = m_offset * glm::vec2(M_calculate_scale(m_offset_scale_type));

    if(scaled_offset.x < 0.0f)
        scaled_offset.x += LR::Window_Controller::instance().get_window_size().x;
    if(scaled_offset.y < 0.0f)
        scaled_offset.y += LR::Window_Controller::instance().get_window_size().y;

    transformation_data()->set_position({ scaled_offset, 0.0f });

    glm::vec3 scale = M_calculate_scale(m_scale_type);

    transformation_data()->set_scale(scale);

    parent_object()->update(0.0f);
    parent_object()->update_previous_state();
}



void Autoscale_Module::M_on_parent_object_set()
{
    Parent_Type::M_on_parent_object_set();
    rescale();
}



void Autoscale_Module::update(float _dt)
{

}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Autoscale_Module_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Autoscale_Module_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_intended_window_size(intended_window_size);
    product->set_offset(offset);
    product->set_offset_scale_type(M_parse_scale_type(offset_scale_type));
    product->set_scale_type(M_parse_scale_type(scale_type));
}



Autoscale_Module::Scale_Type Autoscale_Module_Stub::M_parse_scale_type(const std::string& _str) const
{
    if(_str == "None")
        return Autoscale_Module::Scale_Type::None;
    else if(_str == "Horizontal")
        return Autoscale_Module::Scale_Type::Horizontal;
    else if(_str == "Vertical")
        return Autoscale_Module::Scale_Type::Vertical;
    else if(_str == "Both")
        return Autoscale_Module::Scale_Type::Both;
    else if(_str == "Proportional")
        return Autoscale_Module::Scale_Type::Proportional;

    L_ASSERT(false);
    return Autoscale_Module::Scale_Type::None;
}
