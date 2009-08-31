#pragma once


class MyRenderEventListenerImp
    : IMPLEMENTS_INTERFACE( RenderEventListener )
    , IMPLEMENTS_INTERFACE( SoundRetriever )
    , IMPLEMENTS_INTERFACE( ActorRecognizer )
    , IMPLEMENTS_INTERFACE( BilliardControl )
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

public: // from BilliardControl
    virtual MyCamera * getActiveCamera() OVERRIDE;
    virtual NxVec3 getCueBallPosition() OVERRIDE;
    virtual void readyToHitCueBall() OVERRIDE;
    virtual float getHowMuchPowerIsCharged() OVERRIDE;
    virtual void hitCueBall() OVERRIDE;
    virtual void bringCueBallBack() OVERRIDE;
    virtual void restart() OVERRIDE;
    virtual void pause( bool ) OVERRIDE;
    virtual bool isPaused() OVERRIDE;
    virtual NxActor * getCueBall() OVERRIDE;
    virtual bool isBallMoving() OVERRIDE;

public:
    MyRenderEventListenerImp( wstring sceneFile, wstring physX_File );

private: // init
    void initCamera( size_t index, NxVec3 pos, NxVec3 dir );
    void initLight( size_t index, NxVec3 pos, NxVec3 dir );
    void initSound();
    void initPhys();
    void initVisualOnlyObjects();

    // init sound
    bool loadSound( int soundType, wstring filename );

    // init phys
    void initPhysUserCallBacks();
    void initPhysMainActors();
    void initPhysActorGroups();
    void initPhysBalls();

    // init phys ball
    void initPhysBallMaterial( NxActor * actor );
    void initPhysBallCCD( NxActor * actor );
    void initPhysBallPosition( NxActor * actor );

private: // reset
    void resetEffect( RenderBufferFactory * renderFactory );
    void resetCameraProjection( float aspectRatio );
    void resetLightProjection( float aspectRatio );
    void resetEffectProjection();

private: // update
    void updateCamera( size_t index, float elapsedTime );
    void updateCameraView( size_t index );
    void updateCameraPosAndDir( size_t index );
    void updateEffect( float elapsedTime );
    void updateEffectLights();
    void updateStickPosition();
    void updateStickPower( float elapsedTime );

private: // display
    void preDisplay( Render * render );
    void onDisplay( Render * render );
    void postDisplay( Render * render );

private: // reset
    const NxVec3 & getBallDefaultPosition( NxActor * );
    void resetBall( NxActor * ball );

private: // effect
    void createShadowMap( RenderBufferFactory * );
    EffectShaderFeeder * createEffectFeeder( Node *, RenderBufferFactory * );
    void createSharedVariableFeeder();
    void findSharedVariables( EffectShader * effect);
    ShaderVariable * getSharedVariable( wstring name );

private:
    ScenePtr scene_;
    MyPhysXPtr phys_;
    MyOpenALImp openAL_;

private: // physx
    enum { ACTOR_CUE_BALL, ACTOR_RACK, SIZE_OF_ACTOR };
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

private: // visual only
    enum { VISUAL_BACKGROUND, VISUAL_STICK, SIZE_OF_VISUAL_OBJECTS };
    Node * visualOnlyObjects_[ SIZE_OF_VISUAL_OBJECTS ];

private: // camera
    enum { CAMERA0, LIGHT0, SIZE_OF_CAMERA_ENUM };
    MyCameraPtr camera_[ SIZE_OF_CAMERA_ENUM ];
    RowMajorMatrix44f matrixView_[ SIZE_OF_CAMERA_ENUM ];
    RowMajorMatrix44f matrixProjection_[ SIZE_OF_CAMERA_ENUM ];
    RowMajorMatrix44f matrixProjectionView_[ SIZE_OF_CAMERA_ENUM ];
    NxVec3 cameraPos_[ SIZE_OF_CAMERA_ENUM ];
    NxVec3 cameraDir_[ SIZE_OF_CAMERA_ENUM ];
    const bool bRightHandHardware_;

private: // keyboard input
    bool bPaused_;
    const float cueShotStrength_;
    bool bChargingStickPower_;
    float chargedStickPower_;

private: // effect
    typedef list< EffectShaderFeederPtr > EffectShaderFeeders;
    EffectShaderFeeders feeders_;
    GlobalEffectShaderFeederPtr sharedVaribleFeeder_;

    EffectShaderFeederNull nullToRender_;
    ShaderVariableNull nullShaderVariable_;

    typedef map< wstring, ShaderVariablePtr > SharedVariables;
    SharedVariables sharedVariables_;

private: // shadow
    RenderTargetPtr shadowRenderTarget_;
    GlobalEffectShaderFeederPtr shadowFeeder_;

private: // for random numbers
    mt19937 eng_;
};


