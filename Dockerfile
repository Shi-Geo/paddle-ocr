FROM ubuntu:18.04
ARG DEBIAN_FRONTEND=noninteractive
# Установка зависимостей для сборки GCC, CMake и OpenCV
RUN apt update && \
    apt install -y build-essential wget curl tar unzip git cmake pkg-config \
                   libjpeg-dev libpng-dev libtiff-dev libavcodec-dev \
                   libavformat-dev libswscale-dev libv4l-dev \
                   libxvidcore-dev libx264-dev libgtk-3-dev \
                   libatlas-base-dev gfortran python python3-dev nano && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

RUN apt update && \
    apt install -y software-properties-common && \
    add-apt-repository "deb http://archive.ubuntu.com/ubuntu/ focal main restricted universe multiverse" && \
    apt update && \
    apt install -y build-essential gcc-8 g++-8 wget curl tar


# Установка CMake 3.10.3
WORKDIR /tmp
RUN wget https://github.com/Kitware/CMake/releases/download/v3.10.3/cmake-3.10.3.tar.gz  && \
    tar -xzvf cmake-3.10.3.tar.gz && \
    cd cmake-3.10.3 && \
    ./bootstrap --prefix=/usr/local && \
    make -j$(nproc) && \
    make install

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 60 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 60
    
RUN cmake --version

# Установка OpenCV 4.8.0
WORKDIR /tmp
RUN git clone --depth=1 --branch 4.8.0 https://github.com/opencv/opencv.git  && \
    git clone --depth=1 --branch 4.8.0 https://github.com/opencv/opencv_contrib.git 

WORKDIR /tmp/opencv
RUN mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -D OPENCV_EXTRA_MODULES_PATH=/tmp/opencv_contrib/modules \
          -D BUILD_TESTS=OFF \
          -D BUILD_PERF_TESTS=OFF \
          -D BUILD_EXAMPLES=OFF \
          -D ENABLE_CXX11=ON \
          .. && \
    make -j$(nproc) && \
    make install

RUN mv /usr/local/include/opencv4/opencv2 /usr/local/include

WORKDIR /tmp
RUN git clone https://github.com/PaddlePaddle/Paddle-Lite.git && \
    cd Paddle-Lite && \
    git checkout release/v2.12 && \
    ./lite/tools/build_linux.sh --arch=x86 --with_extra=ON full_publish

WORKDIR /tmp
RUN cd Paddle-Lite && \
    rm -rf third-party && \
    ./lite/tools/build.sh build_optimize_tool --with_extra=ON

WORKDIR /tmp
RUN wget https://paddleocr.bj.bcebos.com/dygraph_v2.0/ch/ch_ppocr_mobile_v2.0_rec_infer.tar && \
    tar -xf ch_ppocr_mobile_v2.0_rec_infer.tar

WORKDIR /tmp
RUN cd /tmp/Paddle-Lite/build.opt/lite/api && \
    ./opt --model_file=/tmp/ch_ppocr_mobile_v2.0_rec_infer/inference.pdmodel  --param_file=/tmp/ch_ppocr_mobile_v2.0_rec_infer/inference.pdiparams  --optimize_out_type=naive_buffer --optimize_out=ch_ppocr_mobile_v2.0_rec_infer_opt

# Копируем проект
WORKDIR /app
COPY . .

RUN mkdir -p build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --config Release && \
    mv OCR /ocr-app

RUN ls -la build/

RUN mkdir -p /output

WORKDIR /

CMD ["/ocr-app"]
