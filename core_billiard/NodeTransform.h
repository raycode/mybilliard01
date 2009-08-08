#pragma once
namespace my_render_imp {


enum NodeTransformType
{
    ENodeTransformRotate,
    ENodeTransformTranslate,
    ENodeTransformLookAt,
    ENodeTransformMatrix, 
    ENodeTransformScale,
    ENodeTransformSkew,
    ENodeTransformUnknown, 
};


class NodeTransform
{
private:
    NodeTransformType type_;

private:
    NxVec3 vector_; // this will store axis rotation, translation or scale 
    NxReal rotationAngle_;
    NxVec3 lookAt_[3]; // this will store lookAt, eyePoint and up 
    NxMat34 matrix_;  

private:
    NodeAnimation * animation_;
    wstring sid_;

public: // type
    NodeTransformType getType() { return type_; }	
    void setType( NodeTransformType type ) { type_ = type; };
    static	NodeTransformType getType( wstring nameType ); 

public: // get
    NxVec3 & getTranslate() { return vector_;}
    NxVec3 & getRotateDirection() { return vector_; }
    NxReal & getRotationAngle() { return rotationAngle_; }
    NxVec3 & getScale() { return vector_; }
    NxVec3 * getLookAt() { return lookAt_;} 
    NxMat34 & getMatrix() { return matrix_; }
    NodeAnimation * getAnimation() {return animation_; }
    wstring getSid() { return sid_; }

public: // set
    NodeTransform();
    void setTranslate( NxVec3 ); 
    void setRotate( NxVec3 dir, NxReal angle );  
    void setScale( NxVec3 );  
    void setLookAt( NxVec3 v[] ); 
    void setMatrix( NxMat34 m ); 
    void setAnimation( NodeAnimation * anim ) { animation_ = anim; }; 
    void setSid( wstring sid ); 
};

}
