#pragma once


class RenderMonkeySemanticFeeder
    : IMPLEMENTS_INTERFACE( EffectShaderFeeder )
{
public: // from EffectShaderFeeder
    virtual void setEffectShader( EffectShader * ) OVERRIDE;

    virtual EffectShader * getEffectShader() OVERRIDE;

    virtual void updateCameraProjection( const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE;

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) OVERRIDE;

public:
    RenderMonkeySemanticFeeder( bool bShared );

private: // update and set
    void initPredefinedSemantics();
    bool initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, size_t countOfFloat );
    void initRenderTargets();
    void updateForPredefinedSemantic( int whichSemantic );
    void uploadValue( int whichSemantic );

private: // input
    EffectShader * effect_;
    bool bShared_;

private: // input - matrices
    NxVec3 cameraPos_, cameraDir_;
    RowMajorMatrix44f matWorld_, matView_, matProj_, matProjView_;

private: // render monkey semantics
    ShaderVariable * predefinedVariables_[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

    typedef vector< int > ActiveSemanticFlags;
    ActiveSemanticFlags activeSemantics_;

private: 
    typedef vector< float > TemporaryStorage;
    TemporaryStorage temporaryStorage_[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

};

