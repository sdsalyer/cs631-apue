# CS631 APUE Homework Assignments General Information

Unless stated otherwise in the individual assignment, the following applies:

- All code needs to compile without any warnings or errors (i.e. using '-Wall
  -Werror -Wextra') on a NetBSD 10.x system, using the default compiler ('cc' or 'gcc').

  Testing your code for portability on other unix platforms you may have
  access to is probably a good idea, but in the end grading is done on
  on a NetBSD 10.x system.

  If you develop your programs on another system, remember to test them on
  a NetBSD 10.x system before submitting them!

- Code that does not compile successfully will receive 0 points.
  Before you submit anything, make sure to compile it.  Even if you just make
  a one-character change in the last minute, compile it before submitting the
  source code.

- All code should be well-formatted according to
  https://stevens.netmeister.org/631/style, with line breaks near 80
  characters and consistent indentation and style.

- Code should contain _useful_ commentary _where necessary_.

- All programs should exhibit standard unix behaviour with respect to return
  values, handling of errors, handling of stdin, stdout and stderr,
  command-line flags etc.

- All programs should follow the principle of least surprise for the user.

- The only files to submit are:
  - the source code files
  - a Makefile
  - a README file containing additional commentary or explanations of the
    code, problems encountered, limitations known etc.
  - the completed 'checklist' for this assignment
    https://stevens.netmeister.org/631/checklist

  Do NOT submit any binary files, executables or data input or output.

- When submitting your homework, please create a directory named after your
  username in which to store all the files to submit, then create a tar
  archive of that directory.  Email the file to me at jschauma@stevens.edu
  with a subject line of "[CS631]: HW #N: username"

- The due date is always given in the date format YYYY-MM-DD HH:MM:SS,
  according to our systems local time (EST or EDT).  The due date is always
  fixed, and no late submissions are accepted.
