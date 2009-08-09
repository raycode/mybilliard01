#pragma once
namespace my_render_imp {


class GeometryMeshOffset {
public:
    GeometryMeshOffset( domInputLocalOffset_Array & inputs )
    {
        max_offset = 0;
        position_offset = -1;
        normal_offset = -1;
        texture1_offset = -1;
        position_floats = NULL;
        normal_floats = NULL;
        texture1_floats = NULL;
        SetInputs(inputs);
    };
    ~GeometryMeshOffset(){};

    int max_offset;

    int position_offset;
    int normal_offset;
    int texture1_offset;

    domListOfFloats * position_floats;
    domListOfFloats * normal_floats;
    domListOfFloats * texture1_floats;

private:
    void SetInputs(domInputLocalOffset_Array & inputs)
    {
        // inputs with offsets
        for( size_t i = 0; i < inputs.getCount(); ++i)
        {
            const int thisoffset  = (size_t) inputs[i]->getOffset();
            if( max_offset < thisoffset ) ++max_offset;

            domSource * const source = (domSource*) (domElement*) inputs[i]->getSource().getElement();
            if(strcmp("VERTEX", inputs[i]->getSemantic())) {
                position_offset = thisoffset;
            } else if(strcmp("NORMAL", inputs[i]->getSemantic())) {
                normal_offset = thisoffset;
                normal_floats = & source->getFloat_array()->getValue();
            } else if(strcmp("TEXCOORD", inputs[i]->getSemantic())) {
                texture1_offset = thisoffset;
                texture1_floats = & source->getFloat_array()->getValue();
            }
        }
        max_offset++;

        // inputs without offsets in vertices
        domMesh * mesh = (domMesh*) inputs[0]->getParentElement()->getParentElement();
        domVertices * vertices = mesh->getVertices();
        domInputLocal_Array& vertices_inputs = vertices->getInput_array();
        for(size_t i=0; i<vertices_inputs.getCount(); i++)
        {
            domSource * source = (domSource*) (domElement*) vertices_inputs[i]->getSource().getElement();
            if(strcmp("POSITION", vertices_inputs[i]->getSemantic())) {
                position_floats = & source->getFloat_array()->getValue();
            } else if(strcmp("NORMAL", vertices_inputs[i]->getSemantic())) {
                normal_floats = & source->getFloat_array()->getValue();
                normal_offset = position_offset;
            } else if(strcmp("TEXCOORD", vertices_inputs[i]->getSemantic())) {
                texture1_floats = & source->getFloat_array()->getValue();
                texture1_offset = position_offset;
            }
        }

    };
};


}
