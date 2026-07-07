#include "camera/common/command.h"

#include <type_traits>

namespace camera::common {
namespace {

template <typename>
inline constexpr bool kDependentFalse = false;

CommandValidationResult valid_command()
{
    return {true, ErrorCode::None, "Command is valid."};
}

CommandValidationResult unsupported_setting(std::string_view message)
{
    return {false, ErrorCode::UnsupportedSetting, message};
}

bool is_supported_frame_rate(int frames_per_second)
{
    return frames_per_second >= kMinFrameRateFps && frames_per_second <= kMaxFrameRateFps;
}

bool is_supported_resolution(int width, int height)
{
    return width >= kMinResolutionWidth && width <= kMaxResolutionWidth
        && height >= kMinResolutionHeight && height <= kMaxResolutionHeight;
}

}  // namespace

Command make_connect_command()
{
    return ConnectCommand{};
}

Command make_disconnect_command()
{
    return DisconnectCommand{};
}

Command make_frame_rate_command(int frames_per_second)
{
    return FrameRateCommand{frames_per_second};
}

Command make_resolution_command(int width, int height)
{
    return ResolutionCommand{width, height};
}

CommandType command_type(const Command& command)
{
    return std::visit(
        [](const auto& payload) {
            using Payload = std::decay_t<decltype(payload)>;
            if constexpr (std::is_same_v<Payload, ConnectCommand>) {
                return CommandType::Connect;
            } else if constexpr (std::is_same_v<Payload, DisconnectCommand>) {
                return CommandType::Disconnect;
            } else if constexpr (std::is_same_v<Payload, FrameRateCommand>) {
                return CommandType::SetFrameRate;
            } else if constexpr (std::is_same_v<Payload, ResolutionCommand>) {
                return CommandType::SetResolution;
            } else {
                static_assert(kDependentFalse<Payload>, "Unhandled command payload type.");
            }
        },
        command);
}

CommandValidationResult validate_command(const Command& command)
{
    return std::visit(
        [](const auto& payload) -> CommandValidationResult {
            using Payload = std::decay_t<decltype(payload)>;
            if constexpr (std::is_same_v<Payload, ConnectCommand>
                || std::is_same_v<Payload, DisconnectCommand>) {
                return valid_command();
            } else if constexpr (std::is_same_v<Payload, FrameRateCommand>) {
                if (is_supported_frame_rate(payload.frames_per_second)) {
                    return valid_command();
                }

                return unsupported_setting("Unsupported frame rate. Supported range is 1-240 FPS.");
            } else if constexpr (std::is_same_v<Payload, ResolutionCommand>) {
                if (is_supported_resolution(payload.width, payload.height)) {
                    return valid_command();
                }

                return unsupported_setting("Unsupported resolution. Supported range is 1x1-7680x4320.");
            } else {
                static_assert(kDependentFalse<Payload>, "Unhandled command payload type.");
            }
        },
        command);
}

bool is_valid_command(const Command& command)
{
    return validate_command(command).valid;
}

}  // namespace camera::common
