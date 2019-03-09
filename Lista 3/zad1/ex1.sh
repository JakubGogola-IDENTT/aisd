#!/bin/bash

#Declaring variables.
oldsectread=0
oldsectwrite=0
oldload=0

newsectread=0
newsectwrite=0
newload=0

tabread=(0 0 0 0 0 0)
tabwrite=(0 0 0 0 0 0)
tabload=(0 0 0 0 0 0)

#Setting new values of variables.
function newStats {
  line=$( cat /proc/meminfo | grep "MemFree: " )
  i=0
  for temp in $line
  do
    tab[$i]=$temp
    i=`expr $i + 1`
  done
  newsectread=${tab[5]}
  newsectwrite=${tab[9]}

  line=$( cat /proc/loadavg )
  i=0
  for temp in $line
  do
    tab[$i]=$temp
    i=`expr $i + 1`
  done
  newload=${tab[0]}
}

#Remembering old values of variables.
function oldStats {
  oldsectread=$newsectread
  oldsectwrite=$newsectwrite
  oldload=$newload
}

#Counting difference between new and old values.
function countDiff {
  dsectread=$( echo "($newsectread - $oldsectread) * 512" | bc )
  dsectwrite=$( echo "($newsectwrite - $oldsectwrite) * 12" | bc )
  dload=$newload
}

#Shifting arrays
function shiftTab {
  declare -i i
  for((i=0; i<5; i++))
  do
    tabread[$i]=${tabread[`expr $i + 1`]}
    tabwrite[$i]=${tabwrite[`expr $i + 1`]}
    tabload[$i]=${tabload[`expr $i + 1`]}
  done

  tabread[5]=$dsectread
  tabwrite[5]=$dsectwrite
  tabload[5]=$dload
}

#Finding maximum value
function setMax {
  maxread=${tabread[0]}
  maxwrite=${tabwrite[0]}
  maxload=${tabload[0]}

  declare -i i
  for((i=1; i<=5; i++))
  do
    if [ $maxread -lt ${tabread[$i]} ]
      then
      maxread=${tabread[$i]}
    fi

    if [ $maxwrite -lt ${tabwrite[$i]} ]
      then
      maxwrite=${tabwrite[$i]}
    fi

    if [[ `echo "$maxload < ${tabload[$i]}" | bc`  -eq 1 ]]
      then
      maxload=${tabload[$i]}
    fi
  done
}

function setScale {
  valname=$1
  value=$2
  if [ `echo "$value / 1024" | bc` -eq 0 ]
    then
    gawk 'BEGIN {print "'$valname'" "'$value'" " B/s"}'
  elif [ `echo "${tabval[5]} / 1024" | bc` -gt 0 ] && [ `echo "${tabval[5]} / 1024" | bc` -lt 1024 ]
    then
      value=$( echo "$value / 1024" | bc )
      gawk 'BEGIN {print "'$valname'" "'$value'" " kB/s"}'
    else
      value=$( echo "$value / 1048576" | bc )
      gawk 'BEGIN {print "'$valname'" "'$value'" " MB/s"}'
  fi
}

#Drawing graph.
function drawGraph {
  name=$1
  tpX=$2
  tpY=$3
  maxval=$4
  tabval=($5 $6 $7 $8 $9 ${10})
  tput sc
  declare -i i
  for((i=0; i<6; i++))
  do
    tput cup `expr $tpX + $i` $tpY
    if [ `echo "$maxval != 0" | bc`  -eq 1  ] || [ `echo "$maxval != 0.0" | bc`  -eq 1 ]
      then
      n=`calc '('${tabval[$i]}' / '$maxval') * 10' | sed -e "s/\..*//" | sed -e "s/~//"`
    else
      n=0
    fi

    if [ $n -gt 10 ]
      then
      n=10
    fi

    tput setab 1
    declare -i j
    for ((j=0; j<$n; j++))
    do
      tput cup `expr $tpX + $i` `expr $tpY + $j`
      gawk 'BEGIN {print " "}'
    done

    tput setab 0
    for ((j=0; j<`expr 10 - $n`; j++))
    do
      tput cup `expr $tpX + $i` `expr $tpY + $n + $j`
      gawk 'BEGIN {print " "}'
    done

    for ((j=0; j<20; j++))
    do
      tput cup `expr $tpX + $i` `expr $tpY + 10 + $j`
      gawk 'BEGIN {print " "}'
    done

    tput cup `expr $tpX + $i` `expr $tpY + 11`
    gawk 'BEGIN {print "|"'${tabval[$i]}' " B/s"}'
  done

  for ((j=0; j<30; j++))
  do
    tput cup  `expr $tpX + 8` `expr $tpY + $j`
    gawk 'BEGIN {print " "}'
  done
  name+=": "

  tput cup `expr $tpX + 8` $tpY
  setScale $name ${tabval[5]}
  tput rc
}

first=1

clear

while [ 1 -eq 1 ]
do
  tput civis
  if [ $first -eq 1 ]
    then
    newStats
    oldsectread=$newsectread
    oldsectwrite=$newsectwrite
    countDiff
    setMax
    shiftTab
    first=0
  else
    newStats
    shiftTab
    countDiff
    setMax
  fi
  drawGraph 'Read' 2 2 $maxread ${tabread[0]} ${tabread[1]} ${tabread[2]} ${tabread[3]} ${tabread[4]} ${tabread[5]}
  drawGraph 'Write' 2 32 $maxwrite ${tabwrite[0]} ${tabwrite[1]} ${tabwrite[2]} ${tabwrite[3]} ${tabwrite[4]} ${tabwrite[5]}
  drawGraph 'Load' 2 62 $maxload ${tabload[0]} ${tabload[1]} ${tabload[2]} ${tabload[3]} ${tabload[4]} ${tabload[5]}
  oldStats
  tput cnorm
done