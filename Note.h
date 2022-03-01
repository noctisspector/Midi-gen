#pragma once
#include "lib/MidiFile.h"
#include "Music.h"

class Note : public Music
{

private:
    int     pitch;
    double  duration;
    double  time;

public:
                    Note        ();
                    Note        (int pitch_, double duration_, double time_);
                    Note        (int pitch_);
    virtual void    toMidi      (smf::MidiFile &midiFile) const override;

};