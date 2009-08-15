#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderDX9Imp::EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice )
: d3dDevice_( d3dDevice )
, effect_( NULL )
{
}

ShaderVariable * EffectShaderDX9Imp::createVariable( wstring name )
{
    D3DXHANDLE newHandle = getParameterByName( name );
    ShaderVariableDX9 * const newVariable = new ShaderVariableDX9Imp( name, newHandle );
    shaderVariables_.push_back( ShaderVariablePtr( newVariable ) );
    return newVariable;
}

ShaderVariable * EffectShaderDX9Imp::createTechniqueVariable( wstring name )
{
    D3DXHANDLE newHandle = getTechniqueByName( name );
    ShaderVariableDX9 * const newVariable = new ShaderVariableDX9Imp( name, newHandle );
    shaderVariables_.push_back( ShaderVariablePtr( newVariable ) );
    return newVariable;
}

bool EffectShaderDX9Imp::releaseShaderVariable( ShaderVariable * variable )
{
    MY_FOR_EACH( ShaderVariables, iter, shaderVariables_ ) {
        if( variable != &**iter ) continue;
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
    const HRESULT hr = effect_->SetString( varDX9->getHandleDX9(), convertString( newValue ).c_str() );
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

HRESULT EffectShaderDX9Imp::createEffectFromFile( wstring filename )
{
    filename_ = filename;

    ID3DXBuffer * error = NULL;
    const HRESULT hr = D3DXCreateEffectFromFile( d3dDevice_, filename_.c_str(), NULL, NULL, 0, NULL, &effect_, &error );

    if( NULL != error ) {
        DXUT_ERR( (wchar_t*) error->GetBufferPointer(), hr );
        SAFE_RELEASE( error );
        return hr;
    }

    if( FAILED( hr ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::createEffectFromFile", hr );
        return hr;
    }

    return S_OK;
}

D3DXHANDLE EffectShaderDX9Imp::getParameterByName( wstring name )
{
    return effect_->GetParameterByName( 0, convertString( name ).c_str() );
}

D3DXHANDLE EffectShaderDX9Imp::getTechniqueByName( wstring name )
{
    return effect_->GetTechniqueByName( convertString( name ).c_str() );
}


}