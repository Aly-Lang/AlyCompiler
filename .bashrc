alybuild() {
  # Default dialect
  DIALECT="att"

  # Parse options
  while getopts "d:" opt; do
    case $opt in
      d) DIALECT="$OPTARG" ;;
      *) echo "Usage: alybuild [-d dialect] <example>" >&2
         return 1 ;;
    esac
  done
  shift $((OPTIND - 1))

  # Require an argument (example path)
  if [ $# -lt 1 ]; then
    echo "Error: Missing example path (e.g., ../Examples/foo.aly)" >&2
    return 1
  fi

  cd /c/Dev/AlyCompiler && \
  mkdir -p bld && \
  cd bld && \
  cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc .. && \
  mingw32-make && \
  ./bin/alyc.exe -v -d "$DIALECT" "$@"
}
