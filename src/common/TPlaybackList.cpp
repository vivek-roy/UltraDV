//---------------------------------------------------------------------
//
//	File:	TPlaybackList.cpp
//
//	Author:	Gene Z. Ragan
//
//	Date:	03.17.98
//
///	Desc:	List that contains cue events
//
//
//
//	Copyright ©1998 mediapede Software
//
//---------------------------------------------------------------------

// Includes
#include "BuildApp.h"

#include "TPlaybackList.h"


// Constants


//
//  TPlaybackList Class
//


//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//

TPlaybackList::TPlaybackList() : BList()
{
}


//---------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------
//
//

TPlaybackList::~TPlaybackList()
{

	int32 totalItems = CountItems();
	for ( int32 index = 0; index < totalItems; index++) {
		TPlaybackEvent* playbackEvent = (TPlaybackEvent*)ItemAt(index);

		// We have an event.  Clean up all items in it.
		if (playbackEvent) {
			int32 totalCueEvents = playbackEvent->fCueEvents.CountItems();
			for ( int32 cueIndex = 0; cueIndex < totalCueEvents; cueIndex++) {
				TCueEvent* cueEvent = (TCueEvent*)playbackEvent->fCueEvents.ItemAt(cueIndex);

				// Clean up cue events
				if (cueEvent) {
					int32 totalEvents = cueEvent->fEvents.CountItems();
					for ( int32 eventIndex = 0; eventIndex < totalEvents; eventIndex++) {
						BMessage* message = (BMessage*)cueEvent->fEvents.ItemAt(eventIndex);
						if (message) {
							delete message;
							message = NULL;
						}
					}

					delete cueEvent;
				}

			}
			// Clean up playbackEvent
			free(playbackEvent);
		}
	}

}


//
//  PlaybackEvent Class
//
//	Contains reference time and list of cues that have an event at
//	the reference time.

//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//

TPlaybackEvent::TPlaybackEvent()
{
}


//---------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------
//
//

TPlaybackEvent::~TPlaybackEvent()
{
}



//
//  CueEvent Class
//
//
//	Contains a cue and a list of all events that happen at
//	the reference time.
//

//---------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------
//
//

TCueEvent::TCueEvent()
{
}


//---------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------
//
//

TCueEvent::~TCueEvent()
{
}
