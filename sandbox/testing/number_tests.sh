#!/bin/bash
perl -i -pe 's{^(\[.*$)}{$n=$n+1; "test #$n $1"}e' ./sandbox/testing/tests_to_run_test.txt
