#include <Screen.h>

using namespace LGui;


//  Screen

Screen::Screen()
{

}

Screen::~Screen()
{
    for(auto it = m_objects.iterator(); !it.end_reached(); ++it)
        delete *it;
    m_objects.clear();
}



void Screen::add_object(const std::string &_name, LEti::Object_2D *_object)
{
    L_ASSERT(_object);
    L_ASSERT(_name.size() > 0);

    auto check_it = m_objects.find(_name);
    L_ASSERT(!check_it.is_ok());

    m_objects.insert(_name, _object);
}

LEti::Object_2D* Screen::extract_object(const std::string& _name)
{
    LDS::Map<std::string, LEti::Object_2D*>::Iterator maybe_object_it = m_objects.find(_name);
    L_ASSERT(maybe_object_it.is_ok());

    LEti::Object_2D* result = *maybe_object_it;

    m_objects.erase(maybe_object_it);

    return result;
}

LEti::Object_2D* Screen::get_object(const std::string &_name) const
{
    LDS::Map<std::string, LEti::Object_2D*>::Const_Iterator maybe_object_it = m_objects.find(_name);
    L_ASSERT(maybe_object_it.is_ok());

    return *maybe_object_it;
}



void Screen::update_previous_state()
{
    for(LDS::Map<std::string, LEti::Object_2D*>::Iterator object_it = m_objects.iterator(); object_it.end_reached(); ++object_it)
        (*object_it)->update_previous_state();
}

void Screen::update(float _dt)
{
    for(LDS::Map<std::string, LEti::Object_2D*>::Iterator object_it = m_objects.iterator(); object_it.end_reached(); ++object_it)
        (*object_it)->update(_dt);
}





//  Screen_Constructor

Screen* Screen_Constructor::construct_screen(const LV::MDL_Variable_Stub &_stub) const
{
    L_ASSERT(m_object_constructor);

    Screen* result = new Screen;

    for(auto it = _stub.childs.iterator(); !it.end_reached(); ++it)
    {
        const std::string& name = it.key();

        LV::Variable_Base* constructed_object = m_object_constructor->construct(*it);
        UI_Object_Stub* object_stub = LV::cast_variable<UI_Object_Stub>(constructed_object);

        L_ASSERT(object_stub);

        LEti::Object_2D* screen_object = (LEti::Object_2D*)object_stub->construct();

        result->add_object(name, screen_object);
    }

    return result;
}
