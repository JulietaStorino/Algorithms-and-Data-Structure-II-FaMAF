#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "weather_utils.h"

int lower_minimum_temperature(WeatherTable a){
    int temperature = a[0][0][0]._min_temp;
    for(unsigned int year = 0u; year < YEARS; ++year){
        for(unsigned int month = 0u; month < MONTHS; ++month){
            for(unsigned int day = 0u; day < DAYS; ++day){
                if(a[year][month][day]._min_temp < temperature){
                    temperature = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return temperature;
}

void higher_maximum_temperature(WeatherTable a, int output[YEARS]){
    for(unsigned int year = 0u; year < YEARS; ++year){
        int temperature = a[year][0][0]._max_temp;
        for(unsigned int month = 0u; month < MONTHS; ++month){
            for(unsigned int day = 0u; day < DAYS; ++day){
                if(a[year][month][day]._max_temp > temperature){
                    temperature = a[year][month][day]._max_temp;
                }
            }
        }
        output[year] = temperature;
    }
}

void highest_monthly_rainfall(WeatherTable a, month_t output[YEARS]){
    for(unsigned int year = 0u; year < YEARS; ++year){
        unsigned int highest_rainfall = 0u, rainfall_month = 0u;
        for(unsigned int month = 0u; month < MONTHS; ++month){
            unsigned int rainfall_acumulator = 0u;
            for(unsigned int day = 0u; day < DAYS; ++day){
                rainfall_acumulator += a[year][month][day]._rainfall;
            }
            if(rainfall_acumulator > highest_rainfall){
                    highest_rainfall = rainfall_acumulator;
                    rainfall_month = month;
            }
        }
        output[year] = rainfall_month;
    }
}