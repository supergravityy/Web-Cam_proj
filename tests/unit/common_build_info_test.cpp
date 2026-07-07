#include "camera/common/build_info.h"

#include <gtest/gtest.h>

TEST(CommonBuildInfoTest, ProvidesBaselineProjectMetadata)
{
    EXPECT_EQ(camera::common::project_name(), "Web-Cam_proj");
    EXPECT_EQ(camera::common::common_component_name(), "camera_common");
    EXPECT_GE(camera::common::common_api_version(), 1);
}
