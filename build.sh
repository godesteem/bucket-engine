#!/bin/bash
# File              : build.sh
# Author            : Philipp Zettl <philipp.zettl@godesteem.de>
# Date              : 28.09.2019
# Last Modified Date: 28.09.2019
# Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
# build.sh
# Copyright (c) 2019 Philipp Zettl <philipp.zettl@godesteem.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
set -e

echo "Cleaning up..."
rm -rf build/
mkdir -p build/

cd build

cmake -Wdev -Wall -Wextra --debug-output ..
make

if [ ! $CI ]; then
  echo "build done, execute test?"
  read input

  if [[ $input == "y" || $input == "Y" ]]; then
    ./bucket-engine-test
  else
    ./bucket-engine
  fi
else
  ./bucket-engine
fi

cd ..

