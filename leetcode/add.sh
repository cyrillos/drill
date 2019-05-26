#! /bin/sh

if [ $# -lt 1 ]; then
	echo "Usage: $0 <name> [<difficulty> <tags>]" >&2
	exit 1
fi

name=$1
difficulty=$2
tags=$3

dir=`dirname $0`

mkdir -p $dir/solutions/$name
echo "[NAME](https://leetcode.com/problems/$name/)" > $dir/solutions/$name/problem.md
touch $dir/solutions/$name/solution.py

if [ "$difficulty" ] ; then
	ln -sv ../../solutions/$name $dir/by-difficulty/$difficulty
fi

if [ "$tags" ] ; then
	for tag in `echo $tags | tr , \\\n`; do
		mkdir -pv $dir/by-tag/$tag
		ln -sv ../../solutions/$name $dir/by-tag/$tag
	done
fi
