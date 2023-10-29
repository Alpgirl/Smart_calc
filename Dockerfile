# Download base image ubuntu 23.04
FROM ubuntu:23.04

# LABEL about the custom image
LABEL version="1.0"
LABEL description="This is custom Docker Image for gcc, check.h, lcov, and pkg-config."

# Disable Prompt During Packages Installation
ARG DEBIAN_FRONTEND=noninteractive

# Update Ubuntu Software repository
RUN apt update

# Install gcc, lcov, pkg-config, check library, git, and make
RUN apt install -y lcov pkg-config

# Clone GitHub repository
RUN git clone https://github.com/Alpgirl/Smart_calc.git

# 
COPY 

# Change the working directory
WORKDIR /Smart_calc/src

# Run make run
CMD ["make", "run"]


# to build image enter command docker build -t smart_calc .
# to run container enter command docker run -it --rm smart_calc
