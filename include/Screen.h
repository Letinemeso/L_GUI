#pragma once

#include <Data_Structures/Map.h>
#include <Data_Structures/List.h>

#include <Variable_Base.h>
#include <Object_Constructor.h>

#include <Renderer/Renderer.h>

#include <UI_Object_Stub.h>


namespace LGui
{

    class Screen
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

    public:
        Screen();
        ~Screen();

    private:
        Screen(Screen&& _other) = delete;
        Screen(const Screen& _other) = delete;

    public:
        void add_object(const std::string& _name, LEti::Object* _object);    //  Screen takes ownership of _object
        LEti::Object* extract_object(const std::string& _name);              //  Screen releases ownership of returned object
        LEti::Object* get_object(const std::string& _name) const;                  //  Screen does not release ownership of returned object

        void tag_object(const std::string& _object_name, const std::string& _tag);
        void untag_object(const std::string& _object_name, const std::string& _tag);

    public:
        void select_tag(const std::string& _tag);

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
        inline void inject_object_constructor(const LV::Object_Constructor* _ptr) { m_object_constructor = _ptr; }

    public:
        Screen* construct_screen(const LV::MDL_Variable_Stub& _stub) const;

    };

}
