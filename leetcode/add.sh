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
echo "[NAME](link)" > $dir/solutions/$name/problem.md
touch $dir/solutions/$name/solution.py

ln -sv ../../solutions/$name $dir/by-difficulty/$difficulty

for tag in `echo $tags | tr , \\\n`; do
	mkdir -pv $dir/by-tag/$tag
	ln -sv ../../solutions/$name $dir/by-tag/$tag
done
