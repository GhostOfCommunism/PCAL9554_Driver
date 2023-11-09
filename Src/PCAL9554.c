
#include "PCAL9554.h"

static void RegRead(PCAL9554_Handle_TypeDef*HandleP, uint8_t RegAddr, uint8_t*DataP)
{
	HandleP->I2C_TxRx(HandleP->I2CAddr, &RegAddr, 1, DataP, 1);
}

static void RegWrite(PCAL9554_Handle_TypeDef*HandleP, uint8_t RegAddr, uint8_t Data)
{
	static uint8_t TempArr[2];
	TempArr[0] = RegAddr;
	TempArr[1] = Data;
	HandleP->I2C_TxRx(HandleP->I2CAddr, TempArr, 2, 0, 0);
}

void PCAL9554_Init(PCAL9554_Handle_TypeDef*HandleP,
		void (*I2C_TxRx)(uint8_t I2C_Addr, uint8_t*TxDataP, uint32_t TxDataAmount, uint8_t*RxDataP,
				uint32_t RxDataAmount), PCAL9554_Version_TypeDef Version, uint8_t A0_Val,
		uint8_t A1_Val, uint8_t A2_Val)
{
	// Functions filling out:
	HandleP->I2C_TxRx = I2C_TxRx;
	// I2C Address filling out:
	if (Version == PCAL9554_Version_B)
		HandleP->I2CAddr = PCAL9554_I2C_ADDR_PREFIX_B;
	else
		HandleP->I2CAddr = PCAL9554_I2C_ADDR_PREFIX_C;
	HandleP->I2CAddr |= (0x01 && A0_Val) || (0x02 && A1_Val) || (0x04 && A2_Val);
	// Data reading:
	PCAL9554_RegsRead(HandleP);
}

void PCAL9554_RegsRead(PCAL9554_Handle_TypeDef*HandleP)
{
	RegRead(HandleP, PCAL9554_REG_ADDR_IN, HandleP->Regs + PCAL9554_REG_NUMB_IN);
	RegRead(HandleP, PCAL9554_REG_ADDR_OUT, HandleP->Regs + PCAL9554_REG_NUMB_OUT);
	RegRead(HandleP, PCAL9554_REG_ADDR_POL_INV, HandleP->Regs + PCAL9554_REG_NUMB_POL_INV);
	RegRead(HandleP, PCAL9554_REG_ADDR_CONF, HandleP->Regs + PCAL9554_REG_NUMB_CONF);
	RegRead(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR0, HandleP->Regs + PCAL9554_REG_NUMB_OUT_DR_STR0);
	RegRead(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR1, HandleP->Regs + PCAL9554_REG_NUMB_OUT_DR_STR1);
	RegRead(HandleP, PCAL9554_REG_ADDR_IN_LATCH, HandleP->Regs + PCAL9554_REG_NUMB_IN_LATCH);
	RegRead(HandleP, PCAL9554_REG_ADDR_PULL_EN, HandleP->Regs + PCAL9554_REG_NUMB_PULL_EN);
	RegRead(HandleP, PCAL9554_REG_ADDR_PULL_SEL, HandleP->Regs + PCAL9554_REG_NUMB_PULL_SEL);
	RegRead(HandleP, PCAL9554_REG_ADDR_INT_MASK, HandleP->Regs + PCAL9554_REG_NUMB_INT_MASK);
	RegRead(HandleP, PCAL9554_REG_ADDR_INT_STAT, HandleP->Regs + PCAL9554_REG_NUMB_INT_STAT);
	RegRead(HandleP, PCAL9554_REG_ADDR_OUT_CONF, HandleP->Regs + PCAL9554_REG_NUMB_OUT_CONF);
}

uint8_t PCAL9554_InputsRead(PCAL9554_Handle_TypeDef*HandleP)
{
	RegRead(HandleP, PCAL9554_REG_ADDR_IN, HandleP->Regs + PCAL9554_REG_NUMB_IN);
	return HandleP->Regs[PCAL9554_REG_NUMB_IN];
}

void PCAL9554_OutputsSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_OUT, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_OUT] = Data;
}

void PCAL9554_PolarsInvSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_POL_INV, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_POL_INV] = Data;
}

void PCAL9554_DirectionsSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_CONF, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_CONF] = Data;
}

void PCAL9554_OutputsCurrentSet(PCAL9554_Handle_TypeDef*HandleP, uint16_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR0, (uint8_t) Data);
	HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR0] = (uint8_t) Data;
	Data = Data >> 8;
	RegWrite(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR1, (uint8_t) Data);
	HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR1] = (uint8_t) Data;
}

void PCAL9554_InputsLatchSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_IN_LATCH, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_IN_LATCH] = Data;
}

