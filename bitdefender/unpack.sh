#!/bin/bash

# Glue to keep unpack_makeself() unchanged
find_unpackable_file() { echo "$@"; }
debug-print() { :; }
emktemp() { mktemp "$@"; }
die() { eerror "$*"; exit 1; }
assert() { _pipestatus="${PIPESTATUS[*]}"; [[ "${_pipestatus// /}" -eq 0 ]] || die; }

# Straight copied from unpacker.eclass ... should be kept in sync

unpack_banner() {
	echo ">>> Unpacking ${1##*/} to ${PWD}"
}

unpack_makeself() {
	local src_input=${1:-${A}}
	local src=$(find_unpackable_file "${src_input}")
	local skip=$2
	local exe=$3

	[[ -z ${src} ]] && die "Could not locate source for '${src_input}'"

	unpack_banner "${src}"

	if [[ -z ${skip} ]] ; then
		local ver=$(grep -m1 -a '#.*Makeself' "${src}" | awk '{print $NF}')
		local skip=0
		exe=tail
		case ${ver} in
			1.5.*|1.6.0-nv*)	# tested 1.5.{3,4,5} ... guessing 1.5.x series is same
				skip=$(grep -a ^skip= "${src}" | cut -d= -f2)
				;;
			2.0|2.0.1)
				skip=$(grep -a ^$'\t'tail "${src}" | awk '{print $2}' | cut -b2-)
				;;
			2.1.1)
				skip=$(grep -a ^offset= "${src}" | awk '{print $2}' | cut -b2-)
				(( skip++ ))
				;;
			2.1.2)
				skip=$(grep -a ^offset= "${src}" | awk '{print $3}' | head -n 1)
				(( skip++ ))
				;;
			2.1.3)
				skip=`grep -a ^offset= "${src}" | awk '{print $3}'`
				(( skip++ ))
				;;
			2.1.4|2.1.5|2.1.6|2.2.0)
				skip=$(grep -a offset=.*head.*wc "${src}" | awk '{print $3}' | head -n 1)
				skip=$(head -n ${skip} "${src}" | wc -c)
				exe="dd"
				;;
			*)
				die "makeself version '${ver}' not supported"
				;;
		esac
		debug-print "Detected Makeself version ${ver} ... using ${skip} as offset"
	fi
	case ${exe} in
		tail)	exe="tail -n +${skip} '${src}'";;
		dd)		exe="dd ibs=${skip} skip=1 if='${src}'";;
		*)		die "makeself cant handle exe '${exe}'"
	esac

	# lets grab the first few bytes of the file to figure out what kind of archive it is
	local filetype tmpfile=$(emktemp)
	eval ${exe} 2>/dev/null | head -c 512 > "${tmpfile}"
	filetype=$(file -b "${tmpfile}") || die
	case ${filetype} in
		*tar\ archive*)
			eval ${exe} | tar --no-same-owner -xf -
			;;
		bzip2*)
			eval ${exe} | bzip2 -dc | tar --no-same-owner -xf -
			;;
		gzip*)
			eval ${exe} | tar --no-same-owner -xzf -
			;;
		compress*)
			eval ${exe} | gunzip | tar --no-same-owner -xf -
			;;
		XZ*)
			eval ${exe} | unxz | tar --no-same-owner -xf -
			;;
		*)
			eerror "Unknown filetype \"${filetype}\" ?"
			false
			;;
	esac
	assert "failure unpacking (${filetype}) makeself ${src##*/} ('${ver}' +${skip})"
	rm "${tmpfile}"
}

for x; do unpack_makeself "$x" ; done
