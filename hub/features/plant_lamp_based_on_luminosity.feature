Feature: plant lamp trigger by window

  Scenario: plant lamp is turned on based on window luminosity
     Given window luminosity is below threshold
      When plant is activated
      Then plant luminosity is above the min value

  Scenario: plant lamp is turned off on a hot day
     Given plant temperature is above 30 degrees
      When automation rules are ran for plant
      Then plant luminosity is unchanged after halving