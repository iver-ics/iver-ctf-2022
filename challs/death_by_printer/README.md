# Death by printer

- Category: `OSINT`
- Challenge author: **Robert Teir**

## Description

The sysadmin Bob has just died in a horrible printer accident. Or was it an accident? When you go to pack up his computer you notice a file called secrets.kdbx, strange you think…? On Bobs monitor the webpage of Iver.com is open. You don’t have the password for the file, what could it be?
Bra!

## Writeup

1. Extract all the words from iver.com (cewl https://www.iver.com -w word_list.txt -d 1)
2. extract hash with a tool like keepass2john (.\keepass2john.exe Cdb.kdbx)
3. Run john with the word list