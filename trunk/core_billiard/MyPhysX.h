#pragma once
namespace my_phys_x {

class MyPhysX {
public:
    MyPhysX();
    ~MyPhysX();

    void loadColladaFile( wstring filename );

    size_t countActors() const;
    NxActor * getActor( size_t index );

private:
    NxPhysicsSDK*	physicsSDK_;
    NxScene*		scene_;
    PerfRenderer    perfRenderer_;
};

}
