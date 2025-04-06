#pragma once

#include <Resources_Manager.h>

#include <Sound.h>

#include <Modules/Activation_Response_Module.h>


namespace LGui
{

    class Response_Sound_Module : public Activation_Response_Module
    {
    public:
        INIT_VARIABLE(LGui::Response_Sound_Module, LGui::Activation_Response_Module)

    private:
        LSound::Sound* m_on_hovered_sound = nullptr;
        LSound::Sound* m_on_pressed_sound = nullptr;
        LSound::Sound* m_on_released_sound = nullptr;

        bool m_is_hovered = false;
        bool m_was_hovered = false;

    public:
        Response_Sound_Module();
        ~Response_Sound_Module();

    public:
        inline void set_on_hovered_sound(LSound::Sound* _sound) { delete m_on_hovered_sound; m_on_hovered_sound = _sound; }
        inline void set_on_pressed_sound(LSound::Sound* _sound) { delete m_on_pressed_sound; m_on_pressed_sound = _sound; }
        inline void set_on_released_sound(LSound::Sound* _sound) { delete m_on_released_sound; m_on_released_sound = _sound; }

    public:
        void on_hovered() override;
        void on_pressed() override;
        void on_released() override;

    public:
        void update(float _dt) override;

    };


    class Response_Sound_Module_Stub : public Activation_Response_Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Response_Sound_Module_Stub, LGui::Activation_Response_Module_Stub)

        INIT_CHILDS
        ADD_CHILD("on_hovered_sound", on_hovered_sound)
        ADD_CHILD("on_pressed_sound", on_pressed_sound)
        ADD_CHILD("on_released_sound", on_released_sound)
        CHILDS_END

    public:
        LSound::Sound_Stub* on_hovered_sound = nullptr;
        LSound::Sound_Stub* on_pressed_sound = nullptr;
        LSound::Sound_Stub* on_released_sound = nullptr;

    public:
        INIT_BUILDER_STUB(Response_Sound_Module)

    public:
        ~Response_Sound_Module_Stub();

    };

}
