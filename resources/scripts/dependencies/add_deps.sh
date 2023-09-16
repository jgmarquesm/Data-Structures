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

PUBLIC='pub'
PROTECTED='ptd'
PRIVATE='pvt'
DS='ds'
H='hp'

function _get_this_DS() {
  this="$(echo set -- "$(pwd)" | grep -P 'main\/(?:.+)$' -o | cut -c6-)"
  echo "$this"
}

function _title_case_to_snake_case() {
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
  PATTERN="^(?:hp|ds)(?:|_DEP)_FOLDER_\d+ = ../(../resources/helpers/|)${1}/\\$\(MAIN\)$"
  IS_ADDED="$(grep -P "$PATTERN" Makefile)"
  if [[ $IS_ADDED ]]
  then
    echo 'is'
  fi
}

function _add_dep_with_type_and_access_modifier() {
  if [[ "${1}" == "$PUBLIC" ]]
  then
    sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"$(_title_case_to_snake_case "${3}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/include/"$(_title_case_to_snake_case "$(_get_this_DS)")".h
  else
    sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"../include/$(_title_case_to_snake_case "${3}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/src/"$(_title_case_to_snake_case "$(_get_this_DS)")".c
  fi
    echo "${1}_${2}_${3}" >> .info
}

function _add_dep_deps_with_type_and_access_modifier() {
  if [[ "${1}" == "$PUBLIC" ]]
  then
    sed -i~ "s#//\#--ADD_TO_INCLUDE#\#include \"$(_title_case_to_snake_case "${3}").h\"\n//\#--ADD_TO_INCLUDE#" ./main/include/"$(_title_case_to_snake_case "$(_get_this_DS)")".h
    echo "${1}_${2}_${3}" >> .info
  else
    echo "pvt_${2}_${3}" >> .info
  fi
}

function _get_dep_modifier() {
  echo "${${1}:0:3}"
}

function _get_dep_type() {
    # shellcheck disable=SC2005
    echo "$(echo "${1}" | cut -c5-6)"
}

function _get_dep() {
    # shellcheck disable=SC2005
    echo "$(echo "${1}" | cut -c8-)"
}

function _get_DSs_count() {
  adt_count="$(grep -c -P "^ds_[\d]+" Makefile)"
  echo "$adt_count"
}

function _get_Helpers_count() {
  count="$(grep -c -P "^hp_[\d]+" Makefile)"
  echo "$count"
}

function _set_new_deps() {
  TYPE=$( grep -P -o 'ds|hp' <<< "${1}")
  IS_DEP=$(grep -P 'DEP' <<< "${1}")
  FULL_PATH='..'
  INDEX=${3}
  if [[ $TYPE == "$H" ]]
  then
    FULL_PATH='../../resources/helpers'
  fi
  if [[ $IS_DEP ]]
  then
    if [[ $TYPE == "$H" ]]
    then
      DEP_INDEX=$(( $(_get_Helpers_count) - 1 ))
    else
      DEP_INDEX=$(( $(_get_DSs_count) - 1 ))
    fi
    INDEX="$DEP_INDEX\_${3}"
  fi

  sed -i~ "s#^\#--ADD_FOLDER_NEW_$TYPE#${1}_FOLDER_${3} = $FULL_PATH/${2}/\$(MAIN)\n\#--ADD_FOLDER_NEW_$TYPE#" Makefile
  sed -i~ "s#^\#--ADD_NEW_$TYPE#${1}_$INDEX = $(_title_case_to_snake_case "${2}")\n\#--ADD_NEW_$TYPE#" Makefile
  sed -i~ "s#^\#--ADD_GET_NEW_LIB#\tcp \$(${1}_FOLDER_$INDEX)/\$(SRC)/\$(${1}_$INDEX).c \$(MAIN)/\$(SRC)/\n\tcp \$(${1}_FOLDER_$INDEX)/\$(INCLUDE)/\$(${1}_$INDEX).h \$(MAIN)/\$(INCLUDE)/\n\#--ADD_GET_NEW_LIB#" Makefile
  sed -i~ "s#^\#--ADD_TO_PACK#\t\$(MAIN)/\$(OBJ)/\$(${1}_$INDEX).o \\\\\n\#--ADD_TO_PACK#" Makefile
  sed -i~ "s#^\#--ADD_TO_COMPILE_TEST#\t\$(MAIN)/\$(OBJ)/\$(${1}_$INDEX).o \\\\\n\#--ADD_TO_COMPILE_TEST#" Makefile
  sed -i~ "s#^\#--ADD_TO_CLEAN#\trm -rf \$(MAIN)/\$(SRC)/\$(${1}_$INDEX).c\n\trm -rf \$(MAIN)/\$(INCLUDE)/\$(${1}_$INDEX).h\n\#--ADD_TO_CLEAN#" Makefile
}

