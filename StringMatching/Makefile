clean:
	rm rabinKarp naive KMPAlgorithm

naive:
	gcc -g -o naive naive.c

rabinKarp:
	gcc -g -o rabinKarp rabinKarp.c

KMP:
	gcc -g -o KMPAlgorithm KMPAlgorithm.c

all:
	gcc -g -o naive naive.c
	gcc -g -o rabinKarp rabinKarp.c
	gcc -g -o KMPAlgorithm KMPAlgorithm.c

naiveText1: naive.c
	time ./naive "Moby Dick" MobyDick.txt

naiveText2: naive.c
	time ./naive "the" MobyDick.txt

naiveText3: naive.c
	time ./naive "Whales in the sea God's voice obey." MobyDick.txt

rabinKarpText1: rabinKarp.c
	time ./rabinKarp "Moby Dick" MobyDick.txt 255

rabinKarpText2: rabinKarp.c
	time ./rabinKarp "the" MobyDick.txt 255

rabinKarpText3: rabinKarp.c
	time ./rabinKarp "Whales in the sea God's voice obey." MobyDick.txt 255

KMPText1: KMPAlgorithm.c
	time ./KMPAlgorithm "Moby Dick" MobyDick.txt

KMPText2: KMPAlgorithm.c
	time ./KMPAlgorithm "the" MobyDick.txt

KMPText3: KMPAlgorithm.c
	time ./KMPAlgorithm "Whales in the sea God's voice obey." MobyDick.txt

naiveDNA1: naive.c
	time ./naive "TGATT" bacteria.txt

naiveDNA2: naive.c
	time ./naive "CCATATACTTCTTTA" bacteria.txt

naiveDNA3: naive.c
	time ./naive "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" bacteria.txt

rabinKarpDNA1: rabinKarp.c
	time ./rabinKarp "TGATT" bacteria.txt 255

rabinKarpDNA2: rabinKarp.c
	time ./rabinKarp "CCATATACTTCTTTA" bacteria.txt 255

rabinKarpDNA3: rabinKarp.c
	time ./rabinKarp "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" bacteria.txt 255

KMPDNA1: KMPAlgorithm.c
	time ./KMPAlgorithm "TGATT" bacteria.txt

KMPDNA2: KMPAlgorithm.c
	time ./KMPAlgorithm "CCATATACTTCTTTA" bacteria.txt

KMPDNA3: KMPAlgorithm.c
	time ./KMPAlgorithm "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" bacteria.txt


KMPRussian: KMPAlgorithm.c
	time ./KMPAlgorithm "шести" CrimeAndPunishment.txt

rabinKarpRussian: rabinKarp.c
	time ./rabinKarp "шести" CrimeAndPunishment.txt 255

naiveRussian: naive.c
	time ./naive "шести" CrimeAndPunishment.txt

naiveIll1: naive.c
	time ./naive "the" Illiad.txt

naiveIll2: naive.c
	time ./naive "Odysseus" Illiad.txt

naiveIll3: naive.c
	time ./naive "Hector" Illiad.txt

rabinKarpIll1: rabinKarp.c
	time ./rabinKarp "the" Illiad.txt 255

rabinKarpIll2: rabinKarp.c
	time ./rabinKarp "Odysseus" Illiad.txt 255

rabinKarpIll3: rabinKarp.c
	time ./rabinKarp "Hector" Illiad.txt 255

KMPIll1: rabinKarp.c
	time ./KMPAlgorithm "the" Illiad.txt

KMPIll2: rabinKarp.c
	time ./KMPAlgorithm "Odysseus" Illiad.txt

KMPIll3: rabinKarp.c
	time ./KMPAlgorithm "Hector" Illiad.txt