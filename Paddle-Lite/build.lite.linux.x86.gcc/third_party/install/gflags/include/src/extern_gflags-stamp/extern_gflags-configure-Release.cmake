

set(command "/usr/local/bin/cmake;-DBUILD_STATIC_LIBS=ON;-DCMAKE_INSTALL_PREFIX=/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags;-DCMAKE_POSITION_INDEPENDENT_CODE=ON;-DBUILD_TESTING=OFF;-DCMAKE_BUILD_TYPE=;-DCMAKE_CXX_COMPILER=/usr/bin/c++;-DCMAKE_C_COMPILER=/usr/bin/cc;-DCMAKE_CXX_FLAGS= -fopenmp -mavx;-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG;-DCMAKE_CXX_FLAGS_DEBUG=-g;-DCMAKE_C_FLAGS= -fopenmp -mavx;-DCMAKE_C_FLAGS_DEBUG=-g;-DCMAKE_C_FLAGS_RELEASE=-O3 -DNDEBUG;-C/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/include/tmp/extern_gflags-cache-Release.cmake;-GUnix Makefiles;/home/admin1/paddle/Paddle-Lite/third-party/gflags")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/include/src/extern_gflags-stamp/extern_gflags-configure-out.log"
  ERROR_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/include/src/extern_gflags-stamp/extern_gflags-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/include/src/extern_gflags-stamp/extern_gflags-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "extern_gflags configure command succeeded.  See also /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/include/src/extern_gflags-stamp/extern_gflags-configure-*.log")
  message(STATUS "${msg}")
endif()
