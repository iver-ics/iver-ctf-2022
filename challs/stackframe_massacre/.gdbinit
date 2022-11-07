set width 0
set height 0
set verbose off

set print pretty on
set mem inaccessible-by-default off
set arch i386:x86-64

file ./bin/stackframe_massacre-dbg

# Write addresses of relevant variables
b exploit_me
commands 1
  printf "Stack pointer: %p\n", $sp
  printf "Address of stuff: %p\n", stuff
  printf "Address of gets return value: %p\n", stuff+128
  printf "Saved rip address should be: %p\n", stuff+128+8
  printf "Saved rip value should be: %p\n\n", *(unsigned long long)(stuff + 128 + 8)

  printf "Bytes between stuff and return pointer: %i\n\n", 136

  info frame

  x/64x $sp

  continue
end

run
