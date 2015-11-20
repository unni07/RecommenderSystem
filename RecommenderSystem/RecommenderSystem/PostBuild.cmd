@pushd "%~1"
@xcopy BuildDependancies\*.dll "%~2" /y /s /q /d /C /F
@popd