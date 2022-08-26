#!/bin/bash
#Number and format each test sequentially
perl -i -pe 's{^.*(\[[*x].*$)}{$n=$n+1; "test #$n \t $1"}e' ./tests_to_run.txt
