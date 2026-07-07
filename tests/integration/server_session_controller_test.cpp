#include "camera/server/session_controller.h"

#include "camera/common/command.h"
#include "camera/common/error.h"
#include "camera/common/video_policy.h"

#include <gtest/gtest.h>

#include <string>

TEST(ServerSessionControllerTest, StartsDisconnectedWithDefaultSettings)
{
    const camera::server::SessionController controller;

    EXPECT_FALSE(controller.has_active_client());
    EXPECT_EQ(controller.active_client_id(), "");
    EXPECT_EQ(controller.frame_rate(), camera::common::kDefaultVideoFrameRateFps);
    EXPECT_EQ(controller.resolution().width, camera::common::kDefaultVideoWidth);
    EXPECT_EQ(controller.resolution().height, camera::common::kDefaultVideoHeight);
}

TEST(ServerSessionControllerTest, ConnectsClientAndTreatsDuplicateConnectAsSuccess)
{
    camera::server::SessionController controller;

    const auto first = controller.connect_client("client-a");
    const auto duplicate = controller.connect_client("client-a");

    EXPECT_TRUE(first.success);
    EXPECT_EQ(first.error_code, camera::common::ErrorCode::None);
    EXPECT_TRUE(duplicate.success);
    EXPECT_EQ(duplicate.error_code, camera::common::ErrorCode::None);
    EXPECT_TRUE(controller.has_active_client());
    EXPECT_EQ(controller.active_client_id(), "client-a");
}

TEST(ServerSessionControllerTest, RejectsSecondClientWhileActiveClientIsConnected)
{
    camera::server::SessionController controller;

    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto response = controller.connect_client("client-b");

    EXPECT_FALSE(response.success);
    EXPECT_EQ(response.error_code, camera::common::ErrorCode::ConnectionFailure);
    EXPECT_EQ(controller.active_client_id(), "client-a");
}

TEST(ServerSessionControllerTest, DisconnectsActiveClient)
{
    camera::server::SessionController controller;

    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto response = controller.disconnect_client("client-a");

    EXPECT_TRUE(response.success);
    EXPECT_EQ(response.error_code, camera::common::ErrorCode::None);
    EXPECT_FALSE(controller.has_active_client());
    EXPECT_EQ(controller.active_client_id(), "");
}

TEST(ServerSessionControllerTest, RejectsInactiveClientDisconnectWithoutClearingActiveSession)
{
    camera::server::SessionController controller;

    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto response = controller.disconnect_client("client-b");

    EXPECT_FALSE(response.success);
    EXPECT_EQ(response.error_code, camera::common::ErrorCode::ConnectionFailure);
    EXPECT_TRUE(controller.has_active_client());
    EXPECT_EQ(controller.active_client_id(), "client-a");
}

TEST(ServerSessionControllerTest, UpdatesFrameRateAndResolutionForActiveClient)
{
    camera::server::SessionController controller;

    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto frame_rate = controller.handle_command("client-a", camera::common::make_frame_rate_command(60));
    const auto resolution = controller.handle_command("client-a", camera::common::make_resolution_command(3840, 2160));

    EXPECT_TRUE(frame_rate.success);
    EXPECT_EQ(frame_rate.error_code, camera::common::ErrorCode::None);
    EXPECT_TRUE(resolution.success);
    EXPECT_EQ(resolution.error_code, camera::common::ErrorCode::None);
    EXPECT_EQ(controller.frame_rate(), 60);
    EXPECT_EQ(controller.resolution().width, 3840);
    EXPECT_EQ(controller.resolution().height, 2160);
}

TEST(ServerSessionControllerTest, RejectsInvalidCommandUsingCommonValidationResult)
{
    camera::server::SessionController controller;

    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto frame_rate_response = controller.handle_command("client-a", camera::common::make_frame_rate_command(0));
    const auto frame_rate_validation = camera::common::validate_command(camera::common::make_frame_rate_command(0));
    const auto resolution_response = controller.handle_command("client-a", camera::common::make_resolution_command(0, 1080));
    const auto resolution_validation = camera::common::validate_command(camera::common::make_resolution_command(0, 1080));

    EXPECT_FALSE(frame_rate_response.success);
    EXPECT_EQ(frame_rate_response.error_code, frame_rate_validation.error_code);
    EXPECT_EQ(frame_rate_response.message, std::string(frame_rate_validation.message));
    EXPECT_FALSE(resolution_response.success);
    EXPECT_EQ(resolution_response.error_code, resolution_validation.error_code);
    EXPECT_EQ(resolution_response.message, std::string(resolution_validation.message));
    EXPECT_EQ(controller.frame_rate(), camera::common::kDefaultVideoFrameRateFps);
    EXPECT_EQ(controller.resolution().width, camera::common::kDefaultVideoWidth);
    EXPECT_EQ(controller.resolution().height, camera::common::kDefaultVideoHeight);
}

TEST(ServerSessionControllerTest, RejectsCommandFromDisconnectedOrInactiveClient)
{
    camera::server::SessionController controller;

    const auto disconnected = controller.handle_command("client-a", camera::common::make_resolution_command(1280, 720));
    ASSERT_TRUE(controller.connect_client("client-a").success);
    const auto inactive = controller.handle_command("client-b", camera::common::make_frame_rate_command(30));

    EXPECT_FALSE(disconnected.success);
    EXPECT_EQ(disconnected.error_code, camera::common::ErrorCode::ConnectionFailure);
    EXPECT_FALSE(inactive.success);
    EXPECT_EQ(inactive.error_code, camera::common::ErrorCode::ConnectionFailure);
}

TEST(ServerSessionControllerTest, RoutesConnectAndDisconnectCommandsThroughHandler)
{
    camera::server::SessionController controller;

    const auto connect = controller.handle_command("client-a", camera::common::make_connect_command());
    const auto disconnect = controller.handle_command("client-a", camera::common::make_disconnect_command());

    EXPECT_TRUE(connect.success);
    EXPECT_TRUE(disconnect.success);
    EXPECT_FALSE(controller.has_active_client());
}
