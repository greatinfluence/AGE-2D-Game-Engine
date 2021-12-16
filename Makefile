SUBDIRS = arlg/src snooker/src

all:
	@list='$(SUBDIRS)'; for subdir in $$list; do (cd $$subdir && make); done;

.PHONY: clean

clean:
	@list='$(SUBDIRS)'; for subdir in $$list; do (cd $$subdir && make clean); done;

