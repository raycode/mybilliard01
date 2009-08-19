#pragma once
namespace my_render_imp {


class NodeImp : public BaseImp, IMPLEMENTS_INTERFACE( Node ) {
public: // from Node
    virtual Node * getParent() OVERRIDE;
    virtual Node * getNextSibling() OVERRIDE;
    virtual Node * getFirstChild() OVERRIDE;
    virtual size_t getNbChild() OVERRIDE;
    virtual wstring getSID() OVERRIDE;

    virtual bool hasParent() OVERRIDE;
    virtual bool hasNextSibling() OVERRIDE;
    virtual bool hasFirstChild() OVERRIDE;

    virtual void update( float time ) OVERRIDE;
    virtual void display( Render * render ) OVERRIDE;

public:
    NodeImp();

public: // set
    void setParent( NodeImp * parent );
    void setNextSibling( NodeImp * nextSibling );
    void appendChild( NodeImp * child );
    void setSID( wstring sid );

    void appendInstanceGeometry( Instance * instanceGeometry );

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

private: // render
    void renderInstanceGeometries( Render * render );

private:
    bool isNeedToUpdate() const;
    bool needToUpdateLocalMatrix_, needToUpdateLocalToWorldMatrix_;
};


}