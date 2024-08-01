#pragma once

#include <Module.h>

#include <Window/Window_Controller.h>

#include <Actions_Controller.h>


namespace LGui
{

    class Keyboard_Input_Listener_Module : public LEti::Module
    {
    public:
        INIT_VARIABLE(LGui::Keyboard_Input_Listener_Module, LEti::Module);

    private:
        unsigned int m_keys_to_listen_amount = 0;
        unsigned int* m_keys_to_listen = nullptr;

        Action m_on_key_pressed_action;

    public:
        Keyboard_Input_Listener_Module();
        ~Keyboard_Input_Listener_Module();

    public:
        inline void set_on_key_pressed_action(const Action& _action) { m_on_key_pressed_action = _action; }
        inline void set_keys_to_listen(unsigned int* _keys, unsigned int _amount) { delete m_keys_to_listen; m_keys_to_listen = _keys; m_keys_to_listen_amount = _amount; }

    public:
        void update(float) override;

    };


    class Keyboard_Input_Listener_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Keyboard_Input_Listener_Module_Stub, LEti::Module_Stub);

        INIT_FIELDS
        ADD_FIELD(std::string, on_key_press_action_name)
        ADD_FIELD(unsigned int*, keys_to_listen)
        ADD_FIELD(unsigned int, keys_to_listen_amount)
        FIELDS_END

    public:
        const Actions_Controller* action_controller = nullptr;

    public:
        std::string on_key_press_action_name;
        unsigned int* keys_to_listen = nullptr;
        unsigned int keys_to_listen_amount = 0;

    public:
        INIT_BUILDER_STUB(Keyboard_Input_Listener_Module);

    };

}
