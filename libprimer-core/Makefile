VERSION=$(shell cat Cargo.toml | grep "^version" | sed "s/version = //" | sed 's/"//g')
VERSION_MAJOR=$(shell echo $(VERSION) | cut -d "." -f 1)
VERSION_MINOR=$(shell echo $(VERSION) | cut -d "." -f 2)
VERSION_PATCH=$(shell echo $(VERSION) | cut -d "." -f 3)

default:
	cargo build --release
	cp target/release/libprimer.so target/release/libprimer-core.so.$(VERSION)

clean:
	cargo clean

