#!/bin/bash

### Author: Anonymous.

extendedhelp="### $0
# 
# Combines an arbitrary amount of pdf documents into one by appending the documents one after another.
# 
###"

output_file_default='/dev/stdout'

errmsg() {
  if [ "$#" -ge "1" ]; then
    msg="$1"
  else
    msg="$0: Unspecified error."
  fi
  
  echo "${msg}" >> /dev/stderr
}

exiterror() {
  if [ "$#" -ge "1" ]; then
    msg="$1"
  else
    msg="$0: Unspecified error."
  fi
  
  if [ "$#" -ge "2" ]; then
    exitcode="$2"
  else
    exitcode=2
  fi
  
  errmsg "${msg}"
  exit "${exitcode}"
}

printusage() {
  echo "Usage:"
  echo "  $0 <pdf_input_files> [<pdf_output_file]"
  echo "(<pdf_output_file> defaults to '${output_file_default}')"
}

printextendedhelp() {
  echo "${extendedhelp}"
}

if [ "$#" -lt "1" ]; then
  errmsg "$0: Error: Too few arguments specified."
  errmsg ""
  errmsg "$(printusage)"
  errmsg ""
  errmsg "=== Extended information on this software: ==="
  errmsg ""
  errmsg "$(printextendedhelp)"
  errmsg ""
  exiterror "$0: Aborting, since too few arguments specified." 1
fi

if [ "$#" -ge "1" ]; then
  output_file="${@: -1:1}" # Last argument: ${@: -1:1}
else
  output_file="${output_file_default}"
fi

### The following two lines are there to enable them for debugging:
# echo "I would call:"
# echo "pdftk ${@:1:$(($#-1))} cat output ${output_file}"
###

pdftk "${@:1:$(($#-1))}" cat output "${output_file}" # All but last arguments: ${@:1:$(($#-1))}
exitcode_pdftk="$?"

if [ "${exitcode_pdftk}" -ne 0 ]; then
  errmsg "$0: Error: The run of 'pdftk' produced an error. See above error message from the call to 'pdftk' for details."
fi
exit "${exitcode_pdftk}"
