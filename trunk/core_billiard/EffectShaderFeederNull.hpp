#pragma once
namespace my_render {


NULL_OBJECT( EffectShaderFeeder ) {

    void displayWithEffect() OVERRIDE {}

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE {}

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matWorld,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE {}

    virtual EffectShader * getEffectShader() OVERRIDE { return NULL; }

};

}

