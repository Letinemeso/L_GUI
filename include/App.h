#pragma once

#include <chrono>
#include <thread>
#include <map>

#include <Stuff/Timer.h>
#include <Stuff/File.h>

#include <MDL_Reader.h>
#include <Object_Constructor.h>

#include <FPS_Timer.h>
#include <Object_System/Object.h>

#include <Shader/Shader_Components/Shader_Transform_Component.h>
#include <Shader/Shader_Types/Vertex_Shader.h>
#include <Shader/Shader_Types/Geometry_Shader.h>
#include <Shader/Shader_Types/Fragment_Shader.h>
#include <Shader/Shader_Program.h>
#include <Camera/Camera_2D.h>
#include <Picture/Graphic_Resources_Manager.h>
#include <Renderer/Renderer.h>


namespace PCV
{

    class App final
    {
    private:
        LV::Object_Constructor m_object_constructor;

    private:
        LR::Shader_Transform_Component* m_vs_transform_component = nullptr;
        LR::Shader_Component* m_fs_component = nullptr;

        LR::Shader_Program m_shader_program;
        LR::Camera_2D m_camera;

        LR::Renderer m_renderer;

    private:
        LEti::FPS_Timer timer;

    private:
//        LEti::Object* m_user = nullptr;
//        LEti::Object* test_object = nullptr;
    public:
        App();
        ~App();

    private:
        App(const App&) = delete;
        App(App&&) = delete;
        void operator=(const App&) = delete;
        void operator=(App&&) = delete;

    private:
        void M_register_basic_types();
        void M_register_object_types();
        void M_init_renderer();
        void M_init_misc_stuff();

    public:
        void run();

    };

}
