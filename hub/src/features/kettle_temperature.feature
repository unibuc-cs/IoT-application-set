Feature: Kettle's temperature
    Scenario Outline: Kettle's temperature is set based on window's temperature
     Given window's temperature is <X>
      When automation rules are triggered for kettle
      Then kettle's temperature is set to <Y>
     Examples:
      | X  | Y  |
      | 15 | 40 |
      | 9  | 43 |
      | 5  | 55 |
      | 0  | 70 |
      | -3 | 79 |
      | -5 | 85 |