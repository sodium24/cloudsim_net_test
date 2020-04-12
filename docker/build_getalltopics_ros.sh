#!/bin/bash

user_id=$(id -u)

docker build --rm -t "getalltopics_ros:latest" --build-arg user_id=$user_id -f getalltopics_ros/Dockerfile .

