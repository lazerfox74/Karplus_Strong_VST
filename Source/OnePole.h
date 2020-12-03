/*
  ==============================================================================

    OnePole.h
    Created: 1 Dec 2020 8:17:02pm
    Author:  josh

  ==============================================================================
*/

#pragma once
#include <Math.h>

class CParamSmooth
{
public:
    CParamSmooth(float smoothingTimeInMs, float samplingRate)
    {
        const float c_twoPi = 6.283185307179586476925286766559f;

        a = (-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        z = 0.0f;
    }

    ~CParamSmooth()
    {

    }

    inline float process(float in)
    {
        z = (in * b) + (z * a);
        return z;
    }

private:
    float a;
    float b;
    float z;
};