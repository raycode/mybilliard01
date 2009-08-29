#pragma once


class BallContactReport : public NxUserContactReport { // NxUserContactModify 
public: // from NxUserContactReport
    virtual void  onContactNotify(NxContactPair& pair, NxU32 events);

public:
    NxContactPairFlag getContactReportFlags();

public: // sound
    void setSound_BallBounce( SoundHandle * );
    void playSoundForBallBounce( NxContactPair & pair );

private:
    void onContactStart( NxContactPair & pair );
    void onContactEnd( NxContactPair & pair );
    void onContactTouch( NxContactPair & pair );

private:
    static bool isActorBall( NxActor * actor );

private:
    enum SoundEnum { SOUND_BALL, SOUND_POCKET, SOUND_CUE, SOUND_BREAK, SOUND_BUMP, SIZE_OF_SOUND_ENUM };
    SoundHandle * sounds_[ SIZE_OF_SOUND_ENUM ];
};