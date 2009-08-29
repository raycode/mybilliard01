#pragma once

MY_INTERFACE SoundRetriever {
    virtual ~SoundRetriever() {}

    virtual SoundHandle * getRandomSound( int soundType ) PURE;

    enum SoundEnum {
        SOUND_BALL_STRONG,
        SOUND_BALL_WEAK,
        SOUND_POCKET,
        SOUND_CHALK,
        SOUND_CUE_STRONG,
        SOUND_CUE_WEAK,
        SOUND_BREAK,
        SOUND_BUMP,
        SOUND_RACK,
        SIZE_OF_SOUND_ENUM };
};