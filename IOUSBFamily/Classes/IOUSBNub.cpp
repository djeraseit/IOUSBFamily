/*
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
 * Please see the License for the specific language governing rights and 
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#include <libkern/OSByteOrder.h>

#include <libkern/c++/OSDictionary.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <libkern/c++/OSData.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/IOUSBController.h>
#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBPipe.h>

//#include "IOUSBUserClient.h"

#define DEBUGGING_LEVEL 0

#if DEBUGGING_LEVEL > 0
#define USBExpertStatusLevel(a, b, c, d) if (IOUSBController::_log) IOUSBController::_log->AddStatusLevel((UInt32)a, (UInt32)b, (char*)c, (UInt32)d)
#else
#define USBExpertStatusLevel(a, b, c, d)
#endif

#define super	IOService

#if 0
static const 
IOUSBDescriptorHeader *NextDescriptor(const void *desc)
{
    const UInt8 *next = (const UInt8 *)desc;
    UInt8 length = next[0];
    next = &next[length];
    return((const IOUSBDescriptorHeader *)next);
}



const IOUSBDescriptorHeader*
IOUSBNub::FindNextDescriptor(const void *cur, UInt8 descType)
{
    const IOUSBDescriptorHeader *hdr;
    hdr = (const IOUSBDescriptorHeader *)cur;
    do {
	hdr = NextDescriptor(hdr);
        if(hdr->length == 0)
            break;
        if(descType == 0)
            return hdr;	// type 0 is wildcard.
        else if(hdr->descriptorType == descType)
            return hdr;
    }
    while(true);

    return NULL;	// Fell off end of list
}
#endif
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OSDefineMetaClass( IOUSBNub, IOService )
OSDefineAbstractStructors(IOUSBNub, IOService)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 ** Matching methods
 **/

bool 
IOUSBNub::USBCompareProperty( OSDictionary   * matching, const char     * key )
{
    // We return success iff we match the key in the dictionary with the key in
    // the property table.
    //
    OSObject 	* value;
    bool		matches;

    value = matching->getObject( key );

    if( value)
        matches = value->isEqualTo( getProperty( key ));
    else
        matches = false;

    return matches;
}
