#pragma once

#include "gauri.h"

namespace gauri
{
extern Application *CreateApplication();
}

int main(int /* argc */, char * /*argv[]*/)
{
    gauri::Log::Init();

    auto app = gauri::CreateApplication();

    app->Run();

    delete app;
}
