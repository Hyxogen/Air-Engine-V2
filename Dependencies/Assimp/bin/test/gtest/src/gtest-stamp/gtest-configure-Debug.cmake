

set(command "G:/program files/CMake/bin/cmake.exe;-DCMAKE_BUILD_TYPE=;-Dgtest_force_shared_crt=ON;-Dgtest_disable_pthreads:BOOL=OFF;-DBUILD_GTEST=ON;-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs;-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs;-GVisual Studio 15 2017;G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-configure-out.log"
  ERROR_FILE "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest configure command succeeded.  See also G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/test/gtest/src/gtest-stamp/gtest-configure-*.log")
  message(STATUS "${msg}")
endif()
