# Steiner Tree Heuristics (for submission to PACE 2018)

The source code is written in `st-steiner.c`. The sample input available on the website is copied in `heuristic/input.gr`. To run the program on the sample input, execute ```./run.sh```. The original input is available [here]

## Heuristics 1:
* reduce all the non-terminals with degree 2 (if a terminal has degree 2, then reduce its non-terminal neighbors so that they are of degree at least three. Update the new weights accordingly.)
* return the MST of the reduced graph
* if a leaf of the MST is non-terminal, delete it. Then the MST will have all terminal leaves. (see what might go wrong after here)
* what next?


Good luck.

Edit:

Here is a [paper] on the possible reductions.

[here]: http://www.lamsade.dauphine.fr/~sikora/pace18/heuristic.zip
[paper]: https://opus4.kobv.de/opus4-zib/files/252/SC-96-42.pdf
