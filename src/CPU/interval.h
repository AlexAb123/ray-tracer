#pragma once

#include "utils.h"

class Interval {

private:
    double m_min, m_max;

public:

    Interval() : m_min(+INF), m_max(-INF) {}
    Interval(double min, double max) : m_min(min), m_max(max) {}

    double min() { return m_min; }
    double max() { return m_max; }

    double size() const {
        return m_max - m_min;
    }

    bool contains(double x) const {
        return m_min <= x && x <= m_max;
    }

    bool surrounds(double x) const {
        return m_min < x && x < m_max;
    }

    // Clamps 'x' to be in between min and max
    double clamp(double x) const {
        if (x < m_min) return m_min;
        if (x > m_max) return m_max;
        return x;
    }

    static const Interval empty, universe;
};
