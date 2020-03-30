# BibleSearch
This Python Flask API to take multiple words, and search them in the bible.
It can be used with or without the HTTP server part.

To compile bible data, run:
`node compile.js`

Some notes can be found in compile.js, and are needed to
be looked over before running.

### URL Parameters
words: The words to search. Seperate by space only.
callback: callback for JSONP
length: short/long. Can be used to return longer book names or shorter book names (Gen/Genesis)
page: Used to shorten the ammount results returned. Ex: 1-10, 10-20, etc

Examples:
http://api.heb12.com/search?words=god&&page=1-10

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
