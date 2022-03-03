
#include "lib/MidiFile.h"
#include "Music.h"
#include "gen/Motif.h"
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace smf;
int main (int argc, char **argv)
{

    // Random seed
    srand(static_cast<unsigned>(time(0)));

    MidiFile midiFile;
    Music::initMidi(midiFile);

    

    Music::endMidi(midiFile);

    return 0;

}