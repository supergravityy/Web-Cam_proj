#pragma once

#include <string_view>

namespace camera::common {

std::string_view project_name();
std::string_view common_component_name();
int common_api_version();

}  // namespace camera::common
