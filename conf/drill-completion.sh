_drill()
{
	local cur prev

	cur=${COMP_WORDS[COMP_CWORD]}
	prev=${COMP_WORDS[COMP_CWORD-1]}
	options="--category --language --name --difficulty --tag"

	cats="leetcode google yandex codility facebook geeksforgeeks amazon codeforces"
	langs="python3 cpp"
	diffs="easy medium hard"

	tag="array bit-manipulation divide-and-conquer heap math stack"
	tag="${tag} two-pointers backtracking breadth-first-search"
	tag="${tag} dynamic-programming linked-list sliding-window string"
	tag="${tag} binary-search depth-first-search hash-table linked-lists"
	tag="${tag} sort tree union-find greedy graph prefix-sum"
	tag="${tag} binary-indexed-tree binary-tree segment-tree line-sweep"
	tag="${tag} string-matching hash-function binary-search-tree matrix"
	tag="${tag} trie monotonic-stack"

	case ${COMP_CWORD} in
	1)
		COMPREPLY=($(compgen -W "new" -- ${cur}))
		;;
	2)
		case ${prev} in
		new)
			COMPREPLY=($(compgen -W "${options}" -- ${cur}))
			;;
		esac
		;;
	*)
		case ${prev} in
		--category)
			COMPREPLY=($(compgen -W "${cats}" -- ${cur}))
			;;
		--language)
			COMPREPLY=($(compgen -W "${langs}" -- ${cur}))
			;;
		--difficulty)
			COMPREPLY=($(compgen -W "${diffs}" -- ${cur}))
			;;
		--tag)
			COMPREPLY=($(compgen -W "${tag}" -- ${cur}))
			;;
		*)
			COMPREPLY=($(compgen -W "${options}" -- ${cur}))
			;;
		esac
            	;;
    	esac
}
complete -F _drill drill
