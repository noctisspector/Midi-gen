#include "Note.h"
#include "Music.h"
#include "Scale.h"
#include <vector>

static std::vector<int> b3p = { 0, 2, 4, 6, 7, 9, 11 };
static std::vector<int> b2p = { 0, 2, 4, 5, 7, 9, 11 };
static std::vector<int> b1p = { 0, 2, 4, 5, 7, 9, 10 };
static std::vector<int> b0  = { 0, 2, 3, 5, 7, 9, 10 };
static std::vector<int> b1n = { 0, 2, 3, 5, 7, 8, 10 };
static std::vector<int> b2n = { 0, 1, 3, 5, 7, 8, 10 };
static std::vector<int> b3n = { 0, 1, 3, 5, 6, 8, 10 };

Scale::Scale()
    : brightness(2), start_pitch(30) { };

Scale::Scale(int brightness_, int start_pitch_)
    : brightness(brightness_), start_pitch(start_pitch_) { };

static int scaleData(int brightLevel, int position)
{

    std::vector<std::vector<int>> levels = 
        {b3n, b2n, b1n, b0, b1p, b2p, b3p};

    int octave = position / 7;
    position %= 7;
    brightLevel += 3;

    return levels[brightLevel][position] + octave * 12;

}

Note *Scale::grabNote(int position) const
{

    return grabNote(position, 0);

}

Note *Scale::grabNote(int position, int start) const
{

    return new Note(start_pitch + scaleData(brightness, position), 1, start);

}

std::vector<Note*> *Scale::grabChord(int inversion) const
{

    std::vector<int> inv_positions = {0, 2, 4};
    std::vector<Note*> *out = new std::vector<Note*>;

    for (int &i : inv_positions)
    {

        for (int _ = 0; _ < inversion; _++)
        {
            i += 2 * inversion;
            if (i > 4) i = 0;
        }

        out->push_back(grabNote(i));

    }

    return out;

}

std::vector<Note*> *Scale::grabChord() const
{ return Scale::grabChord(0); }

void Scale::toMidi(smf::MidiFile &midiFile) const
{

    int line = 0;

    for (int i = 0; i < 30; i++)
    {

        Note *note = grabNote(i, line);
        note->toMidi(midiFile);

        delete note;
        line += 2;

    }

}