# Arduino hydroponics system

The project creates a system to measure water temperature and conductivity in hydroponics. These metrics are important to measure because they directly control how the plant grows.

## Purpose

Water temperature has an impact on oxygen availability. Cool water holds more dissolved oxygen, and as it warms, the oxygen drops rapidly, which can suffocate root systems.  Additionally, warm water with low oxygen levels creates ground for pathogens that can harm plant growth. If the water is too cold, the plant metabolism slows the enzyme activity and nutrient transports. Most crops thrive in a temperature between 18-21 degrees Celsius.

Conductivity measures the concentration of dissolved mineral salts in the solution. If the salt concentration is too high, water is pulled out of root cells, causing leaf burn and root damage. If the conductivity is low, plants cannot get sufficient nutrients, leading to stunted development.

## Technical specification

The conductivity is measured in a range from 0-1000 ppm. With a measurement accuracy of ±5 % at a temperature of 25 degrees Celsius. The temperature is measured within -55 to +125 degrees Celsius with an accuracy of 0.2 degrees Celsius.