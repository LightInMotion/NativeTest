/*
   File Info:

      $Workfile:   Control.cpp  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   08 Aug 2004 15:15:10  $

   Module Description:

      This is the base class of all the derived control variations. The 
      virtual function ControlUpdateBuffer() has to be implemented by the
      derived control (unless the control has no DMX functionality like the
      label control).
*/

// Includes ..................................................................

#include "Control.h"
//#include "FileHelper.h"


// Local Defines .............................................................

// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
   Control::Control

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

Control::Control()
   :  m_DeviceBaseAddress(0)
{
}


/*----------------------------------------------------------------------------
   Control::~Control

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/

Control::~Control()
{
}


// Member Access functions ...................................................

/*
   Get/Set position and other member variables
*/

/*----------------------------------------------------------------------------
   Control::ControlGetPosition

   Get the position rectangle for the visual representation in the cue editor
   and the template editor. The returned position is given in coordinates
   relative to the cue control view and template control view, respectively.

   The given position is NOT identical with the windows position if the
   UI control is a nested UI control (e.g. used in the UIModeControl).

   Returns: rectangle
----------------------------------------------------------------------------*/

Control::Position
Control::ControlGetPosition() const
{
   // return control position
   return m_Position;
}


/*----------------------------------------------------------------------------
   Control::ControlSetPosition

   set the position rectangle for the visual representation of the control in 
   the cue editor and template editor.

   This function should only be called from the template editor while we 
   create/edit a template. Once a device is created based on a template
   the position should not be changed anymore. Therefor this funcions 
   should not be called from the cue editor.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Control::ControlSetPosition( const Control::Position& rect )
{
   // update control position
   m_Position = rect;
}


/*----------------------------------------------------------------------------
   Control::ControlGetAddress

   Get the base address from the control

   Returns: base address of control
----------------------------------------------------------------------------*/

uint32
Control::ControlGetAddress() const
{
   return m_DeviceBaseAddress;
}


/*----------------------------------------------------------------------------
   Control::ControlSetAddress

   Set the base address of the control to the same as the device. This 
   function is virtual and the mode control (which has nested sub controls)
   has to overload this function in order to also set the base address of
   its nested controls.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Control::ControlSetAddress (uint32 baseAddress)
{
   // save the base address of the device
   m_DeviceBaseAddress = baseAddress;
}


// name ......................................................................
/*
   Set/Get name
*/

/*----------------------------------------------------------------------------
   Control::ControlGetName

   Get name

   Returns: name string 
----------------------------------------------------------------------------*/

String
Control::ControlGetName() const
{
   // return a copy of the name
    return m_Name;
}


/*----------------------------------------------------------------------------
   Control::ControlSetName

   Set name

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Control::ControlSetName (String pName)
{
   // set name
   m_Name = pName;
}


// save/load .................................................................
/*
   Save and load the control to/from the structure storage file. The base
   implementation of those functions write/read the basic control data to/from
   the file and have to be called from the derived classed BEFORE any other
   control specific data is writen/read from the file.
*/

#if 0
/*----------------------------------------------------------------------------
   Control::ControlSerialize

   Save the base control data to the structure storage file. This is a virtual
   function and has to be called from the derived classes BEFORE saving any
   control specific data

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Control::ControlSerialize( IStream* pStream ) const
{
   // We don't save/load the control type here, that is done in 
   // DeviceSerialize()/DeviceLoad() so that the device can create the 
   // correct control object.

   // save position
   if( pStream->Write( &m_Position, sizeof(RECT), NULL ) != S_OK )
      return false;

   // save control name
   if( ! FileHelpWriteString( pStream, m_Name ))
      return false;

   return true;
}

#endif

/*----------------------------------------------------------------------------
   Control::ControlLoad

   Load all Control specific data (base class specific) to the structure
   storage file.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Control::ControlLoad( ShowFile& show,
                      uint32 version )
{
   // We don't save/load the control type here, that is done in 
   // DeviceSerialize()/DeviceLoad() so that the device can create the 
   // correct control object.

   uint32 bytesRead = 0;
   int rectSize = sizeof(Position);

   // load position
   if(! show.readBytes ((uint8 *)(&m_Position), rectSize, bytesRead))
      return false;

   // check read bytes
   if( bytesRead != (uint32)rectSize )
      return false;

   // load control name
    if (! show.readString (m_Name))
      return false;

   return true;
}


// Protected Functions .......................................................

/*----------------------------------------------------------------------------
   Control::ControlCloneAllData

   This function is called from the derived classes during the clone process.
   It duplicates/clones all data from the "Control" class, all members from 
   the derived classes have to be duplicated/cloned by the derived class.

   Returns: no return value
 
 !!!! Should this just be a copy operator?
----------------------------------------------------------------------------*/

void 
Control::ControlCloneAllData( Control* pNewControl ) const
{
   // copy position 
   pNewControl->m_Position = m_Position;

   // copy base address
   pNewControl->m_DeviceBaseAddress = m_DeviceBaseAddress;

   // duplicate control name (don't just copy the string pointer)
   pNewControl->m_Name = m_Name;
}









