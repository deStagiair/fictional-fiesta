/// @file Implementation of the command line utilities.

#include "test/test_utils/itf/CommandLineUtils.h"

namespace testutils
{

bool commandLineAccessible()
{
  return system(nullptr) != 0;
}

int runCommand(const std::string& command)
{
  return system(command.c_str());
}

} // namespace testutils
