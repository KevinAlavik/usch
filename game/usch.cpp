#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include <string>
#include <sstream>

#include "../engine/engine.hpp"
#include "../engine/drawer.hpp"
#include "../engine/texture.hpp"
#include "state.hpp"

static struct State state;

static std::unique_ptr<Engine::Window> engineWindow;
static std::unique_ptr<Engine::Renderer> engineRenderer;
static std::unique_ptr<Engine::Drawer> engineDrawer;

static std::unique_ptr<Engine::Texture> testTexture;

static Uint64 lastTime = 0;
static float fps = 0.0f;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    try
    {
        SDL_SetAppMetadata("usch", "1.0", "org.piraterna.usch");
        SDL_Init(SDL_INIT_VIDEO);

        state.bg_color = math::Vec4(0.0f, 0.2f, 0.0f, 1.0f);
        state.text_color = math::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        state.mouse_pos = math::Vec2(0.0f, 0.0f);

        engineWindow = std::make_unique<Engine::Window>("usch", math::Vec2(800, 600));
        engineRenderer = std::make_unique<Engine::Renderer>(*engineWindow);
        engineDrawer = std::make_unique<Engine::Drawer>(*engineRenderer);

        // Load the test image
        testTexture = std::make_unique<Engine::Texture>(*engineRenderer, "image.png");
        testTexture->setScale(0.5f, 0.5f);
        lastTime = SDL_GetTicks();
    }
    catch (const std::exception &e)
    {
        SDL_Log("Initialization failed: %s", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_KEY_DOWN && event->key.scancode == SDL_SCANCODE_ESCAPE)
    {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        state.mouse_pos = math::Vec2(event->motion.x, event->motion.y);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    try
    {
        // Calculate FPS
        Uint64 currentTime = SDL_GetTicks();
        Uint64 delta = currentTime - lastTime;
        lastTime = currentTime;
        if (delta > 0)
        {
            fps = 1000.0f / delta;
        }

        engineRenderer->setDrawColor(state.bg_color);
        engineRenderer->clear();

        testTexture->setRotation(static_cast<float>(SDL_GetTicks()) / 10.0f);
        engineDrawer->drawTexture(state.mouse_pos, *testTexture);

        // Draw debug text
        engineRenderer->setDrawColor(state.text_color);
        std::ostringstream debugText;
        debugText.precision(2);
        debugText << std::fixed << "FPS: " << fps;
        SDL_RenderDebugText(engineRenderer->getHandle(), 0, 0, debugText.str().c_str());

        // Output mouse position
        engineRenderer->setDrawColor(state.text_color);
        std::ostringstream mouseText;
        mouseText.precision(2);
        mouseText << std::fixed << "Mouse position: " << state.mouse_pos.x << ", " << state.mouse_pos.y;
        SDL_RenderDebugText(engineRenderer->getHandle(), 0, 10, mouseText.str().c_str());

        // Update screen buffer
        engineRenderer->present();
    }
    catch (const std::exception &e)
    {
        SDL_Log("Error during iteration: %s", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    testTexture.reset();
    engineDrawer.reset();
    engineRenderer.reset();
    engineWindow.reset();
    SDL_Quit();
}
