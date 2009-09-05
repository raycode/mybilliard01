#pragma once


class NodeDisplayer : IMPLEMENTS_INTERFACE( EffectShaderCallBack ) {
public: // from EffectShaderCallBack
    virtual void displayPass( size_t pass ) OVERRIDE;

public:
    NodeDisplayer( Node *, bool bPositionOnly );

private:
    Node * const node_;
    bool bPositionOnly_;
};

