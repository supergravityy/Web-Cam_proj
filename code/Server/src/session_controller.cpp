#include "camera/server/session_controller.h"

#include <type_traits>
#include <utility>
#include <variant>

namespace camera::server {
namespace {

template <typename>
inline constexpr bool kDependentFalse = false;

ServerResponse success_response(std::string message)
{
    return {true, camera::common::ErrorCode::None, std::move(message)};
}

ServerResponse error_response(camera::common::ErrorCode error_code, std::string message)
{
    return {false, error_code, std::move(message)};
}

bool is_empty(std::string_view value)
{
    return value.empty();
}

}  // namespace

SessionController::SessionController()
    : video_format_(camera::common::default_video_format())
{
}

ServerResponse SessionController::connect_client(std::string_view client_id)
{
    if (is_empty(client_id)) {
        return error_response(camera::common::ErrorCode::ConnectionFailure, "Client id is required.");
    }

    if (!has_active_client()) {
        active_client_id_.assign(client_id.data(), client_id.size());
        return success_response("Client connected.");
    }

    if (is_active_client(client_id)) {
        return success_response("Client is already connected.");
    }

    return error_response(camera::common::ErrorCode::ConnectionFailure,
        "Another client is already connected. Only one active client is supported.");
}

ServerResponse SessionController::disconnect_client(std::string_view client_id)
{
    if (!is_active_client(client_id)) {
        return reject_inactive_client(client_id);
    }

    active_client_id_.clear();
    return success_response("Client disconnected.");
}

ServerResponse SessionController::handle_command(std::string_view client_id, const camera::common::Command& command)
{
    return std::visit(
        [this, client_id](const auto& payload) -> ServerResponse {
            using Payload = std::decay_t<decltype(payload)>;

            if constexpr (std::is_same_v<Payload, camera::common::ConnectCommand>) {
                return connect_client(client_id);
            } else if constexpr (std::is_same_v<Payload, camera::common::DisconnectCommand>) {
                return disconnect_client(client_id);
            } else if constexpr (std::is_same_v<Payload, camera::common::FrameRateCommand>) {
                if (!is_active_client(client_id)) {
                    return reject_inactive_client(client_id);
                }

                const auto validation = camera::common::validate_command(
                    camera::common::make_frame_rate_command(payload.frames_per_second));
                if (!validation.valid) {
                    return error_response(validation.error_code, std::string(validation.message));
                }

                return apply_frame_rate(payload.frames_per_second);
            } else if constexpr (std::is_same_v<Payload, camera::common::ResolutionCommand>) {
                if (!is_active_client(client_id)) {
                    return reject_inactive_client(client_id);
                }

                const auto validation = camera::common::validate_command(
                    camera::common::make_resolution_command(payload.width, payload.height));
                if (!validation.valid) {
                    return error_response(validation.error_code, std::string(validation.message));
                }

                return apply_resolution({payload.width, payload.height});
            } else {
                static_assert(kDependentFalse<Payload>, "Unhandled command payload type.");
            }
        },
        command);
}

bool SessionController::has_active_client() const
{
    return !active_client_id_.empty();
}

bool SessionController::is_active_client(std::string_view client_id) const
{
    return has_active_client() && std::string_view(active_client_id_) == client_id;
}

std::string SessionController::active_client_id() const
{
    return active_client_id_;
}

int SessionController::frame_rate() const
{
    return video_format_.frames_per_second;
}

camera::common::Resolution SessionController::resolution() const
{
    return video_format_.resolution;
}

camera::common::VideoFormat SessionController::video_format() const
{
    return video_format_;
}

ServerResponse SessionController::apply_frame_rate(int frames_per_second)
{
    video_format_.frames_per_second = frames_per_second;
    return success_response("Frame rate updated.");
}

ServerResponse SessionController::apply_resolution(camera::common::Resolution resolution)
{
    video_format_.resolution = resolution;
    return success_response("Resolution updated.");
}

ServerResponse SessionController::reject_inactive_client(std::string_view client_id) const
{
    if (is_empty(client_id)) {
        return error_response(camera::common::ErrorCode::ConnectionFailure, "Client id is required.");
    }

    if (!has_active_client()) {
        return error_response(camera::common::ErrorCode::ConnectionFailure, "No active client is connected.");
    }

    return error_response(camera::common::ErrorCode::ConnectionFailure,
        "Client is not the active client for this server session.");
}

}  // namespace camera::server
