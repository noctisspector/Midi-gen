
#include "lib/MidiFile.h"
#include "Music.h"
#include "Note.h"
#include "Scale.h"
#include <iostream>
#include <string>

using namespace smf;
int main (int argc, char **argv)
{

    MidiFile midiFile;
    Music::initMidi(midiFile);

    Scale *scale = new Scale(2, 40);
    scale->toMidi(midiFile);

    delete scale;

    Music::endMidi(midiFile);

    return 0;

}