void PCAL9554_PullsEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_PULL_EN, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_PULL_EN] = Data;
}

void PCAL9554_PullsSelSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_PULL_SEL, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_PULL_SEL] = Data;
}

void PCAL9554_InterruptsEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data)
{
	RegWrite(HandleP, PCAL9554_REG_ADDR_INT_MASK, Data);
	HandleP->Regs[PCAL9554_REG_NUMB_INT_MASK] = Data;
}

uint8_t PCAL9554_InterruptsStatusRead(PCAL9554_Handle_TypeDef*HandleP)
{
	RegRead(HandleP, PCAL9554_REG_ADDR_INT_STAT, HandleP->Regs + PCAL9554_REG_NUMB_INT_STAT);
	return HandleP->Regs[PCAL9554_REG_NUMB_INT_STAT];
}

void PCAL9554_OutputsTypeSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t PP_or_OD_Flag)
{
	PP_or_OD_Flag = PP_or_OD_Flag ? 0 : 1;
	RegWrite(HandleP, PCAL9554_REG_ADDR_OUT_CONF, PP_or_OD_Flag);
	HandleP->Regs[PCAL9554_REG_NUMB_OUT_CONF] = PP_or_OD_Flag;
}

uint8_t PCAL9554_InputRead(PCAL9554_Handle_TypeDef*HandleP, uint8_t InNumber)
{
	PCAL9554_InputsRead(HandleP);
	return HandleP->Regs[PCAL9554_REG_NUMB_IN] & (1 << InNumber);
}

void PCAL9554_OutputSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber)
{
	OutNumber = 1 << OutNumber;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_OUT] | OutNumber;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_OUT] & (~OutNumber);
	PCAL9554_OutputsSet(HandleP, Data);
}

void PCAL9554_PolarInvSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber)
{
	OutNumber = 1 << OutNumber;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_POL_INV] | OutNumber;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_POL_INV] & ~OutNumber;
	PCAL9554_PolarsInvSet(HandleP, Data);
}

void PCAL9554_DirectionSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t OutNumber)
{
	OutNumber = 1 << OutNumber;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_CONF] | OutNumber;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_CONF] & ~OutNumber;
	PCAL9554_DirectionsSet(HandleP, Data);
}

void PCAL9554_OutputCurrentSet(PCAL9554_Handle_TypeDef*HandleP, PCAL9554_OutCurrent_TypeDef Current,
		uint8_t OutNumber)
{
	OutNumber *= 2;
	if (OutNumber < 6)
	{
		uint8_t Temp = HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR0] & ~(0x03 << OutNumber);
		Temp |= (((uint8_t) Current) & 0x03) << OutNumber;
		RegWrite(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR0, Temp);
		HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR0] = Temp;
	}
	else
	{
		OutNumber -= 8;
		uint8_t Temp = HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR1] & ~(0x03 << OutNumber);
		Temp |= (((uint8_t) Current) & 0x03) << OutNumber;
		RegWrite(HandleP, PCAL9554_REG_ADDR_OUT_DR_STR1, Temp);
		HandleP->Regs[PCAL9554_REG_NUMB_OUT_DR_STR1] = Temp;
	}
}

void PCAL9554_InputLatchSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t InNumber)
{
	InNumber = 1 << InNumber;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_IN_LATCH] | InNumber;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_IN_LATCH] & ~InNumber;
	PCAL9554_InputsLatchSet(HandleP, Data);
}

void PCAL9554_PullEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t IO_Number)
{
	IO_Number = 1 << IO_Number;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_EN] | IO_Number;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_EN] & ~IO_Number;
	PCAL9554_PullsEnableSet(HandleP, Data);
}

void PCAL9554_PullSelSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t IO_Number)
{
	IO_Number = 1 << IO_Number;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_SEL] | IO_Number;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_SEL] & ~IO_Number;
	PCAL9554_PullsSelSet(HandleP, Data);
}

void PCAL9554_InterruptEnableSet(PCAL9554_Handle_TypeDef*HandleP, uint8_t Data, uint8_t InNumber)
{
	InNumber = 1 << InNumber;
	if (Data)
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_SEL] & ~InNumber;
	else
		Data = HandleP->Regs[PCAL9554_REG_NUMB_PULL_SEL] | InNumber;
	PCAL9554_PullsSelSet(HandleP, Data);
}

uint8_t PCAL9554_InterruptStatusRead(PCAL9554_Handle_TypeDef*HandleP, uint8_t InNumber)
{
	PCAL9554_InputsRead(HandleP);
	return HandleP->Regs[PCAL9554_REG_NUMB_INT_STAT] & (1 << InNumber);
}

