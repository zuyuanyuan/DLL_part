/*HEAD nxcocadapp_gui_impl HXX COMX_COMPONENT_MODULE */

/*==============================================================================

                    Copyright 2006 Jilin Kingmesh Corp.
                           All rights reserved

================================================================================ 
File description:

    -- Please append file description informations here --

================================================================================
Date            Name            Description of Change

$HISTORY$
================================================================================
*/

#ifndef _KMAS_COMX_NXCOCADAPP_GUI_IMPL_H_2009102022354
#define _KMAS_COMX_NXCOCADAPP_GUI_IMPL_H_2009102022354

#define SAMPLE_TOOLBAR_ID "0xaf8f110b-0x6c75-0x4706-0x99-0x9f-0xe7-0x4e-0x47-0x72-0xfd-0x79"

using namespace KMAS::Die_maker::comx;

template<typename TOwner>
class TNxcocadappGuiImpl
{
protected:
    TNxcocadappGuiImpl(){}
    ~TNxcocadappGuiImpl(){}
protected:
    bool impl_OnDispatch(const char* tbid, const int index);

/*- Other Declarations Begin -*/

// Append your codes here.

/*- Other Declaration End -*/
};

//////////////////////////////////////////////////////////////////////////
// IUiToolbarParser Implementation

template<typename TOwner>
bool TNxcocadappGuiImpl<TOwner>::impl_OnDispatch(const char* tbid, const int index)
{
    TOwner *pOwner = static_cast<TOwner*>(this);
    bool ret = false;

    /*- impl_OnDispatch Begin -*/

    // Append your codes here.

	if(strcmp(tbid, SAMPLE_TOOLBAR_ID) == 0)
	{
		//Append your codes here.
		
		ret = true;
	}

    /*- impl_OnDispatch End -*/

    return ret;
}

/*- Other Implementation Begin -*/

// Append your codes here.

/*- Other Implementation End -*/

#endif
