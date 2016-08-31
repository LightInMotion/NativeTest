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

// Includes ..................................................................

#include "Template.h"
#include "Control.h"
//#include "UIControl.h"
//#include "FileHelper.h"
//#include "resource.h"
//#include "Registry.h"
//#include "SelectControl.h"
//#include "ModeControl.h"
//#include "PositionControl.h"
#include "FaderControl.h"
//#include "FileManager.h"
//#include "Main.h"


// Local Defines .............................................................

// template file versions.

// modified position control data (add use effects)
const uint32 _TEMPLATE_FILE_VERSION_PREALPHA5    = 0x0005;


//const DWORD _TEMPLATE_FILE_VERSION_1_00    = 0x0100;

// current version
const uint32 _TEMPLATE_FILE_VERSION_CURRENT = _TEMPLATE_FILE_VERSION_PREALPHA5;


// Local Data Types ..........................................................

// Public Interface ..........................................................

/*----------------------------------------------------------------------------
   Template::Template

   Constructor

   Returns: no return value
----------------------------------------------------------------------------*/

Template::Template( String pTemplatePath,
                    String pFoldername,
                    String pFilename,
                    String pName )
   :  m_IsLoaded (false),
      m_GUID ("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
      m_Name (pName),
      m_TemplatePath (pTemplatePath),
      m_Foldername (pFoldername),
      m_Filename (pFilename)
{
}


/*----------------------------------------------------------------------------
   Template::~Template

   Destructor

   Returns: no return value
----------------------------------------------------------------------------*/

Template::~Template()
{
   // free all controls contained in the template
   // Owned array takes care of it...
}


// member access..............................................................

/*
   member access functions
*/

/*----------------------------------------------------------------------------
   Template::TempGetName 

   get the template name

   Returns: template name
----------------------------------------------------------------------------*/

String
Template::TempGetName() const
{
   return m_Name;
}


/*----------------------------------------------------------------------------
   Template::TempSetName   

   Set the template name. This function also renames the associated template
   file to match the new template name. The function updates the template
   file (with the new name) after it renames the file itself.

   This function does NOT generate a new GUID for the template. If a template
   only differs by name then the generated devices are still considered
   'identical'.

   Returns: true or false
----------------------------------------------------------------------------*/

bool
Template::TempSetName (String pName)
{
   // make sure the remainder is loaded, otherwise it can happen that we
   // save an empty template
   if (! TempLoadRemainder())
      return false;

   // get current template path and file extension
//   std::wstring oldPath = GetFullFilenamePath();
//   std::wstring fileExtension = TempGetExtension();

   // new template path
//   std::wstring newPath = m_TemplatePath.c_str();
//   newPath += TEXT("\\");
//   newPath += m_Foldername.c_str();
//   newPath += TEXT("\\");
//   newPath += pName;
//   newPath += fileExtension.c_str();

   // rename the template file, return false if the function fails
//   if( ! MoveFile( oldPath.c_str(), newPath.c_str()))
//      return false;

   // save old name and file name in case the serialize fails
//   std::wstring oldName = m_Name.c_str();
//   std::wstring oldFilename = m_Filename.c_str();

   // update the template name and file name
   m_Name = pName;
//   m_Filename = pName;
//   m_Filename += fileExtension.c_str();

   // save the file to the new template file
//   if( ! Serialize())
//   {
      // restore old name and file name
//      m_Name = oldName.c_str();
//      m_Filename = oldFilename.c_str();

      // rename the file back to the old file name.
//      MoveFile( newPath.c_str(), oldPath.c_str());
//      return false;
//   }

   return true;
}


/*----------------------------------------------------------------------------
   Template::TempGetFilename

   Return the file name for the template including the file extension.

   Returns: file name
----------------------------------------------------------------------------*/

String
Template::TempGetFilename() const
{
   // return file name
   return m_Filename;
}


/*----------------------------------------------------------------------------
   Template::TempGetExtension

   Return the file name extension for templates. This is a static function

   Returns: 
----------------------------------------------------------------------------*/

String
Template::TempGetExtension()
{
   // load the template file extension from the resources
   return String (".tpl");
}


/*----------------------------------------------------------------------------
   Template::TempSetFolderName

   This function gets called from TemplateFolder when the folder name changes.
   We have to update the folder name in all templates in order to access
   the correct template path.

   Returns: no return value
----------------------------------------------------------------------------*/

void 
Template::TempSetFolderName (String pFoldername)
{
   // update the folder name
   m_Foldername = pFoldername;
}


// control access ............................................................
/*
   access to the controls in the template. Used from Device and template 
   control view.
*/
/*----------------------------------------------------------------------------
   Template::TempGetControlCount   

   get the number of controls contained in the template

   Returns: number of controls
----------------------------------------------------------------------------*/

int 
Template::TempGetControlCount() const
{
   // return number of controls
   return m_ControlList.size();
}


/*----------------------------------------------------------------------------
   Template::TempGetControl   

   Get the control from the control list. No index validation is performed,
   the index must be valid.

   Returns: control pointer
----------------------------------------------------------------------------*/

Control* 
Template::TempGetControl( int index ) const
{
   // return control pointer
   return m_ControlList[index];
}


/*----------------------------------------------------------------------------
   Template::TempGetNumberOfChannels 

   Return number of DMX channels of the template. We get all occupied DMX
   channels from all controls and return the number of occupied channels.
   That is the channel count from the first and last occupied channel.

   ! The implementation of this function is identical to 
   DeviceCalculateNumberOfChannels() !

   Returns: number of DMX channels occupied by the template
----------------------------------------------------------------------------*/

int 
Template::TempGetNumberOfChannels() const
{
   std::vector<int> channels;

   // for all controls
   int controlCount = m_ControlList.size();
   for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      // get the number of used channels from the control. Each control adds
      // their channels to the given vector
      m_ControlList[controlIndex]->ControlGetUsedChannels( channels, true );

   // do we have any channels at all
   int channelCount = channels.size();
   if( channelCount == 0 )
      // we don't contain any channels at all
      return 0;

   int maxChannel = channels[0];

   // for all returned channels, it is possible that some channels are 
   // duplicated. E.g. the sub controls in the mode control might contain
   // the same channel.

   for( int channelIndex = 0; channelIndex < channelCount; channelIndex++ )
   {
      // update the maximum channel
      if( channels[channelIndex] > maxChannel )
         maxChannel = channels[channelIndex];
   }

   // return the number of occupied channels, it always starts at zero
   return maxChannel + 1;
}


/*----------------------------------------------------------------------------
   Template::TempValidateChannels

   This function gets called from the template editor before the template
   gets saved. The function checks if all controls have a unique DMX channel.
   The function doesn't check sub controls from the mode control, since 
   those channels can use overlapping DMX channels.

   This function doesn't actually check the existing Control objects, it
   uses the given UIControl objects and creates temporary Control objects.
   That is necessary because we call this function before we save the 
   template and therefore the existing controls are not the once we want
   to check/validate.

   This function is a static function.

   If this function returns false then we warn the user.

   Returns: true if every control has a unique DMX channel, false if 
            one or more controls occupy the same channel.
----------------------------------------------------------------------------*/

bool 
Template::TempValidateChannels(
   const std::vector<UIControl*>& UIControls) // UI controls from the
                                              // template control view
{
   std::vector< Control* > tempControls;

   // create a temporary control from the given UI controls
   int UIControlCount = UIControls.size();
   int UIControlIndex;
   for( UIControlIndex = 0; 
        UIControlIndex < UIControlCount; 
        UIControlIndex++ )
   {
      // create temporary control based on the given UI control
      Control* pTempControl = 
         UIControls[UIControlIndex]->UIControlCreateControl();

      if( ! pTempControl )
         return false;

      tempControls.push_back( pTempControl );
   }

   // check if any of the controls have overlapping DMX channels
   bool result = ValidateControls( tempControls );

   // free all temporary controls
   for(UIControlIndex = 0; UIControlIndex < UIControlCount; UIControlIndex++)
      delete tempControls[UIControlIndex];

   return result;
}


/*----------------------------------------------------------------------------
   Template::TempGetGUID

   Return the GUID of the template

   Returns: GUID
----------------------------------------------------------------------------*/

GUID 
Template::TempGetGUID() const
{
   return m_GUID;
}


// load/save .................................................................
/*
   The template manager (template folder) calls the function TempLoadName()
   during startup. This function only checks if the file is a valid template
   file and loads the name. 
   The controls get only loaded on request when the function 
   TempLoadRemainder() gets called. The optional logo file gets only loaded
   on request from the template editor for display purpose.
*/

/*----------------------------------------------------------------------------
   Template::TempLoadName

   This function gets called during startup from the template manager.
   It opens the template file and checks the version if it is a valid template
   file. Then loads the template name from the file and returns.
   The is loaded flag does NOT get set from this function.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::TempLoadName()
{
   bool result = true;

   // open the template file and verify that the version is correct
   IStorage* pStorage = OpenFileForRead();
   if( pStorage )
   {
      // load the info stream, this will load the name and the GUID.
      // We ignore the control count and creator ID here.

      DWORD controlCount = 0;
      if( ! LoadInfo( pStorage, controlCount ))
         result = false;

      // close the template file
      pStorage->Release();
   }
   else
      result = false;;

   return result;
}

      
/*----------------------------------------------------------------------------
   Template::TempLoadRemainder

   Load the remainder of the template and set the is loaded flag. This
   function gets called from the device window to load templates on request.
   Once the template is loaded it stays in memory until the application gets
   closed. If the function gets called multiple times it just checks the
   loaded flag and returns.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::TempLoadRemainder()
{
   // check if the template is already fully loaded
   if( m_IsLoaded )
      return true;

   bool result = true;

   // open the template file and verify that the version is correct
   IStorage* pStorage = OpenFileForRead();
   if( pStorage )
   {
      // load all template data with the exception of the optional logo
      // file.

      // load info, this will return the control count
      DWORD controlCount = 0;
      if( LoadInfo( pStorage, controlCount ))
      {
         // load all controls
         if( ! LoadControls( pStorage, controlCount ))
            result = false;
      }
      else
         result = false;

      // close the template file
      pStorage->Release();
   }
   else
      result = false;

   // was the load successful
   if( result )
      // set the loaded flag
      m_IsLoaded = true;

   return result;
}

      
/*----------------------------------------------------------------------------
   Template::TempGetLogo

   Get the optional logo for certified template manufacturers. The caller
   of this function has to free (Release()) the texture after he is finished
   using the texture.

   Returns: DirectX texture or NULL if failed
----------------------------------------------------------------------------*/

IDirect3DTexture8* 
Template::TempGetLogo( IDirect3DDevice8* pDevice )
{
   IDirect3DTexture8* pTexture = NULL;

   // open the template file and verify that the version is correct
   IStorage* pStorage = OpenFileForRead();
   if( pStorage )
   {
      // open "Logo" stream
      IStream* pStreamLogo = FileHelpOpenStream( pStorage, 
                                                 IDS_TEMPLATE_FILE_LOGO );
      if( pStreamLogo )
      {
         STATSTG stat;
         ZeroMemory( &stat, sizeof(stat));

         // get the size of the stream
         if( pStreamLogo->Stat( &stat, STATFLAG_NONAME ) == S_OK )
         {
            int size = stat.cbSize.u.LowPart;

            // allocate buffer for logo file
            BYTE* pBuffer = new BYTE[size];
            if( pBuffer )
            {
               // read the logo data from the stream
               ULONG bytesRead = 0;
               if( pStreamLogo->Read( pBuffer, 
                                      size, 
                                      &bytesRead ) == S_OK )
               {
                  // double check size read
                  if( bytesRead == size )
                  {
                     // read the texture from the logo data. The logo data has
                     // to be a png-file
                     if( D3DXCreateTextureFromFileInMemory( pDevice,
                                                            pBuffer,
                                                            size,
                                                            &pTexture ) 
                        != D3D_OK )
                     {
                        pTexture = NULL;
                     }
                  }
               }

               delete[] pBuffer;
            }
         }

         // close logo stream
         pStreamLogo->Release();
      }

      // close the template file
      pStorage->Release();
   }

   return pTexture;
}


/*----------------------------------------------------------------------------
   Template::TempUpdate

   Update all changes to the template object in memory and save all changes
   to the associated disc file. This function will generate a new GUID.

   Returns: value of TEMP_RESULT
----------------------------------------------------------------------------*/

TEMP_RESULT 
Template::TempUpdate( 
   const std::vector< UIControl* >& UIControls )// new UI controls to save
                                                // to the template.
{
   // check if the template file is read only, if so return an error
   if( IsReadOnly())
      return TEMP_FILE_READ_ONLY;

   // we save all existing control pointers in a temporary vector. Only 
   // after everything was successful do we delete all old controls. If 
   // an error occurs (e.g. the save to disc fails), then we restore the
   // old control vector and the old GUID

   // copy existing controls to temporary vector
   std::vector< Control* > oldControls( m_ControlList );

   // copy existing GUID to temporary GUID
   GUID oldGUID;
   CopyMemory( &oldGUID, &m_GUID, sizeof(GUID));

   // create new GUID
   if( CoCreateGuid( &m_GUID ) != S_OK )
   {
      // copy old GUID back
      CopyMemory( &m_GUID, &oldGUID, sizeof(GUID));
      return TEMP_UNKNOWN_ERROR;
   }

   // clear the control vector
   m_ControlList.clear();

   bool success = true;

   // for all new given UI controls
   int UIControlCount = UIControls.size();
   for( int UIControlIndex = 0; 
        UIControlIndex < UIControlCount; 
        UIControlIndex++ )
   {
      // create new Control based on the UIControl
      Control* pNewControl = 
         UIControls[UIControlIndex]->UIControlCreateControl();

      if( ! pNewControl )
      {
         // abort
         success = false;
         break;
      }

      // add new control pointer to the control vector
      m_ControlList.push_back( pNewControl );
   }

   if( success )
      // save the file to disc
      success = Serialize();

   if( success )
   {
      // for all old controls
      int oldControlCount = oldControls.size();
      for( int oldIndex = 0; oldIndex < oldControlCount; oldIndex++ )
      {
         // delete the old control
         Control* pOldControl = oldControls[oldIndex];
         delete pOldControl;
      }  

      // set the loaded flag
      m_IsLoaded = true;
   }
   // an error occurred
   else
   {
      // for all new controls
      int newControlCount = m_ControlList.size();
      for( int newIndex = 0; newIndex < newControlCount; newIndex++ )
      {
         Control* pNewControl = m_ControlList[newIndex];
         delete pNewControl;
      }

      m_ControlList.clear();

      // copy the old control pointers back to the control vector
      m_ControlList = oldControls;

      // copy old GUID back 
      CopyMemory( &m_GUID, &oldGUID, sizeof(GUID));
   }

   if( success )
      return TEMP_SUCCESS;

   return TEMP_UNKNOWN_ERROR;
}


/*----------------------------------------------------------------------------
   Template::TempHasLogo

   Checks if the template has a logo. If a template has a logo then it is
   a certified template and the user is not allowed to overwrite the template.
   If the user is a certified user itself then we allow overwriting the 
   template.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::TempHasLogo()
{
   // we just check if the template file has a logo stream. We don't actually
   // validate the logo.

   bool hasLogo = false;

   // open the template file and verify that the version is correct
   IStorage* pStorage = OpenFileForRead();
   if( pStorage )
   {
      // open "Logo" stream
      IStream* pStreamLogo = FileHelpOpenStream( pStorage, 
                                                 IDS_TEMPLATE_FILE_LOGO );
      if( pStreamLogo )
      {
         hasLogo = true;

         // close logo stream
         pStreamLogo->Release();
      }

      // close the template file
      pStorage->Release();
   }

   return hasLogo;
}


// Private Functions .........................................................

// template file access ......................................................
/*
   The template gets stored as a structure storage file (just as the show 
   file itself). See TemplateFileFormat.txt for more details.
*/

/*----------------------------------------------------------------------------
   Template::Serialize

   Serialize the template to the template disc file

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::Serialize()
{
   // first create a temporary structure storage file and then save all the
   // data to that file. After that we replace the old file with the new
   // temporary file.

   bool result = true;

   // file information of the temporary file. We need the file name in case
   // anything fails
   STATSTG rootStorageInfo;
   ZeroMemory( &rootStorageInfo, sizeof( rootStorageInfo ));

   // create a temporary structure storage file. When passing NULL as the 
   // file name this function automatically creates a temporary file 
   // (in the temporary folder), that's exactly what we want.
   IStorage* pStorage = NULL;
   if( StgCreateStorageEx( 
            NULL, 
            STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_DIRECT,
            STGFMT_STORAGE, 
            0,
            NULL,
            0,
            IID_IStorage,
            (void**)&pStorage ) == S_OK )
   {
      // get the file name of the temporary file
      if( pStorage->Stat( &rootStorageInfo, 0 ) != S_OK )
         result = false;

      // save template file version
      if( ! SaveVersion( pStorage ))
         result = false;

      // serialize template data to "Info" stream
      if( ! SerializeInfo( pStorage ))
         result = false;

      // serialize control data
      if( ! SerializeControls( pStorage ))
         result = false;

      // serialize template creator logo (if available)
      if( ! SerializeLogo( pStorage ))
         result = false;

      // close temporary file
      pStorage->Release();
   }
   else
      // could not create temporary file
      return false;

   // did we write successful to the file
   if( result )
   {
      // overwrite the current file (if exist) with the temporary file. 
      // We could also use the new Win2000 function ReplaceFile() to 
      // keep the attributes of the original file but apparently MoveFileEx
      // also keeps the attributes and we don't have to check if the 
      // file already exists. ReplaceFile() fails if the old file doesn't 
      // exist yet.

      if( ! MoveFileEx( rootStorageInfo.pwcsName, 
                        GetFullFilenamePath().c_str(), 
                        MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING ))
         result = false;
   }

   // if anything fails, delete temp file
   if( ! result )
   {
      // do we have a valid temp file name
      if( rootStorageInfo.pwcsName )
         DeleteFile( rootStorageInfo.pwcsName );
   }

   return result;
}


/*----------------------------------------------------------------------------
   Template::OpenFileForRead

   Open the template file for reading. This function is called from 
   TempLoadName(), TempLoadRemainder() and TempGetLogo().
   Call Release() on the storage object to close the file.

   Returns: root storage pointer or NULL if failed
----------------------------------------------------------------------------*/

IStorage* 
Template::OpenFileForRead()
{
   // open structure storage file with read access
   IStorage* pStorage = NULL;
   if( StgOpenStorageEx( GetFullFilenamePath().c_str(), 
                         STGM_READ | STGM_SHARE_DENY_WRITE | STGM_DIRECT,// STGM_SHARE_EXCLUSIVE 
                         STGFMT_STORAGE,
                         0,
                         NULL,
                         0,
                         IID_IStorage,
                         (void**)&pStorage ) == S_OK )
   {
      // verify the template version and return the storage object
      if( VerifyVersion( pStorage ))
         return pStorage;
      else
      {
         pStorage->Release();
         return NULL;
      }
   }

   return NULL;
}


/*----------------------------------------------------------------------------
   Template::VerifyVersion

   read the template version from the structore storage file and verify that
   it is the correct version.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::VerifyVersion( IStorage* pStorage )
{
   bool result = true;

   // open version stream
   IStream* pStreamVersion = FileHelpOpenStream( pStorage, 
                                                 IDS_TEMPLATE_FILE_VERSION );
   if( pStreamVersion )
   {
      // load template file version
      DWORD fileVersion = 0;
      if( FileHelpReadDWORD( pStreamVersion, fileVersion ))
      {
         // verify the version. Currently we have only one template file
         // version and we don't support any other version.
         // Should we change the file format in a later version then we
         // have to be able to load new and old versions.

         if( fileVersion != _TEMPLATE_FILE_VERSION_CURRENT )
            result = false;
      }
      else
         result = false;

      // close version stream
      pStreamVersion->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Template::SaveVersion

   Save the template file version to the structure storage file.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::SaveVersion( IStorage* pStorage )
{
   bool result = true;

   // create the version stream
   IStream* pVersionStream = FileHelpCreateStream(pStorage, 
                                                  IDS_TEMPLATE_FILE_VERSION);
   if( pVersionStream )
   {
      // save the current template file version to the stream
      if( ! FileHelpWriteDWORD(pVersionStream,_TEMPLATE_FILE_VERSION_CURRENT))
         result = false;

      // close version stream
      pVersionStream->Release();
   }
   else
      result = false;;

   return result;
}


/*----------------------------------------------------------------------------
   Template::IsReadOnly

   Checks if the template is read only. Before we try to save the template
   we check if the file is read only

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::IsReadOnly() const
{
   // get file attributes
   DWORD attributes = GetFileAttributes( GetFullFilenamePath().c_str());

   // check if the call was successful. This function gets also called 
   // when the file does not exist yet, in which case the get attibutes
   // function fails.
   if( attributes != INVALID_FILE_ATTRIBUTES )
   {
      // check if the read-only attribute is set
      if(( attributes & FILE_ATTRIBUTE_READONLY ) == FILE_ATTRIBUTE_READONLY )
         return true;
   }

   return false;
}


// subfunctions of Serialize() ...............................................
/*
   sub functions of Serialize(), write template data to the structure storage
   file. See TemplateFileFormat.txt for detail about the template file format.
*/

/*----------------------------------------------------------------------------
   Template::SerializeInfo

   Save the info stream to the template file

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::SerializeInfo( IStorage* pStorage )
{
   bool result = true;

   // create stream "Info"
   IStream* pStreamInfo = FileHelpCreateStream( pStorage,
                                                IDS_TEMPLATE_FILE_INFO );
   if( pStreamInfo )
   {
      // write the GUID of the device
      if( pStreamInfo->Write( &m_GUID, sizeof(GUID), NULL ) != S_OK )
         result = false;

      // write number of controls
      DWORD controlCount = m_ControlList.size();
      if( ! FileHelpWriteDWORD( pStreamInfo, controlCount ))
         result = false;

      // write template creator ID. The default creator ID is zero. If 
      // we find an optional registry key with a creator ID then we use
      // this creator ID

      DWORD creatorID = GetCreatorID();
      if( ! FileHelpWriteDWORD( pStreamInfo, creatorID ))
         result = false;

      // write template name
      if( ! FileHelpWriteString( pStreamInfo, m_Name ))
         result = false;

      // close stream "Info"
      pStreamInfo->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Template::SerializeControls

   Write all control data to the template file. 

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::SerializeControls( IStorage* pStorage )
{
   bool result = true;

   // create stream "Controls"
   IStream* pStreamControls = 
      FileHelpCreateStream( pStorage, IDS_TEMPLATE_FILE_CONTROLS );

   if( pStreamControls )
   {
      // for all controls
      int controlCount = m_ControlList.size();
      for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      {
         // ! Important: Save the control type first, so that we can 
         // instantiate the appropriate control when reading the data back !

         // save control type as a DWORD
         DWORD controlType = m_ControlList[controlIndex]->ControlGetType();
         if( ! FileHelpWriteDWORD( pStreamControls, controlType ))
         {
            result = false;
            break;
         }

         // serialize the control data to the stream
         if( ! m_ControlList[controlIndex]->ControlSerialize(pStreamControls))
         {
            result = false;
            break;
         }
      }

      // close stream "Controls"
      pStreamControls->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Template::SerializeLogo

   Check if there is an optional registry key with an creator ID and creator
   logo. If so then we load that logo and save it into the template file.
   The logo gets displayed in the template editor to identify certified
   templates.

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::SerializeLogo( IStorage* pStorage )
{
   DWORD creatorID = 0;
   std::wstring tempPath;
   bool success = false;

   // try to read the optional registry key for certified template 
   // manufacturers. The function returns false if the registry key doesn't 
   // exist. If the key doesn't exist then we just return 
   if( RegLoadTemplateLogoPath( tempPath, creatorID ))
   {
      // we already saved the creator ID in the info field so we only need
      // to save the logo file here. We save the logo file as a binary
      // png-file.

      // open the logo file
      HANDLE hLogoFile = CreateFile( tempPath.c_str(),
                                     GENERIC_READ,
                                     FILE_SHARE_READ,
                                     NULL,
                                     OPEN_EXISTING,
                                     0,
                                     NULL );

      if( hLogoFile != INVALID_HANDLE_VALUE )
      {
         // get the file size of the logo file
         DWORD fileSize = GetFileSize( hLogoFile, NULL );

         // double check result
         if(( fileSize != INVALID_FILE_SIZE ) && ( fileSize > 0 ))
         {
            // allocate buffer for file
            BYTE* pBuffer = new BYTE[fileSize];
            if( pBuffer )
            {
               // read the data from the logo file
               DWORD bytesRead = 0;
               if(( ReadFile(hLogoFile, pBuffer, fileSize,&bytesRead,NULL)) &&
                  ( bytesRead == fileSize ))
               {
                  // create stream "Logo"
                  IStream* pStream = 
                     FileHelpCreateStream( pStorage, 
                                           IDS_TEMPLATE_FILE_LOGO );
                  if( pStream )
                  {
                     // write the data to the logo stream
                     if( pStream->Write( pBuffer, fileSize, NULL ) == S_OK )
                        success = true;

                     // close logo stream
                     pStream->Release();
                  }
               }

               // free logo buffer
               delete[] pBuffer;
            }
         }

         // close logo file
         CloseHandle( hLogoFile );
      }
   }
   else
      // if the registry entry for the logo path does not exist then we
      // still return true, since that is a valid case.
      return true;

   return success;
}


// load functions ............................................................
/*
   load data from the template structure storage file
*/

/*----------------------------------------------------------------------------
   Template::LoadInfo

   Load the info data from the template file

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::LoadInfo( IStorage* pStorage, 
                    DWORD& controlCount ) // returned control count
{
   bool result = true;

   // open stream "Info"
   IStream* pStreamInfo = FileHelpOpenStream(pStorage,IDS_TEMPLATE_FILE_INFO);
   if( pStreamInfo )
   {
      // load the GUID
      ULONG bytesRead = 0;
      if(( pStreamInfo->Read( &m_GUID, sizeof(GUID), &bytesRead ) != S_OK ) ||
         ( bytesRead != sizeof(GUID)))
      {
         result = false;
      }

      // load number of controls
      if( ! FileHelpReadDWORD( pStreamInfo, controlCount ))
         result = false;

      // load creator ID, currently we don't use the creator ID but we 
      // keep it in the template file just in case
      DWORD tempCreatorID = 0;
      if( ! FileHelpReadDWORD( pStreamInfo, tempCreatorID ))
         result = false;

      // load template name
      if( ! FileHelpReadString( pStreamInfo, m_Name ))
         result = false;

      // close stream "Info"
      pStreamInfo->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Template::LoadControls

   Load all controls from the template file

   Returns: true or false
----------------------------------------------------------------------------*/

bool 
Template::LoadControls( IStorage* pStorage, 
                        DWORD controlCount ) // control count from info stream
{
   bool result = true;

   // open stream "Controls"
   IStream* pStreamControls = FileHelpOpenStream(pStorage, 
                                                 IDS_TEMPLATE_FILE_CONTROLS);
   if( pStreamControls )
   {
      // for all controls
      for( DWORD controlIndex = 0;controlIndex < controlCount; controlIndex++ )
      {
         // The first element for each control is always the control
         // type. We have to read the type first so that we can create
         // the correct control object.

         Control* pControl = NULL;

         // read control type
         DWORD controlType = 0;
         if( FileHelpReadDWORD( pStreamControls, controlType ))
         {
            // check the control type
            switch( controlType )
            {
               case CT_SELECT:
                  // create select control, check result below
                  pControl = new SelectControl;
                  break;

               case CT_FADER:    
                  // create fader control, check result below
                  pControl = new FaderControl;
                  break;

               case CT_MODE:     
                  // create mode control, check result below
                  pControl = new ModeControl;
                  break;

               case CT_SWITCH:   
                  // create switch control, check result below
                  // !!!! todo
                  break;

               case CT_POSITION: 
                  // create position control, check result below
                  pControl = new PositionControl;
                  break;

               case CT_LABEL:    
                  // create label control, check result below
                  // !!!! todo
                  break;

               default:
                  // invalid control type
                  result = false;
                  break;
            }
         }
         else
            result = false;

         // did we successful create a control
         if( result && pControl )
         {
            // load the control data from the stream

            // ! Todo: The template file currently has no version control.
            // If we decide to add different template versions, then we
            // might need to change this logic here !

            if( pControl->ControlLoad( pStreamControls, 
                                       0 ))  // version is ignored currently

               // add the control to the control vector
               m_ControlList.push_back( pControl );
            else
            {
               // set error flag and delete control
               result = false;
               delete pControl;
               break;
            }               
         }
         else
         {
            result = false;
            break;
         }
      }

      // close stream "Controls"
      pStreamControls->Release();
   }
   else
      result = false;

   return result;
}


/*----------------------------------------------------------------------------
   Template::GetCreatorID

   This function checks if the optional registry key for a template creator
   exists. If it exists the function returns that creator ID, if the registry
   key does not exist then the function returns the default creator ID of
   zero.

   Returns: creator ID
----------------------------------------------------------------------------*/

DWORD 
Template::GetCreatorID()
{
   DWORD creatorID = 0;
   std::wstring tempPath;

   // try to read the optional registry key for certified template 
   // manufacturers. The function returns false if the registry key doesn't 
   // exist.

   if( RegLoadTemplateLogoPath( tempPath, creatorID ))
      return creatorID;

   // by default we return the creator ID zero
   return 0;
}


/*----------------------------------------------------------------------------
   Template::GetFullFilename

   Return the full file name path for the template file.

   Returns: full file name path
----------------------------------------------------------------------------*/

std::wstring 
Template::GetFullFilenamePath() const
{
   // create file name using the following path:
   // "templatePath\foldername\filename"

   std::wstring fullFilename = m_TemplatePath.c_str();
   fullFilename += TEXT("\\");
   fullFilename += m_Foldername.c_str();
   fullFilename += TEXT("\\");
   fullFilename += m_Filename.c_str();

   return fullFilename;
}


/*----------------------------------------------------------------------------
   Template::ValidateControls

   This function gets called from TempValidateControls(). We validate the
   given controls. For more information about validating see description of
   TempValidateControls()

   Returns: true if every control has a unique DMX channel, false if 
            one or more controls occupy the same channel.
----------------------------------------------------------------------------*/

bool 
Template::ValidateControls( const std::vector< Control* >& controls )
{
   std::vector<int> allChannels;

   // get all used channels from the control
   int controlCount = controls.size();
   for( int controlIndex = 0; controlIndex < controlCount; controlIndex++ )
      // get the used channel from the control, set the 'getSubcontrols'
      // flag to false so any mode controls don't return overlapping 
      // sub controls
      controls[controlIndex]->ControlGetUsedChannels(allChannels, false);

   std::vector<int> existingChannels;

   // for all channels
   int channelCount = allChannels.size();
   for( int channelIndex = 0; channelIndex < channelCount; channelIndex++ )
   {
      // get the DMX channel
      int channel = allChannels[channelIndex];

      // compare with all already checked channels
      int existingCount = existingChannels.size();
      for(int existingIndex = 0;existingIndex < existingCount;existingIndex++)
      {
         // if the channel matches an already checked channel then we have
         // overlapping channels and we return false
         if( channel == existingChannels[existingIndex] )
            return false;
      }

      // add the channel to the vector for already checked channels
      existingChannels.push_back( channel );
   }

   // all channels are unique, return true
   return true;

}





