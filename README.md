# take
##### NAME
take - easily slice and substring text.
##### SYNOPSIS
**take** [**-l** | **--by-lines**] _start:stop:end_

##### DECRIPTION
**take** slices a string read from stdin (mostly for use with pipes) by using a start-index (inclusive), stop index (exclusive) and a step size, very much python-like.
**take** also supports splitting the original text by a delimiter and then choosing one or more splitted parts.

##### EXAMPLES

| command | output           | 
| ------------- |:-------------:| 
| echo "Hello" \| take :       | Hello | 
| echo "Hello" \| take \::-1        | olleH      | 
| echo "Hello" \| take 1:3 |  el     | 
| echo "Hello" \| take :-1  |  Hell     | 
| echo "Hello" \| take -3:-1 |  ll     | 
| echo "Hello" \| take ::2 |  Hlo     | 
| echo "Hello" \| take 1 |  e     | 
| echo "Hello\nWorld\n" \| take -l 1: |  World     | 
| echo "Hello\nWorld\n" \| take -l :1 |  Hello     | 
