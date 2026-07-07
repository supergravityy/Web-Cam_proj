#include "camera/common/command.h"

#include <gtest/gtest.h>

#include <variant>

TEST(CommonCommandTest, AcceptsConnectAndDisconnectCommands)
{
    const auto connect = camera::common::make_connect_command();
    const auto disconnect = camera::common::make_disconnect_command();

    EXPECT_EQ(camera::common::command_type(connect), camera::common::CommandType::Connect);
    EXPECT_TRUE(camera::common::is_valid_command(connect));
    EXPECT_EQ(camera::common::validate_command(connect).error_code, camera::common::ErrorCode::None);

    EXPECT_EQ(camera::common::command_type(disconnect), camera::common::CommandType::Disconnect);
    EXPECT_TRUE(camera::common::is_valid_command(disconnect));
    EXPECT_EQ(camera::common::validate_command(disconnect).error_code, camera::common::ErrorCode::None);
}

TEST(CommonCommandTest, AcceptsSupportedFrameRateCommand)
{
    const auto command = camera::common::make_frame_rate_command(30);

    ASSERT_TRUE(std::holds_alternative<camera::common::FrameRateCommand>(command));
    EXPECT_EQ(std::get<camera::common::FrameRateCommand>(command).frames_per_second, 30);
    EXPECT_EQ(camera::common::command_type(command), camera::common::CommandType::SetFrameRate);
    EXPECT_TRUE(camera::common::is_valid_command(command));
}

TEST(CommonCommandTest, RejectsUnsupportedFrameRateCommand)
{
    const auto too_low = camera::common::validate_command(camera::common::make_frame_rate_command(0));
    const auto too_high = camera::common::validate_command(
        camera::common::make_frame_rate_command(camera::common::kMaxFrameRateFps + 1));

    EXPECT_FALSE(too_low.valid);
    EXPECT_EQ(too_low.error_code, camera::common::ErrorCode::UnsupportedSetting);
    EXPECT_FALSE(too_high.valid);
    EXPECT_EQ(too_high.error_code, camera::common::ErrorCode::UnsupportedSetting);
}

TEST(CommonCommandTest, AcceptsSupportedResolutionCommand)
{
    const auto command = camera::common::make_resolution_command(1920, 1080);

    ASSERT_TRUE(std::holds_alternative<camera::common::ResolutionCommand>(command));
    EXPECT_EQ(std::get<camera::common::ResolutionCommand>(command).width, 1920);
    EXPECT_EQ(std::get<camera::common::ResolutionCommand>(command).height, 1080);
    EXPECT_EQ(camera::common::command_type(command), camera::common::CommandType::SetResolution);
    EXPECT_TRUE(camera::common::is_valid_command(command));
}

TEST(CommonCommandTest, RejectsUnsupportedResolutionCommand)
{
    const auto zero_width = camera::common::validate_command(camera::common::make_resolution_command(0, 1080));
    const auto too_wide = camera::common::validate_command(
        camera::common::make_resolution_command(camera::common::kMaxResolutionWidth + 1, 1080));
    const auto too_tall = camera::common::validate_command(
        camera::common::make_resolution_command(1920, camera::common::kMaxResolutionHeight + 1));

    EXPECT_FALSE(zero_width.valid);
    EXPECT_EQ(zero_width.error_code, camera::common::ErrorCode::UnsupportedSetting);
    EXPECT_FALSE(too_wide.valid);
    EXPECT_EQ(too_wide.error_code, camera::common::ErrorCode::UnsupportedSetting);
    EXPECT_FALSE(too_tall.valid);
    EXPECT_EQ(too_tall.error_code, camera::common::ErrorCode::UnsupportedSetting);
}
