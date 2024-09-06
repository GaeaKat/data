FROM gigamonkey/gigamonkey-base-dev:latest

WORKDIR /home/data
COPY . .
RUN mkdir build
WORKDIR /home/data/build
RUN cmake ../
RUN cmake --build .
CMD ["ctest"]