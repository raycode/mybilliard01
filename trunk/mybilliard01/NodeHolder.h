#pragma once


class NodeHolder {
public:
    NodeHolder( Node * );

    wstring getNodeName() const;
    Node * getNode();

    enum EFFECT_TYPE { EFFECT_COMPLETE, EFFECT_LIGHT_0, EFFECT_CAMERA_0, SIZE_OF_EFFECT_TYPE_ENUM };
    void setEffectShaderFeeder( EFFECT_TYPE, EffectShaderFeeder * );
    EffectShaderFeeder * getEffectShaderFeeder( EFFECT_TYPE ) const;

    void setActor( NxActor * );
    NxActor * getActor();

    NxVec3 getPosition();

    bool operator< ( const NodeHolder & rhs ) const;

    void updateCameraDistance( const NxVec3 & cameraPosition );
    float getDistance() const;

public:
    struct isName {
        bool operator()( const NodeHolder & rhs ) { return rhs.getNodeName() == name_; }

        isName( wstring name ) : name_( name ) {}
    private:
        const wstring name_;
    };

    struct sortByDistance {
        bool operator()( const NodeHolder & lhs, const NodeHolder & rhs )
        { return lhs.getDistance() < rhs.getDistance(); }
    };

private:
    Node * node_;
    EffectShaderFeeder * feeder_[ SIZE_OF_EFFECT_TYPE_ENUM ];
    NxActor * actor_;

private:
    float distance_;
};