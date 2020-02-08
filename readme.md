# BibleSearch
This Python program takes multiple words, and searches them in the bible.

It takes advantage of sed and grep, to search data lists really fast.

To use compile.html, get JUBL2000.json:

`wgethttp://api.heb12.com/translations/en/jubl2000.json`

Rename it to jubl2000.js and add `var jubl200 = ` at the start of it.

Or, you can find everything here: http://api.heb12.com/biblesearch/

### Enhancement Ideas:
1. Sort word by first letter alphabetically, but then by popularity.
