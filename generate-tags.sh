#!/bin/bash

set -x

basedir=$(readlink -f $(dirname $0))
files=($(find ${basedir} -name '*.c' -or -name '*.h'))
etags "${files[@]}"
