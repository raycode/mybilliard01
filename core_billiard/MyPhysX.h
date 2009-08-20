#pragma once
namespace my_phys {


class MyPhysX {
public:
    MyPhysX();
    ~MyPhysX();

    bool loadXMLFile( wstring filename );

    size_t getNumberOfActors() const;
    NxActor * getActor( size_t index );

    void simulate( float elapsedTime );
    void fetchResult();
    bool isSimulationDone();

    NxController * addCapsuleCharacter( NxVec3 position, float radius, float height,
        float skinWidth, NxHeightFieldAxis upDirection );

    NxU32 MoveCharacter(NxU32 characterIndex, const NxVec3& dispVector, NxF32 elapsedTime, NxU32 collisionGroups, NxF32 heightDelta);
    const NxExtendedVec3& GetCharacterPos(NxU32 characterIndex);
    bool ResetCharacterPos(NxU32 index, const NxVec3& pos);
    void UpdateControllers();
    NxActor* GetCharacterActor(NxU32 characterIndex);

private:
    NxPhysicsSDK * physicsSDK_;
    NxScene * scene_;
    PerfRenderer perfRenderer_;

private: // character
    static NxControllerManager * characterMnager_;
    UserAllocator * const userAllocator_;
    
    typedef list< NxController * > Controllers;
    Controllers controllers_;
};


}
