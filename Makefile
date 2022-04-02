build_static:
	mkdir build && \
	cd build && \
	cmake -D STATIC=ON -D STATIC_TESTS=ON ..  && \
	make

build_shared:
	mkdir build && \
	cd build && \
	cmake -D SHARED=ON -D SHARED_TESTS=ON ..  && \
	make

clean:
	rm -rf build && \
	clear

packages:
	sudo apt-get update -y && \
	sudo apt-get install build-essential && \
	sudo apt-get install -y cppcheck clang-tidy python3-pip libc6-dbg lcov libgtest-dev && \
	pip3 install cpplint && \
	sudo apt-get install valgrind

analysis_static: 
	./linters/run_static.sh

analysis_shared:
	./linters/run_shared.sh

test_static:
	./build/tests_static/test_calc

test_shared:
	./build/tests_shared/test_calc