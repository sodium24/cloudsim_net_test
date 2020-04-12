FROM osrf/subt-virtual-testbed:subt_solution_latest

ADD --chown=developer:developer ./getalltopics_ros /home/developer/getalltopics_ros

RUN /bin/bash -c 'source /opt/ros/melodic/setup.bash && cd /home/developer/getalltopics_ros && catkin_make install'
RUN /bin/bash -c 'cp /home/developer/getalltopics_ros/src/getalltopics_ros/src/entrypoint.sh .'

ENTRYPOINT ./entrypoint.sh


