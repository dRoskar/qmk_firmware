@ECHO OFF
docker container rm qmk
docker image rm qmk
docker build . -t qmk
docker create --name qmk qmk