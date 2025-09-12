#pragma once

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>

#include <Variable_Base.h>
#include <Object_Constructor.h>

#include <Renderer/Renderer.h>
#include <Camera/Camera_2D.h>

#include <Collision_Detection/Collision_Detector.h>
#include <Collision_Detection/Broad_Phase/Binary_Space_Partitioner.h>
#include <Collision_Detection/Narrow_Phase/Narrow_Phase__Model_Vs_Point.h>
#include <Collision_Resolution/Collision_Resolver.h>
#include <Collisions/GUI_Collision_Resolution.h>

#include <Tools/Physical_Model_Renderer.h>

#include <UI_Object_Stub.h>


namespace LGui
{

    class Screen : public LV::Variable_Base
    {
    public:
        INIT_VARIABLE(LGui::Screen, LV::Variable_Base)

    private:
        using Objects_Map = LDS::Map<std::string, LEti::Object*>;
        using Tagged_Objects_List = LDS::List<LEti::Object*>;
        using Tags_Map = LDS::Map<std::string, Tagged_Objects_List>;

    private:
        Objects_Map m_objects;
        Tags_Map m_tags;

        std::string m_current_tag;
        const Tagged_Objects_List* m_current_tag_list = nullptr;

    private:
        bool m_collisions_registration_required = false;

        LPhys::Collision_Detector m_collision_detector;
        LPhys::Collision_Resolver m_collision_resolver;

        LEti::Object m_cursor_object;
        LPhys::Physics_Module__Point* m_cursor_physics_module = nullptr;

        bool m_input_enabled_on_next_update = true;
        bool m_input_enabled = true;

    private:
        LMD::Physical_Model_Renderer* m_physical_model_renderer = nullptr;

    private:
        const LR::Camera_2D* m_camera = nullptr;

    public:
        inline static const std::string& events_log_level() { static std::string name = "GUI EVENT"; return name; }

    public:
        Screen();
        ~Screen();

    private:
        Screen(Screen&& _other) = delete;
        Screen(const Screen& _other) = delete;

    public:
        inline void inject_camera(const LR::Camera_2D* _ptr) { m_camera = _ptr; }
        inline const LR::Camera_2D* camera() const { return m_camera; }

        inline void enable_input(bool _enable) { m_input_enabled = _enable; m_input_enabled_on_next_update = _enable; }
        inline void enable_input_on_next_update(float _enable) { m_input_enabled_on_next_update = _enable; }
        inline bool input_enabled() const { return m_input_enabled; }

        inline void set_physical_model_renderer(LMD::Physical_Model_Renderer* _ptr) { delete m_physical_model_renderer; m_physical_model_renderer = _ptr; }

    private:
        void M_init_collision_stuff();
        void M_update_collision_detector_registrations();
        void M_update_collisions(float _dt);

    public:
        void add_object(const std::string& _name, LEti::Object* _object);    //  Screen takes ownership of _object
        LEti::Object* extract_object(const std::string& _name);              //  Screen releases ownership of returned object
        LEti::Object* get_object(const std::string& _name) const;            //  Screen does not release ownership of returned object

        void tag_object(const std::string& _object_name, const std::string& _tag);
        void untag_object(const std::string& _object_name, const std::string& _tag);

    public:
        void select_tag(const std::string& _tag);
        void reset_interactive_objects();

    public:
        inline const std::string& current_tag() const { return m_current_tag; }

    private:
        void M_draw_interactable_objects();

    public:
        void update_previous_state();
        void update(float _dt);

    };


    class Screen_Stub : public LV::Builder_Stub
    {
    public:
        INIT_VARIABLE(LGui::Screen_Stub, LV::Builder_Stub);

        INIT_FIELDS
        ADD_FIELD(std::string, default_tag)
        FIELDS_END

        INIT_CHILDS
        ADD_CHILD("physical_model_renderer_draw_module", physical_model_renderer_draw_module)
        CHILDS_END

        INIT_CHILDS_LISTS
        ADD_CHILDS_LIST("GUI_object__*", &gui_object_stubs)
        CHILDS_LISTS_END

    public:
        std::string default_tag;

    public:
        LV::Variable_Base::Childs_List gui_object_stubs;
        LR::Draw_Module_Stub* physical_model_renderer_draw_module = nullptr;

    public:
        const LV::Object_Constructor* object_constructor = nullptr;
        const LR::Camera_2D* camera = nullptr;

    public:
        ~Screen_Stub();

    private:
        LMD::Physical_Model_Renderer* M_construct_physical_model_renderer() const;

    public:
        INIT_BUILDER_STUB(Screen);

    };

}
