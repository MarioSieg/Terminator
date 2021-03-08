project("Terminator" C)

add_library("libterminator" STATIC
"src/stream.c"
"src/stream.h")

add_executable("terminator" "src/exec.c")