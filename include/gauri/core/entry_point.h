#pragma once

#include "gauri.h"

int main(int /* argc */, char * /*argv[]*/)
{
    gauri::Log::Init();

    auto app = gauri::CreateApplication();

    app->Run();

    delete app;
}
