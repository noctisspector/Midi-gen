#include "Motif.h"
#include "cassert"
#include <random>
#include <ctime>

static const int DEFAULT_RANGE = Motif::DEFAULT_RANGE;

/*
Populates motifData with a random melody. 
*/
void Motif::generate()
{

    // Initialize weights to 1
    std::vector<ScaleWeight> initialWeights;
    int range = (int)(DEFAULT_RANGE * params.range);

    for (int position = -range; position <= range; position++)
        {
            ScaleWeight newWeight = {position, 1};
            initialWeights.push_back(newWeight);
        }

    // Apply initial rough modifier
    

    double time;

    while (time <= min_duration)
    {

        // TODO

    }

}

/*
Generates the next pitch of a note in a melody.
*/
int Motif::nextPitch(MotifData motifData) const
{
    return weightedRandom(motifData.scaleWeights);
}

/*
Generates the next duration of a note in a melody.
*/
double Motif::nextDuration(MotifData motifData) const
{

    return 0;

}

/*
Generates weighted random numbers for pitch and duration generation
*/
int Motif::weightedRandom(std::vector<ScaleWeight> scaleWeights)
{

    // Find sum of weights

    double weightSum = 0;

    for (ScaleWeight &i : scaleWeights)
        weightSum += i.weight;

    // Get random number
    double rand = fRand(0, weightSum);

    // Subtract off weights
    for (ScaleWeight &i : scaleWeights)
    {

        if (rand < i.weight)
            return i.position;

        rand -= i.weight;

    }

    // Should never reach this
    assert(false);
    return 0;

}

double Motif::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
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

std::vector<Note*>* Motif::getNotes(const Scale *scale, double time, int variation) const
{
    return getVariation(variation)->getNotes(scale, time);
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

int Motif::getMotifSize() const
{
    return static_cast<int>(motifData.size());
}