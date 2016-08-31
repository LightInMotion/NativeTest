/*
   Module Description:

      Templates are one of the key elements of the application. All devices
      are based on a template, no device can't be created without a template.
      Unless they are loaded from an already saved show file. Once a device
      is created it is independent from the template, which means even if 
      the template gets changed the device stays the same.

      A template gets loaded/saved to a template file. Each template 
      correlates to a template file. At the beginning (template manager
      initialize) all template objects get created but only the template 
      name gets loaded.

      Once the template gets selected in the device window, the remaining
      data of the template gets loaded (with the exception of the logo file).
      The optional template logo file gets only loaded when the template 
      gets loaded into the template editor.

      In order to certify templates by registered manufacturer we use an
      optional registry key. All certified template manufacturers have
      an additional registry key with their creator ID and a path to 
      a logo file. Each template created on a machine of an certified
      manufacturer automatically creates templates containing their specified
      logo.

      See TemplateFileFormat.txt for a description of the template file
      format.
*/


#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

// Includes ..................................................................

#include "../JuceLibraryCode/JuceHeader.h"

class Control;


// Defines ...................................................................

// Data Types ................................................................

// error code used for saving templates
enum TEMP_RESULT
{
   TEMP_SUCCESS,
   TEMP_UNKNOWN_ERROR,
   TEMP_FILE_READ_ONLY     // template file is read only and can't be saved
};

// Class Definition ..........................................................

class Template
{
   public:

      // constructor, no default constructor available
      Template( String pTemplatePath,
                String pFoldername,
                String pFilename,
                String pName );

      ~Template();


      // Public Interface ....................................................

      // member access
      String TempGetName() const;
      bool TempSetName (String name);
      String TempGetFilename() const;
      static String TempGetExtension();
      void TempSetFolderName (String foldername);

      // control access
      int TempGetControlCount() const;
      Control* TempGetControl (int index) const;

      int TempGetNumberOfChannels() const;
//      static bool TempValidateChannels(const std::vector<UIControl*>& UIControls);
      Uuid TempGetGUID() const;

      // load/save
      bool TempLoadName();
      bool TempLoadRemainder();
//      IDirect3DTexture8* TempGetLogo( IDirect3DDevice8* pDevice );
 //     TEMP_RESULT TempUpdate( const std::vector< UIControl* >& UIControls );

      bool TempHasLogo();

   private:

      // Private Functions ...................................................

      // template file access
/*
      bool Serialize();
      IStorage* OpenFileForRead();
      bool VerifyVersion( IStorage* pStorage );
      bool SaveVersion( IStorage* pStorage );
      bool IsReadOnly() const;

      // subfunctions of Serialize()
      bool SerializeInfo( IStorage* pStorage );
      bool SerializeControls( IStorage* pStorage );
      bool SerializeLogo( IStorage* pStorage );

      // load functions
      bool LoadInfo( IStorage* pStorage, DWORD& controlCount );
      bool LoadControls( IStorage* pStorage, DWORD controlCount );
*/
      uint32 GetCreatorID();
      String GetFullFilenamePath() const;

//      static bool ValidateControls( const std::vector< Control* >& controls );


      // Private Members .....................................................

      // flag to indicate if the template is completely loaded. This flag is
      // set after TempLoadRemainder() gets successfully called.
      bool m_IsLoaded;

      // each template has a unique GUID, whenever the template gets changed
      // a new GUID gets created and assigned to the template. That way
      // every device with the same GUID is 100% identical.
      Uuid m_GUID;

      // the template name doesn't have to match exactly the template file
      // name, but by default they are identical.
      String m_Name;

      // controls belonging to the template, get loaded in TempLoadRemainder()
      OwnedArray<Control> m_ControlList;

      // the template gets saved to the following path:
      // "m_TemplatePath\m_Foldername\m_Filename"
      // The filename already contains the extension.

      String m_TemplatePath;
      String m_Foldername;
      String m_Filename;
};


#endif // _TEMPLATE_H_

