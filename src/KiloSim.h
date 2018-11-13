/*
    Kilobot simulator where the simulator is no longer the master

    Created 2018-10 by Julia Ebert
    Based on Kilobot simulator by Michael Rubenstein
*/

#ifndef __KILOSIM_H
#define __KILOSIM_H

#include <set>
#include <string>
#include <iterator>
#include <memory>
#include <SFML/Graphics.hpp>
#include "robot.h"

namespace KiloSim
{
class World
{
  struct RobotPose
  {
    // x, y, and theta (rotation) of a robot
    double x;
    double y;
    double theta;
    RobotPose(double x, double y, double theta);
    RobotPose();
  };

protected:
  // Set of (unique) Robots in the world
  std::vector<Robot *> m_robots;
  // How many ticks per second in simulation
  // TODO: Set default
  uint16_t m_tick_rate = 32;
  // Current tick of the system (starts at 0)
  uint32_t m_tick = 0;
  // Duration (seconds) of a tick
  double m_tick_delta_t = 1.0 / m_tick_rate;
  // Number of ticks between messages (eg, 3 means 10 messages per second)
  uint m_comm_rate = 3;
  // Height of the arena in mm
  const double m_arena_width;
  // Width of the arena in mm
  const double m_arena_height;
  // probability of a controller executing its time step
  const double m_prob_control_execute = .99;

  // Background light pattern image (as a 2D vector)
  sf::Image m_light_pattern;

public:
  typedef std::vector<Robot *>::iterator RobotsIterator;
  typedef std::shared_ptr<std::vector<RobotPose>> PosesPtr;

protected:
  // Run the controllers (kilolib) for all robots
  void run_controllers();
  // Send messages between robots
  void communicate();
  // Compute the next positions of the robots from positions and motor commands
  PosesPtr compute_next_step();
  // Check to see if motion causes robots to collide
  std::shared_ptr<std::vector<int16_t>> find_collisions(PosesPtr newPos);
  // Move the robots based on new positions and collisions
  void move_robots(PosesPtr newPos, std::shared_ptr<std::vector<int16_t>> collisions);
  // Wrap an angle to in [0, 2*pi)
  double wrap_angle(double angle);

public:
  // Construct a world of a fixed size with the background light pattern
  World(double arena_width, double arena_height, std::string light_img_src);
  // Construct a world with no background/light pattern
  World(double arena_width, double arena_height);
  // Destructor, destroy all objects
  virtual ~World();

  // Run a step of the simulator
  void step();
  // Return whether there is a light pattern
  bool has_light_pattern();
  // Return a reference to the current light in the world
  sf::Image &get_light_pattern();
  // Set the light pattern for the world ground surface
  void set_light_pattern(std::string light_img_src);
  // Get the 10-bit color at the given coordinates in World space
  // (NOT in image coordinates. (0,0) is bottom left)
  uint16_t get_light(float x, float y);
  // Add a robot to the world. If the robot is already in the world, do nothing
  void add_robot(Robot *robot);
  // Remove a robot from the world and destroy it. If not in the world, do nothing
  void remove_robot(Robot *robot);
  // Get/set the tick rate
  void set_tick_rate(uint16_t newTickRate);
  uint16_t get_tick_rate();
  // Get the current tick of the simulation (only set by simulator)
  uint32_t get_tick();
  // Get the current computed time in seconds (from tick and tickRate)
  double get_time();
  // Return a pointer to the robots in the world
  std::vector<Robot *> &get_robots();
  // Get the dimensions of the world (in mm)
  std::vector<double> get_dimensions();
};
} // namespace KiloSim

#endif