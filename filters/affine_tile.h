#pragma once

#include "../filter.h"
#include "../image.h"
#include <cstdint>

class AffineTileFilter : public BaseFilter {
public:
    static constexpr double AfineCoef = 0.7071;
    explicit AffineTileFilter(double a = AfineCoef, double b = -AfineCoef, double c = AfineCoef, double d = AfineCoef,
                              double tx = 0.0, double ty = 0.0);

    void Apply(Image& image) override;

private:
    double a_;
    double b_;
    double c_;
    double d_;
    double tx_;
    double ty_;

    double Mod(double value, double modulus) const;
};
