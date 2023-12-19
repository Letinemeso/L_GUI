#include <Data_Extraction_Module.h>

using namespace LGui;


INIT_FIELDS(LGui::Data_Extraction_Module, LEti::Module)
FIELDS_END


Data_Extraction_Module::Data_Extraction_Module()
{

}

Data_Extraction_Module::~Data_Extraction_Module()
{

}



void Data_Extraction_Module::update(float /*_dt*/)
{
    L_ASSERT(m_data_extraction_func);
    L_ASSERT(m_update_logic_func);

    m_update_logic_func(m_data_extraction_func);
}



INIT_FIELDS(LGui::Data_Extraction_Module_Stub, LV::Builder_Stub)
FIELDS_END


LV::Variable_Base* Data_Extraction_Module_Stub::M_construct_product() const
{
    return new Data_Extraction_Module;
}

void Data_Extraction_Module_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    LV::Builder_Stub::M_init_constructed_product(_product);

    Data_Extraction_Module* product = (Data_Extraction_Module*)_product;

    product->set_data_extraction_func(data_extraction_func);
    product->set_update_logic_func(update_logic_func);
}
