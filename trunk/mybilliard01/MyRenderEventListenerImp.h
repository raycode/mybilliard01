#pragma once


class MyRenderEventListenerImp
    : IMPLEMENTS_INTERFACE( RenderEventListener )
    , IMPLEMENTS_INTERFACE( SoundRetriever )
    , IMPLEMENTS_INTERFACE( ActorRecognizer )
{
public: // from RenderEventListener
    virtual void init() OVERRIDE;
    virtual void displayReset( RenderBufferFactory *, int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE;
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public: // from SoundRetriever
    virtual SoundHandle * getRandomSound( int soundType ) OVERRIDE;

public: // from ActorRecognizer
    virtual bool isActorBall( NxActor * actor ) OVERRIDE;
    virtual bool isActorPocket( NxActor * actor ) OVERRIDE;
    virtual bool isActorRail( NxActor * actor ) OVERRIDE;

public:
    MyRenderEventListenerImp( wstring sceneFile, wstring physX_File );

public:
    MyCamera * getMyCamera();
    NxVec3 getBallPosition();
    void shotCueBall();
    void bringCueBallBack();
    void restart();
    void pause( bool );
    bool isPaused();

private:
    NxActor * getCueBall();
    NxActor * getStick();

private: // init
    void initCamera( NxVec3 pos, NxVec3 dir );
    void initSound();
    void initPhys();
    void initEffect( RenderBufferFactory * renderFactory );
    void initEffectLights();

    bool loadSound( int soundType, wstring filename );
    void initPhysUserCallBacks();
    void initPhysActors();
    void initPhysActorGroups();
    void initPhysBalls();

    void initPhysBallMaterial( NxActor * actor );
    void initPhysBallCCD( NxActor * actor );
    void initPhysBallPosition( NxActor * actor );

private: // update
    void updateCamera( float elapsedTime );
    void updateCameraProjection( float aspectRatio );
    void updateEffectProjection();
    void updateCameraView();
    void updateCameraPosAndDir();
    void updateEffect( float elapsedTime );
    void updateStickPosition();

private: // reset
    const NxVec3 & getBallDefaultPosition( NxActor * );
    void resetBall( NxActor * ball );

private:
    ScenePtr scene_;
    MyPhysXPtr phys_;
    MyOpenALImp openAL_;

private: // physx
    enum { ACTOR_CUE_BALL, ACTOR_STICK, ACTOR_RACK, SIZE_OF_ACTOR };
    NxActor * actors_[ SIZE_OF_ACTOR ];

    enum { ACTORS_BALL, ACTORS_POCKET, ACTORS_RAIL, SIZE_OF_ACTOR_GROUP };
    typedef set< NxActor * > ActorGroup;
    ActorGroup actorGroup_[ SIZE_OF_ACTOR_GROUP ];

    BallContactReport ballContactReport_;

private: // default setting
    typedef map< NxActor *, NxVec3 > BallDefaultPositions;
    BallDefaultPositions ballDefaultPositions_;

private: // sound
    typedef vector< SoundHandlePtr > SimilarSoundHandles;
    SimilarSoundHandles sounds_[ SoundRetriever::SIZE_OF_SOUND_ENUM ];

private: // camera
    MyCameraPtr camera_;
    RowMajorMatrix44f matrixView_;
    RowMajorMatrix44f matrixProjection_;
    RowMajorMatrix44f matrixProjectionView_;
    NxVec3 cameraPos_, cameraDir_;
    const bool bRightHandHardware_;

private: // keyboard input
    bool bPaused_;
    const float cueShotStrength_;

private: // effect
    EffectShaderFeeder * createEffectFeeder( Node * node, RenderBufferFactory * renderFactory );
    void createSharedVariableFeeder();
    void findSharedVariables( EffectShader * effect);
    ShaderVariable * getSharedVariable( wstring name );

    typedef list< EffectShaderFeederPtr > EffectShaderFeeders;
    EffectShaderFeeders feeders_;
    EffectShaderFeederPtr sharedVaribleFeeder_;

    EffectShaderFeederNull nullToRender_;
    ShaderVariableNull nullShaderVariable_;

    typedef map< wstring, ShaderVariablePtr > SharedVariables;
    SharedVariables sharedVariables_;

private: // for random numbers
    mt19937 eng_;
};


