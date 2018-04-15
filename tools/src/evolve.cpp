#include "fictional-fiesta/world/itf/Location.h"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

namespace
{
void missing_option(const std::string& option);
}

int main(int argc, char* argv[])
{
  // Declare the supported options.
  po::options_description description("Allowed options");
  description.add_options()
    ("help,h", "Produce help message.")
    ("cycles,c", po::value<int>(), "Number of cycles (iterations).")
    ("initial-state,i", po::value<std::string>(), "Path to the initial world state.");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, description), vm);
  po::notify(vm);

  po::positional_options_description p;
  p.add("initial-state", -1);

  po::store(po::command_line_parser(argc, argv).
      options(description).positional(p).run(), vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cout << description << "\n";
    return 1;
  }

  constexpr auto cycles_option = "cycles";

  if (!vm.count(cycles_option))
  {
    missing_option(cycles_option);
    return 1;
  }

  const auto cycle_count = vm[cycles_option].as<int>();

  constexpr auto initial_option = "initial-state";
  if (!vm.count(initial_option))
  {
    missing_option(initial_option);
    return 1;
  }

  const auto state_filename = vm[initial_option].as<std::string>();

  std::cout << "Evolving " << cycle_count << " cycles...\n";
  std::cout << "Initial state file: " << state_filename << "\n";
}

namespace
{

void missing_option(const std::string& option)
{
  std::cerr << "Missing mandatory option '" + option + "'.\n";
}

}
