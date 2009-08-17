#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderDX9Imp::EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice, wstring filename )
: d3dDevice_( d3dDevice )
, filename_( filename )
, effect_( NULL )
{
}

EffectShaderDX9Imp::~EffectShaderDX9Imp() {
    releaseResource();
}

bool EffectShaderDX9Imp::acquireResource()
{
    releaseResource();
    ID3DXBuffer * error = NULL;
    const HRESULT hr = D3DXCreateEffectFromFile( d3dDevice_, filename_.c_str(), NULL, NULL, 0, NULL, &effect_, &error );

    if( NULL != error ) {
        DXUT_ERR( (wchar_t*) error->GetBufferPointer(), hr );
        SAFE_RELEASE( error );
        return false;
    }

    if( FAILED( hr ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::acquireResource", hr );
        return false;
    }

    MY_FOR_EACH( ShaderVariables, iter, shaderVariables_ ) {
        (*iter)->setEffect( effect_ );
        (*iter)->acquireResource();
    }

    return true;
}

void EffectShaderDX9Imp::releaseResource()
{
    MY_FOR_EACH( ShaderVariables, iter, shaderVariables_ ) {
        (*iter)->releaseResource();
    }

    SAFE_RELEASE( effect_ );
}


ShaderVariable * EffectShaderDX9Imp::createVariable( wstring name )
{
    ShaderVariableEffectDX9 * const newVariable
        = new ShaderVariableEffectDX9Imp( name, ShaderVariableEffectDX9Imp::ETYPE_PARAM );
    shaderVariables_.push_back( ShaderVariableEffectDX9Ptr( newVariable ) );

    if( NULL != effect_ ) {
        newVariable->setEffect( effect_ );
        newVariable->acquireResource();
    }
    return newVariable;
}

ShaderVariable * EffectShaderDX9Imp::createTechniqueVariable( wstring name )
{
    ShaderVariableEffectDX9 * const newVariable
        = new ShaderVariableEffectDX9Imp( name, ShaderVariableEffectDX9Imp::ETYPE_TECHNIQUE );
    shaderVariables_.push_back( ShaderVariableEffectDX9Ptr( newVariable ) );

    if( NULL != effect_ ) {
        newVariable->setEffect( effect_ );
        newVariable->acquireResource();
    }
    return newVariable;
}

bool EffectShaderDX9Imp::releaseShaderVariable( ShaderVariable * variable )
{
    MY_FOR_EACH( ShaderVariables, iter, shaderVariables_ ) {
        if( variable != &**iter ) continue;
        (*iter)->releaseResource();
        shaderVariables_.erase( iter );
        return true;
    }
    return false;
}

bool EffectShaderDX9Imp::setFloat( ShaderVariable * variable, float newValue )
{
    ShaderVariableDX9 * const varDX9 = (ShaderVariableDX9 *) variable;
    const HRESULT hr = effect_->SetFloat( varDX9->getHandleDX9(), newValue );
    return S_OK == hr;
}

bool EffectShaderDX9Imp::setFloatArray( ShaderVariable * variable, const float * newValue, size_t siz )
{
    ShaderVariableDX9 * const varDX9 = (ShaderVariableDX9 *) variable;
    const HRESULT hr = effect_->SetFloatArray( varDX9->getHandleDX9(), newValue, siz );
    return S_OK == hr;
}

bool EffectShaderDX9Imp::setString( ShaderVariable * variable, wstring newValue )
{
    ShaderVariableDX9 * const varDX9 = (ShaderVariableDX9 *) variable;
    string szNewValue = convertString( newValue );
    const HRESULT hr = effect_->SetString( varDX9->getHandleDX9(), szNewValue.c_str() );
    return S_OK == hr;
}

bool EffectShaderDX9Imp::setTexture( ShaderVariable * variable, Texture * tex )
{
    //const HRESULT hr = effect_->SetTexture( getParameterByName( variable ), newValue );
    //return S_OK == hr;
    return false;
}

bool EffectShaderDX9Imp::setVertexShader( ShaderVariable * variable, VertexShader * vb )
{
    //VertexShaderDX9 * const vbDX9 = dynamic_cast< VertexShaderDX9 * >( vb );
    //const HRESULT hr = effect_->SetFloat( getParameterByName( variable ), newValue );
    //return S_OK == hr;
    return false;
}

bool EffectShaderDX9Imp::setPixelShader( ShaderVariable * variable, PixelShader * )
{
    return false;
}

bool EffectShaderDX9Imp::setTechnique( ShaderVariable * variable )
{
    ShaderVariableDX9 * const varDX9 = static_cast< ShaderVariableDX9 * >( variable );
    const HRESULT hr = effect_->SetTechnique( varDX9->getHandleDX9() );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::setTechnique", hr );
        return false;
    }
    return true;
}


bool EffectShaderDX9Imp::isValidTechnique( ShaderVariable * variable )
{
    ShaderVariableDX9 * const varDX9 = static_cast< ShaderVariableDX9 * >( variable );
    const HRESULT hr = effect_->ValidateTechnique( varDX9->getHandleDX9() );
    if( FAILED( hr ) ) {
        return false;
    }
    return true;
}

size_t EffectShaderDX9Imp::begin()
{
    UINT count;
    const HRESULT hr = effect_->Begin( &count, 0 );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::begin", hr );
        return 0;
    }
    return count;
}

void EffectShaderDX9Imp::end()
{
    effect_->End();
}

void EffectShaderDX9Imp::beginPass( size_t whichPass )
{
    effect_->BeginPass( whichPass );
}

void EffectShaderDX9Imp::endPass()
{
    effect_->EndPass();
}



}