function _vai_completion_ {
  if [ -f ~/.config/vai/config ]
  then

    if (( COMP_CWORD > 1 ))
    then
      [[ ${COMP_WORDS[1]} == -* ]] && return;

      local list pos

      pos=$(( COMP_CWORD - 1 ))
      list=()
      while read line
      do
        list+=( "$line" )
      done <<< "$(vai -c ${COMP_WORDS[1]} "${COMP_WORDS[@]:2}")"

      COMPREPLY=( $(compgen -W "$(vai -c ${COMP_WORDS[1]} " -- "${COMP_WORDS[COMP_CWORD]}") )
      # COMPREPLY=( $(compgen -W "${list[@]}" -- "${COMP_WORDS[COMP_CWORD]}") )

    elif (( COMP_CWORD == 1 ))
    then

      local list

      if [[ ${COMP_WORDS[1]} == -* ]]
      then
        list=( "-h" "-c" "-e" )
        COMPREPLY=( $(compgen -W "${list[@]}" -- "${COMP_WORDS[COMP_CWORD]}") )
      else
        list=( $(vai -e ${COMP_WORDS[1]}) )
        COMPREPLY=( $(compgen -W "${list[@]}" -- "${COMP_WORDS[COMP_CWORD]}") )
      fi
    fi
  fi
}

complete -o nosort -F _vai_completion_ vai
