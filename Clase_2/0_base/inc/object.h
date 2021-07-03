/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/05/03
 * Version: v1.3
 *===========================================================================*/

#ifndef MAIN_H_
#define MAIN_H_

/*==================[inclusiones]============================================*/
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"
#include "queue.h"
#include "semphr.h"
#include "FreeRTOSConfig.h"
/*==================[definiciones y macros]==================================*/

typedef struct
{
    QueueHandle_t cola;
} tObjeto;

void objeto_crear(tObjeto* objeto);
void post(tObjeto* objeto,tMensaje mensaje);
void get(tObjeto* objeto,tMensaje mensaje);

#endif /* MAIN_H_ */
