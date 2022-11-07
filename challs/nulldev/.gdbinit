set width 0
set height 0
set verbose off

set print pretty on
set mem inaccessible-by-default off
set arch i386:x86-64

file ./bin/nulldev-dbg

# Write addresses of relevant variables
b main
commands 1
  printf "Address of message: %p\n", message
  printf "Address of flag_fd: %p\n", &flag_fd
  printf "Address of void_of_nothingness_fd: %p\n\n", &void_of_nothingness_fd

  printf "Bytes between message and flag_fd: %i\n", (int)&flag_fd - (int)&message
  printf "Bytes between message and void_of_nothingness_fd: %i\n\n", (int)&void_of_nothingness_fd - (int)&message
  continue
end

# Break at scanf
b 33
commands 2
  printf "flag_fd value: %i (0x%08x)\n", flag_fd, flag_fd
  printf "void_of_nothingness_fd value: %i (0x%08x)\n", void_of_nothingness_fd, void_of_nothingness_fd
  continue
end

# Break after scanf
b 34
commands 3
  printf "flag_fd value: %i (0x%08x)\n", flag_fd, flag_fd
  printf "void_of_nothingness_fd value: %i (0x%08x)\n", void_of_nothingness_fd, void_of_nothingness_fd
  continue
end

run

