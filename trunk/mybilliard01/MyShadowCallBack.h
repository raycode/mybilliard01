#pragma once

class MyShadowCallBack
    : IMPLEMENTS_INTERFACE( RenderTargetCallBack )
    , IMPLEMENTS_INTERFACE( EffectShaderCallBack )
{
public: // from RenderTargetCallBack
    virtual void display( Render * ) OVERRIDE;

public: // from EffectShaderCallBack
    void displayPass( size_t pass ) OVERRIDE;

public:
    typedef map< NxActor *, Node * > NodeMap;
    typedef set< NxActor * > ActorGroup;

    MyShadowCallBack( GlobalEffectShaderFeeder * feeder, const ActorGroup *, const NodeMap * );

private:
    GlobalEffectShaderFeeder * feeder_;
    const ActorGroup * const actors_;
    const NodeMap * const nodeMap_;

private:
    Node * currentNode_;
};