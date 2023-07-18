VERSION=$(shell cat Cargo.toml | grep "^version" | sed "s/version = //" | sed 's/"//g')
VERSION_MAJOR=$(shell echo $(VERSION) | cut -d "." -f 1)
VERSION_MINOR=$(shell echo $(VERSION) | cut -d "." -f 2)
VERSION_PATCH=$(shell echo $(VERSION) | cut -d "." -f 3)

INSTALL_DIR=$(shell ../tools/dist-install-dir.sh)

default:
	cargo build --release

install: $(DESTDIR)/usr/include/primer/core
	cp include/primer/core/*.h $(DESTDIR)/usr/include/primer/core/
	strip target/release/libprimer-core.so.$(VERSION)
	cp target/release/libprimer-core.so.$(VERSION) $(DESTDIR)/$(INSTALL_DIR)
	cp -P target/release/libprimer-core.so.$(VERSION_MAJOR).$(VERSION_MINOR) $(DESTDIR)/$(INSTALL_DIR)
	cp -P target/release/libprimer-core.so.$(VERSION_MAJOR) $(DESTDIR)/$(INSTALL_DIR)
	cp -P target/release/libprimer-core.so $(DESTDIR)/$(INSTALL_DIR)

$(DESTDIR)/usr/include/primer/core:
	mkdir -p $(DESTDIR)/usr/include/primer/core

test:
	cargo test --release

clean:
	cargo clean

version-major:
	@echo $(VERSION_MAJOR)

version-minor:
	@echo $(VERSION_MINOR)

version-patch:
	@echo $(VERSION_PATCH)
