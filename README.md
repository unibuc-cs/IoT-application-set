# IoT Dataset - Hub App
Hub App for the IoT Dataset
  
This is the repository for the hub app of the IoT Dataset project. 
  
For each IoT app in the Dataset, openapi-generator will be run, and the app-api-client will be generated. 
  
`app.py` is the hub app, that will import all the generated app-api-clients, and orchestrate different information flows between them. 

## Prerequisites

To generate new app-api-clients you will need to follow [the instalation instructions](https://github.com/OpenAPITools/openapi-generator) for openapi-generator.

## How to use

`python app.py` 

## To Do

- Create a python environment to containerize the libraries used by the project
- Build a tutorial, 
