#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-none-eabi-gcc
CCC=arm-none-eabi-g++
CXX=arm-none-eabi-g++
FC=gfortran
AS=arm-none-eabi-gcc

# Macros
CND_PLATFORM=GnuArmEmbedded-Generic
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/71a66020/startup_stm32f030xc.o \
	${OBJECTDIR}/_ext/71a66020/system_stm32f0xx.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_adc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_comp.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crs.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dac.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dma.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_exti.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_gpio.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_i2c.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_pwr.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rcc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rtc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_spi.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_tim.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_usart.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_utils.o \
	${OBJECTDIR}/_ext/aafdca29/ws2812b.o \
	${OBJECTDIR}/_ext/58d20332/delay_us.o \
	${OBJECTDIR}/_ext/58d20332/iprintf.o \
	${OBJECTDIR}/_ext/df150946/error.o \
	${OBJECTDIR}/_ext/df150946/expression.o \
	${OBJECTDIR}/_ext/df150946/fifo.o \
	${OBJECTDIR}/_ext/df150946/ieee488.o \
	${OBJECTDIR}/_ext/df150946/lexer.o \
	${OBJECTDIR}/_ext/df150946/minimal.o \
	${OBJECTDIR}/_ext/df150946/parser.o \
	${OBJECTDIR}/_ext/df150946/units.o \
	${OBJECTDIR}/_ext/df150946/utils.o \
	${OBJECTDIR}/_ext/58d20332/queue.o \
	${OBJECTDIR}/_ext/58d20332/scpi-def.o \
	${OBJECTDIR}/_ext/58d20332/timer.o \
	${OBJECTDIR}/_ext/58d20332/ugui.o \
	${OBJECTDIR}/_ext/413f9488/LEDS.o \
	${OBJECTDIR}/_ext/413f9488/eeprom.o \
	${OBJECTDIR}/_ext/413f9488/i2c.o \
	${OBJECTDIR}/_ext/413f9488/inputs.o \
	${OBJECTDIR}/_ext/413f9488/internal_timer.o \
	${OBJECTDIR}/_ext/413f9488/mySCPI.o \
	${OBJECTDIR}/_ext/413f9488/power_supply.o \
	${OBJECTDIR}/_ext/413f9488/ssd1306.o \
	${OBJECTDIR}/_ext/413f9488/uart.o \
	${OBJECTDIR}/_ext/d29c42da/UI.o \
	${OBJECTDIR}/_ext/d29c42da/battery.o \
	${OBJECTDIR}/_ext/d29c42da/main.o \
	${OBJECTDIR}/_ext/d29c42da/syscalls.o \
	${OBJECTDIR}/_ext/d29c42da/systick.o


# C Compiler Flags
CFLAGS=--specs=nano.specs -fdata-sections -ffunction-sections

# CC Compiler Flags
CCFLAGS=--specs=nano.specs -fdata-sections -ffunction-sections
CXXFLAGS=--specs=nano.specs -fdata-sections -ffunction-sections

# Fortran Compiler Flags
FFLAGS=FortranCompiler

# Assembler Flags
ASFLAGS=--specs=nano.specs -fdata-sections -ffunction-sections -c -x assembler-with-cpp

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sc-ide.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sc-ide.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sc-ide ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--gc-sections -Wl,-Map=.map -Tnbproject/ldscript-${CND_CONF}.ld

${OBJECTDIR}/_ext/71a66020/startup_stm32f030xc.o: ../Drivers/CMSIS/startup_stm32f030xc.s
	${MKDIR} -p ${OBJECTDIR}/_ext/71a66020
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/_ext/71a66020/startup_stm32f030xc.o ../Drivers/CMSIS/startup_stm32f030xc.s

${OBJECTDIR}/_ext/71a66020/system_stm32f0xx.o: ../Drivers/CMSIS/system_stm32f0xx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/71a66020
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/71a66020/system_stm32f0xx.o ../Drivers/CMSIS/system_stm32f0xx.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_adc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_adc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_adc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_adc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_comp.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_comp.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_comp.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_comp.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crs.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crs.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crs.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crs.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dac.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dac.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dac.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dac.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dma.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dma.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dma.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_exti.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_exti.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_gpio.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_gpio.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_i2c.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_i2c.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_i2c.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_i2c.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_pwr.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_pwr.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rcc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rcc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rtc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rtc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rtc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rtc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_spi.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_spi.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_spi.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_spi.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_tim.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_tim.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_tim.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_tim.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_usart.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_usart.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_usart.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_utils.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_utils.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c

