#include <Screen.h>

using namespace LGui;


//  Screen

Screen::Screen()
{
    M_init_collision_stuff();
}

Screen::~Screen()
{
    for(auto it = m_objects.iterator(); !it.end_reached(); ++it)
        delete *it;
    m_objects.clear();
}



void Screen::M_init_collision_stuff()
{
    LPhys::Binary_Space_Partitioner* broad_phase = new LPhys::Binary_Space_Partitioner;
    broad_phase->set_precision(2);
    m_collision_detector.set_broad_phase(broad_phase);

    LPhys::Narrow_Phase__Model_Vs_Point* narrow_phase = new LPhys::Narrow_Phase__Model_Vs_Point;
    m_collision_detector.set_narrow_phase(narrow_phase);


    LGui::GUI_Collision_Resolution* collision_resolution = new LGui::GUI_Collision_Resolution;
    m_collision_resolver.set_resolution(collision_resolution);


    m_cursor_physics_module = new LPhys::Physics_Module__Point;
    m_cursor_object.remove_all_modules();
    m_cursor_object.add_module(m_cursor_physics_module);
}

void Screen::M_update_collision_detector_registrations()
{
    if(!m_collisions_registration_required)
        return;

    reset_interactive_objects();

    m_collision_detector.unregister_all_modules();

    LST::Function<void(const Physics_Module__GUI*)> add_to_collision_detector_func([this](const Physics_Module__GUI* _module)
    {
        m_collision_detector.register_module(_module);
    });

    for(Tagged_Objects_List::Const_Iterator object_it = m_current_tag_list->begin(); !object_it.end_reached(); ++object_it)
        (*object_it)->process_logic_for_modules_of_type(add_to_collision_detector_func);

    m_collision_detector.register_module(m_cursor_physics_module);

    m_collisions_registration_required = false;
}

void Screen::M_update_collisions(float _dt)
{
    L_ASSERT(m_camera);

    m_cursor_object.current_state().set_position(m_camera->convert_window_coords({LR::Window_Controller::get_cursor_position().x, LR::Window_Controller::get_cursor_position().y, 0.0f}));
    m_cursor_object.update(_dt);

    m_collision_detector.update();
    m_collision_resolver.resolve_all(m_collision_detector.found_collisions(), _dt);
}



void Screen::add_object(const std::string &_name, LEti::Object *_object)
{
    L_ASSERT(_object);
    L_ASSERT(_name.size() > 0);

    auto check_it = m_objects.find(_name);
    L_ASSERT(!check_it.is_ok());

    m_objects.insert(_name, _object);
}

LEti::Object* Screen::extract_object(const std::string& _name)
{
    LDS::Map<std::string, LEti::Object*>::Iterator maybe_object_it = m_objects.find(_name);
    L_ASSERT(maybe_object_it.is_ok());

    LEti::Object* result = *maybe_object_it;

    m_objects.erase(maybe_object_it);

    for(Tags_Map::Iterator tags_map_it = m_tags.iterator(); !tags_map_it.end_reached(); ++tags_map_it)
    {
        Tagged_Objects_List& tag_list = *tags_map_it;

        Tagged_Objects_List::Iterator it = tag_list.begin();
        while(!it.end_reached() && *it != result)
            ++it;

        if(it.end_reached())
            continue;

        tag_list.erase(it);
        m_collisions_registration_required = true;
    }

    //  tag list may be left empty after this operation. need to add some functionality to LDS::Map to fix it

    return result;
}

LEti::Object* Screen::get_object(const std::string &_name) const
{
    LDS::Map<std::string, LEti::Object*>::Const_Iterator maybe_object_it = m_objects.find(_name);
    L_ASSERT(maybe_object_it.is_ok());

    return *maybe_object_it;
}


void Screen::tag_object(const std::string& _object_name, const std::string& _tag)
{
    L_ASSERT(_tag.size() > 0);

    LDS::Map<std::string, LEti::Object*>::Iterator maybe_object_it = m_objects.find(_object_name);
    L_ASSERT(maybe_object_it.is_ok());

    LEti::Object* object = *maybe_object_it;

    Tags_Map::Iterator tag_iterator = m_tags.find(_tag);
    if(!tag_iterator.is_ok())
    {
        m_tags.insert(_tag, {});
        tag_iterator = m_tags.find(_tag);
    }

    Tagged_Objects_List& tag_list = *tag_iterator;

    Tagged_Objects_List::Iterator it = tag_list.begin();
    while(!it.end_reached() && *it != object)
        ++it;
    L_ASSERT(it.end_reached());

    tag_list.push_back(object);
    m_collisions_registration_required = true;
}

void Screen::untag_object(const std::string& _object_name, const std::string& _tag)
{
    L_ASSERT(_tag.size() > 0);

    LDS::Map<std::string, LEti::Object*>::Iterator maybe_object_it = m_objects.find(_object_name);
    L_ASSERT(maybe_object_it.is_ok());

    LEti::Object* object = *maybe_object_it;

    Tags_Map::Iterator tag_iterator = m_tags.find(_tag);
    L_ASSERT(tag_iterator.is_ok());

    Tagged_Objects_List& tag_list = *tag_iterator;

    Tagged_Objects_List::Iterator it = tag_list.begin();
    while(!it.end_reached() && *it != object)
        ++it;
    L_ASSERT(!it.end_reached());

    tag_list.erase(it);
    m_collisions_registration_required = true;

    if(tag_list.size() > 0)
        return;

    if(m_current_tag_list == &(*tag_iterator))
        m_current_tag_list = nullptr;

    m_tags.erase(tag_iterator);
}



void Screen::select_tag(const std::string& _tag)
{
    m_collisions_registration_required = true;

    if(_tag.size() == 0)
    {
        m_current_tag = _tag;
        m_current_tag_list = nullptr;
        return;
    }

    Tags_Map::Iterator tag_iterator = m_tags.find(_tag);
    L_ASSERT(tag_iterator.is_ok());

    m_current_tag = _tag;
    m_current_tag_list = &(*tag_iterator);
}

void Screen::reset_interactive_objects()
{
    for(LPhys::Collision_Detector::Registred_Modules_List::Const_Iterator module_it = m_collision_detector.registred_modules().begin(); !module_it.end_reached(); ++module_it)
    {
        if(*module_it == m_cursor_physics_module)
            continue;

        Physics_Module__GUI* module = (Physics_Module__GUI*)*module_it;     //  this casts and removes const at the same time - ugly af, but Screen should only put valid modules there and it also kinda owns them
        module->reset();
    }
}



void Screen::update_previous_state()
{
    if(m_current_tag_list == nullptr)
        return;

    for(Tagged_Objects_List::Const_Iterator object_it = m_current_tag_list->begin(); !object_it.end_reached(); ++object_it)
        (*object_it)->update_previous_state();
}

void Screen::update(float _dt)
{
    if(m_current_tag_list == nullptr)
        return;

    M_update_collision_detector_registrations();

    M_update_collisions(_dt);

    for(Tagged_Objects_List::Const_Iterator object_it = m_current_tag_list->begin(); !object_it.end_reached(); ++object_it)
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

        LEti::Object* screen_object = (LEti::Object*)object_stub->construct();

        result->add_object(name, screen_object);

        for(unsigned int i=0; i<object_stub->tags_amount; ++i)
            result->tag_object(name, object_stub->tags[i]);

        delete constructed_object;
    }

    return result;
}
