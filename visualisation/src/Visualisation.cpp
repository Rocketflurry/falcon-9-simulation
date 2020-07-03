#include "Visualisation.h"
#include "../3rd_party/imgui/imgui.h"
#include "../3rd_party/imgui/imgui_impl_bgfx.h"
#include "../3rd_party/imgui/imgui_impl_glfw.h"
#include "CameraSystem.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>
#include <stdio.h>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>


namespace F9Sim {
namespace Graphics {


static void glfw_errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}


Visualisation::Visualisation() :
    m_window(nullptr),
    m_width(0),
    m_height(0) {

    glfwSetErrorCallback(glfw_errorCallback);

    if(!glfwInit())
        printf("glfwInit() failed");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(960, 540, "Simulation Visualiser", nullptr, nullptr);

    if(!m_window)
        printf("glfwCreateWindow() failed");

    bgfx::renderFrame();

    bgfx::Init init;
    init.platformData.ndt = glfwGetX11Display();
    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_window);
    glfwGetWindowSize(m_window, &m_width, &m_height);
    init.resolution.width = (uint32_t)m_width;
    init.resolution.height = (uint32_t)m_height;

    if(!bgfx::init(init))
        printf("bgfx::init() failed");

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
    bgfx::setDebug(BGFX_DEBUG_TEXT);

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_Implbgfx_Init(0);

    Input_init(*m_window);
    Input_hideMouseCursor();

    // temp
    m_mesh = std::make_unique<Mesh>("resources/obj/Merlin1D.obj");

    m_fpvCam = std::make_unique<FPVCamera>();
    cams.bind("first_person_view");

    m_staticCamera.aspectRatio = 1.0f;
    m_staticCamera.near = 0.1f;
    m_staticCamera.far = 100.0f;
    m_staticCamera.verticalFOV = 45.0f;
    m_staticCamera.position = {10.0f, 10.0f, 10.0f};
    m_staticCamera.up = {0.0f, 1.0f, 0.0f};
    m_staticCamera.lookAt = -m_staticCamera.position.GetNormalized();
    CameraSystem& cams = CameraSystem::getInstance();
    cams.registerCam(m_staticCamera, "static_cam");
    //

    bgfx::touch(0);
}


Visualisation::~Visualisation() {
    ImGui_Implbgfx_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    bgfx::shutdown();
    glfwTerminate();
}


Visualisation& Visualisation::getInstance() {
    static Visualisation instance;
    return instance;
}


void Visualisation::run() {
    double dt = 0.0;
    double frameTime = 0.0;
    double lastFrameTime = 0.0;

    while(!glfwWindowShouldClose(m_window)) {
        lastFrameTime = frameTime;
        frameTime = glfwGetTime();

        glfwPollEvents();
        Input_update();

        // Handle window resize.
        const int oldWidth = m_width;
        const int oldHeight = m_height;
        glfwGetWindowSize(m_window, &m_width, &m_height);
        if(m_width != oldWidth || m_height != oldHeight) {
            bgfx::reset((uint32_t)m_width, (uint32_t)m_height);
            bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
        }

        ImGui_Implbgfx_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // todo: get the required input from the Input module into the FPVCamera's input struct here
        FPVCamera::Input input;
        input.mouseDelta = Input_getMouseDelta();
        input.move.forward = Input_isKeyDown(GLFW_KEY_E);
        input.move.backwards = Input_isKeyDown(GLFW_KEY_D);
        input.move.up = Input_isKeyDown(GLFW_KEY_SPACE);
        input.move.down = Input_isKeyDown(GLFW_KEY_LEFT_SHIFT);
        input.move.left = Input_isKeyDown(GLFW_KEY_S);
        input.move.right = Input_isKeyDown(GLFW_KEY_F);

        m_fpvCam->process(input, dt);
        m_fpvCam->update(dt);

        bgfx::touch(0);
        {
            const float aspectRatio = (float)m_width / (float)m_height;
            CameraSystem::getInstance().setViewTransform(aspectRatio);

            m_mesh->draw();
        }
        bgfx::frame();

        // Render ImGui on top of everything else
        ImGui::Render();

        dt = frameTime - lastFrameTime;
    }
}


} // namespace Graphics
} // namespace F9Sim

