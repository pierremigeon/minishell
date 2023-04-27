#!/bin/bash

base_dir="../commit_tracker/$(pwd | rev | cut -f 1 -d / | rev)_project"

#Record number of branches and the number of merged branches
NUM_BRANCH=$(git branch | wc -l | sed 's/ //g')
NUM_MERGED=$(git branch --merged master | wc -l | sed 's/ //g')
PERCENT_MERGED=$(printf '%0.f%%\n' $(echo "$NUM_MERGED * 100 / $NUM_BRANCH" | bc -l))
echo $NUM_BRANCH\|$PERCENT_MERGED \($NUM_MERGED/$NUM_BRANCH\) > ./${base_dir}/branch_number
