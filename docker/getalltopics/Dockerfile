FROM ubuntu:18.04

RUN /bin/sh -c 'apt-get update' \
 && /bin/sh -c 'apt-get install -y build-essential lsb-release wget' \
 && /bin/sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list' \
 && /bin/sh -c 'wget http://packages.osrfoundation.org/gazebo.key -O - | apt-key add -' \
 && /bin/sh -c 'apt-get update && apt-get install -y libignition-transport7-dev libignition-msgs4-dev libignition-common3-dev'

ADD ./getalltopics/getalltopics /root/getalltopics

RUN /bin/sh -c 'cd /root/getalltopics && mkdir build && cd build && cmake ../ && make && make install && ldconfig'


