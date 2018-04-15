#include "fictional-fiesta/world/itf/Individual.h"
#include "fictional-fiesta/world/itf/Location.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <boost/program_options.hpp>

#include <experimental/filesystem>

#include <iostream>

namespace fs = std::experimental::filesystem;
namespace po = boost::program_options;

using namespace fictionalfiesta;

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


  const auto& state_path = fs::path(state_filename);
  const auto& document = XmlDocument{state_path};

  auto rng = FSM::createRng();
  auto location = Location(document.getRootNode());
  for (int cycle_index = 0; cycle_index < cycle_count; ++cycle_index)
  {
    std::cout << "Cycle " << cycle_index << ":\n";
    std::cout << "Population : " << location.getIndividuals().size() << std::endl;

    location.cycle(rng);
  }
}

namespace
{

void missing_option(const std::string& option)
{
  std::cerr << "Missing mandatory option '" + option + "'.\n";
}

}
