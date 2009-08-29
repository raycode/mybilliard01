#pragma once

MY_INTERFACE ActorRecognizer {
    virtual ~ActorRecognizer() {}

    virtual bool isActorBall( NxActor * actor ) PURE;
    virtual bool isActorPocket( NxActor * actor ) PURE;
    virtual bool isActorRail( NxActor * actor ) PURE;

};
