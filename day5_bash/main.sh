#!/bin/bash

read_file() {
    local filename="$1"
    cat "$filename"
}

test_data="3-5
10-14
16-20
12-18

1
5
8
11
17
32"


part_one(){
  delim=$'\n\n'

  fresh_ids="${data%%$delim*}"
  available_ids="${data#*$delim*}"

  answer=0
  while read -r target; do
    while read -r range; do
      low="${range%%-*}"
      high="${range#*-}"
      if ((target >= low && target <= high)); then
        (( answer++ ))
        break
      fi
    done <<< $fresh_ids
  done <<< $available_ids

  echo $answer
}



part_two(){
  # echo "into"
  # data=$test_data
  delim=$'\n\n'

  fresh_ids="${data%%$delim*}"

  declare -a ranges

  # echo "extracting ranges"
  while read -r range; do
    ranges+=($range)
  done <<< $fresh_ids

  # echo "sorting"
  n=${#ranges[@]}
  for ((i = 0; i < n; i++)); do
    for ((j = 0; j < n - i - 1; j++)); do
      low_one="${ranges[j]%%-*}"
      low_two="${ranges[j+1]%%-*}"
      if (( low_one > low_two )); then
        temp=${ranges[j]}
        ranges[j]=${ranges[j+1]}
        ranges[j+1]=$temp
      fi
    done
  done

  echo "here are ranges before (${ranges[@]})"
  for (( i=n-2; i >= 0; i-- )); do
    current_element="${ranges[i]}"
    low="${current_element%%-*}"
    high="${current_element#*-}"

    for (( j=i+1; j<n; j++ )); do
      # echo "loop"
      next_element="${ranges[j]}"
      low_next="${next_element%%-*}"
      high_next="${next_element#*-}"
      if ((low_next>high)); then
        break
      fi

      if ((high_next>high)); then
        ranges[i]="$low-$high_next"
      fi

        unset "ranges[j]"
    done
  done
  ranges=("${ranges[@]}")

  answer=0

  n=${#ranges[@]}
  for (( i=0; i<n; i++ )); do
    current_element="${ranges[i]}"
    low="${current_element%%-*}"
    high="${current_element#*-}"
    ((answer+=(high-low+1)))
  done

  echo "here are ranges (${ranges[@]})"
  echo $answer
}

main(){
  data=$(read_file "./input.txt")
  # echo "hii"
  # echo $(part_one)
  echo $(part_two)
  
  # echo "bye"
  # echo "$test_data"
  # echo "$answers"
}

main
