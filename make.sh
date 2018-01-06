#!/bin/bash
make -C writer 2>&1 | sed 's/connor/xyzzy/'
