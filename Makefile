default:
	@$(CC) biblec/biblec.c test.c
	@./a.out
	@rm *.out

setup:
	@cd biblec; mkdir bibles; cd bibles;
	@cd biblec/bibles; wget http://api.heb12.com/translations/biblec/kj2000.i
	@cd biblec/bibles; wget http://api.heb12.com/translations/biblec/kj2000.t