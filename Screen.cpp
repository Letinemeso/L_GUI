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
    auto check_it = m_objects.find(_name);
    L_ASSERT(!check_it.is_ok());

    m_objects.insert(_name, _object);
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
        LEti::Object_2D* screen_object = LV::cast_variable<LEti::Object_2D>(constructed_object);

        L_ASSERT(screen_object);

        result->add_object(name, screen_object);
    }

    return result;
}
