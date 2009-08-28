#pragma once


class BallContactReport : public NxUserContactReport { // NxUserContactModify 
public: // from NxUserContactReport
    virtual void  onContactNotify(NxContactPair& pair, NxU32 events);

public:
    NxContactPairFlag getContactReportFlags();

private:
    void onContactStart( NxContactPair & pair );
    void onContactEnd( NxContactPair & pair );
    void onContactTouch( NxContactPair & pair );

private:
    static bool isActorBall( NxActor * actor );
};