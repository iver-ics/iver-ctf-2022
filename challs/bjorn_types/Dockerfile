FROM ubuntu:22.04

RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd

RUN useradd -m ctf

WORKDIR /home/ctf

RUN mkdir -p /home/ctf/usr

RUN cp -a /lib /home/ctf/lib && \
    cp -a /lib64 /home/ctf/lib64 && \
    cp -a /lib32 /home/ctf/lib32 && \
    cp -a /libx32 /home/ctf/libx32 && \
    cp -a /usr/lib /home/ctf/usr/lib && \
    cp -a /usr/lib64 /home/ctf/usr/lib64 && \
    cp -a /usr/lib32 /home/ctf/usr/lib32 && \
    cp -a /usr/libx32 /home/ctf/usr/libx32

RUN mkdir /home/ctf/dev && \
    mknod /home/ctf/dev/null c 1 3 && \
    mknod /home/ctf/dev/zero c 1 5 && \
    mknod /home/ctf/dev/random c 1 8 && \
    mknod /home/ctf/dev/urandom c 1 9 && \
    chmod 666 /home/ctf/dev/*

RUN mkdir /home/ctf/bin && \
    cp /bin/sh /home/ctf/bin && \
    cp /bin/ls /home/ctf/bin && \
    cp /bin/cat /home/ctf/bin

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /start.sh
RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail

RUN chmod +x /start.sh

COPY ./bin/ /home/ctf/
RUN chown -R root:ctf /home/ctf && \
    chmod -R 750 /home/ctf && \
    chmod 740 /home/ctf/flag.txt

CMD ["/start.sh"]

EXPOSE 9999