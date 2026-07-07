#include "camera/common/build_info.h"

#include <iostream>

int main()
{
    std::cout << camera::common::project_name() << " camera_server ready\n";
    return 0;
}
