# BibleSearch
This Python program takes multiple words, and searches them in the bible.

To compile bible data, run:
`node compile.js`

Some notes can be found in compile.js, and are needed to
be looked over before running.

### Enhancement Ideas:
1. Sort word by first letter alphabetically, but then by popularity.

### How It Works:

BibleSearch is a Bible search engine optimized for speed rather than portibility.
It weights about 20MB.

In a nutshell, there are 2 main files.
One with every word in the bible, sorted alphabetically, and one with
the verses that use it. Both are the same length. It starts out by searching the words file with GNU Grep.

To make the searching quicker, a file stating on what line in the words file a letter starts
off with. Ex: A: 1 B: 10,000 C: 20,000, etc.

If the word is matched, then the corosponding line in the verses file is
grabbed. Each line in the verses file is a JSON array, but it is not JSON alltogether.

If the request is only one word, then the read JSON will be returned. If longer than one,
then the process starts over again, but instead of returning,
it uses a Python function to find matches in both arrays.
