Feature: plant lamp trigger by window

  Scenario: plant lamp is turned on based on window luminosity
     Given window luminosity is below threshold
      When plant is activated
      Then plant luminosity is above the min value