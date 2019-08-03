#! /bin/sh

if [ $# -lt 1 ]; then
	echo "Usage: $0 <name>" >&2
	exit 1
fi

name=$1

dir=`dirname $0`

mkdir -p $dir/$name
echo "[NAME](https://xxx/$name/)" > $dir/$name/problem.md
cat <<EOF >>$dir/$name/solution.py
class Solution:
    def name(self):
        return 0

data = [
]
for i in range(0, len(data)):
    print(Solution().name(data[i]))
EOF
