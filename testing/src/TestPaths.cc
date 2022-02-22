/*
* Copyright (C) 2022 Open Source Robotics Foundation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include "ignition/common/testing/TestPaths.hh"
#include "ignition/common/testing/BazelTestPaths.hh"
#include "ignition/common/testing/CMakeTestPaths.hh"

#include <ignition/common/Console.hh>
#include <ignition/common/Util.hh>

namespace ignition::common::testing
{
//////////////////////////////////////////////////
TestPaths::TestPaths(const std::string &_projectSourcePath)
  : projectSourcePath(_projectSourcePath)
{
}

//////////////////////////////////////////////////
TestPaths::~TestPaths() = default;

//////////////////////////////////////////////////
BuildType TestBuildType(const std::string &_projectSourcePath)
{
  std::string ign_bazel;
  bool ign_bazel_set = common::env("IGN_BAZEL", ign_bazel);
  bool ign_cmake_set = !_projectSourcePath.empty();

  if (ign_bazel_set)
    return BuildType::kBazel;
  else if (ign_cmake_set)
    return BuildType::kCMake;
  else
    return BuildType::kUnknown;
}

//////////////////////////////////////////////////
std::unique_ptr<TestPaths>
TestPathFactory(const std::string &_projectSourcePath)
{
  std::unique_ptr<TestPaths> ret {nullptr};

  switch(TestBuildType(_projectSourcePath))
  {
    case BuildType::kBazel:
      ret = std::make_unique<BazelTestPaths>(_projectSourcePath);
      break;
    case BuildType::kCMake:
      ret = std::make_unique<CMakeTestPaths>(_projectSourcePath);
      break;
    case BuildType::kUnknown:
      ret = nullptr;
      break;
    default:
      ret = nullptr;
      break;
  }
  return ret;
}

//////////////////////////////////////////////////
std::shared_ptr<ignition::common::TempDirectory>
MakeTestTempDirectoryImpl(const std::string &_projectSourcePath,
                          const std::string &_prefix,
                          const std::string &_subDir,
                          bool _cleanup)
{
  auto testPaths = TestPathFactory(_projectSourcePath);

  if (!testPaths)
    return nullptr;

  std::string dataDir;
  testPaths->TestTmpPath(dataDir);

  if (dataDir.empty())
    return nullptr;

  return std::make_shared<ignition::common::TempDirectory>(
      dataDir, _prefix, _subDir, _cleanup);
}

}  // namespace ignition::common::testing
