#pragma once
namespace my_render {


NULL_OBJECT( EffectShaderFeeder ) {

    virtual void setEffectShader( EffectShader * ) OVERRIDE {}
    virtual EffectShader * getEffectShader() OVERRIDE { return NULL; }

    virtual void updateCameraProjection( const RowMajorMatrix44f & matProj ) OVERRIDE {}

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE {}

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE {}

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) OVERRIDE { return false; }


};

}
