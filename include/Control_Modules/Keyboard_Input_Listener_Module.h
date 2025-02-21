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

    public:
        using Keys_To_Listen_Vector = LDS::Vector<unsigned int>;

    private:
        Keys_To_Listen_Vector m_keys_to_listen;

        Action m_on_key_pressed_action;

        bool m_enabled = true;

    public:
        Keyboard_Input_Listener_Module();
        ~Keyboard_Input_Listener_Module();

    public:
        inline void set_on_key_pressed_action(const Action& _action) { m_on_key_pressed_action = _action; }
        inline void set_keys_to_listen(const Keys_To_Listen_Vector& _keys) { m_keys_to_listen = _keys; }
        inline void set_enabled(bool _value) { m_enabled = _value; }

        inline bool enabled() const { return m_enabled; }

    public:
        void update(float) override;

    };


    class Keyboard_Input_Listener_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Keyboard_Input_Listener_Module_Stub, LEti::Module_Stub);

        INIT_FIELDS
        ADD_FIELD(std::string, on_key_press_action_name)
        ADD_FIELD(LDS::Vector<unsigned int>, keys_to_listen)
        FIELDS_END

    public:
        const Actions_Controller* action_controller = nullptr;

    public:
        std::string on_key_press_action_name;
        LDS::Vector<unsigned int> keys_to_listen;

    public:
        INIT_BUILDER_STUB(Keyboard_Input_Listener_Module);

    };

}
