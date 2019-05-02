
#include "../includes/dma.h"


bool buff_check_flag = false;
bool dma_interrupt_flag;
uint16_t data_buff[256];
uint32_t double_buff1 = 0;
uint32_t double_buff_temp =0;
uint32_t double_buff2 =128;



void dma_init()
{

	// DMA MUX clock gate enable
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// DMA clock gate control enable
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;

	// DMA MUX Disable
	DMAMUX0->CHCFG[0] = 0x00;

	// Assigning the source address as ADC0 register address
	DMA0->DMA[0].SAR = &ADC0->R[0];

	// Assigning the destination address as buffer address
    DMA0->DMA[0].DAR=&data_buff[double_buff1];

	// No of bytes to be transferred is 128, it decrements in the steps of 2
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(128*2);

	// Enable DMA Interrupt once 128 bytes are transferred from ADC data register to double buffer
	DMA0->DMA[0].DCR |= DMA_DCR_EINT_MASK;

	// Enable peripheral request and initiate the transfer
	DMA0->DMA[0].DCR |= DMA_DCR_ERQ_MASK;

	// Forces a single read/write transfer per request.
	DMA0->DMA[0].DCR |= DMA_DCR_CS_MASK;

	// data size of source bus cycle is set as 16 bit
	DMA0->DMA[0].DCR |= DMA_DCR_SSIZE(2);

	// increment destination
	DMA0->DMA[0].DCR |= DMA_DCR_DINC_MASK;	//increment destination

	// data size of destination bus cycle is set as 16 bit
	DMA0->DMA[0].DCR |= DMA_DCR_DSIZE(2);

	// Enable the DMA channel and slect DMA source
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL(1) | DMAMUX_CHCFG_SOURCE(40);

//	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
//	PORTB->PCR[18] |= PORT_PCR_MUX(0x1);
//	GPIOB->PDDR |= 0x40000;

	__enable_irq();
	NVIC_EnableIRQ(DMA0_IRQn);

	// begin the DMA transfer
	DMA0->DMA[0].DCR |= DMA_DCR_START_MASK;
}




void DMA0_IRQHandler(void)
{
	// disable the interrupts
	__disable_irq();

	// check if the first 128 bytes are transferred by the DMA
	if(DMA_DSR_BCR_DONE_MASK)
	{
		// Set a flag corresponding to the IRQ
		dma_interrupt_flag =true;

		// Clear Done Flag
		DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

		if(buff_check_flag 	==	 0)
		{
			buff_check_flag = 1;

			DMA0->DMA[0].SAR =&ADC0->R[0];
			DMA0->DMA[0].DAR = &data_buff[double_buff2];
			DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(256);
			DMA0->DMA[0].DCR |= DMA_DCR_START_MASK;


		}

		else if(buff_check_flag == 1)
		{
			buff_check_flag = 0;

			DMA0->DMA[0].SAR =&ADC0->R[0];
			DMA0->DMA[0].DAR = &data_buff[double_buff1];
			DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(256);
			DMA0->DMA[0].DCR |= DMA_DCR_START_MASK;

		}

	}

	// enable the interrupts
	__enable_irq();
}


