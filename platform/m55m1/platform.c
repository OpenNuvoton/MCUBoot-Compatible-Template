#include "platform.h"

/* bootloader platform-specific hw initialization */
int32_t platform_init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Enable PLL0 220MHz clock from HIRC and switch SCLK clock source to PLL0 */
    CLK_SetBusClock(CLK_SCLKSEL_SCLKSEL_APLL0, CLK_APLLCTL_APLLSRC_HIRC, FREQ_220MHZ);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

#if 1 // PH, TEST CHIP
    /* Enable External HXT clock */
    CLK_EnableXtalRC(CLK_SRCCTL_HXTEN_Msk);

    /* Waiting for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Select UART6 clock source from HXT */
    CLK_SetModuleClock(UART3_MODULE, CLK_UARTSEL0_UART3SEL_HXT, CLK_UARTDIV0_UART3DIV(1));

    /* Enable UART clock */
    CLK_EnableModuleClock(UART3_MODULE);

    /* Reset UART module */
    SYS_ResetModule(SYS_UART3RST);

    /* Set multi-function pins for UART0 RXD and TXD */
    SET_UART3_RXD_PE0();
    SET_UART3_TXD_PE1();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART3, 115200);
#endif

    return 0;
}