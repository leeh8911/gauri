#pragma once

#include "gauri.h"

int main(int /* argc */, char * /*argv[]*/)
{
    gauri::Log::Init();

    GR_PROFILE_BEGIN_SESSION("Startup", "gauri-profile-startup.json");
    auto app = gauri::CreateApplication();
    GR_PROFILE_END_SESSION();

    GR_PROFILE_BEGIN_SESSION("Runtime", "gauri-profile-runtime.json");
    app->Run();
    GR_PROFILE_END_SESSION();

    GR_PROFILE_BEGIN_SESSION("Startup", "gauri-profile-shutdown.json");
    delete app;
    GR_PROFILE_END_SESSION();
}
