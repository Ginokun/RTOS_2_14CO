/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/05/03
 * Version: v1.3
 *===========================================================================*/

/*==================[inclusiones]============================================*/
#include "object.h"
#include "main.h"
/*==================[definiciones de datos internos]=========================*/
extern tObjeto obj_1;
extern tObjeto obj_2;
/*==================[definiciones de datos externos]=========================*/

/*==================[funcion principal]======================================*/

void imprimir ( tMensaje mensaje )
{
	uartWriteString(USED_UART, mensaje);
	uartWriteString( USED_UART , "\r\n" );
}

bool_t objeto_crear(tObjeto* objeto)
{
	objeto->cola = xQueueCreate(N_QUEUE,sizeof(tMensaje));

	configASSERT( objeto->cola != NULL);

	return TRUE
}

void post(tObjeto* objeto,tMensaje mensaje)
{
	xQueueSend(objeto->cola, &mensaje, portMAX_DELAY );
}

void post_to_c(tMensaje mensaje)
{
	post(&obj_1,mensaje);
}

void post_to_d(tMensaje mensaje)
{
	post(&obj_2,mensaje);
}

void get(tObjeto* objeto,tMensaje* mensaje)
{
	xQueueReceive(objeto->cola, mensaje,  portMAX_DELAY ); 
}

void get_to_c(tObjeto* objeto,tMensaje* mensaje)
{
	get(&obj_1, mensaje); 
}

void get_to_d(tObjeto* objeto,tMensaje* mensaje)
{
	get(&obj_2, mensaje); 
}