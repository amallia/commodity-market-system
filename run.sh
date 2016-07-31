#!/bin/bash

if [ "$MODE" == "base" ]; then
    /cms/build/cms base
elif [ "$MODE" == "test" ]; then
    make test -C /cms/build/
else
    /cms/build/cms $MODE $PORT
fi
