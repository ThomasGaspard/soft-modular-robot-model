# soft-modular-robot-model
#Changing the location of the project/files/first instalation

Upon first installation, the user needs to modify the paths in main.cpp (RESULT_PATH -> where the results will be stored and under what name (should be a .csv) TIME_PATH -> where is the file "time.md", ROBOT_PATH -> where is the file "robot.md"). Those values may be modified later if the user wish.

#Changing the robot used

The programm does not be to be recompiled when different robots are modelised. Instead, the user should only modify the "robot.md" file.
This file must contain the rest size and max size of each cell, separated by a blank space (space, tab, CR) and, after this done, the string "EOF". The order given is the order of construction for the robot (that is, for a forward movement to the right, from left to right). For instance, a robot made of three modules having a rest size of 12 (respectively 13.1 and 9.9), and a max size of 14.1 (respectively 15.7 and 12) the file should be :

12 14.1
13.1 15.7
9.9 12
EOF

Whatever is left after the "EOF" will not be processed and may be left as a comment.
#Changing the sequence of actuation

In the file "time.md", the user should put, for each module (in the same order as in "robot.md"), the time at wich its actuation starts, a blank space (space, tab, CR), the string "EOST", a blank space (space, tab, CR), and the description of the sequence.
For instance, with the same robot we used before, if the second module starts 0.3s after the first one (that starts being actuated at the begining of the simulation), and the last one 0.4s after the second one, the file should look like

0.0
0.3
0.7
EOST

Please note that if there is not the number of starting times is different from the number of modules, the program will raise an error and crash.

The sequence must be describe as the duration of the four phases being : INFLATION BREAK DEFLATION BREAK
For instance, if the modules are to be inflated during 0.6s, hold their maximum size for 1s and then deflate in 0
2 second, the sequence is :
0.6 1 0.2 0
Note that the last break keep the module into an "actuated" status but does not affect its size.
During the simulation, if all of the modules have been actuaded (that is when all of the modules have been actuated and their actuation is over), the actuation starts again with the same patern. Whatever is written after thos 4 values will not be processed and may be left as a comment.

#Getting the result

The result will be saved as a csv file for treatment. The file is made of 4 columns, the first being the time, the second the x-position of the center of the last module, the second the x-position of the right module, and the last the position of the center of gravity of the robot at given time.
A python3 script plotting XG over time is given in the depositery.
