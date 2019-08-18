FROM gcc:8 AS build

WORKDIR /home
COPY ./app.cpp /home
RUN g++ app.cpp -o app -g -O0 -std=c++17 -static

FROM centos:7 
WORKDIR /home
COPY --from=build /home/app /home/app
CMD ["./app"]

