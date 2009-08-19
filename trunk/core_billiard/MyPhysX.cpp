#include "stdafx.h"
#include "my_phys.h"
namespace my_phys {


MyPhysX::MyPhysX()
{
    // Initialize PhysicsSDK
    NxPhysicsSDKDesc desc;
    NxSDKCreateError errorCode = NXCE_NO_ERROR;
    physicsSDK_ = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, NULL, desc, &errorCode);
    if( NULL == physicsSDK_ ) throw exception();

    // Create a scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
    scene_ = physicsSDK_->createScene(sceneDesc);
    if( NULL == scene_ ) throw exception();
}

MyPhysX::~MyPhysX()
{
    if(physicsSDK_ != NULL)
    {
        if(scene_ != NULL) 
        {
            physicsSDK_->releaseScene(*scene_);
            scene_ = NULL;
        }

        NXU::releasePersistentMemory();
        NxReleasePhysicsSDK(physicsSDK_);
        physicsSDK_ = NULL;
    }
}

bool MyPhysX::loadXMLFile( wstring filename ) {
    wchar_t LoadFilename[512];
    FindMediaFile( filename.c_str(), LoadFilename);

    NXU::setEndianMode(isProcessorBigEndian());
    NXU::NxuPhysicsCollection *c = NXU::loadCollection( convertString( LoadFilename ).c_str(), NXU::FT_XML );
    if ( c )
    {
        NXU::instantiateCollection(c, *physicsSDK_, scene_, 0, NULL );
        NXU::releaseCollection(c);
    }
    else
    {
        //printf("Error: Unable to find the input file for this sample: %s\n", buff);
        return false;
    }

    return true;
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

NxActor * MyPhysX::addCameraActor( NxMat34 globalPose ) {

    NxSphereShapeDesc shapeDesc;
    shapeDesc.radius = 0.1f;
    shapeDesc.skinWidth = 0.0001f;

    NxActorDesc actorDesc;
    actorDesc.shapes.pushBack( & shapeDesc );
    actorDesc.globalPose = globalPose;
    actorDesc.userData = NULL;
    actorDesc.name = "Camera"; // be careful for const char * pointer.

    NxActor * const newCamera = scene_->createActor( actorDesc );
    actors_.push_back( newCamera );
    return newCamera;
}


}
