#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderVariableDX9Imp::EffectShaderVariableDX9Imp(
    ESEARCH_BY searchBy, wstring nameOrSemantic, ShaderVariableHandleDX9 * parent )
    : searchBy_( searchBy )
    , nameOrSemantic_( nameOrSemantic )
    , variableIndex_( 0u )
    , parent_( parent )
    , effect_( NULL )
    , handle_( 0 )
{
    assert( ESEARCH_BY_INDEX != searchBy );
}

EffectShaderVariableDX9Imp::EffectShaderVariableDX9Imp(
    ESEARCH_BY searchBy, size_t index, ShaderVariableHandleDX9 * parent )
    : searchBy_( searchBy )
    , variableIndex_( index )
    , parent_( parent )
    , effect_( NULL )
{
    assert( ESEARCH_BY_INDEX == searchBy );
}

bool EffectShaderVariableDX9Imp::acquireResource() {
    if( NULL == effect_ ) return false;

    switch( searchBy_ )
    {
    case ESEARCH_BY_INDEX:
        handle_ = effect_->GetParameter( getParentHandleDX9(), (UINT) variableIndex_ );
        break;
    case ESEARCH_BY_NAME:
        handle_ = effect_->GetParameterByName( getParentHandleDX9(), convertString( nameOrSemantic_ ).c_str() );
        break;
    case ESEARCH_BY_SEMANTIC:
        handle_ = effect_->GetParameterBySemantic( getParentHandleDX9(), convertString( nameOrSemantic_ ).c_str() );
        break;
    }

    if( NULL == handle_ ) {
        wchar_t tmp[256];
        _snwprintf_s( tmp, 256, L"EffectShaderVariableDX9Imp::acquireResource\n" );
        OutputDebugStr( tmp );
        return false;
    }

    assert( effect_ );

    effect_->GetParameterDesc( handle_, &desc_ );

    MY_FOR_EACH( NestedVariables, iter, nestedVariables_ )
        setEffectOntoNestedVariable( &**iter );

    return true;
}

bool EffectShaderVariableDX9Imp::setEffectOntoNestedVariable( ReleasableEffectResourceDX9 * var ) {
    assert( var );
    if( NULL == effect_ ) return false;
    var->setEffect( effect_ );
    return var->acquireResource();
}

void EffectShaderVariableDX9Imp::releaseResource() {
    nestedVariables_.clear();
    effect_ = NULL;
}

bool EffectShaderVariableDX9Imp::releaseAnyEffectVariable( ReleasableEffectResourceDX9 * var ) {
    return remove_only_one_pointer< NestedVariables >( nestedVariables_, var );
}
bool EffectShaderVariableDX9Imp::releaseNestedVariable( ShaderVariable * nestedVariable ) {
    return releaseAnyEffectVariable( dynamic_cast< ReleasableEffectResourceDX9 * >( nestedVariable ) );
}
bool EffectShaderVariableDX9Imp::releaseShaderAnnotation( EffectShaderAnnotation * anno ) {
    return releaseAnyEffectVariable( dynamic_cast< ReleasableEffectResourceDX9 * >( anno ) );
}
void EffectShaderVariableDX9Imp::setEffect( LPD3DXEFFECT effect ) {
    effect_ = effect;
}

bool EffectShaderVariableDX9Imp::hasNestedVariableByName( wstring name ) {
    return NULL != effect_->GetParameterByName( getHandleDX9(), convertString( name ).c_str() );
}
bool EffectShaderVariableDX9Imp::hasNestedVariableBySemantic( wstring semantic ) {
    return NULL != effect_->GetParameterBySemantic( getHandleDX9(), convertString( semantic ).c_str() );
}
bool EffectShaderVariableDX9Imp::hasAnnotationByName( wstring anno ) {
    return NULL != effect_->GetAnnotationByName( getHandleDX9(), convertString( anno ).c_str() );
}

ShaderVariable * EffectShaderVariableDX9Imp::createNestedVariableByIndex( size_t index ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( ESEARCH_BY_INDEX, index, this ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoNestedVariable( &*newVariable ) ) return NULL;
    nestedVariables_.push_back( newVariable );
    return &*newVariable;
}
ShaderVariable * EffectShaderVariableDX9Imp::createNestedVariableByName( wstring name ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( ESEARCH_BY_NAME, name, this ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoNestedVariable( &*newVariable ) ) return NULL;
    nestedVariables_.push_back( newVariable );
    return &*newVariable;
}
ShaderVariable * EffectShaderVariableDX9Imp::createNestedVariableBySemantic( wstring semantic ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( ESEARCH_BY_SEMANTIC, semantic, this ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoNestedVariable( &*newVariable ) ) return NULL;
    nestedVariables_.push_back( newVariable );
    return &*newVariable;
}

