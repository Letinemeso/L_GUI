#pragma once

#include <Camera/Camera_2D.h>

#include <Object_Constructor.h>

#include <Actions_Controller.h>


namespace LGui
{
    void register_types(LV::Object_Constructor& _object_constructor,
                        LR::Camera_2D& _camera,
                        const Actions_Controller& _actions_controller);
}
