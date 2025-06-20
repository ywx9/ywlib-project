@echo off
set HERE=%~dp0
set HERE=%HERE:~0,-1%

set RET=0
if not exist "%HERE%\ywlib.ifc" (
  call "%HERE%\compile-module.bat"
  set RET=%errorlevel%
)
if not exist "%HERE%\ywlib.obj" (
  call "%HERE%\compile-module.bat"
  set RET=%errorlevel%
)

if %RET% neq 0 (
  exit /b %RET%
)

set SOURCE=%1
if "%SOURCE%"=="" (
  echo. Usage: ywlib/compile [source file]
  exit /b 1
)

echo(#include "../%SOURCE%" > "%HERE%\compile.cpp"
@REM echo(int wWinMain(HANDLE, HANDLE, wchar_t*, int) { >> "%HERE%\compile.cpp"
echo(int wmain(int, wchar_t**) { >> "%HERE%\compile.cpp"
echo(  int return_code = 0; >> "%HERE%\compile.cpp"
echo(  try { >> "%HERE%\compile.cpp"
echo(    return_code = yw::main::main(); >> "%HERE%\compile.cpp"
echo(  } catch (const std::exception^& e) { >> "%HERE%\compile.cpp"
echo(    std::cout ^<^< e.what() ^<^< std::endl; >> "%HERE%\compile.cpp"
echo(  } >> "%HERE%\compile.cpp"
echo(  return return_code; >> "%HERE%\compile.cpp"
echo(} >> "%HERE%\compile.cpp"

echo(import os, sys, subprocess > "%HERE%\compile.py"
echo(CL = fR"%HERE%\bin\cl.exe" >> "%HERE%\compile.py"
echo(STDIFC = fR"%HERE%\ywlib.ifc" >> "%HERE%\compile.py"
echo(STDOBJ = fR"%HERE%\ywlib.obj" >> "%HERE%\compile.py"
echo(cpp_file = fR'%SOURCE%' >> "%HERE%\compile.py"
echo(exe_file = os.path.splitext(cpp_file)[0] + '.exe' >> "%HERE%\compile.py"
echo(obj_file = os.path.splitext(cpp_file)[0] + '.obj' >> "%HERE%\compile.py"
echo(args = [CL, R'%HERE%\compile.cpp', f'/Fe{exe_file}', f'/Fo{obj_file}', '/D__ywlib_import', ] >> "%HERE%\compile.py"
echo(args+= ['/std:c++latest', '/EHsc', '/nologo', '/W4', '/O2', '/Qpar', '/utf-8', '/diagnostics:caret', ] >> "%HERE%\compile.py"
echo(args+= [fR'/I%HERE%', f'/referenceywlib={STDIFC}', '/link', STDOBJ, fR'/LIBPATH:%HERE%\lib', ] >> "%HERE%\compile.py"
echo(print(f'compiling {cpp_file}', end='', flush=True) >> "%HERE%\compile.py"
echo(result = subprocess.run(args, capture_output=True, text=True, encoding='cp932') >> "%HERE%\compile.py"
echo(if os.path.exists(obj_file): os.remove(obj_file) >> "%HERE%\compile.py"
echo(print(f' -^> {result.returncode}') >> "%HERE%\compile.py"
echo(if result.returncode != 0: >> "%HERE%\compile.py"
echo(  print(result.stdout) >> "%HERE%\compile.py"
echo(  sys.exit(result.returncode) >> "%HERE%\compile.py"
echo(if '--run' in sys.argv: >> "%HERE%\compile.py"
echo(  sys.argv.remove('--run')  >> "%HERE%\compile.py"
echo(  sys.argv[0] = exe_file  >> "%HERE%\compile.py"
echo(  sys.argv[1] = "--ywlib"  >> "%HERE%\compile.py"
echo(  return_code = subprocess.run(sys.argv).returncode >> "%HERE%\compile.py"
echo(  print(f'{exe_file} returns -^> {return_code}') >> "%HERE%\compile.py"
call python "%HERE%\compile.py" %*
set RET=%errorlevel%
del "%HERE%\compile.cpp" > nul
del "%HERE%\compile.py" > nul
exit /b %RET%
