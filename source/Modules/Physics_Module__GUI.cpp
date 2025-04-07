#include <Modules/Physics_Module__GUI.h>

#include <glfw3.h>

#include <Modules/Activation_Response_Module.h>

using namespace LGui;


void Physics_Module__GUI::notify_on_hovered(const glm::vec3& _where_exactly)
{
    m_is_hovered_on_current_frame = true;
    m_hovered_at = _where_exactly;
}

void Physics_Module__GUI::reset()
{
    m_is_hovered_on_current_frame = false;
    m_is_held = false;
}



void Physics_Module__GUI::M_process_input()
{
    if(m_is_hovered_on_current_frame)
        M_on_hovered();

    if(!m_is_held && m_is_hovered_on_current_frame && LR::Window_Controller::instance().mouse_button_was_pressed(GLFW_MOUSE_BUTTON_1))
    {
        m_is_held = true;

        M_on_pressed();
    }

    if(m_is_held && LR::Window_Controller::instance().mouse_button_was_released(GLFW_MOUSE_BUTTON_1))
    {
        m_is_held = false;

        if(m_is_hovered_on_current_frame)
            M_on_released();
    }
}

void Physics_Module__GUI::M_on_hovered()
{
    if(m_on_hover)
        m_on_hover(m_hovered_at, this);

    parent_object()->process_logic_for_modules_of_type<LGui::Activation_Response_Module>(
        [](Activation_Response_Module* _module)
        {
            _module->on_hovered();
        });
}

void Physics_Module__GUI::M_on_pressed()
{
    if(m_on_pressed)
        m_on_pressed(m_hovered_at, this);

    parent_object()->process_logic_for_modules_of_type<LGui::Activation_Response_Module>(
        [](Activation_Response_Module* _module)
        {
            _module->on_pressed();
        });
}

void Physics_Module__GUI::M_on_released()
{
    if(m_on_released)
        m_on_released(m_hovered_at, this);

    parent_object()->process_logic_for_modules_of_type<LGui::Activation_Response_Module>(
        [](Activation_Response_Module* _module)
        {
            _module->on_released();
        });
}



void Physics_Module__GUI::update(float _dt)
{
    LPhys::Physics_Module_2D::update(_dt);

    M_process_input();

    m_is_hovered_on_current_frame = false;
}





BUILDER_STUB_CONSTRUCTION_FUNC(Physics_Module_Stub__GUI) BUILDER_STUB_CONSTRUCTION_FUNC_DEFAULT_IMPL

BUILDER_STUB_INITIALIZATION_FUNC(Physics_Module_Stub__GUI)
{
    L_ASSERT(actions_controller);

    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    if(on_hover_action_name.size() > 0)
        product->set_on_hover_action(actions_controller->get_action(on_hover_action_name));
    if(on_pressed_action_name.size() > 0)
        product->set_on_pressed_action(actions_controller->get_action(on_pressed_action_name));
    if(on_released_action_name.size() > 0)
        product->set_on_released_action(actions_controller->get_action(on_released_action_name));
}
