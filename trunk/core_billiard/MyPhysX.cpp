#include "stdafx.h"
#include "my_phys.h"
namespace my_phys {


NxControllerManager * MyPhysX::characterMnager_ = NULL;


MyPhysX::MyPhysX()
: userAllocator_( new UserAllocator() )
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

    if( NULL == characterMnager_ )
        characterMnager_ = NxCreateControllerManager( userAllocator_ );
    assert( characterMnager_ );
}

MyPhysX::~MyPhysX()
{
    if( NULL != characterMnager_ ) {
        NxReleaseControllerManager( characterMnager_ );
        characterMnager_ = NULL;
    }

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

    delete userAllocator_;
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

NxController * MyPhysX::addCapsuleCharacter( NxVec3 position, float radius, float height,
                                     float skinWidth, NxHeightFieldAxis upDirection )
{
    NxCapsuleControllerDesc desc;

    desc.position.set( position.x, position.y, position.z );
    desc.skinWidth = skinWidth;
    desc.upDirection = upDirection;
    desc.slopeLimit = cosf( NxMath::degToRad( 45.0f ) );

    desc.radius = radius;
    desc.height = height;

    NxController * const newChar = characterMnager_->createController( scene_, desc );
    assert( newChar );
    controllers_.push_back( newChar );
    return newChar;
}

NxU32 MyPhysX::MoveCharacter(NxU32 characterIndex, const NxVec3& dispVector, NxF32 elapsedTime, NxU32 collisionGroups, NxF32 heightDelta)
{
    //	NxF32 sharpness = 0.1f;
    NxF32 sharpness = 1.0f;

    NxU32 collisionFlags;
    NxVec3 d = dispVector*elapsedTime;
    if(heightDelta!=0.0f)
        d.y+=heightDelta;
    NxController* c = characterMnager_->getController(characterIndex);
    c->move(d, collisionGroups, 0.000001f, collisionFlags, sharpness);
    return collisionFlags;
}

NxActor* MyPhysX::GetCharacterActor(NxU32 characterIndex)
{
    return characterMnager_->getController(characterIndex)->getActor();
}

void MyPhysX::UpdateControllers()
{
    characterMnager_->updateControllers();
}

bool MyPhysX::ResetCharacterPos(NxU32 index, const NxVec3& pos)
{
    return characterMnager_->getController(index)->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
}

const NxExtendedVec3& MyPhysX::GetCharacterPos(NxU32 characterIndex)
{
    return characterMnager_->getController(characterIndex)->getFilteredPosition();
}


}
