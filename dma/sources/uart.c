///*
// * uart.c
// *
// *  Created on: Apr 10, 2019
// *      Author: amosh
// */
//
///* TODO: insert other include files here. */
//
///* TODO: insert other definitions and declarations here. */
//
///*
// * @brief   Application entry point.
// */
////UART0_Type uart0;
//
//#include "../includes/uart.h"
////#include "../includes/c_buff.h"
//
//
//extern uint8_t data_poll;
//extern int GPIO_flag;
//extern char report_charac[256];
//extern int char_count[256];
//extern int character_entred_flag;
//extern c_buf *buffer; // Creating instance for the structure
////c_buf *buffer; // Creating instance for the structure
//
//
//
//
//
//void interrupt_enable()
//{
//	 // Enable Interrupts for UART0
//	 NVIC_EnableIRQ(UART0_IRQn);
//
//	 UART0->C2 |= UART0_C2_RIE(1);
//	 // UART0->C2 |= UART0_C2_TIE(1);
//	 // UART0->C2 |= UART0_C2_TCIE(1);
//
//
//	 //Enable global interrupts (IRQs)
//     __enable_irq();
//}
//
//void uart_init()
//{
//	// Enabling clock for port A
//	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
//
//	//Enable UART0 clock (D10 bit in SIM_SCSC4 register)
//	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //clock
//
//	// Configuring the PTA2 UART0_Rx pin
//	PORTA->PCR[1] |= PORT_PCR_MUX(0x2);
//
//	// Configuring the PTA2 UART0_Tx pin
//	PORTA->PCR[2] |= PORT_PCR_MUX(0x2);
//
//	// Select FLL clock o/p for UART0 to obtain 41.94 MHz frequency
//	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); //enable uart0 clock
//
////	uint16_t baud_rate_modulo_divisor;
////	baud_rate_modulo_divisor = DEFAULT_SYSTEM_CLOCK/((16)*115200);
//
//	// PRINTF("\n The baud calue is: %d",baud_rate_modulo_divisor);
//	UART0->C2 &= 0x00;
//
//	// Set values in BDH and BDL to set the required baud rate
//	UART0->BDH = 0x00;
//	//UART0->BDL |= UART0_BDL_SBR(++baud_rate_modulo_divisor);
//	UART0->BDL = 0x18;
//	// Disable the UART
//	UART0->C1 &= 0x00;
//
//	// Enable Transmit and recieve for UART0
//	UART0->C2 |= (UART0_C2_TE(1) | UART0_C2_RE(1));
//
//	// Set OSR required to achieve the baud rate
//	//UART0->C4 |= UART0_C4_OSR_MASK;
//	UART0->C4 = 0x0f;
//}
//
////void putch(uint8_t *data)
//void putch(uint8_t *data_poll)
//{
////#ifdef POLLING
//	while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK))
//	{
//
//	}
//	UART0->D = *data_poll;
//}
//
//void getch()
//{
//#ifdef POLLING
//	while(!(UART0->S1 & UART0_S1_RDRF_MASK) )
//	{
//
//	}
//    data_poll = UART0->D;
//#endif
//
//#ifdef INTERRUPTS
//    interrupt_enable();
//#endif
//}
//
////void putstr(char *ch)
////{
////	while(*ch != '\0')
////		putch(*ch++);
////}
//
//void putst(char *string)
//{
//	while(*string != '\0')
//	{
//		while(!(UART0->S1 & UART0_S1_TDRE_MASK) && !(UART0->S1 & UART0_S1_TC_MASK))
//			{
//
//			}
//
//		UART0->D = *string;
//		string++;
//	}
//}
//
////int main(void) {
////
////
////	//putstr('amya');
////  	/* Init board hardware. */
////   BOARD_InitBootPins();
////   BOARD_InitBootClocks();
////    BOARD_InitBootPeripherals();
////  	/* Init FSL debug console. */
////   BOARD_InitDebugConsole();
////
////    PRINTF("Hello World\n");
////
////    uart_init();
////  //  interrupt_enable();
////    /* Force the counter to be placed into memory. */
////   // volatile static int i = 0 ;
////    /* Enter an infinite loop, just incrementing a counter. */
////    while(1) {
//////        i++ ;
////
////#ifdef POLLING
////
////        getch();
////      //  putch( *data);
////        putch(data_poll);
////       // delayMs(2);
////
////#endif
////
////#ifdef INTERRUPTS
////        {
////        	interrupt_enable();
////        }
////#endif
////    }
////    return 0 ;
////}
//
//
//void UART0_IRQHandler()
//{
//	//Disable all interrupts
//	__disable_irq();
//	GPIO_flag = 0;
//
//	/*If the interrupt is RECEIVE interrupt*/
//	if(UART0->S1 & UART0_S1_RDRF_MASK)
//	{
//
//        character_entred_flag=1;
//		uint8_t data = UART0->D;
//
//		add_elements(buffer, data);
//		report_charac[data]++;
//		char_count[data]++;
//		delete_buffer (buffer) ;
////		putch(&data);
//
//	}
//
//	GPIO_flag = 1;
//	/*Enable all interrupts*/
//	__enable_irq();
//}
//
//void GPIO_init()
//{
//	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
////	PORTA->PCR[3] |= PORT_PCR_MUX(0x1);
////	GPIOA->PSOR &= 0x03;
//	PORTB->PCR[18] |= PORT_PCR_MUX(0x1);
//	//GPIOB->PSOR &= 0x40000;
//	GPIOB->PDDR |= 0x40000;
//}
//
//void GPIO_toggle()
//{
//	GPIOB->PSOR |= 0x40000;
//	delayms1(100);
//	GPIOB->PCOR |= 0x40000;
//}
//
//void delayms1(int t)
//{
//	int i,j;
//
//	for(i=0;i<t;i++)
//	{
//		for(j=0;j<10000;j++)
//		{
//
//		}
//	}
//}
