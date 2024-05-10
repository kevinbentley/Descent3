/*
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WEATHER_H
#define WEATHER_H

#define WEATHER_FLAGS_RAIN 1
#define WEATHER_FLAGS_LIGHTNING 2
#define WEATHER_FLAGS_SNOW 4

#define MAX_RAIN_INTENSITY 50
#define MAX_SNOW_INTENSITY 200

struct weather {
  int flags; // see weather flags, above

  float snow_intensity_scalar; // how hard it is snowing
  float rain_intensity_scalar; // how hard its raining
  int rain_color;              // the color of the rain
  int lightning_color;         // the color of the lightning
  int sky_flash_color;         // the color of the sky when lightning occurs

  uint8_t lightning_sequence;

  float last_lightning_evaluation_time;
  float lightning_interval_time;
  int lightning_rand_value;

  int snowflakes_to_create;

};

extern weather Weather;

// resets the weather so there is nothing happening
void ResetWeather();

// does all the weather stuff that is going to be done for this frame
void DoWeatherForFrame();

// Sets the state of the rain to on or off, plus sets the intensity of the rain (0 to 1)
void SetRainState(int on, float intensity);

// Sets the state of lightning to on or off, plus allows the setting of how often to check
// for lightning and the randomness at which lightning happens
void SetLightningState(int on, float interval_time, int randval);

// Sets the state of the snow to on or off, plus sets the intensity of the snow (0 to 1)
void SetSnowState(int on, float intensity);

#endif
