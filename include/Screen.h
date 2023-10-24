#ifndef SCREEN_H
#define SCREEN_H

#include <Data_Structures/Map.h>

#include <Variable_Base.h>
#include <Object_Constructor.h>

#include <Object_System/Object_2D.h>

#include <Renderer/Renderer.h>


namespace LGui
{

    class Screen
    {
    private:
        LDS::Map<std::string, LEti::Object_2D*> m_objects;

        bool m_is_active = false;

    public:
        Screen();
        ~Screen();

    private:
        Screen(Screen&& _other) = delete;
        Screen(const Screen& _other) = delete;

    public:
        inline void set_active(bool _value) { m_is_active = _value; }

    public:
        void add_object(const std::string& _name, LEti::Object_2D* _object);    //  Screen takes ownership of _object
        LEti::Object_2D* extract_object(const std::string& _name);              //  Screen releases ownership of returned object
        LEti::Object_2D* get_object(const std::string& _name);                  //  Screen does not release ownership of returned object

    public:
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

#endif // SCREEN_H
