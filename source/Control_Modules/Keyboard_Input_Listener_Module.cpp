#include <Control_Modules/Keyboard_Input_Listener_Module.h>
#include <Object.h>

using namespace LGui;


Keyboard_Input_Listener_Module::Keyboard_Input_Listener_Module()
{

}

Keyboard_Input_Listener_Module::~Keyboard_Input_Listener_Module()
{
    delete m_keys_to_listen;
}



void Keyboard_Input_Listener_Module::update(float)
{
    for(unsigned int i=0; i<m_keys_to_listen_amount; ++i)
    {
        if(!LR::Window_Controller::key_was_pressed(m_keys_to_listen[i]))
            continue;

        m_on_key_pressed_action(parent_object()->current_state().position(), this);
        return;
    }
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Keyboard_Input_Listener_Module_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Keyboard_Input_Listener_Module_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    L_ASSERT(keys_to_listen);
    L_ASSERT(keys_to_listen_amount > 0);
    L_ASSERT(on_key_press_action_name.size() > 0);
    L_ASSERT(action_controller);

    product->set_on_key_pressed_action(action_controller->get_action(on_key_press_action_name));
    product->set_keys_to_listen(keys_to_listen, keys_to_listen_amount);
}
