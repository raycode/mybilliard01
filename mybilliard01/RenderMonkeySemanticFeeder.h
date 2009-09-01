#pragma once


class RenderMonkeySemanticFeeder
    : IMPLEMENTS_INTERFACE( EffectShaderFeeder )
    , IMPLEMENTS_INTERFACE( EffectShaderCallBack )
{
public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public: // from EffectShaderFeeder
    void display() OVERRIDE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public:
    RenderMonkeySemanticFeeder( Node *, EffectShader *, Texture * shadowMap );

private: // update and set
    void initPredefinedSemantics();
    void updateMatrixForPredefinedSemantic( int whichSemantic );
    void updateVec4ForPredefinedSemantic( int whichSemantic );
    void uploadValue( int whichSemantic, size_t count );

private: // input
    Node * const node_;
    EffectShader * const effect_;
    Texture * const shadowMap_;

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
    typedef float TemporaryStorage[16];
    TemporaryStorage temporaryStorage16f[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

};

