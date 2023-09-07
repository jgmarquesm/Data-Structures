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

function _get_this_Helper() {
  HELPER="$(echo set -- "$(pwd)" | grep -P 'helpers\/(?:.+)$' -o | cut -c9-)"
  echo "$HELPER"
}

function TitleCaseTo_snake_case() {
  # shellcheck disable=SC2001
  sed 's/[A-Z]/_\l&/g' <<<"$1" | cut -c2-
}

function _is_this_Helper() {
  if [[ "$(_get_this_Helper)" == "$1" ]]
  then
    echo 'is'
  fi
}

function _is_already_there() {
  PATTERN="^HELPER_FOLDER_(?:[\d]+|DEP_[\d]+) = ../${1}/\\$\(MAIN\)$"
  IS_ADDED="$(grep -P "$PATTERN" Makefile)"
  if [[ $IS_ADDED ]]
  then
    echo 'is'
  fi
}

function _get_Helpers_count() {
  count="$(grep -c -P "^HELPER_[\d]+" Makefile)"
  echo "$count"
}

function _addNewHelper () {
  echo "${BLUE}Adding ${1}...${NO_COLOR}"
  index=$(_get_Helpers_count)
  sed -i~ "s#^\#--ADD_FOLDER_NEW_HELPER#HELPER_FOLDER_$index = ../${1}/\$(MAIN)\n\#--ADD_FOLDER_NEW_HELPER#" Makefile
  sed -i~ "s#^\#--ADD_NEW_HELPER#HELPER_$index = $(TitleCaseTo_snake_case "${1}")\n\#--ADD_NEW_HELPER#" Makefile
  sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(HELPER_FOLDER_$index)/\$(SRC)/\$(HELPER_$index).c \$(MAIN)/\$(SRC)/\n\tcp \$(HELPER_FOLDER_$index)/\$(INCLUDE)/\$(HELPER_$index).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
  sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(HELPER_$index).o \\\\\n\#--ADD_TO_PACK#" Makefile
  sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(HELPER_$index).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
  sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(HELPER_$index).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(HELPER_$index).h\n\#--ADD_TO_CLEAN#" Makefile
  sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${1}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_Helper)")".c
  echo "${1}" >> .info
  echo "${GREEN}${1} successfully added.${NO_COLOR}"
}

function _addNewHelperDeps () {
  # shellcheck disable=SC2207
  local newHelperDeps=( $(echo "${2}" | tr '\n' "\n") )
  local i=1
  for dependency in "${newHelperDeps[@]}"
  do
    if [[ "$(_is_this_Helper "${dependency}")" == 'is' || "$(_is_already_there "${dependency}")" == 'is' ]]
    then
      echo "${YELLOW}SKIPPING: ${dependency}...${NO_COLOR}"
      continue
    fi

    echo "${BLUE}Adding ${dependency}...${NO_COLOR}"
    local infoContent=( "${(f)$(< ../"${dependency}"/.info)}" )
    # shellcheck disable=SC2128
    if [[ -n "${infoContent}" ]]
    then
      _addNewHelperDeps "${dependency}" "${infoContent}"
    fi

    sed -i~ "s#^\#--ADD_FOLDER_NEW_HELPER#HELPER_FOLDER_DEP_${i} = ../${dependency}/\$(MAIN)\n\#--ADD_FOLDER_DEP_NEW_HELPER#" Makefile
    sed -i~ "s#^\#--ADD_NEW_HELPER#HELPER_DEP_${i} = $(TitleCaseTo_snake_case "${dependency}")\n\#--ADD_NEW_HELPER#" Makefile
    sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(HELPER_FOLDER_DEP_${i})/\$(SRC)/\$(HELPER_DEP_${i}).c \$(MAIN)/\$(SRC)/\n\tcp \$(HELPER_FOLDER_DEP_${i})/\$(INCLUDE)/\$(HELPER_DEP_${i}).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
    sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(HELPER_DEP_${i}).o \\\\\n\#--ADD_TO_PACK#" Makefile
    sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(HELPER_DEP_${i}).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
    sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(HELPER_DEP_${i}).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(HELPER_DEP_${i}).h\n\#--ADD_TO_CLEAN#" Makefile
    sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${dependency}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_Helper)")".c
    echo "${dependency}" >> .info
    echo "${GREEN}${dependency} successfully added.${NO_COLOR}"
    (( i++ ))
  done
}

function CheckIfCanAdd() {
  if [[ "$(_is_this_Helper "${1}")" == 'is' ]]
  then
    # shellcheck disable=SC2028
    echo "${RED}Self dependency not allowed.\nFinishing...${NO_COLOR}"
    exit 0
  else
    if [[ "$(_is_already_there "${1}")" == 'is' ]]
    then
      # shellcheck disable=SC2028
      echo "${YELLOW}${1} is already added.\nFinishing...${NO_COLOR}"
      exit 0
    fi
  fi
}

function UpdateExtLibsLabel() {
  sed -i~ "s#--private-get_unity#--private-get_external_lib#" Makefile
  sed -i~ "s#clean_unity#clean_external#" Makefile
}

function AddNewDependencies() {
  local infoContent=( "${(f)$(< ../"${1}"/.info)}" )
  _addNewHelper "${1}"
  # shellcheck disable=SC2128
  if [[ -n "${infoContent}" ]]; then
    _addNewHelperDeps "${1}" "${infoContent}"
  fi
  sed -i~ "/^ *$/d" .info
}

function EvalIndex() {
  sed -i~ "s#^\#H[0-9]\+#\#H$(( $(_get_Helpers_count) ))#" Makefile
}

clear

echo "${CYAN}Select a new dependency to add:${WHITE}
${PURPLE}1 )${WHITE} Exception Handler
${PURPLE}2 )${WHITE} Node
${PURPLE}3 )${WHITE} Vertex
${NO_COLOR}" #--H

read -r SELECTION

case ${SELECTION} in
    1 ) HELPER_FOLDER="ExceptionHandler";;
    2 ) HELPER_FOLDER="Node";;
    3 ) HELPER_FOLDER="Vertex";;
#--ADD_NEW_HELPER_OPT
    * )
      echo "${YELLOW}Invalid selection: ${RED}${SELECTION}.${NO_COLOR}"
      exit 1
    ;;
esac

CheckIfCanAdd "$HELPER_FOLDER"
UpdateExtLibsLabel
AddNewDependencies "$HELPER_FOLDER"
EvalIndex

echo "${GREEN}Finishing...${NO_COLOR}"