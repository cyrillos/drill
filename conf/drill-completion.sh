_drill()
{
	local cur prev

	cur=${COMP_WORDS[COMP_CWORD]}
	prev=${COMP_WORDS[COMP_CWORD-1]}
	options="--category --language --name --difficulty --tag"

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
			COMPREPLY=($(compgen -W "leetcode google yandex codility facebook geeksforgeeks amazon codeforces" -- ${cur}))
			;;
		--language)
			COMPREPLY=($(compgen -W "python3 cpp" -- ${cur}))
			;;
		--difficulty)
			COMPREPLY=($(compgen -W "easy medium hard" -- ${cur}))
			;;
		*)
			COMPREPLY=($(compgen -W "${options}" -- ${cur}))
			;;
		esac
            	;;
    	esac
}
complete -F _drill drill
