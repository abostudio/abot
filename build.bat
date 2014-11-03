SET ABOT_HOME=%~dp0
SET PATH=%ABOT_HOME%/third_party/v8/third_party/cygwin/bin;%ABOT_HOME%/third_party/v8/build/gyp;%ABOT_HOME%/third_party/v8/third_party/python_26;%PATH%
REM ABOT
call gyp abot.gyp -DOUTDIR="output" -Dtarget_arch=ia32 -Dhost_arch=ia32 -Dcomponent=static_library -Dv8_optimized_debug=1 -Dicu_gyp_path="./../../third_party/icu/icu.gyp"  -Dclang=0 

REM refresh V8 build
call python third_party/v8/build/gyp_v8 -Dtarget_arch=ia32