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

function _get_this_DS() {
  DS="$(echo set -- "$(pwd)" | grep -P 'main\/(?:.+)$' -o | cut -c6-)"
  echo "$DS"
}

function TitleCaseTo_snake_case() {
 # shellcheck disable=SC2001
 sed 's/[A-Z]/_\l&/g' <<<"$1" | cut -c2-
}

function _is_this_DS() {
  if [[ "$(_get_this_DS)" == "$1" ]]
  then
    echo 'is'
  fi
}

function _is_already_there() {
  PATTERN="^(HELPER_FOLDER|DS_FOLDER)_(?:[\d+]|DEP_[\d]+) = ../(../resources/helpers/|)${1}/\\$\(MAIN\)$"
  IS_ADDED="$(grep -P "$PATTERN" Makefile)"
  if [[ $IS_ADDED ]]
  then
    echo 'is'
  fi
}

function _get_DSs_count() {
  adt_count="$(grep -c -P "^DS_[\d]+" Makefile)"
  echo "$adt_count"
}

function _get_Helpers_count() {
  count="$(grep -c -P "^HELPER_[\d]+" Makefile)"
  echo "$count"
}

function _addNewBaseDS () {
  echo "${BLUE}Adding ${1}...${NO_COLOR}"
  index=$(_get_DSs_count)
  sed -i~ "s#^\#--ADD_FOLDER_NEW_DS#DS_FOLDER_$index = ../${1}/\$(MAIN)\n\#--ADD_FOLDER_NEW_DS#" Makefile
  sed -i~ "s#^\#--ADD_NEW_DS#DS_$index = $(TitleCaseTo_snake_case "${1}")\n\#--ADD_NEW_DS#" Makefile
  sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(DS_FOLDER_$index)/\$(SRC)/\$(DS_$index).c \$(MAIN)/\$(SRC)/\n\tcp \$(DS_FOLDER_$index)/\$(INCLUDE)/\$(DS_$index).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
  sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(DS_$index).o \\\\\n\#--ADD_TO_PACK#" Makefile
  sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(DS_$index).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
  sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(DS_$index).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(DS_$index).h\n\#--ADD_TO_CLEAN#" Makefile
  sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${1}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_DS)")".c
  echo "ds_${1}" >> .info
  echo "${GREEN}${1} successfully added.${NO_COLOR}"
}

function _addNewHelper () {
  echo "${BLUE}Adding ${1}...${NO_COLOR}"
  index=$(_get_Helpers_count)
  sed -i~ "s#^\#--ADD_FOLDER_NEW_HELPER#HELPER_FOLDER_$index = ../../resources/helpers/${1}/\$(MAIN)\n\#--ADD_FOLDER_NEW_HELPER#" Makefile
  sed -i~ "s#^\#--ADD_NEW_HELPER#HELPER_$index = $(TitleCaseTo_snake_case "${1}")\n\#--ADD_NEW_HELPER#" Makefile
  sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(HELPER_FOLDER_$index)/\$(SRC)/\$(HELPER_$index).c \$(MAIN)/\$(SRC)/\n\tcp \$(HELPER_FOLDER_$index)/\$(INCLUDE)/\$(HELPER_$index).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
  sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(HELPER_$index).o \\\\\n\#--ADD_TO_PACK#" Makefile
  sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(HELPER_$index).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
  sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(HELPER_$index).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(HELPER_$index).h\n\#--ADD_TO_CLEAN#" Makefile
  sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${1}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_DS)")".c
  echo "hp_${1}" >> .info
  echo "${GREEN}${1} successfully added.${NO_COLOR}"
}

