#include "camera/common/error.h"

namespace camera::common {

std::string_view to_user_text(ErrorCode code)
{
    switch (code) {
    case ErrorCode::None:
        return "No error.";
    case ErrorCode::ConnectionFailure:
        return "Connection failed. Check network and camera availability.";
    case ErrorCode::StreamingFailure:
        return "Streaming failed. Check camera stream state.";
    case ErrorCode::CommandFailure:
        return "Command failed. Check the requested camera command.";
    case ErrorCode::UnsupportedSetting:
        return "Unsupported camera setting.";
    }

    return "Unknown camera error.";
}

}  // namespace camera::common
