

set(command "/usr/local/bin/cmake;-DCMAKE_INSTALL_PREFIX=/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/xbyak;-C/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/tmp/extern_xbyak-cache-Release.cmake;-GUnix Makefiles;/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/src/extern_xbyak")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/src/extern_xbyak-stamp/extern_xbyak-configure-out.log"
  ERROR_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/src/extern_xbyak-stamp/extern_xbyak-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/src/extern_xbyak-stamp/extern_xbyak-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "extern_xbyak configure command succeeded.  See also /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/xbyak/src/extern_xbyak-stamp/extern_xbyak-configure-*.log")
  message(STATUS "${msg}")
endif()