function _add_DS () {
  echo "${BLUE}Adding ${1}...${NO_COLOR}"
  index=$(_get_DSs_count)
  _set_new_deps "$DS" "${1}" "$index"
  _add_dep_with_type_and_access_modifier "${2}" "$DS" "${1}"
  echo "${GREEN}${1} successfully added.${NO_COLOR}"
}

function _add_Helper () {
  echo "${BLUE}Adding ${1}...${NO_COLOR}"
  index=$(_get_Helpers_count)
  _set_new_deps "$H" "${1}" "$index"
  _add_dep_with_type_and_access_modifier "${2}" "$H" "${1}"
  echo "${GREEN}${1} successfully added.${NO_COLOR}"
}

function _add_DS_deps () {
  # shellcheck disable=SC2207
  local newBaseDSDeps=( $(echo "${1}" | tr '\n' "\n") )
  local i=$(( $2 ))
  for dependency in "${newBaseDSDeps[@]}"
  do
    DEP_MODIFIER=$(_get_dep_modifier "$dependency")
    DEP_TYPE=$(_get_dep_type "$dependency")
    DEP=$(_get_dep "$dependency")

    if [[ "$(_is_this_DS "$DEP")" == 'is' || "$(_is_already_there "$DEP")" == 'is' ]]
    then
      echo "${YELLOW}SKIPPING: $DEP...${NO_COLOR}"
      continue
    fi

    echo "${BLUE}Adding $DEP...${NO_COLOR}"
    if [[ $DEP_TYPE == "$DS" ]]
    then
      _set_new_deps "$DS\_DEP" "$DEP" "${i}"
      _add_dep_deps_with_type_and_access_modifier "$DEP_MODIFIER" "$DS" "$DEP"
      echo "${GREEN}$DEP successfully added.${NO_COLOR}"
      (( i++ ))

      local infoContent=( "${(f)$(< ../"$DEP"/.info)}" )
      # shellcheck disable=SC2128
      if [[ -n "${infoContent}" ]]
      then
        _add_DS_deps "${infoContent}" "$i"
      fi
    elif [[ $DEP_TYPE == "$H" ]]
    then
      index=$(_get_Helpers_count)
      _set_new_deps "$H" "$DEP" "$index"
      _add_dep_deps_with_type_and_access_modifier "$DEP_MODIFIER" "$H" "$DEP"
      echo "${GREEN}$DEP successfully added.${NO_COLOR}"

      local infoContent=( "${(f)$(< ../../resources/helpers/"$DEP"/.info)}" )
      # shellcheck disable=SC2128
      if [[ -n "${infoContent}" ]]
      then
        _add_Helper_deps "${infoContent}" 1
      fi
    else
      echo "${BLUE}$DEP ${YELLOW}does not match any pattern of dependency.${NO_COLOR}"
    fi
  done
}

