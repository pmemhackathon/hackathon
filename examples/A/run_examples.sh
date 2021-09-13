#!/bin/bash -e
#
# shell commands to run this example
#

echo "Run numa example"
./numa
echo "-------------------------------------"

echo "Run numa example with --membind=2"
numactl --membind=2 ./numa
echo "-------------------------------------"
