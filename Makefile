COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R

all:
	$(MAKE) -C generator && $(COPY) generator/generator ./taskGenerator
	$(MAKE) -C simulator && $(COPY) simulator/simulator ./simDM
	$(MAKE) -C study && $(COPY) study/study ./studyDM

clean:
	$(MAKE) clean -C generator
	$(MAKE) clean -C simulator
	$(MAKE) clean -C study
