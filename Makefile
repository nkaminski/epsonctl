PREFIX := /usr

epsonctl: epsonctl.c
	$(CC) -o epsonctl epsonctl.c

.PHONY: clean install uninstall

clean:
	$(RM) epsonctl

install: epsonctl
	install -m755 epsonctl $(PREFIX)/bin

uninstall:
	$(RM) $(PREFIX)/bin/epsonctl
