

set(command "G:/program files/CMake/bin/cmake.exe;--build;.;--config;Debug")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-build-out.log"
  ERROR_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest build command succeeded.  See also G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(STATUS "${msg}")
endif()
