#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <test_case>"
    echo ""
    echo "Set common test configuration in test_config.env"
    echo ""
    echo "================================================================================"
    echo "Test cases:"
    echo "--------------------------------------------------------------------------------"
    for name in ./test_cases/*; do
        test_path=$(basename $name)
        echo "- $test_path:"
        cat ./test_cases/$test_path/README.txt
        echo ""
    done
    echo "================================================================================"
    exit 1
fi

test_case=$1
mkdir ./runtest || true
cp ./test_config.env ./runtest/.env
cp ./test_cases/$test_case/docker-compose.yml ./runtest/
cp ./scripts/run_docker_compose.sh ./runtest/

cd ./runtest/
./run_docker_compose.sh
