#!/bin/sh


pio run
pio run --target upload
pio device monitor

