#pragma once


NULL_OBJECT( ToRender ) {

    void display() OVERRIDE {}
    void displayPass( size_t pass ) OVERRIDE {}

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matProj,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE {};

};

