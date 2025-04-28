#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
BOLD='\033[1m'
RESET='\033[0m'

print_header() {
    clear
    echo -e "${BLUE}${BOLD}"
    echo "████████╗███████╗███████╗████████╗███████╗██████╗     ██╗  ██╗██████╗ ███████╗██╗  ██╗"
    echo "╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗    ██║  ██║╚════██╗██╔════╝██║  ██║"
    echo "   ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝    ███████║ █████╔╝███████╗███████║"
    echo "   ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗    ╚════██║██╔═══╝ ╚════██║██╔══██║"
    echo "   ██║   ███████╗███████║   ██║   ███████╗██║  ██║         ██║███████╗███████║██║  ██║"
    echo "   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝         ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝"
    echo -e "${RESET}${YELLOW}${BOLD}                     You know the answer...${RESET}\n"
    echo -e "${CYAN}${BOLD}===========================================================================${RESET}"
    echo -e "${WHITE}${BOLD}Testing script for 42sh UNIX Shell${RESET}"
    echo -e "${CYAN}${BOLD}===========================================================================${RESET}\n"
}

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

disp_test()
{
  id=$1
  $CAT tests | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      echo -e "Test $id ($NAME) : ${GREEN}${BOLD}OK${RESET}"
      if [ $debug -eq 2 ]
      then
        echo -e "${YELLOW}Output $MYSHELL :${RESET}"
        $CAT -e /tmp/.shell.$$
        echo "" 
        echo -e "${YELLOW}Output $REFER :${RESET}"
        $CAT -e /tmp/.refer.$$
        echo ""
      fi
    else
      echo -e "${GREEN}${BOLD}OK${RESET}"
    fi
  else
    if [ $debug -ge 1 ]
    then
      echo -e "Test $id ($NAME) : ${RED}${BOLD}KO${RESET} - Check output in /tmp/test.$$/$id/" 
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.shell.$$ /tmp/test.$$/$id/mysh.out
      $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
    else
      echo -e "${RED}${BOLD}KO${RESET}"
    fi
  fi
}

print_header

if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig !" $sig
    fi
  done
fi

if [ ! -f tests ]
then
  echo -e "${RED}${BOLD}No tests file. Please read README.ME${RESET}" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo -e "${RED}${BOLD}$MYSHELL not found${RESET}" >&2
  exit 1
fi

if [ $# -eq 2 ]
then
  echo -e "${CYAN}Debug mode${RESET}" >&2
  echo -e "${CYAN}Shell : $MYSHELL${RESET}" >&2
  echo -e "${CYAN}Reference : $REFER${RESET}" >&2
  echo ""
fi

echo -e "${MAGENTA}${BOLD}Running tests...${RESET}\n"

if [ $# -eq 0 ]
then
  for lst in `cat tests | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
  do
    path_backup=$PATH
    load_test $lst 1
    export PATH=$path_backup
  done
else
  if [ $# -eq 1 ]
  then
    load_test $1 0
  else
    if [ "X$1" = "X-d" ]
    then
      load_test $2 2
    else
      load_test $1 2
    fi
  fi
fi

echo -e "\n${CYAN}${BOLD}===========================================================================${RESET}"
echo -e "${WHITE}${BOLD}Tests completed${RESET}"
echo -e "${CYAN}${BOLD}===========================================================================${RESET}\n"