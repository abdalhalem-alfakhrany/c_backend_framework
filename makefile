CC=gcc
OUT=build/socket

app:
	$(CC) src/main.c src/common.c src/request.c src/response.c src/test_site.c src/website.c -o $(OUT) -ggdb

clean:
	rm build/*