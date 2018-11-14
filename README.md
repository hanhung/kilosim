# KiloSim: Kilobot Simulator

This is maintained on GitHub in the [kilobot-simulator](https://github.com/jtebert/kilosim) repository. You can [submit any issues or questions here](https://github.com/jtebert/kilosim/issues).

---

KiloSim is designed to be a fast, lightweight, pseudo-physical* simulator for Kilobots. Notable benefits include:

- Directly use code written for Kilobots, using the same Kilolib API
- Included Logger to easily to save experiment parameters in log continuous state data
- Includes support for ambient light sensing
- Cross-platform viewer for debugging and recording simulations
- [Coming soon] Parallelization with OpenMP
- [Coming soon] Easy configuration with JSON files to run multiple and varied experiments

_* Pseudo-physical means that it is spatial and handles issues like collisions in a functional but hand-wavy manner. We make no attempt to accurately model true physical interactions. If you want to see what this means, run an example simulation with the viewer._

## Installing and Using

### Dependencies

[HDF5](https://portal.hdfgroup.org/display/HDF5/HDF5) and [SFML](https://www.sfml-dev.org/index.php). Install on Ubuntu-like systems with:

 `sudo apt install libsfml-dev libhdf5-dev`

### Compile

**TODO: This needs a proper make/cmake file instead of my hacky bash scripts**

`./make_test.sh`

### Run

`./bin/kilosim`

### Build Documentation

(Requires Doxygen to be installed.)

`doxygen`

This will automatically use the settings in `Doxyfile` and save the results to `docs/`

## Configuration and Parameters

*This doesn't exist yet. This is wishful thinking about I'll eventually have.*

A `ConfigParser` class is provided to load JSON configuration files and pass them to a `Logger`. The user is responsible for passing any configuration parameters to other objects where necessary (for example, specifying the trial number when creating the `Logger`.) However, an example is provided in `exampleConfig.json`.

- [JSON?](https://github.com/nlohmann/json)
- [YAML?](https://github.com/jbeder/yaml-cpp)
- Explain configuration files... when they exist
