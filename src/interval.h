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

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+INF, -INF);
const Interval Interval::universe = Interval(-INF, +INF);
