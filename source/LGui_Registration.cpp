#include <LGui_Registration.h>

#include <Screen.h>
#include <UI_Object_Stub.h>
#include <Modules/Keyboard_Input_Listener_Module.h>
#include <Modules/Physics_Module__GUI.h>
#include <Modules/Response_Sound_Module.h>
#include <GUI_Shader_Components/FS__Component__Crop_Rect.h>

using namespace LGui;


void LGui::register_types(LV::Object_Constructor& _object_constructor,
                          LR::Camera_2D& _camera,
                          const Actions_Controller& _actions_controller)
{
    LV::Object_Constructor* object_constructor = &_object_constructor;
    LR::Camera_2D* camera = &_camera;
    const Actions_Controller* actions_controller = &_actions_controller;

    _object_constructor.register_type<Screen_Stub>().override_initialization_func([object_constructor, camera](LV::Variable_Base* _product)
    {
        Screen_Stub* product = (Screen_Stub*)_product;

        product->object_constructor = object_constructor;
        product->camera = camera;
    });

    _object_constructor.register_type<LGui::UI_Object_Stub>();

    _object_constructor.register_type<LGui::Keyboard_Input_Listener_Module_Stub>().override_initialization_func([actions_controller](LV::Variable_Base* _product)
    {
        LGui::Keyboard_Input_Listener_Module_Stub* product = (LGui::Keyboard_Input_Listener_Module_Stub*)_product;

        product->action_controller = actions_controller;
    });

    _object_constructor.register_type<LGui::Physics_Module_Stub__GUI>().override_initialization_func([actions_controller](LV::Variable_Base* _product)
    {
        LGui::Physics_Module_Stub__GUI* product = (LGui::Physics_Module_Stub__GUI*)_product;

        product->actions_controller = actions_controller;
    });

    _object_constructor.register_type<LGui::Response_Sound_Module_Stub>();

    _object_constructor.register_type<LGui::FS__Component_Stub__Crop_Rect>();
}
