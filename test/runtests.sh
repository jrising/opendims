#!/bin/bash

# Make the tool
cd ../tool
make all

if [ "`./convert "[unixtime]"`" != "1 Unix time [s [time]]" ]; then
   echo "Test [unixtime] failed."
   exit 1
fi
   
if [ "`./convert 3.7 [lon]`" != "3.7 longitude [deg [angle]]" ]; then
   echo "Test 3.7 [lon] failed."
   exit 1
fi
   
