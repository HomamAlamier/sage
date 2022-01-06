#include <engine.h>
#include <engine_gl.h>
#include <glvertexbuffer.h>
#include <glshader.h>
opengl::GLVertexBuffer vb(opengl::Triangles);
opengl::GLShader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

void gldraw(sage3d::Engine_GL* gl)
{
    shader.use();
    gl->drawBuffer(&vb);
}

void glinit(sage3d::Engine* e)
{
    float vtx[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    vb.add(vtx, 9, 3);
    vb.init();

}

int main()
{
    sage3d::Engine e(800, 600);
    e.setDrawCallback(gldraw);
    e.setInitCallback(glinit);
    e.setOptions(sage3d::ShowFps);
    return e.exec();
}
