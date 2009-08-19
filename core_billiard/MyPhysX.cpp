#include "stdafx.h"
#include "my_phys.h"
namespace my_phys {

MyPhysX::MyPhysX( NxUserOutputStream * userOutputStream )
{
    // Initialize PhysicsSDK
    NxPhysicsSDKDesc desc;
    NxSDKCreateError errorCode = NXCE_NO_ERROR;
    physicsSDK_ = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, userOutputStream, desc, &errorCode);
    if( NULL == physicsSDK_ ) 
        throw exception();

    // Create a scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
    scene_ = physicsSDK_->createScene(sceneDesc);
    if( NULL == scene_ ) 
        throw exception();
}

MyPhysX::~MyPhysX()
{
    if( NULL == physicsSDK_ ) return;

    if( NULL != scene_ ) physicsSDK_->releaseScene(*scene_);
    NxReleasePhysicsSDK(physicsSDK_);
}

bool MyPhysX::loadColladaFile( wstring filename, NXU_userNotify * userNotify ) {
    wchar_t LoadFilename[512];
    FindMediaFile( filename.c_str(), LoadFilename);
    NXU::NxuPhysicsCollection * const collection
        = NXU::loadCollection( convertString( LoadFilename ).c_str(), NXU::FT_COLLADA );
    if( NULL == collection ) return false;
    const bool success = NXU::instantiateCollection( collection, *physicsSDK_, scene_, NULL, userNotify );
    NXU::releaseCollection( collection );
    return success;
}

size_t MyPhysX::getNumberOfActors() const {
    return scene_->getNbActors();
}

NxActor * MyPhysX::getActor( size_t index ) {
    return scene_->getActors()[ index ];
}

void MyPhysX::simulate( float elapsedTime ) {
    scene_->simulate( elapsedTime );
    scene_->flushStream();
}

void MyPhysX::fetchResult() {
    scene_->fetchResults( NX_RIGID_BODY_FINISHED, true );
}

bool MyPhysX::isSimulationDone() {
    return scene_->checkResults( NX_RIGID_BODY_FINISHED, false );
}

}
