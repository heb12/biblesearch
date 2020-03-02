# BibleSearch
This Python program takes multiple words, and searches them in the bible.

To use compile.html, get JUBL2000.json:

`wget http://api.heb12.com/translations/en/jubl2000.json`

Rename it to jubl2000.js and add `var jubl200 = ` at the start of it.

Or, you can find everything in use here: http://api.heb12.com/biblesearch/

### Enhancement Ideas:
1. Sort word by first letter alphabetically, but then by popularity.

### How It Works:

BibleSearch is a Bible search engine optimized for speed rather than portibility. It weights about 20MB.

In a nutshell, there are 2 main files. One with every word in the bible, sorted alphabetically, and one with the verses that use it. Both are the same length. It starts out by searching the words file with GNU Grep.
To make the searching quicker, a file stating on what line in the words file a letter starts off with. Ex: A: 1 B: 10,000 C: 20,000, etc.

If the word is matched, then the corosponding line in the verses file is grabbed. Each line in the verses file is a JSON array, but it is not JSON alltogether.
If the request is only one word, then the read JSON will be returned. If longer than one, then the process starts over
again, but instead of returning, it uses a Python function to find matches in both arrays.