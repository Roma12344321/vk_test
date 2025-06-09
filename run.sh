#!/usr/bin/env sh

if [ ! -d build ]; then
  mkdir build
fi

cd build || exit 1

cmake .. \
  && cmake --build . \
  && echo "Сборка выполнена успешно."

if [ -x ./bin/vk_first ]; then
  ./bin/vk_first
else
  echo "Ошибка: ./bin/vk_first не найден или не исполнителен."
  exit 1
fi