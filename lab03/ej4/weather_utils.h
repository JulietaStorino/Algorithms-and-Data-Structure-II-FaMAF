#ifndef WEATHER_UTILS_H
#define WEATHER_UTILS_H

#include "array_helpers.h" 

int lower_minimum_temperature(WeatherTable a);

void higher_maximum_temperature(WeatherTable a, int output[YEARS]);

void highest_monthly_rainfall(WeatherTable a, month_t output[YEARS]);

#endif