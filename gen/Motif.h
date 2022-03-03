#pragma once
#include "../Music.h"
#include "Scale.h"
#include "../Note.h"
#include <vector>

struct ScaleWeight
{
    int     position;
    double  weight;
};

struct MotifData
{
    std::vector<ScaleWeight>    scaleWeights;
    int                         pitch;
    double                      duration;
};

struct MotifParams
{
    double rough;       // Non-prevalence of "passing" notes
    double volitile;    // Tendency to jump large gaps from last note
    double repeative;   // Scaling factor for remembering previous notes
    double range;       // Multiplier for DEFAULT_RANGE
};


class Motif : public Music
{

private:
    std::vector<MotifData>  motifData;
    std::vector<Motif*>     variations;
    MotifParams             params;
    double                  min_duration;

    const int               TRIAD_POSITIONS[3]  = {0, 2, 4};

    void                    generate            ();
    int                     nextPitch           (MotifData motifData) const;
    double                  nextDuration        (MotifData motifData) const;
    static int              weightedRandom      (std::vector<ScaleWeight> scaleWeights);
    static double           fRand               (double fMin, double fMax);

public:
                            Motif               (MotifParams params_, double min_duration_);
                            Motif               (const Motif *motif);
    virtual void            toMidi              (smf::MidiFile &midiFile) const override;
    std::vector<Note*>*     getNotes            (const Scale *scale, double time) const;  
    std::vector<Note*>*     getNotes            (const Scale *scale, double time, int variation) const;  
    void                    makeVariations      (int count); 
    Motif*                  getVariation        (int index) const;
    double                  getDuration         () const;
    int                     getMotifSize        () const;

    static const int        DEFAULT_RANGE       =  12;

};
