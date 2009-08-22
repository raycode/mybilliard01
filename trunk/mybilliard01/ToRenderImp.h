#pragma once


class ToRenderImp : IMPLEMENTS_INTERFACE( ToRender ) 
{
public: // from EffectShaderVariableBlockCallBack
    virtual void setEffectShaderVariableBlock() OVERRIDE;

public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public:
    ToRenderImp( Node *, EffectShader * );

    void updateMatrix( NxActor *, const RowMajorMatrix44f & matView, const RowMajorMatrix44f & matProjView ) OVERRIDE;

    void display() OVERRIDE;

private: // input
    Node * const node_;
    EffectShader * const effect_;
    EffectShaderVariableBlock * block_;

private: // shader variables
    ShaderVariable * wvp_, * world_;

private: // matrices
    float columnMajor44_World_[16];
    float columnMajor44_View_[16];
    float columnMajor44_WVP_[16];
};

