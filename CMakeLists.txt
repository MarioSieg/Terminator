project("Terminator" C)

add_library("libterminator" STATIC
"src/stream.c"
"src/stream.h" 
"src/branch_hints.h" "src/x86_64/registers.h" "src/x86_64/registers.c" "src/x86_64/instruction.h" "src/x86_64/instruction.c" "src/x86_64/machine.h" "src/x86_64/machine.c" "src/imm.h" "src/imm.c")

add_executable("terminator" "src/exec.c")
target_link_libraries("terminator" "libterminator")

if(MSVC)
  target_compile_options("terminator" PRIVATE /W3 /WX)
  target_compile_options("libterminator" PRIVATE /W3 /WX)
else()
  target_compile_options("terminator" PRIVATE -Wall -Wextra -pedantic -Werror)
  target_compile_options("libterminator" PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
