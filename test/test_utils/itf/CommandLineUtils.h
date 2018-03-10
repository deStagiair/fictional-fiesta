#ifndef INCLUDE_TEST_TEST_UTILS_COMMAND_LINE_UTILS_H
#define INCLUDE_TEST_TEST_UTILS_COMMAND_LINE_UTILS_H

#include <string>

namespace testutils
{

/// @brief Check whether the command line is accessible.
///
/// @return true if the command line is accessible and false if not.
bool commandLineAccessible();

/// @brief Runs a command in the command line.
///
/// @param command String representing the command.
/// @return return value of the command executed.
int runCommand(const std::string& command);

} // namespace testutils

#endif
