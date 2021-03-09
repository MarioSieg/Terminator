project("Terminator" C)

add_library("libterminator" STATIC
"src/stream.c"
"src/stream.h" 
"src/branch_hints.h")

add_executable("terminator" "src/exec.c")
target_link_libraries("terminator" "libterminator")

if(MSVC)
  target_compile_options("terminator" PRIVATE /W4 /WX)
  target_compile_options("libterminator" PRIVATE /W4 /WX)
else()
  target_compile_options("terminator" PRIVATE -Wall -Wextra -pedantic -Werror)
  target_compile_options("libterminator" PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
