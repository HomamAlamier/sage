#include <w3d_model.h>
#include <iostream>

void pchunk(w3d::W3D_Chunk* c)
{
    c->print();
}

int main()
{
    w3d::W3D_Model mdl("test.W3D");
    if (mdl.loaded())
        mdl.hierarchy().print();
    return 0;
}

