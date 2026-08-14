@echo off
echo [FastCompress] Building Native Library...
call compile.bat
if errorlevel 1 exit /b 1

echo [FastCompress] Building Core Project...
call mvn clean package -DskipTests -q
if errorlevel 1 exit /b 1

echo [FastCompress] Running Demo...
cd examples\Demo
call mvn package -DskipTests -q
java -cp "target\demo-0.1.1.jar;..\..\target\FastCompress-0.1.1.jar;%USERPROFILE%\.m2\repository\com\github\andrestubbe\FastCore\0.1.0\FastCore-0.1.0.jar;%USERPROFILE%\.m2\repository\com\github\andrestubbe\fastcore\0.1.0\fastcore-0.1.0.jar" fastcompress.demo.Demo
cd ..\..
pause
