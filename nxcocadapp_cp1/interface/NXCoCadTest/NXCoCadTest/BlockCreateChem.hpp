//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\Users\Administrator\Desktop\BlockCreateChem.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 8.5
//              Date: 06-06-2016  (Format: mm-dd-yyyy)
//              Time: 18:00
//
//==============================================================================

#ifndef BLOCKCREATECHEM_H_INCLUDED
#define BLOCKCREATECHEM_H_INCLUDED

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include <uf_defs.h>
#include <uf_ui_types.h>
#include <iostream>
#include <NXOpen/Session.hxx>
#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/Callback.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/BlockStyler_UIBlock.hxx>
#include <NXOpen/BlockStyler_BlockDialog.hxx>
#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <NXOpen/BlockStyler_Group.hxx>
#include <NXOpen/BlockStyler_StringBlock.hxx>
#include <NXOpen/BlockStyler_Button.hxx>

//------------------------------------------------------------------------------
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

class DllExport BlockCreateChem
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    BlockCreateChem();
    ~BlockCreateChem();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementation
    // of these prototypes is provided in the BlockCreateChem.cpp file. 
    // You are REQUIRED to write the implementation for these functions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    PropertyList* GetBlockProperties(const char *blockID);
    
private:
    const char* theDlxFileName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
    NXOpen::BlockStyler::Group* group0;// Block type: Group
    NXOpen::BlockStyler::StringBlock* string0;// Block type: String
    NXOpen::BlockStyler::StringBlock* string01;// Block type: String
    NXOpen::BlockStyler::StringBlock* string02;// Block type: String
    NXOpen::BlockStyler::StringBlock* string03;// Block type: String
    NXOpen::BlockStyler::Button* button0;// Block type: Button
    
};
#endif //BLOCKCREATECHEM_H_INCLUDED
