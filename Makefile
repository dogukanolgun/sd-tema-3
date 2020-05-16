build-p1:
	gcc 1.c -o p1
build-p2:
	gcc reprezentanti.c -o p2
build-p3:
	gcc 3.c -o p3
build-p4:
	gcc 4.c -o p4
build-bonus:
	gcc bonus.c -o bonus
run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4
run-bonus:
	./bonus
clean:
	rm p1 p2 p3 p4 bonus
