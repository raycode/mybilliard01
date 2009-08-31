#pragma once

class MyShadowDisplayer
    : IMPLEMENTS_INTERFACE( RenderTargetCallBack )
    , IMPLEMENTS_INTERFACE( EffectShaderCallBack )
{
public: // from RenderTargetCallBack
    virtual void display( Render * ) OVERRIDE;

public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public:
    MyShadowDisplayer( GlobalEffectShaderFeeder * feeder, const set< NxActor * > & );

private:
    GlobalEffectShaderFeeder * feeder_;
    const set< NxActor * > & nodes_;

private:
    Node * currentNode_;
};