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

    NxActor * addCameraActor( const NxMat34 & globalPose );

private:
    friend class MyUserSceneNotify;

private:
    NxPhysicsSDK * physicsSDK_;
    NxScene * scene_;
    PerfRenderer perfRenderer_;

    typedef list< NxActor * > Actors;
    Actors actors_;
};


}
