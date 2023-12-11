#include <App.h>

using namespace PCV;


App::App()
{
    M_register_basic_types();
    M_register_object_types();
    M_init_renderer();
    M_init_misc_stuff();
}

App::~App()
{
//    delete m_user;
}



void App::M_register_basic_types()
{
    //  registration of basic types for model parser

    LV::Type_Manager::register_type("int", {
                                        [](const std::string& _val)
                                        {
                                            unsigned int i=0;
                                            if(_val[0] == '+' || _val[0] == '-')
                                            ++i;
                                            for(; i<_val.size(); ++i)
                                            if(_val[i] < '0' || _val[i] > '9')
                                            return false;
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string) { *((int*)_variable_vptr) = std::stoi(_values_as_string[0]); }
                                    });
    LV::Type_Manager::register_type("int*", {
                                        [](const std::string& _val)
                                        {
                                            unsigned int i=0;
                                            if(_val[0] == '+' || _val[0] == '-')
                                            ++i;
                                            for(; i<_val.size(); ++i)
                                            if(_val[i] < '0' || _val[i] > '9')
                                            return false;
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            int** var_ptr_ptr = (int**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                                *var_ptr_ptr = new int[_values_as_string.size()];

                                            int* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                                var_ptr[i] = std::stoi(_values_as_string[i]);
                                        }
                                    });
    LV::Type_Manager::register_type("unsigned char*", {
                                        [](const std::string& _val)
                                        {
                                            if(_val.size() != 1)
                                                return false;
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            unsigned char** var_ptr_ptr = (unsigned char**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                                *var_ptr_ptr = new unsigned char[_values_as_string.size()];

                                            unsigned char* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                                var_ptr[i] = _values_as_string[i][0];
                                        }
                                    });
    LV::Type_Manager::register_type("unsigned int", {
                                        [](const std::string& _val)
                                        {
                                            for(unsigned int i=0; i<_val.size(); ++i)
                                            if(_val[i] < '0' || _val[i] > '9')
                                            return false;
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string) { *((int*)_variable_vptr) = std::stoi(_values_as_string[0]); }
                                    });
    LV::Type_Manager::register_type("unsigned int*", {
                                        [](const std::string& _val)
                                        {
                                            for(unsigned int i=0; i<_val.size(); ++i)
                                            if(_val[i] < '0' || _val[i] > '9')
                                            return false;
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            unsigned int** var_ptr_ptr = (unsigned int**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                                *var_ptr_ptr = new unsigned int[_values_as_string.size()];

                                            unsigned int* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                                var_ptr[i] = std::stoi(_values_as_string[i]);
                                        }
                                    });
    LV::Type_Manager::register_type("bool", {
                                        [](const std::string& _val)
                                        {
                                            if(_val == "true" || _val == "false" || _val == "+" || _val == "-" || _val == "1" || _val == "0")
                                            return true;
                                            return false;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            bool& var = *((bool*&)_variable_vptr);

                                            if(_values_as_string[0] == "true" || _values_as_string[0] == "+" || _values_as_string[0] == "1")
                                            var = true;
                                            else if(_values_as_string[0] == "false" || _values_as_string[0] == "-" || _values_as_string[0] == "0")
                                            var = false;
                                        }
                                    });
    LV::Type_Manager::register_type("bool*", {
                                        [](const std::string& _val)
                                        {
                                            if(_val == "true" || _val == "false" || _val == "+" || _val == "-" || _val == "1" || _val == "0")
                                            return true;
                                            return false;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            bool** var_ptr_ptr = (bool**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                            *var_ptr_ptr = new bool[_values_as_string.size()];

                                            bool* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                            {
                                                if(_values_as_string[i] == "true" || _values_as_string[i] == "+" || _values_as_string[i] == "1")
                                                var_ptr[i] = true;
                                                else if(_values_as_string[i] == "false" || _values_as_string[i] == "-" || _values_as_string[i] == "0")
                                                var_ptr[i] = false;
                                            }
                                        }
                                    });
    LV::Type_Manager::register_type("std::string", {
                                        [](const std::string& /*_val*/) { return true; },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string) {
                                            *((std::string*)_variable_vptr) = _values_as_string[0];
                                        }
                                    });
    LV::Type_Manager::register_type("float*", {
                                        [](const std::string& _val)
                                        {
                                            if(_val == ".")
                                            return false;

                                            unsigned int dots_count = 0;
                                            unsigned int i=0;
                                            if(_val[0] == '+' || _val[0] == '-')
                                            ++i;
                                            for(; i<_val.size(); ++i)
                                            {
                                                if(_val[i] == '.')
                                                {
                                                    ++dots_count;
                                                    continue;
                                                }
                                                if(_val[i] < '0' || _val[i] > '9')
                                                return false;
                                            }

                                            if(dots_count > 1)
                                            return false;

                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            float** var_ptr_ptr = (float**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                            *var_ptr_ptr = new float[_values_as_string.size()];

                                            float* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                            var_ptr[i] = std::stof(_values_as_string[i]);
                                        }
                                    });
    LV::Type_Manager::register_type("std::string*", {
                                        [](const std::string& /*_val*/)
                                        {
                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            std::string** var_ptr_ptr = (std::string**)_variable_vptr;

                                            if(*var_ptr_ptr == nullptr)
                                            *var_ptr_ptr = new std::string[_values_as_string.size()];

                                            std::string* var_ptr = *var_ptr_ptr;

                                            for(unsigned int i=0; i<_values_as_string.size(); ++i)
                                            var_ptr[i] = _values_as_string[i];
                                        }
                                    });
    LV::Type_Manager::register_type("glm::vec3", {
                                        [](const std::string& _val)
                                        {
                                            if(_val == ".")
                                            return false;

                                            unsigned int dots_count = 0;
                                            unsigned int i=0;
                                            if(_val[0] == '+' || _val[0] == '-')
                                            ++i;
                                            for(; i<_val.size(); ++i)
                                            {
                                                if(_val[i] == '.')
                                                {
                                                    ++dots_count;
                                                    continue;
                                                }
                                                if(_val[i] < '0' || _val[i] > '9')
                                                return false;
                                            }

                                            if(dots_count > 1)
                                            return false;

                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string)
                                        {
                                            L_ASSERT(_values_as_string.size() == 3);

                                            glm::vec3& vec = *((glm::vec3*)_variable_vptr);
                                            for(unsigned int i=0; i<3; ++i)
                                            vec[i] = std::stof(_values_as_string[i]);
                                        }
                                    });
    LV::Type_Manager::register_type("float", {
                                        [](const std::string& _val)
                                        {
                                            if(_val == ".")
                                            return false;

                                            unsigned int dots_count = 0;
                                            unsigned int i=0;
                                            if(_val[0] == '+' || _val[0] == '-')
                                            ++i;
                                            for(; i<_val.size(); ++i)
                                            {
                                                if(_val[i] == '.')
                                                {
                                                    ++dots_count;
                                                    continue;
                                                }
                                                if(_val[i] < '0' || _val[i] > '9')
                                                return false;
                                            }

                                            if(dots_count > 1)
                                            return false;

                                            return true;
                                        },
                                        [](void* _variable_vptr, const LDS::Vector<std::string>& _values_as_string) { *((float*)_variable_vptr) = std::stof(_values_as_string[0]); }
                                    });
}

void App::M_register_object_types()
{
//    m_object_constructor.register_type<Camera_Control_Module_Stub>().override_initialization_func([this](LV::Variable_Base* _product)
//    {
//        Camera_Control_Module_Stub* product = (Camera_Control_Module_Stub*)_product;

//        product->camera = &m_camera;
//        product->shader_point_expansion_component = m_gs_point_expansion_component;
//    });

//    m_object_constructor.register_type<User_Stub>();
}

void App::M_init_renderer()
{
    LR::Window_Controller::create_window(1200, 800, "L_GUI TEST");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);

    LST::File vertex_shader_file("Resources/Shaders/vertex_transform_component.shader");
    LST::File fragment_shader_file("Resources/Shaders/fragment_shader.shader");

    LV::MDL_Reader reader;

    m_vs_transform_component = new LR::Shader_Transform_Component;
    m_vs_transform_component->set_source(vertex_shader_file.extract_block());
    m_vs_transform_component->set_main_call("process_transform();");

    LR::Vertex_Shader* vertex_shader = new LR::Vertex_Shader;
    vertex_shader->set_glsl_version("330 core");
    vertex_shader->add_component(m_vs_transform_component);
    vertex_shader->compile();

    m_fs_component = new LR::Shader_Component;
    m_fs_component->set_source(fragment_shader_file.extract_block());
    m_fs_component->set_main_call("process_color();");

    LR::Fragment_Shader* fragment_shader = new LR::Fragment_Shader;
    fragment_shader->set_glsl_version("330 core");
    fragment_shader->add_component(m_fs_component);
    fragment_shader->compile();

    m_shader_program.add_shader(vertex_shader);
    m_shader_program.add_shader(fragment_shader);
    m_shader_program.init();

    m_camera.set_view_scale(1.0f);
    m_camera.set_position({600, 400, 0});

    m_renderer.set_camera(&m_camera);
    m_renderer.set_shader_program(&m_shader_program);
}



void App::M_init_misc_stuff()
{
    timer.set_max_dt(60.0f / 1000.0f);
}

#include <Modules/Rigid_Body_2D.h>
#include <Draw_Modules/Default_Draw_Module.h>
#include <UI_Object_Stub.h>
#include <Screen.h>

void App::run()
{
    srand(time(nullptr));

    LV::MDL_Reader reader;

    reader.parse_file("Resources/Textures/textures");
    reader.parse_file("Resources/Models/triangle");

    LR::Graphic_Resources_Manager graphics_resources_manager;
    graphics_resources_manager.load_resources(reader.get_stub("resources"));

    LV::Object_Constructor object_constructor;

    object_constructor.register_type<LR::Default_Draw_Module_Stub>().override_initialization_func([this, &graphics_resources_manager](LV::Variable_Base* _product)
    {
        LR::Default_Draw_Module_Stub* product = (LR::Default_Draw_Module_Stub*)_product;

        product->renderer = &m_renderer;
        product->shader_transform_component = m_vs_transform_component;
        product->graphic_resources_manager = &graphics_resources_manager;
    });
    object_constructor.register_type<LPhys::Rigid_Body_2D__Stub>();
    object_constructor.register_type<LGui::UI_Object_Stub>();


    reader.parse_file("Resources/Models/ui_object_stub_test");
    reader.parse_file("Resources/Models/screen_test");

    LGui::Screen_Constructor screen_constructor;
    screen_constructor.inject_object_constructor(&object_constructor);
    LGui::Screen* screen = screen_constructor.construct_screen(reader.get_stub("screen_test"));


    LGui::UI_Object_Stub* ui_object_stub_test = (LGui::UI_Object_Stub*)object_constructor.construct(reader.get_stub("ui_object_stub_test"));
    LEti::Object* ui_object_test = (LEti::Object*)ui_object_stub_test->construct();
    delete ui_object_stub_test;



    while (!LR::Window_Controller::window_should_close())
    {
        timer.update();
        LR::Window_Controller::update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//        ui_object_test->update_previous_state();
        screen->update_previous_state();





//        ui_object_test->update(timer.dt());
        screen->update(timer.dt());


        LR::Window_Controller::swap_buffers();
    }

    delete screen;
    delete ui_object_test;
}
