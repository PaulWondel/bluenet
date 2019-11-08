#!/bin/bash

read -p 'Name testfile: ' hexfile

nrfjprog  -f nrf52  --eraseall
nrfjprog  -f nrf52  --program  softdevice_mainpart.hex  --sectorerase
nrfjprog  -f nrf52  --program  $hexfile  --sectorerase
nrfjprog  -f nrf52  --program  bootloader-settings.hex  --sectorerase
nrfjprog  --reset
