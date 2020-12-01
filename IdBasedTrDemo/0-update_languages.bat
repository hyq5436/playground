set QT_DIR=C:\Qt\5.12.9\msvc2015_64\
%QT_DIR%\bin\lupdate -recursive . -source-language zh_CN -target-language en_GB -ts  i18n/app_en_GB.ts
%QT_DIR%\bin\lupdate -recursive . -source-language zh_CN -target-language en_US -ts  i18n/app_en_US.ts
%QT_DIR%\bin\lupdate -recursive . -source-language zh_CN -target-language zh_CN -ts  i18n/app_zh_CN.ts
%QT_DIR%\bin\lupdate -recursive . -source-language zh_CN -target-language zh_HK -ts  i18n/app_zh_HK.ts