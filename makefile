EXTENSION = pg_mq        # the extensions name
# DATA = base36--0.0.1.sql  # script files to install

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

all: main.c
	  gcc main.c -o main -lcurl -I`pg_config --includedir-server`

clean:
	  $(RM) main


