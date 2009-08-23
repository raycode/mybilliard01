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

void EffectShaderAnnotationDX9Imp::getValue( void * dest, size_t sizeInByte ) {
    assert( effect_ );
    effect_->GetValue( getHandleDX9(), dest, sizeInByte );
}

wstring EffectShaderAnnotationDX9Imp::getAnnotationName() {
    assert( effect_ );
    D3DXPARAMETER_DESC desc;
    effect_->GetParameterDesc( getHandleDX9(), &desc );
    return convertString( desc.Name );
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
    return true;
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


}