

set(command "/usr/local/bin/cmake;-DCMAKE_CXX_COMPILER=/usr/bin/c++;-DCMAKE_C_COMPILER=/usr/bin/cc;-DCMAKE_CXX_FLAGS= -fopenmp -mavx;-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG;-DCMAKE_CXX_FLAGS_DEBUG=-g;-DCMAKE_C_FLAGS= -fopenmp -mavx;-DCMAKE_C_FLAGS_DEBUG=-g;-DCMAKE_C_FLAGS_RELEASE=-O3 -DNDEBUG;-DCMAKE_INSTALL_PREFIX=/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/glog;-DCMAKE_POSITION_INDEPENDENT_CODE=ON;-DWITH_GFLAGS=ON;-Dgflags_DIR=/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/gflags/lib/cmake/gflags;-DBUILD_TESTING=OFF;-DCMAKE_BUILD_TYPE=;-C/home/admin1/paddle/Paddle-Lite/third-party/glog/tmp/extern_glog-cache-Release.cmake;-GUnix Makefiles;/home/admin1/paddle/Paddle-Lite/third-party/glog")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/glog/glog-stamp/extern_glog-configure-out.log"
  ERROR_FILE "/home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/glog/glog-stamp/extern_glog-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/glog/glog-stamp/extern_glog-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "extern_glog configure command succeeded.  See also /home/admin1/paddle/Paddle-Lite/build.lite.linux.x86.gcc/third_party/install/glog/glog-stamp/extern_glog-configure-*.log")
  message(STATUS "${msg}")
endif()
