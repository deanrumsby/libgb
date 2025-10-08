#!/usr/bin/env sh

mkdir -p ./build
cp web/* ./build

emcc src/*.c --no-entry -sENVIRONMENT=web -Isrc/include -o ./build/gb.wasm