# ![Kilosim logo](docs/logo.svg) Kilosim: Kilobot Simulator

[![Build Status](https://travis-ci.com/jtebert/kilosim.svg?token=s6ZVW1bvfNjgbZQh2x9M&branch=master)](https://travis-ci.com/jtebert/kilosim)
[![GitHub Issues](https://img.shields.io/github/issues/jtebert/kilosim.svg)](https://github.com/jtebert/kilosim/issues)
[![GitHub release](https://img.shields.io/github/release-pre/jtebert/kilosim?color=yellow)](https://github.com/jtebert/kilosim/releases)
[![DOI](https://zenodo.org/badge/151430556.svg)](https://zenodo.org/badge/latestdoi/151430556)


This is maintained on GitHub in the [kilosim repository](https://github.com/jtebert/kilosim). You can [submit any issues or questions here](https://github.com/jtebert/kilosim/issues).

[**Full Documentation**](https://jtebert.github.io/kilosim/index.html)

---

Kilosim is a fast, lightweight, pseudo-physical* C++ simulator for Kilobot robots. Notable benefits include:

- Pseudo-physical model means fast simulation for high-throughput
- Easily re-use code written for Kilobots, using the same Kilolib API
- Includes support for ambient light sensing
- Included `Logger` to easily to save experiment parameters in log continuous state data
- Cross-platform `Viewer` for debugging and recording simulations
- Easy configuration with JSON files to run multiple trials and varied experiments
- *[In progress]* Parallelization with OpenMP

\* *Pseudo-physical means that it is spatial and handles issues like collisions in a functional but hand-wavy manner. We make no attempt to accurately model true physical interactions. If you want to see what this means, run an example simulation with the Viewer.*

Note that this project is currently in a pre-release state and may still contain bugs, incomplete documentation, and missing features. If you have issues using the code, contact the developers or [open an issue](https://github.com/jtebert/kilosim/issues/new).

## Installing and Using

**NOTE:** At this time, we only support Kilosim on Linux. Other operating systems will be supported by a full release.

You can either [clone the repository from GitHub](https://github.com/jtebert/kilosim) or [download the latest release](https://github.com/jtebert/kilosim/releases).

### Dependencies

[HDF5](https://portal.hdfgroup.org/display/HDF5/HDF5), [SFML](https://www.sfml-dev.org/index.php), and [OpenMP](https://www.openmp.org/). Install on Ubuntu-like systems with: `sudo apt install libsfml-dev libhdf5-dev libomp-dev`

[nlohmann/json](https://github.com/nlohmann/json): Add [`json.hpp`](https://github.com/nlohmann/json/releases/download/v3.5.0/json.hpp) to the `include/` folder. **Note:** This links to the most recent release (3.5) that has been verified for compatibility. You can find other [versions and release notes on Github](https://github.com/nlohmann/json/releases).

### Compile

Create a static library at `bin/libKilosim.a`:

    make
or

    make static

Create an executable at `bin/kilosim` using the example `MyKilobot.cpp` and `test.cpp`:

    make exec

**NOTE:** This is tested with g++ 7.3 but currently fails (for as-of-yet unclear reasons) with g++ 8.1

### Run

Run the executable generated by `make exec`

    ./bin/kilosim

### Using static library

**TODO:** Write tutorial on linking to static library


## Configuration and Parameters

Configuration files are defined as JSON files and can be loaded with a ConfigParser. The contents of flat JSON files can be automatically saved with your data using the Logger. (Support for saving JSON objects and arrays to HDF5 may be added in the future if someone needs/wants it.)

There are no fixed requirements for the contents of the configuration files; it's an un-opinionated convenience tool for importing and using whatever (atomic) parameters you want.

## Support

If you are having issues installing or using the simulator, [open an issue](https://github.com/jtebert/kilosim/issues/new) or [email Julia](mailto:julia@juliaebert.com).

### Known Issues

- Fails with GCC 8 (We suspect this is a GCC bug; see [issue #23](https://github.com/jtebert/kilosim/issues/23).) **Workaround:** Change your GCC version.
- Viewer does not work over SSH

## Citing

If you use this software, please cite it as follows:

**DOI (v0.3):** [10.5281/zenodo.3406865](https://doi.org/10.5281/zenodo.3406865)

**DOI (all/latest version):** [10.5281/zenodo.3406864](https://doi.org/10.5281/zenodo.3406864)

**BibTeX:**

```bibtex
@misc{julia_ebert_2019_3406865,
  author       = {Julia Ebert and
                  Richard Barnes},
  title        = {Kilosim},
  month        = sep,
  year         = 2019,
  doi          = {10.5281/zenodo.3406865},
  url          = {https://doi.org/10.5281/zenodo.3406865}
}
```

## Contributing

We welcome contributions to the repository. To find things we're currently looking for help with, [check out the open issues](https://github.com/jtebert/kilosim/issues?utf8=✓&q=is%3Aissue+is%3Aopen+).

If you discover a bug or have an idea, for an improvement, [open an issue](https://github.com/jtebert/kilosim/issues/new).

If you add something you think would be useful to others, submit a pull request. All code should be [fully documented](http://www.doxygen.nl/manual/docblocks.html). You can check your documentation by [building the documentation locally](#build-documentation) Code reviews will be required for all pull requests, but we currently do not perform unit testing.

See a [full list of the contributors and their contributions here](CONTRIBUTORS.md).

### Build Documentation

Build the HTML documentation: (Requires Doxygen to be installed.)

    doxygen

This will automatically use the settings in `Doxyfile` and save the results to `docs/`. (The latest full documentation is automatically generated and published [here](https://jtebert.github.io/kilosim/index.html).)

## License

This software is released under the [MIT License](LICENSE).

If you use this software for a publication, please cite it.
