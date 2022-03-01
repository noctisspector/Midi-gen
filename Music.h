#pragma once
#include "lib/MidiFile.h"

class Music
{

private:
    static int tpq;

public:

    static void     initMidi    (smf::MidiFile &midiFile);
    static void     endMidi     (smf::MidiFile &midiFile);
    virtual void    toMidi      (smf::MidiFile &midiFile) const = 0;
    static int      getTpq      ();
    static double   applyTpq    (double value);


};