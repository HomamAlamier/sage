#include <engine.h>
#include <engine_gl.h>
#include <glvertexbuffer.h>
#include <glshader.h>
#include <w3d_model.h>
#include <gltexture.h>
#include <GL/glew.h>
#include <glmesh.h>
#include <w3dmodel.h>
#include <thread>
#include <camera.h>

opengl::GLShader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
glm::mat4 mats[3];
sage3d::GLW3DModel* mdl;
sage3d::Camera camera(glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f));

int width = 1280;
int height = 720;

std::vector<std::string> mdls = {
  "test.W3D",
  "test2.W3D",
  "test3.W3D",
  "test4.W3D"
};

auto mdls_it = mdls.begin();

int __ffi = 0;

void handleKeys(sage3d::KeyboardKeyData* e)
{
    if (e->hasKey(sage3d::KEY_RIGHT))
    {
        camera.rotate(sage3d::Yaw, 1.0f);
    }
    if (e->hasKey(sage3d::KEY_LEFT))
    {
        camera.rotate(sage3d::Yaw, -1.0f);
    }
    if (e->hasKey(sage3d::KEY_DOWN))
    {
        camera.rotate(sage3d::Pitch, -1.0f);
    }
    if (e->hasKey(sage3d::KEY_UP))
    {
        camera.rotate(sage3d::Pitch, 1.0f);
    }

    if (e->hasKey(sage3d::KEY_W))
    {
        camera.move(sage3d::Forward, 1.0f);
    }
    if (e->hasKey(sage3d::KEY_S))
    {
        camera.move(sage3d::Backward, 1.0f);
    }
    if (e->hasKey(sage3d::KEY_D))
    {
        camera.move(sage3d::StrafeRight, 1.0f);
    }
    if (e->hasKey(sage3d::KEY_A))
    {
        camera.move(sage3d::StrafeLeft, 1.0f);
    }

    if (e->hasKey(sage3d::KEY_R))
    {
        camera.rotate(sage3d::Roll, 1.0f);
    }
    if (e->hasKey(sage3d::KEY_L))
    {
        shader.setVec3(camera.front(), "world_light.dir");
    }

    if (e->hasKey(sage3d::KEY_SPACE))
    {
        mdls_it++;
        if (mdls_it == mdls.end())
        {
            mdls_it = mdls.begin();
        }
        delete mdl;
        mdl = new sage3d::GLW3DModel(*mdls_it);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void nextMesh()
{


    mdl = new sage3d::GLW3DModel("test2.W3D");

    mats[0] = glm::mat4(1.f);

}

void gldraw(sage3d::Engine_GL* gl)
{
    shader.use();
    shader.setVec3(camera.position(), "view_pos");

    shader.setMatrix4(camera.view(), "view");
    shader.setMatrix4(mats[2], "projection");

    ++__ffi;
    if (__ffi == 2)
    {
        __ffi = 0;
        mdl->nextFrame();
    }

    mdl->draw(gl, &shader, mats[0]);
}

void glinit(sage3d::Engine* e)
{
    nextMesh();

    mats[1] = glm::mat4(1.0f);
    mats[2] = glm::mat4(1.0f);

    mats[1] = glm::translate(mats[1], glm::vec3(-0.f, 0.f, -110.f));
    mats[2] = glm::perspective(glm::radians(90.0f), width / (float)height, 0.1f, 170.0f);

    shader.use();
    shader.setVec3(glm::vec3(30.0f, 50.0f, 0.0f), "world_light.pos");
    shader.setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "world_light.col");
}

int main()
{
    sage3d::Engine e(width, height);
    e.setDrawCallback(gldraw);
    e.setInitCallback(glinit);
    e.setKeyboardCallback(handleKeys);
    e.setOptions(sage3d::ShowFps);
    return e.exec();
}
