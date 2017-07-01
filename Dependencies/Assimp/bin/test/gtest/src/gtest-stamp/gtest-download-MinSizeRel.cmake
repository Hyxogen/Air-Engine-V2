

set(command "G:/program files/CMake/bin/cmake.exe;-P;G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(STATUS "${msg}")
endif()
