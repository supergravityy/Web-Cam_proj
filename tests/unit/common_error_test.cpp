#include "camera/common/error.h"

#include <gtest/gtest.h>

TEST(CommonErrorTest, ConvertsKnownErrorCodesToUserText)
{
    EXPECT_EQ(camera::common::to_user_text(camera::common::ErrorCode::None), "No error.");
    EXPECT_EQ(camera::common::to_user_text(camera::common::ErrorCode::ConnectionFailure),
        "Connection failed. Check network and camera availability.");
    EXPECT_EQ(camera::common::to_user_text(camera::common::ErrorCode::StreamingFailure),
        "Streaming failed. Check camera stream state.");
    EXPECT_EQ(camera::common::to_user_text(camera::common::ErrorCode::CommandFailure),
        "Command failed. Check the requested camera command.");
    EXPECT_EQ(camera::common::to_user_text(camera::common::ErrorCode::UnsupportedSetting),
        "Unsupported camera setting.");
}

TEST(CommonErrorTest, ConvertsUnknownErrorCodeToFallbackText)
{
    const auto unknown_code = static_cast<camera::common::ErrorCode>(999);

    EXPECT_EQ(camera::common::to_user_text(unknown_code), "Unknown camera error.");
}
