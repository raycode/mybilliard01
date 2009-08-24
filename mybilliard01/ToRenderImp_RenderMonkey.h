#pragma once


#define ADD_SEMANTIC( NEW_SEMANTIC ) NEW_SEMANTIC, NEW_SEMANTIC##Transpose, NEW_SEMANTIC##Inverse, NEW_SEMANTIC##InverseTranspose


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
    ToRenderImp_RenderMonkey( Node *, EffectShader * );

private:
    void initPredefinedSemantics();
    void updateMatrixForPredefinedSemantics( int whichSemantic );
    void setMatrixForPredefinedSemantics( int whichSemantic );
    void setVec4ForPredefinedSemantics( int whichSemantic );

private: // input
    Node * const node_;
    EffectShader * const effect_;

private:
    enum { ADD_SEMANTIC( ViewPosition ), ADD_SEMANTIC( ViewDirection),
        ADD_SEMANTIC( World ), ADD_SEMANTIC( View ), ADD_SEMANTIC( Projection ),
        ADD_SEMANTIC( ViewProjection ), ADD_SEMANTIC( WorldView ), ADD_SEMANTIC( WorldViewProjection ),
        SIZE_OF_SEMANTICS };
    ShaderVariable * predef_[ SIZE_OF_SEMANTICS ];

    typedef vector< int > MatrixSemantics;
    MatrixSemantics matrixSemantics_;

    typedef vector< int > Vec4Semantics;
    Vec4Semantics vec4Semantics_;

private: // matrices
    NxVec3 cameraPos_, cameraDir_;
    RowMajorMatrix44f matWorld_, matView_, matProj_, matProjView_;

    typedef float ColMajorMatrix44f[16];
    ColMajorMatrix44f colMat44fs_[ SIZE_OF_SEMANTICS ];
};

