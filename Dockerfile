FROM gcc:latest

RUN apt update -y && \
    apt install -y gcc cppcheck clang-tidy python3-pip libc6-dbg cmake lcov tree libgtest-dev && \
    pip install cpplint

ADD . /iz2
