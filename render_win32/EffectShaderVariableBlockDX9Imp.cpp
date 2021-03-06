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
    if( FAILED( hr ) ) DXUT_ERR( L"EffectShaderVariableBlockDX9Imp::applyNow", hr );
}

bool EffectShaderVariableBlockDX9Imp::acquireResource()  {
    assert( effect_ );
    if( NULL == effect_ ) return false;

    const HRESULT hr = effect_->BeginParameterBlock();
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableBlockDX9Imp::acquireResource" );

    callBack_->setEffectShaderVariableBlock();
    handle_ = effect_->EndParameterBlock();
    return true;
}

void EffectShaderVariableBlockDX9Imp::releaseResource() {
    assert( effect_ );
    const HRESULT hr = effect_->DeleteParameterBlock( getHandleDX9() );
    if( FAILED( hr ) ) DXUT_ERR( L"EffectShaderVariableBlockDX9Imp::releaseResource", hr );
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
