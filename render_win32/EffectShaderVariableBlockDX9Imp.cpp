#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderVariableBlockDX9Imp::EffectShaderVariableBlockDX9Imp(
    EffectShader * parent, EffectShaderVariableBlockCallBack * callBack )
: parent_( parent )
, callBack_( callBack )
, effect_( NULL )
, handle_( 0 )
{
}

EffectShaderVariableBlockDX9Imp::~EffectShaderVariableBlockDX9Imp() {
    releaseResource();
}

void EffectShaderVariableBlockDX9Imp::applyNow()  {
    const HRESULT hr = effect_->ApplyParameterBlock( getHandleDX9() );
    assert( S_OK == hr );
}

bool EffectShaderVariableBlockDX9Imp::acquireResource()  {
    if( NULL == effect_ ) return false;

    effect_->BeginParameterBlock();
    callBack_->setEffectShaderVariableBlock();
    handle_ = effect_->EndParameterBlock();
    return true;
}

void EffectShaderVariableBlockDX9Imp::releaseResource() {
    if( NULL == effect_ ) return;
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