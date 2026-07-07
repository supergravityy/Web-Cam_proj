#include "camera/common/video_policy.h"

#include <algorithm>

namespace camera::common {
namespace {

VideoPolicyValidationResult valid_video_format()
{
    return {true, ErrorCode::None, "Video format is valid."};
}

VideoPolicyValidationResult unsupported_setting(std::string_view message)
{
    return {false, ErrorCode::UnsupportedSetting, message};
}

bool is_supported_frame_rate(int frames_per_second)
{
    return frames_per_second == kDefaultVideoFrameRateFps;
}

}  // namespace

std::string make_rtsp_url(std::string_view server_ip)
{
    std::string url = "rtsp://";
    url.append(server_ip.data(), server_ip.size());
    url += ":";
    url += std::to_string(kRtspPort);
    url += kRtspPath;
    return url;
}

std::string_view to_string(VideoCodec codec)
{
    switch (codec) {
        case VideoCodec::H264:
            return "H.264";
        case VideoCodec::Mjpeg:
            return "MJPEG";
    }

    return "Unknown";
}

VideoFormat default_video_format()
{
    return {{kDefaultVideoWidth, kDefaultVideoHeight}, kDefaultVideoFrameRateFps, VideoCodec::H264};
}

bool is_supported_resolution(Resolution resolution)
{
    return std::any_of(kSupportedVideoResolutions.begin(), kSupportedVideoResolutions.end(),
        [resolution](const Resolution& supported) {
            return supported.width == resolution.width && supported.height == resolution.height;
        });
}

bool is_supported_codec(VideoCodec codec)
{
    return std::any_of(kSupportedVideoCodecs.begin(), kSupportedVideoCodecs.end(),
        [codec](VideoCodec supported) {
            return supported == codec;
        });
}

bool is_supported_video_format(const VideoFormat& format)
{
    return validate_video_format(format).valid;
}

VideoPolicyValidationResult validate_video_format(const VideoFormat& format)
{
    if (!is_supported_resolution(format.resolution)) {
        return unsupported_setting("Unsupported video resolution. Supported values are 1280x720, 1920x1080, 3840x2160.");
    }

    if (!is_supported_frame_rate(format.frames_per_second)) {
        return unsupported_setting("Unsupported video frame rate. Default and supported value is 30 FPS.");
    }

    if (!is_supported_codec(format.codec)) {
        return unsupported_setting("Unsupported video codec. Supported values are H.264 and MJPEG.");
    }

    return valid_video_format();
}

}  // namespace camera::common
