#include "Cameras.h"
#include "../3rd_party/imgui/imgui.h"

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <memory>
#include <string>
#include <unordered_map>


namespace F9Sim {
namespace Graphics {


// Internally, the position of the camera is locked at the origin to eliminate floating point errors
static const bx::Vec3 s_eye = {0.0f, 0.0f, 0.0f};
static CameraBaseState s_activeCamera;
static CameraBaseState s_defaultCamera;
static std::unordered_map<std::string, const CameraBaseState*> s_cameraMap;


void Cameras_init() {
    Cameras_register(s_defaultCamera, "default_camera");
    Cameras_bind("default_camera");
}


chrono::Vector Cameras_getActivePos() {
    return s_activeCamera.position;
}


void Cameras_register(const CameraBaseState& cam, const std::string& name) {
    printf("Registered '%s'.\n", name.c_str());
    s_cameraMap[name] = &cam;
}


void Cameras_bind(const std::string& name) {
    auto it = s_cameraMap.find(name);

    // Camera with name `name` hasn't been registered, can't be bound
    if(it == s_cameraMap.end()) {
        printf("Camera '%s' has not been registered.\n", name.c_str());
        return;
    }

    s_activeCamera = *it->second;
    printf("Bound camera '%s'\n", name.c_str());
}


void Cameras_setViewTransform(float aspectRatio) {
    ImGui::Begin("Before");
    ImGui::Text("m_pos: %f, %f, %f", s_activeCamera.position.x(), s_activeCamera.position.y(), s_activeCamera.position.z());
    chrono::Vector& lookAt = s_activeCamera.lookAt;
    ImGui::Text("lookAt: %f, %f, %f", lookAt.x(), lookAt.y(), lookAt.z());
    ImGui::End();

    const bx::Vec3 at = bx::Vec3(
        s_activeCamera.lookAt.x(),
        s_activeCamera.lookAt.y(),
        s_activeCamera.lookAt.z());

    const bx::Vec3 up = bx::Vec3(
        s_activeCamera.up.x(),
        s_activeCamera.up.y(),
        s_activeCamera.up.z());

    float view[16];
    bx::mtxLookAt(view, s_eye, at, up, bx::Handness::Right);

    float proj[16];
    bx::mtxProj(
        proj,
        s_activeCamera.verticalFOV,
        1.0f,
        s_activeCamera.near,
        s_activeCamera.far,
        bgfx::getCaps()->homogeneousDepth,
        bx::Handness::Right);


    bgfx::setViewTransform(0, view, proj);
}


} // namespace Graphics
} // namespace F9Sim