function _addNewBaseDSDeps () {
  # shellcheck disable=SC2207
  local newBaseDSDeps=( $(echo "${1}" | tr '\n' "\n") )
  local i=1
  for dependency in "${newBaseDSDeps[@]}"
  do
    if [[ "$(_is_this_DS "${dependency}")" == 'is' || "$(_is_already_there "${dependency}")" == 'is' ]]
    then
      echo "${YELLOW}SKIPPING: ${dependency}...${NO_COLOR}"
      continue
    fi

    if [[ ${dependency:0:2} == "ds" ]]
    then
      echo "${BLUE}Adding $(echo "$dependency" | cut -c4-)...${NO_COLOR}"
      local infoContent=( "${(f)$(< ../"$(echo "$dependency" | cut -c4-)"/.info)}" )
      # shellcheck disable=SC2128
      if [[ -n "${infoContent}" ]]
      then
        _addNewBaseDSDeps "$(echo "$dependency" | cut -c4-)" "${infoContent}"
      fi

      sed -i~ "s#^\#--ADD_FOLDER_NEW_DS#DS_FOLDER_DEP_${i} = ../${dependency}/\$(MAIN)\n\#--ADD_FOLDER_NEW_DS#" Makefile
      sed -i~ "s#^\#--ADD_NEW_DS#DS_DEP_${i} = $(TitleCaseTo_snake_case "${dependency}")\n\#--ADD_NEW_DS#" Makefile
      sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(DS_FOLDER_DEP_${i})/\$(SRC)/\$(DS_DEP_${i}).c \$(MAIN)/\$(SRC)/\n\tcp \$(DS_FOLDER_DEP_${i})/\$(INCLUDE)/\$(DS_DEP_${i}).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
      sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(DS_DEP_${i}).o \\\\\n\#--ADD_TO_PACK#" Makefile
      sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(DS_DEP_${i}).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
      sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(DS_DEP_${i}).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(DS_DEP_${i}).h\n\#--ADD_TO_CLEAN#" Makefile
      sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${dependency}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_DS)")".c
      echo "${dependency}" >> .info
      echo "${GREEN}${dependency} successfully added.${NO_COLOR}"
      (( i++ ))
    elif [[ ${dependency:0:2} == "hp" ]]
    then
      local infoContent=( "${(f)$(< ../../resources/helpers/"$(echo "$dependency" | cut -c4-)"/.info)}" )
      # shellcheck disable=SC2128
      if [[ -n "${infoContent}" ]]
      then
        _addNewHelperDeps "${infoContent}"
      fi

      _addNewHelper "$(echo "$dependency" | cut -c4-)"
    else
      echo "${BLUE}${dependency} ${YELLOW}does not match any pattern of dependency.${NO_COLOR}"
    fi
  done
}

function _addNewHelperDeps () {
  # shellcheck disable=SC2207
  local newHelperDeps=( $(echo "${1}" | tr '\n' "\n") )
  local i=1
  for dependency in "${newHelperDeps[@]}"
  do
    if [[ "$(_is_this_DS "${dependency}")" == 'is' || "$(_is_already_there "${dependency}")" == 'is' ]]
    then
      echo "${YELLOW}SKIPPING: ${dependency}...${NO_COLOR}"
      continue
    fi

    echo "${BLUE}Adding ${dependency}...${NO_COLOR}"
    local infoContent=( "${(f)$(< ../../resources/helpers/"${dependency}"/.info)}" )
    # shellcheck disable=SC2128
    if [[ -n "${infoContent}" ]]
    then
      _addNewHelperDeps "${infoContent}"
    fi

    sed -i~ "s#^\#--ADD_FOLDER_NEW_HELPER#HELPER_FOLDER_DEP_${i} = ../../resources/helpers/${dependency}/\$(MAIN)\n\#--ADD_FOLDER_DEP_NEW_HELPER#" Makefile
    sed -i~ "s#^\#--ADD_NEW_HELPER#HELPER_DEP_${i} = $(TitleCaseTo_snake_case "${dependency}")\n\#--ADD_NEW_HELPER#" Makefile
    sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(HELPER_FOLDER_DEP_${i})/\$(SRC)/\$(HELPER_DEP_${i}).c \$(MAIN)/\$(SRC)/\n\tcp \$(HELPER_FOLDER_DEP_${i})/\$(INCLUDE)/\$(HELPER_DEP_${i}).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
    sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(HELPER_DEP_${i}).o \\\\\n\#--ADD_TO_PACK#" Makefile
    sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(HELPER_DEP_${i}).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
    sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(HELPER_DEP_${i}).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(HELPER_DEP_${i}).h\n\#--ADD_TO_CLEAN#" Makefile
    sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(TitleCaseTo_snake_case "${dependency}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(TitleCaseTo_snake_case "$(_get_this_DS)")".c
    echo "hp_${dependency}" >> .info
    echo "${GREEN}${dependency} successfully added.${NO_COLOR}"
    (( i++ ))
  done
}

function CheckIfCanAdd() {
  if [[ "$(_is_this_DS "${1}")" == 'is' ]]
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
  if [[ "${2}" == "DS" ]]; then
    local infoContent=( "${(f)$(< ../"${1}"/.info)}" )
    _addNewBaseDS "${1}"
  elif [[ "${2}" == "H" ]]; then
    local infoContent=( "${(f)$(< ../../resources/helpers/"${1}"/.info)}" )
    _addNewHelper "${1}"
  fi
  # shellcheck disable=SC2128
  if [[ -n "${infoContent}" ]]; then
    if [[ "${2}" == "DS" ]]; then
      _addNewBaseDSDeps "${infoContent}"
    elif [[ "${2}" == "H" ]]; then
      _addNewHelperDeps "${infoContent}"
    fi
  fi
  sed -i~ "/^ *$/d" .info
}

function EvalIndex() {
  sed -i~ "s#^\#DS[0-9]\+#\#DS$(( $(_get_DSs_count) ))#" Makefile
  sed -i~ "s#^\#H[0-9]\+#\#H$(( $(_get_Helpers_count) ))#" Makefile
}

clear

echo "${CYAN}Do you wanna add a Data Structure or a Helper?${NO_COLOR}
${PURPLE}1 )${WHITE} Data Structure
${PURPLE}2 )${WHITE} Helper"
read -r DS_OR_HELPER

