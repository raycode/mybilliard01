#pragma once
namespace my_render_imp {


class NodeImp : public BaseImp, IMPLEMENTS_( Node ) {
public: // from Node
    virtual Node * getParent() OVERRIDE;
    virtual Node * getNextSibling() OVERRIDE;
    virtual Node * getFirstChild() OVERRIDE;
    virtual size_t getNbChild() OVERRIDE;
    virtual wstring getSID() OVERRIDE;

    virtual void update( float time ) OVERRIDE;
    virtual void render( Render * render ) OVERRIDE;

public:
    NodeImp();

public: // set
    void setParent( NodeImp * parent );
    void setNextSibling( NodeImp * nextSibling );
    void appendChild( NodeImp * child );
    void setSID( wstring sid );

    void appendInstanceGeometry( Instance * instanceGeometry );
    void appendNodeTransform( NodeTransform transform );

public: // update
    void updateOrient( float time );
    void updateLocalMatrix();

public:

private: // from Node
    wstring sid_;
    NodeImp * parent_;
    NodeImp * nextSibling_;
    NodeImp * firstChildren_;
    size_t nbChildren_;

private: // instance
    typedef vector< Instance * > Instances;
    Instances instanceGeometries_;

private: // transform
    typedef vector< NodeTransform > Transforms;
    Transforms transforms_;

private: // render
    void renderInstanceGeometries( Render * render );

private:
    bool isNeedToUpdate() const;
    bool needToUpdateLocalMatrix_, needToUpdateLocalToWorldMatrix_;
};


}