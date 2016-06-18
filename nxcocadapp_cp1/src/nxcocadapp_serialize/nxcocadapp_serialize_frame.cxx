/*HEAD nxcocadapp_serialize CXX COMX_COMPONENT_MODULE */

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

#include "nxcocadapp_serialize.hxx"

#include <base\service.hxx>
#include <base\factory.hxx>

#include <acis\acis_core.hxx>
#include <acis\acis_serialize.hxx>

#include <fem\fem_base.hxx>
using namespace fem;;

#include <base/util.hxx>
using namespace KMAS::util;

#include <ui\plugin_common_toolbar.hxx>

#include "nxcocadapp_serialize_impl.hxx"

using namespace KMAS::Die_maker::comx;

class TNxcocadappSerializeComponent : public IPluginCommonToolbarFileEvent,
                                    public IService,
                                    public TFactory,
                                    public TNxcocadappSerializeImpl<TNxcocadappSerializeComponent>
{
    friend class TNxcocadappSerializeImpl<TNxcocadappSerializeComponent>;
public:
    TNxcocadappSerializeComponent() : 
        INITIALIZE_REF_COUNT()
    {
        /*Do nothing*/
    }
    ~TNxcocadappSerializeComponent()
    {
        /*Do nothing*/
    }
public:
    BEGIN_IMPLEMENT_ROOT()
        IMPLEMENT_INTERFACE(IPluginCommonToolbarFileEvent)
        IMPLEMENT_INTERFACE_ROOT(IPluginCommonToolbarFileEvent)
        IMPLEMENT_INTERFACE(IService)
    END_IMPLEMENT_ROOT()
public:
    virtual TStatus STDCALL OnOpen();
    virtual TStatus STDCALL OnSave();
    virtual TStatus STDCALL OnPrint();
public:
    virtual TStatus STDCALL InitializeService();
    virtual TStatus STDCALL TerminalService();
public:
    DECLARE_CREATE_INSTANCE_SINGLETON(TNxcocadappSerializeComponent)

/*- Other Declarations Begin -*/

// Append your codes here.

TConnectManager cmgr;

/*- Other Declaration End -*/
};

BEGIN_IMPLEMENT_CREATE_INSTANCE_SINGLETON(TNxcocadappSerializeComponent)
    IMPLEMENT_CREATE_INSTANCE_SINGLETON(TNxcocadappSerializeComponent,CLSID_INxcocadappSerialize)
END_IMPLEMENT_CREATE_INSTANCE_SINGLETON()

SUPPORT_SERVICE_COMPONENT(CLSID_INxcocadappSerialize)

//////////////////////////////////////////////////////////////////////////
// IPluginCommonToolbarFileEvent Implementation

TStatus STDCALL TNxcocadappSerializeComponent::OnOpen()
{
    if(impl_OnOpen() == true)
    {
        return M_OK;
    }
    else
    {
        return M_FAIL;
    }
}

TStatus STDCALL TNxcocadappSerializeComponent::OnSave()
{
    if(impl_OnSave() == true)
    {
        return M_OK;
    }
    else
    {
        return M_FAIL;
    }
}

TStatus STDCALL TNxcocadappSerializeComponent::OnPrint()
{
    if(impl_OnPrint() == true)
    {
        return M_OK;
    }
    else
    {
        return M_FAIL;
    }
}

//////////////////////////////////////////////////////////////////////////
// IService Implementation

TStatus STDCALL TNxcocadappSerializeComponent::InitializeService()
{
    TStatus status = M_FAIL;
    
    /*- InitializeService Begin -*/

    // Append your codes here.

	TFactory factory;
	QUERY_SERVICE(factory,
		CLSID_IPluginCommonToolbar,
		IComxUiPlugin,
		p_plugin_common);

	if (p_plugin_common != NULL)
	{
		cmgr.AddConnect(p_plugin_common, 
			IID_IPluginCommonToolbarFileEvent, 
			(IPluginCommonToolbarFileEvent*)this);
		p_plugin_common->Release();

		status = M_OK;
	}

    /*- InitializeService End -*/

    return status;
}

TStatus STDCALL TNxcocadappSerializeComponent::TerminalService()
{
    TStatus status = M_FAIL;
    
    /*- TerminalService Begin -*/

    // Append your codes here.

	cmgr.ReleaseConnects();

    /*- TerminalService End -*/

    return status;
}

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       )
{
    return TRUE;
}
