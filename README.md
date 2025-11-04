## Repo for Lab Week 10
Complete assignment as assigned.

Note, no make file is provided.  It is suggested you create one to be more efficient building your programs.

### Lab Research
- **What is a signal disposition?**
  A signal disposition is the action a process will take when it recieves a specific signal.
- **What is a signal handler? What is it used for?**
  A signal handler is a function called by the target when the corresponding signal occurs. If it is set up, the kernel does not follow the default action and instead calls the function.
- **Name and describe each of the five (5) default dispositions?**
  Term - Used to terminate a process
  Ign - Used to ignore a signal
  Core - Used to terminate processes and create a core dump file
  Stop - Used to stop (suspend) a process
  Cont - Used to continue a process if it is stopped, else ignored
- **Name and describe one way to programmatically send a signal to a process. Be able to give an example (the code) to send a signal.**
  An example is if you wanted to send a signal interrupt to interrupt and kill a process. Here is a code example:
``` C
  #include <signal.h> // For signal definitions and kill()
  #include <sys/types.h> // For pid_t
  #include <unistd.h> // For getpid()
  #include <stdio.h>
  
  int main() {
      pid_t target_pid = getpid();

      // Send the SIGINT signal to the current process
      if (kill(target_pid, SIGINT) == -1) {
          printf("Error: KILL failed.");
          return 1;
      }
  
      // Process will be terminated at this point

      return 0;
  }
```
  This example kills the current running process, but you can use any process id you want.
- **Name and describe one way to send a signal to a process from the command line. Be able to give an example (the command, key combination, etc.) to send a signal.**
  If you wanted to do the same thing but in the command line, you could use something like this:
  ```C
  kill -s SIGINT 12345
  ```
  Where '12345' is the pid of the process you wanted to interrupt.
**Name and describe the signal, define the default disposition taken by the operating system if a process does not define a signal handler, and determine if the disposition can be overridden by a signal handler.**
- **SIGINT**: SIGINT is used to interrupt a process. By default, the process terminates upon recieving a SIGINT signal. The default disposition of SIGINT can be overridden by a signal handler.
- **SIGTERM**: SIGTERM is used to terminate a process. By default, the process terminates. The default disposition of SIGTERM can be overridden by a signal handler.
- **SIGUSR1**: SIGUSR1 is made to be a user defined signal. Thus, there is no default disposition and the default disposition of SIGUSR1 can be overridden by a signal handler.
- **SIGKILL**: SIGKILL is used to terminate a process. The signal is immediately terminated, and there is no way to override the default disposition of SIGKILL by a signal handler.
- **SIGSTOP**: SIGSTOP is used to stop a process. The process can only be resumed by the SIGCONT. There is no way to override the default disposition of SIGSTOP by a signal handler.
