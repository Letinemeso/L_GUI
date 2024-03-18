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

#include <UI_Object_Stub.h>
#include <Collisions/Physics_Module__GUI.h>


namespace LGui
{

    class Screen final
    {
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

    private:
        const LR::Camera_2D* m_camera = nullptr;

    public:
        Screen();
        ~Screen();

    private:
        Screen(Screen&& _other) = delete;
        Screen(const Screen& _other) = delete;

    public:
        inline void inject_camera(const LR::Camera_2D* _ptr) { m_camera = _ptr; }

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

    public:
        void update_previous_state();
        void update(float _dt);

    };


    class Screen_Constructor
    {
    private:
        const LV::Object_Constructor* m_object_constructor = nullptr;

    public:
        using Action = LST::Function<void()>;

    private:
        using Actions_Map = LDS::Map<std::string, Action>;
        Actions_Map m_on_press_functions;

    public:
        inline void inject_object_constructor(const LV::Object_Constructor* _ptr) { m_object_constructor = _ptr; }

    public:
        void register_action(const std::string& _name, const Action& _action);

    public:
        Screen* construct_screen(const LV::MDL_Variable_Stub& _stub) const;

    };

}
