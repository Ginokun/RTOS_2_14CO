/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/05/03
 * Version: v1.3
 *===========================================================================*/

/*==================[inclusiones]============================================*/
#include "main.h"
#include "keys.h"
#include "user_tasks.h"
/*==================[definiciones de datos internos]=========================*/
const gpioMap_t leds_t[] = {LED2,LED3};
const gpioMap_t gpio_t[] = {GPIO3,GPIO1};
/*==================[definiciones de datos externos]=========================*/
tObjeto obj_1,obj_2;
/*==================[definiciones de funciones internas]=====================*/
void gpio_init(void)
{
    gpioInit( GPIO7, GPIO_OUTPUT );
    gpioInit( GPIO5, GPIO_OUTPUT );
    gpioInit( GPIO3, GPIO_OUTPUT );
    gpioInit( GPIO1, GPIO_OUTPUT );
}
/*==================[definiciones de funciones externas]=====================*/

// Implementacion de funcion de la tarea

void tarea_A( void* taskParmPtr )
{
    // ---------- CONFIGURACIONES ------------------------------
	TickType_t xPeriodicity =  MAX_RATE;
	TickType_t xLastWakeTime = xTaskGetTickCount();
    // ---------- REPETIR POR SIEMPRE --------------------------

	tMensaje mensaje;

	while( TRUE )
	{
		gpioWrite( LEDB , ON );
		vTaskDelay( MAX_RATE / 2 );

		//mensaje = pvPortMalloc(sizeof(MSG_LED));
		mensaje = ( tMensaje ) QMPool_get(&Pool_memoria, 0);
		
		if ( mensaje != NULL)
		{
			memcpy( mensaje, MSG_LED, sizeof(MSG_LED) );
			//xQueueSend(cola_1, &mensaje ,portMAX_DELAY);}
			//post(obj_1,mensaje);
			post_to_c(mensaje);
		}
		else
		{
			printf(MALLOC_ERROR);
		}
		
		gpioWrite( LEDB , OFF );

		vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
	}
}

void tarea_C( void* taskParmPtr )
{
    // ---------- CONFIGURACIONES ------------------------------
	TickType_t xPeriodicity =  PRINT_RATE;
	TickType_t xLastWakeTime = xTaskGetTickCount();
    // ---------- REPETIR POR SIEMPRE --------------------------

	tMensaje mensaje;

	while( TRUE )
	{
		//xQueueReceive( cola_1 , &mensaje , portMAX_DELAY );
		//get(obj_1,&mensaje);
		get_to_c(&mensaje);

		imprimir(mensaje);
		//uartWriteString( USED_UART , mensaje );
		//uartWriteString( USED_UART , "\r\n" );

		//post(obj_2,mensaje);
		post_to_d(mensaje);
		vTaskDelay( PRINT_RATE );
	}
}



void tarea_D( void* taskParmPtr )
{
    // ---------- CONFIGURACIONES ------------------------------
	TickType_t xPeriodicity =  MAX_RATE;
	TickType_t xLastWakeTime = xTaskGetTickCount();
    // ---------- REPETIR POR SIEMPRE --------------------------

	tMensaje mensaje;

	while( TRUE )
	{
		//get(obj_2,&mensaje);
		get_to_d(&mensaje);

		//vPortFree(mensaje);
		// Devuelvo el bloque de memoria que ya fue usado
		QMPool_put(&Pool_memoria, mensaje );
		
		tMensaje = NULL;

		vTaskDelay( xPeriodicity / 20 );
	}
}
/*==================[fin del archivo]========================================*/
