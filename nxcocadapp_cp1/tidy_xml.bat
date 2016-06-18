@echo off
y:\comx_sdk\bin\tidy.exe -xml -imq -w 1024 --show-warnings no y:\nxcocadapp/script\script.ksc
y:\comx_sdk\bin\tidy.exe -xml -imq -w 1024 --show-warnings no y:\nxcocadapp/script\package.xml
y:\comx_sdk\bin\tidy.exe -xml -imq -w 1024 --show-warnings no y:\nxcocadapp/distribute\nxcocadapp.krelease
y:\comx_sdk\bin\tidy.exe -xml -imq -w 1024 --show-warnings no y:\nxcocadapp\nxcocadapp.kproduct
y:\comx_sdk\bin\tidy.exe -xml -imq -w 1024 --show-warnings no y:\nxcocadapp/kul\sample.kul
