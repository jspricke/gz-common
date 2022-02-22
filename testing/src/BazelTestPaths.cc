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

#include "ignition/common/testing/BazelTestPaths.hh"

#include <ignition/common/Console.hh>
#include <ignition/common/Util.hh>

namespace ignition::common::testing
{

//////////////////////////////////////////////////
BazelTestPaths::~BazelTestPaths() = default;

//////////////////////////////////////////////////
bool BazelTestPaths::ProjectSourcePath(std::string &_sourceDir) {
  std::string test_srcdir, bazel_path;

  if (common::env("TEST_SRCDIR", test_srcdir) &&
      common::env("IGN_BAZEL_PATH", bazel_path))
  {
    _sourceDir = ignition::common::joinPaths(test_srcdir,
                                             "ignition",
                                             bazel_path);
    return true;
  }
  else
  {
    return false;
  }
}

//////////////////////////////////////////////////
bool BazelTestPaths::TestTmpPath(std::string &_tmpDir) {
  return common::env("TEST_UNDECLARED_OUTPUTS_DIR", _tmpDir);
}

}  // namespace ignition::common::testing

