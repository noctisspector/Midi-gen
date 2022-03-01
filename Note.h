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
                    Note        (const Note *note);
    virtual void    toMidi      (smf::MidiFile &midiFile) const override;
    void            setPitch    (int pitch_);
    void            setDuration (int duration_);
    void            setTime     (int time_);
    void            octave      (int octaves);

};