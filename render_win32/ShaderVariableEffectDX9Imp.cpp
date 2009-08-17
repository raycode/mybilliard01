#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


ShaderVariableEffectDX9Imp::ShaderVariableEffectDX9Imp( wstring variableName, EVARIABLETYPE variableType )
: variableName_( variableName )
, variableType_( variableType )
, effect_( NULL )
{
}

ShaderVariableEffectDX9Imp::~ShaderVariableEffectDX9Imp() {
    releaseResource();
}

bool ShaderVariableEffectDX9Imp::acquireResource() {
    if( NULL == effect_ ) return false;

    switch( variableType_ )
    {
    case ETYPE_TECHNIQUE:
        handle_ = effect_->GetTechniqueByName( convertString( variableName_ ).c_str() );
        break;
    case ETYPE_PARAM:
        handle_ = effect_->GetParameterByName( 0, convertString( variableName_ ).c_str() );
        break;
    }
    return true;
}

void ShaderVariableEffectDX9Imp::releaseResource() {
    effect_ = NULL;
}

void ShaderVariableEffectDX9Imp::setEffect( LPD3DXEFFECT effect ) {
    effect_ = effect;
}

wstring ShaderVariableEffectDX9Imp::getVariableName() {
    return variableName_;
}

D3DXHANDLE ShaderVariableEffectDX9Imp::getHandleDX9() {
    return handle_;
}


}