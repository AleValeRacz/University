#include "Domain.h"


double ElectricEngine::calculate_price() const
{
    return base_price + autonomy * 0.01;
}


string ElectricEngine::toString() const
{
    stringstream ss;
    ss << "Engine Type: Electric, Fuel Type: " << fuel_type << ", Autonomy: " << autonomy << " km";
    return ss.str();
}