function _add_Helper_deps () {
  # shellcheck disable=SC2207
  local newHelperDeps=( $(echo "${1}" | tr '\n' "\n") )
  local i=$(( $2 ))
  for dependency in "${newHelperDeps[@]}"
  do
    DEP_MODIFIER=$(_get_dep_modifier "$dependency")
    DEP=$(_get_dep "$dependency")

    if [[ "$(_is_this_DS "$DEP")" == 'is' || "$(_is_already_there "$DEP")" == 'is' ]]
    then
      echo "${YELLOW}SKIPPING: $DEP...${NO_COLOR}"
      continue
    fi

    echo "${BLUE}Adding $DEP...${NO_COLOR}"
    _set_new_deps "$H\_DEP" "$DEP" "${i}"
    _add_dep_deps_with_type_and_access_modifier "$DEP_MODIFIER" "$H" "$DEP"
    echo "${GREEN}$DEP successfully added.${NO_COLOR}"
    (( i++ ))

    local infoContent=( "${(f)$(< ../../resources/helpers/"$DEP"/.info)}" )
    # shellcheck disable=SC2128
    if [[ -n "${infoContent}" ]]
    then
      _add_Helper_deps "${infoContent}" "$i"
    fi
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
  if [[ "${2}" == "$DS" ]]; then
    local infoContent=( "${(f)$(< ../"${3}"/.info)}" )
    _add_DS "${3}" "${1}"
  elif [[ "${2}" == "$H" ]]; then
    local infoContent=( "${(f)$(< ../../resources/helpers/"${3}"/.info)}" )
    _add_Helper "${3}" "${1}"
  fi
  # shellcheck disable=SC2128
  if [[ -n "${infoContent}" ]]; then
    if [[ "${2}" == "$DS" ]]; then
      _add_DS_deps "${infoContent}" 1
    elif [[ "${2}" == "$H" ]]; then
      _add_Helper_deps "${infoContent}" 1
    fi
  fi
  sed -i~ "/^ *$/d" .info
}

function EvalIndex() {
  sed -i~ "s#^\#ds[0-9]\+#\#ds$(( $(_get_DSs_count) ))#" Makefile
  sed -i~ "s#^\#hp[0-9]\+#\#hp$(( $(_get_Helpers_count) ))#" Makefile
}

function SetDepAccessModifier() {
  read -r MODIFIER_SELECTION
  case ${MODIFIER_SELECTION} in
      1 ) echo $PUBLIC;;
      2 ) echo $PROTECTED;;
      3 ) echo $PRIVATE;;
      * )
        echo "${YELLOW}Invalid selection: ${RED}${MODIFIER_SELECTION}.${NO_COLOR}"
        exit 1
  esac
}

function CallTasks() {
  CheckIfCanAdd "${3}"
  UpdateExtLibsLabel
  AddNewDependencies "${1}" "${2}" "${3}"
  EvalIndex
}

clear

echo "${CYAN}Do you wanna add a Data Structure or a Helper?${NO_COLOR}
${PURPLE}1 )${WHITE} Data Structure
${PURPLE}2 )${WHITE} Helper
${NO_COLOR}"
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
        1 ) FOLDER="Array";;
        2 ) FOLDER="SinglyLinkedList";;
        3 ) FOLDER="DoublyLinkedList";;
        4 ) FOLDER="CircularDoublyLinkedList";;
        5 ) FOLDER="StaticStack";;
        6 ) FOLDER="DynamicStack";;
        7 ) FOLDER="StaticQueue";;
        8 ) FOLDER="DynamicQueue";;
        9 ) FOLDER="Matrix";;
        10 ) FOLDER="UndirectedWeightedGraph";;
#--ADD_NEW_OPT
        * )
          echo "${YELLOW}Invalid selection: ${RED}${SELECTION}.${NO_COLOR}"
          exit 1
        ;;
    esac
    ;;
  2 )
    echo "${CYAN}Select new dependency to add:${WHITE}
${PURPLE}1 )${WHITE} Exception Handler
${PURPLE}2 )${WHITE} Node
${PURPLE}3 )${WHITE} Vertex
${NO_COLOR}" #--H

      read -r SELECTION

      case ${SELECTION} in
          1 ) FOLDER="ExceptionHandler";;
          2 ) FOLDER="Node";;
          3 ) FOLDER="Vertex";;
#--ADD_NEW_HELPER_OPT
          * )
            echo "${YELLOW}Invalid selection: ${RED}${SELECTION}.${NO_COLOR}"
            exit 1
          ;;
      esac
    ;;
  * )
    echo "${YELLOW}Invalid selection: ${RED}${DS_OR_HELPER}.${NO_COLOR}"
    exit 1
    ;;
esac

echo "${CYAN}What is the access modifier for this dependency?${WHITE}
${PURPLE}1 )${WHITE} Public
${PURPLE}2 )${WHITE} Protected
${PURPLE}3 )${WHITE} Private
${NO_COLOR}"
MODIFIER=$(SetDepAccessModifier)
TYPE=$DS
if [[ ${DS_OR_HELPER} == "2" ]]
then
  TYPE=$H
fi

CallTasks "$MODIFIER" "$TYPE" "$FOLDER"

echo "${GREEN}Finishing...${NO_COLOR}"
