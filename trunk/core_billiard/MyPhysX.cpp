#include "stdafx.h"
#include "my_phys.h"
namespace my_phys {


NxControllerManager * MyPhysX::characterMnager_ = NULL;


MyPhysX::MyPhysX( const NxVec3 & gravity )
: userAllocator_( new UserAllocator() )
{
    // Initialize PhysicsSDK
    NxPhysicsSDKDesc desc;
    NxSDKCreateError errorCode = NXCE_NO_ERROR;
    physicsSDK_ = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, NULL, desc, &errorCode);
    if( NULL == physicsSDK_ ) throw exception();
    physicsSDK_->setParameter( NX_CONTINUOUS_CD, 1.f );
    physicsSDK_->setParameter( NX_CCD_EPSILON, 0.01f );

    // Create a scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity = gravity;
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
    const float TimeStep = 1.0f / 60.0f;
    scene_->setTiming( TimeStep, 8, NX_TIMESTEP_FIXED );

    scene_->simulate( elapsedTime );
    scene_->flushStream();
}

void MyPhysX::fetchResult() {
    scene_->fetchResults( NX_RIGID_BODY_FINISHED, true );

    NxReal maxTimestep;
    NxTimeStepMethod method;
    NxU32 maxIter;
    NxU32 numSubSteps;
    scene_->getTiming(maxTimestep, maxIter, method, &numSubSteps);
    if(numSubSteps)	UpdateControllers();
}

bool MyPhysX::isSimulationDone() {
    return scene_->checkResults( NX_RIGID_BODY_FINISHED, false );
}

NxController * MyPhysX::addCapsuleCharacter( NxVec3 position, float radius, float height,
                     float skinWidth, NxHeightFieldAxis upDirection, NxUserControllerHitReport * report )
{
    NxCapsuleControllerDesc desc;

    desc.position.set( position.x, position.y, position.z );
    desc.skinWidth = skinWidth;
    desc.upDirection = upDirection;
    desc.slopeLimit = cosf( NxMath::degToRad( 45.0f ) );
    desc.callback = report;

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

void MyPhysX::setContactReportCallBack( ContactReport * contactReport )
{
    scene_->setActorGroupPairFlags( 0, 0, contactReport->getContactReportFlags() );
    scene_->setUserContactReport( contactReport );
}

void MyPhysX::assignCCDSkeleton( NxActor * actor )
{
    const size_t nShapes = actor->getNbShapes();
    for( size_t i = 0; i < nShapes; ++i )
    {
        NxShape * const shape = actor->getShapes()[ i ];
        shape->setFlag( NX_SF_DYNAMIC_DYNAMIC_CCD, true );

        NxSimpleTriangleMesh triMesh;
        createMeshFromShape( triMesh, shape );
        NxCCDSkeleton * const newSkeleton = physicsSDK_->createCCDSkeleton( triMesh );
        freeSimpleMesh( triMesh );
        shape->setCCDSkeleton( newSkeleton );
    }
}

void MyPhysX::createMeshFromShape( NxSimpleTriangleMesh & triMesh, NxShape * shape )
{
    if( NULL != shape->isBox() )
        createMeshFromBoxShape( triMesh, shape->isBox() );
    else if( NULL != shape->isSphere() )
        createMeshFromSphereShape( triMesh, shape->isSphere() );
    else if( NULL != shape->isConvexMesh() )
        createMeshFromConvexMeshShape( triMesh, shape->isConvexMesh() );
    else {
        assert( L"Not supported shape for CCD generation." && false );
    }
    NX_ASSERT(triMesh.isValid());
}

void MyPhysX::freeSimpleMesh( const NxSimpleTriangleMesh & triMesh )
{
    delete triMesh.points;
    delete triMesh.triangles;
}

void MyPhysX::createMeshFromBoxShape( NxSimpleTriangleMesh & triMesh, const NxBoxShape * boxShape )
{
    triMesh.numVertices = 8;
    triMesh.points = new NxVec3[ triMesh.numVertices ];
    triMesh.pointStrideBytes = sizeof( NxVec3 );

    triMesh.numTriangles = 2 * 6;
    triMesh.triangles = new NxU32[ triMesh.numTriangles * 3 ];
    triMesh.triangleStrideBytes = sizeof( NxU32 ) * 3;

    triMesh.flags = 0;

    NxBox obb = NxBox( NxVec3(0.0f,0.0f,0.0f), boxShape->getDimensions(), NxMat33( NX_IDENTITY_MATRIX ) );
    NxComputeBoxPoints( obb, (NxVec3 *) triMesh.points );
    memcpy( (NxU32 *) triMesh.triangles, NxGetBoxTriangles(), sizeof( NxU32 ) * 2 * 6 * 3 );
}

void MyPhysX::createMeshFromSphereShape( NxSimpleTriangleMesh & triMesh, const NxSphereShape * sphereShape )
{
    triMesh.flags = 0;
    triMesh.numVertices = 3;
    triMesh.points = new NxVec3[ triMesh.numVertices ];
    triMesh.pointStrideBytes = sizeof( NxVec3 );

    triMesh.numTriangles = 1;
    triMesh.triangles = new NxU32[ triMesh.numTriangles * 3 ];
    triMesh.triangleStrideBytes = sizeof( NxU32 ) * 3;

    const NxU32 triangles[] = { 0,1,2 };
    memcpy( (NxU32 *) triMesh.triangles, triangles, sizeof( triangles ) );

    const float radius = sphereShape->getRadius();
    ((NxVec3*)(triMesh.points))[ 0 ].set( radius, 0.f, 0.f );
    ((NxVec3*)(triMesh.points))[ 1 ].set( -radius / 2.f, radius * sqrt( 3.f ) / 2.f, 0.f );
    ((NxVec3*)(triMesh.points))[ 2 ].set( -radius / 2.f, - radius * sqrt( 3.f ) / 2.f, 0.f );
}

void MyPhysX::createMeshFromConvexMeshShape( NxSimpleTriangleMesh & triMesh, const NxConvexShape * convexShape )
{
    triMesh.flags = 0;
    triMesh.numVertices = 3;
    triMesh.points = new NxVec3[ triMesh.numVertices ];
    triMesh.pointStrideBytes = sizeof( NxVec3 );

    triMesh.numTriangles = 1;
    triMesh.triangles = new NxU32[ triMesh.numTriangles * 3 ];
    triMesh.triangleStrideBytes = sizeof( NxU32 ) * 3;

    const NxU32 triangles[] = { 0,1,2 };
    memcpy( (NxU32 *) triMesh.triangles, triangles, sizeof( triangles ) );

    NxConvexMeshDesc desc;
    convexShape->getConvexMesh().saveToDesc( desc );
    memcpy( (void *) triMesh.points, (void*) desc.points, triMesh.pointStrideBytes * triMesh.numVertices );
}

}
