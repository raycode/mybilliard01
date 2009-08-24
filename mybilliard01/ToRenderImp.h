#pragma once


class ToRenderImp : IMPLEMENTS_INTERFACE( ToRender ) 
{
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
    ToRenderImp( Node *, EffectShader * );

private: // input
    Node * const node_;
    EffectShader * const effect_;

private: // shader variables
    ShaderVariable * wvp_, * world_;

private: // matrices
    float columnMajor44_World_[16];
    float columnMajor44_View_[16];
    float columnMajor44_WVP_[16];
};

