//---------------------------------------------------------------------
//
//	File:	TCDCue.cpp
//
//	Author:	Gene Z. Ragan
//
//	Date:	01.26.98
//
//	Desc:
//
//	Copyright ©1998 mediapede Software
//
//---------------------------------------------------------------------

// Includes
#include "BuildApp.h"

#include <app/Application.h>
#include <support/Debug.h>

#include "AppConstants.h"
#include "AppMessages.h"
#include "BaseCueChunk.h"
#include "ResourceManager.h"

#include "TBitmapView.h"
#include "TCueView.h"
#include "TCDCue.h"
#include "TCueTimeText.h"
#include "TCueChannel.h"
#include "TCueSheetView.h"

//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//

TCDCue::TCDCue(int16 id, TCueChannel* parent, BRect bounds, BPoint point,  long startTime) :
	TCueView(id, parent, bounds, point, startTime, "CDCue")
{
	// Perform default initialization
	Init();
}


//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//	Construct from a CueChunk

TCDCue::TCDCue(BaseCueChunk* theChunk, TCueChannel* parent, BRect bounds) :
	TCueView(theChunk, parent, bounds, "CDCue")
{
	// Perform default initialization
	Init(theChunk);
}


//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//	Construct from a BMessage
//

TCDCue::TCDCue(BMessage* theMessage) : TCueView(theMessage)
{
	// Load cue icon
	LoadCueIcon();
}


//---------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------
//
//

TCDCue::~TCDCue()
{
}


//---------------------------------------------------------------------
//	Init
//---------------------------------------------------------------------
//
//	Perform default initialization tasks

void TCDCue::Init()
{
	// Set up default duration
	fDuration = 1000;

	// Set up default settings
	fIsLocked = false;

	fIsSelected = false;

	fLowColor               = kWhite;
	fHighColor      = kBlack;
	fIsPrepared     = false;
	fIsPlaying      = false;

	fHasDuration    = true;

	/*
	   bool			fCanStretch;			// true if cue is stretchable
	   bool			fCanWindow;			// true if cue can window into file
	   bool			fCanLoop;				// true if cue can loop
	   bool			fCanEnvelope;			// true if cue can volume envelope
	   bool			fHasDuration;			// true if cue has a duration
	   bool			fIsVisible;			// true if cue is visual
	   bool			fCanCrop;				// true if cue can visual crop
	   bool			fCanTransition;		// true if cue can transition
	   bool			fCanTransitionOut;		// true if cue can transition out
	   bool			fCanPath;				// true if cue can path
	   bool			fHasEditor;			// true if cue has internal editor

	   BRect			fOriginalArea;			// Visual size of untouched image
	   BRect			fArea;					// Total visual area (in stage coords).
	   BRect			fCroppedArea;			// Crop area (in itsArea coords).
	 */

	// Default initialization
	TCueView::Init();

	// Add the cue to the cue channel
	if ( fChannel->CanInsertCue(this, fInsertPoint, true)) {
		fChannel->AddChild(this);
		fChannel->InsertCue(this, fInsertPoint, fInsertTime);
		Select();
	}

	// We are now fully instantiated
	fIsInstantiated = true;

}


//---------------------------------------------------------------------
//	Init
//---------------------------------------------------------------------
//
//	Init from BaseCueChunk
//

void TCDCue::Init(BaseCueChunk* theChunk)
{
	TCueView::Init(theChunk);
}


#pragma mark -
#pragma mark === Archiving Functions ===


//---------------------------------------------------------------------
//	Instantiate
//---------------------------------------------------------------------
//
//

BArchivable* TCDCue::Instantiate(BMessage* archive)
{
	if ( validate_instantiation(archive, "TCDCue") )
		return new TCDCue(archive);

	return NULL;
}


//---------------------------------------------------------------------
//	Archive
//---------------------------------------------------------------------
//
//

status_t TCDCue::Archive(BMessage* data, bool deep) const
{

	status_t myErr;

	Looper()->Lock();

	// Start by calling inherited archive
	myErr = TCueView::Archive(data, deep);

	if (myErr == B_OK) {
		// Add ourselves to the archive
		data->AddString("class", "TCDCue");
	}

	Looper()->Unlock();

	return myErr;
}

#pragma mark -
#pragma mark === Drawing Functions ===

//---------------------------------------------------------------------
//	Draw
//---------------------------------------------------------------------
//
//

void TCDCue::Draw(BRect updateRect)
{
	// Save colors
	rgb_color saveColor = HighColor();

	// Restore color
	SetHighColor(saveColor);

	// Pass up to parent
	TCueView::Draw(updateRect);
}

//---------------------------------------------------------------------
//	OpenEditor
//---------------------------------------------------------------------
//
//	Open data editor if cue can edit it's data
//

void TCDCue::OpenEditor()
{

}


#pragma mark -
#pragma mark === Utility Functions ===

//---------------------------------------------------------------------
//	LoadCueIcon
//---------------------------------------------------------------------
//
//	Load cues identifying icon
//

void TCDCue::LoadCueIcon()
{
	BBitmap* cueIcon = NULL;

	cueIcon = GetCicnFromResource("CDCue");

	if (cueIcon) {
		BRect area(0, 0+(kTimeTextHeight+kTimeTextOffset+3), kCueIconWidth-1, (kCueIconWidth-1)+(kTimeTextHeight+kTimeTextOffset+3));
		area.OffsetBy(kResizeZoneWidth+5, 0);
		fCueIcon = new TBitmapView(area, "CDCue", cueIcon, false);
		AddChild(fCueIcon);
	}
}
