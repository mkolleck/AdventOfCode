YEARS := 2022 2023 2024

.PHONY: all
all: $(YEARS)

.PHONY: clean
clean:
	for y in $(YEARS) ; do $(MAKE) -C $$y clean ; done

.PHONY: $(YEARS)
$(YEARS):
	$(MAKE) -C $@
