#include "camera/common/build_info.h"
#include "camera/server/session_controller.h"

#include <iostream>

int main()
{
    const camera::server::SessionController session_controller;

    std::cout << camera::common::project_name() << " camera_server ready\n";
    std::cout << "active client connected: " << std::boolalpha << session_controller.has_active_client() << "\n";
    return 0;
}
