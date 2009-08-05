#include "stdafx.h"
#include "NXU_ColladaImport.h"
#include "NXU_helper.h"
#include "MediaPath.h"
namespace my_phys_x {

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
    if( NULL == physicsSDK_ )
        return;

    if( NULL != scene_ )
        physicsSDK_->releaseScene(*scene_);

    NxReleasePhysicsSDK(physicsSDK_);
}

bool MyPhysX::loadColladaFile( wstring filename, NXU_userNotify * userNotify ) {
    wchar_t LoadFilename[512];
    FindMediaFile( filename.c_str(), LoadFilename);
    const string fn = convertString< wstring, string >( LoadFilename );

    NXU::NxuPhysicsCollection * const collection = NXU::loadCollection( fn.c_str(), NXU::FT_COLLADA );
    if( NULL == collection )
        return false;

    const bool success = NXU::instantiateCollection( collection, *physicsSDK_, scene_, NULL, userNotify );
    NXU::releaseCollection( collection );
    return success;
}

size_t MyPhysX::countActors() const {
    return scene_->getNbActors();
}

NxActor * MyPhysX::getActor( size_t index ) {
    return scene_->getActors()[ index ];
}


}
