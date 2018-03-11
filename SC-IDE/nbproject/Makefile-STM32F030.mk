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
CND_PLATFORM=GnuArmEmbedded_1-Generic
CND_DLIB_EXT=so
CND_CONF=STM32F030
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
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_can.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cec.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_comp.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cortex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dma.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_gpio.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2s.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_irda.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_iwdg.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smbus.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tsc.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart_ex.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_usart.o \
	${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_wwdg.o \
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
	${OBJECTDIR}/_ext/58d20332/queue.o \
	${OBJECTDIR}/_ext/413f9488/LEDS.o \
	${OBJECTDIR}/_ext/d29c42da/main.o \
	${OBJECTDIR}/_ext/d29c42da/systick.o \
	${OBJECTDIR}/_ext/d29c42da/timer.o


# C Compiler Flags
CFLAGS=-mthumb -mcpu=cortex-m0 --specs=nano.specs -fdata-sections -ffunction-sections -Og -g3 -Wextra -Wno-missing-field-initializers -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wimplicit -Werror=implicit-function-declaration -fno-common

# CC Compiler Flags
CCFLAGS=-mthumb -mcpu=cortex-m0 --specs=nano.specs -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fno-threadsafe-statics
CXXFLAGS=-mthumb -mcpu=cortex-m0 --specs=nano.specs -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fno-threadsafe-statics

# Fortran Compiler Flags
FFLAGS=FortranCompiler

# Assembler Flags
ASFLAGS=-mthumb -mcpu=cortex-m0 --specs=nano.specs -fdata-sections -ffunction-sections -c -x assembler-with-cpp

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/app.elf.exe

${CND_DISTDIR}/${CND_CONF}/app.elf.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/app.elf ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--gc-sections -Wl,-Map=${CND_DISTDIR}/${CND_CONF}/app.elf.map -Tnbproject/ldscript-${CND_CONF}.ld

${OBJECTDIR}/_ext/71a66020/startup_stm32f030xc.o: ../Drivers/CMSIS/startup_stm32f030xc.s
	${MKDIR} -p ${OBJECTDIR}/_ext/71a66020
	$(AS) $(ASFLAGS) -g -o ${OBJECTDIR}/_ext/71a66020/startup_stm32f030xc.o ../Drivers/CMSIS/startup_stm32f030xc.s

${OBJECTDIR}/_ext/71a66020/system_stm32f0xx.o: ../Drivers/CMSIS/system_stm32f0xx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/71a66020
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/71a66020/system_stm32f0xx.o ../Drivers/CMSIS/system_stm32f0xx.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_adc_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_can.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_can.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_can.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_can.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cec.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cec.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cec.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cec.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_comp.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_comp.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_comp.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_comp.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cortex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_cortex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_crc_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dac_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dma.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_dma.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_flash_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_gpio.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_gpio.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2c_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2s.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2s.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_i2s.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2s.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_irda.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_irda.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_irda.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_irda.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_iwdg.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_iwdg.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_iwdg.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_iwdg.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pcd_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_pwr_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rcc_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_rtc_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smartcard_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smbus.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smbus.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_smbus.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smbus.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_spi_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tim_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tsc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tsc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_tsc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tsc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_uart_ex.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_usart.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_usart.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_usart.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_wwdg.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_wwdg.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_hal_wwdg.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_wwdg.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_adc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_adc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_adc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_adc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_comp.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_comp.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_comp.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_comp.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crs.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crs.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_crs.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_crs.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dac.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dac.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dac.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dac.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dma.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_dma.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_dma.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_exti.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_exti.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_exti.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_gpio.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_gpio.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_gpio.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_i2c.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_i2c.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_i2c.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_i2c.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_pwr.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_pwr.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_pwr.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rcc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rcc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rcc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rtc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rtc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_rtc.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_rtc.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_spi.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_spi.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_spi.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_spi.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_tim.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_tim.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_tim.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_tim.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_usart.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_usart.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_usart.c

${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_utils.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7a539c06
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7a539c06/stm32f0xx_ll_utils.o ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_ll_utils.c

${OBJECTDIR}/_ext/aafdca29/ws2812b.o: ../Interfaces/ws2812b.c
	${MKDIR} -p ${OBJECTDIR}/_ext/aafdca29
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/aafdca29/ws2812b.o ../Interfaces/ws2812b.c

${OBJECTDIR}/_ext/58d20332/delay_us.o: ../Middlewares/delay_us.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/delay_us.o ../Middlewares/delay_us.c

${OBJECTDIR}/_ext/58d20332/iprintf.o: ../Middlewares/iprintf.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/iprintf.o ../Middlewares/iprintf.c

${OBJECTDIR}/_ext/58d20332/queue.o: ../Middlewares/queue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/58d20332
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/58d20332/queue.o ../Middlewares/queue.c

${OBJECTDIR}/_ext/413f9488/LEDS.o: ../Peripherals/LEDS.c
	${MKDIR} -p ${OBJECTDIR}/_ext/413f9488
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/413f9488/LEDS.o ../Peripherals/LEDS.c

${OBJECTDIR}/_ext/d29c42da/main.o: ../User/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/main.o ../User/main.c

${OBJECTDIR}/_ext/d29c42da/systick.o: ../User/systick.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/systick.o ../User/systick.c

${OBJECTDIR}/_ext/d29c42da/timer.o: ../User/timer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d29c42da
	${RM} "$@.d"
	$(COMPILE.c) -Wall -s -DSTM32F030C8T6 -DSTM32F030x8 -DUSE_FULL_LL_DRIVER -I../Drivers -I../Drivers/CMSIS -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Src -I../Middlewares -I../Peripherals -I../Interfaces -I../User -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d29c42da/timer.o ../User/timer.c

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
