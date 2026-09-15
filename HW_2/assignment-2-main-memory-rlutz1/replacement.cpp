#include "src.hpp"

// Delete First Frame in linked list
// Return how many frames you stepped through to find replacement frame
int fifo(FrameList* active_frames, FrameList** frame_to_remove_ptr)
{
	*frame_to_remove_ptr = active_frames; // head of the list is first in

	return 1; // only one frame to consider due to how list is constructed

}

// Delete Least Recently Used Frame
// frame->idx shows how recently frame has been used
// higher number == more recently used
// Return how many frames you stepped through to find replacement frame
int lru(FrameList* active_frames, FrameList** frame_to_remove_ptr)
{
  int num_frames_traversed = 1; // at minimum always 1
  FrameList* remove_frame = active_frames; // set to head, and use for return
  int min = active_frames->idx; // grab the initial index, assume it's the smallest

  while (min > 0 && active_frames->next) {
    active_frames = active_frames->next; // go to next frame
    if (active_frames->idx < min) { // if we found a new min
      min = active_frames->idx; // set the min
      remove_frame = active_frames; // update the frame to remove
    }
     
    num_frames_traversed++; // increment frames traversed
  }

  *frame_to_remove_ptr = remove_frame; // return this frame
  return num_frames_traversed; // return how many traversed
}

// Step through active frames, starting with first element in linked list (passed as arg)
// Remove first active frame with frame->clock_bit set to zero
// Reset any clock_bit as you traverse over a frame
// Return how many frames you stepped through to find replacement frame
int clock_lru(FrameList* active_frames, FrameList** frame_to_remove_ptr)
{

  int num_frames_traversed = 1; // at minimum always 1
  FrameList* head = active_frames; // for clock cycling
  int clock_bit = active_frames->clock_bit; // grab the initial clock bit
					    
  while (clock_bit) { // while clock bit high
    active_frames->clock_bit = 0; // clock bit must be 1, set to 0


    active_frames = active_frames->next; // go to next frame

    if (!active_frames) {
      active_frames = head; // circle around the clock
    }


    clock_bit = active_frames->clock_bit; // grab the new clock bit
    num_frames_traversed++; // increment num frames

  }

  *frame_to_remove_ptr = active_frames; // return the current frame, loop has broken
  return num_frames_traversed; // return how many traversed

}
