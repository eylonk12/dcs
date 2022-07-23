################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/api.o: C:/Users/eylonk/dcs/lab5/source/api.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-gcc.exe" -c -mmcu=msp430g2553 -I"C:/ti/ccsv7/ccs_base/msp430/include_gcc" -I"C:/Users/eylonk/dcs/lab5/ccs workspace/eylon/lab5 project" -I"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/msp430-elf/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mhwmult=none -MMD -MP -MF"source/api.d" -MT"source/api.d" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bsp.o: C:/Users/eylonk/dcs/lab5/source/bsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-gcc.exe" -c -mmcu=msp430g2553 -I"C:/ti/ccsv7/ccs_base/msp430/include_gcc" -I"C:/Users/eylonk/dcs/lab5/ccs workspace/eylon/lab5 project" -I"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/msp430-elf/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mhwmult=none -MMD -MP -MF"source/bsp.d" -MT"source/bsp.d" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/halGPIO.o: C:/Users/eylonk/dcs/lab5/source/halGPIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-gcc.exe" -c -mmcu=msp430g2553 -I"C:/ti/ccsv7/ccs_base/msp430/include_gcc" -I"C:/Users/eylonk/dcs/lab5/ccs workspace/eylon/lab5 project" -I"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/msp430-elf/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mhwmult=none -MMD -MP -MF"source/halGPIO.d" -MT"source/halGPIO.d" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/main.o: C:/Users/eylonk/dcs/lab5/source/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/bin/msp430-elf-gcc.exe" -c -mmcu=msp430g2553 -I"C:/ti/ccsv7/ccs_base/msp430/include_gcc" -I"C:/Users/eylonk/dcs/lab5/ccs workspace/eylon/lab5 project" -I"C:/ti/ccsv7/tools/compiler/msp430-gcc-6.4.0.32_win32/msp430-elf/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -mhwmult=none -MMD -MP -MF"source/main.d" -MT"source/main.d" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


