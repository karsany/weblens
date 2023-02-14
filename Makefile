ifeq ($(OS),Windows_NT)
    SHELL=cmd
	SEP=&
else
	SEP=;
endif

ui/node_modules: ui/package.json
	cd ui $(SEP) npm i
	
ui/dist/index.html: ui/node_modules ui/src/*
	cd ui $(SEP) npm run build
	
ui-dev: ui/node_modules
	cd ui $(SEP) npm run dev
	
ui: ui/dist/index.html
	@echo "UI"

src/indexhtml.cpp: ui

src/version.cpp: 
	node scripts/update-version.js

version: src/version.cpp

.pio/build/esp32cam/firmware.bin: ui version src/indexhtml.cpp
	pio run

firmware: .pio/build/esp32cam/firmware.bin	ui
	
upload: firmware
	pio run --target upload

monitor: upload
	pio device monitor

all: firmware

.PHONY: upload monitor version ui