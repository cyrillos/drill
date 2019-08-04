_drill()
{
	local cmd cur prev words cword split=false

	if type -t _init_completion >/dev/null; then
		_init_completion -n = || return
	else
		# manual initialization for older bash completion versions
		COMPREPLY=()
		cur="${COMP_WORDS[COMP_CWORD]}"
		prev="${COMP_WORDS[COMP_CWORD-1]}"
	fi

	if [ $COMP_CWORD -gt 1 ] ; then
		cmd="${COMP_WORDS[1]}"
	else
		cmd="$prev"
	fi

	case "$cmd" in
	new)
		COMPREPLY=($(compgen -W '--category --language --name --difficulty --tag' -- $cur))
		return
		;;
	esac

	return
} &&
complete -F _drill drill
