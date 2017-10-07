#!/usr/bin/bash

# convert USA local call NXX list from http://localcallingguide.com/
# to HylaFax+ dialrules

set -u
set -e

if [ -z "${1:-}" ]; then
  echo "Usage: $(basename "$0") nnx.txt > nnxmytown.txt"
  echo "Create nnx.txt from local nnx listing at"
  echo "http://localcallingguide.com/"
  echo "Search, Area Code/Prefix, ..., ..., Local prefixes"
  exit 1
fi

message='! local NNX list generated by localnxxtoregex.sh from Arch Linux HylaFax+ package'

_fn_display() {
  if [ ! -z "${nx}" ]; then
    if [ ! -z "${message}" ]; then
      echo "${message}"
      message=''
    fi
    local tx
    if [ "${#x}" -gt 1 ]; then
      x="[${x}]"
      tx="(${nx}${x})"
    else
      tx="(${nx}${x})\t" # keep tabs lined up
    fi
    local _tx="(${nx}${x})"
    echo -e '^${Country}${Area}'"${tx}\t= \1\t\t! USA NNX/NXX local ${npas[2]} calls"
    nx=''
    x=''
  fi
}

readarray -t npalist < <(grep '^[0-9]' "$1" | LC_ALL=C sort)
#declare -p npalist

nx=''
x=''
# 555 & 556 will be coalesced into 55[56]
#NPA;NXX;Rate Centre;Region;Plan Type;Call Type;Monthly Limit;Note;Effective
#517;555;Operator;MI;;;;;
#517;556;Operator;MI;;;;;
#517;560;Operator;MI;;;;;
#517;570;Operator;MI;;;;;
for npaline in "${npalist[@]}"; do
  IFS=';' read -r -a npas <<<"${npaline}"
  nnx="${npas[1]}"
  if [ "${nnx#${nx}}" = "${nnx}" ]; then
    _fn_display
    nx="${nnx: 0:2}"
    x="${nnx: 2:1}"
  else
    x+="${nnx: 2:1}"
  fi
done
_fn_display