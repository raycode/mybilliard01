#pragma once


class MyEffectShaderFeederImp
    : public RenderMonkeySemanticFeeder
    , IMPLEMENTS_INTERFACE( MyEffectShaderFeeder )
{
public: // EffectShaderShadowMapFeeder
    virtual void updateProjection_shadowMap( size_t index, const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateView_shadowMap(
        size_t index,
        const NxVec3 & lightPos,
        const NxVec3 & lightDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public: // from EffectShaderFeeder
    virtual void setEffectShader( EffectShader * ) OVERRIDE;
    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE;

public:
    MyEffectShaderFeederImp( bool bShared );

private:

    enum ShadowMapSemanticEnum {
        Position,
        DIrection,

        World,
        View,
        Projection,
        WorldView,
        ViewProjection,
        WorldViewProjection,
        SIZE_OF_SHADOWMAP_SEMANTIC_ENUM
    };
    
    struct ShadowMapSemantic
    {
        NxVec3 lightPos_, lightDir_;
        RowMajorMatrix44f matView_, matProj_, matProjView_;

        ShaderVariable * shaderVariables_[ SIZE_OF_SHADOWMAP_SEMANTIC_ENUM ];

        typedef set< int > ActiveSemantics;
        ActiveSemantics activeSemantics_proj_, activeSemantics_view_, activeSemantics_world_;

        ShadowMapSemantic() { memset( (void*) shaderVariables_, NULL, sizeof( shaderVariables_ ) ); }
    };

    void initShadowMapSemantics( EffectShader * );
    void uploadShadowMapValue( size_t index, int whichSemantic );

private:
    RowMajorMatrix44f matWorld_;
    typedef vector< ShadowMapSemantic > ShadowMapSemantics;
    ShadowMapSemantics shadowMaps_;

};

