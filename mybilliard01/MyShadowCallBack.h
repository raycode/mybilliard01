#pragma once

class MyShadowCallBack
    : IMPLEMENTS_INTERFACE( RenderTargetCallBack )
    , IMPLEMENTS_INTERFACE( EffectShaderCallBack )
{
public: // from RenderTargetCallBack
    virtual void drawOnRenderTarget( Render * ) OVERRIDE;

public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public:
    typedef map< NxActor *, Node * > NodeMap;

    MyShadowCallBack( GlobalEffectShaderFeeder * feeder, const NodeMap * );

private:
    GlobalEffectShaderFeeder * feeder_;
    const NodeMap * const nodeMap_;

private:
    Node * currentNode_;
};