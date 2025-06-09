#!/usr/bin/env sh

if [ ! -d build ]; then
  mkdir build
fi

cd build || exit 1

cmake .. \
  && cmake --build . \
  && echo "The build was completed successfully."

if [ -x ./bin/vk_first ]; then
  ./bin/vk_first
else
  echo "Failure: ./bin/vk_first was not found"
  exit 1
fi