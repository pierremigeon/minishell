
# Project Get_next_line (GNL):

This function, called "get_next_line()" reads from a file descriptor, one line at a time. Each call of the function returns subsequent lines read from the file descriptor, until EOF is reached. In this repository, I've included a main that can be compiled for the sake of demonstrating the function. Simply use the make command to compile, then run ./a.out using any textfile as input. Functionally, this will appear as though the user is running the unix cat command, due to the way the function is used in the main. 

### Return Value
	- return 1 for each line read
	- return 0 when EOF is reached
	- Return -1 when an error occurs

### Bonus
	- Uses single static variable
	- Supports multiple file descriptors (including switching back and forth between fds). 
