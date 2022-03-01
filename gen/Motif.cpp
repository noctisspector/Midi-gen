#include "Motif.h"
#include "cassert"
#include <random>

void Motif::generate()
{

    double time;

    while (time <= min_duration)
    {

        // TODO

    }

}

Motif::Motif(MotifParams params_, double min_duration_)
    : min_duration(min_duration_), params(params_)
{
    generate();
}

Motif::Motif(const Motif *motif)
    : motifData(motif->motifData), variations(motif->variations),
      min_duration(motif->min_duration), params(motif->params) { };

void Motif::toMidi(smf::MidiFile &midiFile) const
{

    Scale *scale = new Scale(-1, 40);
    std::vector<Note*>* notes = getNotes(scale, 0);

    for (Note *&note : *notes)
        note->toMidi(midiFile);

    delete scale;
    delete notes;

}

std::vector<Note*>* Motif::getNotes(const Scale *scale, double time) const
{

    std::vector<Note*>* output = new std::vector<Note*>;
    
    for (MotifData data : motifData)
    {

        Note *note = new Note
        (
            data.pitch,
            data.duration,
            time
        );

        output->push_back(note);

        time += data.duration;

    }

    return output;

}

void Motif::makeVariations(int count)
{

    for (int _ = 0; _ < count; _++)
    {

        double newSmooth = 0;
        double newVolitile = 0;

        MotifParams newParams = 
        {
            newSmooth,
            newVolitile
        };

        Motif *motif = new Motif(newParams, min_duration);

        // TODO

        variations.push_back(motif);

    }

}

Motif* Motif::getVariation(int index) const
{

    assert(index >= 0);
    assert(index < static_cast<int>(variations.size()));
    return variations[index];

}

double Motif::getDuration() const
{

    double total = 0;

    for (MotifData data : motifData)
        total += data.duration;

    return total;

}