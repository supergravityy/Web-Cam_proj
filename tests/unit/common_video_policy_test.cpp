#include "camera/common/video_policy.h"

#include <gtest/gtest.h>

TEST(CommonVideoPolicyTest, BuildsFixedRtspUrl)
{
    EXPECT_EQ(camera::common::kRtspPort, 8554);
    EXPECT_EQ(camera::common::kRtspPath, "/camera");
    EXPECT_EQ(camera::common::make_rtsp_url("192.168.0.10"), "rtsp://192.168.0.10:8554/camera");
}

TEST(CommonVideoPolicyTest, ProvidesDefaultVideoFormat)
{
    const auto format = camera::common::default_video_format();

    EXPECT_EQ(format.resolution.width, 1920);
    EXPECT_EQ(format.resolution.height, 1080);
    EXPECT_EQ(format.frames_per_second, 30);
    EXPECT_EQ(format.codec, camera::common::VideoCodec::H264);
    EXPECT_TRUE(camera::common::is_supported_video_format(format));
}

TEST(CommonVideoPolicyTest, AcceptsRequiredResolutions)
{
    EXPECT_TRUE(camera::common::is_supported_resolution({1280, 720}));
    EXPECT_TRUE(camera::common::is_supported_resolution({1920, 1080}));
    EXPECT_TRUE(camera::common::is_supported_resolution({3840, 2160}));
}

TEST(CommonVideoPolicyTest, AcceptsRequiredCodecs)
{
    EXPECT_TRUE(camera::common::is_supported_codec(camera::common::VideoCodec::H264));
    EXPECT_TRUE(camera::common::is_supported_codec(camera::common::VideoCodec::Mjpeg));
    EXPECT_EQ(camera::common::to_string(camera::common::VideoCodec::H264), "H.264");
    EXPECT_EQ(camera::common::to_string(camera::common::VideoCodec::Mjpeg), "MJPEG");
}

TEST(CommonVideoPolicyTest, RejectsUnsupportedVideoFormat)
{
    const auto unsupported_resolution = camera::common::validate_video_format(
        {{640, 480}, camera::common::kDefaultVideoFrameRateFps, camera::common::VideoCodec::H264});
    const auto unsupported_frame_rate = camera::common::validate_video_format(
        {{1920, 1080}, 60, camera::common::VideoCodec::H264});
    const auto unsupported_codec = camera::common::validate_video_format(
        {{1920, 1080}, camera::common::kDefaultVideoFrameRateFps, static_cast<camera::common::VideoCodec>(999)});

    EXPECT_FALSE(unsupported_resolution.valid);
    EXPECT_EQ(unsupported_resolution.error_code, camera::common::ErrorCode::UnsupportedSetting);
    EXPECT_FALSE(unsupported_frame_rate.valid);
    EXPECT_EQ(unsupported_frame_rate.error_code, camera::common::ErrorCode::UnsupportedSetting);
    EXPECT_FALSE(unsupported_codec.valid);
    EXPECT_EQ(unsupported_codec.error_code, camera::common::ErrorCode::UnsupportedSetting);
}
