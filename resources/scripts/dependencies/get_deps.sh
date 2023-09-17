#!/bin/zsh

# shellcheck disable=SC2034
GREY='\033[1;90m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[1;93m'
BLUE='\033[1;94m'
PURPLE='\033[1;95m'
CYAN='\033[1;96m'
WHITE='\033[1;97m'
NO_COLOR='\033[0m'

HEADER_PATH='main/include/'
THIS_DIR='./'
DEPS_PATTERN='= ../(../resources/helpers/|)[^(../)].+/'
UNITY_PATTERN='^UNITY = .+$'

function formatted_dependency() {
  formatted=$(echo "${1}" | tr -d "./" | sed 's/\([A-Z]\)/ \1/g; s/resourceshelpers//')
  echo "$formatted"
}

function get_unity() {
  UNITY_PATH="$(grep -P "$UNITY_PATTERN" Makefile | cut -c9-)"
  echo "${BLUE}Getting header from ${PURPLE}Unity Test Framework${BLUE}...${NO_COLOR}"
  cp "${UNITY_PATH}/include/"*.h "${THIS_DIR}${HEADER_PATH}"
  echo "${GREEN}Successfully got.${NO_COLOR}"
}

function get_deps() {
  # shellcheck disable=SC2207
  local DEPENDENCIES=( $(grep -P -o "$DEPS_PATTERN" Makefile | tr -d "= ") )
  for dependency in "${DEPENDENCIES[@]}"
  do
    echo "${BLUE}Getting header from${PURPLE}$(formatted_dependency "${dependency}")${BLUE}...${NO_COLOR}"
    cp "${dependency}${HEADER_PATH}"*.h "${THIS_DIR}${HEADER_PATH}"
    echo "${GREEN}Successfully got.${NO_COLOR}"
  done
  get_unity
}

clear
get_deps
echo "${GREEN}Finishing...${NO_COLOR}"