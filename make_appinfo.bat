@echo off
echo Building app.info
echo (needs PSM SDK) 
"%SCE_PSM_SDK%\tools\python\python" "%SCE_PSM_SDK%\tools\PublishingUtility\cxml\appinfo\appinfo_compiler.py" "%CD%\app.xml"
copy "app.cxml" "app/app.info" /y
del "app.cxml"
