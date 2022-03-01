
#include "lib/MidiFile.h"
#include "Music.h"
#include "Note.h"

Note::Note()
    : pitch(40), duration(5), time(0) { };

Note::Note(int pitch_, double duration_, double time_)
    : pitch(pitch_), duration(duration_), time(time_) { };

Note::Note(int pitch_)
    : pitch(pitch_), duration(1), time(0) { };

void Note::toMidi(smf::MidiFile &midiFile) const
{

    int starttick =             int(Music::applyTpq(time));
    int endtick   = starttick + int(Music::applyTpq(duration));

    midiFile.addNoteOn (0, starttick, 0, pitch, 50);
    midiFile.addNoteOff(0, endtick,   0, pitch);

}