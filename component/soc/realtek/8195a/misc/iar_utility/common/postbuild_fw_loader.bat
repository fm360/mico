cd /D %2
set tooldir=%2\..\..\..\component\soc\realtek\8195a\misc\iar_utility\common\tools
set libdir=%2\..\..\..\component\soc\realtek\8195a\misc\bsp
set cfgdir=%3

echo config %3

del %cfgdir%/Exe/target.map %cfgdir%/Exe/fw_loader.asm *.bin
cmd /c "%tooldir%\nm %cfgdir%/Exe/fw_loader.axf | %tooldir%\sort > %cfgdir%/Exe/fw_loader.map"
cmd /c "%tooldir%\objdump -d %cfgdir%/Exe/fw_loader.axf > %cfgdir%/Exe/fw_loader.asm"

for /f "delims=" %%i in ('cmd /c "%tooldir%\grep FWLOADER %cfgdir%/Exe/fw_loader.map | %tooldir%\grep Base | %tooldir%\gawk '{print $1}'"') do set fwloader_start=0x%%i
for /f "delims=" %%i in ('cmd /c "%tooldir%\grep FWLOADER %cfgdir%/Exe/fw_loader.map | %tooldir%\grep Limit | %tooldir%\gawk '{print $1}'"') do set fwloader_end=0x%%i

::echo %ram1_start% > tmp.txt
::echo %ram2_start% >> tmp.txt
::echo %ram3_start% >> tmp.txt
::echo %ram1_end% >> tmp.txt
::echo %fwloader_start% >> tmp.txt
::echo %fwloader_end% >> tmp.txt

%tooldir%\objcopy -j "A3 rw" -Obinary %cfgdir%/Exe/fw_loader.axf %cfgdir%/Exe/fw_loader.bin


%tooldir%\pick %fwloader_start% %fwloader_end% %cfgdir%\Exe\fw_loader.bin %cfgdir%\Exe\fw_loader.p.bin body+reset_offset+sig
%tooldir%\pick %fwloader_start% %fwloader_end% %cfgdir%\Exe\fw_loader.bin %cfgdir%\Exe\fw_loader.ns.bin body+reset_offset

copy /b %cfgdir%\Exe\fw_loader.p.bin %cfgdir%\Exe\mico_bootloader.bin

:: %tooldir%\pick %fwloader_start% %fwloader_end% %cfgdir%\Exe\fw_loader.bin %cfgdir%\Exe\fw_loader.r.bin raw
:: copy %cfgdir%\Exe\fw_loader.bin %cfgdir%\Exe\fw_loader.r.bin



:: %tooldir%\padding 24k 0xFF %cfgdir%\Exe\ram_1.r.bin
:: copy /b %cfgdir%\Exe\ram_1.r.bin+%cfgdir%\Exe\fw_loader.r.bin %cfgdir%\Exe\ram_5.r.bin

%tooldir%\..\gen_board_fw_loader.bat %fwloader_start% %fwloader_end%

echo 6666666 > tmp.txt
exit
