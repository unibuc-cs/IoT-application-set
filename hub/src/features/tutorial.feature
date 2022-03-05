Feature: showing off behave

  Scenario: run a simple test
     Given setting up window to temperature: 33
      When we set smartkettle rpm to windwow temperature
      Then check if change was set