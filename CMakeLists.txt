project("Terminator" C)

add_library("libterminator" STATIC
"src/stream.c"
"src/stream.h" 
"src/branch_hints.h")

add_executable("terminator" "src/exec.c")
target_link_libraries("terminator" "libterminator")
