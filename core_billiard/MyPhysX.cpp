#include "stdafx.h"
namespace my_phys_x {

// Rendering
static NxVec3	gEye(50.0f, 50.0f, 50.0f);
static NxVec3	gDir(-0.6f,-0.2f,-0.7f);
static NxVec3	gViewY;
static int		gMouseX = 0;
static int		gMouseY = 0;

MyPhysX::MyPhysX()
{
    // Initialize PhysicsSDK
    NxPhysicsSDKDesc desc;
    NxSDKCreateError errorCode = NXCE_NO_ERROR;
    physicsSDK_ = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, new ErrorStream(), desc, &errorCode);
    if(physicsSDK_ == NULL) 
        throw exception();

    // Create a scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity				= NxVec3(0.0f, -9.81f, 0.0f);
    scene_ = physicsSDK_->createScene(sceneDesc);
    if(scene_ == NULL) 
        throw exception();
}

MyPhysX::~MyPhysX()
{
    if( NULL == physicsSDK_ )
        return;

    if( NULL != scene_ )
        physicsSDK_->releaseScene(*scene_);

    NxReleasePhysicsSDK(physicsSDK_);
}

void MyPhysX::loadColladaFile( wstring filename ) {

}

size_t MyPhysX::countActors() const {
    return 0;
}

NxActor * MyPhysX::getActor( size_t index ) {
    return NULL;
}


}