${OBJECTDIR}/_ext/aafdca29/ws2812b.o: ../Interfaces/ws2812b.c
	${MKDIR} -p ${OBJECTDIR}/_ext/aafdca29
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/aafdca29/ws2812b.o ../Interfaces/ws2812b.c

${OBJECTDIR}/_ext/58d20332/delay_us.o: ../Middlewares/delay_us.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/delay_us.o ../Middlewares/delay_us.c

${OBJECTDIR}/_ext/58d20332/iprintf.o: ../Middlewares/iprintf.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/iprintf.o ../Middlewares/iprintf.c

${OBJECTDIR}/_ext/df150946/error.o: ../Middlewares/libscpi/src/error.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/error.o ../Middlewares/libscpi/src/error.c

${OBJECTDIR}/_ext/df150946/expression.o: ../Middlewares/libscpi/src/expression.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/expression.o ../Middlewares/libscpi/src/expression.c

${OBJECTDIR}/_ext/df150946/fifo.o: ../Middlewares/libscpi/src/fifo.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/fifo.o ../Middlewares/libscpi/src/fifo.c

${OBJECTDIR}/_ext/df150946/ieee488.o: ../Middlewares/libscpi/src/ieee488.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/ieee488.o ../Middlewares/libscpi/src/ieee488.c

${OBJECTDIR}/_ext/df150946/lexer.o: ../Middlewares/libscpi/src/lexer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/lexer.o ../Middlewares/libscpi/src/lexer.c

${OBJECTDIR}/_ext/df150946/minimal.o: ../Middlewares/libscpi/src/minimal.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/minimal.o ../Middlewares/libscpi/src/minimal.c

${OBJECTDIR}/_ext/df150946/parser.o: ../Middlewares/libscpi/src/parser.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/parser.o ../Middlewares/libscpi/src/parser.c

${OBJECTDIR}/_ext/df150946/units.o: ../Middlewares/libscpi/src/units.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/units.o ../Middlewares/libscpi/src/units.c

${OBJECTDIR}/_ext/df150946/utils.o: ../Middlewares/libscpi/src/utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/df150946
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/df150946/utils.o ../Middlewares/libscpi/src/utils.c

${OBJECTDIR}/_ext/58d20332/queue.o: ../Middlewares/queue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/queue.o ../Middlewares/queue.c

${OBJECTDIR}/_ext/58d20332/scpi-def.o: ../Middlewares/scpi-def.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/scpi-def.o ../Middlewares/scpi-def.c

${OBJECTDIR}/_ext/58d20332/timer.o: ../Middlewares/timer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/timer.o ../Middlewares/timer.c

${OBJECTDIR}/_ext/58d20332/ugui.o: ../Middlewares/ugui.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/ugui.o ../Middlewares/ugui.c

${OBJECTDIR}/_ext/413f9488/LEDS.o: ../Peripherals/LEDS.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/LEDS.o ../Peripherals/LEDS.c

${OBJECTDIR}/_ext/413f9488/eeprom.o: ../Peripherals/eeprom.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/eeprom.o ../Peripherals/eeprom.c

${OBJECTDIR}/_ext/413f9488/i2c.o: ../Peripherals/i2c.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/i2c.o ../Peripherals/i2c.c

${OBJECTDIR}/_ext/413f9488/inputs.o: ../Peripherals/inputs.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/inputs.o ../Peripherals/inputs.c

${OBJECTDIR}/_ext/413f9488/internal_timer.o: ../Peripherals/internal_timer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/internal_timer.o ../Peripherals/internal_timer.c

${OBJECTDIR}/_ext/413f9488/mySCPI.o: ../Peripherals/mySCPI.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/mySCPI.o ../Peripherals/mySCPI.c

${OBJECTDIR}/_ext/413f9488/power_supply.o: ../Peripherals/power_supply.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/power_supply.o ../Peripherals/power_supply.c

${OBJECTDIR}/_ext/413f9488/ssd1306.o: ../Peripherals/ssd1306.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/ssd1306.o ../Peripherals/ssd1306.c

${OBJECTDIR}/_ext/413f9488/uart.o: ../Peripherals/uart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/uart.o ../Peripherals/uart.c

${OBJECTDIR}/_ext/d29c42da/UI.o: ../User/UI.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/UI.o ../User/UI.c

${OBJECTDIR}/_ext/d29c42da/battery.o: ../User/battery.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/battery.o ../User/battery.c

${OBJECTDIR}/_ext/d29c42da/main.o: ../User/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/main.o ../User/main.c

${OBJECTDIR}/_ext/d29c42da/syscalls.o: ../User/syscalls.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/syscalls.o ../User/syscalls.c

${OBJECTDIR}/_ext/d29c42da/systick.o: ../User/systick.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/systick.o ../User/systick.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
