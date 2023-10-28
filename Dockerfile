# Download base image ubuntu 20.04
FROM ubuntu:20.04

# LABEL about the custom image
LABEL version="1.0"
LABEL description="This is custom Docker Image for gcc, check.h, lcov, and pkg-config."

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive

# Update Ubuntu Software repository
RUN apt-get update

# Install gcc, lcov, pkg-config and check library
RUN apt-get install -y gcc lcov pkg-config check

# Copy project directory into the docker image
COPY ./src /root/src

# to build image enter command docker build -t smart_calc-main .
# to run container enter command docker run -it smart_calc-main

