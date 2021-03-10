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

SemaphoreHandle_t bouton_semph;


void vTaskInversionLED(){
    const TickType_t macro = pdMS_TO_TICKS(500);
    for(;;){
      
vTaskDelay(macro);
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 0UL);
vTaskDelay(macro);
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 1UL);

/*uint32_t valeur = Cy_GPIO_Read(P1_1_PORT, P1_1_NUM)^1;
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, valeur);

if(Cy_GPIO_Read(P1_1_PORT, P1_1_NUM)==0UL){
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 1UL);
}
else{
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 0UL);
*/
}
}

/*void isr_bouton(void){
    xSemaphoreGiveFromISR(bouton_semph, NULL);
    Cy_GPIO_ClearInterrupt(Bouton_0_PORT, BOUTON_0_NUM);
 */   

    



int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//vTaskInversionLED();
TaskHandle_t xHandle = NULL;
xTaskCreate(vTaskInversionLED,"Inversion",80, NULL, 3,xHandle);
vTaskStartScheduler();
    

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
