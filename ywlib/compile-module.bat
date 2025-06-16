@echo off
set here=%~dp0
set here=%here:~0,-1%

echo(export module ywlib; > "%here%\ywlib.ixx"
echo(#define _BUILD_STD_MODULE >> "%here%\ywlib.ixx"
echo(#include ^<ywlib^> >> "%here%\ywlib.ixx"

echo(import os, sys, subprocess > "%here%\compile.py"
echo(CL = fR"%here%\bin\cl.exe" >> "%here%\compile.py"
echo(STDIFC = fR"%here%\ywlib.ifc" >> "%here%\compile.py"
echo(STDOBJ = fR"%here%\ywlib.obj" >> "%here%\compile.py"
echo(if os.path.exists(STDIFC): os.remove(STDIFC) >> "%here%\compile.py"
echo(if os.path.exists(STDOBJ): os.remove(STDOBJ) >> "%here%\compile.py"
echo(args = [CL, '/c', fR'%here%\ywlib.ixx', '/D__ywlib_export', ] >> "%here%\compile.py"
echo(args+= ['/std:c++latest', '/EHsc', '/nologo', '/W4', '/O2', '/Qpar', '/utf-8', '/diagnostics:caret', ] >> "%here%\compile.py"
echo(args+= [f'/ifcOutput{STDIFC}', f'/Fo{STDOBJ}', fR'/I%here%', fR'/I%here%\inc', fR'/I%here%\std', ] >> "%here%\compile.py"
echo(print('compiling ywlib', end='', flush=True) >> "%here%\compile.py"
echo(result = subprocess.run(args, capture_output=True, text=True, encoding='cp932') >> "%here%\compile.py"
echo(print(f' -^> {result.returncode}') >> "%here%\compile.py"
echo(if result.returncode != 0: >> "%here%\compile.py"
echo(  print(result.stdout) >> "%here%\compile.py"
echo(  sys.exit(result.returncode) >> "%here%\compile.py"
call python "%here%\compile.py" %*
set RET=%errorlevel%
del "%here%\ywlib.ixx" >nul
del "%here%\compile.py" >nul
exit /b %RET%
