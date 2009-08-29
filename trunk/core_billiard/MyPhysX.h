#pragma once
namespace my_phys {


class MyPhysX {
public:
    MyPhysX( const NxVec3 & gravity );
    ~MyPhysX();

public:
    bool loadXMLFile( wstring filename );

    size_t getNumberOfActors() const;
    NxActor * getActor( size_t index );

    void simulate( float elapsedTime );
    void fetchResult();
    bool isSimulationDone();

public: // character
    NxController * addCapsuleCharacter( NxVec3 position, float radius, float height,
        float skinWidth, NxHeightFieldAxis upDirection, NxUserControllerHitReport * report );

    NxU32 MoveCharacter(NxU32 characterIndex, const NxVec3& dispVector, NxF32 elapsedTime, NxU32 collisionGroups, NxF32 heightDelta);
    const NxExtendedVec3& GetCharacterPos(NxU32 characterIndex);
    bool ResetCharacterPos(NxU32 index, const NxVec3& pos);
    NxActor* GetCharacterActor(NxU32 characterIndex);

public: // user call back
    void setContactReportCallBack( ContactReport * );

public: // CCD
    void assignCCDSkeleton( NxActor * );
    void createMeshFromShape( NxSimpleTriangleMesh & triMesh, NxShape * shape );
    void createMeshFromBoxShape( NxSimpleTriangleMesh & triMesh, const NxBoxShape * boxShape );
    void createMeshFromSphereShape( NxSimpleTriangleMesh & triMesh, const NxSphereShape * sphereShape );
    void createMeshFromConvexMeshShape( NxSimpleTriangleMesh & triMesh, const NxConvexShape * convexShape );
    void freeSimpleMesh( const NxSimpleTriangleMesh & triMesh );

private: // character
    void UpdateControllers();

private:
    NxPhysicsSDK * physicsSDK_;
    NxScene * scene_;
    PerfRenderer perfRenderer_;

private: // character
    static NxControllerManager * characterMnager_;
    UserAllocator * const userAllocator_;
    
    typedef list< NxController * > Controllers;
    Controllers controllers_;

private: // CCD
    static void CreateMeshFromShape( NxSimpleTriangleMesh & triMesh, NxShape * shape );
};


}
