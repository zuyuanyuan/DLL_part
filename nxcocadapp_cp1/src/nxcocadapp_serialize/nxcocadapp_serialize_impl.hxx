/*HEAD nxcocadapp_serialize_impl HXX COMX_COMPONENT_MODULE */

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

#ifndef _KMAS_COMX_NXCOCADAPP_SERIALIZE_IMPL_H_2009101535947
#define _KMAS_COMX_NXCOCADAPP_SERIALIZE_IMPL_H_2009101535947

#define DIRTY_INFORMATION  "Current data will be cleaned away,\ndo you want to continue?"
#define DIRTY_TITLE "Warning"

using namespace KMAS::Die_maker::comx;

template<typename TOwner>
class TNxcocadappSerializeImpl
{
protected:
  TNxcocadappSerializeImpl();
  ~TNxcocadappSerializeImpl(){}
protected:
  bool impl_OnOpen();
  bool impl_OnSave();
  bool impl_OnPrint();
  
  /*- Other Declarations Begin -*/
  
  // Append your codes here.
  
private:
  TFileDialogFilter _file_open_dialog_filter;
  TFileDialogFilter _file_save_dialog_filter;
  
private:
  bool is_nastran_file(const char *fname);
  bool is_step_file(const char *fname);
  bool is_iges_file(const char *fname);
  bool is_acis_file(const char *fname);
  
private:
  bool is_have_data();
  bool is_have_fem_data();
  bool is_have_cad_data();
  bool clear_current_data();
  bool clear_fem_data();
  bool clear_cad_data();
  bool is_continue();
private:
  bool load_nastran_file(const char *fname);
  bool save_nastran_file(const char *fname);
  bool load_step_file(const char *fname);
  bool load_igs_file(const char *fname);
  bool load_sat_file(const char *fname);
  bool save_sat_file(const char *fname);
  bool save_iges_file(const char *fname);
  bool save_step_file(const char *fname);
private:
  void acis_modified_notify();
private:
  void init_light();
  
  /*- Other Declaration End -*/
};

template<typename TOwner>
TNxcocadappSerializeImpl<TOwner>::TNxcocadappSerializeImpl()
{
  _file_open_dialog_filter.AppendItem(
    "Nastran Files(*.nas; *.dat)",
    "*.nas;*.dat");
	
  _file_open_dialog_filter.AppendItem(
    "Step Files(*.stp; *.step)",
    "*.stp;*.step");
	
  _file_open_dialog_filter.AppendItem(
    "Iges Files(*.igs; *.iges)",
    "*.igs;*.iges");
	
  _file_open_dialog_filter.AppendItem(
    "Acis Files(*.sta; *.sab)",
    "*.sat;*.sab");
	
  _file_save_dialog_filter.AppendItem(
    "Acis Files(*.sta; *.sab)",
    "*.sat;*.sab");
	
  _file_save_dialog_filter.AppendItem(
    "Nastran Files(*.nas; *.dat)",
    "*.nas;*.dat");

  _file_save_dialog_filter.AppendItem(
    "Iges Files(*.igs; *.iges)",
    "*.igs;*.iges");

  _file_save_dialog_filter.AppendItem(
    "Step Files(*.stp; *.step)",
    "*.stp;*.step");
}

//////////////////////////////////////////////////////////////////////////
// IPluginCommonToolbarFileEvent Implementation

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::impl_OnOpen()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_OnOpen Begin -*/
  
  // Append your codes here.

  init_light();
  
  if (is_continue())
    {
      clear_current_data();
      
      char fname[1024] = "";
      if(TPluginToolbox(_file_open_dialog_filter).
	 CallOpenFileDialog(fname))
	{
	  if (is_nastran_file(fname))
	    {
	      load_nastran_file(fname);
	    }
	  else if (is_step_file(fname))
	    {
	      load_step_file(fname);
	      acis_modified_notify();
	    }
	  else if (is_iges_file(fname))
	    {
	      load_igs_file(fname);
	      acis_modified_notify();
	    }
	  else if (is_acis_file(fname))
	    {
	      load_sat_file(fname);
	      acis_modified_notify();
	    }
	  else
	    {
	      ;// The type don't been supported.
	    }
	}
    }
  
  /*- impl_OnOpen End -*/
  
  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::impl_OnSave()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;
  
  /*- impl_OnSave Begin -*/
  
  // Append your codes here.
  
  if (is_have_data())
    {
      char fname[1024] = "";
      if(TPluginToolbox(_file_save_dialog_filter).
	 CallSaveFileDialog(fname))
	{
	  if (is_nastran_file(fname))
	    {
	      save_nastran_file(fname);
	    }
	  else if (is_acis_file(fname))
	    {
	      save_sat_file(fname);
	    }
	  else if (is_step_file(fname))
	    {
	      save_step_file(fname);
	    }
	  else if (is_iges_file(fname))
	    {
	      save_iges_file(fname);
	    }
	  else
	    {
	      ;// The type don't been supported.
	    }
	}
    }
  
  /*- impl_OnSave End -*/
  
  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::impl_OnPrint()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;
  
  /*- impl_OnPrint Begin -*/
  
  // Append your codes here.
  
  /*- impl_OnPrint End -*/
  
  return ret;
}

