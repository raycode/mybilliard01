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
    void collectPredefinedSemantics();
    void initRenderTargets();
    void updateMatrixForPredefinedSemantic( int whichSemantic );
    void updateVec4ForPredefinedSemantic( int whichSemantic );
    void uploadValue( int whichSemantic, size_t count );

private: // input
    EffectShader * effect_;
    bool bShared_;

private: // input - matrices
    NxVec3 cameraPos_, cameraDir_;
    RowMajorMatrix44f matWorld_, matView_, matProj_, matProjView_;

private: // render monkey semantics
    ShaderVariable * predefinedVariables_[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

    typedef vector< int > ActiveSemanticFlags;
    ActiveSemanticFlags activeSemantics_Matrix_;
    ActiveSemanticFlags activeSemantics_Vec4_;

    bool initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, ActiveSemanticFlags & whereToStore );

private: 
    typedef float TemporaryStorage[ 16 ];
    TemporaryStorage temporaryStorage16f[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

};

