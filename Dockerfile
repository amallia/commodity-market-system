FROM debian:latest

ENV DEBIAN_FRONTEND noninteractive

ENV MODE base
ENV PORT 3000

EXPOSE $PORT

COPY include /cms/include
COPY lib /cms/lib
COPY src /cms/src
COPY test /cms/test
COPY CMakeLists.txt /cms/
COPY run.sh /cms/

RUN apt-get -qq update \
    && apt-get -qqy install \
    libboost-all-dev \
    cmake \
    make \
    g++ \
    && rm -rf /var/lib/apt/lists/* \
    && cd cms && chmod +x /cms/run.sh \
    && mkdir build && cd build && cmake .. \
    && make

CMD [ "/bin/bash", "-c", "/cms/run.sh"]
