#!/bin/bash

set -e                              # should exit if any statement returns a non-true return value
set -o nounset                      # Treat unset variables as an error

### adduser: add a user
# Arguments:
#   name - for user
#   password - for user
# Return: user added to container
adduser()
{
    local name="${1}" passwd="${2}"
    useradd "$name" -M
    (echo $passwd ; echo $passwd ) | smbpasswd -s -a $name

    pdbedit -e smbpasswd:/etc/samba/sambausers.bak
}

### import: import a configuration file
# Arguments:
#   file - file to import
# Return: user(s) added to container
import()
{
    local name id file="${1}"
    while read name id; do
        useradd "$name" -M -u "$id"
    done < <(cut -d: -f1,2 --output-delimiter=' ' $file)
    pdbedit -i smbpasswd:$file
}

while getopts ":i:nu:" opt; do
    case "$opt" in
        i) import "$OPTARG" ;;
        n) NMBD="true" ;;
        u) eval adduser $(sed 's|;| |g' <<< $OPTARG) ;;
        "?") echo "Unknown option: -$OPTARG"; usage 1 ;;
        ":") echo "No argument value for option: -$OPTARG"; usage 2 ;;
    esac
done
shift $(( OPTIND - 1 ))

if [[ $# -ge 1 && -x $(which $1 2>&-) ]]; then
    exec "$@"
elif [[ $# -ge 1 ]]; then
    echo "ERROR: command not found: $1"
    exit 13
elif ps -ef | egrep -v grep | grep -q smbd; then
    echo "Service is already running"
else
    [[ ${NMBD:-""} ]] && ionice -c 3 nmbd -D
    exec systemctl start smbd </dev/null
fi