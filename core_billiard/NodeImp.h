#pragma once
namespace my_render_imp {


class NodeImp : IMPLEMENTS_ Node {
public: // from Base
    virtual wstring getID();
    virtual wstring getSID();
    virtual wstring getName();

public: // from Node
    virtual Node * getParent();
    virtual Node * getNextSibling();
    virtual Node * getFirstChild();
    virtual size_t getNbChild();

    virtual void update( float time );
    virtual void render( Render * render );

public: // initialize
    NodeImp();

    void setID( wstring id );
    void setSID( wstring sid );
    void setName( wstring name );
    void setParent( NodeImp * parent );
    void setNextSibling( NodeImp * nextSibling );
    void appendChild( NodeImp * child );

    void appendInstanceGeometry( Instance * instanceGeometry );

public: // update
    void updateOrient( float time );
    void updateLocalMatrix();

private: // from Base
    wstring id_, sid_, name_;

private: // from Node
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