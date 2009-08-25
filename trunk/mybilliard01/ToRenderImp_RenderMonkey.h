#pragma once


class ToRenderImp_RenderMonkey : IMPLEMENTS_INTERFACE( ToRender ) {
public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public: // from ToRender
    void display() OVERRIDE;

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matProj,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public:
    ToRenderImp_RenderMonkey( Node *, EffectShader *, RenderBufferFactory * renderFactory );

    static const wstring effectFilename;

private: // predefined semantics
    void initPredefinedSemantics();
    void updateMatrixForPredefinedSemantic( int whichSemantic );
    void setMatrixForPredefinedSemantic( int whichSemantic );
    void setVec4ForPredefinedSemantic( int whichSemantic );

private: // input
    Node * const node_;
    EffectShader * const effect_;
    RenderBufferFactory * const renderFactory_;

private: // matrices
    NxVec3 cameraPos_, cameraDir_;
    RowMajorMatrix44f matWorld_, matView_, matProj_, matProjView_;

private: // render monkey semantics

#define MATRIX_SEMANTIC( NEW_SEMANTIC ) NEW_SEMANTIC, NEW_SEMANTIC##Transpose, NEW_SEMANTIC##Inverse, NEW_SEMANTIC##InverseTranspose

    enum { ViewPosition,
        ViewDirection,
        MATRIX_SEMANTIC( World ),
        MATRIX_SEMANTIC( View ),
        MATRIX_SEMANTIC( Projection ),
        MATRIX_SEMANTIC( ViewProjection ),
        MATRIX_SEMANTIC( WorldView ),
        MATRIX_SEMANTIC( WorldViewProjection ),
        SIZE_OF_SEMANTICS };
    ShaderVariable * predef_[ SIZE_OF_SEMANTICS ];

    typedef vector< int > ActivePredefinedSemantics_Matrix;
    ActivePredefinedSemantics_Matrix activePredefinedSemantics_Matrix_;

    typedef vector< int > ActivePredefinedSemantics_Vec4;
    ActivePredefinedSemantics_Vec4 activePredefinedSemantics_Vec4_;

    typedef float PredefinedSemantics_Matrix44f[16];
    PredefinedSemantics_Matrix44f predefinedSemantics_Matrix44f_[ SIZE_OF_SEMANTICS ];

};

