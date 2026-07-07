#include "camera/common/build_info.h"

namespace camera::common {

std::string_view project_name()
{
    return "Web-Cam_proj";
}

std::string_view common_component_name()
{
    return "camera_common";
}

int common_api_version()
{
    return 1;
}

}  // namespace camera::common
