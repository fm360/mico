@set /a tmp = %1-1 
@call :toHex %tmp% end1
@set /a tmp2 = %2-1
@call :toHex %tmp2% end2

@set /a tmp3 = %3-1 
@call :toHex %tmp3% end3
@set /a tmp4 = %4-1
@call :toHex %tmp4% end4


@echo echo image 2 start %1
@echo echo image 1 end 0x%end1%
@echo off
@echo ^<?xml version="1.0" encoding="iso-8859-1"?^> > tmp2.board
@echo.  >> tmp2.board
@echo ^<flash_board^> >> tmp2.board
@echo   ^<pass^>    >> tmp2.board
@echo   	^<range^>CODE 0x10000bc8 0x%end1%^</range^>    >> tmp2.board
@echo     ^<loader^>$PROJ_DIR$\..\..\..\component\soc\realtek\8195a\misc\iar_utility\common\flashloader\FlashRTL8195aMP.flash^</loader^>    >> tmp2.board
@echo     ^<abs_offset^>0x00000000^</abs_offset^>    >> tmp2.board
@echo     ^<args^>--head    >> tmp2.board
@echo     --img2_addr    >> tmp2.board
@echo     0xB000^</args^>    >> tmp2.board
@echo   ^</pass^>    >> tmp2.board
@echo   ^<pass^> >> tmp2.board
@echo   	^<range^>CODE %1 0x%end2%^</range^> >> tmp2.board
@echo     ^<loader^>$PROJ_DIR$\..\..\..\component\soc\realtek\8195a\misc\iar_utility\common\flashloader\FlashRTL8195aMP.flash^</loader^>    >> tmp2.board
@echo     ^<abs_offset^>0xB000^</abs_offset^>  >> tmp2.board
@echo   ^</pass^> >> tmp2.board



@echo   ^<ignore^>CODE 0x00000000 0x000FFFFF^</ignore^> >> tmp2.board 
@echo   ^<ignore^>CODE 0x10000000 0x10000bc7^</ignore^> >> tmp2.board
@echo   ^<ignore^>CODE %2 0x1006FFFF^</ignore^> >> tmp2.board
@echo ^</flash_board^> >> tmp2.board    >> tmp2.board

exit

:toHex dec hex -- convert a decimal number to hexadecimal, i.e. -20 to FFFFFFEC or 26 to 0000001A
@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
set /a dec=%~1
set "hex="
set "map=0123456789ABCDEF"
for /L %%N in (1,1,8) do (
    set /a "d=dec&15,dec>>=4"
    for %%D in (!d!) do set "hex=!map:~%%D,1!!hex!"
)

( ENDLOCAL & REM RETURN VALUES
    IF "%~2" NEQ "" (SET %~2=%hex%) ELSE ECHO.%hex%
)
EXIT /b
