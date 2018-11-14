/*
    KiloSim

    Saves the parameters and time series logs of the Kilobot simulator in HDF5
    files

    Created 2018-10 by Julia Ebert
*/

/*
   * ```
  * logFile.h5
  * |__ trial_1  (group)
  * |   |__ time (dataset)  [1 x t]
  * |   |__ params (group)
  * |   |   |__ param1 (dataset)
  * |   |   |__ param2 (dataset)
  * |   |   |__ ...
  * |   |__ aggregator_1 (dataset)  [n x t]
  * |   |__ aggregator_2 (dataset)  [m x t]
  * |   |__ ...
  * |__ trial_2
  * |   |__ time (dataset)  [1 x t]
  * |   |__ params
  * |   |   |__ ...
  * |   |__ ...
  * ...
  * ```
  */

#ifndef __KILOSIM_LOGGER_H
#define __KILOSIM_LOGGER_H

#include "H5PacketTable.h"
#include "H5Cpp.h"
#include "robot.h"
#include "KiloSim.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

namespace KiloSim
{
/*!
 * A Logger is used to save [HDF5](https://portal.hdfgroup.org/display/support)
 * files containing parameters and continuous state information for multiple
 * simulation trials.
 *
 * State information is logged through aggregator functions, which reduce the
 * state of the robots to a vector. This could be a single average value over
 * all the robots (e.g., mean observed ambient light) all the way to saving a
 * value for every robot (e.g., each robot's ambient light value as an
 * element). Each aggregator is saved as an array, where each row is the
 * output of the aggregator function. Whenever the state is logged, the
 * simulator time is also saved as a timeseries.
 *
 * The resulting file structure would look as follows:
 *
 * ```
 * logFile.h5
 * |__ trial_1  (group)
 * |   |__ time (dataset)  [1 x t]
 * |   |__ params (group)
 * |   |   |__ param1 (dataset)
 * |   |   |__ param2 (dataset)
 * |   |   |__ ...
 * |   |__ aggregator_1 (dataset)  [n x t]
 * |   |__ aggregator_2 (dataset)  [m x t]
 * |   |__ ...
 * |__ trial_2
 * |   |__ time (dataset)  [1 x t]
 * |   |__ params
 * |   |   |__ ...
 * |   |__ ...
 * ...
 * ```
 *
 * where `t` is the number of time steps when data was logged, and
 * `aggregator_1` and `aggregator_2` were specified by the user.
 */
class Logger
{
public:
  /*!
   * A function mapping Robots to values
   * This is used by #log_state to compute values to save from all of the
   * robots at a time step. The output will form a row in an H5::PacketTable. It
   * may be one value per robot (e.g., the current motor command) or all the way
   * to one combined value from all the robots (e.g., the mean light perceived).
   *
   * Functions with this signature are the inputs to #add_aggregator
   */
  typedef std::vector<double> (*aggregatorFunc)(std::vector<Robot *> &robots);

protected:
  //! Managed H5File pointer
  typedef std::shared_ptr<H5::H5File> H5FilePtr;
  //! Managed pointer to HDF5 Group
  typedef std::shared_ptr<H5::Group> H5GroupPtr;
  //! Managed pointer to HDF5 PacketTable
  typedef std::shared_ptr<FL_PacketTable> H5PacketTablePtr;
  typedef std::unordered_map<std::string, double> Params;
  //! Pointer to KiloSim World that this Logger tracks
  World *m_world;
  //! HDF5 file where the data lives
  std::string m_file_id;
  //! Trial number specifying group where the data lives
  int m_trial_num;
  //! Names and functions of aggregators
  std::unordered_map<std::string, aggregatorFunc> aggregators;
  //! Opened HDF5 file where this Logger saves
  H5FilePtr m_h5_file;
  //! HDF5 group name for trial. e.g., /trial_0
  std::string m_trial_group_name;
  //! HDF5 group name for trial parameters. e.g., /trial_0/params
  std::string m_params_group_name;
  //! HDF5 group opened within the file for storing/saving parameters
  H5GroupPtr m_params_group;
  //! HDF5 dataset name for time series (packet table)
  std::string m_time_dset_name;
  //! HDF5 PacketTable used to track the time (in seconds) when logging state
  H5PacketTablePtr m_time_table;

public:
  /*!
   * Construct a Logger that logs within the given HDF5 file and group trial_num
   *
   * If the HDF5 file does not exist, it will be created.
   *
   * __WARNING:__ Data will be overwritten if a group already exists in the file
   * for the given trial number. You'll get a warning, but it will be too late.
   * (This should be fixed with an overwrite flag in a future version.)
   *
   * @param world The world from which state and parameters will be logged
   * @param file_id Name and location of the HDF5 file to log stuff in
   * @param trial_num Number of the trial to save the data. Data will be saved
   * in a group named "trial_#", where # is trial_num.
   */
  Logger(World *world, std::string file_id, int trial_num);
  //! Destructor: closes the file when it goes out of scope
  ~Logger();
  /*!
   * Add an aggregator function that will be run on log_state
   * when #log_state is called, all aggregator functions will be called on the
   * robots in the World. The output is saved as a row in a dataset named by #agg_name
   *
   * @param agg_name Name of the dataset in with to store the output of the
   * agg_func. This exists within the trial_# group.
   * @param agg_func Aggregator that saves values from the Robots in the World.
   * Each output is saved as a row in the dataset.
   */
  void add_aggregator(std::string agg_name, aggregatorFunc agg_func);
  /*!
   * Log the aggregators at the given time mapped over all the given robots in the World.
   *
   * __TODO:__ ...I also haven't implemented this.
   */
  void log_state();
  /*!
   * Log all of the given parameters
   *
   * __TODO:__ This needs to be adapted for the config files and JSON
   */
  void log_params(Params paramPairs);

protected:
  //! Log a single parameter name and value
  void log_param(std::string name, double val);
  //! Log data for this specific aggregator
  void log_aggregator(std::string agg_name, aggregatorFunc aggFunc);
  //! Create or open an HDF5 file
  H5FilePtr create_or_open_file(const std::string &fname);
  //! Create or open a group in an HDF5 file
  H5GroupPtr create_or_open_group(H5FilePtr file, std::string &groupName);
};

/*! \example example_logger.cpp
 * Example minimal usage of a Logger
 */
} // namespace KiloSim

#endif