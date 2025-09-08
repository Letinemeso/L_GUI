#pragma once

#include <Stuff/Message_Translator.h>

#include <Module.h>

#include <Window/Window_Controller.h>


namespace LGui
{

    class Autoscale_Module : public LEti::Module
    {
    public:
        INIT_VARIABLE(LGui::Autoscale_Module, LEti::Module)

    public:
        enum class Scale_Type
        {
            None,
            Horizontal,
            Vertical,
            Both,
            Proportional
        };

    private:
        glm::vec2 m_intended_window_size = { 0.0f, 0.0f };
        glm::vec2 m_offset = { 0.0f, 0.0f };

        Scale_Type m_offset_scale_type = Scale_Type::None;
        Scale_Type m_scale_type = Scale_Type::None;

        LST::Message_Translator::Handle<LR::Message__Window_Resized> m_subscription_handle;

    public:
        Autoscale_Module();
        ~Autoscale_Module();

    public:
        inline void set_intended_window_size(const glm::vec2& _value) { m_intended_window_size = _value; }
        inline void set_offset(const glm::vec2& _value) { m_offset = _value; }
        inline void set_offset_scale_type(Scale_Type _value) { m_offset_scale_type = _value; }
        inline void set_scale_type(Scale_Type _value) { m_scale_type = _value; }

    private:
        glm::vec3 M_calculate_scale(Scale_Type _scale_type) const;

    public:
        void rescale();

    protected:
        void M_on_parent_object_set() override;

    public:
        void update(float _dt) override;

    };


    class Autoscale_Module_Stub : public LEti::Module_Stub
    {
    public:
        INIT_VARIABLE(LGui::Autoscale_Module_Stub, LEti::Module_Stub)

        INIT_FIELDS
        ADD_FIELD(glm::vec2, intended_window_size)
        ADD_FIELD(glm::vec2, offset)
        ADD_FIELD(std::string, offset_scale_type)
        ADD_FIELD(std::string, scale_type)
        FIELDS_END

    public:
        glm::vec2 intended_window_size = { 0.0f, 0.0f };
        glm::vec2 offset = { 0.0f, 0.0f };

        std::string offset_scale_type = "None";
        std::string scale_type = "None";

    public:
        INIT_BUILDER_STUB(Autoscale_Module)

    private:
        Autoscale_Module::Scale_Type M_parse_scale_type(const std::string& _str) const;

    };

}
