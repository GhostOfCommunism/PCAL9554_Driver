
#include <stdio.h>
#include <stdint.h>

#ifndef PCAL9554_INC_PCAL9554_H_
#define PCAL9554_INC_PCAL9554_H_

#define PCAL9554_I2C_ADDR_PREFIX_B				0x20
#define PCAL9554_I2C_ADDR_PREFIX_C				0x38

#define PCAL9554_REGS_AMOUNT					12

#define PCAL9554_REG_ADDR_IN					0x00
#define PCAL9554_REG_ADDR_OUT					0x01
#define PCAL9554_REG_ADDR_POL_INV				0x02
#define PCAL9554_REG_ADDR_CONF					0x03
#define PCAL9554_REG_ADDR_OUT_DR_STR0			0x40
#define PCAL9554_REG_ADDR_OUT_DR_STR1			0x41
#define PCAL9554_REG_ADDR_IN_LATCH				0x42
#define PCAL9554_REG_ADDR_PULL_EN				0x43
#define PCAL9554_REG_ADDR_PULL_SEL				0x44
#define PCAL9554_REG_ADDR_INT_MASK				0x45
#define PCAL9554_REG_ADDR_INT_STAT				0x46
#define PCAL9554_REG_ADDR_OUT_CONF				0x4F

#define PCAL9554_REG_NUMB_IN					0
#define PCAL9554_REG_NUMB_OUT					1
#define PCAL9554_REG_NUMB_POL_INV				2
#define PCAL9554_REG_NUMB_CONF					3
#define PCAL9554_REG_NUMB_OUT_DR_STR0			4
#define PCAL9554_REG_NUMB_OUT_DR_STR1			5
#define PCAL9554_REG_NUMB_IN_LATCH				6
#define PCAL9554_REG_NUMB_PULL_EN				7
#define PCAL9554_REG_NUMB_PULL_SEL				8
#define PCAL9554_REG_NUMB_INT_MASK				9
#define PCAL9554_REG_NUMB_INT_STAT				10
#define PCAL9554_REG_NUMB_OUT_CONF				11

typedef enum
{
	PCAL9554_Version_B = 0,
	PCAL9554_Version_C
} PCAL9554_Version_TypeDef;

typedef enum
{
	PCAL9554_IOType_In = 0,
	PCAL9554_IOType_Out_PP,
	PCAL9554_IOType_OD,
} PCAL9554_IOType_TypeDef;

typedef enum
{
	PCAL9554_OutCurrent_0 = 0,
	PCAL9554_OutCurrent_1,
	PCAL9554_OutCurrent_2,
	PCAL9554_OutCurrent_3,
} PCAL9554_OutCurrent_TypeDef;

typedef struct PCAL_Struct
{
	uint8_t Regs[PCAL9554_REGS_AMOUNT];	// Device registers
	uint8_t I2CAddr;
	uint8_t InitedFlag;
	// Functions:
	void (*I2C_TxRx)(uint8_t I2C_Addr, uint8_t*TxDataP, uint32_t TxDataAmount, uint8_t*RxDataP,
			uint32_t RxDataAmount);
} PCAL9554_Handle_TypeDef;

void PCAL9554_Init(PCAL9554_Handle_TypeDef*HandleP,
		void (*I2C_TxRx)(uint8_t I2C_Addr, uint8_t*TxDataP, uint32_t TxDataAmount, uint8_t*RxDataP,
				uint32_t RxDataAmount), PCAL9554_Version_TypeDef Version, uint8_t A0_Val,
		uint8_t A1_Val, uint8_t A2_Val);

void PCAL9554_RegsRead(PCAL9554_Handle_TypeDef*HandleP);

uint8_t PCAL9554_InputsRead(PCAL9554_Handle_TypeDef*HandleP);
void PCAL9554_OutputsSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_PolarsInvSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_DirectionsSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_OutputsCurrentSet(PCAL9554_Handle_TypeDef*HandleP, uint16_t Data);
void PCAL9554_InputsLatchSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_PullsEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_PullsSelSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
void PCAL9554_InterruptsEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data);
uint8_t PCAL9554_InterruptsStatusRead(PCAL9554_Handle_TypeDef*HandleP);
void PCAL9554_OutputsTypeSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t PP_or_OD_Flag);

uint8_t PCAL9554_InputRead(PCAL9554_Handle_TypeDef*HandleP, uint8_t InNumber);
void PCAL9554_OutputSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber);
void PCAL9554_PolarInvSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber);
void PCAL9554_DirectionSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber);
void PCAL9554_OutputCurrentSet(PCAL9554_Handle_TypeDef*HandleP, PCAL9554_OutCurrent_TypeDef Current,
		uint8_t OutNumber);
void PCAL9554_InputLatchSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t InNumber);
void PCAL9554_PullEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber);
void PCAL9554_PullSelSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber);
void PCAL9554_InterruptEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t InNumber);
uint8_t PCAL9554_InterruptStatusRead(PCAL9554_Handle_TypeDef*HandleP, uint8_t InNumber);

#endif /* PCAL9554_INC_PCAL9554_H_ */
