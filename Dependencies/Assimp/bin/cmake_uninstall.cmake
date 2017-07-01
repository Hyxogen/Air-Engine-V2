IF(NOT EXISTS "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/install_manifest.txt\"")
ENDIF(NOT EXISTS "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/install_manifest.txt")

FILE(READ "G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Dependencies/Assimp/bin/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "G:/program files/CMake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
