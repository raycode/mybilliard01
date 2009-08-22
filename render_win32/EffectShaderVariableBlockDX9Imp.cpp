#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderVariableBlockDX9Imp::EffectShaderVariableBlockDX9Imp(
    EffectShader * parent, EffectShaderVariableBlockCallBack * callBack )
: parent_( parent )
, callBack_( callBack )
, handle_( 0 )
{
}

EffectShaderVariableBlockDX9Imp::~EffectShaderVariableBlockDX9Imp() {
    releaseResource();
}

void EffectShaderVariableBlockDX9Imp::applyNow()  {
    effect_->ApplyParameterBlock( getHandleDX9() );
}

bool EffectShaderVariableBlockDX9Imp::acquireResource()  {
    if( NULL == effect_ ) return false;

    effect_->BeginParameterBlock();
    callBack_->setVariables();
    handle_ = effect_->EndParameterBlock();
    return true;
}

void EffectShaderVariableBlockDX9Imp::releaseResource() {
    effect_->DeleteParameterBlock( getHandleDX9() );
    effect_ = NULL;
}

void EffectShaderVariableBlockDX9Imp::setEffect( LPD3DXEFFECT effect )  {
    effect_ = effect;
}

D3DXHANDLE EffectShaderVariableBlockDX9Imp::getHandleDX9() {
    return handle_;
}

EffectShader * EffectShaderVariableBlockDX9Imp::getEffectShader() {
    return parent_;
}

}