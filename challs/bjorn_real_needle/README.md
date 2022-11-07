# The real needle

This challenge was created because I fubar:ed the Needle-challenge.

There are a thousand files with a fake flag and one file with the correct flag.

To solve the challenge you should first cat one of the flag files and get the fake flag.

Then you can do:
```
echo "cat *" |nc spooktoberctf.se 22078 | sed 's/spooky{stil1_caNt_hide_fr0m_you}//g'
```

Then the needle will pop out :-)

