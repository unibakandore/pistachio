/*********************************************************************
 *                
 * Copyright (C) 2006,  Karlsruhe University
 *                
 * File path:     glue/v4-mips32/resources.h
 * Description:   MIPS32 thread resources
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
 * $Id: resources.h,v 1.1 2006/02/23 21:07:40 ud3 Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_MIPS32__RESOURCES_H__
#define __GLUE__V4_MIPS32__RESOURCES_H__

#include INC_GLUE(context.h)

#define HAVE_RESOURCE_TYPE_E

enum resource_type_e {
    COPY_AREA	= 1,
    EXCEPTION	= 2
};

class thread_resources_t  {

public:

    void dump( tcb_t* tcb );
    void save( tcb_t* tcb );
    void load( tcb_t* tcb );
    void purge( tcb_t* tcb );
    void init( tcb_t* tcb );
    void free( tcb_t* tcb );

    void enable_copy_area( tcb_t* tcb, addr_t* saddr, tcb_t* partner, addr_t* daddr );
    void release_copy_area( tcb_t* tcb );
    addr_t copy_area_real_address( addr_t addr );

private:	
 
    word_t copy_area;
};

#endif /* !__GLUE__V4_MIPS32__RESOURCES_H__ */
