#pragma once


class BallContactReport : IMPLEMENTS_INTERFACE( ContactReport ) {
public: // from NxUserContactReport
    virtual void  onContactNotify(NxContactPair& pair, NxU32 events) OVERRIDE;

public: // from ContactReport 
    virtual NxContactPairFlag getContactReportFlags() OVERRIDE;

public: // init
    BallContactReport( SoundRetriever *, ActorRecognizer * );

private: // onContact
    void onContactStart( NxContactPair & pair );
    void onContactEnd( NxContactPair & pair );
    void onContactTouch( NxContactPair & pair );

private: // sound
    void playSound_BallBounce( NxContactPair & pair );
    void playSound_Pocket( NxContactPair & pair );
    void playSound_Bump( NxContactPair & pair );

private: // action after some cases
    void setBallFallDownOntoPocket( NxActor * ball );

private:
    SoundRetriever * const sound_;
    ActorRecognizer * const actorRecognizer_;

private: // sound strength
    size_t numberOfSamples_BallBounce_;
    float averageForce_BallBounce_;
};