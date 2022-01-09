Feature: Plant lamp trigger by window

  Scenario Outline: Plant lamp is turned on based on window luminosity
     Given Plant lamp is off and luminosity is 24
      When Luminosity is 10
      Then Turn on the plant lamp