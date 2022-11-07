FILENAME=usb-backup

.PHONY: all
all: out/$(FILENAME).zip

.PHONY: imagemagick
imagemagick: Dockerfile-imagemagick
	sudo docker build -t imagemagick -f ./Dockerfile-imagemagick .

build:
	mkdir -p build

out:
	mkdir -p out

build/flag.png: src/flag.txt imagemagick build
	sudo docker run -it --rm -v $$( pwd )/build:/build imagemagick convert -background white -fill black -font "FreeMono" -pointsize 80 "label:$$( cat src/flag.txt )" -strip /build/flag.png
	sudo chown $$USER: build/flag.png

.PHONY: build-image
build-image: Dockerfile-build src/build.sh
	sudo docker build -t shred -f ./Dockerfile-build .

build/dummy-files: src/dummy-files/*
	rm -rf build/dummy-files
	cp -a src/dummy-files build/dummy-files

build/$(FILENAME).img: build-image build/flag.png build/dummy-files
	sudo docker run --privileged -it --rm -v $$( pwd )/build:/root/build -e FILENAME=build/$(FILENAME).img -e PARTITION=no -e FLAG_FILE_PATH=build/flag.png -e DUMMY_FILES_PATH=build/dummy-files shred

out/$(FILENAME).img: build/$(FILENAME).img out
	cp build/$(FILENAME).img out/$(FILENAME).img

out/$(FILENAME).zip: out/$(FILENAME).img out
	rm -f out/$(FILENAME).zip
	zip -9 -j out/$(FILENAME).zip out/$(FILENAME).img

.PHONY: clean
clean:
	rm -rf build/*
	rm -rf out/*


