/*********************************************************************
 *                
 * Copyright (C) 2003,  Karlsruhe University
 *                
 * File path:     l4test/alpha/help.cc
 * Description:   Helper functions for Alpha
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: help.cc,v 1.3 2003/10/20 06:00:21 sjw Exp $
 *                
 ********************************************************************/
/* architecture specific 'helper' functions */

#include <l4/types.h>
#include <l4io.h>
#include <arch.h>

#include "../l4test.h"
#include "../assert.h"

/*
 * Startup stub for setting up the appropriate GP and IP values.
 */
extern L4_Word_t _startup_stub;

/* setup an exreg 
 *
 * *sp == NULL: allocate a new stack
 * *sp != NULL: top of sp from an old exreg used, just refresh it!
 */
void 
setup_exreg( L4_Word_t *ip, L4_Word_t *sp, void (*func)(void) )
{
	L4_Word_t *stack, *hack_ip;
	int max;

	/* get the function address */
	hack_ip = (L4_Word_t*) func;

	/* work out the size in items */
	max = STACK_PAGES * PAGE_SIZE / sizeof( L4_Word_t );
	if( *sp == 0 )
	{
		stack = (L4_Word_t*) get_pages( STACK_PAGES, 1 );
		assert( stack != NULL );

		stack = &stack[max-1];
	}
	else
		stack = (L4_Word_t*) *sp;

	/* work out the size */
	stack[-1] = *hack_ip;      /* get the entry pt out */


	*ip = (L4_Word_t) &_startup_stub;
	*sp = (L4_Word_t) stack;
}

/* get the 1st word out of the function descriptor (stinkin gp!) */
void *
code_addr( void *addr )
{
    return addr;
}

void
get_startup_values (void (*func)(void), L4_Word_t * ip, L4_Word_t * sp)
{
    // Calculate intial SP and BSP values
    L4_Word_t *stack = (L4_Word_t *) get_pages (STACK_PAGES, 1);
    stack += STACK_PAGES * PAGE_SIZE;

    // Push IP onto stack
    *--stack = (L4_Word_t) func;

    *ip = (L4_Word_t) &_startup_stub;
    *sp = (L4_Word_t) stack;
}
