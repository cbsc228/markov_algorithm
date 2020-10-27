 Welcome to my Markov Algorithm!
 Name:Craig Scarboro

-----DESCRIPTION-----
 This program runs a markov algorithm according to production rules provided by the user
 in a formatted .txt file. When the program is running the algorithm, it first checks if
 the current string, or substring, matched the current rule being checked against. If there is
 a match, the program replaces the matched string with the replacement portion of the current
 rule and moves to the next rule according to the current rule. If there is not a match, the program
 checks if there is a match in the numerically next rule and so on. 
 
 This program supports a maximum input of 1000 rules.

-----TO RUN THE PROGRAM-----
 Type "make run" to compile and run the program.

 Typing "make clean" will clean up the object files generated during coimpilation.

-----USING THE PROGRAM-----
 The program will ask for a text file (including the .txt extension), import the data
 into the program, and run the markov algorithm according to the provided rules.