/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file	ee_k1_mppa_trace.h
 *  \brief	TO BE DOCUMENTED!!!
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Errico Guidieri
 *  \date	2016
 */

#undef MPPA_TRACEPOINT_PROVIDER
#define MPPA_TRACEPOINT_PROVIDER erika
#undef MPPA_TRACEPOINT_FILE
#define MPPA_TRACEPOINT_FILE ee_k1_mppa_trace.h

#if !defined(EE_K1_MPPA_TRACE_H_) || defined(MPPA_TRACEPOINT_HEADER_MULTI_READ)
#define EE_K1_MPPA_TRACE_H_

#include <mppa_trace.h>
MPPA_DECLARE_TRACEPOINT(erika,ISR_HANDLER_ENTER,(
	MPPA_TRACEPOINT_DEC_FIELD(int,vector))
)

MPPA_DECLARE_TRACEPOINT(erika,ISR_HANDLER_EXIT,(
	MPPA_TRACEPOINT_DEC_FIELD(int,vector))
)

MPPA_DECLARE_TRACEPOINT(erika,ACTIVATE_TASK_ENTER,(
	MPPA_TRACEPOINT_DEC_FIELD(int,task_id))
)

MPPA_DECLARE_TRACEPOINT(erika,ACTIVATE_TASK_EXIT,(
	MPPA_TRACEPOINT_DEC_FIELD(int,task_id))
)

MPPA_DECLARE_TRACEPOINT(erika,TERMINATE_TASK_ENTER,(
	MPPA_TRACEPOINT_DEC_FIELD(int,task_id))
)

MPPA_DECLARE_TRACEPOINT(erika,TERMINATE_TASK_EXIT,(
	MPPA_TRACEPOINT_DEC_FIELD(int,task_id))
)

MPPA_DECLARE_TRACEPOINT(erika,CONTEXT_SWITCH_ENTER,())
MPPA_DECLARE_TRACEPOINT(erika,CONTEXT_SWITCH_EXIT,())

MPPA_TRACEPOINT_LOGLEVEL(erika,ISR_HANDLER_ENTER,MPPA_TRACE_DEBUG)
MPPA_TRACEPOINT_LOGLEVEL(erika,ISR_HANDLER_EXIT,MPPA_TRACE_DEBUG)
MPPA_TRACEPOINT_LOGLEVEL(erika,ACTIVATE_TASK_ENTER,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,ACTIVATE_TASK_EXIT,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,TERMINATE_TASK_ENTER,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,TERMINATE_TASK_EXIT,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,CONTEXT_SWITCH_ENTER,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,CONTEXT_SWITCH_EXIT,MPPA_TRACE_DEBUG_PROCESS)
#ifdef EE_USER_TRACEPOINT
#include EE_USER_TRACEPOINT
#endif

#if 0
/*
MPPA_DECLARE_TRACEPOINT(erika,ISR_PROFILING,(
	MPPA_TRACEPOINT_DEC_FIELD(int,conf),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm0),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm1),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm2),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm3))
)*/

/*MPPA_DECLARE_TRACEPOINT(erika,CONTEXT_SWITCH,(
	MPPA_TRACEPOINT_DEC_FIELD(int,prev_id),
	MPPA_TRACEPOINT_HEX_FIELD(int,prev_state),
	MPPA_TRACEPOINT_DEC_FIELD(int,prev_prio),
	MPPA_TRACEPOINT_DEC_FIELD(int,next_id),
	MPPA_TRACEPOINT_HEX_FIELD(int,next_state),
	MPPA_TRACEPOINT_DEC_FIELD(int,next_prio))
)*/

MPPA_DECLARE_TRACEPOINT(erika,START_THREAD,(
	MPPA_TRACEPOINT_DEC_FIELD(int,id),
	MPPA_TRACEPOINT_HEX_FIELD(int,name_u32),
	MPPA_TRACEPOINT_STRING_FIELD(char *,namestr),
	MPPA_TRACEPOINT_HEX_FIELD(int,entry),
	MPPA_TRACEPOINT_HEX_FIELD(int,state),
	MPPA_TRACEPOINT_DEC_FIELD(int,prio))
)

MPPA_DECLARE_TRACEPOINT(erika,TERMINATE_THREAD,(
	MPPA_TRACEPOINT_DEC_FIELD(int,id))
)

MPPA_DECLARE_TRACEPOINT(erika,THREAD_PROFILING,(
	MPPA_TRACEPOINT_DEC_FIELD(int,conf),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm0),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm1),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm2),
	MPPA_TRACEPOINT_DEC_FIELD(int,pm3))
)

MPPA_DECLARE_TRACEPOINT(erika,SET_OBJNAME,(
	MPPA_TRACEPOINT_DEC_FIELD(int,id),
	MPPA_TRACEPOINT_STRING_FIELD(char *,namestr))
)


MPPA_DECLARE_TRACEPOINT(erika,PRINTF,(
	MPPA_TRACEPOINT_STRING_FIELD(char *,str),
	MPPA_TRACEPOINT_DEC_FIELD(int,len))
)

MPPA_DECLARE_TRACEPOINT(nodeos, SYSCALL_ENTER,(
	MPPA_TRACEPOINT_DEC_FIELD(int, number),
	MPPA_TRACEPOINT_DEC_FIELD(int, notify),
	MPPA_TRACEPOINT_DEC_FIELD(int, id))
)

MPPA_DECLARE_TRACEPOINT(nodeos,SYSCALL_EXIT,(
	MPPA_TRACEPOINT_DEC_FIELD(int,number),
	MPPA_TRACEPOINT_DEC_FIELD(int,ret),
	MPPA_TRACEPOINT_DEC_FIELD(int,err_no),
	MPPA_TRACEPOINT_DEC_FIELD(int,id))
)

MPPA_DECLARE_TRACEPOINT(erika, THREAD_KILL,(
	MPPA_TRACEPOINT_DEC_FIELD(int,id),
	MPPA_TRACEPOINT_DEC_FIELD(int,signo))
)

MPPA_DECLARE_TRACEPOINT(erika, THREAD_SIG_RECEIVE,(
	MPPA_TRACEPOINT_DEC_FIELD(int,id),
	MPPA_TRACEPOINT_HEX_FIELD(int,sigmask))
)


/*
MPPA_TRACEPOINT_LOGLEVEL(erika,ISR_HANDLER__in,MPPA_TRACE_DEBUG)
MPPA_TRACEPOINT_LOGLEVEL(erika,ISR_HANDLER__out,MPPA_TRACE_DEBUG)
MPPA_TRACEPOINT_LOGLEVEL(erika,ISR_PROFILING,MPPA_TRACE_DEBUG)*/

//MPPA_TRACEPOINT_LOGLEVEL(erika,CONTEXT_SWITCH,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,START_THREAD,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,TERMINATE_THREAD,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,THREAD_PROFILING,MPPA_TRACE_DEBUG_PROCESS)
MPPA_TRACEPOINT_LOGLEVEL(erika,SET_OBJNAME,MPPA_TRACE_DEBUG_PROCESS)

MPPA_TRACEPOINT_LOGLEVEL(erika,PRINTF,MPPA_TRACE_INFO)

MPPA_TRACEPOINT_LOGLEVEL(erika,SYSCALL_ENTER,MPPA_TRACE_DEBUG_SYSTEM)
MPPA_TRACEPOINT_LOGLEVEL(erika,SYSCALL_EXIT,MPPA_TRACE_DEBUG_SYSTEM)

#endif /* 0 */

#endif /* !EE_K1_MPPA_TRACE_H_ || MPPA_TRACEPOINT_HEADER_MULTI_READ */

