#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderDX9Imp::EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice,
                                       wstring filename, LPD3DXEFFECTPOOL effectPool )
: d3dDevice_( d3dDevice )
, effectPool_( effectPool )
, filename_( filename )
, effect_( NULL )
{
}

EffectShaderDX9Imp::~EffectShaderDX9Imp() {
    releaseResource();
}

bool EffectShaderDX9Imp::acquireResource()
{
    ID3DXBuffer * error = NULL;
    const HRESULT hr = D3DXCreateEffectFromFile( d3dDevice_, filename_.c_str(), NULL, NULL, 0, effectPool_, &(effect_), &error );

    if( NULL != error ) {
        DXUT_ERR( (wchar_t*) error->GetBufferPointer(), hr );
        SAFE_RELEASE( error );
        return false;
    }

    if( FAILED( hr ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::acquireResource", hr );
        return false;
    }
    assert( effect_ );

    MY_FOR_EACH( EffectVariables, iter, effectVariables_ )
        setEffectOntoEffectVariable( &**iter );

    return acquireBestValidTechnique();
}

void EffectShaderDX9Imp::setEffectOntoEffectVariable( ReleasableEffectResourceDX9 * var ) {
    assert( var );
    if( NULL == effect_ ) return;
    var->setEffect( effect_ );
    var->acquireResource();
}

bool EffectShaderDX9Imp::acquireBestValidTechnique()
{
    const HRESULT hr1 = effect_->FindNextValidTechnique( NULL, & bestTechnique_ );
    if( FAILED( hr1 ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::acquireBestValidTechnique", hr1 );
        return false;
    }

    const HRESULT hr2 = effect_->SetTechnique( bestTechnique_ );
    if( FAILED( hr2 ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::acquireBestValidTechnique", hr2 );
        return false;
    }

    return true;
}

void EffectShaderDX9Imp::releaseResource()
{
    MY_FOR_EACH( EffectVariables, iter, effectVariables_ )
        (*iter)->releaseResource();
    (effectVariables_).clear();
}

bool EffectShaderDX9Imp::releaseAnyEffectVariable( ReleasableEffectResourceDX9 * var ) {
    MY_FOR_EACH( EffectVariables, iter, effectVariables_ ) {
        if( var != &**iter ) continue;
        (*iter)->releaseResource();
        (effectVariables_).erase( iter );
        return true;
    }
    return false;
}

bool EffectShaderDX9Imp::releaseShaderVariable( ShaderVariable * variable ) {
    return releaseAnyEffectVariable( dynamic_cast< ReleasableEffectResourceDX9 * >( variable ) );
}

bool EffectShaderDX9Imp::releaseShaderVariableBlock( EffectShaderVariableBlock * block ) {
    return releaseAnyEffectVariable( dynamic_cast< ReleasableEffectResourceDX9 * >( block ) );
}

bool EffectShaderDX9Imp::renderWithTechnique( EffectShaderCallBack * callBack )
{
    assert( NULL != callBack );

    UINT nPass;
    const HRESULT hr1 = effect_->Begin( & nPass, 0 );
    if( FAILED( hr1 ) ) {
        DXUT_ERR( L"EffectShaderDX9Imp::renderWithTechnique" , hr1 );
        return false;
    }

    for( size_t i = 0; i < nPass; ++i )
    {
        const HRESULT hr2 = effect_->BeginPass( i );
        if( FAILED( hr2 )  ) {
            DXUT_ERR( L"EffectShaderDX9Imp::renderWithTechnique", hr2 );
            continue;
        }

        callBack->displayPass( i );

        effect_->EndPass();
    }

    effect_->End();
    return true;
}


ShaderVariable * EffectShaderDX9Imp::createVariableByIndex( size_t index )
{
    EffectShaderVariableDX9 * const newVariable
        = new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_INDEX, index, NULL );
    effectVariables_.push_back( ReleasableEffectResourceDX9Ptr( newVariable ) );
    setEffectOntoEffectVariable( newVariable );
    return newVariable;
}
ShaderVariable * EffectShaderDX9Imp::createVariableByName( wstring name )
{
    EffectShaderVariableDX9 * const newVariable
        = new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_NAME, name, NULL );
    effectVariables_.push_back( ReleasableEffectResourceDX9Ptr( newVariable ) );
    setEffectOntoEffectVariable( newVariable );
    return newVariable;
}

ShaderVariable * EffectShaderDX9Imp::createVariableBySemantic( wstring semantic )
{
    EffectShaderVariableDX9 * const newVariable
        = new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_SEMANTIC, semantic, NULL );
    effectVariables_.push_back( ReleasableEffectResourceDX9Ptr( newVariable ) );
    setEffectOntoEffectVariable( newVariable );
    return newVariable;
}

EffectShaderVariableBlock * EffectShaderDX9Imp::createVariableBlock( EffectShaderVariableBlockCallBack * callBack )
{
    if( NULL == callBack ) return NULL;
    EffectShaderVariableBlockDX9 * const newBlock = new EffectShaderVariableBlockDX9Imp( this, callBack );
    effectVariables_.push_back( ReleasableEffectResourceDX9Ptr( newBlock ) );
    setEffectOntoEffectVariable( newBlock );
    return newBlock;
}

size_t EffectShaderDX9Imp::getNumberOfVariables()
{
    D3DXEFFECT_DESC desc;
    effect_->GetDesc( & desc );
    return desc.Parameters;
}

wstring EffectShaderDX9Imp::getFilename() const {
    return filename_;
}


}
