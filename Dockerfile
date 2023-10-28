# Download base image ubuntu 23.04
FROM ubuntu:23.04

# LABEL about the custom image
LABEL version="1.0"
LABEL description="This is custom Docker Image for gcc, check.h, lcov, and pkg-config."

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive

# Update Ubuntu Software repository
RUN apt-get update

# Install gcc, lcov, pkg-config, check library, and git
RUN apt-get install -y gcc lcov pkg-config check git

# Clone GitHub repository
RUN git clone https://github.com/Alpgirl/Smart_calc.git


# to build image enter command docker build -t smart_calc .
# to run container enter command docker run -it smart_calc

