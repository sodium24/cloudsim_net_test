# CloudSim Network Performance Testing

This work is intended to help diagnose CloudSim performance irregularities
which occurred during the DARPA SubT Challenge Urban Circuit event.

A likely cause of these irregularities was a network-related issue, so
several test cases were created to emulate network delays, bandwidth limits,
and packet loss. 

As well, test cases were created to emulate a theoretical event in which 
a large number of UDP multicast Ignition Transport messages are received by
each infrastructure container, saturating their ability to send/receive
messages, and thereby causing a failure.

Results of this testing have been shared with the DARPA SubT Challenge team
in the hopes that it will help to resolve these irregularities in the future.

For more information about the DARPA SubT Challenge, please see
https://www.subtchallenge.com/.

## Internal Docker Containers

- `netsim`: Build with `build_netsim.sh`. Contains packages for performing
  simulation of network links between other docker containers. Build this
  before running the network tests.

- `advertisetopics`: Build with `build_advertisetopics.sh`. Allows many 
  concurrent Ignition Transport topics to be advertised, in order to cause
  saturation of any listening nodes. Build this before running the 
  Ignition Transport related tests.

  Usage: `docker run -it advertisetopics advertisetopics <num_nodes> <topics_per_node>`

- `getalltopics`: Build with `build_getalltopics.sh`. Simple test code
  to print all advertised Ignition Transport topics regardless of their
  partition.

  Usage: `docker run -it getalltopics getalltopics list`

- `getalltopics_ros`: Build with `build_getalltopics_ros.sh`. Similar
  to `getalltopics` except using ROS logging infrastructure.

  Usage: `docker run -it getalltopics_ros`

## External Docker Containers

- `osrf/subt-virtual-testbed:cloudsim_sim_latest`: This is the Gazebo 
  simulation container from Open Robotics for running the simulation. 
  It communicates using Ignition Transport with the bridge containers.

- `osrf/subt-virtual-testbed:cloudsim_bridge_latest`: This is the bridge
  container from Open Robotics. It communicates using Ignition Transport
  with the simulation container, and using ROS messages with a competitor
  solution container.

- `osrf/subt-virtual-testbed:subt_solution_latest`: This is a sample
  solution container from Open Robotics, capable of moving a robot to the
  world entrance.

## Test Structure

The `test_cases` directory contains several test cases, each of which
has a `docker-compose.yml` file defining the test setup. A common
`test_config.env` file in the root directory defines common test parameters.

## Running Test Cases

First, setup `test_config.env` with the common test setup. For testing
the newest version of the CloudSim containers, you can define:

```
simImage=osrf/subt-virtual-testbed:cloudsim_sim_latest
bridgeImage=osrf/subt-virtual-testbed:cloudsim_bridge_latest
```

For debugging issues that occurred in February, these were instead set to:

```
simImage=osrf/subt-virtual-testbed@sha256:ad67999e2e9e1f3d72c9af04340ad3395eb025440d6304ad659c0b99bba83019
bridgeImage=osrf/subt-virtual-testbed@sha256:af4659f789ebdcf497a0ad80e9de613b9cf65ae046ec3a902f281fd835b8a317
```

`solutionImage` can be set to any valid solution container, including 
`osrf/subt-virtual-testbed:subt_solution_latest`.

After defining the common configuration, run `run_test.sh <test_case>` to run 
one of the defined test cases, or just `run_test.sh` to see a list of test 
cases and descriptions.

To stop a test case from running, use `Ctrl+C` or `stop_test.sh`.

Note: be careful to monitor system memory while the tests are running, because
certain test cases can cause a memory leak which may freeze up the host
machine.

## Test Case Descriptions

### bw_100m
Test with 100 Mbps bandwidth.

### bw_100m_5ms_0.1pct
Test with 100 Mbps bandwidth and 5ms delay, variance 1ms, packet loss 0.1%.

### bw_1g
Test with 1 Gbps bandwidth.

### bw_1g_5ms_0.1pct
Test with 1 Gbps bandwidth and 5ms delay, variance 1ms, packet loss 0.1%.

### delay_100ms
Test with 100 ms delay, 10 ms variance.

### delay_10ms
Test with 10 ms delay, 1 ms variance.

### delay_10ms_0.1pct
Test with 10 ms delay, 1 ms variance, 0.1% packet loss.

### delay_10ms_1pct
Test with 10 ms delay, 1 ms variance, 1% packet loss.

### delay_10ms_5pct
Test with 10 ms delay, 1 ms variance, 5% packet loss.

### delay_10ms_reorder_0.1pct
Test with 10 ms delay, 1 ms variance, 0.1% reordering.

### delay_10ms_reorder_1pct
Test with 10 ms delay, 1 ms variance, 1% reordering.

### delay_10ms_var_5ms
Test with 10 ms delay, 5 ms variance.

### delay_10ms_var_5ms_0.1pct
Test with 10 ms delay, 5 ms variance, 0.1% packet loss.

### delay_10ms_var_5ms_1pct
Test with 10 ms delay, 5 ms variance, 1% packet loss.

### delay_10ms_var_5ms_5pct
Test with 10 ms delay, 5 ms variance, 5% packet loss.

### delay_10ms_var_5ms_reorder_0.1pct
Test with 10 ms delay, 5 ms variance, 0.1% reordering.

### delay_10ms_var_5ms_reorder_1pct
Test with 10 ms delay, 5 ms variance, 1% reordering.

### ign_saturation_1
Test with ignition transport message saturation. Two containers have 100 nodes
advertising 100 topics per node, and one container has 50 nodes advertising
with 100 topics per node.

### ign_saturation_2
Test with ignition transport message saturation. Two containers have 100 nodes
advertising 100 topics per node, and one container has 90 nodes advertising
with 100 topics per node.

### ign_saturation_3
Test with ignition transport message saturation. Three containers have 150 nodes
advertising 100 topics per node.

### simple_routing
Simple routing test with the `netsim` docker container.

