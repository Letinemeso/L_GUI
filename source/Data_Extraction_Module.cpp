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



INIT_FIELDS(LGui::Data_Extraction_Module_Stub, LEti::Module_Stub)
FIELDS_END


LV::Variable_Base* Data_Extraction_Module_Stub::M_construct_product() const
{
    return new Data_Extraction_Module;
}

void Data_Extraction_Module_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    LV::Builder_Stub::M_init_constructed_product(_product);
}
