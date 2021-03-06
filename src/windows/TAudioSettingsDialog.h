//---------------------------------------------------------------------
//
//	File:	TAudioSettingsDialog.h
//
//	Author:	Gene Z. Ragan
//
//	Date:	05.27.98
//
//
//	Copyright ©1998 mediapede software
//
//---------------------------------------------------------------------

#ifndef __TAUDIOSETTINGSDIALOG_H__
#define __TAUDIOSETTINGSDIALOG_H__

// Forward Declarations
class TAudioSettingsView;
class TAudioSettingsTabView;

// Class definitions
class TAudioSettingsDialog: public BWindow
{
	public:
		TAudioSettingsDialog(BRect bounds);
		
		void	MessageReceived(BMessage* message);	
		bool 	QuitRequested();
						
	private:	
		// Member Functions	
		void		Init();	
		
		// Member Variable
		TAudioSettingsView		*fBGView;
		TAudioSettingsTabView 	*fTabView;
};

#endif
