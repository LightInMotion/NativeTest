/*
   File Info:

      $Workfile:   Device.h  $
      $Author:   JOE  $
      $Revision:   1.0  $
      $Modtime:   08 Aug 2004 15:12:38  $

   Module Description:

      A Device is very similar to a Template, the only main difference
      between a template and a device is that a device can not modify, add
      or delete and controls anymore. The device also can't modify the 
      control settings/properties anymore.
      Each Device contains a (now fixed) list of controls. Once the update
      function is called (from the cue) the device walks the control list
      and calls the update functions in the controls. The controls do the
      actual work and calculate the DMX values.
*/


#ifndef _DEVICE_H_
#define _DEVICE_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"
#include "ShowFile.h"

class Control;
class Template;
class DeviceGroup;
class DeviceManager;


// Defines ...................................................................

// Data Types ................................................................

// Class Definition ..........................................................

class Device
{
   public:
    
      Device();
      Device (String name, Uuid guid);
      ~Device();

      // Public Interface ....................................................

      // member access
      String DeviceGetName() const;
      void DeviceSetName (String name);

      uint32 DeviceGetBaseAddress() const;
      void DeviceSetBaseAddress (uint32 address);

      int DeviceGetNumberOfChannels() const;
      void DeviceCalculateNumberOfChannels();

      // control access
      int DeviceGetControlCount() const;
      Control* DeviceGetControl (int index);

      void DeviceUpdateBuffer( const uint8* pCueBuffer,
                               uint8* pOutputBuffer,
                               int faderLevel,
                               int GMAdjustedLevel );

      bool DeviceCloneControls (const Template* pTemplate);

      // device group access
      DeviceGroup* DeviceGetGroup();
      void DeviceSetGroup (DeviceGroup* pDeviceGroup);

      // compare operators
      bool operator==( const Device& device ) const;
      bool operator!=( const Device& device ) const;

      // save/load
/*
      bool DeviceSerialize( IStorage* pStorage, 
                            const DeviceManager* pDeviceManager ) const;
*/
      bool DeviceLoad( ShowFile& show,
                       uint32 version,
                       const OwnedArray<DeviceGroup>* groupList );

      // find for saving
      bool DeviceFindPositionControl( const Control* pControl, 
                                      int& controlIndex ) const;

   private:

      // Private Functions ...................................................
/*
      // save/load subfunctions
      bool SerializeInfo( IStorage* pStorage, 
                          const DeviceManager* pDeviceManager ) const;
      
      bool SerializeControls(IStorage* pStorage ) const;
*/
      bool LoadInfo( ShowFile& show,
                     const OwnedArray<DeviceGroup>* groupList,
                     uint32& controlCount );
      
      bool LoadControls( ShowFile& show,
                         uint32 version,
                         uint32 controlCount );


      // Private Members .....................................................

      // each device has a GUID which is identical to the GUID from the 
      // template it is based on. This way devices can be compared with only
      // comparing the GUID.
      Uuid m_GUID;

      // name of the device
      String m_Name;

      // DMX start address of the device. All Control addresses are relative
      // to this address.
      // This address is zero-based to directly access the cue buffer which
      // goes from 0 to 2047.
      // For display purpose we make it one-based and display channel 
      // 1 to 2048 (actually 1 to 512 for 4 universes)
      uint32 m_BaseAddress;

      // number of DMX channels including all controls. This is set during
      // device creation (cloning) based on the template.
      int m_NumberOfChannels;

      // we use std::vector instead of std::list because access it is much 
      // faster (shown in performance tests)

      // vector of controls belonging to the device
//      std::vector< Control* > m_ControlList;

      OwnedArray<Control> m_ControlList;
    
      // device group. Every device (can) belong(s) to a device group.
      DeviceGroup* m_pDeviceGroup;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Device)
};


#endif // _DEVICE_H_

