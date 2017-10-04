#!/bin/bash

INDENT_ARGS="--linux-style --no-tabs"

if (( $# > 0 )); then
    indent ${INDENT_ARGS} "$@"
else
    indent ${INDENT_ARGS} *.{h,c}
fi
