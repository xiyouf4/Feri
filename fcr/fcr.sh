#!/bin/bash

gcc -Wall -Werror -g -std=gnu11 server_main.c server.c proto.c socket.c log.c -o server
gcc -Wall -Werror -g -std=gnu11 client_main.c client.c client_menu.c proto.c socket.c log.c -o client
