#pragma once

#include "camera/common/error.h"

#include <array>
#include <string>
#include <string_view>

namespace camera::common {

inline constexpr int kRtspPort = 8554;
inline constexpr std::string_view kRtspPath = "/camera";

inline constexpr int kDefaultVideoWidth = 1920;
inline constexpr int kDefaultVideoHeight = 1080;
inline constexpr int kDefaultVideoFrameRateFps = 30;

enum class VideoCodec {
    H264,
    Mjpeg,
};

struct Resolution {
    int width;
    int height;
};

struct VideoFormat {
    Resolution resolution;
    int frames_per_second;
    VideoCodec codec;
};

inline constexpr std::array<Resolution, 3> kSupportedVideoResolutions{{
    {1280, 720},
    {1920, 1080},
    {3840, 2160},
}};

inline constexpr std::array<VideoCodec, 2> kSupportedVideoCodecs{{
    VideoCodec::H264,
    VideoCodec::Mjpeg,
}};

struct VideoPolicyValidationResult {
    bool valid;
    ErrorCode error_code;
    std::string_view message;
};

std::string make_rtsp_url(std::string_view server_ip);
std::string_view to_string(VideoCodec codec);

VideoFormat default_video_format();
bool is_supported_resolution(Resolution resolution);
bool is_supported_codec(VideoCodec codec);
bool is_supported_video_format(const VideoFormat& format);
VideoPolicyValidationResult validate_video_format(const VideoFormat& format);

}  // namespace camera::common
