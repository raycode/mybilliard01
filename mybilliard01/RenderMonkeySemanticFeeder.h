#pragma once


class RenderMonkeySemanticFeeder
    : IMPLEMENTS_INTERFACE( EffectShaderFeeder )
    , IMPLEMENTS_INTERFACE( EffectShaderCameraFeeder )
{
public: // from EffectShaderCameraFeeder
    virtual void updateProjection_camera( const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateView_camera(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public: // from EffectShaderFeeder
    virtual void setEffectShader( EffectShader * ) OVERRIDE;

    virtual EffectShader * getEffectShader() OVERRIDE;

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE;

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) OVERRIDE;

public:
    RenderMonkeySemanticFeeder( bool bShared );

private: // update and set
    void initPredefinedSemantics();
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

#define MATRIX_SEMANTIC( NEW_SEMANTIC ) NEW_SEMANTIC, NEW_SEMANTIC##Transpose, NEW_SEMANTIC##Inverse, NEW_SEMANTIC##InverseTranspose

    enum {
        ViewPosition,
        ViewDirection,

        ViewportWidthInverse,
        ViewportHeightInverse,

        MATRIX_SEMANTIC( World ),
        MATRIX_SEMANTIC( View ),
        MATRIX_SEMANTIC( Projection ),
        MATRIX_SEMANTIC( ViewProjection ),
        MATRIX_SEMANTIC( WorldView ),
        MATRIX_SEMANTIC( WorldViewProjection ),
        SIZE_OF_RENDERMONKEY_SEMANTICS_ENUM };

#undef MATRIX_SEMANTIC

    ShaderVariable * predefinedVariables_[ SIZE_OF_RENDERMONKEY_SEMANTICS_ENUM ];

    typedef set< int > ActiveSemanticFlags;
    ActiveSemanticFlags activeSemantics_Projection_, activeSemantics_Camera_, activeSemantics_Model_;

    bool initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, ActiveSemanticFlags & whereToStore, size_t countOfFloat );

private: 
    typedef vector< float > TemporaryStorage;
    TemporaryStorage temporaryStorage_[ SIZE_OF_RENDERMONKEY_SEMANTICS_ENUM ];

};

