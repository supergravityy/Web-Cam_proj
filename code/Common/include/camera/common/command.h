#pragma once

#include "camera/common/error.h"

#include <string_view>
#include <variant>

namespace camera::common {

inline constexpr int kMinFrameRateFps = 1;
inline constexpr int kMaxFrameRateFps = 240;
inline constexpr int kMinResolutionWidth = 1;
inline constexpr int kMaxResolutionWidth = 7680;
inline constexpr int kMinResolutionHeight = 1;
inline constexpr int kMaxResolutionHeight = 4320;

enum class CommandType {
    Connect,
    Disconnect,
    SetFrameRate,
    SetResolution,
};

struct ConnectCommand {
};

struct DisconnectCommand {
};

struct FrameRateCommand {
    int frames_per_second;
};

struct ResolutionCommand {
    int width;
    int height;
};

using Command = std::variant<ConnectCommand, DisconnectCommand, FrameRateCommand, ResolutionCommand>;

struct CommandValidationResult {
    bool valid;
    ErrorCode error_code;
    std::string_view message;
};

Command make_connect_command();
Command make_disconnect_command();
Command make_frame_rate_command(int frames_per_second);
Command make_resolution_command(int width, int height);

CommandType command_type(const Command& command);
CommandValidationResult validate_command(const Command& command);
bool is_valid_command(const Command& command);

}  // namespace camera::common
