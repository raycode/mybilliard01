#pragma once


NULL_OBJECT( ToRender ) {

    void display() {}
    void displayPass( size_t pass ) {}

    void updateMatrix( NxActor *, const RowMajorMatrix44f &, const RowMajorMatrix44f & ) {}

    virtual void setEffectShaderVariableBlock() OVERRIDE {}

private:
    ShaderVariableNull nullShaderVariable_;

};

