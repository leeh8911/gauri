#pragma once

#include "gauri.h"

namespace gauri
{
extern Application *CreateApplication();
}

int main(int /* argc */, char * /*argv[]*/)
{
    auto app = gauri::CreateApplication();

    std::cout << "Start entry point!\n";

    app->Run();

    delete app;
}