/*- Other Implementation Begin -*/

// Append your codes here.

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_nastran_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;
  
  /*- impl_PaintGL Begin -*/
  
  // Append your codes here.
  
  string exfname = get_ext_filename(string(fname));
  return (exfname == string("nas") || exfname == string("dat"));
  
  /*- impl_PaintGL End -*/
  
  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_step_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;
  
  /*- impl_PaintGL Begin -*/
  
  // Append your codes here.
  
  string exfname = get_ext_filename(string(fname));
  return (exfname == string("step") || exfname == string("stp"));
  
  /*- impl_PaintGL End -*/
  
  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_iges_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;
  
  /*- impl_PaintGL Begin -*/
  
  // Append your codes here.

  string exfname = get_ext_filename(string(fname));
  return (exfname == string("igs") || exfname == string("iges"));

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_acis_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  string exfname = get_ext_filename(string(fname));
  return (exfname == string("sat") || exfname == string("sab"));

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_have_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  ret = is_have_fem_data() || is_have_cad_data();

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::clear_current_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  clear_cad_data();
  clear_fem_data();

  ret = true;

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::clear_fem_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IFemCore *p_fem_core = NULL;
  COMX_GetPackageProp("fem:data", (void**)&p_fem_core);
	
  p_fem_core->Clear();
  p_fem_core->Clean();
	
  p_fem_core->Release();

  ret = true;

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::clear_cad_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisCore *p_acis_core = NULL;
  COMX_GetPackageProp("acis:data", (void**)&p_acis_core);
	
  p_acis_core->Clear();
	
  p_acis_core->Release();

  ret = true;

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_have_fem_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IFemCore *p_fem_core = NULL;
  COMX_GetPackageProp("fem:data", (void**)&p_fem_core);

  TNodeIterator nbegin, nend;
  p_fem_core->GetNode(BEGIN ,nbegin);
  p_fem_core->GetNode(END, nend);

  ret = ((nend - nbegin) != 0);

  p_fem_core->Release();

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_have_cad_data()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisCore *p_acis_core = NULL;
  COMX_GetPackageProp("acis:data", (void**)&p_acis_core);

  ENTITY_LIST *p_elist = NULL;
  p_acis_core->RefEntityList(p_elist);

  ret = (p_elist->count() != 0);

  p_acis_core->Release();

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::is_continue()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  if (is_have_data()) 
    {
      return MessageBox(
        NULL, 
        DIRTY_INFORMATION, 
        DIRTY_TITLE,
        MB_ICONWARNING + MB_YESNO) == IDYES;
    }
  else 
    {
      return true;
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::load_nastran_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IFemSerialize *p_fem_serialize = NULL;
  COMX_GetPackageProp("fem:serialize", (void**)&p_fem_serialize);

  if (p_fem_serialize != NULL)
    {
      p_fem_serialize->Import(fname);
      p_fem_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::save_nastran_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IFemSerialize *p_fem_serialize = NULL;
  COMX_GetPackageProp("fem:serialize", (void**)&p_fem_serialize);
	
  if (p_fem_serialize != NULL)
    {
      p_fem_serialize->Export(fname);
      p_fem_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::load_step_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);

  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Import(fname, ACIS_IO_STEP);

      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::load_igs_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);
	
  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Import(fname, ACIS_IO_IGES);
		
      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::load_sat_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);
	
  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Open(fname);
		
      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::save_sat_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);
	
  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Save(fname);
		
      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::save_iges_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);
	
  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Export(fname, ACIS_IO_IGES);
		
      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
bool TNxcocadappSerializeImpl<TOwner>::save_step_file(const char *fname)
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisSerialize *p_acis_serialize = NULL;
  COMX_GetPackageProp("acis:serialize", (void**)&p_acis_serialize);
	
  if (p_acis_serialize != NULL)
    {
      p_acis_serialize->Export(fname, ACIS_IO_STEP);
		
      p_acis_serialize->Release();
    }

  /*- impl_PaintGL End -*/

  return ret;
}

template<typename TOwner>
void TNxcocadappSerializeImpl<TOwner>::acis_modified_notify()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  // bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  IAcisCore *p_acis_core = NULL;
  COMX_GetPackageProp("acis:data", (void**)&p_acis_core);
	
  if (p_acis_core != NULL)
    {
      p_acis_core->ModifiedNotify();
      p_acis_core->Release();
    }
	
  /*- impl_PaintGL End -*/

  // return ret;
}

template<typename TOwner>
void TNxcocadappSerializeImpl<TOwner>::init_light()
{
  TOwner *pOwner = static_cast<TOwner*>(this);
  // bool ret = false;

  /*- impl_PaintGL Begin -*/

  // Append your codes here.

  static bool is_init = false;
	
  if (!is_init)
    {
      is_init = true;

      TFactory factory;
      QUERY_SERVICE(factory,
          CLSID_IGlLight,
          IGlLightCustomer,
          p_gl_light_customer);

      if (p_gl_light_customer != NULL)
	{
	  p_gl_light_customer->UseDefaultLampHouse();
	  p_gl_light_customer->Release();
	}
    }

  /*- impl_PaintGL End -*/

  return /*ret*/;
}

/*- Other Implementation End -*/

#endif
