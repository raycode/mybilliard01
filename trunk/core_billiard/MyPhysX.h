#pragma once
namespace my_phys {

class MyPhysX {
public:
    MyPhysX( NxUserOutputStream * userOutputStream = NULL );
    ~MyPhysX();

    bool loadColladaFile( wstring filename, NXU_userNotify * userNotify );
    bool loadColladaFile( wstring filename ) { return loadColladaFile( filename, NULL ); }

    size_t getNumberOfActors() const;
    NxActor * getActor( size_t index );

    void simulate( float elapsedTime );
    void fetchResult();
    bool isSimulationDone();

private:
    NxPhysicsSDK*	physicsSDK_;
    NxScene*		scene_;
    PerfRenderer    perfRenderer_;
};

}
