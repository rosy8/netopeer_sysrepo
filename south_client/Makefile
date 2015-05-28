sysrepo_ifc_daemon: sysrepo_ifc_daemon.c
	@-rm -rf sysrepo_ifc_daemon
	gcc -g -Wall -Wextra $^ ../libsrd.a -lxml2 -o $@;

.PHONY: clean
clean:
	@-rm -rf sysrepo_ifc_daemon
