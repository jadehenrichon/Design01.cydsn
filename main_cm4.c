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
#include "stdio.h"
#include "stdlib.h"

SemaphoreHandle_t bouton_semph;
QueueHandle_t print_queue;
_Bool etat_bouton;
char buffer_appuye[50];
char buffer_relache[50];
task_params_t task_A = {
    .delay = 1000,
    .message = "Tache A en cours\n\r"
};

task_params_t task_B = {
    .delay = 999,
    .message = "Tache B en cours\n\r"
};
    


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
    etat_bouton =  !etat_bouton;
}
    
void bouton_task(){
    for(;;){
        if( xSemaphoreTake(bouton_semph,pdMS_TO_TICKS(20)) == pdTRUE )
        {
            if(etat_bouton){
                UART_1_PutString(buffer_relache);
                UART_1_PutString("\n\r");
            }
            else {
                UART_1_PutString(buffer_appuye);
                UART_1_PutString("\n\r");
            }
        }
       } 
    }

 void print_loop(void * params){
        for(;;){
   task_params_t* tache = (task_params_t*) params;
      UART_1_PutString(tache->message);
      vTaskDelay(pdMS_TO_TICKS(tache->delay));
    
    
   } 
}

/*
  void print() {
    char * message;
    for (;;){
        if(xQueueReceive(print_queue, &message, portMAX_DELAY)== pdTRUE){
            UART_1_PutString("Queue received");
            UART_1_PutString(message);
        }
        else{
            UART_1_PutString("Queue not received");
        }
    }
}

void print_loop(void * params){
    for(;;){
        task_params_t* tache = (task_params_t*) params;
        if(xQueueSend(print_queue,(char*) (tache->message),( TickType_t ) 10)==pdTRUE){
            UART_1_PutString("New Item in Queue\r\n");
        }
        //xQueueSend(print_queue, &params , 0);
        vTaskDelay(pdMS_TO_TICKS(tache->delay));
    }
}
*/


int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
     
    
    UART_1_Start();
    etat_bouton = true;
    bouton_semph = xSemaphoreCreateBinary();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
// Code partie 1
TaskHandle_t xHandle = NULL;
xTaskCreate(vTaskInversionLED,"Inversion",80, NULL, 3,xHandle);

    

// Code partie 2

 sprintf(buffer_relache,"Le bouton est relache");
 sprintf(buffer_appuye,"Le bouton est appuye");
    
 NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
 Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
 NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
 xTaskCreate(bouton_task, "Bouton", 80, NULL, 2, xHandle);

 
 // Code partie 3a) et 3b)
// print_queue = xQueueCreate(2, sizeof(char*));  
 xTaskCreate(print_loop,"task A",configMINIMAL_STACK_SIZE,(void *) &task_A,1,NULL);
 xTaskCreate(print_loop,"task B",configMINIMAL_STACK_SIZE,(void *) &task_B,1,NULL);
 //xTaskCreate(print,"print",80, NULL, 1, NULL);




vTaskStartScheduler();
    for(;;)
    {
        /* Place your application code here. */

    }
}

/* [] END OF FILE */
