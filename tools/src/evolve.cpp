#include "fictional-fiesta/world/itf/World.h"
#include "fictional-fiesta/world/itf/Location.h"

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
    ("world,w", po::value<std::string>(), "Path to the initial world state.");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, description), vm);
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

  constexpr auto world_option = "world";
  if (!vm.count(world_option))
  {
    missing_option(world_option);
    return 1;
  }

  const auto world_filename = vm[world_option].as<std::string>();

  std::cout << "Evolving " << cycle_count << " cycles...\n";
  std::cout << "Initial world file: " << world_filename << "\n";

  const auto& world_path = fs::path(world_filename);
  auto world = World{world_path};

  auto rng = FSM::createRng();
  for (int cycle_index = 0; cycle_index < cycle_count; ++cycle_index)
  {
    std::cout << "Cycle " << cycle_index << ":\n";
    world.cycle(rng);
    //std::cout << "Population : " << location.getIndividuals().size() << std::endl;

    //location.cycle(rng);
  }
}

namespace
{

void missing_option(const std::string& option)
{
  std::cerr << "Missing mandatory option '" + option + "'.\n";
}

}
