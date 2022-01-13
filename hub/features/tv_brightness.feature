Feature: TV auto-brightness
    Scenario Outline: TV brightness is set based on window luminosity
     Given TV brightness is set to <X>, window luminosity to <Y> and base luminosity to <Z>
      When automation rules are triggered
      Then TV brightness is set to max(10 - <Y>/10 + <Z>, <Z>) <= 10
     Examples:
      | X  | Y  | Z  |
      | 3  | 20 | 1  |
      | 4  | 70 | 0  |