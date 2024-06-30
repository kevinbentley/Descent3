#!/bin/sh

# Runs clang-format on all *.cpp/*.h/*.json files in the project, excluding builds/
FILE_TYPES="*.cpp *.h *.json"
EXCLUDED="*/builds/*"

# Make sure we have a clang-format to use.
# Prefer any clang-format already in the user's $PATH.
# PATH=$PATH:/usr/bin/
which -s clang-format || (
    echo Unable to find clang-format in \$PATH.
    exit 1
)

# parse arguments
while [ "$1" != "" ]; do
    case $1 in
        -j | --jobs )
            shift
            JOBS="$1"
            ;;
        * )
            echo "Usage: lint.sh [-j|--jobs <NUM_JOBS>]"
            echo "    If -j is not specified, NUM_JOBS defaults to the number of CPU threads."
            exit 1
            ;;
    esac
    shift
done

# Figure out how parallel we're gonna be
# default to simple single-threaded xargs
EXECUTOR=xargs
if [ "$JOBS" != "1" ]; then
    # if xargs supports parallelism, use that
    if (echo foo bar | xargs -lkj -P 0$JOBS true 2>/dev/null); then
        # prefix the $JOBS with 0 so that unspecified JOBS becomes "0" and specified becomes "02" which is still valid
        # -n 1 so that xargs doesn't simply collect all the args into one job and break parallelism regardless
        EXECUTOR="xargs -P 0$JOBS -n 1"
    # if xargs doesn't support it, see if we can use GNU parallel
    elif which -s parallel; then
        # -X to spread the parameters evenly among jobs
        EXECUTOR="parallel -X"
        # if JOBS is explicitly set, add it (don't use 0-prefix trick; it triggers some buggy behavior in the "-j 0" case)
        if [ "$JOBS" != "" ]; then
            EXECUTOR="$EXECUTOR -j $JOBS"
        fi
    # if nothing supports parallelism, warn if the user appears to expect it
    elif [ "$JOBS" != "" ]; then
        echo "Warning: Parallel jobs specified, but installed xargs does not support -P and GNU parallel not found. Defaulting to single-threaded." >&2
    fi
fi

# takes the FILE_TYPES and EXCLUDED vars and concats them into find parameters
function path_args() {
    for i in $1; do
        echo -path "$i" -or
    done
}

# finally, run the job
find .                              \
    -type f                         \
    \(                              \
        $(path_args "$FILE_TYPES")  \
        -false                      \
    \)                              \
    -not \(                         \
        $(path_args "$EXCLUDED")    \
        -false                      \
    \)                              \
    -print0                         |
# pipe the file list into the executor (xargs or parallel) to run clang-format
$EXECUTOR --null clang-format -i
