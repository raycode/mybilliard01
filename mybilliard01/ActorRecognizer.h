#pragma once

MY_INTERFACE ActorRecognizer {
    virtual ~ActorRecognizer() {}

    virtual bool isActorBall( NxActor * actor ) PURE;

};
