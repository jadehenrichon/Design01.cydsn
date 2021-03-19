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
int *etat_bouton;
char buffer_appuye[50];
char buffer_relache[50];
  
    


void vTaskInversionLED(){
    const TickType_t macro = pdMS_TO_TICKS(500);
    for(;;){
      
vTaskDelay(macro);
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 0UL);
vTaskDelay(macro);
Cy_GPIO_Write(P1_1_PORT, P1_1_NUM, 1UL);

}
}

void isr_bouton(void){
    xSemaphoreGiveFromISR(bouton_semph, NULL);
    Cy_GPIO_ClearInterrupt(Bouton_0_PORT, Bouton_0_NUM);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);  
    *etat_bouton =  ~*etat_bouton;
}
    
void bouton_task(){
    for(;;){
        if( xSemaphoreTake(bouton_semph,pdMS_TO_TICKS(20)) == pdTRUE )
        {
            if(*etat_bouton){
                UART_1_PutString(buffer_relache);
                UART_1_PutString("\r");
            }
            else {
                UART_1_PutString(buffer_appuye);
                UART_1_PutString("\r");
            }
        }
        
    }

        
        
        
    }


int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    *etat_bouton = true;
    sprintf(buffer_relache,"Le bouton est relache");
    sprintf(buffer_appuye,"Le bouton est appuye");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//vTaskInversionLED();
    
// Code partie 1
//TaskHandle_t xHandle = NULL;
//xTaskCreate(vTaskInversionLED,"Inversion",80, NULL, 3,xHandle);
//vTaskStartScheduler();
    

// Code partie 2
 bouton_semph = xSemaphoreCreateBinary();
 Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
 NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
 NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);

    


UART_1_Start();


    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
