#!/bin/bash

/usr/local/redis/redis-5.0.7/src/redis-server &
/bin/sleep 3
/usr/local/redis/redis-5.0.7/src/redis-cli CONFIG SET protected-mode no
/bin/bash
