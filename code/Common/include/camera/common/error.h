#pragma once

#include <string_view>

namespace camera::common {

enum class ErrorCode {
    None,
    ConnectionFailure,
    StreamingFailure,
    CommandFailure,
    UnsupportedSetting,
};

std::string_view to_user_text(ErrorCode code);

}  // namespace camera::common