EffectShaderAnnotation * EffectShaderVariableDX9Imp::createAnnotationByIndex( size_t index ) {
    EffectShaderAnnotationDX9Ptr newAnno = EffectShaderAnnotationDX9Ptr( new EffectShaderAnnotationDX9Imp( index, this ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoNestedVariable( &*newAnno ) ) return NULL;
    nestedVariables_.push_back( newAnno );
    return &*newAnno;
}
EffectShaderAnnotation * EffectShaderVariableDX9Imp::createAnnotationByName( wstring name ) {
    EffectShaderAnnotationDX9Ptr newAnno = EffectShaderAnnotationDX9Ptr( new EffectShaderAnnotationDX9Imp( name , this ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoNestedVariable( &*newAnno ) ) return NULL;
    nestedVariables_.push_back( newAnno );
    return &*newAnno;
}

const D3DXPARAMETER_DESC & EffectShaderVariableDX9Imp::getParameterDesc() {
    return desc_;
}
wstring EffectShaderVariableDX9Imp::getVariableName() {
    return convertString( getParameterDesc().Name );
}
wstring EffectShaderVariableDX9Imp::getSemanticName() {
    return convertString( getParameterDesc().Semantic );
}
size_t EffectShaderVariableDX9Imp::getNumberOfAnnotations() {
    return getParameterDesc().Annotations;
}
size_t EffectShaderVariableDX9Imp::getNumberOfNestedVariables() {
    return getParameterDesc().StructMembers;
}
bool EffectShaderVariableDX9Imp::isFloat()  {
    return getParameterDesc().Type == D3DXPT_FLOAT;
}
bool EffectShaderVariableDX9Imp::isTexture()  {
    return getParameterDesc().Type == D3DXPT_TEXTURE;
}
bool EffectShaderVariableDX9Imp::isTexture1D()  {
    return getParameterDesc().Type == D3DXPT_TEXTURE1D;
}
bool EffectShaderVariableDX9Imp::isTexture2D() {
    return getParameterDesc().Type == D3DXPT_TEXTURE2D;
}
bool EffectShaderVariableDX9Imp::isTexture3D() {
    return getParameterDesc().Type == D3DXPT_TEXTURE3D;
}
bool EffectShaderVariableDX9Imp::isTextureCube() {
    return getParameterDesc().Type == D3DXPT_TEXTURECUBE;
}
bool EffectShaderVariableDX9Imp::isSampler()  {
    return getParameterDesc().Type == D3DXPT_SAMPLER;
}
bool EffectShaderVariableDX9Imp::isSampler1D() {
    return getParameterDesc().Type == D3DXPT_SAMPLER1D;
}
bool EffectShaderVariableDX9Imp::isSampler2D() {
    return getParameterDesc().Type == D3DXPT_SAMPLER2D;
}
bool EffectShaderVariableDX9Imp::isSampler3D() {
    return getParameterDesc().Type == D3DXPT_SAMPLER3D;
}
bool EffectShaderVariableDX9Imp::isSamplerCube() {
    return getParameterDesc().Type == D3DXPT_SAMPLERCUBE;
}

D3DXHANDLE EffectShaderVariableDX9Imp::getHandleDX9() {
    return handle_;
}
D3DXHANDLE EffectShaderVariableDX9Imp::getParentHandleDX9() {
    if( NULL == parent_) return 0;
    return parent_->getHandleDX9();
}

bool EffectShaderVariableDX9Imp::setFloat( float newValue )
{
    const HRESULT hr = effect_->SetFloat( getHandleDX9(), newValue );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setFloat" );
    return true;
}

bool EffectShaderVariableDX9Imp::setFloatArray( const float * newValue, size_t count )
{
    const HRESULT hr = effect_->SetFloatArray( getHandleDX9(), newValue, count );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setFloatArray" );
    return true;
}

bool EffectShaderVariableDX9Imp::setBool( bool newValue ) {
    const HRESULT hr = effect_->SetBool( getHandleDX9(), newValue );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setBool" );
    return true;
}
bool EffectShaderVariableDX9Imp::setBoolArray( const bool * newValues, size_t count ) {
    const HRESULT hr = effect_->SetBoolArray( getHandleDX9(), (BOOL*) newValues, count );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setBoolArray" );
    return true;
}
bool EffectShaderVariableDX9Imp::setInt( int newValue ) {
    const HRESULT hr = effect_->SetInt( getHandleDX9(), newValue );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setInt" );
    return true;
}
bool EffectShaderVariableDX9Imp::setIntArray( const int * newValues, size_t count ) {
    const HRESULT hr = effect_->SetIntArray( getHandleDX9(), newValues, count );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setIntArray" );
    return true;
}
bool EffectShaderVariableDX9Imp::setString( wstring newValue ) {
    const HRESULT hr = effect_->SetString( getHandleDX9(), convertString( newValue ).c_str() );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setString" );
    return true;
}
bool EffectShaderVariableDX9Imp::setTexture( Texture * newTexture ) {
    // I need to find a better way to avoid down casting here.
    TextureDX9 * const newTextureDX9 = dynamic_cast< TextureDX9 * >( newTexture );
    const HRESULT hr = effect_->SetTexture( getHandleDX9(), newTextureDX9->getTextureDX9() );
    RETURN_FALSE_IF_FAILED( hr, L"EffectShaderVariableDX9Imp::setTexture" );
    return true;
}



}