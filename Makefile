
all: ./build ./libhh

./deps/libuv:
	git clone --depth 1 git://github.com/libuv/libuv.git ./deps/libuv

./deps/gyp:
	git clone --depth 1 https://chromium.googlesource.com/external/gyp.git ./deps/gyp
	# TODO: patch no longer applies
	#cd ./deps/gyp && curl -o issue_292.diff https://codereview.chromium.org/download/issue14887003_1_2.diff && patch pylib/gyp/xcode_emulation.py issue_292.diff

./build: ./deps/gyp ./deps/libuv
	deps/gyp/gyp --depth=. -Goutput_dir=./out -Icommon.gypi --generator-output=./build -Dlibrary=static_library -Duv_library=static_library -f make -Dclang=1

./libhh: ./src/libhh.c ./deps/libuv
	make -C ./build/ libhh 
	cp ./build/out/Release/libhh ./libhh

distclean:
	make clean
	rm -rf ./build

clean:
