#!/bin/bash

# Make the tool
cd ../tool
make all

if [ "`./parse 3 m s^2 / s`" != "3 m s [distance time]" ]; then
   echo "Test [3 m s^2 / s] failed."
   exit 1
fi

if [ "`./parse "3 * m s ^2 / s"`" != "3 m s [distance time]" ]; then
   echo "Test [3 * m s ^2 / s] failed."
   exit 1
fi

if [ "`./convert 36 s hr`" != "0.01 hr [time]" ]; then
   echo "Test [36 s -> hr] failed."
   exit 1
fi

if [ "`./convert 36 mt kg`" != "36000 kg [mass]" ]; then
   echo "Test [36 mt -> kg] failed."
   exit 1
fi

if [ "`./convert 36 mt / s "kg hr^-1"`" != "10 hr^-1 kg [mass time^-1]" ]; then
   echo "Test [36 mt / s -> kg hr^-1] failed."
   exit 1
fi

if [ "`./convert 1 degF degC`" != "0.555556 degC [temperature]" ]; then
   echo "Test [1 degF -> degC] failed."
   exit 1
fi

if [ "`./convert 32 F C`" != "0 C [degC [temperature]]" ]; then
   echo "Test [32 F C] failed."
   exit 1
fi

if [ "`./convert 273.15 K F`" != "32 F [degF [temperature]]" ]; then
   echo "Test [273.15 K F] failed."
   exit 1
fi

if [ "`./convert 32 B.C.E. C.E.`" != "-31 C.E. [yr [time]]" ]; then
   echo "Test [32 B.C.E. C.E.] failed."
   exit 1
fi
