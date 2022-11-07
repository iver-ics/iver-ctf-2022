ARG progname=stackframe_massacre

FROM debian:latest AS build-base

RUN apt-get update -y && apt-get install -y \
    clang make \
    python3 python3-pip python3-dev git libssl-dev libffi-dev build-essential # pwntools

RUN python3 -m pip install --no-cache-dir --upgrade pip
RUN python3 -m pip install --no-cache-dir --upgrade pwntools

FROM build-base AS build

RUN useradd -m build

WORKDIR /home/build

# Build program
COPY ./src /home/build/src
COPY ./Makefile /home/build/
RUN make

# Test program
COPY ./test /home/build/test
RUN TERM=xterm make test

FROM debian:latest AS run-base

RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd

FROM run-base AS run-stage

RUN useradd -m ctf

WORKDIR /home/ctf

RUN cp -R /lib* /home/ctf && \
    cp -R /usr/lib* /home/ctf

RUN mkdir -p /home/ctf/bin && \
    cp /bin/sh /home/ctf/bin && \
    cp /bin/ls /home/ctf/bin && \
    cp /bin/cat /home/ctf/bin

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /start.sh
RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail

RUN chmod +x /start.sh

RUN chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf

RUN mkdir /home/ctf/dev && \
    mknod /home/ctf/dev/null c 1 3 && \
    mknod /home/ctf/dev/zero c 1 5 && \
    mknod /home/ctf/dev/random c 1 8 && \
    mknod /home/ctf/dev/urandom c 1 9 && \
    chmod 0666 /home/ctf/dev/*

CMD ["/start.sh"]

EXPOSE 28362

FROM run-stage

COPY --from=build /home/build/bin/stackframe_massacre ./program
COPY --from=build /home/build/flag.txt ./flag.txt
RUN chown root:ctf ./program ./flag.txt
RUN chmod 750 ./program
RUN chmod 640 ./flag.txt