case ${DS_OR_HELPER} in
  1 )
    echo "${CYAN}Select new dependency to add:${WHITE}
${PURPLE}1 )${WHITE} Array
${PURPLE}2 )${WHITE} Singly Linked List
${PURPLE}3 )${WHITE} Doubly Linked List
${PURPLE}4 )${WHITE} Circular Linked List
${PURPLE}5 )${WHITE} Static Stack
${PURPLE}6 )${WHITE} Dynamic Stack
${PURPLE}7 )${WHITE} Static Queue
${PURPLE}8 )${WHITE} Dynamic Queue
${PURPLE}9 )${WHITE} Matrix
${PURPLE}10)${WHITE} Undirected Weighted Graph
${NO_COLOR}" #--DS

    read -r SELECTION

    case ${SELECTION} in
        1 ) NEW_DS_FOLDER="Array";;
        2 ) NEW_DS_FOLDER="SinglyLinkedList";;
        3 ) NEW_DS_FOLDER="DoublyLinkedList";;
        4 ) NEW_DS_FOLDER="CircularDoublyLinkedList";;
        5 ) NEW_DS_FOLDER="StaticStack";;
        6 ) NEW_DS_FOLDER="DynamicStack";;
        7 ) NEW_DS_FOLDER="StaticQueue";;
        8 ) NEW_DS_FOLDER="DynamicQueue";;
        9 ) NEW_DS_FOLDER="Matrix";;
        10 ) NEW_DS_FOLDER="UndirectedWeightedGraph";;
#--ADD_NEW_OPT
        * )
          echo "${YELLOW}Invalid selection: ${RED}${SELECTION}.${NO_COLOR}"
          exit 1
        ;;
    esac
    CheckIfCanAdd "$NEW_DS_FOLDER"
    UpdateExtLibsLabel
    AddNewDependencies "$NEW_DS_FOLDER" "DS"
    EvalIndex
    ;;
  2 )
    echo "${CYAN}Select new dependency to add:${WHITE}
${PURPLE}1 )${WHITE} Exception Handler
${PURPLE}2 )${WHITE} Node
${PURPLE}3 )${WHITE} Vertex
${NO_COLOR}" #--H

      read -r SELECTION

      case ${SELECTION} in
          1 ) NEW_HELPER_FOLDER="ExceptionHandler";;
          2 ) NEW_HELPER_FOLDER="Node";;
          3 ) NEW_HELPER_FOLDER="Vertex";;
#--ADD_NEW_HELPER_OPT
          * )
            echo "${YELLOW}Invalid selection: ${RED}${SELECTION}.${NO_COLOR}"
            exit 1
          ;;
      esac
      CheckIfCanAdd "$NEW_HELPER_FOLDER"
      UpdateExtLibsLabel
      AddNewDependencies "$NEW_HELPER_FOLDER" "H"
      EvalIndex
    ;;
  * )
    echo "${YELLOW}Invalid selection: ${RED}${DS_OR_HELPER}.${NO_COLOR}"
    exit 1
    ;;
esac

echo "${GREEN}Finishing...${NO_COLOR}"
