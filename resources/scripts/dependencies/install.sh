#!/bin/zsh

RED='\033[1;91m'
NO_COLOR='\033[0m'

INSTALL_DS='f'
INSTALL_H='f'
DEPS_PATH='../../resources/scripts/dependencies'
ORIGIN='ds'

function is_helper() {
  line=$(head -n 1 Makefile)
  IS='f'
  if [ "${line}" = '#helper' ]; then
    IS='t'
  fi
  echo "${IS}"
}

IS_HELPER=$(is_helper)

if [ "${IS_HELPER}" = 't' ]; then
  DEPS_PATH='../../scripts/dependencies'
  ORIGIN='h'
fi

if [ "$1" = "--datastructure" ] || [ "$1" = "-ds" ]; then
  if [[ "${IS_HELPER}" == 't' ]]; then
    echo "${RED}Error: Can't add data structures as dependency to Helpers.${NO_COLOR}"
    exit 1
  fi
  INSTALL_DS='t'
elif [ "$1" = "--helper" ] || [ "$1" = "-h" ]; then
  INSTALL_H='t'
fi

if [ "$INSTALL_DS" = 't' ]; then
  exec "${DEPS_PATH}"/install_ds.sh
elif [ "$INSTALL_H" = 't' ]; then
  exec "${DEPS_PATH}"/install_helper.sh -"${ORIGIN}"
else
  exec "${DEPS_PATH}"/get_deps.sh
fi
