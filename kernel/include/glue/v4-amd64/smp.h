/*********************************************************************
 *                
 * Copyright (C) 2003,  Karlsruhe University
 *                
 * File path:     glue/v4-amd64/smp.h
 * Description:   
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
 * $Id: smp.h,v 1.3 2006/09/25 13:40:44 stoess Exp $
 *                
 ********************************************************************/
#ifndef __GLUE__V4_AMD64__SMP_H__
#define __GLUE__V4_AMD64__SMP_H__

#ifndef __API__V4__SMP_H__
#error do not include glue/v4-amd64/smp.h directly -- use api/v4/smp.h
#endif

INLINE void sync_entry_t::set_pending(cpuid_t cpu)
{
    __asm__ ("lock; orq %0, %1\n"
	     :
	     : "r"((word_t)1 << cpu), "m"(this->pending_mask));
}
 
INLINE void sync_entry_t::clear_pending(cpuid_t cpu)
{ 
    __asm__ ("lock; andq %0, %1\n"
	     :
	     : "r"(~((word_t)1 << cpu)), "m"(this->pending_mask));
}

INLINE void sync_entry_t::ack(cpuid_t cpu)
{
    ack_mask = 1 << cpu;
}

void init_xcpu_handling();
void smp_xcpu_trigger( cpuid_t cpu );


#endif /* !__GLUE__V4_AMD64__SMP_H__ */
