#include <Modules/Response_Sound_Module.h>

using namespace LGui;


Response_Sound_Module::Response_Sound_Module()
{

}

Response_Sound_Module::~Response_Sound_Module()
{
    delete m_on_hovered_sound;
    delete m_on_pressed_sound;
    delete m_on_released_sound;
}



void Response_Sound_Module::on_hovered()
{
    if(!m_on_hovered_sound)
        return;

    if(m_is_hovered)
        return;

    m_is_hovered = true;

    if(m_was_hovered)
        return;

    m_on_hovered_sound->play();
}

void Response_Sound_Module::on_pressed()
{
    if(!m_on_pressed_sound)
        return;

    m_on_pressed_sound->play();
}

void Response_Sound_Module::on_released()
{
    if(!m_on_released_sound)
        return;

    m_on_released_sound->play();
}



void Response_Sound_Module::update(float _dt)
{
    m_was_hovered = m_is_hovered;
    m_is_hovered = false;
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(Response_Sound_Module_Stub)

BUILDER_STUB_INITIALIZATION_FUNC(Response_Sound_Module_Stub)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    if(on_hovered_sound)
        product->set_on_hovered_sound(LSound::Sound_Stub::construct_from(on_hovered_sound));
    if(on_pressed_sound)
        product->set_on_pressed_sound(LSound::Sound_Stub::construct_from(on_pressed_sound));
    if(on_released_sound)
        product->set_on_released_sound(LSound::Sound_Stub::construct_from(on_released_sound));
}



Response_Sound_Module_Stub::~Response_Sound_Module_Stub()
{
    delete on_hovered_sound;
    delete on_pressed_sound;
    delete on_released_sound;
}
