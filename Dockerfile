FROM ubuntu
RUN apt-get update \
    && apt-get install -y libsfml-dev cmake g++ \
    && apt-get install -y libx11-dev libxext-dev
WORKDIR /project
COPY fonts fonts
COPY sounds sounds
COPY src src
COPY textures textures
COPY CMakeLists.txt CMakeLists.txt
RUN cmake -S . -B build/ \
    && cd build \
    && make \
    && cp BabaIsYou /project/BabaIsYou    
CMD ["/project/BabaIsYou"]