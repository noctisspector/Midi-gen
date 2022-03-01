#pragma once
#include "../Music.h"
#include "Scale.h"
#include "../Note.h"
#include <vector>

struct ScaleWeight
{
    int position;
    int weight;
};

struct MotifData
{
    std::vector<ScaleWeight>    scale_weights;
    int                         pitch;
    double                      duration;
};

struct MotifParams
{
    double smooth;
    double volitile;
};


class Motif : public Music
{

private:
    std::vector<MotifData> motifData;
    std::vector<Motif*>    variations;
    MotifParams            params;
    double                 min_duration;

    void                generate        ();

public:
                        Motif           (MotifParams params_, double min_duration_);
                        Motif           (const Motif *motif);
    virtual void        toMidi          (smf::MidiFile &midiFile) const override;
    std::vector<Note*>* getNotes        (const Scale *scale, double time) const;  
    void                makeVariations  (int count); 
    Motif*              getVariation    (int index) const;
    double              getDuration     () const;

};
