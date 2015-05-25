sysrepo_ifc_daemon: sysrepo_ifc_daemon.c
	gcc -Wall -Wextra $^ libsrd.a -lxml2 -o $@;

.PHONY: clean
clean:
	rm -rf sysrepo_ifc_daemon
