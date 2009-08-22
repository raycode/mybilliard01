#pragma once


NULL_OBJECT( ToRender ) {

    void display() {}
    void displayPass( size_t pass ) {}

    void updateMatrix( NxActor *, const RowMajorMatrix44f &, const RowMajorMatrix44f & ) {}

private:
    ShaderVariableNull nullShaderVariable_;

};

