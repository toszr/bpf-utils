@echo off
setlocal
set "SCRIPT_DIR=%~dp0"

set "BUILD_OUTPUT_DIR=%SCRIPT_DIR%build"

set "OUTFILE=%BUILD_OUTPUT_DIR%\bpf-test.html"
set "INFILE=%SCRIPT_DIR%bpf-test.c"

set "WPCAP_LIBPCAP_SRC_DIR=%SCRIPT_DIR%winpcap\wpcap\libpcap"
set "DEPENDENCIES=gencode.c pcap.c grammar.c scanner.c nametoaddr.c optimize.c missing\snprintf.c etherent.c"
REM set "ADDITIONAL_OPTS=-DHAVE_STRLCPY -std=gnu99 "

if not exist "%BUILD_OUTPUT_DIR%" mkdir "%BUILD_OUTPUT_DIR%"

REM Transpile the libpcap C code (well, parts of it) 
REM to js or html (based on outfile extension)
pushd "%WPCAP_LIBPCAP_SRC_DIR%"
emcc "%INFILE%" %DEPENDENCIES% -I"%WPCAP_LIBPCAP_SRC_DIR%" -DINET6 -D_U_="" -o "%OUTFILE%" 
popd 


endlocal
