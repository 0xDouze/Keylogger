/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_USBDriver1,
    0xa5d22b57,0x4415,0x452d,0x86,0x4e,0x85,0x45,0xf7,0xac,0xa6,0x06);
// {a5d22b57-4415-452d-864e-8545f7aca606}
