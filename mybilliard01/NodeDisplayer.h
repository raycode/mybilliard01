#pragma once


class NodeDisplayer : IMPLEMENTS_INTERFACE( EffectShaderCallBack ) {
public: // from EffectShaderCallBack
    virtual void displayPass( size_t pass ) OVERRIDE;

public:
    NodeDisplayer( Displayable *, bool bPositionOnly );

private:
    Displayable * const node_;
    bool bPositionOnly_;
};

