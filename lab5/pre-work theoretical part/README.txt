README file: describes all different files and their purpose

header files: 
Files that include Defines and declarations of all functions and variables that 
will be used.

source files: 
The files that include the logic of the system by the following distribution:
Main - The main program, this is the program that we need to perform in its most abstract view,
this layer only uses functions given to the user by the API layer

API - This layer includes functions that can be used in the main layer, it is based on 
the somewhat abstract functions in the HAL layer and geenrates from them more complex 
and abstract functions

HAL - This layer contains basic functions that are based on the BSP layer's configurations 
and MACRO definitions, therefore it uses the most basic building blocks of the hardware to 
start performing actions in a somewhat abstract manner 

BSP - This is the "lowest" layer in the system, it includes only defines and basic configurations
of specific things in the system, such as ports, registers configurations etc. 
