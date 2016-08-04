@echo off

FOR /F %%I IN ("%0") DO SET BASEDIR=%%~dpI
CD /D %BASEDIR%
CD

echo "Registering ActiveX Control.."
regsvr32 /s sopocx.ocx
regsvr32 /s sop.ocx

echo "Install VC Redist.."
vcredist_x86.exe /q

echo "Changing Registry.."
regedit /S foreground.reg

echo "Need To Restart.."
pause


