#pragma once

#include <Stuff/Function_Wrapper.h>

#include <Modules/Physics_Module_2D.h>

#include <Window/Window_Controller.h>

#include <Actions_Controller.h>


namespace LGui
{

    class Physics_Module__GUI : public LPhys::Physics_Module_2D
    {
    public:
        INIT_VARIABLE(LGui::Physics_Module__GUI, LPhys::Physics_Module_2D);

    private:
        Action m_on_hover;
        Action m_on_pressed;
        Action m_on_released;

    public:
        inline void set_on_hover_action(const Action& _action) { m_on_hover = _action; }
        inline void set_on_pressed_action(const Action& _action) { m_on_pressed = _action; }
        inline void set_on_released_action(const Action& _action) { m_on_released = _action; }

    private:
        glm::vec3 m_hovered_at;
        bool m_is_hovered_on_current_frame = false;
        bool m_is_held = false;

    public:
        void notify_on_hovered(const glm::vec3& _where_exactly);
        void reset();

    private:
        void M_process_input();
        void M_on_hovered();
        void M_on_pressed();
        void M_on_released();

    public:
        void update(float _dt) override;

    };


    class Physics_Module_Stub__GUI : public LPhys::Physics_Module_2D_Stub
    {
    public:
        INIT_VARIABLE(LGui::Physics_Module_Stub__GUI, LPhys::Physics_Module_2D_Stub);

        INIT_FIELDS
        ADD_FIELD(std::string, on_hover_action_name)
        ADD_FIELD(std::string, on_pressed_action_name)
        ADD_FIELD(std::string, on_released_action_name)
        FIELDS_END

    public:
        const Actions_Controller* actions_controller = nullptr;

    public:
        std::string on_hover_action_name;
        std::string on_pressed_action_name;
        std::string on_released_action_name;

    public:
        INIT_BUILDER_STUB(Physics_Module__GUI)

    };

}
