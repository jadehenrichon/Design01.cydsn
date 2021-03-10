/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "params.h"
#include "queue.h"


void vTaskInversionLED(){
    for(;;){

if(Cy_GPIO_Read(P1_1_PORT, P1_1_NUM)==0UL){
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 1UL);
}
else {
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 0UL);
}
vTaskDelay(pdMS_TO_TICKS(500));
}
}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
TaskHandle_t xHandle = NULL;
xTaskCreate(vTaskInversionLED,"Inversion",80, NULL, 3,xHandle);
vTaskStartScheduler();
    

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
