#pragma once


class BallContactReport : public NxUserContactReport { // NxUserContactModify 
public: // from NxUserContactReport
    virtual void  onContactNotify(NxContactPair& pair, NxU32 events);

public: // init
    BallContactReport( SoundRetriever *, ActorRecognizer * );

    NxContactPairFlag getContactReportFlags();

private:
    void onContactStart( NxContactPair & pair );
    void onContactEnd( NxContactPair & pair );
    void onContactTouch( NxContactPair & pair );

private: // sound
    void playSoundForBallBounce( NxContactPair & pair );

private:
    SoundRetriever * const sound_;
    ActorRecognizer * const actorRecognizer_;

private: // sound strength
    size_t numberOfSamples_BallBounce_;
    float averageForce_BallBounce_;
};