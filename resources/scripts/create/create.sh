#!/bin/zsh

RED='\033[1;91m'
NO_COLOR='\033[0m'

CREATE_DS='f'
CREATE_H='f'
DEPS_PATH='./resources/scripts/create'

if [ "$1" = "--datastructure" ] || [ "$1" = "-ds" ]; then
  CREATE_DS='t'
elif [ "$1" = "--helper" ] || [ "$1" = "-h" ]; then
  CREATE_H='t'
fi

clear

if [[ "$CREATE_DS" == 't' ]]; then
  exec "${DEPS_PATH}"/create_ds.sh
elif [[ "$CREATE_H" == 't' ]]; then
  exec "${DEPS_PATH}"/create_helper.sh
else
  echo "${RED}Option Required: -ds or -h.${NO_COLOR}"
  exit 1
fi
