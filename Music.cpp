
#include "Music.h"

using namespace smf;

static const std::string FILENAME = "out.midi";
int Music::tpq;

void Music::initMidi(MidiFile &midiFile)
{

    midiFile.addTimbre(0, 0, 0, 0);
    tpq = midiFile.getTPQ();

}

void Music::endMidi(MidiFile &midiFile)
{

    midiFile.sortTracks();
    midiFile.write(FILENAME);

}

int Music::getTpq()
{
    return tpq;
}

double Music::applyTpq(double value)
{
    return value / 4.0 * tpq;
}
