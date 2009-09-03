#pragma once


class RenderMonkeySharedSemanticsFeeder : IMPLEMENTS_INTERFACE( GlobalEffectShaderFeeder ) {
public: // from EffectShaderFeeder
    virtual void displayWithEffect( const RowMajorMatrix44f & matWorld ) OVERRIDE {}
    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE;
    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public:
    void appendSharedVariable( ShaderVariable * );

private: // update and set
    void updateMatrixForPredefinedSemantic( int whichSemantic );
    void updateVec4ForPredefinedSemantic( int whichSemantic );
    void upload( int whichSemantic, size_t count );

private: // input - matrices
    NxVec3 cameraPos_, cameraDir_;
    RowMajorMatrix44f matWorld_, matView_, matProj_, matProjView_;

private: // render monkey semantics
    ShaderVariable * predefinedVariables_[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];

    typedef vector< int > ActiveSemanticFlags;
    ActiveSemanticFlags activeSemantics_Matrix_;
    ActiveSemanticFlags activeSemantics_Vec4_;

    void setSharedVariable( int whichSemantic, ShaderVariable * var, ActiveSemanticFlags &whereToStore );

    typedef float PredefinedSemantics_Matrix44f[16];
    PredefinedSemantics_Matrix44f predefinedSemantics_Matrix44f_[ RenderMonkeySemantics::SIZE_OF_SEMANTICS ];
};
