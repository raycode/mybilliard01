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
    void initLight( size_t index, float nearZ, float farZ, NxVec3 pos, NxVec3 dir );
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
    void resetEffect( RenderBufferFactory *, size_t width, size_t height );
    void resetEffect( RenderBufferFactory *, RenderableCamera *, wstring effectFilenameForPositionOnly );
    void resetShadowMap();

private: // update
    void updateCamera( float elapsedTime );
    void resetProjection( float aspect );
    void resetProjection( float aspect, RenderableCamera * );
    void updateStickPosition();
    void updateStickPower( float elapsedTime );

private: // reset
    const NxVec3 & getBallDefaultPosition( NxActor * );
    void resetBall( NxActor * ball );

private: // display
    void display_renderStates( Render * );
    void display_lightMaps( Render * );
    void display_activeCamera( Render * );

private: // effect
    MyEffectShaderFeeder * createEffectFeeder( wstring nodeName, RenderBufferFactory * );
    void findSharedVariables( EffectShader * effect);
    ShaderVariable * getSharedVariable( wstring name );
    void createPostEffects( RenderBufferFactory * );

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
    enum { LIGHT_0, SIZE_OF_LIGHT_ENUM };
    RenderableCamera * lights_[ SIZE_OF_LIGHT_ENUM ];
    RenderTarget * lightRenderTargets_[ SIZE_OF_LIGHT_ENUM ];

    ShaderVariable * lightMatrices_[ SIZE_OF_LIGHT_ENUM ];

    enum CameraEnum { CAMERA_0, SIZE_OF_CAMERA_ENUM };
    MyCamera * cameras_[ SIZE_OF_CAMERA_ENUM ];
    RenderableCamera * depthCameras_[ SIZE_OF_CAMERA_ENUM ];

    CameraEnum activeCamera_;

    typedef list< my_render::CameraPtr > ColladaCameras;
    ColladaCameras colladaCameras_;

    typedef list< RenderableCameraPtr > RenderableCameras;
    RenderableCameras cameraOrLights_;

private: // effect
    typedef list< EffectShaderFeederPtr > EffectShaderFeeders;
    EffectShaderFeeders feeders_, sharedFeeders_;

    typedef map< wstring, ShaderVariable * > SharedVariables;
    SharedVariables sharedVariables_;

private: // keyboard input
    bool bPaused_;
    const float cueShotStrength_;
    bool bChargingStickPower_;
    float chargedStickPower_;

    typedef ShaderVariable * Light_Position_Variables;
    Light_Position_Variables light_Position_Variables_[ SIZE_OF_LIGHT_ENUM ];

    typedef map< EffectShaderFeeder *, ShaderVariable * > Light_WVP_Variables;
    Light_WVP_Variables light_WVP_Variables_[ SIZE_OF_LIGHT_ENUM ];

private: // for random numbers
    mt19937 randomEngine;
};


