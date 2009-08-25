#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderAnnotationDX9Imp::EffectShaderAnnotationDX9Imp( size_t index, EffectShaderVariableDX9 * parent )
: searchBy_( ESEARCH_BY_INDEX )
, index_( index )
, parent_( parent )
, effect_( NULL )
{
    if( NULL == parent ) throw exception();
}

EffectShaderAnnotationDX9Imp::EffectShaderAnnotationDX9Imp( wstring name, EffectShaderVariableDX9 * parent )
: searchBy_( ESEARCH_BY_NAME )
, index_( 0 )
, name_( name )
, parent_( parent )
{
    if( NULL == parent ) throw exception();
}

void EffectShaderAnnotationDX9Imp::setEffect( LPD3DXEFFECT effect ) {
    effect_ = effect;
}

bool EffectShaderAnnotationDX9Imp::acquireResource()
{
    assert( effect_ );
    if( NULL == effect_ ) return false;

    switch( searchBy_ )
    {
    case ESEARCH_BY_INDEX:
        handle_ = effect_->GetAnnotation( getParentHandle(), index_ );
        break;
    case ESEARCH_BY_NAME:
        handle_ = effect_->GetParameterByName( getParentHandle(), convertString( name_ ).c_str() );
        break;
    }

    if( NULL == handle_ ) {
        wchar_t tmp[256];
        _snwprintf_s( tmp, 256, L"EffectShaderAnnotationDX9Imp::acquireResource\n" );
        OutputDebugStr( tmp );
        return false;
    }

    assert( effect_ );
    effect_->GetParameterDesc( getHandleDX9(), & desc_ );

    return true;
}

bool EffectShaderAnnotationDX9Imp::isString() {
    return D3DXPT_STRING == getParameterDesc().Type;
}
bool EffectShaderAnnotationDX9Imp::isFloat() {
    return D3DXPT_FLOAT == getParameterDesc().Type;
}
bool EffectShaderAnnotationDX9Imp::isBool() {
    return D3DXPT_BOOL == getParameterDesc().Type;
}
wstring EffectShaderAnnotationDX9Imp::getAnnotationName() {
    return convertString( getParameterDesc().Name );
}
const D3DXPARAMETER_DESC & EffectShaderAnnotationDX9Imp::getParameterDesc() {
    return desc_;
}

void EffectShaderAnnotationDX9Imp::releaseResource() {
    effect_ = NULL;
}

D3DXHANDLE EffectShaderAnnotationDX9Imp::getParentHandle() {
    assert( parent_ );
    return parent_->getHandleDX9();
}

D3DXHANDLE EffectShaderAnnotationDX9Imp::getHandleDX9() {
    return handle_;
}

wstring EffectShaderAnnotationDX9Imp::getString() {
    const char * buff;
    const HRESULT hr = effect_->GetString( getHandleDX9(), & buff );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderAnnotationDX9Imp::getString" );
    return convertString( buff );
}

float EffectShaderAnnotationDX9Imp::getFloat() {
    float buff;
    const HRESULT hr = effect_->GetFloat( getHandleDX9(), & buff );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderAnnotationDX9Imp::getFloat" );
    return buff;
}
bool EffectShaderAnnotationDX9Imp::getBool() {
    BOOL buff;
    const HRESULT hr = effect_->GetBool( getHandleDX9(), & buff );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderAnnotationDX9Imp::getBool" );
    return TRUE == buff;
}


}