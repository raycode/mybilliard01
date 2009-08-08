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
    NxVec3 vector_; // this will store axis rotation, translation or scale 
    NxReal rotationAngle_;
    NodeAnimation * animation_;
    NodeAnimation lookAt_[3]; // this will store lookAt, eyePoint and up 
    NxMat34 matrix_;  
    wstring sid_;

public: // type
    NodeTransformType getType() { return type_; }	
    void setType( NodeTransformType type ) { type_ = type; };
    static	NodeTransformType getType( wstring nameType ); 

public: // get
    NxVec3 &getVecTrans() { return vector_;} // this will be rot,trans or scale depending on type	
    NodeAnimation * getLookAt() { return lookAt_;} 
    NodeAnimation * getAnimation() {return animation_; }
    NxMat34 &getMatrix() { return matrix_; }

public: // set
    NodeTransform();
    void setTranslate( NxVec3 ); 
    void setRotate( NxVec3 dir, NxReal angle );  
    void setScale( NxVec3 );  
    void setLookAt( NxVec3 v[] ); 
    void setMatrix( NxMat34 m ); 

    void setAnimation( NodeAnimation * anim ) { animation_ = anim; }; 
    void setSid( wstring sid ); 
    wstring getSid() { return sid_; }
};

}
