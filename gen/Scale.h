#pragma once
#include "../Note.h"
#include "../Music.h"
#include <vector>

class Scale : public Music
{

private:
    int brightness; // From +3 to -3
    int start_pitch;

public:
                            Scale       ();
                            Scale       (int brightness_, int start_pitch_);
                            Scale       (const Scale *scale);
    Note                    *grabNote   (int position) const;
    Note                    *grabNote   (int position, int start) const;
    std::vector<Note*>      *grabChord  () const;
    std::vector<Note*>      *grabChord  (int inversion) const;
    virtual void            toMidi      (smf::MidiFile &midiFile) const override;

};