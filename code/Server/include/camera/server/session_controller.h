#pragma once

#include "camera/common/command.h"
#include "camera/common/error.h"
#include "camera/common/video_policy.h"

#include <string>
#include <string_view>

namespace camera::server {

struct ServerResponse {
    bool success;
    camera::common::ErrorCode error_code;
    std::string message;
};

class SessionController {
public:
    SessionController();

    ServerResponse connect_client(std::string_view client_id);
    ServerResponse disconnect_client(std::string_view client_id);
    ServerResponse handle_command(std::string_view client_id, const camera::common::Command& command);

    bool has_active_client() const;
    bool is_active_client(std::string_view client_id) const;
    std::string active_client_id() const;

    int frame_rate() const;
    camera::common::Resolution resolution() const;
    camera::common::VideoFormat video_format() const;

private:
    ServerResponse apply_frame_rate(int frames_per_second);
    ServerResponse apply_resolution(camera::common::Resolution resolution);
    ServerResponse reject_inactive_client(std::string_view client_id) const;

    std::string active_client_id_;
    camera::common::VideoFormat video_format_;
};

}  // namespace camera::server
