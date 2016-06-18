/*HEAD nxcocadapp_gui CXX COMX_COMPONENT_MODULE */

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

#include "nxcocadapp_gui.hxx"

#include <base\service.hxx>
#include <base\factory.hxx>

#include <ui\ui_toolbar_parser.hxx>
#include <ui\plugin.hxx>

#include "nxcocadapp_gui_impl.hxx"

using namespace KMAS::Die_maker::comx;

class TNxcocadappGuiComponent : public IUiToolbarParser,
                              public IService,
                              public TFactory,
                              public TNxcocadappGuiImpl<TNxcocadappGuiComponent>
{
    friend class TNxcocadappGuiImpl<TNxcocadappGuiComponent>;
public:
    TNxcocadappGuiComponent() : 
        INITIALIZE_REF_COUNT()
    {
        /*Do nothing*/
    }
    ~TNxcocadappGuiComponent()
    {
        /*Do nothing*/
    }
public:
    BEGIN_IMPLEMENT_ROOT()
        IMPLEMENT_INTERFACE(IUiToolbarParser)
        IMPLEMENT_INTERFACE_ROOT(IUiToolbarParser)
        IMPLEMENT_INTERFACE(IService)
    END_IMPLEMENT_ROOT()
public:
    virtual TStatus STDCALL OnDispatch(const char* tbid, const int index);
public:
    virtual TStatus STDCALL InitializeService();
    virtual TStatus STDCALL TerminalService();
public:
    DECLARE_CREATE_INSTANCE_SINGLETON(TNxcocadappGuiComponent)

/*- Other Declarations Begin -*/

// Append your codes here.

TConnectManager cmgr;

/*- Other Declaration End -*/
};

BEGIN_IMPLEMENT_CREATE_INSTANCE_SINGLETON(TNxcocadappGuiComponent)
    IMPLEMENT_CREATE_INSTANCE_SINGLETON(TNxcocadappGuiComponent,CLSID_INxcocadappGui)
END_IMPLEMENT_CREATE_INSTANCE_SINGLETON()

SUPPORT_SERVICE_COMPONENT(CLSID_INxcocadappGui)

//////////////////////////////////////////////////////////////////////////
// IUiToolbarParser Implementation

TStatus STDCALL TNxcocadappGuiComponent::OnDispatch(const char* tbid, const int index)
{
    if(impl_OnDispatch(tbid, index) == true)
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

TStatus STDCALL TNxcocadappGuiComponent::InitializeService()
{
    TStatus status = M_FAIL;
    
    /*- InitializeService Begin -*/

    // Append your codes here.

	TFactory factory;
	QUERY_SERVICE(factory,
		CLSID_IUiToolbarParser,
		IComxUiPlugin,
		p_tb_parser);
	
	if (p_tb_parser != NULL)
	{
		cmgr.AddConnect(p_tb_parser, IID_IUiToolbarParser, (IUiToolbarParser*)this);
		p_tb_parser->Release();
	}

	status = M_OK;

    /*- InitializeService End -*/

    return status;
}

TStatus STDCALL TNxcocadappGuiComponent::TerminalService()
{
    TStatus status = M_FAIL;
    
    /*- TerminalService Begin -*/

    // Append your codes here.

	cmgr.ReleaseConnects();

	status = M_OK;

    /*- TerminalService End -*/

    return status;
}

// BOOL APIENTRY DllMain( HANDLE hModule,
//                        DWORD  ul_reason_for_call,
//                        LPVOID lpReserved
//                        )
// {
//     return TRUE;
// }
