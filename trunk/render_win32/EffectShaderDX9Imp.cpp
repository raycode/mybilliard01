#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShaderDX9Imp::EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice,
                                       wstring filename, LPD3DXEFFECTPOOL effectPool,
                                       RenderBufferFactory * renderFactory )
: d3dDevice_( d3dDevice )
, effectPool_( effectPool )
, renderFactory_ ( renderFactory )
, filename_( filename )
, effectVariables_( new EffectVariables() )
, borrwoedTextures_( new BorrowedTextures() )
{
}

bool EffectShaderDX9Imp::acquireResource()
{
    if( NULL == effect_ ) {

        DWORD dwFlags = 0;

#if defined( _DEBUG ) || defined( DEBUG )
        dwFlags |= D3DXSHADER_DEBUG | D3DXSHADER_OPTIMIZATION_LEVEL0;
#endif

        ID3DXBuffer * error = NULL;
        ID3DXEffect * effect;
        const HRESULT hr = D3DXCreateEffectFromFile( d3dDevice_, filename_.c_str(), NULL, NULL, dwFlags, effectPool_, & effect, & error );

        if( NULL != error ) {
            DXUT_ERR( (wchar_t*) error->GetBufferPointer(), hr );
            SAFE_RELEASE( error );
            return false;
        }
        RETURN_FALSE_IF_FAILED( hr, L"EffectShaderDX9Imp::acquireResource" );
        assert( effect );

        effect_ = ID3DXEffectPtr( effect, ComReleaser< ID3DXEffect >() );
        effect_->GetDesc( & effectDesc_ );

        acquireBestValidTechnique();
        acquireTextures();
    }

    MY_FOR_EACH( EffectVariables, iter, *effectVariables_ )
        setEffectOntoEffectVariable( &**iter );

    return true;
}

bool EffectShaderDX9Imp::setEffectOntoEffectVariable( ReleasableEffectResourceDX9 * var ) {
    assert( var );
    if( NULL == effect_ ) return false;
    var->setEffect( &*effect_ );
    return var->acquireResource();
}

bool EffectShaderDX9Imp::acquireBestValidTechnique()
{
    const HRESULT hr1 = effect_->FindNextValidTechnique( NULL, & bestTechnique_ );
    RETURN_FALSE_IF_FAILED( hr1, L"EffectShaderDX9Imp::acquireBestValidTechnique" );

    const HRESULT hr2 = effect_->SetTechnique( bestTechnique_ );
    RETURN_FALSE_IF_FAILED( hr2, L"EffectShaderDX9Imp::acquireBestValidTechnique" );

    return true;
}

void EffectShaderDX9Imp::releaseResource()
{
    (*effectVariables_).clear();
    effect_.reset();
}

bool EffectShaderDX9Imp::releaseAnyEffectVariable( ReleasableEffectResourceDX9 * var ) {
    return remove_only_one_pointer< EffectVariables >( *effectVariables_, var );
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
    RETURN_FALSE_IF_FAILED( hr1, L"EffectShaderDX9Imp::renderWithTechnique"  );

    for( size_t i = 0; i < nPass; ++i )
    {
        const HRESULT hr2 = effect_->BeginPass( i );
        RETURN_FALSE_IF_FAILED( hr2, L"EffectShaderDX9Imp::renderWithTechnique" );

        callBack->displayPass( i );

        effect_->EndPass();
    }

    effect_->End();
    return true;
}


bool EffectShaderDX9Imp::hasVariableByName( wstring name ) {
    return NULL != effect_->GetParameterByName( 0, convertString( name ).c_str() );
}
bool EffectShaderDX9Imp::hasVariableBySemantic( wstring semantic )  {
    return NULL != effect_->GetParameterBySemantic( 0, convertString( semantic ).c_str() );
}

EffectShaderVariable * EffectShaderDX9Imp::createEffectVariableByIndex( size_t index ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_INDEX, index, NULL ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoEffectVariable( &*newVariable ) ) return NULL;
    effectVariables_->push_back( newVariable );
    return &*newVariable;
}
EffectShaderVariable * EffectShaderDX9Imp::createEffectVariableByName( wstring name ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_NAME, name, NULL ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoEffectVariable( &*newVariable ) ) return NULL;
    effectVariables_->push_back( newVariable );
    return &*newVariable;
}
EffectShaderVariable * EffectShaderDX9Imp::createEffectVariableBySemantic( wstring semantic ) {
    EffectShaderVariableDX9Ptr newVariable = EffectShaderVariableDX9Ptr( new EffectShaderVariableDX9Imp( EffectShaderVariableDX9Imp::ESEARCH_BY_SEMANTIC, semantic, NULL ), ReleasableResourceDX9::Releaser() );
    if( false == setEffectOntoEffectVariable( &*newVariable ) ) return NULL;
    effectVariables_->push_back( newVariable );
    return &*newVariable;
}
ShaderVariable * EffectShaderDX9Imp::createVariableByIndex( size_t index ) {
    return createEffectVariableByIndex( index );
}
ShaderVariable * EffectShaderDX9Imp::createVariableByName( wstring name ) {
    return createEffectVariableByName( name );
}

ShaderVariable * EffectShaderDX9Imp::createVariableBySemantic( wstring semantic ) {
    return createEffectVariableBySemantic( semantic );
}

EffectShaderVariableBlock * EffectShaderDX9Imp::createVariableBlock( EffectShaderVariableBlockCallBack * callBack )
{
    if( NULL == callBack ) return NULL;
    EffectShaderVariableBlockDX9Ptr newBlock = EffectShaderVariableBlockDX9Ptr( new EffectShaderVariableBlockDX9Imp( this, callBack ), ReleasableResourceDX9::Releaser() );

    if( false == setEffectOntoEffectVariable( &*newBlock ) ) return NULL;
    effectVariables_->push_back( newBlock );
    return &*newBlock;
}

size_t EffectShaderDX9Imp::getNumberOfVariables()
{
    return effectDesc_.Parameters;
}

wstring EffectShaderDX9Imp::getFilename() const {
    return filename_;
}

RenderBufferFactory * EffectShaderDX9Imp::getRenderBufferFactory() {
    return renderFactory_;
}

void EffectShaderDX9Imp::acquireTextures()
{
    DirectoryHelper::ChangeDirectory changePath( getFilename() );
    for( size_t i = 0; i < getNumberOfVariables(); ++i )
    {
        EffectShaderVariablePtr textureVariable = EffectShaderVariablePtr( createEffectVariableByIndex( i ), Shader::Releaser( this ) );

        const bool bTexture = ( textureVariable->isTexture() || textureVariable->isTexture1D() ||
            textureVariable->isTexture2D() || textureVariable->isTextureCube() );
        if( false == bTexture ) continue;

        for( size_t j = 0; j < textureVariable->getNumberOfAnnotations(); ++j ) {
            EffectShaderAnnotationPtr anno = EffectShaderAnnotationPtr( textureVariable->createAnnotationByIndex( j ), EffectShaderVariable::Releaser( textureVariable.get() ) );
            if( false == anno->isString() ) continue;

            const wstring textureFilename = anno->getString();
            TexturePtr newTex = TexturePtr( renderFactory_->createTexture( textureFilename ), RenderBufferFactory::Releaser( renderFactory_ ) );
            if( NULL == newTex ) continue;

            textureVariable->setTexture( newTex.get() );
            borrwoedTextures_->push_back( newTex );
            break;
        }
    }


}


}
